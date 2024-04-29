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
#include "rtt_board.h"

#define HWTIMER_DEV_NAME   "GPT1"       /* Timer Name */
rt_device_t hw_dev;                     /* Timer Device Handler */
rt_hwtimer_mode_t mode;                 /* Timer Mode */
rt_hwtimerval_t timeout_s;              /* Timer Value */

/* Timer timeout callback */
static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("this is hwtimer timeout callback fucntion!\n");
    rt_kprintf("tick is :%d !\n", rt_tick_get());

    return 0;
}

static int hwtimer_sample(int argc, char *argv[])
{
    char device_name[RT_NAME_MAX];

    /* Check whether the device name is provided or not */
    if (argc == 2)
    {
        rt_strncpy(device_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(device_name, HWTIMER_DEV_NAME, RT_NAME_MAX);
    }
    /* Find HWTimer device */
    hw_dev = rt_device_find(device_name);
    /* Open device via read-only mode */
    rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    /* Set timeout callback */
    rt_device_set_rx_indicate(hw_dev, timeout_cb);
    /* Set HWTimer mode to Periodic */
    mode = HWTIMER_MODE_PERIOD;
    rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);

    /* Set timeout interval to 5 seconds and start the timer */
    timeout_s.sec = 5; /* second */
    timeout_s.usec = 0; /* microsecond */
    rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s));

    return 0;
}

MSH_CMD_EXPORT(hwtimer_sample, hwtimer_sample);


#define WDT_DEVICE_NAME    "wdt0"    /* Watchdog Name */

static rt_device_t wdg_dev;         /* Watchdong handler */

static void idle_hook(void)
{
    /* Service watchdog in idle hook */
    rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, NULL);
}

static int wdt_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t timeout = 1;        /* Overflow interval, unit:second */
    char device_name[RT_NAME_MAX];

    /* Check whether the device name is provided or not */
    if (argc == 2)
    {
        rt_strncpy(device_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(device_name, WDT_DEVICE_NAME, RT_NAME_MAX);
    }

    wdg_dev = rt_device_find(device_name);
    if (!wdg_dev)
    {
        rt_kprintf("find %s failed!\n", device_name);
        return RT_ERROR;
    }

    /* Set timeout interval for watchdog */
    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    if (ret != RT_EOK)
    {
        rt_kprintf("set %s timeout failed!\n", device_name);
        return RT_ERROR;
    }
    /* Start watchdog */
    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_START, RT_NULL);
    if (ret != RT_EOK)
    {
        rt_kprintf("start %s failed!\n", device_name);
        return -RT_ERROR;
    }
    /* Set idle hook callback */
    rt_thread_idle_sethook(idle_hook);

    return ret;
}
/* Export wdt example to command list */
MSH_CMD_EXPORT(wdt_sample, wdt sample);

static int wdt_reset(int argc, char *argv[])
{
    rt_thread_idle_delhook(idle_hook);
}
MSH_CMD_EXPORT(wdt_reset, wdt reset);

int main(void)
{
    return 0;
}

