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

/**
 *
 * @brief DMAMUX driver APIs
 * @defgroup dmamux_interface DMAMUX driver APIs
 * @{
 */


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Config DMAMUX channel
 *
 * @param[in] ptr DMAMUX base address
 * @param[in] ch_index Target channel index to be configured
 * @param[in] src DMAMUX source, please refer to HPM_DMA_SRC_* macros
 * @param[in] enable Set true to enable the channel
 */
static inline void dmamux_config_channel(DMAMUX_Type *ptr, uint8_t ch_index,
                                 uint8_t src, bool enable)
{
    ptr->CHCFG[ch_index] = DMAMUX_CHCFG_SOURCE_SET(src)
                       | DMAMUX_CHCFG_ENABLE_SET(enable);
}

/**
 * @brief   Enable specific channel
 *
 * @param[in] ptr DMAMUX base address
 * @param[in] ch_index Target channel index
 * @param[in] enable Set true to enable the channel
 */
static inline void dmamux_enable_channel(DMAMUX_Type *ptr, uint8_t ch_index,
                                 bool enable)
{
    ptr->CHCFG[ch_index] = (ptr->CHCFG[ch_index] & ~DMAMUX_CHCFG_ENABLE_MASK)
                        | DMAMUX_CHCFG_ENABLE_SET(enable); 
}
#ifdef __cplusplus
}
#endif
/**
 * @}
 */

#endif /* HPM_DMAMUX_DRV_H */

