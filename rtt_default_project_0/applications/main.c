/*
 * Copyright (c) 2021 hpmicro
 *
 * Change Logs:
 * Date         Author          Notes
 * 2021-08-13   Fan YANG        first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

void thread_entry(void *arg);



int main(void)
{

    board_init_led_pins();

    static uint32_t thread0_arg = 0;
    rt_thread_t thread0 = rt_thread_create("thread0", thread_entry, &thread0_arg, 512, 1, 10);
    rt_thread_startup(thread0);

    return 0;
}


void thread_entry(void *arg)
{
    while(1){
        board_led_write(0, BOARD_LED_ON);
        rt_thread_mdelay(500);
        board_led_write(0, BOARD_LED_OFF);
        rt_thread_mdelay(500);
        board_led_write(1, BOARD_LED_ON);
        rt_thread_mdelay(500);
        board_led_write(1, BOARD_LED_OFF);
        rt_thread_mdelay(500);
        board_led_write(2, BOARD_LED_ON);
        rt_thread_mdelay(500);
        board_led_write(2, BOARD_LED_OFF);
        rt_thread_mdelay(500);
    }
}
