/*
 * Copyright (c) 2021 hpm
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2022-01-11   hpm     First version
 */

#include <rtdevice.h>

#ifdef BSP_USING_ETH
#include <rtdbg.h>
#include <netif/ethernetif.h>
#include "drv_enet.h"
#include "board.h"
#include "hpm_soc_feature.h"
#include "hpm_enet_soc_drv.h"
#include "hpm_enet_drv.h"
#include "rtt_board.h"

#define ENET_CONCTL         HPM_CONCTL
#define ENET_INF_TYPE       enet_inf_rmii
#define ENET                HPM_ENET1
#define ENET_MCU_CORE       HPM_CORE0
#define ENET_ID             (1UL)
#define ENET_INT_REF_CLK    (0UL)
#define ENET_TX_BUFF_COUNT  (10U)
#define ENET_RX_BUFF_COUNT  (20U)
#define ENET_RX_BUFF_SIZE   ENET_MAX_FRAME_SIZE
#define ENET_TX_BUFF_SIZE   ENET_MAX_FRAME_SIZE

#define ETH_DEBUG


typedef struct {
    ENET_Type * instance;
    enet_desc_t desc;
    enet_mac_config_t mac_config;
    uint8_t media_interface;
    uint32_t mask;
    uint32_t irq_number;
} enet_device;

ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(ENET_SOC_DESC_ADDR_ALIGNMENT)
__RW enet_rx_desc_t dma_rx_desc_tab[ENET_RX_BUFF_COUNT] ; /* Ethernet Rx DMA Descriptor */

ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(ENET_SOC_DESC_ADDR_ALIGNMENT)
__RW enet_tx_desc_t dma_tx_desc_tab[ENET_TX_BUFF_COUNT] ; /* Ethernet Tx DMA Descriptor */

ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(ENET_SOC_BUFF_ADDR_ALIGNMENT)
__RW uint8_t rx_buff[ENET_RX_BUFF_COUNT][ENET_RX_BUFF_SIZE]; /* Ethernet Receive Buffer */

ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(ENET_SOC_BUFF_ADDR_ALIGNMENT)
__RW uint8_t tx_buff[ENET_TX_BUFF_COUNT][ENET_TX_BUFF_SIZE]; /* Ethernet Transmit Buffer */

struct eth_device eth_dev;
static enet_device enet_dev;

#if defined ETH_TX_DUMP || defined ETH_RX_DUMP
#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')
static void dump_hex(const rt_uint8_t *ptr, rt_size_t buflen)
{
    unsigned char *buf = (unsigned char *)ptr;
    int i, j;

    if (buflen != 0)
    {
        for (i = 0; i < buflen; i += 16)
        {
            rt_kprintf("%08x: ", i);

            for (j = 0; j < 16; j++)
                if (i + j < buflen)
                    rt_kprintf("%02x ", buf[i + j]);
                else
                    rt_kprintf("   ");

            rt_kprintf(" ");

            for (j = 0; j < 16; j++)
                if (i + j < buflen)
                    rt_kprintf("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');

            rt_kprintf("\n");
        }
    }
}
#endif

static hpm_stat_t hpm_enet_init(enet_device *init)
{
    /* Initialize eth controller */
    enet_controller_init(init->instance, init->media_interface, &init->desc, &init->mac_config, init->mask);

    /* Initialize reference clock */
    #if ENET_INT_REF_CLK
        board_init_enet_rmii_reference_clock(ENET);
        enet_rmii_enable_clock(ENET_CONCTL, ENET_ID, true);
    #else
        enet_rmii_enable_clock(ENET_CONCTL, ENET_ID, false);
    #endif

    /* enable irq */
    intc_m_enable_irq(init->irq_number);
}

static rt_err_t rt_hpm_eth_init(rt_device_t dev)
{
    enet_device *enet_dev = (enet_device *)dev->user_data;

    /* Initialize GPIOs */
    init_enet_pins(enet_dev->instance);

    /* Initialize MAC and DMA */
    if (hpm_enet_init(enet_dev) == 0) {
        LOG_D("Ethernet control initialize successfully\n");
    }

    return RT_EOK;
}

static rt_err_t rt_hpm_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_hpm_eth_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t rt_hpm_eth_read(rt_device_t dev, rt_off_t pos, void * buffer, rt_size_t size)
{
    return 0;
}

static rt_size_t rt_hpm_eth_write(rt_device_t dev, rt_off_t pos, const void * buffer, rt_size_t size)
{
    return 0;
}

static rt_err_t rt_hpm_eth_control(rt_device_t dev, int cmd, void * args)
{
    uint8_t *mac;

    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* read MAC address */
        if (args != NULL)
        {
            mac = (uint8_t *)args;
            mac[0] = MAC_ADDR0;
            mac[1] = MAC_ADDR1;
            mac[2] = MAC_ADDR2;
            mac[3] = MAC_ADDR3;
            mac[4] = MAC_ADDR4;
            mac[5] = MAC_ADDR5;
            SMEMCPY(args, mac, 6);
        }
        else
        {
            return -RT_ERROR;
        }
        break;
    default:
        break;
    }

    return RT_EOK;
}

static rt_err_t rt_hpm_eth_tx(rt_device_t dev, struct pbuf * p)
{
    rt_err_t ret = RT_ERROR;
    uint32_t status;
    enet_device *enet_dev = (enet_device *)dev->user_data;

    struct pbuf *q;
    uint8_t *buffer;
    __IO enet_tx_desc_t *dma_tx_desc;
    uint32_t frame_length = 0;
    uint32_t buffer_offset = 0;
    uint32_t bytes_left_to_copy = 0;
    uint32_t payload_offset = 0;
    enet_tx_desc_t  *tx_desc_list_cur = enet_dev->desc.tx_desc_list_cur;

    dma_tx_desc = tx_desc_list_cur;
    buffer = (uint8_t *)(dma_tx_desc->tdes2_bm.buffer1);
    buffer_offset = 0;

    /* copy frame from pbufs to driver buffers */
    for (q = p; q != NULL; q = q->next)
    {
        /* Get bytes in current lwIP buffer */
        bytes_left_to_copy = q->len;
        payload_offset = 0;

        /* Check if the length of data to copy is bigger than Tx buffer size*/
        while ((bytes_left_to_copy + buffer_offset) > ENET_TX_BUFF_SIZE)
        {
            /* Copy data to Tx buffer*/
            SMEMCPY((uint8_t *)((uint8_t *)buffer + buffer_offset),
                    (uint8_t *)((uint8_t *)q->payload + payload_offset),
                    ENET_TX_BUFF_SIZE - buffer_offset);

            /* Point to next descriptor */
            dma_tx_desc = (enet_tx_desc_t *)(dma_tx_desc->tdes3_bm.next_desc);

            /* Check if the buffer is available */
            if (dma_tx_desc->tdes0_bm.own != 0)
            {
                LOG_E("DMA tx desc buffer is not valid\n");
                return ERR_USE;
            }

            buffer = (uint8_t *)(dma_tx_desc->tdes2_bm.buffer1);

            bytes_left_to_copy = bytes_left_to_copy - (ENET_TX_BUFF_SIZE - buffer_offset);
            payload_offset = payload_offset + (ENET_TX_BUFF_SIZE - buffer_offset);
            frame_length = frame_length + (ENET_TX_BUFF_SIZE - buffer_offset);
            buffer_offset = 0;
        }

        /* Copy the remaining bytes */
        SMEMCPY((uint8_t *)((uint8_t *)buffer + buffer_offset),
                (uint8_t *)((uint8_t *)q->payload + payload_offset),
                bytes_left_to_copy);

        buffer_offset = buffer_offset + bytes_left_to_copy;
        frame_length = frame_length + bytes_left_to_copy;
    }

#ifdef ETH_TX_DUMP
    dump_hex(buffer, p->tot_len);
#endif

    /* Prepare transmit descriptors to give to DMA */
    LOG_D("The length of the transmitted frame: %d\n", frame_length);

    frame_length += 4;
    status = enet_prepare_transmission_descriptors(ENET, &enet_dev->desc.tx_desc_list_cur, frame_length, enet_dev->desc.tx_buff_cfg.size);
    if (status != ENET_SUCCESS)
    {
        LOG_E("Ethernet controller transmit unsuccessfully: %d\n", status);
    }

    return ERR_OK;
}

static struct pbuf *rt_hpm_eth_rx(rt_device_t dev)
{
    struct pbuf *p = NULL, *q = NULL;
    enet_device *enet_dev = (enet_device *)dev->user_data;
    uint16_t len = 0;
    uint8_t *buffer;
    enet_frame_t frame = {0, 0, 0};
    enet_rx_desc_t *dma_rx_desc;
    uint32_t buffer_offset = 0;
    uint32_t payload_offset = 0;
    uint32_t bytes_left_to_copy = 0;
    uint32_t i = 0;

    /* Get a received frame */
    frame = enet_get_received_frame_interrupt(&enet_dev->desc.rx_desc_list_cur,
                                              &enet_dev->desc.rx_frame_info,
                                              enet_dev->desc.rx_buff_cfg.count);

    /* Obtain the size of the packet and put it into the "len" variable. */
    len = frame.length;
    buffer = (uint8_t *)frame.buffer;

    LOG_D("The current received frame length : %d\n", len);

    if (len > 0)
    {
        /* We allocate a pbuf chain of pbufs from the Lwip buffer pool */
        p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);

#ifdef ETH_RX_DUMP
    dump_hex(buffer, p->tot_len);
#endif
    }

    if (p != NULL)
    {
        dma_rx_desc = frame.rx_desc;
        buffer_offset = 0;
        for (q = p; q != NULL; q = q->next)
        {
            bytes_left_to_copy = q->len;
            payload_offset = 0;

            /* Check if the length of bytes to copy in current pbuf is bigger than Rx buffer size*/
            while ((bytes_left_to_copy + buffer_offset) > ENET_RX_BUFF_SIZE)
            {
                /* Copy data to pbuf */
                SMEMCPY((uint8_t *)((uint8_t *)q->payload + payload_offset), (uint8_t *)((uint8_t *)buffer + buffer_offset), (ENET_RX_BUFF_SIZE - buffer_offset));

                /* Point to next descriptor */
                dma_rx_desc = (enet_rx_desc_t *)(dma_rx_desc->rdes3_bm.next_desc);
                buffer = (uint8_t *)(dma_rx_desc->rdes2_bm.buffer1);

                bytes_left_to_copy = bytes_left_to_copy - (ENET_RX_BUFF_SIZE - buffer_offset);
                payload_offset = payload_offset + (ENET_RX_BUFF_SIZE - buffer_offset);
                buffer_offset = 0;
            }
            /* Copy remaining data in pbuf */
            SMEMCPY((uint8_t *)((uint8_t *)q->payload + payload_offset), (uint8_t *)((uint8_t *)buffer + buffer_offset), bytes_left_to_copy);
            buffer_offset = buffer_offset + bytes_left_to_copy;
        }
    }
    else
    {
        return NULL;
    }

    /* Release descriptors to DMA */
    /* Point to first descriptor */
    dma_rx_desc = frame.rx_desc;

    /* Set Own bit in Rx descriptors: gives the buffers back to DMA */
    for (i = 0; i < enet_dev->desc.rx_frame_info.seg_count; i++)
    {
        dma_rx_desc->rdes0_bm.own = 1;
        dma_rx_desc = (enet_rx_desc_t*)(dma_rx_desc->rdes3_bm.next_desc);
    }

    /* Clear Segment_Count */
    enet_dev->desc.rx_frame_info.seg_count = 0;

    return p;
}

static void eth_rx_callback(struct eth_device* dev)
{
    rt_err_t result;
    result = eth_device_ready(dev);
    if (result != RT_EOK)
    {
        LOG_I("Receive callback error = %d\n", result);
    }
}

void isr_enet1(void)
{
    uint32_t status;

    status = ENET->DMA_STATUS;

    if (ENET_DMA_STATUS_GLPII_GET(status)) {
        ENET->DMA_STATUS |= ENET_DMA_STATUS_GLPII_SET(ENET_DMA_STATUS_GLPII_GET(status));
    }

    if (ENET_DMA_STATUS_RI_GET(status)) {
        ENET->DMA_STATUS |= ENET_DMA_STATUS_RI_SET(ENET_DMA_STATUS_RI_GET(status));
        eth_rx_callback(&eth_dev);
    }
}
SDK_DECLARE_EXT_ISR_M(IRQn_ENET1, isr_enet1)

int rt_hw_eth_init(void)
{
    rt_err_t err = RT_ERROR;

    /* Clear memory */
    memset((uint8_t *)dma_tx_desc_tab, 0x00, sizeof(dma_tx_desc_tab));
    memset((uint8_t *)dma_rx_desc_tab, 0x00, sizeof(dma_rx_desc_tab));
    memset((uint8_t *)rx_buff, 0x00, sizeof(rx_buff));
    memset((uint8_t *)tx_buff, 0x00, sizeof(tx_buff));

    /* Set list heads */
    enet_dev.desc.tx_desc_list_head = (enet_tx_desc_t *)core_local_mem_to_sys_address(ENET_MCU_CORE, (uint32_t)dma_tx_desc_tab);
    enet_dev.desc.rx_desc_list_head = (enet_rx_desc_t *)core_local_mem_to_sys_address(ENET_MCU_CORE, (uint32_t)dma_rx_desc_tab);

    enet_dev.desc.tx_buff_cfg.buffer = core_local_mem_to_sys_address(ENET_MCU_CORE, (uint32_t)tx_buff);
    enet_dev.desc.tx_buff_cfg.count = ENET_TX_BUFF_COUNT;
    enet_dev.desc.tx_buff_cfg.size = ENET_TX_BUFF_SIZE;

    enet_dev.desc.rx_buff_cfg.buffer = core_local_mem_to_sys_address(ENET_MCU_CORE, (uint32_t)rx_buff);
    enet_dev.desc.rx_buff_cfg.count = ENET_RX_BUFF_COUNT;
    enet_dev.desc.rx_buff_cfg.size = ENET_RX_BUFF_SIZE;

    /* Set the mac0 address */
    enet_dev.mac_config.mac_addr_high[0] = MAC_ADDR5 << 8 | MAC_ADDR4;
    enet_dev.mac_config.mac_addr_low[0] = MAC_ADDR3 << 24 | MAC_ADDR2 << 16 | MAC_ADDR1 << 8 | MAC_ADDR0;
    enet_dev.mac_config.valid_max_count = 1;

    /* Set the instance */
    enet_dev.instance = ENET;

    /* Set the media interface */
    enet_dev.media_interface = ENET_INF_TYPE;

    /* Set the interrupt mask */
    enet_dev.mask = ENET_DMA_INTR_EN_NIE_SET(1)   /* Enable normal interrupt summary */
                  | ENET_DMA_INTR_EN_RIE_SET(1);  /* Enable receive interrupt */;

    /* Set the irq number */
    enet_dev.irq_number = IRQn_ENET1;

    /* Set the parent parameters */
    eth_dev.parent.init      = rt_hpm_eth_init;
    eth_dev.parent.open      = rt_hpm_eth_open;
    eth_dev.parent.close     = rt_hpm_eth_close;
    eth_dev.parent.read      = rt_hpm_eth_read;
    eth_dev.parent.write     = rt_hpm_eth_write;
    eth_dev.parent.control   = rt_hpm_eth_control;
    eth_dev.parent.user_data = &enet_dev;

    eth_dev.eth_rx = rt_hpm_eth_rx;
    eth_dev.eth_tx = rt_hpm_eth_tx;

    /* register eth device */
    err = eth_device_init(&eth_dev, "eth1");

    if (RT_EOK == err)
    {
        LOG_D("Ethernet device initialize successfully!\n");
    }
    else
    {
        LOG_D("Ethernet device initialize unsuccessfully!\n");
    }

    return err;

}
INIT_DEVICE_EXPORT(rt_hw_eth_init);
#endif /* BSP_USING_ETH */

