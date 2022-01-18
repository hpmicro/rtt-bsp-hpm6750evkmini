/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PTPC_DRV_H
#define HPM_PTPC_DRV_H

#include "hpm_common.h"
#include "hpm_ptpc_regs.h"

#define PTPC_EVENT_COMPARE1_MASK (1U << 18)
#define PTPC_EVENT_CAPTURE1_MASK (1U << 17)
#define PTPC_EVENT_PPS1_MASK (1U << 16)
#define PTPC_EVENT_COMPARE0_MASK (1U << 2)
#define PTPC_EVENT_CAPTURE0_MASK (1U << 1)
#define PTPC_EVENT_PPS0_MASK (1U << 0)

typedef enum ptpc_ns_counter_rollover_type {
    ptpc_nc_counter_rollover_binary = 0,
    ptpc_nc_counter_rollover_digital = 1,
} ptpc_ns_counter_rollover_type_t;

typedef enum ptpc_capture_trigger_type {
    ptpc_capture_trigger_type_positive_edge = PTPC_PTPC_CTRL0_CAPT_SNAP_POS_EN_MASK,
    ptpc_capture_trigger_type_negative_edge = PTPC_PTPC_CTRL0_CAPT_SNAP_NEG_EN_MASK,
    ptpc_capture_trigger_type_both_edges = PTPC_PTPC_CTRL0_CAPT_SNAP_POS_EN_MASK
                                        | PTPC_PTPC_CTRL0_CAPT_SNAP_NEG_EN_MASK,
} ptpc_capture_trigger_type_t;

#ifdef __cplusplus
extern "C" {
#endif

static inline void ptpc_config_ns_counter_rollover(PTPC_Type *ptr, uint8_t index,
                                ptpc_ns_counter_rollover_type_t rollover)
{
    ptr->PTPC[index].CTRL0 = (ptr->PTPC[index].CTRL0 & ~PTPC_PTPC_CTRL0_SUBSEC_DIGITAL_ROLLOVER_MASK)
        | PTPC_PTPC_CTRL0_SUBSEC_DIGITAL_ROLLOVER_SET(rollover);
}

static inline void ptpc_set_ns_counter_update_type(PTPC_Type *ptr, uint8_t index, bool fine_update)
{
    ptr->PTPC[index].CTRL0 = (ptr->PTPC[index].CTRL0 & ~PTPC_PTPC_CTRL0_FINE_COARSE_SEL_MASK)
        | PTPC_PTPC_CTRL0_FINE_COARSE_SEL_SET(fine_update);
}

static inline void ptpc_init_timer_values(PTPC_Type *ptr, uint8_t index, uint32_t high, uint32_t low)
{
    ptr->PTPC[index].TS_UPDTH = PTPC_PTPC_TS_UPDTH_SEC_UPDATE_SET(high);
    ptr->PTPC[index].TS_UPDTL = PTPC_PTPC_TS_UPDTL_NS_UPDATE_SET(low);
}

static inline void ptpc_init_timer(PTPC_Type *ptr, uint8_t index)
{
    ptr->PTPC[index].CTRL0 |= PTPC_PTPC_CTRL0_INIT_TIMER_MASK;
}

static inline void ptpc_update_timer_values(PTPC_Type *ptr, uint8_t index,
                                    uint32_t high, uint32_t low, bool decr)
{
    ptr->PTPC[index].TS_UPDTH = PTPC_PTPC_TS_UPDTH_SEC_UPDATE_SET(high);
    ptr->PTPC[index].TS_UPDTL = PTPC_PTPC_TS_UPDTL_NS_UPDATE_SET(low) | PTPC_PTPC_TS_UPDTL_ADD_SUB_SET(decr);
}

static inline void ptpc_update_timer(PTPC_Type *ptr, uint8_t index)
{
    ptr->PTPC[index].CTRL0 |= PTPC_PTPC_CTRL0_UPDATE_TIMER_MASK;
}

static inline void ptpc_set_cmp(PTPC_Type *ptr, uint8_t index, uint32_t high, uint32_t low)
{
    ptr->PTPC[index].TARH = PTPC_PTPC_TARH_TARGET_TIME_HIGH_SET(high);
    ptr->PTPC[index].TARL = PTPC_PTPC_TARL_TARGET_TIME_LOW_SET(low);
}

static inline void ptpc_enable_cmp(PTPC_Type *ptr, uint8_t index, bool enable)
{
    ptr->PTPC[index].CTRL0 = (ptr->PTPC[index].CTRL0 & ~PTPC_PTPC_CTRL0_COMP_EN_MASK)
                | PTPC_PTPC_CTRL0_COMP_EN_SET(enable);
}

static inline void ptpc_config_capture_trigger(PTPC_Type *ptr, uint8_t index,
                                ptpc_capture_trigger_type_t trigger)
{
    ptr->PTPC[index].CTRL0 = (ptr->PTPC[index].CTRL0 & ~(PTPC_PTPC_CTRL0_CAPT_SNAP_POS_EN_MASK
                | PTPC_PTPC_CTRL0_CAPT_SNAP_NEG_EN_MASK)) | trigger;
}

static inline void ptpc_enable_capture_keep(PTPC_Type *ptr, uint8_t index, bool enable)
{
    ptr->PTPC[index].CTRL0 = (ptr->PTPC[index].CTRL0 & ~PTPC_PTPC_CTRL0_CAPT_SNAP_KEEP_MASK)
        | PTPC_PTPC_CTRL0_CAPT_SNAP_KEEP_SET(enable);
}

static inline void ptpc_enable_timer(PTPC_Type *ptr, uint8_t index, bool enable)
{
    ptr->PTPC[index].CTRL0 = (ptr->PTPC[index].CTRL0 & ~PTPC_PTPC_CTRL0_TIMER_ENABLE_MASK)
                    | PTPC_PTPC_CTRL0_TIMER_ENABLE_SET(enable);
}

static inline void ptpc_set_ns_counter_incr(PTPC_Type *ptr, uint8_t index, uint32_t incr)
{
    ptr->PTPC[index].CTRL1 = PTPC_PTPC_CTRL1_SS_INCR_SET(incr);
}

static inline uint32_t ptpc_get_timestamp_high(PTPC_Type *ptr, uint8_t index)
{
    return PTPC_PTPC_TIMEH_TIMESTAMP_HIGH_GET(ptr->PTPC[index].TIMEH);
}

static inline void ptpc_set_timestamp_high(PTPC_Type *ptr, uint8_t index, uint32_t high)
{
    ptr->PTPC[index].TIMEH = PTPC_PTPC_TIMEH_TIMESTAMP_HIGH_SET(high);
}

static inline uint32_t ptpc_get_timestamp_low(PTPC_Type *ptr, uint8_t index)
{
    return PTPC_PTPC_TIMEL_TIMESTAMP_LOW_GET(ptr->PTPC[index].TIMEL);
}

static inline void ptpc_set_timestamp_low(PTPC_Type *ptr, uint8_t index, uint32_t low)
{
    ptr->PTPC[index].TIMEL = PTPC_PTPC_TIMEL_TIMESTAMP_LOW_SET(low);
}

static inline void ptpc_update_timestamp_high(PTPC_Type *ptr, uint8_t index, uint32_t high)
{
    ptr->PTPC[index].TS_UPDTH = PTPC_PTPC_TS_UPDTH_SEC_UPDATE_SET(high);
}

static inline void ptpc_update_timestamp_low(PTPC_Type *ptr, uint8_t index, uint32_t low, bool decr)
{
    ptr->PTPC[index].TS_UPDTL = PTPC_PTPC_TS_UPDTL_NS_UPDATE_SET(low) | PTPC_PTPC_TS_UPDTL_ADD_SUB_SET(decr);
}

static inline void ptpc_set_pps_ctrl(PTPC_Type *ptr, uint8_t index, uint32_t pps)
{
    ptr->PTPC[index].PPS_CTRL = PTPC_PTPC_PPS_CTRL_PPS_CTRL_SET(pps);
}

static inline uint32_t ptpc_get_capture_high(PTPC_Type *ptr, uint8_t index)
{
    return PTPC_PTPC_CAPT_SNAPH_CAPT_SNAP_HIGH_GET(ptr->PTPC[index].CAPT_SNAPH);
}

static inline void ptpc_set_capture_high(PTPC_Type *ptr, uint8_t index, uint32_t high)
{
    ptr->PTPC[index].CAPT_SNAPH = PTPC_PTPC_CAPT_SNAPH_CAPT_SNAP_HIGH_SET(high);
}

static inline uint32_t ptpc_get_capture_low(PTPC_Type *ptr, uint8_t index)
{
    return PTPC_PTPC_CAPT_SNAPL_CAPT_SNAP_LOW_GET(ptr->PTPC[index].CAPT_SNAPL);
}

static inline void ptpc_set_capture_low(PTPC_Type *ptr, uint8_t index, uint32_t low)
{
    ptr->PTPC[index].CAPT_SNAPL = PTPC_PTPC_CAPT_SNAPL_CAPT_SNAP_LOW_SET(low);
}

static inline void ptpc_timer_select(PTPC_Type *ptr, uint8_t can_index, bool use_ptpc1)
{
    ptr->TIME_SEL = (ptr->TIME_SEL & ~(1 << can_index))
                | (use_ptpc1 ? (1 << can_index) : 0);
}

static inline void ptpc_clear_status(PTPC_Type *ptr, uint32_t mask)
{
    ptr->INT_STS |= mask;
}

static inline uint32_t ptpc_get_status(PTPC_Type *ptr)
{
    return ptr->INT_STS;
}

static inline void ptpc_irq_enable(PTPC_Type *ptr, uint32_t mask, bool enable)
{
    ptr->INT_EN = (ptr->INT_EN & ~mask) | (enable ? mask : 0);
}

#ifdef __cplusplus
}
#endif

#endif /* HPM_PTPC_DRV_H */
