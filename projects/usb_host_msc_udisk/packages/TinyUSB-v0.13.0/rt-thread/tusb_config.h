/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-20     tfx2001      first version
 */

#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

#include <rtconfig.h>

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------
// COMMON CONFIGURATION
//--------------------------------------------------------------------

#if  defined(SOC_SERIES_STM32F1)
#define CFG_TUSB_MCU    OPT_MCU_STM32F1
#elif defined(SOC_SERIES_STM32F4)
#define CFG_TUSB_MCU    OPT_MCU_STM32F4
#elif defined(SOC_SERIES_STM32H7)
#define CFG_TUSB_MCU    OPT_MCU_STM32H7
#elif defined(SOC_SERIES_STM32L4)
#define CFG_TUSB_MCU    OPT_MCU_STM32L4
#elif defined(SOC_NRF52840)
#define CFG_TUSB_MCU    OPT_MCU_NRF5X
#elif defined(SOC_HPM6000)
#define CFG_TUSB_MCU    OPT_MCU_HPM
#elif defined(SOC_HPM5000)
#define CFG_TUSB_MCU    OPT_MCU_HPM
#else
#error "Not support for current MCU"
#endif

#define CFG_TUSB_OS OPT_OS_RTTHREAD

//--------------------------------------------------------------------
// DEBUG CONFIGURATION
//--------------------------------------------------------------------

#ifdef CFG_TUSB_DEBUG
#define CFG_TUSB_DEBUG_PRINTF rt_kprintf
#endif /* CFG_TUSB_DEBUG */



#ifndef BOARD_DEVICE_RHPORT_NUM
#define BOARD_DEVICE_RHPORT_NUM     0
#endif

#ifndef BOARD_DEVICE_RHPORT_SPEED
#define BOARD_DEVICE_RHPORT_SPEED   OPT_MODE_HIGH_SPEED
#endif

#if   BOARD_DEVICE_RHPORT_NUM == 0
#define CFG_TUSB_RHPORT0_MODE     (OPT_MODE_HOST | OPT_MODE_HIGH_SPEED)
#elif BOARD_DEVICE_RHPORT_NUM == 1
#define CFG_TUSB_RHPORT1_MODE     (OPT_MODE_HOST | OPT_MODE_HIGH_SPEED)
#else
  #error "Incorrect RHPort configuration"
#endif

/* USB DMA on some MCUs can only access a specific SRAM region with restriction on alignment.
 * Tinyusb use follows macros to declare transferring memory so that they can be put
 * into those specific section.
 * e.g
 * - CFG_TUSB_MEM SECTION : __attribute__ (( section(".usb_ram") ))
 * - CFG_TUSB_MEM_ALIGN   : __attribute__ ((aligned(4)))
 */
#ifndef CFG_TUSB_MEM_SECTION
#define CFG_TUSB_MEM_SECTION        __attribute__ ((section(".noncacheable")))
#endif

#ifndef CFG_TUSB_MEM_ALIGN
#define CFG_TUSB_MEM_ALIGN          __attribute__ ((aligned(4)))
#endif

//--------------------------------------------------------------------
// DEVICE CONFIGURATION
//--------------------------------------------------------------------
#define CFG_TUH_HUB                 0
#define CFG_TUH_CDC                 0
#define CFG_TUH_HID_KEYBOARD        0
#define CFG_TUH_HID_MOUSE           0
#define CFG_TUSB_HOST_HID_GENERIC   0
#define CFG_TUH_MSC                 1
#define CFG_TUH_VENDOR              0

#define CFG_TUSB_HOST_DEVICE_MAX    (CFG_TUH_HUB ? 5 : 1) /* normal hub has 4 ports */

#ifdef __cplusplus
}
#endif

#endif /* _TUSB_CONFIG_H_ */
