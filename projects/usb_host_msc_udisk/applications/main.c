/*
/*
 * Copyright (c) 2021-2022 hpmicro
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
#include "msc_app.h"

/*---------------------------------------------------------------------*
 * Macro Enum Declaration
 *---------------------------------------------------------------------*/
/* Blink pattern
 * - 250 ms  : device not mounted
 * - 1000 ms : device mounted
 * - 2500 ms : device is suspended
 */
enum  {
    BLINK_NOT_MOUNTED = 250,
    BLINK_MOUNTED     = 1000,
    BLINK_SUSPENDED   = 2500,
};

/*---------------------------------------------------------------------*
 * Variable Definitions
 *---------------------------------------------------------------------*/
static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;

void tled_thread_entry(void *arg);
void tfs_thread_entry(void *arg);

/*---------------------------------------------------------------------*
 * Get system Tick
 *---------------------------------------------------------------------*/
uint64_t board_millis(void)
{
    return rt_tick_get();
}

/*---------------------------------------------------------------------*
 * tusb board init
 *---------------------------------------------------------------------*/
int tusb_board_init(void)
{
    rt_thread_delay(200);
    return 0;
}

/*---------------------------------------------------------------------*
 * Main
 *---------------------------------------------------------------------*/
int main(void)
{
    rt_err_t result = RT_EOK;
    static uint32_t tled_thread_arg = 0;
    static uint32_t tfs_thread_arg = 0;

    app_init_led_pins();

    rt_thread_t led_thread = rt_thread_create("tled", tled_thread_entry, &tled_thread_arg, 1024, 25, 10);
    rt_thread_startup(led_thread);

    result = rt_mb_init(&tfs_thread_mb, "tfsmb",
                            &tfs_thread_mb_pool[0], FS_THREAD_MBOX_MSG_COUNT,
                            RT_IPC_FLAG_FIFO);

    RT_ASSERT(result == RT_EOK);

    rt_thread_t fs_thread = rt_thread_create("tfs", tfs_thread_entry, &tfs_thread_arg, 8 * 1024, 20, 10);
    rt_thread_startup(fs_thread);

    return 0;
}

/*---------------------------------------------------------------------*
 * LED Thread
 *---------------------------------------------------------------------*/
void led_set_blinking_mounted_interval(void)
{
    blink_interval_ms = BLINK_MOUNTED;
}

void led_set_blinking_unmounted_interval(void)
{
    blink_interval_ms = BLINK_NOT_MOUNTED;
}

void tled_thread_entry(void *arg)
{
    static uint32_t start_ms = 0;
    static bool led_state = false;

    while(1)
    {
        /* Blink every interval ms */
        if (board_millis() - start_ms < blink_interval_ms) {
            continue; /* not enough time */
        }

        start_ms += blink_interval_ms;

        app_led_write(0, led_state);
        led_state = 1 - led_state; /* toggle */
    }
}
