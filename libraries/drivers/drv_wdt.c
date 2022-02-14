/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "board.h"
#include "drv_wdt.h"
#include "hpm_wdog_drv.h"
#include "hpm_sysctl_drv.h"
#include <rthw.h>
#include <rtdevice.h>
#include <rtdbg.h>

#ifdef RT_USING_WDT

typedef struct hpm_wdog_clk
{
    sysctl_resource_t resource;
    uint32_t resource_group;
    wdog_clksrc_t clk_src;
    uint32_t clk_freq;
} hpm_wdog_clk_t;

struct hpm_wdog
{
    WDOG_Type *wdog_base;
    uint32_t irq_num;
    hpm_wdog_clk_t clk;
    rt_watchdog_t *wdog;
    char *device_name;
};

static rt_err_t hpm_wdog_init(rt_watchdog_t *wdt);
static rt_err_t hpm_wdog_open(rt_watchdog_t *wdt, rt_uint16_t oflag);
static rt_err_t hpm_wdog_close(rt_watchdog_t *wdt);
static rt_err_t hpm_wdog_refreash(rt_watchdog_t *wdt);
static rt_err_t hpm_wdog_control(rt_watchdog_t *wdt, int cmd, void *args);

static void hpm_wdog_isr(rt_watchdog_t *wdt);

static wdog_control_t wdog_ctrl = {
    .reset_interval = reset_interval_clock_period_mult_16k,
    .interrupt_interval = interrupt_interval_clock_period_multi_8k,
    .reset_enable = true,
    .interrupt_enable = true,
    .clksrc = wdog_clksrc_extclk,
    .wdog_enable = false,
}
;

#if defined(BSP_USING_WDT0)
rt_watchdog_t wdog0;
void wdog0_isr(void)
{
    hpm_wdog_isr(&wdog0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_WDOG0, wdog0_isr)
#endif

#if defined(BSP_USING_WDT1)
rt_watchdog_t wdog1;
void wdog1_isr(void)
{
    hpm_wdog_isr(&wdog1);
}
SDK_DECLARE_EXT_ISR_M(IRQn_WDOG1, wdog1_isr)
#endif

#if defined(BSP_USING_WDT2)
rt_watchdog_t wdog2;
void wdog2_isr(void)
{
    hpm_wdog_isr(&wdog2);
}
SDK_DECLARE_EXT_ISR_M(IRQn_WDOG2, wdog2_isr)
#endif

#if defined(BSP_USING_WDT3)
rt_watchdog_t wdog3;
void wdog3_isr(void)
{
    hpm_wdog_isr(&wdog3);
}
SDK_DECLARE_EXT_ISR_M(IRQn_WDOG3, wdog3_isr)
#endif

static struct hpm_wdog wdogs[] = {
#ifdef BSP_USING_WDT0
    {
        HPM_WDOG0,
        IRQn_WDOG0,
        {sysctl_resource_wdog0, SYSCTL_RESOURCE_GROUP0, wdog_clksrc_extclk, BOARD_APP_WDOG_CLK_SRC_FREQ},
        &wdog0,
        "wdt0",
    },
#endif

#ifdef BSP_USING_WDT1
    {
        HPM_WDOG1,
        IRQn_WDOG1,
        {sysctl_resource_wdog1, SYSCTL_RESOURCE_GROUP0, wdog_clksrc_extclk, BOARD_APP_WDOG_CLK_SRC_FREQ},
        &wdog1,
        "wdt1",
    },
#endif

#ifdef BSP_USING_WDT2
    {
        HPM_WDOG2,
        IRQn_WDOG2,
        {sysctl_resource_wdog2, SYSCTL_RESOURCE_GROUP0, wdog_clksrc_extclk, BOARD_APP_WDOG_CLK_SRC_FREQ},
        &wdog2,
        "wdt2",
    },
#endif

#ifdef BSP_USING_WDT3
    {
        HPM_WDOG3,
        IRQn_WDOG3,
        {sysctl_resource_wdog3, SYSCTL_RESOURCE_GROUP0, wdog_clksrc_extclk, BOARD_APP_WDOG_CLK_SRC_FREQ},
        &wdog3,
        "wdt3",
    },
#endif
};

static struct rt_watchdog_ops hpm_wdog_ops = {
    .init = hpm_wdog_init,
    .control = hpm_wdog_control,
};

static rt_err_t hpm_wdog_init(rt_watchdog_t *wdt)
{
    WDOG_Type *base = (WDOG_Type *)wdt->parent.user_data;

    wdog_init(base, &wdog_ctrl);

    hpm_wdog_close(wdt);

    return RT_EOK;
}

static rt_err_t hpm_wdog_open(rt_watchdog_t *wdt, rt_uint16_t oflag)
{
    WDOG_Type *base = (WDOG_Type *)wdt->parent.user_data;

    rt_uint32_t level = rt_hw_interrupt_disable();
    wdog_enable(base, true);
    rt_hw_interrupt_enable(level);
}

static rt_err_t hpm_wdog_close(rt_watchdog_t *wdt)
{
    WDOG_Type *base = (WDOG_Type *)wdt->parent.user_data;

    rt_uint32_t level = rt_hw_interrupt_disable();
    wdog_enable(base, false);
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t hpm_wdog_refreash(rt_watchdog_t *wdt)
{
    WDOG_Type *base = (WDOG_Type *)wdt->parent.user_data;

    rt_uint32_t level = rt_hw_interrupt_disable();
    wdog_restart(base);
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t hpm_wdog_control(rt_watchdog_t *wdt, int cmd, void *args)
{
    rt_err_t ret = RT_EOK;
    WDOG_Type *base = (WDOG_Type *)wdt->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        *(uint32_t *)args = wdog_convert_reset_interval_to_us(BOARD_APP_WDOG_CLK_SRC_FREQ, wdog_ctrl.reset_interval);
        break;
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        RT_ASSERT(*(uint32_t *)args != 0);
        hpm_wdog_close(wdt);
        wdog_ctrl.interrupt_interval = wdog_get_interrupt_interval(BOARD_APP_WDOG_CLK_SRC_FREQ, *(uint32_t *)args / 2);
        wdog_ctrl.reset_interval = wdog_get_reset_interval(BOARD_APP_WDOG_CLK_SRC_FREQ, *(uint32_t *)args);
        wdog_ctrl.wdog_enable = true;
        hpm_wdog_init(wdt);
        break;
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        hpm_wdog_refreash(wdt);
        break;
    case RT_DEVICE_CTRL_WDT_START:
        hpm_wdog_open(wdt, *(uint16_t*)args);
        break;
    case RT_DEVICE_CTRL_WDT_STOP:
        hpm_wdog_close(wdt);
        break;
    default:
        ret = RT_EINVAL;
        break;
    }

    return RT_EOK;
}

void hpm_wdog_isr(rt_watchdog_t *wdt)
{
    WDOG_Type *base = (WDOG_Type *)wdt->parent.user_data;

    uint32_t status = wdog_get_status(base);

    if (IS_HPM_BITMASK_SET(status, WDOG_ST_INTEXPIRED_MASK)) {
        //Do something here, customer defined.
    }
}

int rt_hw_wdt_init(void)
{
    rt_err_t err = RT_EOK;

#if defined(BSP_USING_WDT)
    for (uint32_t i = 0; i < sizeof(wdogs) / sizeof(wdogs[0]); i++)
    {

        wdogs[i].wdog->ops = &hpm_wdog_ops;

        err = rt_hw_watchdog_register(wdogs[i].wdog, wdogs[i].device_name, RT_DEVICE_FLAG_RDWR, (void *)&wdogs[i]);
        if (err != RT_EOK)
        {
            LOG_E("rt device %s failed, status=%d\n", wdogs[i].device_name, err);
        }
    }
#endif
    return err;
}

INIT_DEVICE_EXPORT(rt_hw_wdt_init);
#endif /* RT_USING_WDT */