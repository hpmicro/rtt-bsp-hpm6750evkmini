/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_VAD_DRV_H
#define HPM_VAD_DRV_H

#include "hpm_common.h"
#include "hpm_vad_regs.h"

#define VAD_EVENT_VAD                   (1U << 7)
#define VAD_EVENT_FIFO_DATA_AVAILABLE   (1U << 6)
#define VAD_EVENT_MEMBUF_EMPTY          (1U << 5)
#define VAD_EVENT_FIFO_OVERFLOW         (1U << 4)
#define VAD_EVENT_IIR_OVERLOAD          (1U << 3)
#define VAD_EVENT_IIR_OVERFLOW          (1U << 2)
#define VAD_EVENT_CIC_OVERLOAD_ERROR    (1U << 1)
#define VAD_EVENT_CIC_STA_ERROR         (1U << 0)

typedef struct vad_config {
    bool enable_buffer;
    bool enable_dma_request;
    bool enable_pdm_clock_out;
    bool enable_two_channels;
    uint8_t capture_delay;
    uint8_t pdm_half_div;
    uint8_t fifo_threshold;
    uint8_t post_scale;
    bool channel_polarity_high[2];
} vad_config_t;

#ifdef __cplusplus
extern "C" {
#endif

static inline void vad_set_capture_delay(VAD_Type *ptr, uint8_t delay)
{
    ptr->CTRL = (ptr->CTRL & ~VAD_CTRL_CAPT_DLY_MASK)
        | VAD_CTRL_CAPT_DLY_SET(delay);
}

static inline void vad_set_pdm_clock_half_div(VAD_Type *ptr, uint8_t div)
{
    ptr->CTRL = (ptr->CTRL & ~VAD_CTRL_PDM_CLK_HFDIV_MASK)
        | VAD_CTRL_PDM_CLK_HFDIV_SET(div);
}

static inline void vad_disable_dma_request(VAD_Type *ptr)
{
    ptr->CTRL &= ~VAD_CTRL_DMA_EN_MASK;
}

static inline void vad_enable_dma_request(VAD_Type *ptr)
{
    ptr->CTRL |= VAD_CTRL_DMA_EN_MASK;
}

static inline void vad_enable_irq(VAD_Type *ptr, uint32_t irq_mask)
{
    ptr->CTRL |= irq_mask;
}

static inline void vad_disable_irq(VAD_Type *ptr, uint32_t irq_mask)
{
    ptr->CTRL &= ~irq_mask;
}

static inline void vad_disable_buffer(VAD_Type *ptr)
{
    ptr->CTRL |= VAD_CTRL_MEMBUF_DISABLE_MASK;
}

static inline void vad_enable_buffer(VAD_Type *ptr)
{
    ptr->CTRL &= ~VAD_CTRL_MEMBUF_DISABLE_MASK;
}

static inline void vad_set_fifo_threshold(VAD_Type *ptr, uint8_t threshhold)
{
    ptr->CTRL = (ptr->CTRL & ~(VAD_CTRL_FIFO_THRSH_MASK))
        | VAD_CTRL_FIFO_THRSH_SET(threshhold);
}

static inline void vad_enable_pdm_clock_out(VAD_Type *ptr)
{
    ptr->CTRL |= VAD_CTRL_PDM_CLK_OE_MASK;
}

static inline void vad_disable_pdm_clock_out(VAD_Type *ptr)
{
    ptr->CTRL &= ~VAD_CTRL_PDM_CLK_OE_MASK;
}

static inline void vad_set_pdm_clock_capture_level(VAD_Type *ptr, uint8_t level)
{
    ptr->CTRL = (ptr->CTRL & ~VAD_CTRL_CH_POL_MASK)
        | VAD_CTRL_CH_POL_SET(level);
}

static inline void vad_set_channel_number(VAD_Type *ptr, bool two_channels)
{
    ptr->CTRL = (ptr->CTRL & ~VAD_CTRL_CHNUM_MASK)
        | (two_channels ? VAD_CTRL_CHNUM_MASK : 0);
}

static inline uint32_t vad_get_status(VAD_Type *ptr)
{
    return ptr->ST;
}

static inline void vad_clear_status(VAD_Type *ptr, uint32_t mask)
{
    ptr->ST |= mask;
}

static inline uint32_t vad_get_data(VAD_Type *ptr)
{
    return ptr->OFIFO;
}

static inline void vad_software_reset(VAD_Type *ptr)
{
    ptr->RUN |= VAD_RUN_SFTRST_MASK;
    ptr->RUN &= ~VAD_RUN_SFTRST_MASK;
}

static inline void vad_start(VAD_Type *ptr)
{
    ptr->RUN |= VAD_RUN_VAD_EN_MASK;
}

static inline void vad_stop(VAD_Type *ptr)
{
    ptr->RUN &= ~VAD_RUN_VAD_EN_MASK;
}

static inline bool vad_is_running(VAD_Type *ptr)
{
    return ptr->RUN & VAD_RUN_VAD_EN_MASK;
}

static inline void vad_enable_fifo(VAD_Type *ptr)
{
    ptr->OFIFO_CTRL |= VAD_OFIFO_CTRL_EN_MASK;
}

static inline void vad_disable_fifo(VAD_Type *ptr)
{
    ptr->OFIFO_CTRL &= ~VAD_OFIFO_CTRL_EN_MASK;
}

static inline uint32_t vad_get_coef_value(VAD_Type *ptr, uint32_t index)
{
    return ptr->COEF[index];
}

static inline uint32_t vad_get_cic_config(VAD_Type *ptr)
{
    return ptr->CIC_CFG;
}

static inline void vad_set_post_scale(VAD_Type *ptr, uint8_t post_scale)
{
    ptr->CIC_CFG = VAD_CIC_CFG_POST_SCALE_SET(post_scale);
}

static inline void vad_set_amplify(VAD_Type *ptr, uint16_t high, uint16_t low)
{
    ptr->DEC_CTRL2 = VAD_DEC_CTRL2_AMP_HIGH_SET(high)
        | VAD_DEC_CTRL2_AMP_LOW_SET(low);
}

void vad_get_default_config(VAD_Type *ptr, vad_config_t *config);

void vad_init(VAD_Type *ptr, vad_config_t *config);

void vad_reset(VAD_Type *ptr);

#ifdef __cplusplus
}
#endif

#endif /* HPM_VAD_DRV_H */
