/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_GPTMR_DRV_H
#define HPM_GPTMR_DRV_H
#include "hpm_common.h"
#include "hpm_gptmr_regs.h"

#define _GPTMR_CH_CMP_IRQ_MASK(ch, cmp) GPTMR_IRQEN_CH##ch##CMP##cmp##EN_MASK
#define _GPTMR_CH_CAP_IRQ_MASK(ch) GPTMR_IRQEN_CH##ch##CAPEN_MASK
#define _GPTMR_CH_RLD_IRQ_MASK(ch) GPTMR_IRQEN_CH##ch##RLDEN_MASK

#define GPTMR_CH_CMP_IRQ_MASK(ch, cmp) _GPTMR_CH_CMP_IRQ_MASK(ch, cmp)
#define GPTMR_CH_CAP_IRQ_MASK(ch) _GPTMR_CH_CAP_IRQ_MASK(ch)
#define GPTMR_CH_RLD_IRQ_MASK(ch) _GPTMR_CH_RLD_IRQ_MASK(ch)

#define _GPTMR_CH_CMP_STAT_MASK(ch, cmp) GPTMR_SR_CH##ch##CMP##cmp##F_MASK
#define _GPTMR_CH_CAP_STAT_MASK(ch) GPTMR_SR_CH##ch##CAPF_MASK
#define _GPTMR_CH_RLD_STAT_MASK(ch) GPTMR_SR_CH##ch##RLDF_MASK

#define GPTMR_CH_CMP_STAT_MASK(ch, cmp) _GPTMR_CH_CMP_STAT_MASK(ch, cmp)
#define GPTMR_CH_CAP_STAT_MASK(ch) _GPTMR_CH_CAP_STAT_MASK(ch)
#define GPTMR_CH_RLD_STAT_MASK(ch) _GPTMR_CH_RLD_STAT_MASK(ch)

#define GPTMR_CH_CMP_COUNT (2U)

typedef enum gptmr_synci_edge {
    gptmr_synci_edge_none = 0,
    gptmr_synci_edge_falling = GPTMR_CHANNEL_CR_SYNCIFEN_MASK,
    gptmr_synci_edge_rising = GPTMR_CHANNEL_CR_SYNCIREN_MASK,
    gptmr_synci_edge_both = gptmr_synci_edge_falling | gptmr_synci_edge_rising,
} gptmr_synci_edge_t;

typedef enum gptmr_work_mode {
    gptmr_work_mode_no_capture = 0,
    gptmr_work_mode_capture_at_rising_edge = 1,
    gptmr_work_mode_capture_at_falling_edge = 2,
    gptmr_work_mode_capture_at_both_edge = 3,
    gptmr_work_mode_measure_width = 4,
} gptmr_work_mode_t;

typedef enum gptmr_dma_request_event {
    gptmr_dma_request_on_reload = 0,
    gptmr_dma_request_on_input_signal_toggle = 1,
    gptmr_dma_request_on_cmp0 = 2,
    gptmr_dma_request_on_cmp1 = 3,
    gptmr_dma_request_disabled = 0xFF,
} gptmr_dma_request_event_t;

typedef enum gptmr_counter_type {
    gptmr_counter_type_rising_edge,
    gptmr_counter_type_falling_edge,
    gptmr_counter_type_measured_period,
    gptmr_counter_type_measured_duty_cycle,
    gptmr_counter_type_normal,
} gptmr_counter_type_t;

typedef struct gptmr_channel_config {
    gptmr_work_mode_t mode;
    gptmr_dma_request_event_t dma_request_event;
    gptmr_synci_edge_t synci_edge;
    uint32_t cmp[GPTMR_CH_CMP_COUNT];
    uint32_t reload;
    bool cmp_initial_polarity_high;
    bool enable_cmp_output;
    bool enable_sync_follow_previous_channel;
    bool enable_software_sync;
    bool debug_mode;
} gptmr_channel_config_t;

#ifdef __cplusplus
extern "C" {
#endif

static inline void gptmr_channel_enable(GPTMR_Type *ptr, uint8_t ch_index, bool enable)
{
    ptr->CHANNEL[ch_index].CR = (ptr->CHANNEL[ch_index].CR
         & ~(GPTMR_CHANNEL_CR_CNTRST_MASK | GPTMR_CHANNEL_CR_CMPEN_MASK))
        | GPTMR_CHANNEL_CR_CMPEN_SET(enable);
}

static inline void gptmr_channel_reset_count(GPTMR_Type *ptr, uint8_t ch_index)
{
    ptr->CHANNEL[ch_index].CR |= GPTMR_CHANNEL_CR_CNTRST_MASK;
    ptr->CHANNEL[ch_index].CR &= ~GPTMR_CHANNEL_CR_CNTRST_MASK;
}

static inline void gptmr_channel_update_count(GPTMR_Type *ptr,
                                             uint8_t ch_index,
                                             uint32_t value)
{
    ptr->CHANNEL[ch_index].CNTUPTVAL = GPTMR_CHANNEL_CNTUPTVAL_CNTUPTVAL_SET(value);
    ptr->CHANNEL[ch_index].CR |= GPTMR_CHANNEL_CR_CNTUPT_MASK;
}

static inline void gptmr_channel_select_synci_valid_edge(GPTMR_Type *ptr,
                                                        uint8_t ch_index,
                                                        gptmr_synci_edge_t edge)
{
    ptr->CHANNEL[ch_index].CR = (ptr->CHANNEL[ch_index].CR
            & ~(GPTMR_CHANNEL_CR_SYNCIFEN_MASK
              | GPTMR_CHANNEL_CR_SYNCIREN_MASK)) | edge;
}

static inline void gptmr_channel_enable_dma_request(GPTMR_Type *ptr,
                                                   uint8_t ch_index,
                                                   bool enable)
{
    ptr->CHANNEL[ch_index].CR = (ptr->CHANNEL[ch_index].CR
            & ~(GPTMR_CHANNEL_CR_DMAEN_MASK)) | GPTMR_CHANNEL_CR_DMAEN_SET(enable);
}

static inline uint32_t gptmr_channel_get_counter(GPTMR_Type *ptr,
                                                     uint8_t ch_index,
                                                     gptmr_counter_type_t capture)
{
    uint32_t value;
    switch (capture) {
        case gptmr_counter_type_rising_edge:
            value = (ptr->CHANNEL[ch_index].CAPPOS & GPTMR_CHANNEL_CAPPOS_CAPPOS_MASK) >> GPTMR_CHANNEL_CAPPOS_CAPPOS_SHIFT;
            break;
        case gptmr_counter_type_falling_edge:
            value = (ptr->CHANNEL[ch_index].CAPNEG & GPTMR_CHANNEL_CAPNEG_CAPNEG_MASK) >> GPTMR_CHANNEL_CAPNEG_CAPNEG_SHIFT;
            break;
        case gptmr_counter_type_measured_period:
            value = (ptr->CHANNEL[ch_index].CAPPRD & GPTMR_CHANNEL_CAPPRD_CAPPRD_MASK) >> GPTMR_CHANNEL_CAPPRD_CAPPRD_SHIFT;
            break;
        case gptmr_counter_type_measured_duty_cycle:
            value = (ptr->CHANNEL[ch_index].CAPDTY & GPTMR_CHANNEL_CAPDTY_MEAS_HIGH_MASK) >> GPTMR_CHANNEL_CAPDTY_MEAS_HIGH_SHIFT;
            break;
        default:
            value = (ptr->CHANNEL[ch_index].CNT & GPTMR_CHANNEL_CNT_COUNTER_MASK) >> GPTMR_CHANNEL_CNT_COUNTER_SHIFT;
            break;
    }
    return value;
}

static inline void gptmr_trigger_channel_software_sync(GPTMR_Type *ptr, uint32_t ch_index_mask)
{
    ptr->GCR = ch_index_mask;
}

static inline void gptmr_enable_irq(GPTMR_Type *ptr, uint32_t irq_mask, bool enable)
{
    if (enable) {
        ptr->IRQEN |= irq_mask;
    } else {
        ptr->IRQEN &= ~irq_mask;
    }
}

static inline bool gptmr_check_status(GPTMR_Type *ptr, uint32_t mask)
{
    return (ptr->SR & mask) == mask;
}

static inline void gptmr_clear_status(GPTMR_Type *ptr, uint32_t mask)
{
    ptr->SR |= mask;
}

static inline uint32_t gptmr_get_status(GPTMR_Type *ptr)
{
    return ptr->SR;
}

static inline void gptmr_start_counter(GPTMR_Type *ptr, uint8_t ch_index)
{
    ptr->CHANNEL[ch_index].CR |= GPTMR_CHANNEL_CR_CEN_MASK;
}

static inline void gptmr_stop_counter(GPTMR_Type *ptr, uint8_t ch_index)
{
    ptr->CHANNEL[ch_index].CR &= ~GPTMR_CHANNEL_CR_CEN_MASK;
}

static inline void gptmr_update_cmp(GPTMR_Type *ptr, uint8_t ch_index, uint8_t cmp_index, uint32_t cmp)
{
    ptr->CHANNEL[ch_index].CMP[cmp_index] = GPTMR_CMP_CMP_SET(cmp);
}

hpm_stat_t gptmr_channel_config(GPTMR_Type *ptr,
                         uint8_t ch_index,
                         gptmr_channel_config_t *config,
                         bool enable);

void gptmr_channel_get_default_config(GPTMR_Type *ptr, gptmr_channel_config_t *config);

#ifdef __cplusplus
}
#endif

#endif /* HPM_GPTMR_DRV_H */
