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
#define IMAGE_WIDTH      800
#define IMAGE_HEIGHT     480
int jepg_cam_init(void);
rt_base_t get_cam_jpeg_data(uint8_t *data, uint32_t *size);

#endif
