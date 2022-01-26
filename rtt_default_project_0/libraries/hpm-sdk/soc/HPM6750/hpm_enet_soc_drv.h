/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_ENET_SOC_DRV_H
#define HPM_ENET_SOC_DRV_H

#include "hpm_conctl_regs.h"

#if defined __cplusplus
extern "C" {
#endif

static inline hpm_stat_t enet_rgmii_set_clock_delay(CONCTL_Type *ptr, uint8_t idx, uint8_t tx_delay, uint8_t rx_delay)
{
    hpm_stat_t stat = status_success;

    if (idx == 0) {
        ptr->CTRL0 &= ~(CONCTL_CTRL0_ENET0_TXCLK_DLY_SEL_MASK | CONCTL_CTRL0_ENET0_RXCLK_DLY_SEL_MASK);
        ptr->CTRL0 |= CONCTL_CTRL0_ENET0_RXCLK_DLY_SEL_SET(tx_delay) | CONCTL_CTRL0_ENET0_RXCLK_DLY_SEL_SET(rx_delay);
    } else if (idx == 1) {
        ptr->CTRL0 &= ~(CONCTL_CTRL0_ENET1_TXCLK_DLY_SEL_MASK | CONCTL_CTRL0_ENET1_RXCLK_DLY_SEL_MASK);
        ptr->CTRL0 |= CONCTL_CTRL0_ENET1_RXCLK_DLY_SEL_SET(tx_delay) | CONCTL_CTRL0_ENET1_RXCLK_DLY_SEL_SET(rx_delay);
    } else {
        return status_invalid_argument;
    }

    return stat;
}

static inline hpm_stat_t enet_rmii_enable_clock(CONCTL_Type *ptr, uint8_t idx, bool internal)
{
    hpm_stat_t stat = status_success;

    /* use an internal PLL clock as reference clock for rmii mode */
    if (idx == 0) {
        if (internal == true) {
            /* use a pll clock */
            ptr->CTRL2 |= CONCTL_CTRL2_PAD_OE_ETH0_REFCLK_MASK | CONCTL_CTRL2_ENET0_RMII_TXCLK_SEL_MASK;
        } else {
            /* use an external clock as reference clock for rmii mode */
            ptr->CTRL2 |= CONCTL_CTRL2_ENET0_RMII_TXCLK_SEL_MASK; /* use an external clock */
        }
    } else if (idx == 1) {
        if (internal == true) {
            /* use a pll clock */
            ptr->CTRL3 |= CONCTL_CTRL3_PAD_OE_ETH1_REFCLK_MASK | CONCTL_CTRL3_ENET1_RMII_TXCLK_SEL_MASK;
        } else {
            /* use an external clock as reference clock for rmii mode */
            ptr->CTRL3 |= CONCTL_CTRL3_ENET1_RMII_TXCLK_SEL_MASK; /* use an external clock */
        }
    } else {
        return status_invalid_argument;
    }

    return stat;
}

static inline hpm_stat_t enet_rgmii_enable_clock(CONCTL_Type *ptr, uint8_t idx)
{
    hpm_stat_t stat = status_success;

    if (idx == 0) {
        /* use an internal PLL clock for rgmii mode */
        ptr->CTRL2 &= ~CONCTL_CTRL2_ENET0_RMII_TXCLK_SEL_MASK;
    } else if (idx == 1) {
        /* use an internal PLL clock for rgmii mode */
        ptr->CTRL3 &= ~CONCTL_CTRL3_ENET1_RMII_TXCLK_SEL_MASK;
    } else {
        return status_invalid_argument;
    }

    return stat;
}
#if defined __cplusplus
} /* __cplusplus */
#endif

#endif /* HPM_ENET_SOC_DRV_H */