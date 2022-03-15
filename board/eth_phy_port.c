/*
 * Copyright (c) 2021 hpm
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2022-01-11   hpm     First version
 */

#include "rtthread.h"

#ifdef RT_USING_PHY
#include <rtdevice.h>
#include <rtdbg.h>
#include "hpm_enet_drv.h"
#include "eth_phy_port.h"
#include "hpm_soc.h"
#include "ethernetif.h"

extern struct eth_device eth_dev;

static phy_device_t phy_dev;
static struct rt_mdio_bus mdio_bus;
static struct rt_phy_ops phy_ops;

static rt_phy_status phy_init(void *object, rt_uint32_t phy_addr, rt_uint32_t src_clock_hz)
{
    rt_pin_mode(PHY_RST_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(PHY_RST_PIN, PIN_LOW);
    rt_thread_mdelay(50);
    rt_pin_write(PHY_RST_PIN, PIN_HIGH);
}

static rt_size_t phy_read(void *bus, rt_uint32_t addr, rt_uint32_t reg, void *data, rt_uint32_t size)
{
    *(uint16_t *)data = enet_read_phy(((struct rt_mdio_bus *)bus)->hw_obj, addr, reg);

    return size;
}

static rt_size_t phy_write(void *bus, rt_uint32_t addr, rt_uint32_t reg, void *data, rt_uint32_t size)
{
    enet_write_phy(((struct rt_mdio_bus *)bus)->hw_obj, addr, reg,  *(uint16_t *)data);

    return size;
}

static rt_phy_status phy_get_link_status(rt_bool_t *status)
{
    uint16_t reg_status;

    reg_status = enet_read_phy((ENET_Type *)phy_dev.phy.bus->hw_obj, phy_dev.phy.addr, PHY_BASIC_STATUS_REG);

#if PHY_AUTO_NEGO
    reg_status &= PHY_AUTONEGO_COMPLETE_MASK | PHY_LINKED_STATUS_MASK;
    *status = reg_status ? RT_TRUE : RT_FALSE;

#else
    reg_status &= PHY_LINKED_STATUS_MASK;
    *status = reg_status ? RT_TRUE : RT_FALSE;
#endif

    return PHY_STATUS_OK;
}

static rt_phy_status phy_get_link_speed_duplex(rt_uint32_t *speed, rt_uint32_t *duplex)
{
    uint16_t reg_status;

    reg_status = enet_read_phy((ENET_Type *)phy_dev.phy.bus->hw_obj, phy_dev.phy.addr, PHY_STATUS_REG);

    *speed = PHY_STATUS_SPEED_100M(reg_status) ? PHY_SPEED_100M : PHY_SPEED_10M;
    *duplex = PHY_STATUS_FULL_DUPLEX(reg_status) ? PHY_FULL_DUPLEX: PHY_HALF_DUPLEX;

    return PHY_STATUS_OK;
}

static void phy_status_polling(void *parameter)
{
    int ret;
    phy_info_t phy_info;
    rt_uint32_t status;
    rt_device_t dev;
    rt_phy_msg_t msg;
    rt_uint32_t speed, duplex;
    phy_device_t *phy_dev = (phy_device_t *)parameter;

    phy_dev->phy.ops->get_link_status(&status);

    if (status)
    {
        phy_dev->phy.ops->get_link_speed_duplex(&phy_info.phy_speed, &phy_info.phy_duplex);

        ret = memcmp(&phy_dev->phy_info, &phy_info, sizeof(phy_info_t));
        if (ret != 0)
        {
            memcpy(&phy_dev->phy_info, &phy_info, sizeof(phy_info_t));
        }
    }

    if (phy_dev->phy_link != status)
    {
        phy_dev->phy_link = status ? PHY_LINK_UP : PHY_LINK_DOWN;
        eth_device_linkchange(&eth_dev, status);
        LOG_I("PHY Status: %s", status ? "Link up" : "Link down\n");
        if (status == PHY_LINK_UP)
        {
            LOG_I("PHY Speed:  %s", phy_dev->phy_info.phy_speed & PHY_SPEED_100M ? "100Mbps" : "10Mbps");
            LOG_I("PHY Duplex: %s\n", phy_dev->phy_info.phy_duplex & PHY_FULL_DUPLEX ? "full duplex" : "half duplex");
        }
    }
}

static void phy_detection(void *parameter)
{
    uint8_t detected_count = 0;
    struct rt_phy_msg msg = {PHY_ID1_REG, 0};
    phy_device_t *phy_dev = (phy_device_t *)parameter;
    rt_uint32_t i;

    phy_dev->phy.ops->init(phy_dev->phy.bus->hw_obj, phy_dev->phy.addr, PHY_MDIO_CSR_CLK_FREQ);

    while(phy_dev->phy.addr == 0xffff)
    {
        /* Search a PHY */
        for (i = 0; i <= 0x1f; i++)
        {
            ((rt_phy_t *)(phy_dev->phy.parent.user_data))->addr = i;
            phy_dev->phy.parent.read(&(phy_dev->phy.parent), 0, &msg, 1);

            if (msg.value == PHY_ID1)
            {
                phy_dev->phy.addr = i;
                break;
            }
        }

        detected_count++;
        rt_thread_mdelay(1000);

        if (detected_count > 12)
        {
            LOG_E("No PHY device was detected, please check hardware!\n");
        }
    }

    LOG_D("Found a PHY, address:0x%02x\n", phy_dev->phy.addr);
}

static void phy_monitor_thread_entry(void *args)
{
    rt_timer_t phy_status_timer;
    phy_device_t *phy_dev = (phy_device_t *)args;

    phy_detection(phy_dev);
    phy_status_timer = rt_timer_create("PHY_Monitor", phy_status_polling,
                                        phy_dev, RT_TICK_PER_SECOND, RT_TIMER_FLAG_PERIODIC);

    if (!phy_status_timer || rt_timer_start(phy_status_timer) != RT_EOK)
    {
        LOG_E("Start link change detection timer failed\n");
    }
}

int phy_device_register(void)
{
    rt_err_t err = RT_ERROR;
    rt_thread_t thread_phy_monitor;

    /* Set PHY address */
    phy_dev.phy.addr = 0xffff;

    /* Set bus */
    mdio_bus.hw_obj = HPM_ENET1;
    mdio_bus.name = "MDIO";
    mdio_bus.ops->read = phy_read;
    mdio_bus.ops->write = phy_write;
    phy_dev.phy.bus = &mdio_bus;

    /* Set ops for PHY status */
    phy_ops.init = phy_init;
    phy_ops.get_link_status = phy_get_link_status;
    phy_ops.get_link_speed_duplex = phy_get_link_speed_duplex;
    phy_dev.phy.ops = &phy_ops;

    rt_hw_phy_register(&phy_dev.phy, PHY_NAME);

    /* Start PHY monitor */
    thread_phy_monitor = rt_thread_create("PHY", phy_monitor_thread_entry, &phy_dev, 1024, RT_THREAD_PRIORITY_MAX - 2, 2);

    if (thread_phy_monitor != RT_NULL)
    {
        rt_thread_startup(thread_phy_monitor);
    }
    else
    {
        err = RT_ERROR;
    }

    return err;
}
INIT_PREV_EXPORT(phy_device_register);
#endif /* RT_USING_PHY */

