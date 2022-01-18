/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_BATT_ACC_DRV_H
#define HPM_BATT_ACC_DRV_H

#include "hpm_common.h"
#include "hpm_batt_acc_regs.h"

typedef enum {
    batt_acc_ratio_0 = 0,
    batt_acc_ratio_1_32768 = 1,
    batt_acc_ratio_1_16384 = 2,
    batt_acc_ratio_1_8192 = 3,
    batt_acc_ratio_1_4096 = 4,
    batt_acc_ratio_1_2048 = 5,
    batt_acc_ratio_1_1024 = 6,
    batt_acc_ratio_1_512 = 7,
    batt_acc_ratio_1_256 = 8,
    batt_acc_ratio_1_128 = 9,
    batt_acc_ratio_1_64 = 10,
    batt_acc_ratio_1_32 = 11,
    batt_acc_ratio_1_16 = 12,
    batt_acc_ratio_1_8 = 13,
    batt_acc_ratio_1_4 = 14,
    batt_acc_ratio_1_2 = 15,
} batt_acc_ratio_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * brief set timing gap after rising edge
 *
 * @param ptr BATT_ACC base address
 * @param ratio Ratio of guard band after rising edge
 * @param offset Guard band after rising edge
 */
static inline void batt_acc_timing_gap_post(BATT_ACC_Type *ptr, batt_acc_ratio_t ratio, uint16_t offset)
{
    ptr->PRE_TIME = BATT_ACC_PRE_TIME_POST_RATIO_SET(ratio)
        | BATT_ACC_PRE_TIME_POST_OFFSET_SET(offset);
}

/*
 * brief set timing gap before rising edge
 *
 * @param ptr BATT_ACC base address
 * @param ratio Ratio of guard band before rising edge
 * @param offset Guard band before rising edge
 */
static inline void batt_acc_timing_gap_pre(BATT_ACC_Type *ptr, batt_acc_ratio_t ratio, uint16_t offset)
{
    ptr->PRE_TIME = BATT_ACC_PRE_TIME_PRE_RATIO_SET(ratio)
        | BATT_ACC_PRE_TIME_PRE_OFFSET_SET(offset);
}

/*
 * brief disable fast read
 *
 * @param ptr BATT_ACC base address
 */
static inline void batt_acc_disable_fast_read(BATT_ACC_Type *ptr)
{
    ptr->CONFIG &= ~BATT_ACC_CONFIG_FAST_READ_MASK;
}

/*
 * brief enable fast read
 *
 * @param ptr BATT_ACC base address
 */
static inline void batt_acc_enable_fast_read(BATT_ACC_Type *ptr)
{
    ptr->CONFIG |= BATT_ACC_CONFIG_FAST_READ_MASK;
}

/*
 * brief disable fast wirte
 *
 * @param ptr BATT_ACC base address
 */
static inline void batt_acc_disable_fast_write(BATT_ACC_Type *ptr)
{
    ptr->CONFIG &= ~BATT_ACC_CONFIG_FAST_WRITE_MASK;
}

/*
 * brief enable fast wirte
 *
 * @param ptr BATT_ACC base address
 */
static inline void batt_acc_enable_fast_write(BATT_ACC_Type *ptr)
{
    ptr->CONFIG |= BATT_ACC_CONFIG_FAST_WRITE_MASK;
}

/*
 * brief set timing of access
 *
 * @param ptr BATT_ACC base address
 * @param timing Time in APB clock cycles
 */
static inline void batt_acc_set_timing(BATT_ACC_Type *ptr, uint16_t timing)
{
    ptr->CONFIG = (ptr->CONFIG & ~(BATT_ACC_CONFIG_TIMING_MASK))
        | BATT_ACC_CONFIG_TIMING_SET(timing);
}

#ifdef __cplusplus
}
#endif
#endif /* HPM_BATT_ACC_DRV_H */
