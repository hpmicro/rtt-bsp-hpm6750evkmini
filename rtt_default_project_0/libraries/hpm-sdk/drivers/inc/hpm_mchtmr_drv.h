/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_MCHTMR_DRV_H
#define HPM_MCHTMR_DRV_H
#include "hpm_common.h"
#include "hpm_mchtmr_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline uint64_t mchtmr_get_count(MCHTMR_Type *ptr)
{
    return (ptr->MTIME & MCHTMR_MTIME_MTIME_MASK) >> MCHTMR_MTIME_MTIME_SHIFT;
}

static inline void mchtmr_set_compare_value(MCHTMR_Type *ptr, uint64_t target)
{
    ptr->MTIMECMP = MCHTMR_MTIMECMP_MTIMECMP_SET(target);
}

static inline void mchtmr_delay(MCHTMR_Type *ptr, uint64_t delay)
{
    mchtmr_set_compare_value(ptr, mchtmr_get_count(ptr) + delay);
}

#ifdef __cplusplus
}
#endif
#endif /* HPM_MCHTMR_DRV_H */
