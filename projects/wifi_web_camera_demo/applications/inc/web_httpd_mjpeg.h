/*
 * Copyright (c) 2023 hpmicro
 *
 * Change Logs:
 * Date         Author          Notes
 * 2023-10-17   HPMicro     first version
 *
 */

#ifndef __WEB_HTTPD_MJPEG_H
#define __WEB_HTTPD_MJPEG_H

#define   HTTP_VIDEO_STOP              (0x00)
#define   HTTP_VIDEO_START             (0x01)
#define   WEB_SERVER_PORT                 (80)
typedef enum {
    http_ok,
    cam_timeout,
    http_fail,
}http_sta;

void http_mjpeg_server(void *parameter);

#endif
