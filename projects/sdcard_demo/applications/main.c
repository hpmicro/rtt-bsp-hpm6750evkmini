/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * Change Logs:
 * Date         Author          Notes
 * 2021-08-13   HPMicro         first version
 * 2024-01-03   HPMicro         change the SD card name
 * 2024-05-24   HPMicro         add mmcsd_perf test function
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <dfs_fs.h>
#include <stdio.h>
#include "rtt_board.h"

void thread_entry(void *arg);
void mmcsd_perf_test(void);

#define TEST_BUF_SIZE (64UL * 1024UL)
#define TEST_RW_SIZE (20 * 1024UL * 1024UL)



#define EVENT_MMCSD_PERF_TEST 1
struct rt_event test_evt;

static volatile bool is_busy = false;

extern int write(int fd, const void *buf, size_t len);
extern int read(int fd, void *buf, size_t len);
extern int close(int fd);

void mmcsd_perf(void);


int main(void)
{
    rt_event_init(&test_evt, "perf_evt", RT_IPC_FLAG_PRIO);
    rt_thread_t mmcsd_perf_th = rt_thread_create("cperf_th", thread_entry, NULL, 4096, 24, 10);
    rt_thread_startup(mmcsd_perf_th);

    rt_thread_mdelay(2000);

    if (dfs_mount(BOARD_SD_NAME, "/", "elm", 0, NULL) == 0)
    {
        rt_kprintf("%s mounted to /\n", BOARD_SD_NAME);
    }
    else
    {
        rt_kprintf("%s mount to / failed\n", BOARD_SD_NAME);
    }

    return 0;
}


void thread_entry(void *arg)
{
    while(1)
    {
       if (rt_event_recv(&test_evt, EVENT_MMCSD_PERF_TEST, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, NULL) == RT_EOK)
       {
           rt_kprintf("Running eMMC/SD performance test ...\n");
           mmcsd_perf_test();
           is_busy = false;
       }
    }
}

void mmcsd_perf_test(void)
{
    int fd = 0;
    uint8_t *rw_buf = RT_NULL;
    int result;
    do
    {
        fd = open("tmp_data.bin", O_CREAT | O_RDWR);
        if (fd < 0)
        {
            rt_kprintf("Failed to create test file\n");
            break;
        }
        rw_buf = (uint8_t *) rt_malloc(TEST_BUF_SIZE);
        if (rw_buf == NULL)
        {
            rt_kprintf("No enough heap for mmcsd read/write test, please reduce the test buffer size\n");
            break;
        }
        /* Generate random data and fill into the rw_buf */
        for (uint32_t i = 0; i < TEST_BUF_SIZE; i++)
        {
            rw_buf[i] = rand() % 0xFF;
        }

        /* Write 20MB data to MMC/SD */
        rt_tick_t start_ms = rt_tick_get_millisecond();
        rt_tick_t end_ms;
        uint32_t remaining_size = TEST_RW_SIZE;
        while (remaining_size > 0)
        {
            result = write(fd, rw_buf, TEST_BUF_SIZE);
            if (result < 0)
            {
                rt_kprintf("Failed to write file\n");
                break;
            }
            remaining_size -= TEST_BUF_SIZE;
        }
        if (result < 0)
        {
            break;
        }
        close(fd);
        end_ms = rt_tick_get_millisecond();
        uint32_t elapsed_ms = end_ms - start_ms;
        double rw_speed = (TEST_RW_SIZE * 1.0L) / (elapsed_ms * 1.0L / 1000) / 1024 / 1024;
        int int_speed = (uint32_t)rw_speed;
        int frac_speed = (rw_speed - int_speed) * 100;
        rt_kprintf("eMMC/SD write performance: %d.%02dMB/s\n", int_speed, frac_speed);

        /* Read 20MB data from MMC/SD */
        fd = open("tmp_data.bin", O_RDONLY);
        if (result < 0)
        {
            rt_kprintf("Failed to open test file\n");
            break;
        }

        /* Read 20MB data from MMC/SD */
        start_ms = rt_tick_get_millisecond();
        remaining_size = TEST_RW_SIZE;
        while (remaining_size > 0)
        {
            result = read(fd, rw_buf, TEST_BUF_SIZE);
            if (result < 0)
            {
                rt_kprintf("Failed to read test file\n");
                break;
            }
            remaining_size -= TEST_BUF_SIZE;
        }
        if (result < 0)
        {
            break;
        }
        close(fd);
        end_ms = rt_tick_get_millisecond();
        elapsed_ms = end_ms - start_ms;
        rw_speed = (TEST_RW_SIZE * 1.0L) / (elapsed_ms * 1.0L / 1000) / 1024 / 1024;
        int_speed = (uint32_t)rw_speed;
        frac_speed = (rw_speed - int_speed) * 100;
        rt_kprintf("eMMC/SD read performance: %d.%02dMB/s\n", int_speed, frac_speed);

    } while (false);

    if (fd > 0) {
        close(fd);
    }
    if (rw_buf != RT_NULL)
    {
        rt_free(rw_buf);
        rw_buf = RT_NULL;
    }
}

void mmcsd_perf(void)
{
    if (!is_busy)
    {
        is_busy = true;
        rt_event_send(&test_evt, EVENT_MMCSD_PERF_TEST);
    } else {
        rt_kprintf("mmcsd_perf test is in progress...\n");
    }
}

MSH_CMD_EXPORT(mmcsd_perf, test emmc/sd read write speed);
