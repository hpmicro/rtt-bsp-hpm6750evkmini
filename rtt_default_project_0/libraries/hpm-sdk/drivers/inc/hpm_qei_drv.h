/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_QEI_DRV_H
#define HPM_QEI_DRV_H

#include "hpm_common.h"
#include "hpm_qei_regs.h"

#define QEI_EVENT_WDOG_FLAG_MASK (1U << 31)
#define QEI_EVENT_HOME_FLAG_MASK (1U << 30)
#define QEI_EVENT_POSITIVE_COMPARE_FLAG_MASK (1U << 29)
#define QEI_EVENT_Z_PHASE_FLAG_MASK (1U << 28)

typedef enum qei_z_count_inc_mode {
    qei_z_count_inc_on_z_input_assert = 0,
    qei_z_count_inc_on_phase_count_max = 1,
} qei_z_count_inc_mode_t;

typedef enum qei_rotation_dir_cmp {
    qei_rotation_dir_cmp_positive = 0,
    qei_rotation_dir_cmp_negative= 1,
    qei_rotation_dir_cmp_ignore = 2,
} qei_rotation_dir_cmp_t;

typedef enum qei_counter_type {
    qei_counter_type_z = 0,
    qei_counter_type_phase = 1,
    qei_counter_type_speed = 2,
    qei_counter_type_timer = 3,
} qei_counter_type_t;

typedef enum qei_work_mode {
    qei_work_mode_abz = 0,
    qei_work_mode_pd = 1,
    qei_work_mode_ud = 2,
} qei_work_mode_t;

#ifdef __cplusplus
extern "C" {
#endif

static inline void qei_wdog_enable(QEI_Type *ptr)
{
    ptr->WDGCFG |= QEI_WDGCFG_WDGEN_MASK;
}

static inline void qei_wdog_disable(QEI_Type *ptr)
{
    ptr->WDGCFG &= ~QEI_WDGCFG_WDGEN_MASK;
}

static inline void qei_wdog_config(QEI_Type *ptr, uint32_t timeout, bool enable)
{
    ptr->WDGCFG = QEI_WDGCFG_WDGTO_SET(timeout) | QEI_WDGCFG_WDGEN_SET(enable);
}

static inline void qei_phase_config(QEI_Type *ptr, uint32_t phase_count,
                              qei_z_count_inc_mode_t mode, bool z_calibrate)
{
    ptr->PHCFG = QEI_PHCFG_ZCNTCFG_SET(mode) | QEI_PHCFG_PHCALIZ_SET(z_calibrate)
                | QEI_PHCFG_PHMAX_SET(phase_count - 1);
}

static inline void qei_phase_set_index(QEI_Type *ptr, uint32_t phase_index)
{
    ptr->PHIDX = QEI_PHIDX_PHIDX_SET(phase_index);
}

static inline void qei_output_trigger_event_enable(QEI_Type *ptr, uint32_t event_mask)
{
    ptr->TRGOEN |= event_mask;
}

static inline void qei_output_trigger_event_disable(QEI_Type *ptr, uint32_t event_mask)
{
    ptr->TRGOEN &= ~event_mask;
}

static inline void qei_load_read_trigger_event_enable(QEI_Type *ptr, uint32_t event_mask)
{
    ptr->READEN |= event_mask;
}

static inline void qei_load_read_trigger_event_disable(QEI_Type *ptr, uint32_t event_mask)
{
    ptr->READEN &= ~event_mask;
}

static inline void qei_z_cmp_set(QEI_Type *ptr, uint32_t cmp)
{
    ptr->ZCMP = QEI_ZCMP_ZCMP_SET(cmp);
}

static inline void qei_speed_cmp_set(QEI_Type *ptr, uint32_t cmp)
{
    ptr->SPDCMP = QEI_SPDCMP_SPDCMP_SET(cmp);
}

static inline void qei_phase_cmp_set(QEI_Type *ptr, uint32_t cmp,
                            bool cmp_z, qei_rotation_dir_cmp_t rotation_dir)
{
    ptr->PHCMP = QEI_PHCMP_PHCMP_SET(cmp)
        | QEI_PHCMP_ZCMPDIS_SET(!cmp_z)
        | ((rotation_dir == qei_rotation_dir_cmp_ignore)
                ? QEI_PHCMP_DIRCMPDIS_MASK : (QEI_PHCMP_DIRCMP_SET(rotation_dir)));
}

static inline void qei_clear_status(QEI_Type *ptr, uint32_t mask)
{
    ptr->SR = mask;
}

static inline uint32_t qei_get_status(QEI_Type *ptr)
{
    return ptr->SR;
}

static inline bool qei_get_bit_status(QEI_Type *ptr, uint32_t mask)
{
    if((ptr->SR & mask) == mask){
        return true;
    }
    else{
        return false;
    }
}

static inline void qei_irq_enable(QEI_Type *ptr, uint32_t mask)
{
    ptr->IRQEN |= mask;
}

static inline void qei_irq_disable(QEI_Type *ptr, uint32_t mask)
{
    ptr->IRQEN &= ~mask;
}

static inline void qei_dma_request_enable(QEI_Type *ptr, uint32_t mask)
{
    ptr->DMAEN |= mask;
}

static inline void qei_dma_request_disable(QEI_Type *ptr, uint32_t mask)
{
    ptr->DMAEN &= ~mask;
}

static inline uint32_t qei_get_current_count(QEI_Type *ptr,
                                            qei_counter_type_t type)
{
    return *(&ptr->COUNT[QEI_COUNT_CURRENT].Z + type);
}

static inline uint32_t qei_get_count_on_read_event(QEI_Type *ptr,
                                            qei_counter_type_t type)
{
    return *(&(ptr->COUNT[QEI_COUNT_READ].Z) + type);
}

static inline uint32_t qei_get_count_on_snap0_event(QEI_Type *ptr,
                                            qei_counter_type_t type)
{
    return *(&ptr->COUNT[QEI_COUNT_SNAP0].Z + type);
}

static inline uint32_t qei_get_count_on_snap1_event(QEI_Type *ptr,
                                            qei_counter_type_t type)
{
    return *(&ptr->COUNT[QEI_COUNT_SNAP1].Z + type);
}

static inline uint32_t qei_get_speed_history(QEI_Type *ptr, uint8_t hist_index)
{
    if (hist_index > QEI_SPDHIS_SPDHIS3) {
        return 0;
    }
    return QEI_SPDHIS_SPDHIS0_GET(ptr->SPDHIS[hist_index]);
}

static inline void qei_load_counter_to_read_registers(QEI_Type *ptr)
{
    ptr->CR |= QEI_CR_READ_MASK;
}

static inline void qei_reset_counter_on_h_assert(QEI_Type *ptr,
                                               uint32_t counter_mask)
{
    ptr->CR |= counter_mask << 16;
}

static inline void qei_pause_counter_on_pause(QEI_Type *ptr,
                                               uint32_t counter_mask)
{
    ptr->CR |= counter_mask << 12;
}

static inline void qei_snap_enable(QEI_Type *ptr)
{
    ptr->CR |= QEI_CR_SNAPEN_MASK;
}

static inline void qei_snap_disable(QEI_Type *ptr)
{
    ptr->CR &= ~QEI_CR_SNAPEN_MASK;
}

static inline void qei_counter_reset_assert(QEI_Type *ptr)
{
    ptr->CR |= QEI_CR_RSTCNT_MASK;
}

static inline void qei_counter_reset_release(QEI_Type *ptr)
{
    ptr->CR &= ~QEI_CR_RSTCNT_MASK;
}

static inline void qei_set_work_mode(QEI_Type *ptr, qei_work_mode_t mode)
{
    ptr->CR = (ptr->CR & ~QEI_CR_ENCTYP_MASK) | QEI_CR_ENCTYP_SET(mode);
}

#ifdef __cplusplus
}
#endif

#endif /* HPM_QEI_DRV_H */
