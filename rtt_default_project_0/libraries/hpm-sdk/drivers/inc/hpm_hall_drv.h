/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_HALL_DRV_H
#define HPM_HALL_DRV_H

#include "hpm_common.h"
#include "hpm_hall_regs.h"

#define HALL_EVENT_WDOG_FLAG_MASK (1U << 31)
#define HALL_EVENT_PHUPT_FLAG_MASK (1U << 30)
#define HALL_EVENT_PHPRE_FLAG_MASK (1U << 29)
#define HALL_EVENT_PHDLYEN_FLAG_MASK (1U << 28)
#define HALL_EVENT_U_FLAG_MASK (1U << 23)
#define HALL_EVENT_V_FLAG_MASK (1U << 22)
#define HALL_EVENT_W_FLAG_MASK (1U << 21)
#define HALL_UVW_STAT_MASK (HALL_COUNT_U_USTAT_MASK | HALL_COUNT_U_VSTAT_MASK | HALL_COUNT_U_WSTAT_MASK)
#define HALL_U_STAT_MASK HALL_COUNT_U_USTAT_MASK
#define HALL_V_STAT_MASK HALL_COUNT_U_VSTAT_MASK
#define HALL_W_STAT_MASK HALL_COUNT_U_WSTAT_MASK

typedef enum hall_count_delay_start {
    hall_count_delay_start_after_uvw_toggle = 0,
    hall_count_delay_start_after_pre_trigger = 1,
} hall_count_delay_start_t;

typedef enum hall_rotate_direction {
    hall_rotate_direction_forward = 0,
    hall_rotate_direction_reversed = 1
} hall_rotate_direction_t;

typedef enum hall_counter_type {
    hall_counter_type_w = 0,
    hall_counter_type_v = 1,
    hall_counter_type_u = 2,
    hall_counter_type_timer = 3,
} hall_counter_type_t;

#ifdef __cplusplus
extern "C" {
#endif

static inline void hall_wdog_config(HALL_Type *ptr, uint32_t timeout, bool enable)
{
    ptr->WDGCFG = HALL_WDGCFG_WDGTO_SET(timeout)
                | HALL_WDGCFG_WDGEN_SET(enable);
}

static inline void hall_phase_config(HALL_Type *ptr, uint32_t delay_count,
                              hall_count_delay_start_t delay_start)
{
    ptr->PHCFG = HALL_PHCFG_DLYSEL_SET(delay_start)
                | HALL_PHCFG_DLYCNT_SET(delay_count);
}

static inline void hall_pre_uvw_transition_config(HALL_Type *ptr, uint32_t counter)
{
    ptr->UVWCFG = HALL_UVWCFG_PRECNT_SET(counter);
}

static inline void hall_trigger_output_event_enable(HALL_Type *ptr,
                                        uint32_t event_mask, bool enable)
{
    ptr->TRGOEN = (ptr->TRGOEN & ~event_mask) | (enable ? event_mask : 0);
}

static inline void hall_load_read_trigger_event_enable(HALL_Type *ptr,
                                        uint32_t event_mask, bool enable)
{
    ptr->READEN = (ptr->READEN & ~event_mask) | (enable ? event_mask : 0);
}

static inline void hall_clear_status(HALL_Type *ptr, uint32_t mask)
{
    ptr->SR = mask;
}

static inline uint32_t hall_get_status(HALL_Type *ptr)
{
    return ptr->SR;
}

static inline void hall_irq_enable(HALL_Type *ptr, uint32_t mask, bool enable)
{
    ptr->IRQEN = (ptr->IRQEN & ~mask) | (enable ? mask : 0);
}

static inline void hall_dma_request_enable(HALL_Type *ptr, uint32_t mask, bool enable)
{
    ptr->DMAEN = (ptr->DMAEN & ~mask) | (enable ? mask : 0);
}

static inline hall_rotate_direction_t hall_get_rotate_direction(HALL_Type *ptr)
{
    return (hall_rotate_direction_t)HALL_COUNT_U_DIR_GET(ptr->COUNT[HALL_COUNT_CURRENT].U);
}

static inline uint32_t hall_get_current_uvw_stat(HALL_Type *ptr)
{
    return (ptr->COUNT[HALL_COUNT_CURRENT].U & (HALL_UVW_STAT_MASK)) >> HALL_COUNT_U_WSTAT_SHIFT;
}

static inline uint32_t hall_get_current_count(HALL_Type *ptr,
                                            hall_counter_type_t type)
{
    return *(&ptr->COUNT[HALL_COUNT_CURRENT].W + type) & HALL_COUNT_U_UCNT_MASK;
}

static inline uint32_t hall_get_count_on_read_event(HALL_Type *ptr,
                                            hall_counter_type_t type)
{
    return *(&ptr->COUNT[HALL_COUNT_READ].W + type);
}

static inline uint32_t hall_get_count_on_snap0_event(HALL_Type *ptr,
                                            hall_counter_type_t type)
{
    return *(&ptr->COUNT[HALL_COUNT_SNAP0].W + type);
}

static inline uint32_t hall_get_count_on_snap1_event(HALL_Type *ptr,
                                            hall_counter_type_t type)
{
    return *(&ptr->COUNT[HALL_COUNT_SNAP1].W + type);
}

static inline uint32_t hall_get_u_history0(HALL_Type *ptr)
{
    return ptr->HIS[0].HIS0;
}

static inline uint32_t hall_get_u_history1(HALL_Type *ptr)
{
    return ptr->HIS[0].HIS1;
}

static inline uint32_t hall_get_v_history0(HALL_Type *ptr)
{
    return ptr->HIS[1].HIS0;
}

static inline uint32_t hall_get_v_history1(HALL_Type *ptr)
{
    return ptr->HIS[1].HIS1;
}

static inline uint32_t hall_get_w_history0(HALL_Type *ptr)
{
    return ptr->HIS[2].HIS0;
}

static inline uint32_t hall_get_w_history1(HALL_Type *ptr)
{
    return ptr->HIS[2].HIS1;
}

static inline void hall_load_count_to_read_registers(HALL_Type *ptr)
{
    ptr->CR |= HALL_CR_READ_MASK;
}

static inline void hall_snap_enable(HALL_Type *ptr, bool enable)
{
    ptr->CR = (ptr->CR & HALL_CR_SNAPEN_MASK) | HALL_CR_SNAPEN_SET(enable);
}

static inline void hall_counter_reset_assert(HALL_Type *ptr)
{
    ptr->CR |= HALL_CR_RSTCNT_MASK;
}

static inline void hall_counter_reset_release(HALL_Type *ptr)
{
    ptr->CR &= ~HALL_CR_RSTCNT_MASK;
}

#ifdef __cplusplus
}
#endif

#endif /* HPM_HALL_DRV_H */
