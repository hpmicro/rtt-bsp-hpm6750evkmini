/*
 * Copyright (c) 2022 hpmicro
 *
 * Change Logs:
 * Date         Author          Notes
 * 2022-02-14   hpmicro         first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <lvgl.h>
#include <lv_port_indev.h>
#define DBG_TAG    "LVGL.demo"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#include "rtt_board.h"


extern void lv_demo_music(void);

#ifndef LV_THREAD_STACK_SIZE
#define LV_THREAD_STACK_SIZE 4096
#endif

#ifndef LV_THREAD_PRIO
#define LV_THREAD_PRIO (RT_THREAD_PRIORITY_MAX * 2 / 3)
#endif

void thread_entry(void *parameter)
{
    lv_demo_music();

    /* handle the tasks of LVGL */
    while(1)
    {
        lv_task_handler();
        rt_thread_mdelay(5);
    }
}


int main(void)
{
    rt_thread_t t = rt_thread_create("lvgl", thread_entry, RT_NULL, LV_THREAD_STACK_SIZE, LV_THREAD_PRIO, 10);
    rt_thread_startup(t);

    return 0;
}
