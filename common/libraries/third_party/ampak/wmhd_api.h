/*
 * Copyright (c) 2024-2025 Ampak Technology Inc.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/** 
**********************************************************************************
* @file       wmhd_api.h
* @brief      Wireless Minimum Host Driver Application Programming Interface
* @author     Cloud.Chiu   
* @date       2024-12-2
* @version    V1.0
* @copyright  Copyright (c) 2024-2025 Ampak Technology Inc.
**********************************************************************************
*/ 

#ifndef INCLUDED_WMHD_API_H
#define INCLUDED_WMHD_API_H

#include <stdint.h>

/*! Make a Country Code */
#define WMHD_MK_CNTRY(a, b)          (((unsigned char)(a)) + (((unsigned char)(b)) << 8))

/** 
 * @brief  Wi-Fi Module GPIO Type
 */
typedef enum {
    WL_REG_ON = 0,      /**< Wi-Fi Module Power Control      */
    WL_HW_OOB = 1   /**< Wi-Fi Module Interrupt Control  */
} wmhd_gpio_type_t;

/** 
 * @brief  Wi-Fi Frequency Band Type
 */
typedef enum {
    WMHD_802_11_BAND_2_4GHZ = 0, /**< Denotes 2.4GHz radio band  */
    WMHD_802_11_BAND_5GHZ,       /**< Denotes 5GHz radio band    */
    WMHD_802_11_BAND_6GHZ,       /**< Denotes 6GHz radio band    */
    WMHD_802_11_BAND_UNKNOWN,    /**< Denotes unknown radio band */
} wmhd_802_11_band_t;

/** 
 * @brief  Wi-Fi Station Security Type
 */
typedef enum {
    WMHD_SECURE_OPEN = 0,        // OPEN
    WMHD_WPA_PSK_AES,            // WPA-PSK AES
    WMHD_WPA2_PSK_AES,           // WPA2-PSK AES
    WMHD_WEP_OPEN,               // WEP+OPEN
    WMHD_WEP_SHARED,             // WEP+SHARE
    WMHD_WPA_PSK_TKIP,           // WPA-PSK TKIP
    WMHD_WPA_PSK_MIXED,          // WPA-PSK AES & TKIP MIXED
    WMHD_WPA2_PSK_TKIP,          // WPA2-PSK TKIP
    WMHD_WPA2_PSK_MIXED,         // WPA2-PSK AES & TKIP MIXED
    WMHD_WPA2_WPA_PSK,           // WPA2/WPA-PSK AES & TKIP MIXED
    WMHD_WPA2_PSK_SHA256,        // WPA2-PSK-SHA256
    WMHD_WPA3_PSK_SAE,           // WPA3-PSK SAE
    WMHD_WPA3_WPA2_PSK,          // WPA3 SAE & WPA2-PSK AES
        WMHD_WPA3_OWE,               // WPA3 OWE
    WMHD_WPS_OPEN,               // WPS OPEN, NOT supported
    WMHD_WPS_AES,                // WPS AES, NOT supported
    WMHD_IBSS_OPEN,              // ADHOC, NOT supported
    WMHD_WPA_ENT_AES,            // WPA-ENT AES, NOT supported
    WMHD_WPA_ENT_TKIP,           // WPA-ENT TKIP, NOT supported
    WMHD_WPA_ENT_MIXED,          // WPA-ENT AES & TKIP MIXED, NOT supported
    WMHD_WPA2_ENT_AES,           // WPA2-ENT AES, NOT supported
    WMHD_WPA2_ENT_TKIP,          // WPA2-ENT TKIP, NOT supported
    WMHD_WPA2_ENT_MIXED,         // WPA2-ENT AES & TKIP MIXED, NOT supported
    WMHD_WPA2_WPA_ENT,           // WPA2/WPA-ENT AES & TKIP MIXED, NOT supported
    WMHD_WPA3_ENT,
    WMHD_SECURITY_AUTO = 99,     // MHD auto select security
    WMHD_SECURITY_MAX = 0x7f,    // force host_security_t type to 8bits
    WMHD_SECURITY_UNKNOWN = -1   // Unknown security type
} wmhd_sta_security_t;

/** 
 * @brief  Wi-Fi SoftAP Security Type
 */
typedef enum {
    WMHD_AP_OPEN = 0,            // 0 OPEN
    WMHD_AP_WPA_AES_PSK,         // 1 WPA-PSK AES
    WMHD_AP_WPA2_AES_PSK,        // 2 WPA2-PSK AES
    WMHD_AP_WEP_OPEN,            // 3 WEP+OPEN
    WMHD_AP_WEP_SHARED,          // 4 WEP+SHARE
    WMHD_AP_WPA_TKIP_PSK,        // 5 WPA-PSK TKIP
    WMHD_AP_WPA_MIXED_PSK,       // 6 WPA-PSK AES & TKIP MIXED
    WMHD_AP_WPA2_TKIP_PSK,       // 7 WPA2-PSK TKIP
    WMHD_AP_WPA2_MIXED_PSK,      // 8 WPA2-PSK AES & TKIP MIXED
    WMHD_AP_WPA3_WPA2_PSK,       // 9 WPA3 & WPA2 AES
    WMHD_AP_WPA3_SAE,            //10 WPA3 SAE
    WMHD_AP_WPS_OPEN,            //11 WPS OPEN, NOT supported
    WMHD_AP_WPS_AES,             //12 WPS AES, NOT supported
    WMHD_AP_WPA2_WPA_AES_PSK,    //13 WPA2/WPA-PSK AES
    WMHD_AP_WPA2_WPA_TKIP_PSK,   //14 WPA2/WPA-PSK TKIP
    WMHD_AP_WPA2_WPA_MIXED_PSK,  //15 WPA2/WPA-PSK AES & TKIP MIXED
} wmhd_ap_security_t;

/** 
 * @brief  SSID information
 */
typedef struct {
    uint8_t length;     /**< SSID length         */
        uint8_t value[32];      /**< SSID name (AP name) */
} wmhd_ssid_t;

/** 
 * @brief  MAC address information
 */
typedef struct {
    uint8_t octet[6];  /**< Unique 6-byte MAC address */
} wmhd_mac_t;

/** 
 * @brief  Scan AP information
 */
typedef struct {
    char ssid[32];
    char bssid[6];
    uint8_t reserved[2];
    uint32_t channel;
    uint32_t security;
    uint32_t rssi;
    uint32_t data_rate;
    char ccode[4];
    uint8_t band;
    uint8_t mfp;
    uint8_t reserved2[2];
} wmhd_ap_info_t;

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * @brief      Configuration Host GPIO to connect Wi-Fi Module
 * @note       It must be used before wmhd_module_init()
 * @param[in]  type            Wi-Fi Module GPIO type
 *                             WL_REG_ON: Enable/Disable and Reset Wi-Fi gpio control
 *                             WL_HW_OOB: Interruption notification from Wi-Fi Module
 * @param[in]  port            Host GPIO port number
 * @param[in]  pin             Host GPIO pin number
 */
extern void wmhd_gpio_config(uint8_t type, uint32_t port, uint32_t pin);

/** 
 * @brief      It is called before the sdio driver initialization, RT-Thread must use it, others doesn't need it.
 * @return     Zero on success, others on error
 */
extern void wmhd_wlregon_reset(void);

/** 
 * @brief      Configuration Host SDIO base address
 * @note       It must be used before wmhd_module_init(), and using non RT-Thread RTOS
 * @param[in]  sdio_base[]     SDIO base address table lists
 * @param[in]  num             SDIO total slot number
 */
extern void wmhd_sdio_config(void* sdio_base[], uint8_t num);

/** 
 * @brief      Select SDIO slot and setting maximum SDIO clock
 * @note       It must be used before wmhd_module_init(), It can limit maximum SDIO clock
 * @param[in]  index           SDIO slot index if platform support it
 * @param[in]  clock           SDIO clock
 */
extern void wmhd_sdio_set_slot_and_maxclk(uint8_t index, uint32_t clock);

/** 
 * @brief      Configuration thread priority and stack size
 * @param[in]  type            Thread type
 *                             0: MHD thread
 *                             1: MHD workqueue thread
 * @param[in]  priority        Thread priority
 * @param[in]  stack_size      Thread stack size
 */
extern void wmhd_thread_config(uint8_t type, uint32_t priority, uint32_t stack_size);

/** 
 * @brief      Set Country Code
 * @note       It must be used before wmhd_module_init()
 * @param[in]  country         Set country code by using WMHD_MK_CNTRY MACRO to generate it
 */
extern void wmhd_set_country_code(uint32_t country);

/** 
 * @brief      Get Country Code
 * @param[out] country         Get country code on current
 */
extern void wmhd_get_country_code(uint32_t* country);

/** 
 * @brief      Initial Wireless Minimum Host Driver to Enable Wi-Fi Module device
 * @return     Zero on success, others on error
 */
extern int wmhd_module_init(void);

/** 
 * @brief      Uninitial Wireless Minimum Host Driver to Disable Wi-Fi Module device
 * @return     Zero on success, others on error
 */
extern int wmhd_module_exit(void);

/** 
 * @brief      It be used to trigger out of band interrupt event to running SDIO data read/write check.
 * @note       If there is a problem of stuck when transferring big data for a long time, 
 *             It maybe due to an lost interruption. You can call this function to confirm or solve the problem.
 *             It only support the OOB(GPIO) interrupt type design.
 */
extern void wmhd_host_oob_isr(void);

/** 
 * @brief      It be used to trigger SDIO interrupt event to running SDIO data read/write check.
 * @note       If there is a problem of stuck when transferring big data for a long time, 
 *             It maybe due to an lost interruption. You can call this function to confirm or solve the problem.
 *             It only support the SDIO(D1) interrupt type design.
 */
extern void wmhd_host_sdio_isr(void);

/** 
 * @brief      Get the MAC Address
 * @param[out] mac             Get the MAC Address of the Wi-Fi device
 * @return     Zero on success, others on error
 */
extern int wmhd_get_mac_address(wmhd_mac_t *mac);

/** 
 * @brief      Set the MAC Address
 * @param[out] mac             Set the MAC Address of the Wi-Fi device
 * @return     Zero on success, others on error
 */
extern int wmhd_set_mac_address( wmhd_mac_t mac );

/** 
 * @brief      Scan Wireless Access Point device lists
 * @param[out] ap_info         Information data of AP lists  
 * @param[out] num             Scan to get the number of AP lists 
 * @return     Zero on success, others on error
 */
extern int wmhd_scan_aplist(wmhd_ap_info_t *ap_info, int *num);

typedef void (*wmhd_scan_report_cb_t)(wmhd_ap_info_t *ap_info);

/** 
 * @brief      Scan Wireless Access Point device lists using call back function
 * @param[in]  report_cb       Scan report call back function
 * @param[out] ap_info         Information data of AP 
 * @return     Zero on success, others on error
 */
extern int wmhd_scan_ap(wmhd_scan_report_cb_t report_cb, wmhd_ap_info_t *ap_info);

/** 
 * @brief      Scan specified target Wireless Access Point device using call back function
 * @param[in]  ssid            Scan specified ssid device
 * @param[in]  bssid           Scan specified bssid device
 * @param[in]  channel_list    Only scan specified channel list, default use NULL to scan all channel
 * @param[in]  report_cb       Scan report call back function
 * @param[out] ap_info         Information data of AP 
 * @return     Zero on success, others on error
 */
extern int wmhd_scan_ap_ext(wmhd_ssid_t *ssid, wmhd_mac_t *bssid, uint16_t *channel_list, 
                            wmhd_scan_report_cb_t scan_report_cb, wmhd_ap_info_t* scan_report_param);

/** 
 * @brief      Connect Wireless Access Point and binding Network Interface
 * @param[in]  ssid            SSID name of Wireless Access Point
 * @param[in]  bssid           BSSID of Wireless Access Point, default use NULL to scan it then connect
 * @param[in]  security        Security type of Wireless Access Point, use WMHD_SECURITY_AUTO to scan it then connect
 * @param[in]  password        Password of Wireless Access Point
 * @param[in]  channel         Channel of Wireless Access Point, use 0 to scan it then connect
 * @return     Zero on success, others on error
 */
extern int wmhd_sta_connect(char *ssid, char *bssid, wmhd_sta_security_t security, char *password, uint8_t channel);

/** 
 * @brief      Disconnect Wireless Access Point and unbinding Network Interface
 * @return     Zero on success, others on error
 */
extern int wmhd_sta_disconnect(void);

/** 
 * @brief      Connect Wireless Access Point no binding Network Interface
 * @param[in]  ssid            SSID name of Wireless Access Point
 * @param[in]  password        Password of Wireless Access Point
 * @return     Zero on success, others on error
 */
extern int wmhd_join_ap(char *ssid, char *password);

/** 
 * @brief      Disconnect Wireless Access Point
 * @return     Zero on success, others on error
 */
extern int wmhd_leave_ap(void);

/** 
 * @brief      Set network ip address on Network Interface
 * @param[in]  ip              IP address, DHCP: 0; Fixed IP: 192.168.10.1 --> 0xC0A80A01
 * @param[in]  gateway         Gateway IP address
 * @param[in]  netmask         Netmask IP address
 * @return     Zero on success, others on error
 */
extern int wmhd_sta_network_up(uint32_t ip, uint32_t gateway, uint32_t netmask);

/** 
 * @brief      Remove network ip address on Network Interface
 * @return     Zero on success, others on error
 */
extern int wmhd_sta_network_down(void);

typedef void (*wmhd_link_cb_t)(void);

/** 
 * @brief      Register connection call back function
 * @param[in]  link_up_cb      Link up call back function
 * @param[in]  link_down_cb    Link down call back function
 * @return     Zero on success, others on error
 */
extern int wmhd_sta_register_link_callback(wmhd_link_cb_t link_up_cb, wmhd_link_cb_t link_down_cb);

/** 
 * @brief      Deregister connection call back function
 * @param[in]  link_up_cb      Link up call back function
 * @param[in]  link_down_cb    Link down call back function
 * @return     Zero on success, others on error
 */
extern int wmhd_sta_deregister_link_callback(wmhd_link_cb_t link_up_cb, wmhd_link_cb_t link_down_cb);

/** 
 * @brief      Get connection status
 * @return     0: Disconnected, 1: Connected, others: Failed
 */
extern int wmhd_sta_get_connection(void);

/** 
 * @brief      Get connection SSID
 * @param[out] ssid_data       SSID name string 
 * @return     Zero on success, others on error
 */
extern int wmhd_sta_get_ssid(char ssid_data[]);

/** 
 * @brief      Get connection BSSID
 * @param[out] mac_addr        BSSID mac address 
 * @return     Zero on success, others on error
 */
extern int wmhd_sta_get_bssid(char mac_addr[]);

/** 
 * @brief      Get connection RSSI
 * @return     0xffff: error, others: rssi
 */
extern int wmhd_sta_get_rssi(void);

/** 
 * @brief      Get connection Data rate
 * @return     -1: error, others: rate*2 (return value is not real rate)
 */
extern int wmhd_sta_get_rate(void);

/** 
 * @brief      Get connection Noise
 * @return     Noise value
 */
extern int wmhd_sta_get_noise(void);

/** 
 * @brief      Get IPv4 IP Address
 * @return     IP address
 */
extern uint32_t wmhd_sta_ipv4_ipaddr(void);

/** 
 * @brief      Get IPv4 Gateway Address
 * @return     Gateway address
 */
extern uint32_t wmhd_sta_ipv4_gateway(void);

/** 
 * @brief      Get IPv4 Netmask Address
 * @return     Netmask address
 */
extern uint32_t wmhd_sta_ipv4_netmask(void);

/** 
 * @brief      Set Wi-Fi power saving mode.
 * @note       When there is no data for Wi-Fi, it will go into power saving mode automatically to save power. 
 *             Suggest setting fast power saving mode.
 * @param[in]  mode            Power saving mode
 *                                         0: no power saving mode
 *                                         1: IEEE80211 power saving mode
 *                                         2: fast power saving mode. Normally mode will be 2.
 * @param[in]  time_ms         Configure how long should go into power saving mode if no data traffic.
 *                             This parameter works only when mode = 2. Suggest 200 msec.
 * @return     Zero on success, others on error
 */
extern int wmhd_sta_set_powersave(uint8_t mode, uint8_t time_ms);

/** 
 * @brief      Get Wi-Fi power saving mode.
 * @param[out] mode            Power saving mode
 *                                         0: no power saving mode
 *                                         1: IEEE80211 power saving mode
 *                                         2: fast power saving mode.
 * @param[out] time_ms         When mode = 2, this value indicates how long should go into
 *                             power saving mode if no data traffic.
 * @return     Zero on success, others on error
 */
extern int wmhd_sta_get_powersave(uint8_t *mode, uint8_t *time_ms);

/** 
 * @brief      Set Beacon Listen DTIM
 * @param[in]  dtim            DTIM value 
 * @return     Zero on success, others on error
 */
extern int wmhd_sta_set_bcn_li_dtim(uint8_t dtim);

/** 
 * @brief      Get Beacon Listen DTIM
 * @return     DTIM value
 */
extern int wmhd_sta_get_bcn_li_dtim(void);

/** 
 * @brief      Set DTIM Interval
 * @param[in]  interval_ms     DTIM Interval value 
 * @return     Zero on success, others on error
 */
extern int wmhd_sta_set_dtim_interval(int interval_ms);

/** 
 * @brief      Set Wi-Fi mac address for host device bring up
 * @param[out] mac             Set the MAC Address of the Wi-Fi device
 * @return     Zero on success, others on error
 */
extern void wmhd_host_set_mac_address(wmhd_mac_t mac);

/** 
 * @brief      Get Wi-Fi mac address for host device bring up
 * @param[out] mac             Get the MAC Address of the Wi-Fi device
 * @return     Zero on success, others on error
 */
extern int wmhd_host_get_mac_address(wmhd_mac_t *mac);

/** 
 * @brief      Create a Soft Access Point device
 * @param[in]  ssid            SSID name of Wireless Access Point, less than 32 bytes
 * @param[in]  password        Password of Wireless Access Point, less than 32 bytes
 * @param[in]  security        Security type of Wireless Access Point
 * @param[in]  channel         Channel of Wireless Access Point
 * @return     Zero on success, others on error
 */
extern int wmhd_softap_start(char *ssid, char *password, wmhd_ap_security_t security, uint8_t channel);

/** 
 * @brief      Create a Soft Access Point device and setting network ip address
 * @param[in]  ssid            SSID name of Wireless Access Point, less than 32 bytes
 * @param[in]  password        Password of Wireless Access Point, less than 32 bytes
 * @param[in]  security        Security type of Wireless Access Point
 * @param[in]  channel         Channel of Wireless Access Point
 * @param[in]  ip_addr         IP Address of Network interface
 * @param[in]  net_mask        Netmask Address of Network interface
 * @param[in]  gateway         Gateway Address of Network interface
 * @return     Zero on success, others on error
 */
extern int wmhd_softap_start_ex(char *ssid, char *password, wmhd_ap_security_t security, uint8_t channel, 
                                                                uint32_t ip_addr, uint32_t net_mask, uint32_t gateway);

/** 
 * @brief      Delete a Soft Access Point device and remove network interface
 * @return     Zero on success, others on error
 */
extern int wmhd_softap_stop(void);

/** 
 * @brief      Start a DHCP Server Daemon on Wi-Fi Module and setting IP address of Network Interface
 * @return     Zero on success, others on error
 */
extern int wmhd_softap_start_dhcpd(uint32_t ip_address);

/** 
 * @brief      Stop a DHCP Server Daemon on Wi-Fi Module
 * @return     Zero on success, others on error
 */
extern int wmhd_softap_stop_dhcpd(void);

/** 
 * @brief      Enable/Disable hidden SSID of SoftAP 
 * @param[in]  enable          0: disable hidden SSID (default); 1: enable hidden SSID
 * @return     Zero on success, others on error
 */
extern int wmhd_softap_set_hidden(uint8_t enable);

/** 
 * @brief      Getting SoftAP hidden mode is enable or disable 
 * @return     0: disable hidden SSID (default); 1: enable hidden SSID, others on error
 */
extern int wmhd_softap_get_hidden(void);

/** 
 * @brief      Get the MAC address list of SoftAP connection
 * @param[out] mac_list         MAC address list of SoftAP connection
 * @param[out] count            Number of SoftAP connections
 * @return     Zero on success, others on error
 */
extern int wmhd_softap_get_mac_list(wmhd_mac_t *mac_list, uint32_t *count);

/** 
 * @brief      Get the RSSI of SoftAP connection
 * @param[in]  mac              MAC address of SoftAP connection
 * @return     0xffff: error, others: rssi
 */
extern int wmhd_softap_get_rssi(wmhd_mac_t *mac);

/** 
 * @brief      Disconnect the SoftAP connection
 * @param[in]  mac              MAC address of SoftAP connection
 * @return     Zero on success, others on error
 */
extern int wmhd_softap_deauth_assoc_sta(wmhd_mac_t *mac);

typedef void (*wmhd_client_cb_t)(wmhd_mac_t *);

/** 
 * @brief      Register the SoftAP call back function
 * @param[in]  assoc_cb        Client association call back function
 * @param[in]  disassoc_cb     Client disassociation call back function
 * @return     Zero on success, others on error
 */
extern int wmhd_softap_register_client_callback(wmhd_client_cb_t assoc_cb, wmhd_client_cb_t disassoc_cb);

/** 
 * @brief      Set the maximum associations number of SoftAP
 * @param[in]  max_assoc       the maximum associations number of SoftAP
 * @return     Zero on success, others on error
 */
extern int wmhd_wifi_set_max_associations(uint32_t max_assoc);

/** 
 * @brief      Get the maximum associations number of SoftAP
 * @param[in]  max_assoc       the maximum associations number of SoftAP
 * @return     Zero on success, others on error
 */
extern int wmhd_wifi_get_max_associations(uint32_t *max_assoc);

/** 
 * @brief      Set the channel number of interface
 * @param[in]  interface       0: Station interface; 1: SoftAP interface
 * @param[in]  channel         Channel Number
 * @return     Zero on success, others on error
 */
extern int wmhd_wifi_set_channel(int interface, uint32_t channel);

/** 
 * @brief      Get the channel number of interface
 * @param[in]  interface       0: Station interface; 1: SoftAP interface
 * @param[in]  channel         Channel Number
 * @return     Zero on success, others on error
 */
extern int wmhd_wifi_get_channel(int interface, uint32_t *channel);

/** 
 * @brief      Enable Monitor Mode
 * @return     Zero on success, others on error
 */
extern int wmhd_enable_monitor_mode(void);

/** 
 * @brief      Disable Monitor Mode
 * @return     Zero on success, others on error
 */
extern int wmhd_disable_monitor_mode(void);

typedef void (*wmhd_packet_cb_t)(void *buffer, int interface);

/** 
 * @brief      Set call back function of Monitor Mode
 * @param[in]  function        Call back function
 * @return     Zero on success, others on error
 */
extern int wmhd_wifi_set_raw_packet_processor(wmhd_packet_cb_t function);

/** 
 * @brief      Set call back function of Network interface for  data receive
 * @param[in]  function        Call back function
 * @return     Zero on success, others on error
 */
extern void wmhd_set_netif_rx_callback(wmhd_packet_cb_t function);

/** 
 * @brief      Enable/Disable Wi-Fi Firmware log for debug using
 * @param[in]  enable          0: disable fw log; 1: enable fw log
 * @param[in]  interval        Interval frequency with millisecond
 * @return     Zero on success, others on error
 */
extern int wmhd_config_fwlog(uint8_t enable, uint32_t interval);

/** 
 * @brief      Loading WiFi Firmware information into driver initialion
 * @param[in]  target          Wi-Fi Firmware information table
 * @param[in]  fw_num          Total number of supported wireless modules
 */
extern void wmhd_wlan_fw_load(void **target, uint8_t fw_num);

/** 
 * @brief      Loading WiFi NVRAM information into driver initialion
 * @param[in]  target          Wi-Fi NVRAM information table
 * @param[in]  nv_num          Total number of supported wireless modules
 */
extern void wmhd_wlan_nv_load(void **target, uint8_t nv_num);

/** 
 * @brief      Assign Network interface for driver control
 * @param[in]  netif           Current Network Interface
 * @param[in]  interface       0: Station interface; 1: SoftAP interface
 * @return     NULL on error, others for current netif
 */
extern void* wmhd_ext_netif(void *netif, uint8_t interface);


extern int wmhd_network_xmit_intf(uint8_t interface, void* packet);

/** 
 * @brief      Send packet into Network interface
 * @param[in]  netif           Network Interface
 * @param[in]  packet          Network Packet Data
 * @return     Zero on success, others on error
 */
extern int wmhd_network_xmit_packet(void *netif, void *packet);
extern int wmhd_network_xmit_data(void *netif, void* buff, int len);


//WIFI Test Using
/** 
 * @brief      Wi-Fi feature commands
 * @param[in]  argc            The number of arguments entered on the command line 
 * @param[in]  argv            Array of pointers pointing to an array of character objects
 * @return     Zero on success, others on error
 */
extern int wmhd_wifi_commands(uint32_t argc, char **argv);

/** 
 * @brief      Wi-Fi Test commands
 * @param[in]  argc            The number of arguments entered on the command line 
 * @param[in]  argv            Array of pointers pointing to an array of character objects
 * @return     Zero on success, others on error
 */
extern int wmhd_wl_cmds(uint32_t argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif /* ifndef INCLUDED_MHD_API_H */
