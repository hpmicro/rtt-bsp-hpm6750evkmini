/*
/*
 * Copyright (c) 2021-2024 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*---------------------------------------------------------------------*
 * Includes
 *---------------------------------------------------------------------*/
#include <rtthread.h>
#include <rtdevice.h>
#include "rtt_board.h"
#include "usb_config.h"
#include "usbh_core.h"

void thread_entry(void *arg);

/*---------------------------------------------------------------------*
 * Main
 *---------------------------------------------------------------------*/
int main(void)
{
    static uint32_t led_thread_arg = 0;

    app_init_led_pins();
    app_init_usb_pins();
    intc_set_irq_priority(CONFIG_HPM_USBH_IRQn, 2);
    usbh_initialize(0, CONFIG_HPM_USBH_BASE);
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
