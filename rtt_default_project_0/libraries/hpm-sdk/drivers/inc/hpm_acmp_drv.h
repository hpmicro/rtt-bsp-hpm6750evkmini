/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_ACMP_DRV_H
#define HPM_ACMP_DRV_H

#include "hpm_common.h"
#include "hpm_acmp_regs.h"

#define ACMP_HYST_LEVEL_0 (0U)
#define ACMP_HYST_LEVEL_1 (1U)
#define ACMP_HYST_LEVEL_2 (2U)
#define ACMP_HYST_LEVEL_3 (3U)

#define ACMP_INPUT_DAC_OUT (0U)
#define ACMP_INPUT_ANALOG_1 (1U)
#define ACMP_INPUT_ANALOG_2 (2U)
#define ACMP_INPUT_ANALOG_3 (3U)
#define ACMP_INPUT_ANALOG_4 (4U)
#define ACMP_INPUT_ANALOG_5 (5U)
#define ACMP_INPUT_ANALOG_6 (6U)
#define ACMP_INPUT_ANALOG_7 (7U)

#define ACMP_FILTER_MODE_BYPASS (0U)
#define ACMP_FILTER_MODE_CHANGE_IMMEDIATELY (4U)
#define ACMP_FILTER_MODE_CHANGE_AFTER_FILTER (5U)
#define ACMP_FILTER_MODE_STABLE_LOW (6U)
#define ACMP_FILTER_MODE_STABLE_HIGH (7U)

#define ACMP_EVENT_RISING_EDGE  (1U)
#define ACMP_EVENT_FALLING_EDGE (2U)

typedef struct acmp_channel_config {
    uint8_t plus_input;
    uint8_t minus_input;
    uint8_t filter_mode;
    uint8_t hyst_level;
    bool enable_cmp_output;
    bool enable_window_mode;
    bool invert_output;
    bool enable_clock_sync;
    bool bypass_filter;
    bool enable_dac;
    bool enable_hpmode;
    uint16_t filter_length; /* ACMP output digital filter length in ACMP clock cycle */
} acmp_channel_config_t;

#ifdef __cplusplus
extern "C" {
#endif

static inline void acmp_channel_config_dac(ACMP_Type *ptr, uint8_t ch, uint32_t value)
{
    ptr->CHANNEL[ch].DACCFG = ACMP_CHANNEL_DACCFG_DACCFG_SET(value);
}

static inline void acmp_channel_clear_status(ACMP_Type *ptr, uint8_t ch, uint32_t mask)
{
    ptr->CHANNEL[ch].SR = mask;
}

static inline uint32_t acmp_channel_get_status(ACMP_Type *ptr, uint8_t ch)
{
    return ptr->CHANNEL[ch].SR;
}

static inline void acmp_channel_dma_request_enable(ACMP_Type *ptr, uint8_t ch,
                                            uint32_t mask, bool enable)
{
    ptr->CHANNEL[ch].DMAEN = (ptr->CHANNEL[ch].DMAEN & ~mask)
                        | (enable ? mask : 0);
}

static inline void acmp_channel_enable_irq(ACMP_Type *ptr, uint8_t ch,
                                            uint32_t mask, bool enable)
{
    ptr->CHANNEL[ch].IRQEN = (ptr->CHANNEL[ch].IRQEN & ~mask)
                        | (enable ? mask : 0);
}

static inline void acmp_channel_enable_dac(ACMP_Type *ptr, uint8_t ch, bool enable)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_DACEN_MASK)
                        | ACMP_CHANNEL_CFG_DACEN_SET(enable);
}

static inline void acmp_channel_enable_hpmode(ACMP_Type *ptr, uint8_t ch, bool enable)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_HPMODE_MASK)
                        | ACMP_CHANNEL_CFG_HPMODE_SET(enable);
}

static inline void acmp_channel_set_hyst(ACMP_Type *ptr, uint8_t ch, uint8_t level)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_HYST_MASK)
                        | ACMP_CHANNEL_CFG_HYST_SET(level);
}

static inline void acmp_channel_enable_cmp(ACMP_Type *ptr, uint8_t ch, bool enable)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_CMPEN_MASK)
                        | ACMP_CHANNEL_CFG_CMPEN_SET(enable);
}

static inline void acmp_channel_enable_cmp_output(ACMP_Type *ptr, uint8_t ch, bool enable)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_CMPOEN_MASK)
                        | ACMP_CHANNEL_CFG_CMPOEN_SET(enable);
}

static inline void acmp_channel_cmp_output_bypass_filter(ACMP_Type *ptr, uint8_t ch, bool enable)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_FLTBYPS_MASK)
                        | ACMP_CHANNEL_CFG_FLTBYPS_SET(!enable);
}

static inline void acmp_channel_enable_cmp_window_mode(ACMP_Type *ptr, uint8_t ch, bool enable)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_WINEN_MASK)
                        | ACMP_CHANNEL_CFG_WINEN_SET(enable);
}

static inline void acmp_channel_invert_output(ACMP_Type *ptr, uint8_t ch, bool enable)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_OPOL_MASK)
                        | ACMP_CHANNEL_CFG_OPOL_SET(enable);
}

static inline void acmp_channel_set_filter_mode(ACMP_Type *ptr, uint8_t ch, uint8_t filter)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_FLTMODE_MASK)
                        | ACMP_CHANNEL_CFG_FLTMODE_SET(filter);
}

static inline void acmp_channel_enable_sync(ACMP_Type *ptr, uint8_t ch, bool enable)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_SYNCEN_MASK)
                        | ACMP_CHANNEL_CFG_SYNCEN_SET(enable);
}

static inline void acmp_channel_set_filter_length(ACMP_Type *ptr, uint8_t ch, uint16_t filter_length)
{
    ptr->CHANNEL[ch].CFG = (ptr->CHANNEL[ch].CFG & ~ACMP_CHANNEL_CFG_FLTLEN_MASK)
                        | ACMP_CHANNEL_CFG_FLTLEN_SET(filter_length);
}

hpm_stat_t acmp_channel_config(ACMP_Type *ptr, uint8_t ch, acmp_channel_config_t *config, bool enable);

void acmp_channel_get_default_config(ACMP_Type *ptr, acmp_channel_config_t *config);
#ifdef __cplusplus
}
#endif

#endif /* HPM_ACMP_DRV_H */
