/*
 * File      : drv_wlan.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __DRV_WLAN_H__
#define __DRV_WLAN_H__

#include "rtthread.h"
#include "rtdevice.h"
#include "wmhd_api.h"

//#define RT_WMHD_DEBUG

#ifdef RT_WMHD_DEBUG
#define DBG_LEVEL   DBG_LOG
#else
#define DBG_LEVEL   DBG_INFO
#endif /* RT_WMHD_DEBUG */
#define DBG_LVL         DBG_LEVEL //New RT-Thread using

#define DBG_SECTION_NAME        "WMHD"

#include <rtdbg.h>

int rthw_wifi_init(void);
int rthw_wifi_deinit(void);
int rthw_wifi_send(/*struct netif*/ void *netif, int interface, void *buff, int len);
int rthw_wifi_mac_set(rt_uint8_t mac[], int interface);
int rthw_wifi_mac_get(rt_uint8_t mac[], int interface);
void wifi_chip_resource_init(void);

#ifdef RT_USING_WIFI
int rthw_wifi_connect(char *ssid, int ssid_len, char *password, int pass_len, int security_type);
int rthw_wifi_connect_bssid(char *bssid, char *ssid, int ssid_len, char *password, int pass_len, int security_type, int channel);
int rthw_wifi_disconnect(void);

int rthw_wifi_ap_start(char *ssid, char *password, int security, int channel);
int rthw_wifi_ap_disconnect(void);
void rthw_wifi_ap_callback(int event, struct rt_wlan_buff *buff, void *parameter);

int rthw_wifi_rssi_get(void);
int rthw_wifi_channel_get(int interface);
void rthw_wifi_channel_set(int interface, int channel);

int rthw_wifi_scan(void *content, struct rt_scan_info *info);
int rthw_wifi_scan_stop(void);

int rthw_wifi_get_powersave_mode(void);
int rthw_wifi_set_powersave_enable(int enable);

void rthw_wifi_monitor_enable(int enable);

void rthw_wifi_country_set(rt_country_code_t country_code);
rt_country_code_t rthw_wifi_country_get(void);
#endif

#endif
