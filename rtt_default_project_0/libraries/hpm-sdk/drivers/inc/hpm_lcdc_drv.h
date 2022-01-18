/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_LCDC_DRV_H
#define HPM_LCDC_DRV_H
#include "hpm_display_common.h"
#include "hpm_soc_feature.h"
#include "hpm_lcdc_regs.h"

#define LCDC_TEST_MODE_DISABLE       (0U)
#define LCDC_TEST_MODE_BACKGROUND    (1U)
#define LCDC_TEST_MODE_COLOR_BAR_COL (2U)
#define LCDC_TEST_MODE_COLOR_BAR_ROW (3U)

enum {
    status_lcdc_no_active_layer_yet = MAKE_STATUS(status_group_lcdc, 1),
    status_lcdc_layer_not_supported = MAKE_STATUS(status_group_lcdc, 2),
};

typedef enum lcdc_line_pattern {
    lcdc_line_pattern_rgb = 0,
    lcdc_line_pattern_rbg,
    lcdc_line_pattern_gbr,
    lcdc_line_pattern_grb,
    lcdc_line_pattern_brg,
    lcdc_line_pattern_bgr,
} lcdc_line_pattern_t;

typedef enum lcdc_display_mode {
    lcdc_display_mode_normal = 0,
    lcdc_display_mode_test_mode_1,
    lcdc_display_mode_test_mode_2,
    lcdc_display_mode_test_mode_3,
} lcdc_display_mode_t;

typedef struct lcdc_control {
    lcdc_line_pattern_t line_pattern;
    lcdc_display_mode_t display_mode;
    bool invert_pixel_data;
    bool invert_pixel_clock;
    bool invert_href;
    bool invert_vsync;
    bool invert_hsync;
} lcdc_control_t;

typedef struct lcdc_xsync_config {
    uint16_t front_porch_pulse;
    uint16_t back_porch_pulse;
    uint16_t pulse_width;
} lcdc_xsync_config_t;

typedef struct lcdc_config {
    uint16_t resolution_x;
    uint16_t resolution_y;
    lcdc_xsync_config_t hsync;
    lcdc_xsync_config_t vsync;
    display_color_32b_t background;
    lcdc_control_t control;
} lcdc_config_t;

typedef enum lcdc_layer_max_bytes_per_transfer {
    lcdc_layer_max_bytes_64 = 0,
    lcdc_layer_max_bytes_128,
    lcdc_layer_max_bytes_256,
    lcdc_layer_max_bytes_512,
    lcdc_layer_max_bytes_1024,
} lcdc_layer_max_bytes_per_transfer_t;

typedef struct lcdc_layer_config {
    uint8_t max_ot;
    display_byteorder_t byteorder;
    display_yuv_format_t yuv;
    display_pixel_format_t pixel_format;
    display_alphablend_option_t alphablend;
    display_yuv2rgb_config_t csc_config;
    lcdc_layer_max_bytes_per_transfer_t max_bytes;
    uint16_t height;
    uint16_t width;
    uint16_t position_x;
    uint16_t position_y;
    uint16_t payload_frequency;
    display_color_32b_t background;
    uint32_t buffer;
} lcdc_layer_config_t;

#ifdef __cplusplus
extern "C" {
#endif

static inline void lcdc_software_reset(LCDC_Type *ptr)
{
    ptr->CTRL |= LCDC_CTRL_SW_RST_MASK;
    ptr->CTRL &= ~LCDC_CTRL_SW_RST_MASK;
}

static inline void lcdc_enable_interrupt(LCDC_Type *ptr, uint32_t interrupt_mask)
{
    ptr->INT_EN |= interrupt_mask;
}

static inline void lcdc_disable_interrupt(LCDC_Type *ptr, uint32_t interrupt_mask)
{
    ptr->INT_EN &= ~interrupt_mask;
}

static inline void lcdc_clear_status(LCDC_Type *ptr, uint32_t mask)
{
    ptr->ST |= mask;
}

static inline bool lcdc_layer_control_shadow_loaded(LCDC_Type *ptr, uint8_t layer_index)
{
    return !(ptr->LAYER[layer_index].LAYCTRL & LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK);
}

static inline uint32_t lcdc_get_dma_status(LCDC_Type *ptr)
{
    return ptr->DMA_ST;
}

static inline bool lcdc_check_dma_status(LCDC_Type *ptr, uint32_t mask)
{
    return ((ptr->DMA_ST & mask) == mask);
}

static inline void lcdc_clear_dma_status(LCDC_Type *ptr, uint32_t mask)
{
    ptr->DMA_ST |= mask;
}

static inline uint32_t lcdc_get_status(LCDC_Type *ptr)
{
    return ptr->ST;
}

static inline bool lcdc_check_status(LCDC_Type *ptr, uint32_t mask)
{
    return (ptr->ST & mask) == mask;
}

static inline void lcdc_layer_set_next_buffer(LCDC_Type *ptr, uint32_t layer_index, uint32_t buffer)
{
    ptr->LAYER[layer_index].START0 = LCDC_LAYER_START0_ADDR0_SET(buffer);
    ptr->LAYER[layer_index].LAYCTRL |= LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK;
}

static inline void lcdc_layer_update_background(LCDC_Type *ptr,
                uint8_t layer_index, display_color_32b_t background)
{
    ptr->LAYER[layer_index].BG_CL = LCDC_LAYER_BG_CL_ARGB_SET(background.u);
    ptr->LAYER[layer_index].LAYCTRL |= LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK;
}

static inline void lcdc_layer_update_position(LCDC_Type *ptr,
        uint8_t layer_index, uint16_t x, uint32_t y)
{
    ptr->LAYER[layer_index].LAYPOS = LCDC_LAYER_LAYPOS_X_SET(x)
        | LCDC_LAYER_LAYPOS_Y_SET(y);
    ptr->LAYER[layer_index].LAYCTRL |= LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK;
}

static inline void lcdc_layer_update_dimension(LCDC_Type *ptr,
        uint8_t layer_index, uint8_t width, uint8_t height)
{
    ptr->LAYER[layer_index].LAYSIZE = LCDC_LAYER_LAYSIZE_WIDTH_SET(width)
        | LCDC_LAYER_LAYSIZE_HEIGHT_SET(height);
    ptr->LAYER[layer_index].LAYCTRL |= LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK;
}

static inline void lcdc_layer_set_region(LCDC_Type *ptr, uint8_t layer_index,
                        uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    ptr->LAYER[layer_index].LAYPOS = LCDC_LAYER_LAYPOS_X_SET(x1)
        | LCDC_LAYER_LAYPOS_Y_SET(y1);
    ptr->LAYER[layer_index].LAYSIZE = LCDC_LAYER_LAYSIZE_WIDTH_SET(x2 - x1 + 1)
        | LCDC_LAYER_LAYSIZE_HEIGHT_SET(y2 - y1 + 1);
    ptr->LAYER[layer_index].LAYCTRL |= LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK;
}

static inline void lcdc_layer_update(LCDC_Type *ptr, uint8_t layer_index)
{
    ptr->LAYER[layer_index].LAYCTRL |= LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK;
}

static inline void lcdc_layer_enable(LCDC_Type *ptr,
                                        uint32_t layer_index, bool enable)
{
    ptr->LAYER[layer_index].LAYCTRL |=
        (ptr->LAYER[layer_index].LAYCTRL & ~(LCDC_LAYER_LAYCTRL_EN_MASK))
        | (enable ? (LCDC_LAYER_LAYCTRL_EN_MASK
                    | LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK) : 0);
}

static inline void lcdc_set_testmode(LCDC_Type *ptr, uint8_t test_mode)
{
    ptr->CTRL = ((ptr->CTRL & ~LCDC_CTRL_DISP_MODE_MASK))
        | LCDC_CTRL_DISP_MODE_SET(test_mode)
        | LCDC_CTRL_DISP_ON_MASK;
}

static inline void lcdc_set_background(LCDC_Type *ptr,
                                       display_color_32b_t color)
{
    ptr->BGND_CL = LCDC_BGND_CL_R_SET(color.r)
        | LCDC_BGND_CL_G_SET(color.g)
        | LCDC_BGND_CL_B_SET(color.b);
}

void lcdc_get_default_layer_config(LCDC_Type *ptr,
                                   lcdc_layer_config_t *layer, display_pixel_format_t pixel_format);

void lcdc_get_default_config(LCDC_Type *ptr, lcdc_config_t *config);

void lcdc_init(LCDC_Type *ptr, lcdc_config_t *config);

hpm_stat_t lcdc_config_layer(LCDC_Type *ptr, uint8_t layer_index,
                       lcdc_layer_config_t *layer, bool enable_layer);

void lcdc_turn_on_display(LCDC_Type *ptr);
void lcdc_turn_off_display(LCDC_Type *ptr);

#ifdef __cplusplus
}
#endif

#endif /* HPM_LCDC_DRV_H */
