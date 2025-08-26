/*
 * Copyright (c) 2021-2025 HPMicro
 *
 * Change Logs:
 * Date         Author          Notes
 * 2021-08-13   Fan YANG        first version
 * 2025-06-27   HPMicro         add alarm sample
 *
 */

#include <stdio.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "rtt_board.h"

#define HWTIMER_DEV_NAME   "GPT1"       /* Timer Name */
rt_device_t hw_dev;                     /* Timer Device Handler */
rt_hwtimer_mode_t mode;                 /* Timer Mode */
rt_hwtimerval_t timeout_s;              /* Timer Value */

#ifdef RT_USING_ALARM
static rt_alarm_t alarm = RT_NULL;
#endif

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

#if defined(RT_USING_ALARM) && defined(BSP_USING_RTC)
void user_alarm_callback(rt_alarm_t alarm, time_t timestamp)
{
    struct tm p_tm;
    time_t now = timestamp;

#ifdef RT_ALARM_USING_LOCAL_TIME
    localtime_r(&now, &p_tm);
#else
    gmtime_r(&now, &p_tm);
#endif
    rt_kprintf("user alarm callback function. \r\n");
    rt_kprintf("current time: %04d-%02d-%02d %02d:%02d:%02d \r\n", p_tm.tm_year + 1900, p_tm.tm_mon + 1, p_tm.tm_mday, p_tm.tm_hour, p_tm.tm_min, p_tm.tm_sec); 
}

void alarm_sample(int argc, char *argv[])
{
    rt_uint32_t offset_time;
    time_t curr_time;
    struct tm p_tm;
    struct rt_alarm_setup setup;

    if (argc < 2) {
        rt_kprintf("set the alarm time to a specified time after the current time, such as 5 seconds later \r\n");
        return;
    }

    if (argc > 2) {
        rt_kprintf("too many arguments \r\n");
        return;
    }

    if (sscanf(argv[1], "%d", &offset_time) != 1) {
        rt_kprintf("invalid time format \r\n");
        return;
    }

    curr_time = time(NULL) + offset_time;
#ifdef RT_ALARM_USING_LOCAL_TIME
    localtime_r(&curr_time, &p_tm);
    rt_kprintf("alarm use local time \r\n");
#else
    gmtime_r(&curr_time, &p_tm);
    rt_kprintf("alarm use UTC time \r\n");
#endif
    rt_kprintf("alarm time: %04d-%02d-%02d %02d:%02d:%02d \r\n", p_tm.tm_year + 1900, p_tm.tm_mon + 1, p_tm.tm_mday, p_tm.tm_hour,
            p_tm.tm_min, p_tm.tm_sec - 5);

    setup.flag = RT_ALARM_ONESHOT;
    setup.wktime.tm_year = p_tm.tm_year;
    setup.wktime.tm_mon = p_tm.tm_mon;
    setup.wktime.tm_mday = p_tm.tm_mday;
    setup.wktime.tm_wday = p_tm.tm_wday;
    setup.wktime.tm_hour = p_tm.tm_hour;
    setup.wktime.tm_min = p_tm.tm_min;
    setup.wktime.tm_sec = p_tm.tm_sec;

    alarm = rt_alarm_create(user_alarm_callback, &setup);
    if (RT_NULL != alarm)
    {
        rt_alarm_start(alarm);
    }
    else
    {
        rt_kprintf("rtc alarm create failed");
    }

}
MSH_CMD_EXPORT(alarm_sample, alarm sample);

void del_alarm_sample(void)
{
    rt_alarm_delete(alarm);
    rt_kprintf("delete all alarm\r\n");
}
MSH_CMD_EXPORT(del_alarm_sample, delete alarm sample);

#endif

int main(void)
{
    return 0;
}

