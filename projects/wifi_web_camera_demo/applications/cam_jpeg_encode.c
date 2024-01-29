/*
 * Copyright (c) 2023 hpmicro
 *
 * Change Logs:
 * Date         Author          Notes
 * 2023-10-17   HPMicro     first version
 *
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "hpm_cam_drv.h"
#include "hpm_camera.h"
#include "hpm_jpeg_drv.h"
#include "hpm_lcdc_drv.h"
#include "hpm_gpio_drv.h"
#include "hpm_l1c_drv.h"

#include "cam_jpeg_encode.h"

/* jpeg related */
#ifndef BOARD_JPEG
#define BOARD_JPEG        HPM_JPEG
#endif

#ifndef BOARD_CAM
#define BOARD_CAM         HPM_CAM0
#endif

#ifndef BOARD_CAM_IRQ
#define BOARD_CAM_IRQ     IRQn_CAM0
#endif

/* cam related */
#define CAM_I2C            BOARD_CAM_I2C_BASE
#define CAMERA_INTERFACE   camera_interface_dvp

/* in order to align 16byte for jpeg, buffer + 256 */
#define CAM_BUF_LEN        (IMAGE_HEIGHT * IMAGE_WIDTH * 2)
#define CAM_BUF_COUNT      (2)

#define PIXEL_FORMAT       display_pixel_format_rgb565

ATTR_PLACE_AT_WITH_ALIGNMENT(".framebuffer", HPM_L1C_CACHELINE_SIZE) uint8_t cam_buffers[CAM_BUF_COUNT][CAM_BUF_LEN + 256];

static volatile bool vsync = false;
static rt_sem_t cam_transfer_done_sem = RT_NULL;
static rt_sem_t cam_eof_sem = RT_NULL;
static rt_sem_t  cam_jpeg_sem = RT_NULL;

uint8_t *front_buffer, *back_buffer;

static uint8_t jpeg_header[] = {
#include "jpg_header_rgb.cdat"
};


/*
 * huffmin table
 */
const uint32_t huffmin[16]={
    0xf0e0c082,
    0xf6f6f6f4,
    0x2b5d78f8,
    0x00000001,

    0xf0e0c080,
    0xfefefcf8,
    0xbbdf7efe,
    0x00000000,

    0xf0e0c288,
    0xf4f6f6f4,
    0x2b1c78f6,
    0x00000001,

    0xfcf8f0e0,
    0xfefefefe,
    0xbbdf7efe,
    0x00000001
};

/*
 * huffbase table
 */
const uint16_t huffbase[64] = {
#include "base.cdat"
};

/*
 * huffsymb table
 */
const uint8_t huffsymb[336] = {
#include "symb.cdat"
};

/*
 * huffenc table
 */
const uint16_t huffenc[384] = {
#include "htable.cdat"
};

const uint16_t qetable[256] = {
#include "qetable.cdat"
};

const uint16_t qdtable[256] = {
#include "qdtable.cdat"
};

void isr_cam(void)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    if ((cam_check_status(BOARD_CAM, cam_status_fb1_dma_transfer_done) == true) &&
        (BOARD_CAM->INT_EN & cam_irq_fb1_dma_transfer_done)) {
        cam_clear_status(BOARD_CAM, cam_status_fb1_dma_transfer_done);
        rt_sem_release(cam_transfer_done_sem);
    }
    if ((cam_check_status(BOARD_CAM, cam_status_fb2_dma_transfer_done) == true) &&
        (BOARD_CAM->INT_EN & cam_irq_fb2_dma_transfer_done)) {
        cam_clear_status(BOARD_CAM, cam_status_fb2_dma_transfer_done);
        rt_sem_release(cam_transfer_done_sem);
    }
    if ((cam_check_status(BOARD_CAM, cam_status_end_of_frame) == true) &&
        (BOARD_CAM->INT_EN & cam_irq_end_of_frame)) {
        cam_clear_status(BOARD_CAM, cam_status_end_of_frame);
        rt_sem_release(cam_eof_sem);
    }
    rt_hw_interrupt_enable(level);
}
SDK_DECLARE_EXT_ISR_M(BOARD_CAM_IRQ, isr_cam)

void isr_jpeg(void)
{
    uint32_t status = jpeg_get_status(HPM_JPEG);
    if (status & JPEG_EVENT_OUT_DMA_FINISH) {
        jpeg_clear_status(HPM_JPEG, JPEG_EVENT_OUT_DMA_FINISH);
        rt_sem_release(cam_jpeg_sem);
    }
}
SDK_DECLARE_EXT_ISR_M(IRQn_JPEG, isr_jpeg)

/*
 * sensor configuration
 *
 */

void cam_delay_ms(uint32_t ms)
{
    rt_thread_mdelay(ms);
}

void init_camera_device(void)
{
    camera_context_t camera_context = {0};
    camera_config_t camera_config = {0};
    camera_context.i2c_device_addr = CAMERA_DEVICE_ADDR;
    camera_context.ptr = CAM_I2C;
    camera_context.delay_ms = cam_delay_ms;
#ifdef BOARD_SUPPORT_CAM_RESET
    camera_context.write_rst = board_write_cam_rst;
#endif
#ifdef BOARD_SUPPORT_CAM_PWDN
    camera_context.write_pwdn = board_write_cam_pwdn;
#endif

    camera_config.width = IMAGE_WIDTH;
    camera_config.height = IMAGE_HEIGHT;
    camera_config.interface = CAMERA_INTERFACE;
    camera_config.pixel_format = PIXEL_FORMAT;

    if (CAMERA_INTERFACE == camera_interface_dvp) {
        camera_device_get_dvp_param(&camera_context, &camera_config);
    }

    if (status_success != camera_device_init(&camera_context, &camera_config)) {
        rt_kprintf("failed to init camera device\n");
        while (1) {
            camera_context.delay_ms(10);
        };
    }
}

/*
 *  configure CAM
 */
void init_cam(void)
{
    cam_config_t cam_config;

    cam_get_default_config(BOARD_CAM, &cam_config, PIXEL_FORMAT);

    cam_config.width = IMAGE_WIDTH;
    cam_config.height = IMAGE_HEIGHT;
    cam_config.hsync_active_low = true;
    cam_config.buffer1 = core_local_mem_to_sys_address(BOARD_RUNNING_CORE, (uint32_t)cam_buffers[0]);
    cam_config.buffer2 = core_local_mem_to_sys_address(BOARD_RUNNING_CORE, (uint32_t)cam_buffers[0]);

    if (PIXEL_FORMAT == display_pixel_format_rgb565) {
        cam_config.color_format = CAM_COLOR_FORMAT_RGB565;
    } else if (PIXEL_FORMAT == display_pixel_format_y8) {
        cam_config.color_format = CAM_COLOR_FORMAT_YCBCR422;
        cam_config.data_store_mode = CAM_DATA_STORE_MODE_Y_ONLY;
    }
    cam_init(BOARD_CAM, &cam_config);
    cam_enable_irq(BOARD_CAM, cam_irq_fb1_dma_transfer_done | cam_irq_fb2_dma_transfer_done);
    intc_m_enable_irq_with_priority(BOARD_CAM_IRQ, 4);
}


/*
 * JPEG configuration
 */
void reset_jpeg(bool encoding)
{
    jpeg_init(BOARD_JPEG);
    jpeg_enable(BOARD_JPEG);
    jpeg_fill_table(BOARD_JPEG, jpeg_table_huffmin, (uint8_t *)huffmin, ARRAY_SIZE(huffmin));
    jpeg_fill_table(BOARD_JPEG, jpeg_table_huffbase, (uint8_t *)huffbase, ARRAY_SIZE(huffbase));
    jpeg_fill_table(BOARD_JPEG, jpeg_table_huffsymb, (uint8_t *)huffsymb, ARRAY_SIZE(huffsymb));
    jpeg_fill_table(BOARD_JPEG, jpeg_table_huffenc, (uint8_t *)huffenc, ARRAY_SIZE(huffenc));
    if (encoding) {
        jpeg_fill_table(BOARD_JPEG, jpeg_table_qmem, (uint8_t *)qetable, ARRAY_SIZE(qetable));
    } else {
        jpeg_fill_table(BOARD_JPEG, jpeg_table_qmem, (uint8_t *)qdtable, ARRAY_SIZE(qdtable));
    }
    jpeg_disable(BOARD_JPEG);
}

uint32_t jpeg_hw_encode(uint8_t *src_buf, uint32_t width, uint32_t height, uint8_t format, uint8_t *buffer)
{
    uint32_t jpg_size;
    jpeg_job_config_t config = {0};
    rt_err_t result;
    reset_jpeg(true);
    jpeg_disable_irq(HPM_JPEG, JPEG_EVENT_OUT_DMA_FINISH);
    /* jpeg encode parameter configuration */
    if (format == display_pixel_format_y8) {
        config.jpeg_format = JPEG_SUPPORTED_FORMAT_400;
        config.in_pixel_format = jpeg_pixel_format_y8;
        config.out_pixel_format = jpeg_pixel_format_y8;
        config.enable_ycbcr = false;
    } else if (format == display_pixel_format_rgb565) {
        config.jpeg_format = JPEG_SUPPORTED_FORMAT_420;
        config.in_pixel_format = jpeg_pixel_format_rgb565;
        config.out_pixel_format = jpeg_pixel_format_yuv422h1p;
        config.enable_ycbcr = true;
    } else {
        rt_kprintf("unsupported pixel format 0x%x\n", format);
        while (1) {
        }
    }
    config.width_in_pixel = width;
    config.height_in_pixel = height;
    config.in_buffer = core_local_mem_to_sys_address(BOARD_RUNNING_CORE, (uint32_t) src_buf);
    config.out_buffer = core_local_mem_to_sys_address(BOARD_RUNNING_CORE, (uint32_t) buffer);

    if (status_success != jpeg_start_encode(BOARD_JPEG, &config)) {
        return 0;
    }
    jpeg_enable_irq(HPM_JPEG, JPEG_EVENT_OUT_DMA_FINISH);
    result = rt_sem_take(cam_jpeg_sem, 3000);
    if (result != RT_EOK) {
        return RT_FALSE;
    }
    jpg_size = jpeg_get_encoded_length(BOARD_JPEG);

    return jpg_size;
}

void jpeg_header_update_resolution(uint8_t *header, uint32_t header_size, uint32_t width, uint32_t height)
{
    for (uint32_t i = 0; i < header_size; i++) {
        /* find SOF0 */
        if ((header[i] == 0xFF) && (header[i+1] == 0xC0)) {
            /* frame resolution offset 5 bytes after SOF0 signature */
            header[i+5] = height >> 8;
            header[i+6] = height & 0xFF;
            header[i+7] = width >> 8;
            header[i+8] = width & 0xFF;
            break;
        }
    }
}

void jpeg_add_header(uint8_t *file_buf, uint32_t width, uint32_t height)
{
    jpeg_header_update_resolution(jpeg_header, sizeof(jpeg_header), width, height);
    memcpy(file_buf, &jpeg_header[0], sizeof(jpeg_header));
}


uint32_t jpeg_encode(uint8_t *src_buf, uint32_t width, uint32_t height, uint8_t *file_buf, uint32_t buffer_size)
{
    uint32_t size = 0;
    uint32_t dummy_height = 0;
    if (height % 16)
    {
        dummy_height = ((height / 16) + 1) * 16;
    }
    else
    {
        dummy_height = height;
    }
    size = jpeg_hw_encode(src_buf, width, dummy_height, PIXEL_FORMAT, file_buf + sizeof(jpeg_header));
    if (size) {
        jpeg_add_header(file_buf, width, height);
        size += sizeof(jpeg_header);
    }
    return size;
}

int jepg_cam_init(void)
{
    cam_transfer_done_sem = rt_sem_create("csem", 0, RT_IPC_FLAG_PRIO);
    if (cam_transfer_done_sem == RT_NULL) {
        return 1;
    }
    cam_eof_sem = rt_sem_create("cesem", 0, RT_IPC_FLAG_PRIO);
    if (cam_eof_sem == RT_NULL) {
        return 1;
    }
    cam_jpeg_sem = rt_sem_create("jsem", 0, RT_IPC_FLAG_PRIO);
    if (cam_jpeg_sem == RT_NULL) {
        return 1;
    }
    front_buffer = cam_buffers[0];
    back_buffer = cam_buffers[1];
    board_init_cam_clock(BOARD_CAM);
    board_init_i2c(CAM_I2C);
    board_init_cam_pins();

    init_camera_device();
    init_cam();
    cam_start(BOARD_CAM);
    rt_thread_mdelay(100);
    intc_m_enable_irq_with_priority(IRQn_JPEG, 2);
    return 0;
}


rt_base_t get_cam_jpeg_data(uint8_t *data,uint32_t *size)
{
    uint32_t jpg_size = 0, count = 0;
    rt_err_t result;
    rt_sem_t sem;
    rt_base_t sta = RT_FALSE;
    uint8_t *tmp;
    if (data == RT_NULL) {
        return RT_FALSE;
    }
    result = rt_sem_take(cam_transfer_done_sem, RT_WAITING_FOREVER);
    if (result != RT_EOK) {
        rt_kprintf("t2 take a dynamic semaphore, failed.\n");
        rt_sem_delete(cam_transfer_done_sem);
        return RT_FALSE;
    } else {
        cam_clear_status(BOARD_CAM, cam_status_end_of_frame);
        cam_enable_irq(BOARD_CAM, cam_irq_end_of_frame);
        result = rt_sem_take(cam_eof_sem, RT_WAITING_FOREVER);
        if (result != RT_EOK) {
            rt_kprintf("eof sem take a dynamic semaphore, failed.\n");
            rt_sem_delete(cam_eof_sem);
            return RT_FALSE;
        }
        cam_disable_irq(BOARD_CAM, cam_irq_end_of_frame);
        cam_stop(BOARD_CAM);
        tmp = front_buffer;
        front_buffer = back_buffer;
        back_buffer = tmp;
        cam_update_buffer(BOARD_CAM, (uint32_t)front_buffer);
        BOARD_CAM->DMASA_FB2 = (uint32_t)front_buffer;
        if (l1c_dc_is_enabled()) {
            l1c_dc_invalidate((uint32_t)back_buffer, CAM_BUF_LEN);
        }
        jpg_size = jpeg_encode(back_buffer, IMAGE_WIDTH, IMAGE_HEIGHT, data, (IMAGE_WIDTH * IMAGE_HEIGHT * 2));
        if (jpg_size > 0) {
            *size = jpg_size;
            sta = RT_TRUE;
        }
        cam_start(BOARD_CAM);
    }
    return sta;
}


