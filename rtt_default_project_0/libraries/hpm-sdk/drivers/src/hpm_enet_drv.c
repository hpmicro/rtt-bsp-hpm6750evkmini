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

/*---------------------------------------------------------------------*
 * Internal API
 *---------------------------------------------------------------------*/
static void enet_td_init(enet_alt_ehd_td_t *td, enet_buff_config_t *config)
{
    /* tdes0 */
    td->tdes0_bm.own = 1;
    td->tdes0_bm.ic = 1;
    td->tdes0_bm.ls = 1;
    td->tdes0_bm.fs = 1;
    td->tdes0_bm.dc = 1;
    td->tdes0_bm.ter = 1;
    td->tdes0_bm.tch = 0;

    /* tdes1 */
    td->tdes1_bm.saic = 0x2;
    td->tdes1_bm.tbs2 = config->buffer2_size;
    td->tdes1_bm.tbs1 = config->buffer1_size;

    /* tdes2 */
    td->tdes2_bm.buffer1 = config->buffer1;

    /* tdes3 */
    if (td->tdes0_bm.tch == 0) {
        td->tdes3_bm.buffer2 = config->buffer2;
    } else {
        td->tdes3_bm.next_desc = config->next_desc;
    }

    printf("===========================================\n");
    printf("tdes0: %08x\n", td->tdes0);
    printf("tdes1: %08x\n", td->tdes1);
    printf("tdes2: %08x\n", td->tdes2_bm.buffer1);
    printf("tdes3: %08x\n", td->tdes3_bm.buffer2);
}

static void enet_rd_init(enet_alt_ehd_rd_t *rd, enet_buff_config_t *config)
{
    /* rdes0 */
    rd->rdes0_bm.own = 1;
    rd->rdes0_bm.fs = 1;
    rd->rdes0_bm.ls = 1;

    /* rdes1 */
    rd->rdes1_bm.rer = 1;
    rd->rdes1_bm.rch = 0;
    rd->rdes1_bm.rbs2 = config->buffer2_size;
    rd->rdes1_bm.rbs1 = config->buffer1_size;

    /* rdes2 */
    rd->rdes2_bm.buffer1 = config->buffer1;

    /* rdes3 */
    rd->rdes3_bm.buffer2 = config->buffer2;

     /* rdes3 */
    if (rd->rdes1_bm.rch == 0) {
        rd->rdes3_bm.buffer2 = config->buffer2;
    } else {
        rd->rdes3_bm.next_desc = config->next_desc;
    }

    printf("===========================================\n");
    printf("rdes0: %08x, own: %08x\n", rd->rdes0, rd->rdes0_bm.own);
    printf("rdes1: %08x\n", rd->rdes1);
    printf("rdes2: %08x\n", rd->rdes2_bm.buffer1);
    printf("rdes3: %08x\n", rd->rdes3_bm.buffer2);
}

static int enet_des_init(enet_desc_t *desc)
{
    enet_td_init(desc->td, &desc->td_buffer_config);
    enet_rd_init(desc->rd, &desc->rd_buffer_config);

    return true;
}

static void enet_desc_list_addr_init(ENET_Type *ptr, enet_desc_t *desc)
{
    ptr->DMA_RX_DESC_LIST_ADDR = (uint32_t)desc->rd_head;
    ptr->DMA_TX_DESC_LIST_ADDR = (uint32_t)desc->td_head;

    printf("%s: tx_desc_list_adddr:%#p\n", __FUNCTION__, ptr->DMA_TX_DESC_LIST_ADDR);   //pass
    printf("%s: rx_desc_list_adddr:%#p\n", __FUNCTION__, ptr->DMA_RX_DESC_LIST_ADDR);   //pass

    printf("\n");
}

static void enet_mode_init(ENET_Type *ptr, uint32_t intr)
{
    // Step 9
    /* step a: Receive and Transmit Store And Forward */
    ptr->DMA_OP_MODE |= ENET_DMA_OP_MODE_RSF_MASK | ENET_DMA_OP_MODE_TSF_MASK;

    /* step b: Receive and Transmit Threshold Control (RTC and TTC)*/
    /* ignore */
    ptr->DMA_OP_MODE |= ENET_DMA_OP_MODE_TTC_SET(1); /* TTC 128B, RTC 64B */

    /* step c: Hardware Flow Control enable */
    ptr->DMA_OP_MODE |= ENET_DMA_OP_MODE_EFC_MASK;

    /* step d: Flow Control Activation and De-activation thresholds for MTL Receive and Transmit Fifo (RFA and RFD) */
    /* ignore */

    /* step e: Error Frame and undersized good frame forwarding enable */
    ptr->DMA_OP_MODE |= ENET_DMA_OP_MODE_FEF_MASK;

    /* step f: Disable OSF Mode */
    ptr->DMA_OP_MODE &= ~ENET_DMA_OP_MODE_OSF_MASK;

    //Step 10
   // ptr->DMA_INTR_EN |= intr;

    //Step 11
    /* ignore */
    while (ENET_DMA_BUS_STATUS_AXIRDSTS_GET(ptr->DMA_BUS_STATUS) || ENET_DMA_BUS_STATUS_AXWHSTS_GET(ptr->DMA_BUS_STATUS)) {}

    /* Step 12： Start the Receive and Transmit DMA */
    //ptr->DMA_OP_MODE |= ENET_DMA_OP_MODE_ST_MASK | ENET_DMA_OP_MODE_SR_MASK; //start transmit

    //printf("\nDMA_OP_MODE DATA:%#p\n", ptr->DMA_OP_MODE);
}

static int enet_dma_init(ENET_Type *ptr, enet_desc_t *desc, uint32_t intr)
{
    /* 1. generate software reset */
    ptr->DMA_BUS_MODE |= ENET_DMA_BUS_MODE_SWR_MASK;

    /* 2. wait for the completion of reset process */
    while (ENET_DMA_BUS_MODE_SWR_GET(ptr->DMA_BUS_MODE)) {}

    /* 3. confirm that all previously initiated (before soft reset) or ongoing AHB or AXI transactions are complete */
    //while (ENET_DMA_BUS_STATUS_AXIRDSTS_GET(ptr->DMA_BUS_STATUS) || ENET_DMA_BUS_STATUS_AXWHSTS_GET(ptr->DMA_BUS_STATUS)) {}

    /* 4. Initialize bus mode register */
    /* a. set AAL */
    ptr->DMA_BUS_MODE |= ENET_DMA_BUS_MODE_AAL_MASK;        //para

    /* b. Disable Fixed Burst (set undefined burst) */
    ptr->DMA_BUS_MODE &= ~ENET_DMA_BUS_MODE_FB_MASK;        //para

    /* c. set burst length and burst mode */

    /* Set Programmable Burst Length */
    #if 0
        ptr->DMA_BUS_MODE |= ENET_DMA_BUS_MODE_PBL_SET(enet_pbl_1); //para
    #else
        ptr->DMA_BUS_MODE |= ENET_DMA_BUS_MODE_PBL_SET(enet_pbl_16); //para
    #endif

    /* Disable PBLx8 Mode */
    ptr->DMA_BUS_MODE &= ~ENET_DMA_BUS_MODE_PBLX8_MASK;     //para

    /* Disable Separate PBL */
    ptr->DMA_BUS_MODE &= ~ENET_DMA_BUS_MODE_USP_MASK;       //para

    /* TODO SBP is high, set RPBL */
    //ptr->DMA_BUS_MODE |= ENET_DMA_BUS_MODE_RPBL_SET(1);      //para

    /* d. Descriptor Length */
    #if ALT_EHD_DES_EN == 1 && ALT_EHD_DES_LEN == 4
        ptr->DMA_BUS_MODE &= ~ENET_DMA_BUS_MODE_ATDS_SET(1);
    #elif ALT_EHD_DES_EN == 1 && ALT_EHD_DES_LEN == 8
        ptr->DMA_BUS_MODE |= ENET_DMA_BUS_MODE_ATDS_SET(1);
    #endif

    /* 5. Set the maximum enabled burst length to 32 */
    if (ENET_DMA_BUS_MODE_FB_GET(ptr->DMA_BUS_MODE) == 0) {
        #if 0
            ptr->DMA_AXI_MODE |= ENET_DMA_AXI_MODE_BLEN32_MASK;       //para
        #else
            ptr->DMA_AXI_MODE |= ENET_DMA_AXI_MODE_BLEN4_MASK | ENET_DMA_AXI_MODE_BLEN8_MASK | ENET_DMA_AXI_MODE_BLEN16_MASK;       //para
        #endif
    }
    else {
        //TODO Set BLENX_MASK
        //ptr->DMA_AXI_MODE |= BLENX_MASK;
    }

    /* Step 6 */
    enet_des_init(desc);

    /* Step 7 */
    /* Todo Create three or more different transmit or receive descriptors in the chain */

    /* Step 8 */
    enet_desc_list_addr_init(ptr, desc);

    /* Step 9 ~ 12 */
    enet_mode_init(ptr, intr);

    return true;
}

/*---------------------------------------------------------------------*
 * Driver API
 *---------------------------------------------------------------------*/
void enet_tranmit_start(ENET_Type *ptr)
{
    /* Step 12： Start the Receive and Transmit DMA */
    #if 1
    ptr->DMA_OP_MODE |= ENET_DMA_OP_MODE_ST_MASK
                     | ENET_DMA_OP_MODE_SR_MASK; //start transmit

    ptr->MACCFG |= ENET_MACCFG_TE_SET(1)
                | ENET_MACCFG_RE_SET(1);
    #else
    ptr->DMA_OP_MODE |= ENET_DMA_OP_MODE_SR_MASK; //start transmit
    ptr->MACCFG |= ENET_MACCFG_RE_SET(1);
    #endif

}

void enet_phy_write(ENET_Type *ptr, uint32_t phy_addr, uint32_t addr, uint32_t data)
{
    /* set data to be written */
    ptr->GMII_DATA = ENET_GMII_DATA_GD_SET(data);

    /* set phy address , register address, write operation and busy flag */
    ptr->GMII_ADDR = ENET_GMII_ADDR_PA_SET(phy_addr)
                   | ENET_GMII_ADDR_GR_SET(addr)
                   | ENET_GMII_ADDR_CR_SET(enet_csr_20m_to_35m_mdc_csr_div_16)
                   | ENET_GMII_ADDR_GW_SET(enet_phy_op_write)
                   | ENET_GMII_ADDR_GB_SET(enet_phy_busy);

    /* wait until the write operation is completed */
    while (ENET_GMII_ADDR_GB_GET(ptr->GMII_ADDR)) {}
}

uint16_t enet_phy_read(ENET_Type *ptr, uint32_t phy_addr, uint32_t addr)
{
    /* set phy address, register address, read operation and busy flag */
    ptr->GMII_ADDR = ENET_GMII_ADDR_PA_SET(phy_addr)
                   | ENET_GMII_ADDR_GR_SET(addr)
                   | ENET_GMII_ADDR_CR_SET(enet_csr_20m_to_35m_mdc_csr_div_16)
                   | ENET_GMII_ADDR_GW_SET(enet_phy_op_read)
                   | ENET_GMII_ADDR_GB_SET(enet_phy_busy);

    /* wait until the write operation is completed */
    while (ENET_GMII_ADDR_GB_GET(ptr->GMII_ADDR)) {}

    /* read and return data */
    return (uint16_t)ENET_GMII_DATA_GD_GET(ptr->GMII_DATA);
}

static int enet_mac_init(ENET_Type *ptr, enet_mac_config_t *config)
{
    /* Step 1 & Step 2: Skip */

    /* Step 3: Set CSR Clock Range: Skip */

    /* Step 4 */

    /* Step 5: provide the mac address registers */
    if (config->valid_max_count > 5) {
        return false;
    }

    for (int i = 0; i < config->valid_max_count - 1; i++) {
        if (i == 0) {
            ptr->MAC_ADDR_0_HIGH |= ENET_MAC_ADDR_0_HIGH_ADDRHI_SET(config->mac_addr_high[i]);
            ptr->MAC_ADDR_0_LOW  |= ENET_MAC_ADDR_0_HIGH_ADDRHI_SET(config->mac_addr_low[i]);
        } else {
            ptr->MAC_ADDR[i].HIGH |= ENET_MAC_ADDR_HIGH_ADDRHI_SET(config->mac_addr_high[i]);
            ptr->MAC_ADDR[i].LOW  |= ENET_MAC_ADDR_LOW_ADDRLO_SET(config->mac_addr_low[i]);
        }
    }

    /* Step 6: Skip */

    /* Step 7: Set the appropriate filters for the incoming frames */
    ptr->MACFF |= ENET_MACFF_RA_SET(1)      /* receive all */
               |  ENET_MACFF_PR_SET(1);     /* Promiscuous mode */

    /* Step 8: Skip */
    /* Step 9: Interrupt Mask: Skip */

    /* Step 10: */
    /* replace the content of the MAC Address 0
     * registers(register 16 and 17) in the SA field of all transmitted frames.
     */
    ptr->MACCFG |= ENET_MACCFG_SARC_SET(0x3);

    /* For 1000 Mbps operations */
    ptr->MACCFG &= ~ENET_MACCFG_PS_MASK;

    /* Step 11: Transmitter Enable and Receiver Enable */
    //ptr->MACCFG |= ENET_MACCFG_TE_SET(1) | ENET_MACCFG_RE_SET(1);

    return true;
}

static void enet_intf_selection(ENET_Type *ptr, enet_inf_type_t inf_type)
{
    if (ptr == HPM_ENET0) {
        HPM_CONCTL->CTRL2 &= ~CONCTL_CTRL2_ENET0_PHY_INTF_SEL_MASK;
        HPM_CONCTL->CTRL2 |= CONCTL_CTRL2_ENET0_PHY_INTF_SEL_SET(inf_type);
    }
    else {
        HPM_CONCTL->CTRL3 &= ~CONCTL_CTRL3_ENET1_PHY_INTF_SEL_MASK;
        HPM_CONCTL->CTRL3 |= CONCTL_CTRL3_ENET1_PHY_INTF_SEL_SET(inf_type);
    }
}

int enet_controller_init(ENET_Type *ptr, enet_inf_type_t inf_type, enet_desc_t *desc, enet_mac_config_t *config, uint16_t intr)
{
    /* Initialize DMA */
    enet_dma_init(ptr, desc, intr);

    /* Select RGMII */
    enet_intf_selection(ptr, inf_type);

    /* Initialize MAC */
    enet_mac_init(ptr, config);

    return true;
}

void enet_transmit(ENET_Type *ptr, enet_desc_t *desc)
{
    desc->td->tdes0_bm.own = 1;
    ptr->DMA_TX_POLL_DEMAND = 1;
}

void enet_receive(ENET_Type *ptr, enet_desc_t *desc)
{
    desc->rd->rdes0_bm.own = 1;
    ptr->DMA_RX_POLL_DEMAND = 1;
}

void enet_stopping_transmission(ENET_Type *ptr)
{
}

void enet_starting_transmission(ENET_Type *ptr)
{
}

void enet_current_host_des(ENET_Type *ptr)
{
    /* current td reg */
    printf("%s: ptr->DMA_CURR_HOST_TX_DESC: %#p\n", __FUNCTION__, ptr->DMA_CURR_HOST_TX_DESC);

    /* current rd reg */
    printf("%s: ptr->DMA_CURR_HOST_RX_DESC: %#p\n", __FUNCTION__, ptr->DMA_CURR_HOST_RX_DESC);

    /* current transmit buffer */
    printf("%s: ptr->DMA_CURR_HOST_TX_BUF: %#p\n", __FUNCTION__, ptr->DMA_CURR_HOST_TX_BUF);

    /* current receive buffer */
    printf("%s: ptr->DMA_CURR_HOST_RX_BUF: %#p\n", __FUNCTION__, ptr->DMA_CURR_HOST_RX_BUF);
}
