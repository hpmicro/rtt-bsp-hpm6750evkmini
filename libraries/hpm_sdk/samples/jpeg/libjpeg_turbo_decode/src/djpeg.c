/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
/*---------------------------------------------------------------------*
 * Includes
 *---------------------------------------------------------------------
 */
#include "board.h"
#include "hpm_lcdc_drv.h"
#include "hpm_l1c_drv.h"
#include "hpm_sysctl_drv.h"
#include "jpeglib.h"
/*--------------------------------------------------------------------*
 * Macro Definitions
 *---------------------------------------------------------------------
 */
#if defined  SD_FATFS_MODE
    #include "sd_fatfs.h"
#elif defined TINYUSB_HOST_MODE
    #include "msc_app.h"
#endif

/*LCD Definitions*/
#ifndef LCD
#define LCD BOARD_LCD_BASE
#define LCD_IRQ BOARD_LCD_IRQ
#endif

/*Pixel format of LCD display*/
#define PIXEL_FORMAT display_pixel_format_rgb565
/*rgb565 data buff length*/
#define RGBBUFFLEN 200000
/*JPG data buff length*/
/*---------------------------------------------------------------------*
 * Define variables
 *---------------------------------------------------------------------
 */
/*rgb565 data buff*/
__attribute__((section(".framebuffer"))) uint8_t rgb565buff[RGBBUFFLEN] = {0};
/*JPG file data buff*/
uint8_t filebuff[FILEBUFFLEN];
/*JPG data buff size*/
int32_t jpg_size;

/*---------------------------------------------------------------------*
 * Display picture data on LCD
 *---------------------------------------------------------------------
 */
void lcdc_display_picture(int32_t rgb_width, int32_t rgb_heihgt, int32_t rgb_size)
{
    lcdc_config_t config = {0};
    lcdc_layer_config_t layer;

    /*LCD default parameter settings*/
    lcdc_get_default_config(LCD, &config);
    config.resolution_x = BOARD_LCD_WIDTH;
    config.resolution_y = BOARD_LCD_HEIGHT;
    lcdc_init(LCD, &config);

    /*Rgb565 data parameter configuration*/
    if (l1c_dc_is_enabled()) {
        l1c_dc_writeback((uint32_t)rgb565buff, rgb_size);
    }
    layer.buffer = core_local_mem_to_sys_address(BOARD_RUNNING_CORE, (uint32_t)rgb565buff);
    layer.width = rgb_width;
    layer.height = rgb_heihgt;
    lcdc_get_default_layer_config(LCD, &layer, PIXEL_FORMAT);

    /*LCD layer parameter configuration*/
    layer.position_x = 0;
    layer.position_y = 0;
    layer.pixel_format = PIXEL_FORMAT;
    layer.alphablend.src_alpha = 0xFF;
    layer.alphablend.dst_alpha = 0xFF;
    layer.alphablend.src_alpha_op = display_alpha_op_invalid;
    layer.alphablend.dst_alpha_op = display_alpha_op_invalid;
    layer.background.u = 0;
    layer.alphablend.mode = display_alphablend_mode_src_over;
    layer.yuv = 0;
    layer.csc_config.enable = false;
    lcdc_config_layer(LCD, 0, &layer, true);

    /*LCD display function enable*/
    lcdc_turn_on_display(LCD);
}

/*---------------------------------------------------------------------*
 * libjpeg-turbo  -Convert JPG data to bgr888 data
 *---------------------------------------------------------------------
 */
void jpeg_jpgmem_to_bgr888(const uint8_t *src, int32_t srcLen, uint8_t **_dst, int32_t *dstLen, int32_t *width, int32_t *height, int32_t *depth)
{
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    /* Initialize the JPEG decompression object with default error handling. */
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    /* Specify data source for decompression */
    jpeg_mem_src(&cinfo, src, srcLen);
    /* Read file header, set default decompression parameters */
    jpeg_read_header(&cinfo, TRUE);

    /* Start decompressor */
    jpeg_start_decompress(&cinfo);
    (*width) = cinfo.output_width;
    (*height) = cinfo.output_height;
    (*depth) = cinfo.num_components;
    (*dstLen) = (*width) * (*height) * (*depth);
    uint8_t *dst = (uint8_t *)malloc(*dstLen);

    /* Process data */
    JSAMPROW row_pointer[1];
    while (cinfo.output_scanline < cinfo.output_height) {
        row_pointer[0] = &dst[cinfo.output_scanline * cinfo.image_width * cinfo.num_components];
        jpeg_read_scanlines(&cinfo, row_pointer, 1);
    }
    /* Finish decompression*/
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    *_dst = dst;
}

/*---------------------------------------------------------------------*
 * Convert rgb888 data to rgb565 data
 *---------------------------------------------------------------------
 */
uint16_t jpeg_rgb888_to_rgb565(uint8_t red, uint8_t green, uint8_t blue)
{
    /*RGB24 bit data is combined into 16 bit data*/
    uint16_t B = (blue >> 3) & 0x001F;
    uint16_t G = ((green >> 2) << 5) & 0x07E0;
    uint16_t R = ((red >> 3) << 11) & 0xF800;

    return (uint16_t)(R | G | B);
}

/*---------------------------------------------------------------------*
 * Convert bgr888 data to rgb565 data
 *---------------------------------------------------------------------
 */
void jpeg_bgr888_to_rgb565(uint8_t *bgr, int32_t *bsize, int32_t bit)
{
    int32_t fsize = (*bsize);
    int32_t fnsi = 0;

    /*Blue data bytes and red data bytes are exchanged*/
    for (int32_t i = 0; i < fsize; i += bit / 8) {
        uint8_t b = bgr[i];
        bgr[i] = bgr[i + 2];
        bgr[i + 2] = b;
    }

    /*Convert rgb888 data to rgb565 data */
    for (uint64_t iz = 0, j = 0; iz < fsize; iz += 3, j += 2) {
        uint16_t color565 = jpeg_rgb888_to_rgb565(bgr[iz], bgr[iz + 1], bgr[iz + 2]);
        memcpy(bgr + j, &color565, 2);
        fnsi += 2;
    }
    (*bsize) = fnsi;
}

/*---------------------------------------------------------------------*
 * Libjpeg conversion to convert JPG data into rgb565 data
 *---------------------------------------------------------------------
 */
void jpeg_convert_data(int32_t fileLen, int32_t *size, int32_t *width, int32_t *height)
{
    int32_t component;
    uint8_t *djpegbuff = NULL;

    /* jpeg  -Convert JPG data to bgr888 data */
    jpeg_jpgmem_to_bgr888(filebuff, fileLen, &djpegbuff, size, width, height, &component);
    /*bgr888 data conversion to rgb565*/
    jpeg_bgr888_to_rgb565(djpegbuff, size, 24);
    /*Store data to buff*/
    memcpy(rgb565buff, &djpegbuff[0], *size);
    /*Free memory*/
    free(djpegbuff);
    /*Complete JPG decoding*/
}

/*---------------------------------------------------------------------*
 * MAIN.C
 *---------------------------------------------------------------------
 */
int main(void)
{
    int32_t rgbwidth, rgbheight, rgbsize;

    /*System initialization*/
    board_init();

    do {
#if defined SD_FATFS_MODE
        /*Read picture data by SD card*/
        printf("Read picture data by SD card\n");
        sdfatfs_task();
#elif defined TINYUSB_HOST_MODE
        /*Reading picture data in tinyusb mode*/
        printf("Read picture data by usb-mode\n");
        tinyusb_task();
#endif
    } while (!jpg_size);

    /*Libjpeg conversion to convert JPG data into rgb565 data*/
    jpeg_convert_data(jpg_size, &rgbsize, &rgbwidth, &rgbheight);
    printf("Libjpeg-turbo decode completed\n");

    /*LCD initialization*/
    board_init_lcd();
    /*Display picture data on LCD*/
    lcdc_display_picture(rgbwidth, rgbheight, rgbsize);

    while (1) {
    };
}