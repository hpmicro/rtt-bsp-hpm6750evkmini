/*
 * File      : drv_wlan.c
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

#include <rtdef.h>
#include <rtthread.h>
#include <rthw.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef RT_USING_WIFI
#include <dev_wlan.h>
#include "dev_wlan_mgnt.h"
#endif

#include "drv_wlan.h"
#include "drv_wifi.h"

#if defined(RT_USING_LWIP_VER_NUM) && (RT_USING_LWIP_VER_NUM != 0x20102)
#error "AMPAK Wi-Fi driver requires lwIP v2.1.2, please select RT_USING_LWIP212 in menuconfig"
#endif

#ifdef RT_USING_WIFI
struct rt_wlan_info info;
struct rt_wlan_buff buff;
static wmhd_ap_info_t scan_ap_data;
static struct rt_wlan_device *wlan_sta = NULL;
static struct rt_wlan_device *wlan_ap  = NULL;
#endif

int rthw_wifi_init(void)
{
    wifi_chip_resource_init();
    return wmhd_module_init();
}

int rthw_wifi_deinit(void)
{
    return wmhd_module_exit();
}

int rthw_wifi_send(/*struct netif*/ void *netif, int interface, void *buff, int len)
{
    if (netif == NULL)
        return wmhd_network_xmit_intf(interface, buff);
    else if (netif != NULL && len != 0)
        return wmhd_network_xmit_data(netif, buff, len);
    else if (netif != NULL && len == 0)
        return wmhd_network_xmit_packet(netif, buff);
    return 0;
}

#ifdef RT_USING_WIFI
int rthw_wifi_connect(char *ssid, int ssid_len, char *password, int pass_len, int security_type)
{
    int ret = 0;

    if (security_type == SECURITY_UNKNOWN)
        ret = wmhd_join_ap(ssid, password);
    else
        ret = wmhd_sta_connect(ssid, NULL, security_type, password, 0);

    if (ret == 0) {
      // ret = mhd_wifi_set_listen_interval(10, 0);
      // ret = mhd_wifi_set_listen_interval(10, 1);
    }
    return ret;
}

int rthw_wifi_connect_bssid(char *bssid, char *ssid, int ssid_len, char *password, int pass_len, int security_type, int channel)
{
    return wmhd_sta_connect(ssid, bssid, security_type, password, channel); 
}

int rthw_wifi_disconnect(void)
{
    return wmhd_sta_disconnect();
}

int rthw_wifi_network_up(void)
{
    return wmhd_sta_network_up(0, 0, 0);
}

int rthw_wifi_network_down(void)
{
    return wmhd_sta_network_down();
}

int rthw_wifi_ap_start(char *ssid, char *password, int security, int channel)
{
    int ret = 0;
    uint32_t ip_address = 0; //0: default IP, 0xc0a8a901: 192.168.169.1;
    //ret = wmhd_softap_start(ssid, password, security, channel);
    ret = wmhd_softap_start_ex(ssid, password, security, channel, ip_address, 0, 0);
#if !defined(LWIP_USING_DHCPD)
    if (ret == 0)
        ret = wmhd_softap_start_dhcpd(ip_address);
#endif
    return ret;
}

int rthw_wifi_ap_disconnect(void)
{
#if !defined(LWIP_USING_DHCPD)
    wmhd_softap_stop_dhcpd();
#endif
    return wmhd_softap_stop();
}

static void rthw_wifi_ap_client_event(struct rt_wlan_device *wlan, rt_wlan_dev_event_t event, wmhd_mac_t* bssid)
{
    if (!wlan)
        return;

    memset(&info, 0, sizeof(struct rt_wlan_info));
    buff.data = &info;
    buff.len = sizeof(struct rt_wlan_info);
    rt_memcpy(info.bssid, bssid->octet, sizeof(wmhd_mac_t));
    rt_wlan_dev_indicate_event_handle(wlan, event, &buff);
}

static void rthw_wifi_ap_conn_cb(wmhd_mac_t *mac)
{
    rthw_wifi_ap_client_event(wlan_ap, RT_WLAN_DEV_EVT_AP_ASSOCIATED, mac);
}

static void rthw_wifi_ap_disc_cb(wmhd_mac_t *mac)
{
    rthw_wifi_ap_client_event(wlan_ap, RT_WLAN_DEV_EVT_AP_DISASSOCIATED, mac);
}

void rthw_wifi_ap_callback(int event, struct rt_wlan_buff *buff, void *parameter)
{
    wlan_ap = parameter;
    wmhd_softap_register_client_callback(rthw_wifi_ap_conn_cb, rthw_wifi_ap_disc_cb);
}

int rthw_wifi_rssi_get(void)
{
    int rssi = 0;
        rssi = wmhd_sta_get_rssi();
    return rssi;
}

void rthw_wifi_channel_set(int interface, int channel)
{
    wmhd_wifi_set_channel(interface, channel);
}

int rthw_wifi_channel_get(int interface)
{
    uint32_t channel;
        wmhd_wifi_get_channel(interface, &channel);
    return channel;
}

static rt_wlan_security_t security_map_from_wmhd(int security)
{
    int result = SECURITY_OPEN;

    switch (security) {
    case WMHD_SECURE_OPEN:
        result = SECURITY_OPEN;
        break;
    case WMHD_WEP_OPEN:
        result = SECURITY_WEP_PSK;
        break;
    case WMHD_WEP_SHARED:
        result = SECURITY_WEP_SHARED;
        break;
    case WMHD_WPA_PSK_TKIP:
        result = SECURITY_WPA_TKIP_PSK;
        break;
    case WMHD_WPA_PSK_AES:
        result = SECURITY_WPA_AES_PSK;
        break;
    case WMHD_WPA2_PSK_AES:
        result = SECURITY_WPA2_AES_PSK;
        break;
    case WMHD_WPA2_PSK_TKIP:
        result = SECURITY_WPA2_TKIP_PSK;
        break;
    case WMHD_WPA2_PSK_MIXED:
        result = SECURITY_WPA2_MIXED_PSK;
        break;
    case WMHD_WPA2_PSK_SHA256:
        result = SECURITY_WPA2_SHA256_PSK;
        break;
    case WMHD_WPA2_WPA_PSK:
        result = SECURITY_WPA2_WPA_PSK;
        break;
    case WMHD_WPA3_PSK_SAE:
        result = SECURITY_WPA3_SAE;
        break;
    case WMHD_WPA3_WPA2_PSK:
        result = SECURITY_WPA3_WPA2_PSK;
        break;
    case WMHD_WPS_OPEN:
        result = SECURITY_WPS_OPEN;
        break;
    case WMHD_WPS_AES:
        result = SECURITY_WPS_SECURE;
        break;
    case WMHD_WPA_ENT_AES:
        result = SECURITY_WPA_AES_ENT;
        break;
    case WMHD_WPA_ENT_TKIP:
        result = SECURITY_WPA_TKIP_ENT;
        break;
    case WMHD_WPA_ENT_MIXED:
        result = SECURITY_WPA_MIXED_ENT;
        break;
    case WMHD_WPA2_ENT_AES:
        result = SECURITY_WPA2_AES_ENT;
        break;
    case WMHD_WPA2_ENT_TKIP:
        result = SECURITY_WPA2_TKIP_ENT;
        break;
    case WMHD_WPA2_ENT_MIXED:
        result = SECURITY_WPA2_MIXED_ENT;
        break;
    case WMHD_WPA3_ENT:
        result = SECURITY_WPA3_ENT;
        break;
    case WMHD_WPA3_OWE:
        result = SECURITY_WPA3_OWE;
        break;
    default:
        result = -1;
        break;
    }

    return result;
}

void rthw_scanresult_cb(int event, struct rt_wlan_buff *buff, void *parameter)
{
    if (event == RT_WLAN_EVT_SCAN_REPORT)
    {
    }
}

int rthw_wifi_scan_stop(void)
{
#if 0
    if (wmhd_stop_scan() != 0)
    {
        return -RT_ERROR;
    }
    else
        return RT_EOK;
#else
        return RT_EOK;
#endif
}

static void rthw_wifi_scan_report(wmhd_ap_info_t *results)
{
    int len;

    if (results == NULL) // COMPLETED or ABORTED
        return;

    memset(&info, 0, sizeof(struct rt_wlan_info));
    len = strlen(results[0].ssid);
    if (len >= 32)
        len = 32;
    #if 1 // Hidden SSID to print out
    if (len == 0) {
        sprintf(results[0].ssid, "[HIDDEN SSID]");
        len = strlen(results[0].ssid);
    }
    #endif

    info.ssid.len = len;
    memcpy(info.ssid.val, results[0].ssid, len);
    memcpy(info.bssid, results[0].bssid, 6);
    info.channel = results[0].channel;
    info.rssi = results[0].rssi;
    info.datarate = results[0].data_rate * 1000;
    info.security = security_map_from_wmhd(results[0].security);
    buff.data = &info;
    buff.len = sizeof(struct rt_wlan_info);
    rt_wlan_dev_indicate_event_handle(wlan_sta, RT_WLAN_DEV_EVT_SCAN_REPORT,
                                    &buff);
}

int rthw_wifi_scan(void *content, struct rt_scan_info *info)
{
    struct rt_wlan_device *wlan = (struct rt_wlan_device *)content;
    struct rt_wmhd_wifi *wifi = (struct rt_wmhd_wifi *)(wlan->user_data);

    wlan_sta = wifi->wlan;

    #ifdef RT_WLAN_JOIN_SCAN_BY_MGNT
    if (info) {
        wmhd_ssid_t ssid;
        memset(&scan_ap_data, 0, sizeof(wmhd_ap_info_t));
        memset(&ssid, 0, sizeof(wmhd_ssid_t));
        memcpy(ssid.value, info->ssid.val, info->ssid.len);
        ssid.length = info->ssid.len;
        wmhd_scan_ap_ext(&ssid, NULL, NULL, rthw_wifi_scan_report, &scan_ap_data);
    } else
    #endif
    {
        wmhd_scan_ap(rthw_wifi_scan_report, &scan_ap_data);
    }

    rt_wlan_dev_indicate_event_handle(wlan, RT_WLAN_DEV_EVT_SCAN_DONE, RT_NULL);

    return 0;
}

void rthw_wifi_monitor_enable(int enable)
{
    if (enable)
    {
        wmhd_wifi_set_raw_packet_processor(rthw_wlan_monitor_callback);
        wmhd_enable_monitor_mode();
    }
    else
    {
        wmhd_disable_monitor_mode();
        wmhd_wifi_set_raw_packet_processor(NULL);
    }
}

int rthw_wifi_set_powersave_enable(int enable)
{
    int time_ms = 0;
    if (enable == 2)
        time_ms = 200;
    if (wmhd_sta_set_powersave(enable, time_ms) != 0) {
        return -RT_ERROR;
    }

    return RT_EOK;
}

int rthw_wifi_get_powersave_mode(void)
{
    uint8_t mode, time_ms;
    wmhd_sta_get_powersave(&mode, &time_ms);
    return mode;
}

void rthw_wifi_country_set(rt_country_code_t country_code)
{
    wmhd_set_country_code(country_code);
}

rt_country_code_t rthw_wifi_country_get(void)
{
    rt_country_code_t country_code = RT_COUNTRY_UNKNOWN;
    uint32_t ccode;
    //rt_country_code_t is different with WMHD driver type, so must rewrite a new version
    wmhd_get_country_code(&ccode);
    return country_code;
}

int rthw_wifi_mac_set(rt_uint8_t mac[], int interface)
{
    wmhd_mac_t wmhd_mac;
    memcpy(wmhd_mac.octet, mac, 6);
    return wmhd_set_mac_address(wmhd_mac);
}

int rthw_wifi_mac_get(rt_uint8_t mac[], int interface)
{
    wmhd_mac_t wmhd_mac;
    if (wmhd_get_mac_address(&wmhd_mac) == 0)
    {
        memcpy(mac, wmhd_mac.octet, 6);
        return 0;
    }
    return -1;
}
#endif
