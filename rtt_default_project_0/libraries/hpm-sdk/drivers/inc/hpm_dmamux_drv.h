/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_DMAMUX_DRV_H
#define HPM_DMAMUX_DRV_H
#include "hpm_common.h"
#include "hpm_dmamux_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline void dmamux_config_channel(DMAMUX_Type *ptr, uint8_t ch_num,
                                 dmamux_src_t src, bool enable)
{
    ptr->CHCFG[ch_num] = DMAMUX_CHCFG_SOURCE_SET(src)
                       | DMAMUX_CHCFG_ENABLE_SET(enable);
}

static inline void dmamux_enable_channel(DMAMUX_Type *ptr, uint8_t ch_num,
                                 bool enable)
{
    ptr->CHCFG[ch_num] = (ptr->CHCFG[ch_num] & ~DMAMUX_CHCFG_ENABLE_MASK)
                        | DMAMUX_CHCFG_ENABLE_SET(enable); 
}
#ifdef __cplusplus
}
#endif

#endif /* HPM_DMAMUX_DRV_H */

