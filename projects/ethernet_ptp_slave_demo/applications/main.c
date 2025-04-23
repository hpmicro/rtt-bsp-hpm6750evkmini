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
#include "ptpd/src/ptpd.h"

void ptp_thread_entry(void *arg);
void thread_entry(void *arg);



int main(void)
{

    app_init_led_pins();

    static uint32_t led_thread_arg = 0;
    rt_thread_t led_thread = rt_thread_create("led_th", thread_entry, &led_thread_arg, 1024, 25, 10);
    rt_thread_startup(led_thread);
    rt_thread_t ptp_thread = rt_thread_create("ptp_th", ptp_thread_entry, NULL, 8192, 14, 20);
    rt_thread_startup(ptp_thread);

    return 0;
}


void ptp_thread_entry(void *arg)
{
    static uint32_t localtime = 0;

    ptpd_Init();

    while (1) {
        rt_thread_mdelay(1);
        ptpd_periodic_handle(localtime++);
    }
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
