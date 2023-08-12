/*
 * Copyright (c) 2023 HPMicro
 *
 * Change Logs:
 * Date         Author          Notes
 * 2022-02-14   hpmicro         first version
 * 2023-06-29   hpmicro         Adapt LVGL 8.3.5, optimize performance
 *
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <lvgl.h>
#include <lv_port_indev.h>
#define DBG_TAG    "LVGL.demo"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

extern void lv_demo_music(void);

#ifndef LV_THREAD_STACK_SIZE
#define LV_THREAD_STACK_SIZE 4096
#endif

#ifndef LV_THREAD_PRIO
#define LV_THREAD_PRIO (RT_THREAD_PRIORITY_MAX * 2 / 3)
#endif

void lv_user_gui_init(void)
{
    lv_demo_music();
}



int main(void)
{
    return 0;
}
