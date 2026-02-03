/*
 * File      : drv_wifi.c
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

#include <rtthread.h>
#include <rthw.h>
#include <rtdef.h>
#include <string.h>

#include "hwconfig.h"
#include "drv_wlan.h"
#include "drv_wifi.h"

#ifdef RT_USING_WIFI
#include <dev_wlan.h>
#include <dev_wlan_prot.h>
#endif

#ifdef RT_USING_NETDEV
#include <netdev.h>
#endif

#define WIFI_COUNTRY_CODE     WMHD_MK_CNTRY( 'C', 'N' )

#if defined(RT_USING_WIFI) || defined(RT_USING_NETDEV)
static struct rt_wmhd_wifi wmhd_dev[MAX_INTERFACE] =
{
    [STA_INTERFACE] = 
    {
        .type    = STA_INTERFACE,
        .country = WIFI_COUNTRY_CODE,
    },
    [AP_INTERFACE] = 
    {
        .type    = AP_INTERFACE,
        .country = WIFI_COUNTRY_CODE,
    }
};
#endif

#if !defined(RT_USING_WIFI) && defined(RT_USING_NETDEV)
static rt_err_t rthw_ethif_init(rt_device_t dev)
{
    struct rt_wmhd_wifi *wmhd = (struct rt_wmhd_wifi *)dev;
    struct eth_device *ethif = &wmhd->ethif;
    struct netif *netif = ethif->netif;
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    wmhd_ext_netif(netif, wmhd->type);
    return RT_EOK;
}

static rt_err_t rthw_ethif_open(rt_device_t dev, rt_uint16_t oflag)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    return RT_EOK;
}

static rt_err_t rthw_ethif_close(rt_device_t dev)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    return RT_EOK;
}

static rt_ssize_t rthw_ethif_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    rt_set_errno(-RT_ENOSYS);
    return RT_EOK;
}

static rt_ssize_t rthw_ethif_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    rt_set_errno(-RT_ENOSYS);
    return RT_EOK;
}

static rt_err_t rthw_ethif_control(rt_device_t dev, int cmd, void *args)
{
    struct rt_wmhd_wifi *wmhd = (struct rt_wmhd_wifi *)dev;
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    switch(cmd)
    {
        case NIOCTL_GADDR:
            /* get mac address */
            wmhd_get_mac_address((wmhd_mac_t*)wmhd->dev_addr);
            if(args) rt_memcpy(args, wmhd_dev[STA_INTERFACE].dev_addr, 6);
            else return -RT_ERROR;
            break;
        default :
            break;
    }

    return RT_EOK;
}

rt_err_t rthw_ethif_tx( rt_device_t dev, struct pbuf* p)
{
    struct rt_wmhd_wifi *wmhd = (struct rt_wmhd_wifi *)dev;
    struct eth_device *ethif = &wmhd->ethif;
    struct netif *netif = ethif->netif;
    struct pbuf *q;
    
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    for (q = p; q != NULL; q = q->next)
    {
        rthw_wifi_send(netif, wmhd->type, q, 0);
    }

    return RT_EOK;
}

/* reception packet. */
struct pbuf *rthw_ethif_rx(rt_device_t dev)
{
    struct pbuf* p = NULL;
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    //Not supported yet
    return p;
}
#endif //RT_USING_NETDEV

#ifdef RT_USING_NETDEV
void rthw_netdev_status_change_notify(struct netdev *netdev, enum netdev_cb_type type)
{
#ifdef RT_USING_WIFI
    struct netif *netif = (struct netif*)netdev->user_data;
    struct eth_device *dev = (struct eth_device*)netif->state;
    struct rt_wlan_device *wlan = dev->parent.user_data;
#endif
    LOG_D("F:%s type=%d", __FUNCTION__, type);

    if (type == NETDEV_CB_STATUS_LINK_UP)
    {
#ifdef RT_USING_WIFI
        rt_wlan_dev_indicate_event_handle(wlan, RT_WLAN_DEV_EVT_CONNECT, RT_NULL);
#endif
    }
    else if (type == NETDEV_CB_STATUS_LINK_DOWN)
    {
#ifdef RT_USING_WIFI
        rt_wlan_dev_indicate_event_handle(wlan, RT_WLAN_DEV_EVT_DISCONNECT, RT_NULL);
#endif
    }
    else if (type == NETDEV_CB_STATUS_UP)
    {
    }
}

#ifdef NETDEV_USING_LINK_STATUS_CALLBACK
void netdev_status_change(struct netdev *netdev, enum netdev_cb_type type)
{
    rthw_netdev_status_change_notify(netdev, type);
}
#endif

void rthw_netdev_addr_notify(struct netdev *netdev, enum netdev_cb_type type)
{
    LOG_D("%s: netdev=%X, type=%d", __FUNCTION__, netdev, type);
}

void rthw_netif_link_callback(struct netif *netif)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
}

void rthw_netdev_register_notify(struct netdev *netdev, enum netdev_cb_type type)
{
    LOG_D("%s: type=%d", __FUNCTION__, type);
    if (type == NETDEV_CB_REGISTER)
    {
        struct netif *netif = (struct netif*)netdev->user_data;
#ifdef RT_USING_WIFI
        struct eth_device *dev = (struct eth_device*)netif->state;
        struct rt_wlan_device *wlan = dev->parent.user_data;

        if (wlan->mode == RT_WLAN_STATION)
            wmhd_ext_netif(netif, STA_INTERFACE);
        else
            wmhd_ext_netif(netif, AP_INTERFACE);
#endif
        netdev_set_status_callback(netdev, rthw_netdev_status_change_notify);
        netdev_set_addr_callback(netdev, rthw_netdev_addr_notify);
        netif_set_link_callback(netif, rthw_netif_link_callback);
    }
}
#endif

#ifdef RT_USING_WIFI
static const struct rt_wlan_dev_ops wmhd_wlan_ops;
void rt_wlan_set_netif(rt_wlan_mode_t mode)
{
#if (RTTHREAD_VERSION >= RT_VERSION_CHECK(5, 0, 0)) && !defined(RT_USING_NETDEV) || \
    (RTTHREAD_VERSION <  RT_VERSION_CHECK(5, 0, 0))
    struct rt_wlan_device *wlan = wmhd_dev[mode-1].wlan;
    struct lwip_prot_des *lwip_prot = wlan->prot;
    struct eth_device *eth = &lwip_prot->eth;
    struct netif *netif = eth->netif;
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    wmhd_ext_netif(netif, mode-1);
#endif
}

static int security_map_from_rtthread(rt_wlan_security_t security)
{
    int result = WMHD_SECURE_OPEN;

    switch (security)
    {
    case SECURITY_OPEN:
        result = WMHD_SECURE_OPEN;
        break;
    case SECURITY_WEP_PSK:
        result = WMHD_WEP_OPEN;
        break;
    case SECURITY_WEP_SHARED:
        result = WMHD_WEP_SHARED;
        break;
    case SECURITY_WPA_TKIP_PSK:
        result = WMHD_WPA_PSK_TKIP;
        break;
    case SECURITY_WPA_AES_PSK:
        result = WMHD_WPA_PSK_AES;
        break;
    case SECURITY_WPA2_AES_PSK:
        result = WMHD_WPA2_PSK_AES;
        break;
    case SECURITY_WPA2_TKIP_PSK:
        result = WMHD_WPA2_PSK_TKIP;
        break;
    case SECURITY_WPA2_MIXED_PSK:
        result = WMHD_WPA2_PSK_MIXED;
        break;
    case SECURITY_WPA2_SHA256_PSK:
        result = WMHD_WPA2_PSK_SHA256;
        break;
    case SECURITY_WPA3_SAE:
        result = WMHD_WPA3_PSK_SAE;
        break;
    case SECURITY_WPS_OPEN:
        result = WMHD_WPS_OPEN;
        break;
    case SECURITY_WPS_SECURE:
        result = WMHD_WPS_AES;
        break;
    case SECURITY_UNKNOWN:
    default:
        result = WMHD_SECURITY_AUTO;
        break;
    }

    return result;
}

void rthw_wlan_monitor_callback(void* buf, int interface)
{
    struct rt_wlan_device *wlan = NULL;
    struct pbuf *p = buf;

    if (interface != 0 && interface != 1)
        return;

    wlan = wmhd_dev[interface].wlan;
    rt_wlan_dev_promisc_handler(wlan, p->payload, p->len);
    pbuf_free(p);
}

static rt_err_t rthw_wlan_init(struct rt_wlan_device *wlan)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    return rthw_wifi_init();
}

static rt_err_t rthw_wlan_mode(struct rt_wlan_device *wlan, rt_wlan_mode_t mode)
{
    struct rt_wmhd_wifi *wifi = (struct rt_wmhd_wifi *)(wlan->user_data);

    LOG_D("F:%s L:%d mode:%d", __FUNCTION__, __LINE__, mode);

    if (mode == RT_WLAN_STATION)
    {
        if (wifi->type != STA_INTERFACE)
        {
            LOG_D("this wlan not support sta mode");
            return -RT_ERROR;
        }
    }
    else if (mode == RT_WLAN_AP)
    {
        if (wifi->type != AP_INTERFACE)
        {
            LOG_D("this wlan not support ap mode");
            return -RT_ERROR;
        }
    }

    return RT_EOK;
}

static rt_err_t rthw_wlan_scan(struct rt_wlan_device *wlan, struct rt_scan_info *scan_info)
{
    struct rt_wmhd_wifi *wifi = (struct rt_wmhd_wifi *)(wlan->user_data);

    if (wifi->type != STA_INTERFACE)
    {
        LOG_E("this wlan not support scan mode");
        return -RT_ERROR;
    }

    rthw_wifi_scan((void *)wlan, scan_info);
    return RT_EOK;
}

static rt_err_t rthw_wlan_join(struct rt_wlan_device *wlan, struct rt_sta_info *sta_info)
{
    struct rt_wmhd_wifi *wifi = (struct rt_wmhd_wifi *)(wlan->user_data);
    int result = 0, i;
    char *ssid = RT_NULL, *key = RT_NULL;

    if (wifi->type != STA_INTERFACE)
    {
        LOG_E("this wlan not support sta mode");
        return -RT_ERROR;
    }

    for (i = 0; i < RT_WLAN_BSSID_MAX_LENGTH; i++)
    {
        if (sta_info->bssid[i] != 0xff || sta_info->bssid[i] != 0x00)
            break;
    }

    if (i < RT_WLAN_BSSID_MAX_LENGTH && sta_info->channel != 0)
    {
        if (sta_info->ssid.len > 0)
            ssid = (char*)&sta_info->ssid.val[0];
        if (sta_info->key.len > 0)
            key = (char*)&sta_info->key.val[0];
        LOG_D("bssid connect bssid: %02x:%02x:%02x:%02x:%02x:%02x ssid:%s ssid_len:%d key:%s key_len%d",
        sta_info->bssid[0],sta_info->bssid[1],sta_info->bssid[2],sta_info->bssid[3],sta_info->bssid[4],sta_info->bssid[5],
        ssid, sta_info->ssid.len, key, sta_info->key.len);
        result = rthw_wifi_connect_bssid((char*)sta_info->bssid, ssid, sta_info->ssid.len, key, sta_info->key.len, security_map_from_rtthread(sta_info->security), sta_info->channel);
    }
    else
    {
        LOG_D("ssid %s, key_len %d, key %s i %d", sta_info->ssid.val, sta_info->key.len, sta_info->key.val, i);
        if (sta_info->key.len == 0)
            sta_info->security = SECURITY_OPEN;
        else if (sta_info->key.len >= 8)
            sta_info->security = SECURITY_UNKNOWN; //using scan to get security type
        result = rthw_wifi_connect((char*)sta_info->ssid.val, sta_info->ssid.len, (char*)sta_info->key.val, sta_info->key.len, security_map_from_rtthread(sta_info->security));     
    }

    if (result == 0)
    {
        wifi->connected = 1;
#if !defined(RT_USING_NETDEV)
        rt_wlan_dev_indicate_event_handle(wifi->wlan, RT_WLAN_DEV_EVT_CONNECT, RT_NULL);
#endif
    }
    else
    {
        rt_wlan_dev_indicate_event_handle(wifi->wlan, RT_WLAN_DEV_EVT_CONNECT_FAIL, RT_NULL);
    }

    if (result != 0)
    {
        LOG_E("connect failed...");
        return -RT_ERROR;
    }
#if (RTTHREAD_VERSION >= RT_VERSION_CHECK(5, 0, 0)) && !defined(RT_WLAN_PROT_LWIP_ENABLE)
    else
    {
        rthw_wifi_network_up();
    }
#endif

    return RT_EOK;
}

static rt_err_t rthw_wlan_softap(struct rt_wlan_device *wlan, struct rt_ap_info *ap_info)
{
    struct rt_wmhd_wifi *wifi = (struct rt_wmhd_wifi *)(wlan->user_data);

    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    if (wifi->type != AP_INTERFACE)
    {
        LOG_E("this wlan not support ap mode");
        return -RT_ERROR;
    } else if (wifi->connected)
    {
        LOG_I("ap running!"); //rt_wlan_start_ap_adv check has problem      
        rt_wlan_dev_indicate_event_handle(wifi->wlan, RT_WLAN_DEV_EVT_AP_START, RT_NULL);
        return RT_EOK;
    }

#if (RTTHREAD_VERSION >= RT_VERSION_CHECK(5, 0, 0)) && defined(RT_WLAN_MANAGE_ENABLE) || \
    (RTTHREAD_VERSION <  RT_VERSION_CHECK(5, 0, 0))
    rt_wlan_register_event_handler(RT_WLAN_EVT_AP_START, rthw_wifi_ap_callback, wifi->wlan);
#endif

    if (rthw_wifi_ap_start((char*)ap_info->ssid.val, (char*)ap_info->key.val, 
        security_map_from_rtthread(ap_info->security), ap_info->channel) != 0)
    {
        rt_wlan_dev_indicate_event_handle(wifi->wlan, RT_WLAN_DEV_EVT_AP_STOP, RT_NULL);
        wifi->connected = 0;
        return -RT_ERROR;
    }
    rt_wlan_dev_indicate_event_handle(wifi->wlan, RT_WLAN_DEV_EVT_AP_START, RT_NULL);
    wifi->connected = 1;
    return RT_EOK;
}

static rt_err_t rthw_wlan_disconnect(struct rt_wlan_device *wlan)
{
    struct rt_wmhd_wifi *wifi = (struct rt_wmhd_wifi *)(wlan->user_data);

    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    if (wifi->type != STA_INTERFACE)
    {
        LOG_E("this wlan not support sta mode");
        return -RT_ERROR;
    }

#if (RTTHREAD_VERSION >= RT_VERSION_CHECK(5, 0, 0)) && !defined(RT_WLAN_PROT_LWIP_ENABLE)
    rthw_wifi_network_down();
#endif

    wifi->connected = 0;
    rthw_wifi_disconnect();
    rt_wlan_dev_indicate_event_handle(wifi->wlan, RT_WLAN_DEV_EVT_DISCONNECT, RT_NULL);

    return RT_EOK;
}

static rt_err_t rthw_wlan_ap_stop(struct rt_wlan_device *wlan)
{
    struct rt_wmhd_wifi *wifi = (struct rt_wmhd_wifi *)(wlan->user_data);

    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    if (wifi->type != AP_INTERFACE)
    {
        LOG_E("this wlan not support ap mode");
        return -RT_ERROR;
    }

    rthw_wifi_ap_disconnect();
    rt_wlan_dev_indicate_event_handle(wifi->wlan, RT_WLAN_DEV_EVT_AP_STOP, RT_NULL);
    wifi->connected = 0;
    return RT_EOK;
}

static rt_err_t rthw_wlan_ap_deauth(struct rt_wlan_device *wlan, rt_uint8_t mac[])
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    return RT_EOK;
}

static rt_err_t rthw_wlan_scan_stop(struct rt_wlan_device *wlan)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    if (rthw_wifi_scan_stop() == 0)
        return RT_EOK;
    else
        return -RT_ERROR;
}

static int rthw_wlan_get_rssi(struct rt_wlan_device *wlan)
{
    struct rt_wmhd_wifi *wifi = (struct rt_wmhd_wifi *)(wlan->user_data);

    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    if (wifi->type != STA_INTERFACE)
    {
        LOG_E("this wlan not support sta mode");
        return -RT_ERROR;
    }

    return rthw_wifi_rssi_get();
}

static rt_err_t rthw_wlan_set_powersave(struct rt_wlan_device *wlan, int level)
{
    struct rt_wmhd_wifi *wifi = (struct rt_wmhd_wifi *)(wlan->user_data);

    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    if (wifi->type != STA_INTERFACE)
    {
        LOG_E("this wlan not support sta mode");
        return -RT_ERROR;
    }

    return rthw_wifi_set_powersave_enable(level);
}

static int rthw_wlan_get_powersave(struct rt_wlan_device *wlan)
{
    struct rt_wmhd_wifi *wifi = (struct rt_wmhd_wifi *)(wlan->user_data);

    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);

    if (wifi->type != STA_INTERFACE)
    {
        LOG_E("this wlan not support sta mode");
        return -RT_ERROR;
    }

    return rthw_wifi_get_powersave_mode();
}

static rt_err_t rthw_wlan_cfg_promisc(struct rt_wlan_device *wlan, rt_bool_t start)
{
    LOG_E("F:%s L:%d enable %d \n", __FUNCTION__, __LINE__, start);

    if (start)
        rthw_wifi_monitor_enable(1);
    else
        rthw_wifi_monitor_enable(0);

    return RT_EOK;
}

static rt_err_t rthw_wlan_cfg_filter(struct rt_wlan_device *wlan, struct rt_wlan_filter *filter)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    return RT_EOK;
}

static rt_err_t rthw_wlan_set_channel(struct rt_wlan_device *wlan, int channel)
{
    struct rt_wmhd_wifi *wifi = (struct rt_wmhd_wifi *)(wlan->user_data);

    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    rthw_wifi_channel_set(wifi->type, channel);

    return RT_EOK;
}

static int rthw_wlan_get_channel(struct rt_wlan_device *wlan)
{
    struct rt_wmhd_wifi *wifi = (struct rt_wmhd_wifi *)(wlan->user_data);
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    return rthw_wifi_channel_get(wifi->type);
}

static rt_err_t rthw_wlan_set_country(struct rt_wlan_device *wlan, rt_country_code_t country_code)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    rthw_wifi_country_set(country_code);
    return RT_EOK;
}

static rt_country_code_t rthw_wlan_get_country(struct rt_wlan_device *wlan)
{
    return rthw_wifi_country_get();
}

static rt_err_t rthw_wlan_set_mac(struct rt_wlan_device *wlan, rt_uint8_t mac[])
{
    struct rt_wmhd_wifi *wifi = (struct rt_wmhd_wifi *)wlan->user_data;

    if (rthw_wifi_mac_set(mac, wifi->type) == 0)
    {
        LOG_I("interface %d mac: %02x-%02x-%02x-%02x-%02x-%02x", wifi->type, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        return RT_EOK;
    }

    return -RT_ERROR;
}

static rt_err_t rthw_wlan_get_mac(struct rt_wlan_device *wlan, rt_uint8_t mac[])
{
    struct rt_wmhd_wifi *wifi = (struct rt_wmhd_wifi *)wlan->user_data;
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    if (mac == RT_NULL)
    {
        return -RT_ERROR;
    }

    if (rthw_wifi_mac_get(mac, wifi->type) == 0)
    {
        LOG_I("interface %d mac: %02x-%02x-%02x-%02x-%02x-%02x", wifi->type, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        return RT_EOK;
    }

    return -RT_ERROR;
}

static int rthw_wlan_recv(struct rt_wlan_device *wlan, void *buff, int len)
{
    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    return RT_EOK;
}

static int rthw_wlan_send(struct rt_wlan_device *wlan, void *buff, int len)
{
    struct rt_wmhd_wifi *wifi = (struct rt_wmhd_wifi *)wlan->user_data;
#ifdef RT_USING_NETDEV
    struct netdev *netdev = wlan->netdev;
    struct netif *netif = (struct netif *)(netdev->user_data);
#else
    struct lwip_prot_des *lwip_prot = wlan->prot;
    struct eth_device *eth = &lwip_prot->eth;
    struct netif *netif = eth->netif;
#endif

    LOG_D("F:%s L:%d", __FUNCTION__, __LINE__);
    if (!wifi->connected)
    {
        return RT_EOK;
    }
#ifdef RT_WLAN_PROT_LWIP_PBUF_FORCE
    rthw_wifi_send(netif, wifi->type, buff, 0);
#else
    rthw_wifi_send(netif, wifi->type, buff, len);
#endif
    return RT_EOK;
}

static const struct rt_wlan_dev_ops wmhd_wlan_ops =
{
    .wlan_init             =     rthw_wlan_init,
    .wlan_mode             =     rthw_wlan_mode,
    .wlan_scan             =     rthw_wlan_scan,
    .wlan_join             =     rthw_wlan_join,
    .wlan_disconnect       =     rthw_wlan_disconnect,
    .wlan_softap           =     rthw_wlan_softap,
    .wlan_ap_stop          =     rthw_wlan_ap_stop,
    .wlan_ap_deauth        =     rthw_wlan_ap_deauth,
    .wlan_scan_stop        =     rthw_wlan_scan_stop,
    .wlan_get_rssi         =     rthw_wlan_get_rssi,
    .wlan_set_powersave    =     rthw_wlan_set_powersave,
    .wlan_get_powersave    =     rthw_wlan_get_powersave,
    .wlan_cfg_promisc      =     rthw_wlan_cfg_promisc,
    .wlan_cfg_filter       =     rthw_wlan_cfg_filter,
    .wlan_set_channel      =     rthw_wlan_set_channel,
    .wlan_get_channel      =     rthw_wlan_get_channel,
    .wlan_set_country      =     rthw_wlan_set_country,
    .wlan_get_country      =     rthw_wlan_get_country,
    .wlan_set_mac          =     rthw_wlan_set_mac,
    .wlan_get_mac          =     rthw_wlan_get_mac,
    .wlan_recv             =     rthw_wlan_recv,
    .wlan_send             =     rthw_wlan_send,
#if RTTHREAD_VERSION >= RT_VERSION_CHECK(5, 0, 0)
    .wlan_cfg_mgnt_filter  =     NULL,
    .wlan_send_raw_frame   =     NULL,
    .wlan_get_fast_info    =     NULL,
    .wlan_fast_connect     =     NULL,
#endif
};
#else
#ifdef RT_USING_NETDEV
#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops wmhd_dev_ops =
{
    .init    = rthw_ethif_init,
    .open    = rthw_ethif_open,
    .close   = rthw_ethif_close,
    .read    = rthw_ethif_read,
    .write   = rthw_ethif_write,
    .control = rthw_ethif_control
};
#endif //RT_USING_DEVICE_OPS
#endif //RT_USING_NETDEV
#endif //RT_USING_WIFI

#ifdef RT_USING_WIFI
int rt_wmhd_init_wlan(struct rt_wmhd_wifi *wmhd_wlan, const char *dev_name)
{
    rt_err_t ret = RT_EOK;
    if (wmhd_wlan->wlan == NULL)
    {
        wmhd_wlan->wlan = malloc(sizeof(struct rt_wlan_device));
        if (wmhd_wlan->wlan != NULL)
        {
            memset(wmhd_wlan->wlan, 0, sizeof(struct rt_wlan_device));
            ret = rt_wlan_dev_register(wmhd_wlan->wlan, dev_name, &wmhd_wlan_ops, 0, wmhd_wlan);
#ifdef RT_USING_NETDEV
            if (ret == RT_EOK)
                netdev_set_register_callback(rthw_netdev_register_notify);
#endif
        }
        else
            ret = RT_ENOMEM;
    }
    return ret;
}
#else //RT_USING_WIFI
#ifdef RT_USING_NETDEV
int rt_wmhd_init_ethif(struct rt_wmhd_wifi *wmhd_wlan, char *ifname)
{
#ifdef RT_USING_DEVICE_OPS
    wmhd_wlan->ethif.parent.ops          = &wmhd_dev_ops;
#else
    wmhd_wlan->ethif.parent.init         = rthw_ethif_init;
    wmhd_wlan->ethif.parent.open         = rthw_ethif_open;
    wmhd_wlan->ethif.parent.close        = rthw_ethif_close;
    wmhd_wlan->ethif.parent.read         = rthw_ethif_read;
    wmhd_wlan->ethif.parent.write        = rthw_ethif_write;
    wmhd_wlan->ethif.parent.control      = rthw_ethif_control;
#endif
    wmhd_wlan->ethif.parent.user_data    = wmhd_wlan;
    wmhd_wlan->ethif.eth_rx              = rthw_ethif_rx;
    wmhd_wlan->ethif.eth_tx              = rthw_ethif_tx;
    eth_device_init(&(wmhd_wlan->ethif), ifname);
    return 0;
}
#endif //RT_USING_NETDEV
#endif //RT_USING_WIFI

int rt_wmhd_wifi_init(void)
{
    rt_thread_mdelay(1000);
#ifdef RT_USING_MHD
#ifdef RT_USING_WIFI
    rt_wmhd_init_wlan(&wmhd_dev[STA_INTERFACE], RT_WLAN_DEVICE_STA_NAME);
    rt_wmhd_init_wlan(&wmhd_dev[AP_INTERFACE],  RT_WLAN_DEVICE_AP_NAME);
#else
    rthw_wifi_init();
#ifdef RT_USING_NETDEV
    rt_wmhd_init_ethif(&wmhd_dev[STA_INTERFACE], "w0");
    rt_wmhd_init_ethif(&wmhd_dev[AP_INTERFACE],  "w1");
#endif //RT_USING_NETDEV
#endif //RT_USING_WIFI
#endif //RT_USING_MHD
    return 0;
}
#ifdef RT_USING_WIFI
INIT_DEVICE_EXPORT(rt_wmhd_wifi_init); //if using RT_USING_WIFI
#endif

int rt_wmhd_wifi_config(void)
{
    uint32_t regon_port, regon_pin, hwake_port, hwake_pin;
#ifdef RT_WIFI_WL_REGON_PIN
    rt_base_t regon_gpio;
#endif
#ifdef RT_WIFI_WL_HWAKE_PIN
    rt_base_t hwake_gpio;
#endif
#ifdef RT_WIFI_WL_REGON_PIN
    regon_gpio = rt_pin_get(RT_WIFI_WL_REGON_PIN);
    regon_port = (regon_gpio >> 5);
    regon_pin  = (regon_gpio & 0x1F);
#else
    regon_port = WL_REGON_PORT;
    regon_pin  = WL_REGON_PIN;
#endif
#ifdef RT_WIFI_WL_HWAKE_PIN
    hwake_gpio = rt_pin_get(RT_WIFI_WL_HWAKE_PIN);
    hwake_port = (hwake_gpio >> 5);
    hwake_pin  = (hwake_gpio & 0x1F);
#else
    hwake_port = WL_HWOOB_PORT;
    hwake_pin  = WL_HWOOB_PIN;
#endif
    wmhd_gpio_config(WL_REG_ON, regon_port, regon_pin); //WL_REGON
    wmhd_gpio_config(WL_HW_OOB, hwake_port, hwake_pin); //WL_HWOOB
    wmhd_wlregon_reset();
    //wmhd_sdio_set_slot_and_maxclk(0, 25000000);
    //wmhd_thread_config(0, RT_MHD_THREAD_PRIORITY, RT_MHD_THREAD_STACKSIZE);
    //wmhd_set_country_code(WMHD_MK_CNTRY( 'C', 'N' ));
    //wmhd_network_set_hostname("my_device");
    //wmhd_log_msg_level(0x7fffff);
    return 0;
}
INIT_PREV_EXPORT(rt_wmhd_wifi_config);


int rt_app_wifi_set_mode(void)
{
#ifdef RT_WLAN_MANAGE_ENABLE
    rt_wlan_set_mode(RT_WLAN_DEVICE_STA_NAME, RT_WLAN_STATION);
    rt_wlan_set_mode(RT_WLAN_DEVICE_AP_NAME, RT_WLAN_AP);
#endif
    return RT_EOK;
}
INIT_APP_EXPORT(rt_app_wifi_set_mode);
