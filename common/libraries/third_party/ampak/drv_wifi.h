/*
 * File      : drv_wifi.h
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


#ifndef __DRV_WIFI_H__
#define __DRV_WIFI_H__

#include <netif/ethernetif.h>

#define MAX_ADDR_LEN          (6)

typedef enum
{
    STA_INTERFACE = 0,
    AP_INTERFACE  = 1,
    MAX_INTERFACE
} wifi_interface_t;

struct rt_wmhd_wifi
{
#ifdef RT_USING_WIFI
    struct rt_wlan_device *wlan;
#else //RT_USING_WIFI
#ifdef RT_USING_NETDEV
    struct eth_device ethif;
#endif //RT_USING_NETDEV
#endif //RT_USING_WIFI
    rt_uint8_t dev_addr[MAX_ADDR_LEN];
    //rt_country_code_t country;
    rt_uint32_t country;
    rt_uint32_t flag;
    int connected;
    int type;
};

#ifdef RT_USING_WIFI
//#include "netif.h"
#include <netif/ethernetif.h>
#include <lwip/netifapi.h>
//copy it from wlan_lwip.c
struct lwip_prot_des
{
    struct rt_wlan_prot prot;
    struct eth_device eth;
    rt_int8_t connected_flag;
    struct rt_timer timer;
    struct rt_work work;
};
#endif

void rthw_wlan_monitor_callback(void* buf, int interface);
int rt_wmhd_wifi_config(void);

#endif /* __DRV_WIFI_H__ */

