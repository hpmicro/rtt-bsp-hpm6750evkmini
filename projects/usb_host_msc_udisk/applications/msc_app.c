/*
 * Copyright (c) 2021-2022 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*---------------------------------------------------------------------*
 * Includes
 *---------------------------------------------------------------------*/
#include "hpm_common.h"
#include "tusb.h"
#include "dfs_fs.h"
#include "msc_app.h"
#include "dfs_posix.h"

/*---------------------------------------------------------------------*
 * Variable Definitions
 *---------------------------------------------------------------------*/
msc_app_msg_t msg;
struct rt_mailbox tfs_thread_mb;
rt_ubase_t tfs_thread_mb_pool[FS_THREAD_MBOX_MSG_COUNT];
ATTR_PLACE_AT_NONCACHEABLE_INIT char wbuff[50] = {"USB Host MSC FatFs Demo!"};
ATTR_PLACE_AT_NONCACHEABLE_INIT char rbuff[50] = {0};

#if CFG_TUH_MSC
ATTR_PLACE_AT_NONCACHEABLE static scsi_inquiry_resp_t inquiry_resp;

/*---------------------------------------------------------------------*
 * Function Prototyes
 *---------------------------------------------------------------------*/
void led_set_blinking_mounted_interval(void);
void led_set_blinking_unmounted_interval(void);
extern void ls(const char *pathname);
extern void hpm_usb_set_addr(uint8_t dev_addr);

bool file_system_mount(msc_app_msg_t msg)
{
    int fd;
    rt_uint32_t cnt = 0;

    char *filename = {"USBHost.txt"};

    hpm_usb_set_addr(msg.dev_addr);

    if (dfs_mount("usb0", UDISK_MOUNTPOINT, "elm", 0, NULL) != 0)
    {
        rt_kprintf("FatFs mount failed!\n");
        return false;
    }
    else
    {
        printf("FatFs mount succeeded!\n");
    }

    chdir(UDISK_MOUNTPOINT);
    if ((fd = open(filename, O_RDWR | O_CREAT)) < 0)
    {
        printf("Can't Open the %s file!\n", filename);
    }
    else
    {
        printf("The %s is open.\n", filename);

        /* write the test file to a U disk */
        cnt = write(fd, wbuff, strlen(wbuff));
        if (cnt != strlen(wbuff)) {
            rt_kprintf("Write failed\n");
        }

        close(fd);
        /* read the test file from the U disk */
        if ((fd = open(filename, O_RDWR)) >= 0)
        {
            cnt = read(fd, rbuff, strlen(wbuff));
            close(fd);

            /* check the test file */
            if (rt_memcmp(wbuff, rbuff, strlen(wbuff)) == 0)
            {
                /* scan files in the specified directory of the U disk */
                ls(UDISK_MOUNTPOINT);
                printf("Write the %s file successfully!\n", filename);
            }
            else
            {
                printf("Write the %s file unsuccessfully!\n", filename);
            }
        }
    }

    return 0;
}

bool inquiry_complete_cb(uint8_t dev_addr, msc_cbw_t const* cbw, msc_csw_t const* csw)
{
    uint32_t block_count;
    uint32_t block_size;

    if (csw->status != 0)
    {
        printf("Inquiry failed\r\n");
        return false;
    }

    /* Print out Vendor ID, Product ID and Rev */
    printf("%.8s %.16s rev %.4s\r\n", inquiry_resp.vendor_id, inquiry_resp.product_id, inquiry_resp.product_rev);

    /* Get capacity of device */
    block_count = tuh_msc_get_block_count(dev_addr, cbw->lun);
    block_size = tuh_msc_get_block_size(dev_addr, cbw->lun);

    printf("Disk Size: %lu MB\r\n", block_count / ((1024*1024)/block_size));
    printf("Block Count = %lu, Block Size: %lu\r\n", block_count, block_size);

    msc_app_msg_t msg;
    msg.id = FS_MSG_ID_MOUNT;
    msg.dev_addr = dev_addr;

    rt_mb_send(&tfs_thread_mb,  *(rt_ubase_t *)&msg);

  return true;
}

void tuh_msc_mount_cb(uint8_t dev_addr)
{
    uint8_t const lun = 0;
    printf("\nA MassStorage device is mounted.\r\n");

    led_set_blinking_mounted_interval();
    tuh_msc_inquiry(dev_addr, lun, &inquiry_resp, inquiry_complete_cb);
}

void tuh_msc_umount_cb(uint8_t dev_addr)
{
    printf("A MassStorage device is unmounted.\r\n");
    led_set_blinking_unmounted_interval();

    msg.id = FS_MSG_ID_UNMOUNT;
    msg.dev_addr = dev_addr;
    rt_mb_send(&tfs_thread_mb,  *(rt_ubase_t *)&msg);
}

void tfs_thread_entry(void *arg)
{
    while (1)
    {
        if (rt_mb_recv(&tfs_thread_mb, (rt_ubase_t *)&msg, RT_WAITING_FOREVER) == RT_EOK)
        {
            if (msg.id == FS_MSG_ID_MOUNT)
            {
                file_system_mount(msg);
            }
            else if (msg.id == FS_MSG_ID_UNMOUNT)
            {
                if (dfs_unmount(UDISK_MOUNTPOINT))
                {
                    printf("FatFs unmount succeeded!\n");
                }
            }
            else
            {
                printf("Not supported message !\n");
            }
        }
    }
}

#endif /* End of CFG_TUH_MSC */
