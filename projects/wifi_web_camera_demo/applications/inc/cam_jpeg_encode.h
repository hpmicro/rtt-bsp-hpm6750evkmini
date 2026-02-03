/*
 * Copyright (c) 2023 hpmicro
 *
 * Change Logs:
 * Date         Author          Notes
 * 2023-10-17   HPMicro     first version
 *
 */
#ifndef __CAM_JPEG_ENCODE_H
#define __CAM_JPEG_ENCODE_H

/* image resolution */
#if defined(CONFIG_CAMERA_OV5640) && (CONFIG_CAMERA_OV5640 == 1)
#define IMAGE_WIDTH      800
#define IMAGE_HEIGHT     480
#elif defined(CONFIG_CAMERA_OV7725) && (CONFIG_CAMERA_OV7725 == 1)
#define IMAGE_WIDTH      320
#define IMAGE_HEIGHT     240
#endif
int jepg_cam_init(void);
rt_base_t get_cam_jpeg_data(uint8_t *data, uint32_t *size);

#endif