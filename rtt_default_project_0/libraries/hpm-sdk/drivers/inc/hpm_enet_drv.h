/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_ENET_DRV_H
#define HPM_ENET_DRV_H

/*---------------------------------------------------------------------*
 * Includes
 *---------------------------------------------------------------------*/
#include "hpm_common.h"
#include "hpm_enet_regs.h"
#include "hpm_soc_feature.h"
/*---------------------------------------------------------------------*
 *  Macro Constant Declarations
 *---------------------------------------------------------------------*/
#define ENET_MAX_FRAME_SIZE       (1524U)  /*!< ENET_HEADER + ENET_EXTRA + VLAN_TAG + MAX_ENET_PAYLOAD + ENET_CRC */
#define ENET_HEADER               (14U)    /*!< 6-byte Dest addr, 6-byte Src addr, 2-byte type */
#define ENET_EXTRA                (2U)     /*!< Extra bytes in some cases */
#define ENET_VLAN_TAG             (4U)     /*!< optional 802.1q VLAN Tag */
#define ENET_CRC                  (4U)     /*!< Ethernet CRC */
#define ENET_MIN_PAYLOAD          (46U)    /*!< Minimum Ethernet payload size */
#define ENET_MAX_PAYLOAD          (1500U)  /*!< Maximum Ethernet payload size */
#define ENET_JUMBO_FRAME_PAYLOAD  (9000U)  /*!< Jumbo frame payload size */

/* ETHERNET errors */
#define  ENET_ERROR               (0)
#define  ENET_SUCCESS             (1)

/*---------------------------------------------------------------------*
 *  Typedef Enum Declarations
 *---------------------------------------------------------------------*/
typedef enum {
    enet_pbl_1  = 1,
    enet_pbl_2  = 2,
    enet_pbl_4  = 4,
    enet_pbl_8  = 8,
    enet_pbl_16 = 16,
    enet_pbl_32 = 32
} enet_pbl_t;

typedef enum {
    enet_cic_bypass = 0,
    enet_cic_insert_ipv4_header,
    enet_cic_insert_tcp_udp_icmp,
    enet_cic_insert_tcp_upd_icmp,
} enet_insert_t;

typedef enum {
    enet_phy_op_read = 0,
    enet_phy_op_write
} enet_phy_op_t;

typedef enum {
    enet_phy_idle = 0,
    enet_phy_busy
} enet_phy_status_t;

typedef enum {
    enet_csr_60m_to_100m_mdc_csr_div_42 = 0,
    enet_csr_100m_to_150m_mdc_csr_div_62,
    enet_csr_20m_to_35m_mdc_csr_div_16,
    enet_csr_35m_to_60m_mdc_csr_div_26,
    enet_csr_150m_to_250m_mdc_csr_div_102,
    enet_csr_250m_to_300m_mdc_csr_div_124,

    enet_csr_60m_to_100m_mdc_csr_div_4 = 8,
    enet_csr_60m_to_100m_mdc_csr_div_6,
    enet_csr_60m_to_100m_mdc_csr_div_8,
    enet_csr_60m_to_100m_mdc_csr_div_10,
    enet_csr_60m_to_100m_mdc_csr_div_12,
    enet_csr_60m_to_100m_mdc_csr_div_14,
    enet_csr_60m_to_100m_mdc_csr_div_16,
    enet_csr_60m_to_100m_mdc_csr_div_18
} enet_csr_clk_range_t;

typedef enum {
    enet_inf_rmii = 4,
    enet_inf_rgmii = 1
} enet_inf_type_t;

/*---------------------------------------------------------------------*
 *  Typedef Struct Declarations
 *---------------------------------------------------------------------*/
typedef struct {
    uint32_t buffer;
    uint32_t count;
    uint16_t size;
} enet_buff_config_t;

typedef struct {
    uint32_t mac_addr_high[ENET_SOC_ADDR_MAX_COUNT];
    uint32_t mac_addr_low[ENET_SOC_ADDR_MAX_COUNT];
    uint8_t  valid_max_count;
} enet_mac_config_t;

typedef struct {
    union {
        uint32_t tdes0;
        struct {
            uint32_t db:   1; /* Deferred Bit*/
            uint32_t uf:   1; /* Underflow Error */
            uint32_t ed:   1; /* Excessive Deferral */
            uint32_t cc:   4; /* Collision Count */
            uint32_t vf:   1; /* VLAN Frame */
            uint32_t ec:   1; /* Excessive Collision */
            uint32_t lc:   1; /* Late Collision */
            uint32_t nc:   1; /* No Carrier */
            uint32_t loc:  1; /* Loss of Carrier */
            uint32_t ipe:  1; /* IP Payload Error */
            uint32_t ff:   1; /* Frame Flushed */
            uint32_t jt:   1; /* Jabber Timeout */
            uint32_t es:   1; /* Error Summary */
            uint32_t ihe:  1; /* IP Header Error */
            uint32_t ttss: 1; /* Transmit Timestamp Status */
            uint32_t vlic: 2; /* VLAN Insertion Control */
            uint32_t tch:  1; /* Second Address Chained */
            uint32_t ter:  1; /* Transmit End of Ring */
            uint32_t cic:  2; /* Checksum Insertion Control */
            uint32_t crcr: 1; /* CRC Replacement Control */
            uint32_t ttse: 1; /* Transmit Timestamp Enable */
            uint32_t dp:   1; /* Disable Pad */
            uint32_t dc:   1; /* Disable CRC */
            uint32_t fs:   1; /* First Segment */
            uint32_t ls:   1; /* Last Segment */
            uint32_t ic:   1; /* Interrupt on Completion */
            uint32_t own:  1; /* Own Bit */
        } tdes0_bm;
    };

    union {
        uint32_t tdes1;
        struct {
            uint32_t tbs1: 13; /* Transmit Buffer 1 Size */
            uint32_t     :  3; /* Reserved */
            uint32_t tbs2: 13; /* Transmit Buffer 2 Size */
            uint32_t saic:  3; /* SA Inertion Control */
        } tdes1_bm;
    };

    union {
        uint32_t tdes2;
        struct {
             uint32_t buffer1;
        } tdes2_bm;
    };

    union {
        uint32_t tdes3;
        union {
            uint32_t buffer2;
            uint32_t next_desc;
        } tdes3_bm;
    };

    struct {
        uint32_t reserved;
    } tdes4_bm;

#if ENET_SOC_ALT_EHD_DES_LEN == 8
    struct {
        uint32_t reserved;
    } tdes5_bm;

    struct {
        uint32_t ttsl;  /* Transmit Frame Timestamp Low */
    } tdes6_bm;

    struct {
        uint32_t ttsh;  /* Transmit Frame Timestamp High */
    } tdes7_bm;
#endif
} enet_tx_desc_t;

typedef struct
{
    union {
        uint32_t rdes0;

        struct {
                uint32_t ex_sta_rx_addr      : 1;  /* Extended Status Available or Rx MAC Address*/
                uint32_t ce                  : 1;  /* CRC Error */
                uint32_t dbe                 : 1;  /* Dribble Bit Error */
                uint32_t re                  : 1;  /* Receive Error */
                uint32_t rwt                 : 1;  /* Receive Watchdog Timeout */
                uint32_t ft                  : 1;  /* Frame Type */
                uint32_t lc                  : 1;  /* Late Collision */
                uint32_t ts_ip_gf            : 1;  /* Timestamp Available, IP Checksum Error or Giant Frame*/
                uint32_t ls                  : 1;  /* Last Descriptor */
                uint32_t fs                  : 1;  /* First Descriptor */
                uint32_t vlan                : 1;  /* VLAN Tag */
                uint32_t oe                  : 1;  /* Overflow Error */
                uint32_t le                  : 1;  /* Length Error */
                uint32_t saf                 : 1;  /* Source Address Filter Fail */
                uint32_t dse                 : 1;  /* Descriptor Error */
                uint32_t es                  : 1;  /* Error Summary */
                uint32_t fl                  : 14; /* Frame Length */
                uint32_t afm                 : 1;  /* Destination Address Filter Fail */
                uint32_t own                 : 1;  /* Own Bit */
        } rdes0_bm;
    };

    union {
        uint32_t rdes1;
        struct {
            uint32_t rbs1 : 13; /* Receive Buffer 1 Size */
            uint32_t      : 1;  /* Reserved */
            uint32_t rch  : 1;  /* Second Address Chained */
            uint32_t rer  : 1;  /* Receive End of Ring */
            uint32_t rbs2 : 13; /* Receive Buffer 2 Size */
            uint32_t      : 2;  /* Reserved */
            uint32_t dic  : 1;  /* Disable Interrupt on Completion */
        } rdes1_bm;
    };

    union {
        uint32_t rdes2;
        struct {
        uint32_t buffer1;   /* Buffer 1 Address Pointer */
        } rdes2_bm;
    };

    union {
        uint32_t rdes3;
        union {
            uint32_t buffer2;   /* Buffer 2 Address Pointer */
            uint32_t next_desc; /* Next Descriptor Address */
        } rdes3_bm;
    };

    union {
        uint32_t rdes4;
        struct {
                uint32_t ip_payload_type     : 3; /* IP Payload Type */
                uint32_t ip_header_err       : 1; /* IP Header Error */
                uint32_t ip_payload_err      : 1; /* IP Payload Error */
                uint32_t ip_chksum_bypassed  : 1; /* IP Checksum Bypassed */
                uint32_t ipv4_pkt_received   : 1; /* IPv4 Packet Received */
                uint32_t ipv6_pkt_received   : 1; /* IPv6 Packet Received */
                uint32_t msg_type            : 4; /* Message Type */
                uint32_t ptp_frame_type      : 1; /* PTP Frame Type */
                uint32_t ptp_version         : 1; /* PTP Version */
                uint32_t ts_dp               : 1; /* Timestamp Dropped */
                uint32_t reserved0           : 1; /* Reserved */
                uint32_t av_pkt_recv         : 1; /* AV Packet Received */
                uint32_t av_tagged_pkt_recv  : 1; /* AV Tagged Packet Received */
                uint32_t vlan_tag_pri_value  : 3; /* VLAN Tag Priority Value */
                uint32_t reserved1                : 3; /* Reserved */
                uint32_t l3_fm               : 1; /* Layer 3 Filter Matched */
                uint32_t l4_fm               : 1; /* Layer 4 Filter Matched */
                uint32_t l3_l4_fnl           : 2; /* Layer 3 and Layer 4 Filter Number Matched */
                uint32_t reserved2           : 4; /* Reserved */
            } rdes4_bm;
    };


#if ENET_SOC_ALT_EHD_DES_LEN == 8
    struct {
        uint32_t reserved;
    } rdes5_bm;

    struct {
        uint32_t rtsl;  /* Receive Frame Timestamp Low */
    }rdes6_bm;

    struct {
        uint32_t rtsh;  /* Receive Frame Timestamp High */
    } rdes7_bm;
#endif
} enet_rx_desc_t;

typedef struct{
    uint32_t length;
    uint32_t buffer;
    enet_rx_desc_t *rx_desc;
} enet_frame_t;

typedef struct  {
    enet_rx_desc_t *fs_rx_desc;
    enet_rx_desc_t *ls_rx_desc;
    uint32_t  seg_count;
} enet_rx_frame_info_t;

typedef struct {
    enet_tx_desc_t *tx_desc_list_head;
    enet_rx_desc_t *rx_desc_list_head;
    enet_tx_desc_t *tx_desc_list_cur;
    enet_rx_desc_t *rx_desc_list_cur;
    enet_buff_config_t tx_buff_cfg;
    enet_buff_config_t rx_buff_cfg;
    enet_rx_frame_info_t rx_frame_info;
} enet_desc_t;

/*
 *  @brief  Bit definition of TDES1
 */
#define ENET_DMATxDesc_TBS2  ((uint32_t)0x1FFF0000)  /*!< Transmit Buffer2 Size */
#define ENET_DMATxDesc_TBS1  ((uint32_t)0x00001FFF)  /*!< Transmit Buffer1 Size */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
/*---------------------------------------------------------------------*
 * Exported Functions
 *---------------------------------------------------------------------*/
int enet_controller_init(ENET_Type *ptr, enet_inf_type_t inf_type, enet_desc_t *desc, enet_mac_config_t *config, uint32_t intr);
uint16_t enet_read_phy(ENET_Type *ptr, uint32_t phy_addr, uint32_t addr);
void  enet_write_phy(ENET_Type *ptr, uint32_t phy_addr, uint32_t addr, uint32_t data);
void  enet_transmit(ENET_Type *ptr, enet_desc_t *desc, uint16_t len);
void  enet_receive(ENET_Type *ptr, enet_desc_t *desc);
uint32_t enet_check_received_frame(enet_rx_desc_t **parent_rx_desc_list_cur, enet_rx_frame_info_t *rx_frame_info);
enet_frame_t enet_get_received_frame(enet_rx_desc_t **parent_rx_desc_list_cur, enet_rx_frame_info_t *rx_frame_info);
enet_frame_t enet_get_received_frame_interrupt(enet_rx_desc_t **parent_rx_desc_list_cur, enet_rx_frame_info_t *rx_frame_info, uint32_t rx_desc_count);
uint32_t enet_prepare_transmit_descriptor(ENET_Type *ptr, uint16_t frame_length, uint16_t tx_buff_size);
uint32_t enet_prepare_transmit_descriptors(ENET_Type *ptr, enet_tx_desc_t **parent_tx_desc_list_cur, uint16_t frame_length, uint16_t tx_buff_size);
void enet_dma_tx_desc_chain_init(ENET_Type *ptr, enet_desc_t *desc);
void enet_dma_rx_desc_chain_init(ENET_Type *ptr,  enet_desc_t *desc);
void enet_dma_flush(ENET_Type *ptr);
#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* HPM_ENET_DRV_H */
