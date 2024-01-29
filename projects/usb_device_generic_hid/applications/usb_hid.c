/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "rtconfig.h"

#ifdef PKG_USING_TINYUSB

#include <tusb.h>
#include "usb_descriptor.h"
#include "hpm_common.h"

/* report id */
#if CFG_TUSB_REPORT_ID_COUNT == 2
    #define REPORT_ID_OUT           (1U)
    #define REPORT_ID_IN            (2U)
#elif CFG_TUSB_REPORT_ID_COUNT == 1
  #define REPORT_ID_INOUT           (1U)
#endif

/* total length of configuration */
#ifdef CONFIG_TOTAL_LEN
    #undef CONFIG_TOTAL_LEN
#endif
#define CONFIG_TOTAL_LEN (TUD_CONFIG_DESC_LEN + TUD_HID_INOUT_DESC_LEN)

/* buffer size  */
#define CFG_TUD_HID_EP_BUFSIZE_HS   (1024U)
#define CFG_TUD_HID_EP_BUFSIZE_FS   (64U)

/* interval */
#define CFG_TUD_HID_EP_INTERVAL_HS  (4U) /* 2^(4-1) * 125us = 1ms */
#define CFG_TUD_HID_EP_INTERVAL_FS  (1U) /* 1ms */

/* report size */
#define CFG_TUD_HID_REPORT_SIZE     (1024U)

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
    (void) instance;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) reqlen;

    return 0;
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
    uint8_t echo_buf[bufsize];

    /* echo back anything we received from host */
    memcpy(echo_buf, buffer, bufsize);

    #if (CFG_TUSB_REPORT_ID_COUNT > 0)
        report_id = REPORT_ID_IN;
        tud_hid_report(report_id, echo_buf, bufsize);
    #else
        tud_hid_report(0, echo_buf, bufsize);
    #endif
}

//--------------------------------------------------------------------+
// Device Descriptors
//--------------------------------------------------------------------+
static tusb_desc_device_t const desc_device =
{
        .bLength            = sizeof(tusb_desc_device_t),
        .bDescriptorType    = TUSB_DESC_DEVICE,
        .bcdUSB             = 0x0200,
        .bDeviceClass       = 0x00,
        .bDeviceSubClass    = 0x00,
        .bDeviceProtocol    = 0x00,
        .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,

        .idVendor           = PKG_TINYUSB_DEVICE_VID,
        .idProduct          = PKG_TINYUSB_DEVICE_PID,
        .bcdDevice          = 0x0100,

        .iManufacturer      = 0x01,
        .iProduct           = 0x02,
        .iSerialNumber      = 0x03,

        .bNumConfigurations = 0x01
};

// Invoked when received GET DEVICE DESCRIPTOR
// Application return pointer to descriptor
uint8_t const *tud_descriptor_device_cb(void)
{
    return (uint8_t const *) &desc_device;
}

//--------------------------------------------------------------------+
// HID Report Descriptor
//--------------------------------------------------------------------+
static uint8_t const desc_hid_report[] =
{
    #if   (CFG_TUSB_REPORT_ID_COUNT == 2)
        TUD_HID_REPORT_DESC_GENERIC_INOUT(CFG_TUD_HID_REPORT_SIZE - 1, HID_REPORT_ID(REPORT_ID_IN) HID_REPORT_ID(REPORT_ID_OUT))
    #elif (CFG_TUSB_REPORT_ID_COUNT == 1)
        TUD_HID_REPORT_DESC_GENERIC_INOUT(CFG_TUD_HID_REPORT_SIZE - 1, HID_REPORT_ID(REPORT_ID_INOUT))
    #elif (CFG_TUSB_REPORT_ID_COUNT == 0)
        TUD_HID_REPORT_DESC_GENERIC_INOUT(CFG_TUD_HID_REPORT_SIZE)
    #endif
};

// Invoked when received GET HID REPORT DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
uint8_t const *tud_hid_descriptor_report_cb(uint8_t instance)
{
    (void)instance;
    return desc_hid_report;
}

//--------------------------------------------------------------------+
// Configuration Descriptor
//--------------------------------------------------------------------+
static uint8_t const desc_configuration_hs[] =
{
    /* Config number, interface count, string index, total length, attribute, power in mA */
    TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, PKG_TINYUSB_DEVICE_CURRENT),

    /* Interface number, string index, protocol, report descriptor len, EP In & Out address, size & polling interval */
    TUD_HID_INOUT_DESCRIPTOR(ITF_NUM_HID, 4, HID_ITF_PROTOCOL_NONE, sizeof(desc_hid_report), PKG_TINYUSB_DEVICE_HID_EPNUM, 0x80 | PKG_TINYUSB_DEVICE_HID_EPNUM, CFG_TUD_HID_EP_BUFSIZE_HS, CFG_TUD_HID_EP_INTERVAL_HS)
};

static uint8_t const desc_configuration_fs[] =
{
    /* Config number, interface count, string index, total length, attribute, power in mA */
    TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, PKG_TINYUSB_DEVICE_CURRENT),

    /* Interface number, string index, protocol, report descriptor len, EP In & Out address, size & polling interval */
    TUD_HID_INOUT_DESCRIPTOR(ITF_NUM_HID, 4, HID_ITF_PROTOCOL_NONE, sizeof(desc_hid_report), PKG_TINYUSB_DEVICE_HID_EPNUM, 0x80 | PKG_TINYUSB_DEVICE_HID_EPNUM, CFG_TUD_HID_EP_BUFSIZE_FS, CFG_TUD_HID_EP_INTERVAL_FS)

};
// Invoked when received GET CONFIGURATION DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
uint8_t const *tud_descriptor_configuration_cb(uint8_t index)
{
    (void) index; // for multiple configurations

    if (tud_speed_get() == TUSB_SPEED_HIGH)
    {
        return desc_configuration_hs;
    }
    else
    {
        return desc_configuration_fs;
    }
}

//--------------------------------------------------------------------+
// String Descriptors
//--------------------------------------------------------------------+

// array of pointer to string descriptors
static char _serial_number[32] = "123456";

static char *string_desc_arr[] =
{
    (char[]) {0x09, 0x04},              // 0: is supported language is English (0x0409)
    PKG_TINYUSB_DEVICE_MANUFACTURER,    // 1: Manufacturer
    PKG_TINYUSB_DEVICE_PRODUCT,         // 2: Product
    _serial_number,                     // 3: Serials, should use chip ID
    PKG_TINYUSB_DEVICE_HID_STRING,      // 4: Interface string index
};

void tud_descriptor_set_serial(char *serial_number, uint8_t length)
{
    if (length > 31)
    {
        length = 31;
    }

    memcpy(_serial_number, serial_number, length);
    _serial_number[length] = '\0';
}

static uint16_t desc_str[32];

// Invoked when received GET STRING DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
uint16_t const *tud_descriptor_string_cb(uint8_t index, uint16_t langid)
{
    (void) langid;

    uint8_t chr_count;

    if (index == 0)
    {
        memcpy(&desc_str[1], string_desc_arr[0], 2);
        chr_count = 1;
    }
    else
    {
        // Note: the 0xEE index string is a Microsoft OS 1.0 Descriptors.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/usbcon/microsoft-defined-usb-descriptors

        if (index >= sizeof(string_desc_arr) / sizeof(string_desc_arr[0])) return NULL;

        const char *str = string_desc_arr[index];

        // Cap at max char
        chr_count = strlen(str);
        if (chr_count > 31) chr_count = 31;

        // Convert ASCII string into UTF-16
        for (uint8_t i = 0; i < chr_count; i++)
        {
            desc_str[1 + i] = str[i];
        }
    }

    // first byte is length (including header), second byte is string type
    desc_str[0] = (TUSB_DESC_STRING << 8) | (2 * chr_count + 2);

    return desc_str;
}

#endif
