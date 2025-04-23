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
#include "usb_config.h"

extern void hid_custom_init(uint8_t busid, uint32_t reg_base);

void thread_entry(void *arg);

int main(void)
{
    static uint32_t led_thread_arg = 0;
    app_init_led_pins();
    app_init_usb_pins();
    intc_set_irq_priority(CONFIG_HPM_USBD_IRQn, 2);
    hid_custom_init(0, CONFIG_HPM_USBD_BASE);
    rt_thread_t led_thread = rt_thread_create("led_th", thread_entry, &led_thread_arg, 1024, 1, 10);
    rt_thread_startup(led_thread);

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
