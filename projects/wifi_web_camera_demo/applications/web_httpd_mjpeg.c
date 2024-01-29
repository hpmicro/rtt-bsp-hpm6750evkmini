/*
 * Copyright (c) 2023 hpmicro
 *
 * Change Logs:
 * Date         Author          Notes
 * 2023-10-17   HPMicro     first version
 *
 */

#include <string.h>
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <sys/socket.h>
#include <lwip/opt.h>
#include <netdev.h>
#include <netdb.h>
#include "board.h"
#include "hpm_l1c_drv.h"
#include "web_httpd_mjpeg.h"
#include "cam_jpeg_encode.h"
#include "web_icon.h"

#define   NETIF_NAME         "w0"

#if defined(CONFIG_CAMERA_OV5640) && (CONFIG_CAMERA_OV5640 == 1)
#define   WEB_CAMERA_NAE     "ov5640"
#elif defined(CONFIG_CAMERA_OV7725) && (CONFIG_CAMERA_OV7725 == 1)
#define   WEB_CAMERA_NAE     "ov7725"
#else
#define   WEB_CAMERA_NAE     "NULL"
#endif

const static char http_html_hdr[] =
    "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";

// __attribute__((section(".noncacheable")))
char indexdata[] = "<html> \
    <head>\
    <meta http-equiv=\"Content-Type\" content=\"text/html; charset=gb2312\" />\
    <body> \
    <h1 align=center style='text-align:center'>HPMicro webcam</h1> \
    <h2 align=center style='text-align:center'>RTOS:RT-Thread</h2> \
    <h2 align=center style='text-align:center'>Board:%s</h2> \
    <h2 align=center style='text-align:center'>Sensor:%s</h2> \
    <h2 align=center style='text-align:center'>Resolution:%d*%d</h2> \
    <img style='margin:0 auto;display:block;' src=\"http://%s/?%s=mjpeg\"> \
    </body> \
    </html>";

char buffer[2048]; 
rt_uint8_t video_flag = HTTP_VIDEO_STOP;
rt_uint8_t pic_num = 1;
rt_uint8_t newframe = 0;
int stream_connected;
ATTR_PLACE_AT_NONCACHEABLE rt_uint8_t jpeg_data[256 * 1024];
ATTR_PLACE_AT_NONCACHEABLE char index_data_format[2048];

void http_send_icon(int client) 
{
    int frame_size = 0;
    uint16_t haed_len = 0;
    rt_sprintf(buffer,
            "HTTP/1.1 200 OK\r\n"
            "Server: lwIP/1.3.1 (http://savannah.nongnu.org/projects/lwip)\r\n"
            "Content-type: image/x-icon\r\n\r\n"); //

    frame_size = sizeof(icon_data);
    haed_len = rt_strlen(buffer);
    rt_memcpy(&buffer[haed_len], (char *)icon_data, frame_size);
    frame_size = haed_len + frame_size; //
    send(client, buffer, frame_size, 0);
    closesocket(client);
}

http_sta http_streamer_start(int client, rt_uint8_t count) 
{
    int frame_size = 0;
    uint16_t haed_len = 0;
    rt_sprintf(buffer,
               "HTTP/1.1 200 OK\r\n"
               "Server: HPMicro\r\n"
               "Content-Type: multipart/x-mixed-replace;boundary=%s\r\n"
               "Cache-Control: no-cache\r\n"
               "Pragma: no-cache\r\n\r\n",
               BOARD_NAME);
    haed_len = rt_strlen(buffer);
    if (send(client, buffer, haed_len, 0) == -1) {
        return http_fail;
    }
    return http_ok;
}

http_sta http_send_streamer(int client) 
{
    int32_t frame_size = 0, send_sta;
    uint16_t haed_len = 0;
    uint32_t aligned_len = 0;

    if (get_cam_jpeg_data(jpeg_data, &frame_size) == RT_FALSE) {
        return cam_timeout;
    }
    if (frame_size <= 0) {
        return cam_timeout;
    }
    if (l1c_dc_is_enabled()) {
        aligned_len = (frame_size + HPM_L1C_CACHELINE_SIZE - 1U) & ~(HPM_L1C_CACHELINE_SIZE - 1U);
        l1c_dc_flush((uint32_t)jpeg_data, aligned_len);
    }
    rt_sprintf(buffer,
            "\r\n--%s\r\n"
            "Content-Type: image/jpeg\r\n"
            "Content-Length: %d\r\n\r\n",
            BOARD_NAME, frame_size);
    haed_len = rt_strlen(buffer);
    if (send(client, buffer, haed_len, 0) == -1) 
    {
        rt_kprintf("\r\nerror code:0x01\r\n");
        return http_fail;
    }
    if (send(client, jpeg_data, frame_size, 0) == -1) 
    {
        rt_kprintf("\r\nerror code:0x01\r\n");
        return http_fail;
    }
    return http_ok;
}

void http_mjpeg_send(void *parameter) 
{
    rt_uint8_t i = 0;
    void *msg;
    while (1) {
        if (HTTP_VIDEO_START == video_flag) {
            if (http_send_streamer(stream_connected) == http_fail) // jpeg
            {
                video_flag = HTTP_VIDEO_STOP;
            }
        }
        rt_thread_mdelay(20);
    }
}

void http_mjpeg_server(void *parameter) 
{
    char *uri;
    char *recv_data;
    uint32_t sin_size;
    int sock, bytes_received;
    struct hostent *host;
    struct sockaddr_in server_addr, client_addr;
    rt_base_t stop = 0;
    struct netdev *web_netdev = RT_NULL;
    char *ip_addr_str = RT_NULL;
    uint8_t http_buf[128];
    jepg_cam_init();
    recv_data = rt_malloc(1024);
    if (recv_data == NULL) {
        rt_kprintf("\r\nNo memory\r\n");
        return;
    }
    rt_kprintf("http_mjpeg_server...\r\n");
    while (1) {
        web_netdev = netdev_get_by_name(NETIF_NAME);
        if (web_netdev != RT_NULL) {
            if ((netdev_is_link_up(web_netdev) == RT_TRUE) &&
                (netdev_is_up(web_netdev) == RT_TRUE) &&
                (netdev_is_internet_up(web_netdev) == RT_TRUE)) {
                ip_addr_str = inet_ntoa(web_netdev->ip_addr);
                break;
            }
        }
        rt_thread_mdelay(1000);
    }
    rt_kprintf("web IP address has find....\n");
    host = gethostbyname(ip_addr_str);
    rt_sprintf(index_data_format, indexdata, BOARD_NAME, WEB_CAMERA_NAE, IMAGE_WIDTH, IMAGE_HEIGHT, ip_addr_str, BOARD_NAME);

    /* socketSOCK_STREAMTCPsocket */
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        rt_kprintf("\r\nSocket error\n");
        rt_free(recv_data);
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(WEB_SERVER_PORT);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    rt_memset(&(server_addr.sin_zero), 8, sizeof(server_addr.sin_zero));

    /* socket */
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
        rt_kprintf("Unable to bind\n");
        rt_free(recv_data);
        return;
    }

    if (listen(sock, 5) == -1) {
        rt_kprintf("Listen error\n");
        rt_free(recv_data);
        return;
    }

    rt_kprintf("WebServer Waiting for client on port 80...\n");
    while (stop != 1) {
        sin_size = sizeof(struct sockaddr_in);
        /* socket */
        stream_connected = accept(sock, (struct sockaddr *)&client_addr, &sin_size);
        /* socket */
        rt_kprintf("\nStreamConnected=%d,%s , %d\r\n", stream_connected,
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        /* client_addr */
        rt_sprintf(http_buf, "GET /?%s=mjpeg HTTP/1.1", BOARD_NAME);
        while (1) {
            /* stream_connected socket*/
            bytes_received = recv(stream_connected, recv_data, 1024, 0); //
            if (bytes_received <= 0) {
                closesocket(stream_connected); // stream_connected socket
                rt_kprintf("\r\nbytes_received <= 0,lwip close...\n");
                break;
            }
            recv_data[bytes_received] = '\0'; //
            uri = strtok(recv_data, "\r\n");
            rt_kprintf("\r\nuri=%s\r\n", uri);
            if (strcmp((const char *)uri, "GET / HTTP/1.1") == 0) {
                send(stream_connected, http_html_hdr, rt_strlen(http_html_hdr), 0);
                send(stream_connected, index_data_format, rt_strlen(index_data_format), 0);
                closesocket(stream_connected);
            } else if (strcmp((const char *)uri, http_buf) == 0) {
                if (http_streamer_start(stream_connected, 0) == http_ok) {
                    rt_kprintf("\r\n Now Ok!!\r\n");
                    rt_thread_mdelay(50);
                    video_flag = HTTP_VIDEO_START;
                    http_mjpeg_send(NULL);
                }
            } else if (strcmp((const char *)uri, "GET /favicon.ico HTTP/1.1") ==
                       0) {
                http_send_icon(stream_connected);

            } else {
                rt_kprintf("\r\n%s\r\n", uri);
            }
        }
    }

    closesocket(sock);
    rt_free(recv_data);
    rt_kprintf("\r\nlwip close\r\n");
    return;
}



