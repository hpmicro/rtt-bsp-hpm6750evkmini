/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_CAN_DRV_H
#define HPM_CAN_DRV_H

#include "hpm_common.h"
#include "hpm_can_regs.h"

/***********************************************************************************************************************
 *
 * Definitions
 *
 **********************************************************************************************************************/

/**
 * @brief CAN error codes
 */
enum {
    status_can_bit_error = MAKE_STATUS(status_group_can, 0),
    status_can_form_error = MAKE_STATUS(status_group_can, 1),
    status_can_stuff_error = MAKE_STATUS(status_group_can, 2),
    status_can_ack_error = MAKE_STATUS(status_group_can, 3),
    status_can_crc_error = MAKE_STATUS(status_group_can, 4),
    status_can_other_error = MAKE_STATUS(status_group_can, 5),
};

/**
 * @brief CAN Event definitions
 */
#define CAN_EVENT_RECEIVE (CAN_RTIF_RIF_MASK)
#define CAN_EVENT_RX_BUF_OVERRUN (CAN_RTIF_ROIF_MASK)
#define CAN_EVENT_RX_BUF_FULL (CAN_RTIF_RFIF_MASK)
#define CAN_EVENT_RX_BUF_ALMOST_FULL (CAN_RTIF_RAFIF_MASK)
#define CAN_EVENT_TX_PRIMARY_BUF (CAN_RTIF_TPIF_MASK)
#define CAN_EVENT_TX_SECONDARY_BUF (CAN_RTIF_TSIF_MASK)
#define CAN_EVENT_ERROR (CAN_RTIF_EIF_MASK)
#define CAN_EVENT_ABORT (CAN_RTIF_AIF_MASK)


/**
 * @brief CAN loopback types
 */
typedef enum _can_loopback_mode {
    can_loopback_none,
    can_loopback_internal,
    can_loopback_external,
} can_loopback_mode_t;

/**
 * @brief CAN bit timing options
 */
typedef enum _can_bit_timing_option {
    can_bit_timing_can2_0,
    can_bit_timing_canfd_norminal,
    can_bit_timing_canfd_data,
} can_bit_timing_option_t;

/**
 * @brief CAN DLC definitions
 */
enum {
    can_payload_size_0 = 0,
    can_payload_size_1,
    can_payload_size_2,
    can_payload_size_3,
    can_payload_size_4,
    can_payload_size_5,
    can_payload_size_6,
    can_payload_size_7,
    can_payload_size_8,
    can_payload_size_12,
    can_payload_size_16,
    can_payload_size_20,
    can_payload_size_24,
    can_payload_size_32,
    can_payload_size_48,
    can_payload_size_64,
    can_payload_size_max = can_payload_size_64,
};

/**
 * @brief CAN receive buffer data structure
 */
typedef union _can_rx_buf {
    uint32_t buffer[20];
    struct {
        struct {
            uint32_t id: 29;
            uint32_t : 1;
            uint32_t error_state_indicator: 1;
        };
        struct {
            uint32_t dlc: 4;
            uint32_t bitrate_switch: 1;
            uint32_t canfd_frame: 1;
            uint32_t remote_frame: 1;
            uint32_t extend_id: 1;
            uint32_t : 4;
            uint32_t loopback_message: 1;
            uint32_t error_type: 3;
            uint32_t cycle_time: 16;
        };
        uint8_t data[];
    };
} can_receive_buf_t;

/**
 * @brief CAN transmit buffer data structure
 */
typedef union _can_tx_buf {
    uint32_t buffer[18];
    struct {
        struct {
            uint32_t id: 29;
            uint32_t : 1;
            uint32_t transmit_timestamp_enable: 1;
        };
        struct {
            uint32_t dlc: 4;
            uint32_t bitrate_switch: 1;
            uint32_t canfd_frame: 1;
            uint32_t remote_frame: 1;
            uint32_t extend_id: 1;
            uint32_t : 24;
        };
        uint8_t data[];
    };
} can_transmit_buf_t;

/**
 * @brief CAN acceptance filter modes
 */
typedef enum _can_filter_mode {
    can_filter_mode_both_frames,
    can_filter_mode_standard_frames,
    can_filter_mode_extended_frames,
} can_filter_mode_t;

/**
 * @brief CAN acceptance configuration
 */
typedef struct {
    uint16_t index;
    can_filter_mode_t mode;
    bool enable;
    uint32_t code;
    uint32_t mask;
} can_filter_config_t;

/**
 * @brief CAN configuration
 */
typedef struct {
    uint32_t baudrate;
    uint32_t baudrate_fd;
    can_loopback_mode_t loopback_mode;
    bool enable_canfd;
    bool enable_self_ack;
    bool disable_re_transmission_for_ptb;
    bool disable_re_transmission_for_stb;
    uint32_t filter_list_num;
    can_filter_config_t *filter_list;

} can_config_t;


#ifdef __cpluspuls
extern "C" {
#endif


static inline void can_reset(CAN_Type *base, bool enable)
{
    if (enable) {
        base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_RESET_MASK;
    } else {
        base->CMD_STA_CMD_CTRL &= ~CAN_CMD_STA_CMD_CTRL_RESET_MASK;
    }
}

static inline void can_set_loopback_mode(CAN_Type *base, can_loopback_mode_t mode)
{
    uint32_t cfg_stat = base->CMD_STA_CMD_CTRL & ~(CAN_CMD_STA_CMD_CTRL_LBME_MASK | CAN_CMD_STA_CMD_CTRL_LBMI_MASK);
    if (mode == can_loopback_internal) {
        cfg_stat |= CAN_CMD_STA_CMD_CTRL_LBMI_MASK;
    } else if (mode == can_loopback_external) {
        cfg_stat |= CAN_CMD_STA_CMD_CTRL_LBME_MASK;
    } else {
        // Do nothing
    }
    base->CMD_STA_CMD_CTRL = cfg_stat;
}

static inline void can_enable_listen_only_mode(CAN_Type *base, bool enable)
{
    if (enable) {
        base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_LOM_MASK;
    } else {
        base->CMD_STA_CMD_CTRL &= ~CAN_CMD_STA_CMD_CTRL_LOM_MASK;
    }
}

static inline void can_enter_standby_mode(CAN_Type *base, bool enable)
{
    if (enable) {
        base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_STBY_MASK;
    } else {
        base->CMD_STA_CMD_CTRL &= ~CAN_CMD_STA_CMD_CTRL_STBY_MASK;
    }
}

static inline void can_select_tx_buffer(CAN_Type *base, bool select_secondary_buffer)
{
    if (select_secondary_buffer) {
        base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_TBSEL_MASK;
    } else {
        base->CMD_STA_CMD_CTRL &= ~CAN_CMD_STA_CMD_CTRL_TBSEL_MASK;
    }
}

static inline void can_start_high_priority_message_transmit(CAN_Type *base)
{
    base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_TPE_MASK;
}

static inline void can_abort_high_priority_message_transmit(CAN_Type *base)
{
    base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_TPA_MASK;
}

static inline void can_start_message_transmit(CAN_Type *base)
{
    base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_TSONE_MASK;
}

static inline void can_start_all_message_transmit(CAN_Type *base)
{
    base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_TSALL_MASK;
}

static inline void can_abort_message_transmit(CAN_Type *base)
{
    base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_TSA_MASK;
}

static inline void can_switch_to_next_tx_buffer(CAN_Type *base)
{
    base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_TSNEXT_MASK;
}

static inline void can_select_tx_buffer_priority_mode(CAN_Type *base, bool enable_priority_decision)
{
    if (enable_priority_decision) {
        base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_TSMODE_MASK;
    } else {
        base->CMD_STA_CMD_CTRL &= ~CAN_CMD_STA_CMD_CTRL_TSMODE_MASK;
    }
}

static inline uint8_t can_get_secondary_transmit_buffer_status(CAN_Type *base)
{
    return CAN_CMD_STA_CMD_CTRL_TSSTAT_GET(base->CMD_STA_CMD_CTRL);
}

static inline void can_enable_self_ack(CAN_Type *base, bool enable)
{
    if (enable) {
        base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_SACK_MASK;
    } else {
        base->CMD_STA_CMD_CTRL &= ~CAN_CMD_STA_CMD_CTRL_SACK_MASK;
    }
}

static inline void can_set_receive_buffer_overflow_mode(CAN_Type *base, bool override_enable)
{
    if (override_enable) {
        base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_ROM_MASK;
    } else {
        base->CMD_STA_CMD_CTRL &= ~CAN_CMD_STA_CMD_CTRL_ROM_MASK;
    }
}

static inline bool can_is_receive_buffer_overflow(CAN_Type *base)
{
    return IS_HPM_BITMASK_SET(base->CMD_STA_CMD_CTRL, CAN_CMD_STA_CMD_CTRL_ROV_MASK);
}

static inline void can_release_receive_buffer(CAN_Type *base)
{
    base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_RREL_MASK;
}

static inline void can_allow_store_all_data_in_receive_buffer(CAN_Type *base, bool allow)
{
    if (allow) {
        base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_RBALL_MASK;
    } else {
        base->CMD_STA_CMD_CTRL &= ~CAN_CMD_STA_CMD_CTRL_RBALL_MASK;
    }
}

static inline uint8_t can_get_receive_buffer_status(CAN_Type *base)
{
    return CAN_CMD_STA_CMD_CTRL_RSTAT_GET(base->CMD_STA_CMD_CTRL);
}


static inline void can_enable_can_fd_iso_mode(CAN_Type *base, bool enable)
{
    if (enable) {
        base->CMD_STA_CMD_CTRL |= CAN_CMD_STA_CMD_CTRL_FD_ISO_MASK;
    } else {
        base->CMD_STA_CMD_CTRL &= ~CAN_CMD_STA_CMD_CTRL_FD_ISO_MASK;
    }
}


static inline void can_enable_tx_rx_irq(CAN_Type *base, uint8_t mask)
{
    base->RTIE |= mask;
}

static inline void can_disable_tx_rx_irq(CAN_Type *base, uint8_t mask)
{
    base->RTIE &= ~mask;
}


static inline void can_clear_tx_rx_flags(CAN_Type *base, uint8_t flags)
{
    base->RTIF = flags;
}


static inline uint8_t can_get_tx_rx_flags(CAN_Type *base)
{
    return base->RTIF;
}

static inline void can_enable_error_irq(CAN_Type *base, uint8_t mask)
{
    base->ERRINT |= mask;
}

static inline void can_disable_error_irq(CAN_Type *base, uint8_t mask)
{
    base->ERRINT &= ~mask;
}

static inline uint8_t can_get_error_interrupt_flags(CAN_Type *base)
{
    return (base->ERRINT & (uint8_t) ~(CAN_ERRINT_EPIE_MASK | CAN_ERRINT_ALIE_MASK | CAN_ERRINT_BEIE_MASK));
}

static inline uint8_t can_get_last_error_kind(CAN_Type *base)
{
    return CAN_EALCAP_KOER_GET(base->EALCAP);
}

static inline uint8_t can_get_last_arbitration_lost_position(CAN_Type *base)
{
    return CAN_EALCAP_ALC_GET(base->EALCAP);
}

static inline void can_set_transmitter_delay_compensation(CAN_Type *base, uint8_t sample_point, bool enable)
{
    base->TDC = CAN_TDC_SSPOFF_SET(sample_point) | CAN_TDC_TDCEN_SET((uint8_t) enable);
}


static inline void can_set_warning_limits(CAN_Type *base, uint8_t almost_full_limit, uint8_t error_warning_limit)
{
    base->LIMIT = CAN_LIMIT_AFWL_SET(almost_full_limit) | CAN_LIMIT_EWL_SET(error_warning_limit);
}

static inline uint8_t can_get_receive_error_count(CAN_Type *base)
{
    return base->RECNT;
}

static inline uint8_t can_get_transmit_error_count(CAN_Type *base)
{
    return base->TECNT;
}

static inline void can_disable_filter(CAN_Type *base, uint32_t index)
{
    base->ACF_EN &= (uint16_t) ~(1U << index);
}

/**
 * @brief Get default CAN configuration parameters
 */
hpm_stat_t can_get_default_config(can_config_t *config);

/**
 * @brief Initialize the CAN controller
 */
hpm_stat_t can_init(CAN_Type *base, can_config_t *config, uint32_t src_clk_freq);

/**
 * @brief Configure the CAN bit timing for CAN BUS
 */
hpm_stat_t can_set_bit_timing(CAN_Type *base, can_bit_timing_option_t option, uint32_t src_clk_freq, uint32_t baudrate);

/**
 * @brief Configure the acceptable filter
 */
hpm_stat_t can_set_filter(CAN_Type *base, const can_filter_config_t *config);

/**
 * @brief Send message using blocking transfer
 */
hpm_stat_t can_send_message_blocking(CAN_Type *base, const can_transmit_buf_t *message);

/**
 * @brief Send high-priority message using blocking transfer
 */
hpm_stat_t can_send_high_priority_message_blocking(CAN_Type *base, const can_transmit_buf_t *message);

/**
 * @brief Receive message using blocking transfer
 */
hpm_stat_t can_receive_message_blocking(CAN_Type *base, can_receive_buf_t *message);


#ifdef __cpluspuls
}
#endif


#endif /* HPM_CAN_DRV_H */
