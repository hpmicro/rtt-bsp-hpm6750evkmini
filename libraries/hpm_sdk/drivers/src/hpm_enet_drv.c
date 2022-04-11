/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*---------------------------------------------------------------------*
 * Includes
 *---------------------------------------------------------------------*/
#include "board.h"
#include "hpm_enet_drv.h"
#include "hpm_enet_soc_drv.h"

/*---------------------------------------------------------------------*
 * Internal API
 *---------------------------------------------------------------------*/
static void enet_mode_init(ENET_Type *ptr, uint32_t intr)
{
    /* Receive and Transmit Store And Forward */
    ptr->DMA_OP_MODE |= ENET_DMA_OP_MODE_RSF_MASK | ENET_DMA_OP_MODE_TSF_MASK;

    /*Hardware Flow Control enable */
    ptr->DMA_OP_MODE |= ENET_DMA_OP_MODE_EFC_MASK;

    /* Error Frame and undersized good frame forwarding enable */
    ptr->DMA_OP_MODE |= ENET_DMA_OP_MODE_FEF_MASK;

    /* Disable OSF Mode */
    ptr->DMA_OP_MODE &= ~ENET_DMA_OP_MODE_OSF_MASK;

    ptr->DMA_INTR_EN |= intr;

    while (ENET_DMA_BUS_STATUS_AXIRDSTS_GET(ptr->DMA_BUS_STATUS) || ENET_DMA_BUS_STATUS_AXWHSTS_GET(ptr->DMA_BUS_STATUS)) {}

    /* Start the Receive and Transmit DMA */
    ptr->DMA_OP_MODE |= ENET_DMA_OP_MODE_ST_MASK | ENET_DMA_OP_MODE_SR_MASK;
}

static int enet_dma_init(ENET_Type *ptr, enet_desc_t *desc, uint32_t intr)
{
    /* generate software reset */
    ptr->DMA_BUS_MODE |= ENET_DMA_BUS_MODE_SWR_MASK;

    /* wait for the completion of reset process */
    while (ENET_DMA_BUS_MODE_SWR_GET(ptr->DMA_BUS_MODE)) {}

    /* Initialize bus mode register */
    /* Set AAL */
    ptr->DMA_BUS_MODE |= ENET_DMA_BUS_MODE_AAL_MASK;

    ptr->DMA_BUS_MODE &= ~ENET_DMA_BUS_MODE_FB_MASK;

    /* Set Programmable Burst Length */
    ptr->DMA_BUS_MODE |= ENET_DMA_BUS_MODE_PBL_SET(enet_pbl_16);

    /* Disable PBLx8 Mode */
    ptr->DMA_BUS_MODE &= ~ENET_DMA_BUS_MODE_PBLX8_MASK;

    /* Disable Separate PBL */
    ptr->DMA_BUS_MODE &= ~ENET_DMA_BUS_MODE_USP_MASK;

    /* Descriptor Length */
    #if ALT_EHD_DES_EN == 1 && ALT_EHD_DES_LEN == 4
        ptr->DMA_BUS_MODE &= ~ENET_DMA_BUS_MODE_ATDS_SET(1);
    #elif ALT_EHD_DES_EN == 1 && ALT_EHD_DES_LEN == 8
        ptr->DMA_BUS_MODE |= ENET_DMA_BUS_MODE_ATDS_SET(1);
    #endif

    /* Set the maximum enabled burst length */
    if (ENET_DMA_BUS_MODE_FB_GET(ptr->DMA_BUS_MODE) == 0) {
        ptr->DMA_AXI_MODE |= ENET_DMA_AXI_MODE_BLEN4_MASK | ENET_DMA_AXI_MODE_BLEN8_MASK | ENET_DMA_AXI_MODE_BLEN16_MASK;
    }
    else {
        /* TODO Set BLENX_MASK */
    }

    /* Initialize Tx Descriptors list: Chain Mode */
    enet_dma_tx_desc_chain_init(ptr, desc);
    /* Initialize Rx Descriptors list: Chain Mode  */
    enet_dma_rx_desc_chain_init(ptr, desc);

    enet_mode_init(ptr, intr);

    enet_dma_flush(ptr);
    return true;
}

static int enet_mac_init(ENET_Type *ptr, enet_mac_config_t *config, enet_inf_type_t inf_type)
{
    for (int i = 0; i < config->valid_max_count; i++) {
        if (i == 0) {
            ptr->MAC_ADDR_0_HIGH = ENET_MAC_ADDR_0_HIGH_AE_MASK;
            ptr->MAC_ADDR_0_HIGH |= ENET_MAC_ADDR_0_HIGH_ADDRHI_SET(config->mac_addr_high[i]);
            ptr->MAC_ADDR_0_LOW  = ENET_MAC_ADDR_0_LOW_ADDRLO_SET(config->mac_addr_low[i]);
        } else {
            ptr->MAC_ADDR[i].HIGH |= ENET_MAC_ADDR_HIGH_ADDRHI_SET(config->mac_addr_high[i]);
            ptr->MAC_ADDR[i].LOW  |= ENET_MAC_ADDR_LOW_ADDRLO_SET(config->mac_addr_low[i]);
        }
    }

    ptr->MAC_ADDR[ENET_MAC_ADDR_1].HIGH |= ENET_MAC_ADDR_HIGH_AE_MASK;
    ptr->MAC_ADDR[ENET_MAC_ADDR_1].HIGH |= ENET_MAC_ADDR_HIGH_SA_MASK;
    ptr->MAC_ADDR[ENET_MAC_ADDR_1].HIGH &= ~ENET_MAC_ADDR_HIGH_MBC_MASK;

    ptr->MAC_ADDR[ENET_MAC_ADDR_1].HIGH &= ~ENET_MAC_ADDR_HIGH_AE_MASK;
    ptr->MAC_ADDR[ENET_MAC_ADDR_1].HIGH &= ~ENET_MAC_ADDR_HIGH_SA_MASK;


    /* Step 7: Set the appropriate filters for the incoming frames */
    ptr->MACFF |= ENET_MACFF_RA_SET(1);      /* receive all */

    /* replace the content of the MAC Address 0
     * registers(register 16 and 17) in the SA field of all transmitted frames.
     */
    ptr->MACCFG &= ENET_MACCFG_SARC_MASK;
    ptr->MACCFG |= ENET_MACCFG_SARC_SET(0x3);

    ptr->MACCFG |= ENET_MACCFG_PS_MASK | ENET_MACCFG_FES_MASK;

    if (inf_type == enet_inf_rgmii) {
        ptr->MACCFG &= ~ENET_MACCFG_PS_MASK;
    } else if (inf_type == enet_inf_rmii) {
        ptr->MACCFG |= ENET_MACCFG_PS_MASK | ENET_MACCFG_FES_MASK;
    } else {
        return status_invalid_argument;
    }

    /* Transmitter Enable and Receiver Enable */
    ptr->MACCFG |= ENET_MACCFG_TE_MASK | ENET_MACCFG_RE_MASK;

    return true;
}

/*---------------------------------------------------------------------*
 * Driver API
 *---------------------------------------------------------------------*/
void enet_dma_flush(ENET_Type *ptr)
{
    /* Flush DMA Transmit FIFO */
    ptr->DMA_OP_MODE |= ENET_DMA_OP_MODE_FTF_MASK;
    while (ENET_DMA_OP_MODE_FTF_GET(ptr->DMA_OP_MODE)) {

    }
}

void enet_write_phy(ENET_Type *ptr, uint32_t phy_addr, uint32_t addr, uint32_t data)
{
    /* set data to be written */
    ptr->GMII_DATA = ENET_GMII_DATA_GD_SET(data);

    /* set phy address , register address, write operation and busy flag */
    ptr->GMII_ADDR = ENET_GMII_ADDR_PA_SET(phy_addr)
                   | ENET_GMII_ADDR_GR_SET(addr)
                   | ENET_GMII_ADDR_CR_SET(enet_csr_150m_to_250m_mdc_csr_div_102)
                   | ENET_GMII_ADDR_GW_SET(enet_phy_op_write)
                   | ENET_GMII_ADDR_GB_SET(enet_phy_busy);

    /* wait until the write operation is completed */
    while (ENET_GMII_ADDR_GB_GET(ptr->GMII_ADDR)) {}
}

uint16_t enet_read_phy(ENET_Type *ptr, uint32_t phy_addr, uint32_t addr)
{
    /* set phy address, register address, read operation and busy flag */
    ptr->GMII_ADDR = ENET_GMII_ADDR_PA_SET(phy_addr)
                   | ENET_GMII_ADDR_GR_SET(addr)
                   | ENET_GMII_ADDR_CR_SET(enet_csr_150m_to_250m_mdc_csr_div_102)
                   | ENET_GMII_ADDR_GW_SET(enet_phy_op_read)
                   | ENET_GMII_ADDR_GB_SET(enet_phy_busy);

    /* wait until the write operation is completed */
    while (ENET_GMII_ADDR_GB_GET(ptr->GMII_ADDR)) {}

    /* read and return data */
    return (uint16_t)ENET_GMII_DATA_GD_GET(ptr->GMII_DATA);
}

int enet_controller_init(ENET_Type *ptr, enet_inf_type_t inf_type, enet_desc_t *desc, enet_mac_config_t *config, uint32_t intr)
{
    /* Initialize DMA */
    enet_dma_init(ptr, desc, intr);

    /* Select RGMII */
    enet_intf_selection(ptr, inf_type);

    /* Initialize MAC */
    enet_mac_init(ptr, config, inf_type);

    return true;
}

/******************************************************************************/
/*                           DMA API                                          */
/******************************************************************************/
uint32_t enet_check_received_frame(enet_rx_desc_t **parent_rx_desc_list_cur, enet_rx_frame_info_t *rx_frame_info)
{
    enet_rx_desc_t *rx_desc_list_cur = *parent_rx_desc_list_cur;

    /* check if last segment */
    if ((rx_desc_list_cur->rdes0_bm.own == 0) &&
        (rx_desc_list_cur->rdes0_bm.ls == 1)) {
        rx_frame_info->seg_count++;
        if (rx_frame_info->seg_count == 1) {
            rx_frame_info->fs_rx_desc = rx_desc_list_cur;
        }
        rx_frame_info->ls_rx_desc = rx_desc_list_cur;
        return 1;
    }
    /* check if first segment */
    else if ((rx_desc_list_cur->rdes0_bm.own == 0) &&
             (rx_desc_list_cur->rdes0_bm.fs == 1) &&
             (rx_desc_list_cur->rdes0_bm.ls == 0)) {
        rx_frame_info->fs_rx_desc = rx_desc_list_cur;
        rx_frame_info->ls_rx_desc = NULL;
        rx_frame_info->seg_count = 1;
        rx_desc_list_cur = (enet_rx_desc_t *)rx_desc_list_cur->rdes3_bm.next_desc;
        *parent_rx_desc_list_cur = rx_desc_list_cur;
    }

    /* check if intermediate segment */
    else if ((rx_desc_list_cur->rdes0_bm.own == 0) &&
             (rx_desc_list_cur->rdes0_bm.fs == 0) &&
             (rx_desc_list_cur->rdes0_bm.ls == 0)) {
        rx_frame_info->seg_count++;
        rx_desc_list_cur = (enet_rx_desc_t *)(rx_desc_list_cur->rdes3_bm.next_desc);
        *parent_rx_desc_list_cur = rx_desc_list_cur;
    }

    return 0;
}

enet_frame_t enet_get_received_frame(enet_rx_desc_t **parent_rx_desc_list_cur, enet_rx_frame_info_t *rx_frame_info)
{
    uint32_t frame_length = 0;
    enet_frame_t frame = {0, 0, 0};
    enet_rx_desc_t *rx_desc_list_cur = *parent_rx_desc_list_cur;

    /* Get the Frame Length of the received packet: substruct 4 bytes of the CRC */
    frame_length = rx_desc_list_cur->rdes0_bm.fl - 4;
    frame.length = frame_length;

    /* Get the address of the first frame descriptor and the buffer start address */
    frame.rx_desc = rx_frame_info->fs_rx_desc;
    frame.buffer = rx_frame_info->fs_rx_desc->rdes2_bm.buffer1;

    /* Update the ETHERNET DMA global Rx descriptor with next Rx descriptor */
    /* Chained Mode */
    /* Selects the next DMA Rx descriptor list for next buffer to read */
    rx_desc_list_cur = (enet_rx_desc_t *)(rx_desc_list_cur->rdes3_bm.next_desc);
    *parent_rx_desc_list_cur = rx_desc_list_cur;

    return frame;
}

enet_frame_t enet_get_received_frame_interrupt(enet_rx_desc_t **parent_rx_desc_list_cur, enet_rx_frame_info_t *rx_frame_info, uint32_t rx_desc_count)
{
    enet_frame_t frame = {0, 0, 0};
    uint32_t desc_scan_counter = 0;
    enet_rx_desc_t *rx_desc_list_cur = *parent_rx_desc_list_cur;

    /* scan descriptors owned by CPU */
    while ((rx_desc_list_cur->rdes0_bm.own == 0) &&
        (desc_scan_counter < rx_desc_count)) {

        desc_scan_counter++;

        /* check if first segment in frame */
        if ((rx_desc_list_cur->rdes0_bm.fs == 1) &&
            (rx_desc_list_cur->rdes0_bm.ls == 0)) {
            rx_frame_info->fs_rx_desc = rx_desc_list_cur;
            rx_frame_info->seg_count = 1;
            rx_desc_list_cur = (enet_rx_desc_t *)(rx_desc_list_cur->rdes3_bm.next_desc);
            *parent_rx_desc_list_cur = rx_desc_list_cur;
        }

        /* check if intermediate segment */
        else if ((rx_desc_list_cur->rdes0_bm.ls == 0) &&
                 (rx_desc_list_cur->rdes0_bm.fs == 0)) {
            rx_frame_info->seg_count++;
            rx_desc_list_cur = (enet_rx_desc_t *)(rx_desc_list_cur->rdes3_bm.next_desc);
            *parent_rx_desc_list_cur = rx_desc_list_cur;
        }

        /* should be last segment */
        else {
            /* last segment */
            rx_frame_info->ls_rx_desc = rx_desc_list_cur;

            rx_frame_info->seg_count++;

            /* first segment is last segment */
            if (rx_frame_info->seg_count == 1) {
                rx_frame_info->fs_rx_desc = rx_desc_list_cur;
            }

            /* Get the Frame Length of the received packet: substruct 4 bytes of the CRC */
            frame.length = rx_desc_list_cur->rdes0_bm.fl - 4;

            /* Get the address of the buffer start address */
            /* Check if more than one segment in the frame */
            if (rx_frame_info->seg_count > 1) {
                frame.buffer = rx_frame_info->fs_rx_desc->rdes2_bm.buffer1;
            } else {
                frame.buffer = rx_desc_list_cur->rdes2_bm.buffer1;
            }

            frame.rx_desc = rx_frame_info->fs_rx_desc;

            rx_desc_list_cur = (enet_rx_desc_t *)(rx_desc_list_cur->rdes3_bm.next_desc);
            *parent_rx_desc_list_cur = rx_desc_list_cur;

            return frame;
        }
    }

    return frame;
}

uint32_t enet_prepare_transmission_descriptors(ENET_Type *ptr, enet_tx_desc_t **parent_tx_desc_list_cur, uint16_t frame_length, uint16_t tx_buff_size)
{
    uint32_t buf_count = 0, size = 0, i = 0;
    enet_tx_desc_t *dma_tx_desc;
    enet_tx_desc_t  *tx_desc_list_cur = *parent_tx_desc_list_cur;

    if (tx_buff_size == 0) {
        return ENET_ERROR;
    }
    /* Check if the descriptor is owned by the ETHERNET DMA (when set) or CPU (when reset) */
    dma_tx_desc = tx_desc_list_cur;
    if (frame_length > tx_buff_size) {
        buf_count = frame_length / tx_buff_size;
        if (frame_length % tx_buff_size) {
            buf_count++;
        }
    } else {
        buf_count = 1;
    }

    if (buf_count == 1) {
        /*set LAST and FIRST segment */
        dma_tx_desc->tdes0_bm.own = 0;
        dma_tx_desc->tdes0_bm.fs = 1;
        dma_tx_desc->tdes0_bm.ls = 1;
        dma_tx_desc->tdes0_bm.dc = 1;
        dma_tx_desc->tdes0_bm.dp = 0;
        dma_tx_desc->tdes0_bm.crcr = 0;
        dma_tx_desc->tdes1_bm.saic = 2;

        /* Set frame size */
        dma_tx_desc->tdes1_bm.tbs1 = (frame_length & ENET_DMATxDesc_TBS1);
        /* Set Own bit of the Tx descriptor Status: gives the buffer back to ETHERNET DMA */
        dma_tx_desc->tdes0_bm.own = 1;
        ptr->DMA_TX_POLL_DEMAND = 1;

        dma_tx_desc = (enet_tx_desc_t *)(dma_tx_desc->tdes3_bm.next_desc);
    } else {
        for (i = 0; i < buf_count; i++) {
            /* Clear FIRST and LAST segment bits */
            dma_tx_desc->tdes0_bm.fs = 0;
            dma_tx_desc->tdes0_bm.ls = 0;

            if (i == 0) {
                /* Setting the first segment bit */
                dma_tx_desc->tdes0_bm.fs = 1;
            }

            /* Program size */
            dma_tx_desc->tdes1_bm.tbs1 = (tx_buff_size & ENET_DMATxDesc_TBS1);

            if (i == (buf_count - 1)) {
                /* Setting the last segment bit */
                dma_tx_desc->tdes0_bm.ls = 1;
                size = frame_length - (buf_count - 1) * tx_buff_size;
                dma_tx_desc->tdes1_bm.tbs1 = (size & ENET_DMATxDesc_TBS1);

                /* Set Own bit of the Tx descriptor Status: gives the buffer back to ETHERNET DMA */
                dma_tx_desc->tdes0_bm.own = 1;
                ptr->DMA_TX_POLL_DEMAND = 0;
            }

            dma_tx_desc = (enet_tx_desc_t *)(dma_tx_desc->tdes3_bm.next_desc);
        }
    }

    tx_desc_list_cur = dma_tx_desc;
    *parent_tx_desc_list_cur = tx_desc_list_cur;

    return ENET_SUCCESS;
}

void enet_dma_tx_desc_chain_init(ENET_Type *ptr, enet_desc_t *desc)
{
    uint32_t i = 0;
    enet_tx_desc_t *dma_tx_desc;

    /* Set the tx_desc_list_cur pointer with the first one of the dma_tx_desc_tab list */
    desc->tx_desc_list_cur = desc->tx_desc_list_head;
    /* Fill each dma_tx_desc descriptor with the right values */
    for (i = 0; i < desc->tx_buff_cfg.count; i++) {
        /* Get the pointer on the ith member of the Tx Desc list */
        dma_tx_desc = desc->tx_desc_list_head + i;
        /* Set Second Address Chained bit */
        dma_tx_desc->tdes0_bm.tch = 1;

        /* Set Buffer1 address pointer */
        dma_tx_desc->tdes2_bm.buffer1 = (uint32_t)(&((uint8_t *)desc->tx_buff_cfg.buffer)[i * desc->tx_buff_cfg.size]);

        /* Initialize the next descriptor with the Next Descriptor Polling Enable */
        if (i < desc->tx_buff_cfg.count - 1) {
            /* Set next descriptor address register with next descriptor base address */
            dma_tx_desc->tdes3_bm.next_desc = (uint32_t)(desc->tx_desc_list_head + i + 1);
        } else {
            /* For last descriptor, set next descriptor address register equal to the first descriptor base address */
            dma_tx_desc->tdes3_bm.next_desc = (uint32_t)desc->tx_desc_list_head;
        }
    }

    /* Set Transmit Descriptor List Address Register */
    ptr->DMA_TX_DESC_LIST_ADDR = (uint32_t)desc->tx_desc_list_head;
}

void enet_dma_rx_desc_chain_init(ENET_Type *ptr,  enet_desc_t *desc)
{
    uint32_t i = 0;
    enet_rx_desc_t *dma_rx_desc;

    /* Set the rx_desc_list_cur pointer with the first one of the dma_rx_desc_tab list */
    desc->rx_desc_list_cur = desc->rx_desc_list_head;
    /* Fill each dma_rx_desc descriptor with the right values */
    for (i = 0; i < desc->rx_buff_cfg.count; i++) {
        /* Get the pointer on the ith member of the Rx Desc list */
        dma_rx_desc = desc->rx_desc_list_head + i;
        /* Set Own bit of the Rx descriptor Status */
        dma_rx_desc->rdes0_bm.own = 1;

        /* Set Buffer1 size and Second Address Chained bit */
        dma_rx_desc->rdes1_bm.rch = 1;
        dma_rx_desc->rdes1_bm.rbs1 = desc->rx_buff_cfg.size;

        /* Set Buffer1 address pointer */
        dma_rx_desc->rdes2_bm.buffer1 = (uint32_t)(&((uint8_t *)desc->rx_buff_cfg.buffer)[i * desc->rx_buff_cfg.size]);

        /* Initialize the next descriptor with the Next Descriptor Polling Enable */
        if (i < desc->rx_buff_cfg.count - 1) {
            /* Set next descriptor address register with next descriptor base address */
            dma_rx_desc->rdes3_bm.next_desc = (uint32_t)(desc->rx_desc_list_head + i + 1);
        } else {
            /* For last descriptor, set next descriptor address register equal to the first descriptor base address */
            dma_rx_desc->rdes3_bm.next_desc = (uint32_t)desc->rx_desc_list_head;
        }
    }
    /* Set Receive Descriptor List Address Register */
    ptr->DMA_RX_DESC_LIST_ADDR = (uint32_t)desc->rx_desc_list_head;
}
