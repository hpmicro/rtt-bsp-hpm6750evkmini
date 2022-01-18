/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_DAO_DRV_H
#define HPM_DAO_DRV_H

#include "hpm_common.h"
#include "hpm_dao_regs.h"
#include "hpm_i2s_common.h"

#define DAO_CHANNEL_LEFT_ONLY DAO_CTRL_LEFT_EN_MASK
#define DAO_CHANNEL_RIGHT_ONLY DAO_CTRL_RIGHT_EN_MASK
#define DAO_CHANNEL_BOTH \
    (DAO_CTRL_RIGHT_EN_MASK | DAO_CTRL_LEFT_EN_MASK)

#define DAO_DEFAULT_OUTPUT_ALL_LOW (0U)
#define DAO_DEFAULT_OUTPUT_ALL_HIGH (1U)
#define DAO_DEFAULT_OUTPUT_P_HIGH_N_LOW (2U)
#define DAO_DEFAULT_OUTPUT_DISABLED (3U)

typedef struct dao_config {
    bool enable_mono_output;
    uint8_t default_output_level;
    uint8_t channel_count;
} dao_config_t;

#ifdef __cplusplus
extern "C" {
#endif

static inline void dao_config_hpf(DAO_Type *ptr,
                                     uint32_t hpf_coef_ma,
                                     uint32_t hpf_coef_b,
                                     bool enable)
{
    ptr->HPF_MA = DAO_HPF_MA_COEF_SET(hpf_coef_ma);
    ptr->HPF_B = DAO_HPF_B_COEF_SET(hpf_coef_b);
    ptr->CTRL = (ptr->CTRL & ~DAO_CTRL_HPF_EN_MASK)
        | (enable ? DAO_CTRL_HPF_EN_MASK : 0);
}

static inline void dao_enable_hpf(DAO_Type *ptr)
{
    ptr->CTRL |= DAO_CTRL_HPF_EN_MASK;
}

static inline void dao_disable_hpf(DAO_Type *ptr)
{
    ptr->CTRL &= ~DAO_CTRL_HPF_EN_MASK;
}

static inline void dao_enable_error_irq(DAO_Type *ptr)
{
    ptr->CTRL |= DAO_CTRL_SAT_ERR_IE_MASK;
}

static inline void dao_disable_error_irq(DAO_Type *ptr)
{
    ptr->CTRL &= ~DAO_CTRL_SAT_ERR_IE_MASK;
}

static inline void dao_enable_channel(DAO_Type *ptr, uint32_t ch)
{
    ptr->CTRL |= ch;
}

static inline void dao_disable_channel(DAO_Type *ptr, uint32_t ch)
{
    ptr->CTRL &= ~ch;
}

static inline void dao_enable_mono_output(DAO_Type *ptr)
{
    ptr->CTRL |= DAO_CTRL_MONO_MASK;
}

static inline void dao_disable_mono_output(DAO_Type *ptr)
{
    ptr->CTRL &= ~DAO_CTRL_MONO_MASK;
}

static inline void dao_enable_remap(DAO_Type *ptr)
{
    ptr->CTRL |= DAO_CTRL_REMAP_MASK;
}

static inline void dao_disable_remap(DAO_Type *ptr)
{
    ptr->CTRL &= ~DAO_CTRL_REMAP_MASK;
}

static inline void dao_invert_output(DAO_Type *ptr, bool invert)
{
    ptr->CTRL = (ptr->CTRL & DAO_CTRL_INVERT_MASK)
                | DAO_CTRL_INVERT_SET(invert);
}

/*
 * force pads output with certain level
 */
static inline void dao_force_output(DAO_Type *ptr, uint8_t output)
{
    ptr->CTRL = (ptr->CTRL & DAO_CTRL_FALSE_LEVEL_MASK)
                | DAO_CTRL_FALSE_LEVEL_SET(output);
}

/*
 * when false run mode is enabled, the module continues to consume data,
 * no actual output on pads.
 */
static inline void dao_enable_false_run(DAO_Type *ptr, bool enable)
{
    ptr->CTRL = (ptr->CTRL & DAO_CTRL_FALSE_RUN_MASK)
                | DAO_CTRL_FALSE_RUN_SET(enable);
}

static inline bool dao_has_error_status(DAO_Type *ptr)
{
    return ptr->ST;
}

static inline void dao_clear_error_status(DAO_Type *ptr)
{
    ptr->ST = DAO_ST_SAT_ERR_MASK;
}

static inline void dao_software_reset(DAO_Type *ptr)
{
    ptr->CMD |= DAO_CMD_SFTRST_MASK;
    ptr->CMD &= ~DAO_CMD_SFTRST_MASK;
}

static inline bool dao_is_running(DAO_Type *ptr)
{
    return ptr->CMD & DAO_CMD_RUN_MASK;
}

static inline void dao_start(DAO_Type *ptr)
{
    ptr->CMD |= DAO_CMD_RUN_MASK;
}

static inline void dao_stop(DAO_Type *ptr)
{
    ptr->CMD &= ~DAO_CMD_RUN_MASK;
}

hpm_stat_t dao_init(DAO_Type *ptr, dao_config_t *config);

void dao_get_default_config(DAO_Type *ptr, dao_config_t *config);

#ifdef __cplusplus
}
#endif

#endif /* HPM_DAO_DRV_H */
