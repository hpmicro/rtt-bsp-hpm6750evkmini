/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_TRGM_DRV_H
#define HPM_TRGM_DRV_H

#include "hpm_common.h"
#include "hpm_trgm_drv.h"
#include "hpm_trgmmux_src.h"

typedef enum trgm_filter_mode {
    trgm_filter_mode_bypass = 0,
    trgm_filter_mode_rapid_change = 1,
    trgm_filter_mode_delay = 2,
    trgm_filter_mode_stable_low = 3,
    trgm_filter_mode_stable_high = 4,
} trgm_filter_mode_t;

typedef enum trgm_output_type {
    trgm_output_same_as_input = 0,
    trgm_output_pulse_at_input_falling_edge = TRGM_TRGOCFG_FEDG2PEN_MASK,
    trgm_output_pulse_at_input_rising_edge = TRGM_TRGOCFG_REDG2PEN_MASK,
    trgm_output_pulse_at_input_both_edge = trgm_output_pulse_at_input_falling_edge
                                    | trgm_output_pulse_at_input_rising_edge,
} trgm_output_type_t;

typedef struct trgm_input_filter {
    bool invert;
    bool sync;
    uint16_t filter_length;
    trgm_filter_mode_t mode;
} trgm_input_filter_t;

typedef struct trgm_output {
    bool invert;
    trgm_output_type_t type;
    uint8_t input;
} trgm_output_t;

#ifdef __cplusplus
extern "C" {
#endif

static inline void trgm_enable_io_output(TRGM_Type *ptr, uint32_t mask)
{
    ptr->GCR |= mask;
}

static inline void trgm_disable_io_output(TRGM_Type *ptr, uint32_t mask)
{
    ptr->GCR &= ~mask;
}

static inline void trgm_input_filter_set_filter_length(TRGM_Type *ptr, uint8_t input, uint16_t length)
{
    ptr->FILTCFG[input] = (ptr->FILTCFG[input] & TRGM_FILTCFG_FILTLEN_MASK)
                        | TRGM_FILTCFG_FILTLEN_SET(length);
}

static inline void trgm_input_filter_enable_sync(TRGM_Type *ptr, uint8_t input, bool enable)
{
    ptr->FILTCFG[input] = (ptr->FILTCFG[input] & TRGM_FILTCFG_SYNCEN_MASK)
                        | TRGM_FILTCFG_SYNCEN_SET(enable);
}

static inline void trgm_input_filter_set_mode(TRGM_Type *ptr, uint8_t input, trgm_filter_mode_t mode)
{
    ptr->FILTCFG[input] = (ptr->FILTCFG[input] & TRGM_FILTCFG_MODE_MASK)
                        | TRGM_FILTCFG_MODE_SET(mode);
}

static inline void trgm_input_filter_invert(TRGM_Type *ptr, uint8_t input, bool invert)
{
    ptr->FILTCFG[input] = (ptr->FILTCFG[input] & TRGM_FILTCFG_OUTINV_MASK)
                        | TRGM_FILTCFG_OUTINV_SET(invert);
}

static inline void trgm_input_filter_config(TRGM_Type *ptr, uint8_t input, trgm_input_filter_t *filter)
{
    ptr->FILTCFG[input] = TRGM_FILTCFG_OUTINV_SET(filter->invert)
                        | TRGM_FILTCFG_MODE_SET(filter->mode)
                        | TRGM_FILTCFG_SYNCEN_SET(filter->sync)
                        | TRGM_FILTCFG_FILTLEN_SET(filter->filter_length);
}

static inline void trgm_output_update_source(TRGM_Type *ptr, uint8_t output, uint8_t source)
{
    ptr->TRGOCFG[output] = (ptr->TRGOCFG[output] & ~TRGM_TRGOCFG_TRIGOSEL_MASK)
                        | TRGM_TRGOCFG_TRIGOSEL_SET(source);
}

static inline void trgm_output_config(TRGM_Type *ptr, uint8_t output, trgm_output_t *config)
{
    ptr->TRGOCFG[output] = TRGM_TRGOCFG_TRIGOSEL_SET(config->input)
                         | TRGM_TRGOCFG_FEDG2PEN_SET(config->type)
                         | TRGM_TRGOCFG_REDG2PEN_SET(config->type);
}

static inline void trgm_dma_request_config(TRGM_Type *ptr, uint8_t dma_out, uint8_t dma_src)
{
    ptr->DMACFG[dma_out] = TRGM_DMACFG_DMASRCSEL_SET(dma_src);
}

#ifdef __cplusplus
}
#endif

#endif /* HPM_TRGM_DRV_H */


