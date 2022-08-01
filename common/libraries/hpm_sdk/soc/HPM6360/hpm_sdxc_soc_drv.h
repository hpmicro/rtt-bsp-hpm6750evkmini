/*
 * Copyright (c) 2021 - 2022 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_SDXC_SOC_DRV_H
#define HPM_SDXC_SOC_DRV_H

#include "hpm_soc.h"
#include "hpm_sdxc_regs.h"

#if defined(__cplusplus)
extern "C" {
#endif


static inline void sdxc_enable_tm_clock(SDXC_Type *base)
{
    base->MISC_CTRL0 |= SDXC_MISC_CTRL0_TMCLK_EN_MASK;
}

static inline void sdxc_enable_freq_selection(SDXC_Type *base)
{
    base->MISC_CTRL0 |= SDXC_MISC_CTRL0_FREQ_SEL_SW_EN_MASK;
}

static inline void sdxc_disable_freq_selection(SDXC_Type *base)
{
    base->MISC_CTRL0 &= ~SDXC_MISC_CTRL0_FREQ_SEL_SW_EN_MASK;
}

static inline void sdxc_set_clock_divider(SDXC_Type *base, uint32_t div)
{
    base->MISC_CTRL0 = (base->MISC_CTRL0 & ~SDXC_MISC_CTRL0_FREQ_SEL_SW_MASK) | SDXC_MISC_CTRL0_FREQ_SEL_SW_SET(div) | SDXC_MISC_CTRL0_FREQ_SEL_SW_EN_MASK;
}

static inline uint32_t sdxc_get_clock_divider(SDXC_Type *base)
{
    return SDXC_MISC_CTRL0_FREQ_SEL_SW_GET(base->MISC_CTRL0);
}

/**
 * @brief Wait at least 74 clocks until card is ready to receive the first command
 */
static inline void sdxc_wait_card_active(SDXC_Type *base)
{
    base->SYS_CTRL |= SDXC_SYS_CTRL_SD_CLK_EN_MASK;

    base->MISC_CTRL1 |= SDXC_MISC_CTRL1_CARD_ACTIVE_MASK;

    while (!IS_HPM_BITMASK_SET(base->MISC_CTRL1, SDXC_MISC_CTRL1_CARD_ACTIVE_MASK)) {
    }
}

static inline void sdxc_enable_inverse_clock(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->MISC_CTRL0 |= SDXC_MISC_CTRL0_CARDCLK_INV_EN_MASK;
    } else {
        base->MISC_CTRL0 &= ~SDXC_MISC_CTRL0_CARDCLK_INV_EN_MASK;
    }
}


#if defined(__cplusplus)
}
#endif


#endif /* HPM_SDXC_SOC_DRV_H  */
