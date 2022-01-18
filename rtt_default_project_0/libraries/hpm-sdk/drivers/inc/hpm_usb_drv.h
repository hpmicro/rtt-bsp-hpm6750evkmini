/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_USB_DRV_H
#define HPM_USB_DRV_H
/*---------------------------------------------------------------------*
 * Includes
 *---------------------------------------------------------------------*/
#include "hpm_common.h"
#include "hpm_usb_regs.h"
#include "hpm_soc_feature.h"

/*---------------------------------------------------------------------*
 *  Macro Constant Declarations
 *---------------------------------------------------------------------*/
#define USB_PHY_INIT_DELAY_COUNT  (16U)
#define USB_HOST_FRAMELIST_SIZE   (8U)

/*---------------------------------------------------------------------*
 *  Macro Enum Declarations
 *---------------------------------------------------------------------*/
typedef enum {
    usb_dir_out     = 0,
    usb_dir_in      = 1,
    usb_dir_in_mask = 0x80
}usb_dir_t;

typedef enum {
    usb_xfer_control = 0,
    usb_xfer_isochronous,
    usb_xfer_bulk,
    usb_xfer_interrupt
} usb_xfer_type_t;

typedef enum {
    usb_ctrl_mode_otg    = 0,
    usb_ctrl_mode_device = 2,
    usb_ctrl_mode_host   = 3
} usb_controller_mode_t;
/*---------------------------------------------------------------------*
 * Structure Declarations
 *---------------------------------------------------------------------*/

/* Control Request */
typedef struct  __attribute__ ((packed)){
    union {
        struct  __attribute__ ((packed)) {
            uint8_t recipient :  5;
            uint8_t type      :  2;
            uint8_t direction :  1;
        } bmRequestType_bit;

        uint8_t bmRequestType;
    };

    uint8_t  bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
} usb_control_request_t;

typedef struct {
    uint8_t  xfer;
    uint8_t  ep_addr;
    uint16_t max_packet_size;
} usb_endpoint_config_t;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*---------------------------------------------------------------------*
 * Common API
 *---------------------------------------------------------------------*/
/* Get interrupts */
static inline uint32_t usb_get_interrupts(USB_Type *ptr)
{
    return ptr->USBINTR;
}

/* Set interrupts */
static inline void usb_enable_interrupts(USB_Type *ptr, uint32_t mask)
{
    ptr->USBINTR |= mask;
}

/* Get status flags */
static inline uint32_t usb_get_status_flags(USB_Type *ptr)
{
    return ptr->USBSTS;
}

/* Clear status flags */
static inline void usb_clear_status_flags(USB_Type *ptr, uint32_t mask)
{
    ptr->USBSTS |= mask;
}

/* Get port speed */
static inline uint8_t usb_get_port_speed(USB_Type *ptr)
{
    return USB_PORTSC1_PSPD_GET(ptr->PORTSC1);
}
/* Get controller suspend status */
static inline uint8_t usb_get_suspend_status(USB_Type *ptr)
{
    return USB_PORTSC1_SUSP_GET(ptr->PORTSC1);
}

/* Get reset status */
static inline bool usb_get_port_reset_status(USB_Type *ptr)
{
    return USB_PORTSC1_PR_GET(ptr->PORTSC1);
}

/* Get port current conect status */
static inline bool usb_get_port_ccs(USB_Type *ptr)
{
    return USB_PORTSC1_CCS_GET(ptr->PORTSC1);
}

/*---------------------------------------------------------------------*
 * Device API
 *---------------------------------------------------------------------*/
/* USB device bus reset */
void usb_dcd_bus_reset(USB_Type *ptr, uint16_t ep0_max_packet_size);

/* Initialize controller to device mode */
void usb_dcd_init(USB_Type *ptr);

/* De-initialize controller */
void usb_dcd_deinit(USB_Type *ptr);

/* Wake up host */
void usb_dcd_remote_wakeup(USB_Type *ptr);

/* Configure an endpoint */
void usb_dcd_edpt_open(USB_Type *ptr, usb_endpoint_config_t *config);

/* Submit a transfer */
void usb_dcd_edpt_xfer(USB_Type *ptr, uint8_t ep_idx);

/* Stall endpoint */
void usb_dcd_edpt_stall(USB_Type *ptr, uint8_t ep_addr);

/* Clear stall */
void usb_dcd_edpt_clear_stall(USB_Type *ptr, uint8_t ep_addr);

/* close a specified endpoint */
void usb_dcd_edpt_close(USB_Type *ptr, uint8_t ep_addr);

/* Get setup status of endpoint */
static inline uint32_t usb_dcd_get_edpt_setup_status(USB_Type *ptr)
{
    return ptr->ENDPTSETUPSTAT;
}

/* Clear setup status of endpoint */
static inline void usb_dcd_clear_edpt_setup_status(USB_Type *ptr, uint32_t mask)
{
    ptr->ENDPTSETUPSTAT |= mask;
}

/* Set address */
static inline void usb_dcd_set_address(USB_Type *ptr, uint8_t dev_addr)
{
    ptr->DEVICEADDR = USB_DEVICEADDR_USBADR_SET(dev_addr) | USB_DEVICEADDR_USBADRA_MASK;
}

/* Connect by enabling internal pull-up resistor on D+/D- */
static inline void usb_dcd_connect(USB_Type *ptr)
{
    ptr->USBCMD |= USB_USBCMD_RS_MASK;
}

/* Disconnect by disabling internal pull-up resistor on D+/D- */
static inline void usb_dcd_disconnect(USB_Type *ptr)
{
    ptr->USBCMD &= ~USB_USBCMD_RS_MASK;
}

/* Set endpoint list address */
static inline void usb_dcd_set_edpt_list_addr(USB_Type *ptr, uint32_t addr)
{
    ptr->ENDPTLISTADDR = addr;
}

/* Get device address */
static inline uint8_t usb_dcd_get_device_addr(USB_Type *ptr)
{
    return USB_DEVICEADDR_USBADR_GET(ptr->DEVICEADDR);
}

/* Get complete status of endpoint */
static inline uint32_t usb_dcd_get_edpt_complete_status(USB_Type *ptr)
{
    return ptr->ENDPTCOMPLETE;
}

/* Clear complete status of endpoint */
static inline void usb_dcd_clear_edpt_complete_status(USB_Type *ptr, uint32_t mask)
{
    ptr->ENDPTCOMPLETE |= mask;
}

/*---------------------------------------------------------------------*
 * Host API
 *---------------------------------------------------------------------*/
/* Initialize controller to host mode */
bool usb_hcd_init(USB_Type *ptr, uint32_t int_mask, uint16_t framelist_size);

/* Host Reset port */
void usb_hcd_port_reset(USB_Type *ptr);

/* Host set command register */
static inline void usb_hcd_set_command(USB_Type *ptr ,uint32_t mask)
{
    ptr->USBCMD |= mask;
}

/* Get frame index */
static inline uint32_t usb_hcd_get_frame_index(USB_Type *ptr)
{
    return ptr->FRINDEX;
}

/* Get port connect status change */
static inline bool usb_hcd_get_port_csc(USB_Type *ptr)
{
    return USB_PORTSC1_CSC_GET(ptr->PORTSC1);
}

/* Set async list address */
static inline void usb_hcd_set_async_list_addr(USB_Type *ptr, uint32_t addr)
{
    ptr->ASYNCLISTADDR = addr;
}

/* Set periodic list address */
static inline void usb_hcd_set_periodic_list_addr(USB_Type *ptr, uint32_t addr)
{
    ptr->PERIODICLISTBASE = addr;
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* HPM_USB_DRV_H */
