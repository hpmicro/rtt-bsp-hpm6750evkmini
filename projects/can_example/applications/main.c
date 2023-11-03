/*
 * Copyright (c) 2022-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-08     hpmicro      the first version
 * 2023-05-08     hpmicro      Adapt the RT-Thread V5.0.0
 */

/*****************************************************************************************
 *
 *  CAN Example
 *
 *  This demo works in internal loopback mode. It demonstrates following functions:
 *
 *   1. CAN transmission and reception with standard ID
 *   2. CAN transmission and reception with extended ID
 *   3. CAN transmission and reception with CAN filter enabled
 *   4. CANFD transmission and reception
 *
 *
 *****************************************************************************************/


#include <rtthread.h>
#include <rtdevice.h>
#include "rtt_board.h"

#define CAN_BAUD    (1000000)
#define CANFD_BAUD  (2000000)

#define CAN_FILTERMODE_IDMASK       (0x00000000U)  /*!< Identifier mask mode */


static struct rt_semaphore rx_sem;     /* Semaphore fore CAN receive */
static rt_device_t can_dev;            /* CAN device handler */

static uint8_t can_get_data_bytes_from_dlc(uint32_t dlc);
static void can_rx_thread(void *parameter);

int main(void)
{

    /* Search CAN device */
    can_dev = rt_device_find(BOARD_CAN_NAME);
    if (!can_dev)
    {
        rt_kprintf("find %s failed!\n", BOARD_CAN_NAME);
        return RT_ERROR;
    }

    /* Initialize semaphore for CAN receive */
    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);

    /* OPEN CAN device using interrupt transmit and receive mode */
    rt_err_t res = rt_device_open(can_dev, RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
    rt_device_control(can_dev, RT_CAN_CMD_SET_MODE, (void*) RT_CAN_MODE_LOOPBACK);
    RT_ASSERT(res == RT_EOK);
    /* Create receive thread */
    rt_thread_t thread = rt_thread_create("can_rx", can_rx_thread, RT_NULL, 1024, 25, 10);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        rt_kprintf("create can_rx thread failed!\n");
    }
}


/* Callback for receive */
static rt_err_t can_rx_call(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(&rx_sem);

    return RT_EOK;
}

static void can_rx_thread(void *parameter)
{
    int i;
    rt_err_t res;
    struct rt_can_msg rxmsg = {0};

    /* Set callback for receive */
    rt_device_set_rx_indicate(can_dev, can_rx_call);


    while (1)
    {
        rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
        /* Get one CAN frame */
        rt_device_read(can_dev, 0, &rxmsg, sizeof(rxmsg));
        /* Display CAN frame content */
        rt_kprintf("ID: %x  ", rxmsg.id);
        uint32_t msg_len = can_get_data_bytes_from_dlc(rxmsg.len);
        for (i = 0; i < msg_len; i++)
        {
            rt_kprintf("%02x", rxmsg.data[i]);
        }

        rt_kprintf("\n");
    }
}

static uint8_t can_get_data_bytes_from_dlc(uint32_t dlc)
{
    uint32_t data_bytes = 0;

    dlc &= 0xFU;
    if (dlc <= 8U) {
        data_bytes = dlc;
    } else {
        switch (dlc) {
            case 9:
                data_bytes = 12U;
                break;
            case 10:
                data_bytes = 16U;
                break;
            case 11:
                data_bytes = 20U;
                break;
            case 12:
                data_bytes = 24U;
                break;
            case 13:
                data_bytes = 32U;
                break;
            case 14:
                data_bytes = 48U;
                break;
            case 15:
                data_bytes = 64U;
                break;
            default:
                /* Code should never touch here */
                break;
        }
    }

    return data_bytes;
}


int can_sample(int argc, char *argv[])
{
    struct rt_can_msg msg = {0};
    rt_err_t res;
    rt_size_t  size;
    rt_thread_t thread;
    char can_name[RT_NAME_MAX];

    if (argc == 2)
    {
        rt_strncpy(can_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(can_name, BOARD_CAN_NAME, RT_NAME_MAX);
    }

    /* Search CAN device */
    can_dev = rt_device_find(can_name);
    if (!can_dev)
    {
        rt_kprintf("find %s failed!\n", can_name);
        return RT_ERROR;
    }

    /* Restore CAN filters to default state */
    rt_device_control(can_dev, RT_CAN_CMD_SET_FILTER, NULL);

    msg.id = 0x78;              /* ID 为 0x78 */
    msg.ide = RT_CAN_STDID;     /* Standard ID */
    msg.rtr = RT_CAN_DTR;       /* Data Frame */
    msg.len = CAN_MSG_8BYTES;   /* Data size: 8 */
    /* Data to be sent */
    msg.data[0] = 0x00;
    msg.data[1] = 0x11;
    msg.data[2] = 0x22;
    msg.data[3] = 0x33;
    msg.data[4] = 0x44;
    msg.data[5] = 0x55;
    msg.data[6] = 0x66;
    msg.data[7] = 0x77;

    rt_kprintf("Sent out messages with standard id\n");
    for (uint32_t i = 0; i < 10; i++)
    {
        msg.id = i;
        size = rt_device_write(can_dev, 0, &msg, sizeof(msg));
        if (size == 0)
        {
            rt_kprintf("can dev write data failed!\n");
        }
        rt_thread_mdelay(5); /* delay a while, give the receive thread enough time to print out received message */
    }

    rt_kprintf("Sent out messages with extended id\n");
    msg.ide = RT_CAN_EXTID;     /* Extend ID */
    for (uint32_t i = 0; i < 10; i++)
    {
        msg.id = i + 0x10000;
        size = rt_device_write(can_dev, 0, &msg, sizeof(msg));
        if (size == 0)
        {
            rt_kprintf("can dev write data failed!\n");
        }
        rt_thread_mdelay(5); /* delay a while, give the receive thread enough time to print out received message */
    }

    /****************************************************************************
     *
     *  Configure the CAN Filters
     *
     ****************************************************************************/
    struct rt_can_filter_item items[5] =
    {
    #ifdef RT_CAN_USING_HDR
        /* std, match ID:0x100~0x1ff, default filter list */
        RT_CAN_FILTER_ITEM_INIT(0x100, 0, 0, CAN_FILTERMODE_IDMASK, 0x700, RT_NULL, RT_NULL),
        /* std, match ID:0x300~0x3ff*/
        RT_CAN_FILTER_ITEM_INIT(0x300, 0, 0, CAN_FILTERMODE_IDMASK, 0x700, RT_NULL, RT_NULL),
        /* std,match ID:0x211*/
        RT_CAN_FILTER_ITEM_INIT(0x211, 0, 0, CAN_FILTERMODE_IDMASK, 0x7FF, RT_NULL, RT_NULL),
        /* std,match ID:0x486*/
        RT_CAN_FILTER_STD_INIT(0x486, RT_NULL, RT_NULL),
        /* std, match ID: 0x55, specify the filter number : 7 */
        {0x555, 0, 0, CAN_FILTERMODE_IDMASK, 0x7ff, 7,}
    #else
        /* std, match ID:0x100~0x1ff, default filter list */
        RT_CAN_FILTER_ITEM_INIT(0x100, 0, 0, CAN_FILTERMODE_IDMASK, 0x700),
        /* std, match ID:0x300~0x3ff*/
        RT_CAN_FILTER_ITEM_INIT(0x300, 0, 0, CAN_FILTERMODE_IDMASK, 0x700),
        /* std,match ID:0x211*/
        RT_CAN_FILTER_ITEM_INIT(0x211, 0, 0, CAN_FILTERMODE_IDMASK, 0x7FF),
        /* std,match ID:0x486*/
        RT_CAN_FILTER_STD_INIT(0x486),
        /* std, match ID: 0x55, specify the filter number : 7 */
        {0x555, 0, 0, CAN_FILTERMODE_IDMASK, 0x7ff, 7,}
    #endif
    };

    struct rt_can_filter_config cfg = {5, 1, items};
    res = rt_device_control(can_dev, RT_CAN_CMD_SET_FILTER, &cfg);
    RT_ASSERT(res == RT_EOK);

    rt_kprintf("Sent out messages with filter enabled\n");
    msg.ide = RT_CAN_STDID;
    for (uint32_t i = 0; i < 0x7ff; i++)
    {
        msg.id = i;
        size = rt_device_write(can_dev, 0, &msg, sizeof(msg));
        if (size == 0)
        {
            rt_kprintf("can dev write data failed!\n");
        }
        rt_thread_mdelay(5); /* delay a while, give the receive thread enough time to print out received message */
    }

#ifdef RT_CAN_USING_CANFD
    /* Restore CAN filters to default state */
    rt_device_control(can_dev, RT_CAN_CMD_SET_FILTER, NULL);
    /* Re-Configure CAN baud rate */
    rt_device_control(can_dev, RT_CAN_CMD_SET_BAUD, (void*)CAN_BAUD);
    /* Configure CAN-FD baud rate */
    rt_device_control(can_dev, RT_CAN_CMD_SET_BAUD_FD, (void*)CANFD_BAUD);

    /**
     * NOTE: In real CAN-FD use case, user may need to use the similar codes as below
     *  to get the same bit-timing configuration in the whole CANFD network
     *
     *  Assume the CAN clock is 80MHz, below is the bit timing for CANFD
     *
     */
#if 0
     struct rt_can_bit_timing timing_items[2] =
             {
                     /* prescaler, num_seg1, num_seg2, num_sjw, num_sspoff */
                     {2, 32, 8, 8, 0}, /* 1Mbit/s */
                     {2, 16, 4, 4, 16}, /* 2Mbit/s */
             };
     struct rt_can_bit_timing_config timing_config =
     {
             2,
             &timing_items[0];
     };
     rt_device_control(can_dev, RT_CAN_CMD_SET_BITTIMING, &timing_config);


#endif

    /* Enable CANFD */
    rt_device_control(can_dev, RT_CAN_CMD_SET_CANFD, (void*)1);

    msg.len = CAN_MSG_16BYTES;
    msg.fd_frame = 1;
    for (uint32_t i=8; i<16; i++)
    {
        msg.data[i] = (uint8_t)(i | (i<<4));
    }
    rt_kprintf("Sent out CANFD messages with standard id\n");
    for (uint32_t i = 0; i < 10; i++)
    {
        msg.id = i;
        size = rt_device_write(can_dev, 0, &msg, sizeof(msg));
        if (size == 0)
        {
            rt_kprintf("can dev write data failed!\n");
        }
        rt_thread_mdelay(10); /* delay a while, give the receive thread enough time to print out received message */
    }

    rt_kprintf("Sent out CANFD messages with extended id\n");
    msg.ide = RT_CAN_EXTID; /* Extend ID */
    for (uint32_t i = 0; i < 10; i++)
    {
        msg.id = i + 0x10000;
        size = rt_device_write(can_dev, 0, &msg, sizeof(msg));
        if (size == 0)
        {
            rt_kprintf("can dev write data failed!\n");
        }
        rt_thread_mdelay(10); /* delay a while, give the receive thread enough time to print out received message */
    }

#endif

    return RT_EOK;
}

/* EXPORT to msh command list */
MSH_CMD_EXPORT(can_sample, can device sample);
