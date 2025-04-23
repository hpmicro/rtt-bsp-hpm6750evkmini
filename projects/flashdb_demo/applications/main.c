/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * Change Logs:
 * Date         Author          Notes
 * 2021-08-13   hpmicro         first version
 * 2023-08-01   hpmicro         Optimize logic for rt-thread v5.0.1
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "rtt_board.h"
#include <drv_gpio.h>
#include "hpm_romapi.h"
#ifdef RT_USING_FAL
#include "fal.h"
#endif

#ifdef PKG_USING_FLASHDB
#include "flashdb.h"
#endif


void flashdb_init(void);

void thread_entry(void *arg);

#ifdef FDB_USING_KVDB
struct fdb_kvdb s_kvdb;
uint32_t boot_count;
static struct fdb_default_kv_node default_kv_table[] = {{"boot_count", &boot_count, sizeof(boot_count)}}; /* int type KV */
extern void kvdb_basic_sample(fdb_kvdb_t kvdb);
#endif

int main(void)
{
    rt_thread_t led_thread = rt_thread_create("led_th", thread_entry, NULL, 1024, 1, 10);
    rt_thread_startup(led_thread);

    flashdb_init();

    return 0;
}


void thread_entry(void *arg)
{
    app_init_led_pins();

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

void flashdb_init(void)
{
#ifdef RT_USING_FAL
    fal_init();
#endif

#ifdef FDB_USING_KVDB
    fdb_err_t fdb_err;
    struct fdb_default_kv default_kv;
    default_kv.kvs = default_kv_table;
    default_kv.num = sizeof(default_kv_table) / sizeof(default_kv_table[0]);

    fdb_err = fdb_kvdb_init(&s_kvdb, "env", "flashdb", &default_kv, NULL);
    if (fdb_err != FDB_NO_ERR) {
        rt_kprintf("FlashDB initialization failed, error_code=%d\n", fdb_err);
    }
    else
    {
        kvdb_basic_sample(&s_kvdb);
    }

#endif
}
