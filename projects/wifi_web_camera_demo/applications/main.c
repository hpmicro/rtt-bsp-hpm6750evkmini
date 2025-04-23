/*
 * Copyright (c) 2021 HPMicro
 *
 * Change Logs:
 * Date         Author          Notes
 * 2021-08-13   Fan YANG        first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "rtt_board.h"
#include "web_httpd_mjpeg.h"

void thread_entry(void *arg);

int main(void)
{

    app_init_led_pins();

    static uint32_t led_thread_arg = 0, web_cam_thread_arg = 0;
    rt_thread_t led_thread = rt_thread_create("led_th", thread_entry, &led_thread_arg, 1024, 25, 10);
    rt_thread_startup(led_thread);
    rt_thread_t web_cam_thread = rt_thread_create("web_cam_th", http_mjpeg_server, &web_cam_thread_arg, 8192, 5, 10);
    rt_thread_startup(web_cam_thread);
    return 0;
}


void thread_entry(void *arg)
{
    while(1){
#ifdef APP_LED0
        app_led_write(APP_LED0, APP_LED_ON);
        rt_thread_mdelay(500);
        app_led_write(APP_LED0, APP_LED_OFF);
        rt_thread_mdelay(500);
#endif
#ifdef APP_LED1
        app_led_write(APP_LED1, APP_LED_ON);
        rt_thread_mdelay(500);
        app_led_write(APP_LED1, APP_LED_OFF);
        rt_thread_mdelay(500);
#endif
#ifdef APP_LED2
        app_led_write(APP_LED2, APP_LED_ON);
        rt_thread_mdelay(500);
        app_led_write(APP_LED2, APP_LED_OFF);
        rt_thread_mdelay(500);
#endif
    }
}
