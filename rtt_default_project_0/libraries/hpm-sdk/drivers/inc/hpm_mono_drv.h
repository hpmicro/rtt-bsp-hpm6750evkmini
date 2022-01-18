/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_BATT_MONO_DRV_H
#define HPM_BATT_MONO_DRV_H

#include "hpm_common.h"
#include "hpm_batt_mono_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline uint32_t batt_mono_get_counter_high(BATT_MONO_Type *ptr)
{
    return BATT_MONO_MONOH_COUNTER_GET(ptr->MONOH);
}

static inline uint32_t batt_mono_get_counter_low(BATT_MONO_Type *ptr)
{
    return BATT_MONO_MONOL_COUNTER_GET(ptr->MONOL);
}

static inline uint64_t batt_mono_get_counter(BATT_MONO_Type *ptr)
{
    return (uint64_t)(batt_mono_get_counter_high(ptr) << 31)
        | batt_mono_get_counter_low(ptr);
}

static inline uint32_t batt_mono_get_epoch(BATT_MONO_Type *ptr)
{
    return BATT_MONO_MONOH_EPOCH_GET(ptr->MONOH);
}

static inline void batt_mono_count_by_one(BATT_MONO_Type *ptr)
{
    ptr->MONOL = BATT_MONO_MONOL_COUNTER_SET(1);
}

#ifdef __cplusplus
}
#endif
#endif /* HPM_BATT_MONO_DRV_H */

