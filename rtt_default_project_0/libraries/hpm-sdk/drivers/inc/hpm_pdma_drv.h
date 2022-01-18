/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PDMA_DRV_H
#define HPM_PDMA_DRV_H
#include "hpm_soc_feature.h"
#include "hpm_display_common.h"
#include "hpm_pdma_regs.h"

enum {
    status_pdma_done = status_success,
    status_pdma_error = MAKE_STATUS(status_group_pdma, 1),
    status_pdma_busy = MAKE_STATUS(status_group_pdma, 2),
    status_pdma_idle = MAKE_STATUS(status_group_pdma, 3),
};

typedef enum pdma_plane {
    pdma_plane_src = 0,
    pdma_plane_dst = 1,
    pdma_plane_both,
    pdma_plane_none,
} pdma_plane_t;

typedef enum pdma_flip {
    pdma_flip_none = 0,
    pdma_flip_horizontal = 1 << 0,
    pdma_flip_vertical = 1 << 1,
    pdma_flip_both = pdma_flip_horizontal | pdma_flip_vertical,
} pdma_flip_t;

typedef enum pdma_rotate {
    pdma_rotate_0_degree = 0,
    pdma_rotate_90_degree = 1,
    pdma_rotate_180_degree = 2,
    pdma_rotate_270_degree = 3,
} pdma_rotate_t;

typedef enum pdma_decimation {
    pdma_decimation_by_1 = 0,
    pdma_decimation_by_2 = 1,
    pdma_decimation_by_4 = 2,
    pdma_decimation_by_8 = 3,
} pdma_decimation_t;

typedef enum pdma_blocksize {
    pdma_blocksize_16x16,
    pdma_blocksize_8x8,
} pdma_blocksize_t;

#define PDMA_MAKE_SCALE_SET(integer, fractional)  \
    (((integer) & 0x3) << 12 | ((fractional) & 0xFFF))

typedef struct pdma_plane_config {
    bool swap_byte3_byte1;
    bool use_background_as_clear;
    bool ycbcr_mode;
    bool bypass_colorspace_conversion;
    bool byte_swap;
    display_byteorder_t byteorder;
    pdma_flip_t flip;
    pdma_rotate_t rotate;
    pdma_decimation_t x_dec;
    pdma_decimation_t y_dec;
    display_pixel_format_t pixel_format;
    uint32_t buffer;
    uint32_t background;
    uint32_t colorkey_high;
    uint32_t colorkey_low;
    uint16_t x_scale;
    uint16_t y_scale;
    uint16_t pitch;
    uint16_t x_offset;
    uint16_t y_offset;
    uint16_t width;
    uint16_t height;
} pdma_plane_config_t;


typedef struct pdma_output_config {
    display_alphablend_option_t alphablend;
    display_pixel_format_t pixel_format;
    display_rgb2yuv_config_t rgb2yuv_config;
    uint32_t buffer;
    struct {
        uint16_t x;
        uint16_t y;
        uint16_t width;
        uint16_t height;
    } plane[PDMA_SOC_PS_MAX_COUNT];
    uint16_t width;
    uint16_t height;
    uint16_t pitch;
} pdma_output_config_t;

typedef struct pdma_config {
    display_byteorder_t byteorder;
    pdma_blocksize_t block_size;
    pdma_plane_t enable_plane;
} pdma_config_t;

typedef struct pdma_plane_info {
    uint32_t buffer;
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
    display_pixel_format_t format;
} pdma_plane_info_t;

typedef struct pdma_transform {
    uint8_t x_i; /* 0 ~ 2 */
    uint16_t x_f;
    double scale_y;
} pdma_scale_t;

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Get PDMA_CTRL configuration setting.
 *
 * @param ptr PDMA peripheral base address.
 * @param config Pointer to configuration structure to be restored with the setting values.
 * @param pixel_format PDMA output pixel format.
 */
void pdma_get_default_config(PDMA_Type *ptr, pdma_config_t *config, display_pixel_format_t pixel_format);

/*!
 * @brief Get PDMA plane configuration setting.
 *
 * @param ptr PDMA peripheral base address.
 * @param config Pointer to configuration structure to be restored with the setting values.
 * @param pixel_format PDMA output pixel format.
 */
void pdma_get_default_plane_config(PDMA_Type *ptr, pdma_plane_config_t *config, display_pixel_format_t pixel_format);

/*!
 * @brief Get YUV2RGB_COEF configuration according to plane_src and plane_dst pixel format.
 *
 * Note: The plane_src and plane_dst share one YUV2RGB_COEF, so not support convert one plane YUV422 format
 * and another plane YCbCr422 format at same time.
 *
 * @param ptr PDMA peripheral base address.
 * @param yuv2rgb_coef Pointer to configuration structure to be restored with the setting values.
 * @param plane_src_format The YUV2RGB input source format.
 */
void pdma_get_default_yuv2rgb_coef_config(PDMA_Type *ptr, display_yuv2rgb_coef_t *yuv2rgb_coef, display_pixel_format_t source_format);

/*!
 * @brief Get PDMA output configuration setting.
 *
 * @param ptr PDMA peripheral base address.
 * @param config Pointer to configuration structure to be restored with the setting values.
 * @param pixel_format PDMA output pixel format.
 */
void pdma_get_default_output_config(PDMA_Type *ptr,
                                    pdma_output_config_t *config, display_pixel_format_t pixel_format);

void pdma_enable_irq(PDMA_Type *ptr, uint32_t mask, bool enable);

void pdma_config_output(PDMA_Type *ptr, pdma_output_config_t *config);

/*!
 * @brief Configure PDMA planes.
 *
 * Note: The plane_src and plane_dst share one YUV2RGB_COEF, so not support convert one plane YUV422 format
 * and another plane YCbCr422 format at same time.
 * 
 * @param ptr PDMA peripheral base address.
 * @param plane_src_config Pointer to plane_src configuration structure.
 * @param plane_dst_config Pointer to plan_dst configuration structure.
 * @param yuv2rgb_coef     Pointer to yuv2rgb_coef configuration structure.
 */
void pdma_config_planes(PDMA_Type *ptr, void *plane_src_config, void *plane_dst_config, void *yuv2rgb_coef);

void pdma_init(PDMA_Type *ptr, pdma_config_t *config);

hpm_stat_t pdma_check_status(PDMA_Type *ptr, uint32_t *status);

hpm_stat_t pdma_flip_plane(PDMA_Type *ptr, pdma_plane_info_t *in,
                     pdma_plane_info_t *out, pdma_flip_t flip,
                     bool wait, uint32_t *status);

hpm_stat_t pdma_rotate_plane(PDMA_Type *ptr, pdma_plane_info_t *in,
                     pdma_plane_info_t *out, pdma_rotate_t rotate,
                     bool wait, uint32_t *status);

hpm_stat_t pdma_blend_planes(PDMA_Type *ptr,
                             pdma_plane_info_t *in1,
                             pdma_plane_info_t *in2,
                             pdma_plane_info_t *out,
                             display_alphablend_option_t *alphablend,
                             bool wait, uint32_t *status);

hpm_stat_t pdma_fill_color(PDMA_Type *ptr, uint32_t dst, uint32_t dst_width,
                           uint32_t width, uint32_t height,
                           uint32_t color, uint8_t alpha,
                           display_pixel_format_t format,
                           bool wait, uint32_t *status);

hpm_stat_t pdma_flip_rotate(PDMA_Type *ptr, uint32_t dst, uint32_t dst_width,
                    uint32_t src, uint32_t src_width, uint32_t x, uint32_t y,
                    uint32_t width, uint32_t height,
                    pdma_flip_t flip, pdma_rotate_t rotate, uint8_t alpha,
                    display_pixel_format_t format,
                    bool wait, uint32_t *status);

hpm_stat_t pdma_blit(PDMA_Type *ptr,
                     uint32_t dst, uint32_t dst_width,
                     uint32_t src, uint32_t src_width,
                     uint32_t x, uint32_t y, uint32_t width, uint32_t height,
                     uint8_t alpha,
                     display_pixel_format_t format,
                     bool wait, uint32_t *status);

hpm_stat_t pdma_scale(PDMA_Type *ptr,
                     uint32_t dst, uint32_t dst_width,
                     uint32_t src, uint32_t src_width,
                     uint32_t x, uint32_t y, uint32_t width, uint32_t height,
                     uint32_t target_width, uint32_t target_height,
                     uint8_t alpha,
                     display_pixel_format_t format,
                     bool wait, uint32_t *status);

void pdma_set_block_size(PDMA_Type *ptr, pdma_blocksize_t size);

void pdma_stop(PDMA_Type *ptr);

static inline uint32_t pdma_get_status(PDMA_Type *ptr)
{
    return ptr->STAT;
}

static inline void pdma_start(PDMA_Type *ptr)
{
    ptr->CTRL |= PDMA_CTRL_PDMA_EN_MASK;
    __asm volatile ("" : : "r" (ptr->CTRL));
}

static inline void pdma_software_reset(PDMA_Type *ptr)
{
    ptr->CTRL |= PDMA_CTRL_PDMA_SFTRST_MASK;
    ptr->CTRL &= ~(PDMA_CTRL_PDMA_SFTRST_MASK);
    __asm volatile ("" : : "r" (ptr->CTRL));
}

static inline void pdma_set_plane_colorkey(PDMA_Type *ptr,
                                           uint8_t plane_index,
                                           uint32_t key_high,
                                           uint32_t key_low)
{
    ptr->PS[plane_index].CLRKEY_LOW = PDMA_PS_CLRKEY_LOW_LIMIT_SET(key_low);
    ptr->PS[plane_index].CLRKEY_HIGH = PDMA_PS_CLRKEY_HIGH_LIMIT_SET(key_high);
}


#ifdef __cplusplus
}
#endif
#endif /* HPM_PDMA_DRV_H */
