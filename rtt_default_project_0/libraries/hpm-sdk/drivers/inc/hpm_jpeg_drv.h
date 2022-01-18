/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_JPEG_DRV_H
#define HPM_JPEG_DRV_H

#include "hpm_common.h"
#include "hpm_jpeg_regs.h"

#define JPEG_EVENT_BUSY             JPEG_STAT_BUSY_MASK
#define JPEG_EVENT_OUT_DMA_FINISH   JPEG_STAT_OUT_DMA_TRANSFER_DONE_MASK
#define JPEG_EVENT_IN_DMA_FINISH    JPEG_STAT_IN_DMA_TRANSFER_DONE_MASK
#define JPEG_EVENT_ERROR            (JPEG_STAT_RESTART_MARKER_ERROR_MASK | (0xF << 7))

/* byte order in a word */
#define JPEG_BYTE_ORDER_3210        (0U) /* no order change, {A3, A2, A1, A0} */
#define JPEG_BYTE_ORDER_2301        (1U)
#define JPEG_BYTE_ORDER_1032        (2U)
#define JPEG_BYTE_ORDER_0123        (2U)

#define JPEG_PIXEL_FORMAT_AS_ORIGIN (0U)
#define JPEG_PIXEL_FORMAT_ARGB8888  (1U)
#define JPEG_PIXEL_FORMAT_RGB565    (2U)
#define JPEG_PIXEL_FORMAT_YUV422H1P (3U)

#define JPEG_SUPPORTED_FORMAT_420   (0U)
#define JPEG_SUPPORTED_FORMAT_422H  (1U)
#define JPEG_SUPPORTED_FORMAT_422V  (2U)
#define JPEG_SUPPORTED_FORMAT_444   (3U)
#define JPEG_SUPPORTED_FORMAT_400   (4U)

typedef struct {
    uint8_t hy:2;
    uint8_t vy:2;
    uint8_t hc:2;
    uint8_t vc:2;
} jpeg_sampling_t;

/*
 * Value format:
 *
 * bit:  27           23           3           0
 * name: |    WIDTH   |   ELEMENT  |    TYPE   |
 *       |   IN BYTE  |    COUNT   |           |
 */
typedef enum jpeg_table {
    jpeg_table_qmem =     0x201002,
    jpeg_table_huffenc =  0x201803,
    jpeg_table_huffmin =  0x400104,
    jpeg_table_huffbase = 0x200405,
    jpeg_table_huffsymb = 0x101506,
} jpeg_table_t;

typedef struct {
    uint8_t jpeg_format;            /* supported jpeg format */
    uint8_t in_pixel_format;        /* input pixel format */
    uint8_t out_pixel_format;       /* output pixel format */
    uint8_t byte_order;             /* byte order */
    bool enable_csc;                /* enable color space covertion */
    bool enable_ycbcr;              /* enable YCbCr or YUV */
    uint16_t width_in_pixel;
    uint16_t height_in_pixel;
    uint32_t in_buffer;             /* input buffer */
    uint32_t out_buffer;            /* output buffer */
} jpeg_job_config_t;

#ifdef __cplusplus
extern "C" {
#endif

static inline void jpeg_disable(JPEG_Type *ptr)
{
    ptr->CFG &= ~JPEG_CFG_JPEG_EN_MASK;
}

static inline void jpeg_enable(JPEG_Type *ptr)
{
    ptr->CFG |= JPEG_CFG_JPEG_EN_MASK;
}

static inline void jpeg_stop(JPEG_Type *ptr)
{
    ptr->CFG &= ~JPEG_CFG_START_MASK;
}

static inline void jpeg_start(JPEG_Type *ptr)
{
    ptr->CFG |= JPEG_CFG_START_MASK;
}

static inline uint32_t jpeg_get_status(JPEG_Type *ptr)
{
    return ptr->STAT;
}

static inline void jpeg_clear_status(JPEG_Type *ptr, uint32_t mask)
{
    ptr->STAT |= mask;
}

static inline uint32_t jpeg_get_encoded_length(JPEG_Type *ptr)
{
    return JPEG_OUTDMACNT_VAL_GET(ptr->OUTDMACNT);
}

static inline void jpeg_software_reset(JPEG_Type *ptr)
{
    ptr->CFG |= JPEG_CFG_JPEG_SFTRST_MASK;
    ptr->CFG &= ~JPEG_CFG_JPEG_SFTRST_MASK;
}

/*
 * reset jpeg controller
 */
void jpeg_reset(JPEG_Type *ptr);

void jpeg_enable_irq(JPEG_Type *ptr, uint32_t mask);
void jpeg_disable_irq(JPEG_Type *ptr, uint32_t mask);

void jpeg_init(JPEG_Type *ptr);

/*
 * fill tables for jpeg controller
 */
hpm_stat_t jpeg_fill_table(JPEG_Type *ptr, jpeg_table_t table, uint8_t *data, uint32_t count);

/*
 * it will start corresponding, and the process status needs to be checked by
 * querying JPEG_EVENT
 */ 
hpm_stat_t jpeg_start_decode(JPEG_Type *ptr, jpeg_job_config_t *config, uint32_t length);
hpm_stat_t jpeg_start_encode(JPEG_Type *ptr, jpeg_job_config_t *config);

#ifdef __cplusplus
}
#endif
#endif /* HPM_JPEG_DRV_H */
