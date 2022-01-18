/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PLLCTL_DRV_H
#define HPM_PLLCTL_DRV_H
#include "hpm_common.h"
#include "hpm_soc_feature.h"
#include "hpm_pllctl_regs.h"

#define PLLCTL_PLL_VCO_FREQ_MIN (375000000U)
#define PLLCTL_PLL_VCO_FREQ_MAX (2200000000U)

#define PLLCTL_PLL_LOCK_SS_RESET PLLCTL_PLL_LOCK_LOCK_SS_RSTPTR_MASK
#define PLLCTL_PLL_LOCK_REFDIV PLLCTL_PLL_LOCK_LOCK_REFDIV_MASK
#define PLLCTL_PLL_LOCK_POSTDIV1 PLLCTL_PLL_LOCK_LOCK_POSTDIV1_MASK
#define PLLCTL_PLL_LOCK_SS_SPREAD PLLCTL_PLL_LOCK_LOCK_SS_SPREAD_MASK
#define PLLCTL_PLL_LOCK_SS_DIVVAL PLLCTL_PLL_LOCK_LOCK_SS_DIVVAL_MASK

enum {
    status_pllctl_not_enabled = MAKE_STATUS(status_group_pllctl, 1),
    status_pllctl_out_of_range = MAKE_STATUS(status_group_pllctl, 2),
};

#ifdef __cplusplus
extern "C" {
#endif

static inline void pllctl_pll_unlock(PLLCTL_Type *ptr, uint8_t pll, uint32_t lock_mask)
{
    ptr->PLL[pll].LOCK &= ~lock_mask;
}

static inline void pllctl_pll_lock(PLLCTL_Type *ptr, uint8_t pll, uint32_t lock_mask)
{
    ptr->PLL[pll].LOCK = lock_mask;
}

static inline hpm_stat_t pllctl_pll_ss_disable(PLLCTL_Type *ptr, uint8_t pll)
{
    if (pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1)) {
        return status_invalid_argument;
    }

    ptr->PLL[pll].CFG0 |= (PLLCTL_PLL_CFG0_SS_RSTPTR_MASK
                            | PLLCTL_PLL_CFG0_SS_RESET_MASK);
    ptr->PLL[pll].CFG0 |= PLLCTL_PLL_CFG0_SS_DISABLE_SSCG_MASK;
    return status_success;
}

static inline hpm_stat_t pllctl_pll_powerdown(PLLCTL_Type *ptr, uint8_t pll)
{
    if (pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1)) {
        return status_invalid_argument;
    }

    ptr->PLL[pll].CFG1 = (ptr->PLL[pll].CFG1 &
            ~(PLLCTL_PLL_CFG1_PLLCTRL_HW_EN_MASK | PLLCTL_PLL_CFG1_CLKEN_SW_MASK))
            | PLLCTL_PLL_CFG1_PLLPD_SW_MASK;
    return status_success;
}

static inline hpm_stat_t pllctl_pll_poweron(PLLCTL_Type *ptr, uint8_t pll)
{
    uint32_t cfg;
    if (pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1)) {
        return status_invalid_argument;
    }

    cfg = ptr->PLL[pll].CFG1;
    if (!(cfg & PLLCTL_PLL_CFG1_PLLPD_SW_MASK)) {
        return status_success;
    }

    if (cfg & PLLCTL_PLL_CFG1_PLLCTRL_HW_EN_MASK) {
        ptr->PLL[pll].CFG1 &= ~PLLCTL_PLL_CFG1_PLLCTRL_HW_EN_MASK;
    }

    ptr->PLL[pll].CFG1 &= ~PLLCTL_PLL_CFG1_PLLPD_SW_MASK;

    /*
     * put back to hardware mode
     */
    ptr->PLL[pll].CFG1 |= PLLCTL_PLL_CFG1_PLLCTRL_HW_EN_MASK;
    return status_success;
}

static inline hpm_stat_t pllctl_pll_ss_enable(PLLCTL_Type *ptr, uint8_t pll,
                                                uint8_t spread, uint8_t div,
                                                bool down_spread)
{
    if (pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1)) {
        return status_invalid_argument;
    }
    if (!(ptr->PLL[pll].CFG1 & PLLCTL_PLL_CFG1_PLLPD_SW_MASK)) {
        pllctl_pll_powerdown(ptr, pll);
    }

    ptr->PLL[pll].CFG0 &= ~(PLLCTL_PLL_CFG0_SS_RSTPTR_MASK
                            | PLLCTL_PLL_CFG0_SS_RESET_MASK);
    ptr->PLL[pll].CFG0 &= ~PLLCTL_PLL_CFG0_SS_DISABLE_SSCG_MASK;
    ptr->PLL[pll].CFG0 = (ptr->PLL[pll].CFG0
        & ~(PLLCTL_PLL_CFG0_SS_SPREAD_MASK | PLLCTL_PLL_CFG0_SS_DIVVAL_MASK))
        | PLLCTL_PLL_CFG0_SS_SPREAD_SET(spread)
        | PLLCTL_PLL_CFG0_SS_DIVVAL_SET(div)
        | PLLCTL_PLL_CFG0_SS_DOWNSPREAD_SET(down_spread);

    pllctl_pll_poweron(ptr, pll);
    return status_success;
}

static inline hpm_stat_t pllctl_set_fbdiv_int(PLLCTL_Type *ptr, uint8_t pll, uint16_t div)
{
    if ((pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1))
            || ((div - 1)> (PLLCTL_PLL_CFG2_FBDIV_INT_MASK >> PLLCTL_PLL_CFG2_FBDIV_INT_SHIFT))) {
        return status_invalid_argument;
    }

    ptr->PLL[pll].CFG2 = ((ptr->PLL[pll].CFG2 & ~(PLLCTL_PLL_CFG2_FBDIV_INT_MASK))) | PLLCTL_PLL_CFG2_FBDIV_INT_SET(div - 1);
    return status_success;
}

static inline hpm_stat_t pllctl_set_fbdiv_frac(PLLCTL_Type *ptr, uint8_t pll, uint16_t div)
{
    if ((pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1))
            || ((div - 1)> (PLLCTL_PLL_FREQ_FBDIV_FRAC_MASK >> PLLCTL_PLL_FREQ_FBDIV_FRAC_SHIFT))) {
        return status_invalid_argument;
    }

    ptr->PLL[pll].FREQ = (ptr->PLL[pll].FREQ & ~(PLLCTL_PLL_FREQ_FBDIV_FRAC_MASK))
                        | PLLCTL_PLL_FREQ_FBDIV_FRAC_SET(div - 1);
    return status_success;
}

static inline hpm_stat_t pllctl_set_frac(PLLCTL_Type *ptr, uint8_t pll, uint32_t frac)
{
    if ((pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1))
            || (frac > (PLLCTL_PLL_FREQ_FRAC_MASK >> PLLCTL_PLL_FREQ_FRAC_SHIFT))) {
        return status_invalid_argument;
    }
    ptr->PLL[pll].FREQ = (ptr->PLL[pll].FREQ & ~(PLLCTL_PLL_FREQ_FRAC_MASK))
                        | PLLCTL_PLL_FREQ_FRAC_SET(frac);
    return status_success;
}

static inline hpm_stat_t pllctl_get_div(PLLCTL_Type *ptr, uint8_t pll, uint8_t div_index)
{
    if ((pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1))
            || !(PLLCTL_SOC_PLL_HAS_DIV0(pll))) {
        return status_invalid_argument;
    }
    if (div_index) {
        return PLLCTL_PLL_DIV0_DIV_GET(ptr->PLL[pll].DIV1) + 1;
    } else {
        return PLLCTL_PLL_DIV0_DIV_GET(ptr->PLL[pll].DIV0) + 1;
    }
}

static inline hpm_stat_t pllctl_set_div(PLLCTL_Type *ptr, uint8_t pll, uint8_t div_index, uint16_t div)
{
    if ((pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1))
            || !(PLLCTL_SOC_PLL_HAS_DIV0(pll))
            || ((div - 1) > (PLLCTL_PLL_DIV0_DIV_MASK >> PLLCTL_PLL_DIV0_DIV_SHIFT))) {
        return status_invalid_argument;
    }

    if (div_index) {
        ptr->PLL[pll].DIV1 = (ptr->PLL[pll].DIV1 & ~(PLLCTL_PLL_DIV1_DIV_MASK))
                            | PLLCTL_PLL_DIV1_DIV_SET(div - 1);
    } else {
        ptr->PLL[pll].DIV0 = (ptr->PLL[pll].DIV0 & ~(PLLCTL_PLL_DIV0_DIV_MASK))
                            | PLLCTL_PLL_DIV0_DIV_SET(div - 1);
    }
    return status_success;
}

static inline bool pllctl_div_is_stable(PLLCTL_Type *ptr, uint8_t pll, uint8_t div_index) 
{
    if ((pll > (PLLCTL_SOC_PLL_MAX_COUNT - 1)) || !(PLLCTL_SOC_PLL_HAS_DIV0(pll))) {
        return false;
    }
    if (div_index) {
        return ptr->PLL[pll].DIV1 & PLLCTL_PLL_DIV0_RESPONSE_MASK;
    } else {
        return ptr->PLL[pll].DIV0 & PLLCTL_PLL_DIV0_RESPONSE_MASK;
    }
}

static inline bool pllctl_pll_is_enabled(PLLCTL_Type *ptr, uint8_t pll)
{
    return (ptr->PLL[pll].STATUS & PLLCTL_PLL_STATUS_ENABLE_MASK);
}

static inline bool pllctl_xtal_is_stable(PLLCTL_Type *ptr)
{
    return ptr->XTAL & PLLCTL_XTAL_RESPONSE_MASK;
}

static inline bool pllctl_xtal_is_enabled(PLLCTL_Type *ptr)
{
    return ptr->XTAL & PLLCTL_XTAL_ENABLE_MASK;
}

/*
 * set XTAL rampup time in cycles of IRC24M
 */
static inline void pllctl_xtal_set_rampup_time(PLLCTL_Type *ptr, uint32_t cycles)
{
    ptr->XTAL = (ptr->XTAL & ~PLLCTL_XTAL_RAMP_TIME_MASK) | PLLCTL_XTAL_RAMP_TIME_SET(cycles);
}

hpm_stat_t pllctl_set_refdiv(PLLCTL_Type *ptr, uint8_t pll, uint8_t div);

hpm_stat_t pllctl_init_int_pll_with_freq(PLLCTL_Type *ptr, uint8_t pll,
                                    uint32_t freq_in_hz);

hpm_stat_t pllctl_init_frac_pll_with_freq(PLLCTL_Type *ptr, uint8_t pll,
                                    uint32_t freq_in_hz);

uint32_t pllctl_get_pll_freq_in_hz(PLLCTL_Type *ptr, uint8_t pll);

#ifdef __cplusplus
}
#endif
#endif /* HPM_PLLCTL_DRV_H */

