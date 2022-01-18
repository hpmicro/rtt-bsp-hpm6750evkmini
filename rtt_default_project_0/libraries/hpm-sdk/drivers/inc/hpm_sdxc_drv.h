/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_SDXC_DRV_H
#define HPM_SDXC_DRV_H

#include "hpm_common.h"
#include "hpm_sdxc_regs.h"
#include "hpm_sdxc_soc_drv.h"

/**
 * @brief SDMA Buffer Boundary definitions
 */
#define SDXC_SDMA_BUF_BOUNDARY_4KB (0UL)
#define SDXC_SDMA_BUF_BOUNDARY_8KB (1UL)
#define SDXC_SDMA_BUF_BOUNDARY_16KB (2UL)
#define SDXC_SDMA_BUF_BOUNDARY_32KB (3UL)
#define SDXC_SDMA_BUF_BOUNDARY_64KB (4UL)
#define SDXC_SDMA_BUF_BOUNDARY_128KB (5UL)
#define SDXC_SDMA_BUF_BOUNDARY_256KB (6UL)
#define SDXC_SDMA_BUF_BOUNDARY_512KB (7UL)


/**
 * @brief Command Response Type Selection
 */
#define SDXC_CMD_RESP_TYPE_NO_RESP (0U)         /*!< No Response */
#define SDXC_CMD_RESP_TYPE_RESP_LEN_136 (1U)    /*!< Response Length 136 */
#define SDXC_CMD_RESP_TYPE_RESP_LEN_48 (2U)     /*!< Response Length 48 */
#define SDXC_CMD_RESP_TYPE_RESP_LEN_48B (3U)    /*!< Response Length 48; Check busy after response */


/**
 * @brief Software reset flag definitions
 */
typedef enum _sdxc_software_reset {
    sdxc_reset_all,
    sdxc_reset_cmd_line,
    sdxc_reset_data_line,
} sdxc_sw_reset_type_t;

typedef enum _sdxc_bus_voltage_option {
    sdxc_bus_voltage_sd_1v8 = 0x05U,
    sdxc_bus_voltage_sd_3v0 = 0x06U,
    sdxc_bus_voltage_sd_3v3 = 0x07U,

    sdxc_bus_voltage_emmc_1v2 = 0x05U,
    sdxc_bus_voltage_emmc_1v8 = 0x06U,
    sdxc_bus_voltage_emmc_3v3 = 0x07U,
} sdxc_bus_voltage_option_t;

typedef enum _sdxc_wakeup_event {
    sdxc_wakeup_card_removal = 0x4U,
    sdxc_wakeup_card_insert = 0x02U,
    sdxc_wakeup_cart_interrupt = 0x01U,
} sdxc_wakeup_event_t;

typedef enum _sdxc_dma_type {
    sdxc_dmasel_sdma = 0U,
    sdxc_dmasel_adma2 = 2U,
    sdxc_dmasel_adma2_or_3 = 3U,
    sdxc_dmasel_nodma = 0xFU,
} sdxc_dma_type_t;

typedef enum _sdxc_bus_width {
    sdxc_bus_width_1bit,
    sdxc_bus_width_4bit,
    sdxc_bus_width_8bit,
} sdxc_bus_width_t;

typedef enum _sdxc_speed_mode {
    sdxc_sd_speed_sdr12 = 0U,
    sdxc_sd_speed_sdr25 = 1U,
    sdxc_sd_speed_sdr50 = 2U,
    sdxc_sd_speed_sdr104 = 3U,
    sdxc_sd_speed_ddr50 = 4U,
    sdxc_sd_speed_normal = sdxc_sd_speed_sdr12,
    sdxc_sd_speed_high = sdxc_sd_speed_sdr25,

    sdxc_emmc_speed_legacy = 0U,
    sdxc_emmc_speed_high_speed_sdr = 1U,
    sdxc_emmc_speed_hs200 = 3U,
    sdxc_emmc_speed_high_speed_ddr = 4U,
    sdxc_emmc_speed_hs400 = 7U,

    sdxc_sdmmc_speed_card_init = 0x10,

} sdxc_speed_mode_t;

typedef enum _sdxc_auto_cmd_sel {
    sdxc_auto_cmd_disabled = 0U,
    sdxc_auto_cmd12_enabled = 1U,
    sdxc_auto_cmd23_enabled = 2U,
    sdxc_auto_cmd_auto_select = 3U,
} sdxc_auto_cmd_sel_t;


typedef enum _sdxc_xfer_direction {
    sdxc_xfer_dir_write,
    sdxc_xfer_dir_read,
} sdxc_xfer_direction_t;

typedef enum _sdxc_command_type {
    sdxc_cmd_type_normal_cmd = 0U,
    sdxc_cmd_type_suspend_cmd,
    sdxc_cmd_tye_resume_cmd,
    sdxc_cmd_type_abort_cmd,
    sdxc_cmd_type_empty,

} sdxc_command_type_t;

/**
 * @brief Command Type
 */
#define SDXC_CMD_TYPE_NORMAL (0UL << SDXC_CMD_XFER_CMD_TYPE_SHIFT)
#define SDXC_CMD_TYPE_SUSPEND (1UL << SDXC_CMD_XFER_CMD_TYPE_SHIFT)
#define SDXC_CMD_TYPE_RESUME (1UL << SDXC_CMD_XFER_CMD_TYPE_SHIFT)
#define SDXC_CMD_TYPE_ABORT (1UL << SDXC_CMD_XFER_CMD_TYPE_SHIFT)

typedef enum _sdxc_boot_mode {
    sdxc_boot_mode_normal = 0,
    sdxc_boot_mode_alternative
} sdxc_boot_mode_t;


typedef enum _sdxc_response_type {
    sdxc_response_type_no_resp,
    sdxc_response_type_resp_len_136bit,
    sdxc_response_type_resp_len_48bit,
    sdxc_response_type_resp_len_48bit_check_busy,
} sdxc_response_type_t;

#define SDXC_CMD_RESP_NO_RESPONSE (0UL << SDXC_CMD_XFER_RESP_TYPE_SELECT_SHIFT)
#define SDXC_CMD_RESP_LEN_136 (1UL << SDXC_CMD_XFER_RESP_TYPE_SELECT_SHIFT)
#define SDXC_CMD_RESP_LEN_48 (2UL << SDXC_CMD_XFER_RESP_TYPE_SELECT_SHIFT)
#define SDXC_CMD_RESP_LEN_48B (3UL << SDXC_CMD_XFER_RESP_TYPE_SELECT_SHIFT)

#define SDXC_CMD_CMD_IS_MAIN_CMD (0U)
#define SDXC_CMD_CMD_IS_SUB_CMD (SDXC_CMD_XFER_SUB_CMD_FLAG_MASK)

#define SDXC_CMD_CMD_CRC_CHK_EN (SDXC_CMD_XFER_CMD_CRC_CHK_ENABLE_MASK)
#define SDXC_CMD_CMD_CRC_CHK_DIS (0U)

#define SDXC_CMD_CMD_IDX_CHK_EN (SDXC_CMD_XFER_CMD_IDX_CHK_ENABLE_MASK)
#define SDXC_CMD_CMD_IDX_CHK_DIS (0U)

#define SDXC_CMD_DATA_PRESENT (SDXC_CMD_XFER_DATA_PRESENT_SEL_MASK)
#define SDXC_CMD_DATA_NO_PRESENT (0U)

#define SDXC_CMD_CMD_TYPE_NORMAL (0U)
#define SDXC_CMD_CMD_TYPE_SUSPEND (1UL << SDXC_CMD_XFER_CMD_TYPE_SHIFT)
#define SDXC_CMD_CMD_TYPE_RESUME (2U << SDXC_CMD_XFER_CMD_TYPE_SHIFT)
#define SDXC_CMD_CMD_TYPE_ABORT (3U << SDXC_CMD_XFER_CMD_TYPE_SHIFT)


enum {
    status_sdxc_busy = MAKE_STATUS(status_group_sdxc, 0),
    status_sdxc_error,
    status_sdxc_send_cmd_failed,

    status_sdxc_cmd_timeout_error,
    status_sdxc_cmd_crc_error,
    status_sdxc_cmd_end_bit_error,
    status_sdxc_cmd_index_error,
    status_sdxc_data_timeout_error,
    status_sdxc_data_crc_error,
    status_sdxc_data_end_bit_error,
    status_sdxc_auto_cmd_error,
    status_sdxc_adma_error,
    status_sdxc_tuning_error,
    status_sdxc_response_error,
    status_sdxc_boot_ack_error,
    status_sdxc_retuning_request,
    status_sdxc_autocmd_cmd12_not_exec,
    status_sdxc_autocmd_cmd_timeout_error,
    status_sdxc_autocmd_cmd_crc_error,
    status_sdxc_autocmd_end_bit_error,
    status_sdxc_autocmd_cmd_index_error,
    status_sdxc_autocmd_cmd_response_error,
    status_sdxc_autocmd_cmd_not_issued_auto_cmd12,
    status_sdxc_unsupported,
    status_sdxc_transfer_data_completed,
    status_sdxc_send_cmd_successful,
    status_sdxc_transfer_dma_completed,
    status_sdxc_transfer_data_failed,
    status_sdxc_dma_addr_unaligned,
    status_sdxc_tuning_failed,
};


typedef struct {
    union {
        struct {
            uint32_t tout_clk_freq: 6;
            uint32_t : 1;
            uint32_t tout_clk_unit: 1;
            uint32_t base_clk_freq: 8;
            uint32_t max_blk_len: 2;
            uint32_t embedded_8_bit_support: 1;
            uint32_t adma2_support: 1;
            uint32_t : 1;
            uint32_t high_speed_support: 1;
            uint32_t sdma_support: 1;
            uint32_t suspend_resume_support: 1;
            uint32_t voltage_3v3_support: 1;
            uint32_t voltage_3v0_support: 1;
            uint32_t voltage_1v8_support: 1;
            uint32_t sys_addr_64_bit_v4_support: 1;
            uint32_t sys_addr_64_bit_v3_support: 1;
            uint32_t asysnc_interrupt_support: 1;
            uint32_t slot_type_r: 2;
        };
        uint32_t U;
    } capabilities1;

    union {
        struct {
            uint32_t sdr50_support: 1;
            uint32_t sdr104_support: 1;
            uint32_t ddr50_support: 1;
            uint32_t uhs2_support: 1;
            uint32_t drv_type_a: 1;
            uint32_t drv_type_c: 1;
            uint32_t drv_type_d: 1;
            uint32_t reserved0: 1;
            uint32_t retune_cnt: 4;
            uint32_t : 1;
            uint32_t use_tuning_sdr50: 1;
            uint32_t re_tuning_modes: 2;
            uint32_t clk_mul: 8;
            uint32_t : 3;
            uint32_t adma3_support: 1;
            uint32_t vdd2_1v8_support: 1;
            uint32_t : 3;
        };
        uint32_t U;
    } capabilities2;

    union {
        struct {
            uint32_t max_current_3v3: 8;
            uint32_t max_current_3v0: 8;
            uint32_t max_current_1v8: 8;
            uint32_t reserved: 8;
        };
        uint32_t U;
    } curr_capabilities1;

    union {
        struct {
            uint32_t max_current_vdd2_1v8: 8;
            uint32_t reserved: 24;
        };
        uint32_t U;
    } curr_capabilities2;

} sdxc_capabilities_t;

typedef enum _sdxc_dev_resp_type {
    sdxc_dev_resp_none = 0,
    sdxc_dev_resp_r1,
    sdxc_dev_resp_r1b,
    sdxc_dev_resp_r2,
    sdxc_dev_resp_r3,
    sdxc_dev_resp_r4,
    sdxc_dev_resp_r5,
    sdxc_dev_resp_r5b,
    sdxc_dev_resp_r6,
    sdxc_dev_resp_r7,
} sdxc_dev_resp_type_t;

typedef struct _sdxc_command {
    uint32_t cmd_index;
    uint32_t cmd_argument;
    uint32_t cmd_flags;
    sdxc_command_type_t cmd_type;
    sdxc_dev_resp_type_t resp_type;
    uint32_t resp_error_flags;
    uint32_t response[4];
    uint32_t auto_cmd_resp;
} sdxc_command_t;

typedef struct _sdxc_data_list {
    uint32_t *data_addr;
    uint32_t data_size;
    struct _sdxc_data_list *data_list;
} sdxc_data_list_t;

typedef struct _sdxc_data {
    bool enable_auto_cmd12;
    bool enable_auto_cmd23;
    bool enable_ignore_error;
    uint8_t data_type;
    uint32_t block_size;
    uint32_t block_cnt;
    uint32_t *rx_data;
    const uint32_t *tx_data;
} sdxc_data_t;

enum {
    sdxc_xfer_data_normal = 0U,         /*!< Transfer normal read/write data */
    sdxc_xfer_data_tuning = 1U,         /*!< Transfer Tuning data */
    sdxc_xfer_data_boot = 2U,           /*!< Transfer boot data */
    sdxc_xfer_data_boot_continuous = 3U, /*!< Transfer boot data continuously */
};


typedef struct _sdxc_xfer {
    sdxc_data_t *data;
    sdxc_command_t *command;
} sdxc_xfer_t;

typedef struct _sdxc_adma_config {
    sdxc_dma_type_t dma_type;
    uint32_t *adma_table;
    uint32_t adma_table_words;
} sdxc_adma_config_t;

enum {
    sdxc_adma_desc_single_flag = 0U,
    sdxc_adma_desc_multi_flag = 1U,
};

typedef struct _sdxc_config {
    uint32_t data_timeout;
} sdxc_config_t;

typedef struct _sdxc_adma2_descriptor {
    union {
        struct {
            uint32_t valid: 1;
            uint32_t end: 1;
            uint32_t interrupt: 1;
            uint32_t act: 3;
            uint32_t len_upper: 10;
            uint32_t len_lower: 16;
        };
        uint32_t len_attr;
    };
    const uint32_t *addr;
} sdxc_adma2_descriptor_t;

#define SDXC_ADMA2_DESC_VALID_FLAG (1UL << 0)
#define SDXC_ADMA2_DESC_END_FLAG (1UL << 1)
#define SDXC_ADMA2_DESC_INTERRUPT_FLAG (1UL << 2)
#define SDXC_ADMA2_DESC_ACT0_FLAG (1UL << 3)
#define SDXC_ADMA2_DESC_ACT1_FLAG (1UL << 4)
#define SDXC_ADMA2_DESC_ACT2_FLAG (1UL << 5)

#define SDXC_ADMA2_ADDR_LEN (4U)
#define SDXC_ADMA2_LEN_ALIGN (4U)

#define SDXC_ADMA2_DESC_TYPE_NOP (0U)
#define SDXC_ADMA2_DESC_TYPE_TRANS (4U)
#define SDXC_ADMA2_DESC_TYPE_LINK (6U)
#define SDXC_ADMA3_DESC_TYPE_FOR_SD_MODE (0x1U)
#define SDXC_AMDA3_DESC_TYPE_INTEGRATED_LINKER (7U)

#define SDXC_ADMA3_CMD_FOR_SD_DESC_ATTR (0x09U)
#define SDXC_ADMA3_INTEGRATED_DESC_ATTR (0x39U)

#define SDXC_ADMA3_CMD_DESC_IDX_32BIT_BLK_CNT (0U)
#define SDXC_ADMA3_CMD_DESC_IDX_BLK_SIZE (1U)
#define SDXC_ADMA3_CMD_DESC_IDX_ARG (2U)
#define SDXC_ADMA3_CMD_DESC_IDX_CMD_XFER (3U)
typedef struct _sdxc_adma3_cmd_sd_desc {
    struct {
        uint32_t attr;
        uint32_t data;
    } entry[4];
} sdxc_adma3_cmd_sd_desc_t;

typedef struct _sdxc_adma3_integrated_desc {
    uint32_t attr;
    sdxc_adma3_cmd_sd_desc_t *cmd_desc_ptr;
} sdxc_adma3_integrated_desc_t;

typedef struct _sdxc_boot_config {
    uint32_t ack_timeout_cnt;
    sdxc_boot_mode_t boot_mode;
    uint32_t block_cnt;
    uint32_t block_size;
    bool enable_boot_ack;
    bool enable_auto_stop_at_block_gap;
} sdxc_boot_config_t;


#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @brief Get the SDXC interrupt status
 * @param base SDXC base address
 * @return SDXC inaterrupt status
 */
static inline uint32_t sdxc_get_interrupt_status(SDXC_Type *base)
{
    return base->INT_STAT;
}

static inline bool sdxc_is_card_inserted(SDXC_Type *base)
{
    return IS_HPM_BITMASK_SET(base->PSTATE, SDXC_PSTATE_CARD_INSERTED_MASK);
}

/**
 * @brief Clear SDXC interrupt status
 * @param base SDXC base address
 * @param status_mask the status mask to be cleared
 */
static inline void sdxc_clear_interrupt_status(SDXC_Type *base, uint32_t status_mask)
{
    base->INT_STAT = status_mask;
}

static inline void sdxc_enable_interrupt_status(SDXC_Type *base, uint32_t mask, bool enable)
{
    if (enable) {
        base->INT_STAT_EN |= mask;
    } else {
        base->INT_STAT_EN &= ~mask;
    }
}


static inline void sdxc_enable_interrupt_signal(SDXC_Type *base, uint32_t mask, bool enable)
{
    if (enable) {
        base->INT_SIGNAL_EN |= mask;
    } else {
        base->INT_SIGNAL_EN &= ~mask;
    }
}

hpm_stat_t sdxc_get_capabilities(SDXC_Type *base, sdxc_capabilities_t *capabilities);


static inline uint8_t sdxc_get_adma_error_status(SDXC_Type *base)
{
    return base->ADMA_ERR_STAT;
}

static inline void sdxc_configure_data_timeout(SDXC_Type *base, uint8_t timeout)
{
    base->SYS_CTRL = (base->SYS_CTRL & ~SDXC_SYS_CTRL_TOUT_CNT_MASK) | SDXC_SYS_CTRL_TOUT_CNT_SET(timeout);
}

static inline void sdxc_interrupt_at_block_gap(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->PROT_CTRL |= SDXC_PROT_CTRL_INT_AT_BGAP_MASK;
    } else {
        base->PROT_CTRL &= ~SDXC_PROT_CTRL_INT_AT_BGAP_MASK;
    }
}

static inline void sdxc_read_wait_control(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->PROT_CTRL |= SDXC_PROT_CTRL_RD_WAIT_CTRL_MASK;
    } else {
        base->PROT_CTRL &= ~SDXC_PROT_CTRL_RD_WAIT_CTRL_MASK;
    }
}

static inline void sdxc_continue_request(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->PROT_CTRL |= SDXC_PROT_CTRL_CONTINUE_REQ_MASK;
    } else {
        base->PROT_CTRL &= ~SDXC_PROT_CTRL_CONTINUE_REQ_MASK;
    }
}

static inline void sdxc_stop_at_block_gap_request(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->PROT_CTRL |= SDXC_PROT_CTRL_STOP_BG_REQ_MASK;
    } else {
        base->PROT_CTRL &= ~SDXC_PROT_CTRL_STOP_BG_REQ_MASK;
    }
}

static inline void sdxc_enable_high_speed(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->PROT_CTRL |= SDXC_PROT_CTRL_HIGH_SPEED_EN_MASK;
    } else {
        base->PROT_CTRL &= ~SDXC_PROT_CTRL_HIGH_SPEED_EN_MASK;
    }
}

static inline void sdxc_enable_async_interrupt(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->AC_HOST_CTRL |= SDXC_AC_HOST_CTRL_ASYNC_INT_ENABLE_MASK;
    } else {
        base->AC_HOST_CTRL &= ~SDXC_AC_HOST_CTRL_ASYNC_INT_ENABLE_MASK;
    }
}

static inline void sdxc_enable_preset(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->AC_HOST_CTRL |= SDXC_AC_HOST_CTRL_PRESET_VAL_ENABLE_MASK;
    } else {
        base->AC_HOST_CTRL &= ~SDXC_AC_HOST_CTRL_PRESET_VAL_ENABLE_MASK;
    }
}

static inline void sdxc_enable_host_version4(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->AC_HOST_CTRL |= SDXC_AC_HOST_CTRL_HOST_VER4_ENABLE_MASK;
    } else {
        base->AC_HOST_CTRL &= ~SDXC_AC_HOST_CTRL_HOST_VER4_ENABLE_MASK;
    }
}

static inline void sdxc_execute_tuning(SDXC_Type *base)
{
    base->AC_HOST_CTRL |= SDXC_AC_HOST_CTRL_EXEC_TUNING_MASK;
}

static inline void sdxc_enable_software_tuning(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->AUTO_TUNING_CTRL |= SDXC_AUTO_TUNING_CTRL_SW_TUNE_EN_MASK;
    }
    else {
        base->AUTO_TUNING_CTRL &= ~SDXC_AUTO_TUNING_CTRL_SW_TUNE_EN_MASK;
    }
}

static inline void sdxc_reset_tuning_engine(SDXC_Type *base)
{
    base->AC_HOST_CTRL &= ~SDXC_AC_HOST_CTRL_SAMPLE_CLK_SEL_MASK;
}


static inline void sdxc_switch_to_1v8_signal(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->AC_HOST_CTRL |= SDXC_AC_HOST_CTRL_SIGNALING_EN_MASK;
    } else {
        base->AC_HOST_CTRL &= ~SDXC_AC_HOST_CTRL_SIGNALING_EN_MASK;
    }
}

static inline void sdxc_enable_programmable_clock_mode(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->SYS_CTRL |= SDXC_SYS_CTRL_CLK_GEN_SELECT_MASK;
    } else {
        base->SYS_CTRL &= ~SDXC_SYS_CTRL_CLK_GEN_SELECT_MASK;
    }
}

static inline void sdxc_enable_pll(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->SYS_CTRL |= SDXC_SYS_CTRL_PLL_ENABLE_MASK;
    } else {
        base->SYS_CTRL &= ~SDXC_SYS_CTRL_PLL_ENABLE_MASK;
    }
}

static inline void sdxc_enable_sd_emmc_clock(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->SYS_CTRL |= SDXC_SYS_CTRL_SD_CLK_EN_MASK;
    } else {
        base->SYS_CTRL &= ~SDXC_SYS_CTRL_SD_CLK_EN_MASK;
    }
}

static inline void sdxc_enable_internal_clock(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->SYS_CTRL |= SDXC_SYS_CTRL_INTERNAL_CLK_EN_MASK;
    } else {
        base->SYS_CTRL &= ~SDXC_SYS_CTRL_INTERNAL_CLK_EN_MASK;
    }
}

static inline uint32_t sdxc_get_present_status(SDXC_Type *base)
{
    return base->PSTATE;
}

static inline uint32_t sdxc_read_data(SDXC_Type *base)
{
    return base->BUF_DATA;
}

static inline void sdxc_write_data(SDXC_Type *base, uint32_t data)
{
    base->BUF_DATA = data;
}

static inline void sdxc_set_continue_request(SDXC_Type *base)
{
    base->PROT_CTRL |= SDXC_PROT_CTRL_CONTINUE_REQ_MASK;
}

static inline void sdxc_request_stop_at_block_gap(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->PROT_CTRL |= SDXC_PROT_CTRL_STOP_BG_REQ_MASK;
    } else {
        base->PROT_CTRL &= ~SDXC_PROT_CTRL_STOP_BG_REQ_MASK;
    }
}


static inline bool sdxc_request_retuning(SDXC_Type *base)
{
    return IS_HPM_BITMASK_SET(base->PSTATE, SDXC_PSTATE_RE_TUNE_REQ_MASK);
}


static inline void sdxc_send_data(SDXC_Type *base, uint32_t data)
{
    base->BUF_DATA = data;
}



static inline void sdxc_enable_auto_tuning(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->AUTO_TUNING_CTRL |= SDXC_AUTO_TUNING_CTRL_AT_EN_MASK;
    } else {
        base->AUTO_TUNING_CTRL &= ~SDXC_AUTO_TUNING_CTRL_AT_EN_MASK;
    }
}

static inline void sdxc_enable_mmc_boot(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->EMMC_BOOT_CTRL |= SDXC_EMMC_BOOT_CTRL_MAN_BOOT_EN_MASK;
    } else {
        base->EMMC_BOOT_CTRL &= ~SDXC_EMMC_BOOT_CTRL_MAN_BOOT_EN_MASK;
    }
}

static inline void sdxc_force_event(SDXC_Type *base, uint32_t mask)
{
    base->FORCE_EVENT = mask;
}

static inline void sdxc_enable_dma(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->CMD_XFER |= SDXC_CMD_XFER_DMA_ENABLE_MASK;
    } else {
        base->CMD_XFER &= ~SDXC_CMD_XFER_DMA_ENABLE_MASK;
    }
}

static inline void sdxc_enable_sd_clock(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->SYS_CTRL |= SDXC_SYS_CTRL_SD_CLK_EN_MASK;
        while (!IS_HPM_BITMASK_SET(base->SYS_CTRL, SDXC_SYS_CTRL_SD_CLK_EN_MASK)) {
        }
    } else {
        base->SYS_CTRL &= ~SDXC_SYS_CTRL_SD_CLK_EN_MASK;
        while (IS_HPM_BITMASK_SET(base->SYS_CTRL, SDXC_SYS_CTRL_SD_CLK_EN_MASK)) {
        }
    }
}

static inline void sdxc_set_center_phase_code(SDXC_Type *base, uint32_t value)
{
    base->AUTO_TUNING_STAT = (base->AUTO_TUNING_STAT & ~SDXC_AUTO_TUNING_STAT_CENTER_PH_CODE_MASK) |
                             SDXC_AUTO_TUNING_STAT_CENTER_PH_CODE_SET(value);
}

static inline void sdxc_enable_enhanced_strobe(SDXC_Type *base, bool enable)
{
    if (enable) {
        base->EMMC_BOOT_CTRL |= SDXC_EMMC_BOOT_CTRL_ENH_STROBE_ENABLE_MASK;
    }
    else {
        base->EMMC_BOOT_CTRL &= ~SDXC_EMMC_BOOT_CTRL_ENH_STROBE_ENABLE_MASK;
    }
}


void sdxc_set_mmc_boot_config(SDXC_Type *base, const sdxc_boot_config_t *config);

void sdxc_send_command(SDXC_Type *base, sdxc_command_t *cmd);

hpm_stat_t sdxc_wait_cmd_done(SDXC_Type *base, sdxc_command_t *cmd, bool polling_cmd_done);

void sdxc_set_data_config(SDXC_Type *base, sdxc_xfer_direction_t data_dir, uint32_t block_cnt, uint32_t block_size);

hpm_stat_t sdxc_set_adma_table_config(SDXC_Type *base, sdxc_adma_config_t *dma_cfg,
                                      sdxc_data_t *data_cfg, uint32_t flags);

hpm_stat_t sdxc_set_adma2_desc(uint32_t *adma_tbl, uint32_t adma_table_words, const uint32_t *data_buf,
                               uint32_t data_bytes, uint32_t flags);

hpm_stat_t sdxc_set_dma_config(SDXC_Type *base, sdxc_adma_config_t *dma_cfg, const uint32_t *data_addr,
                               bool enable_auto_cmd23);

void sdxc_init(SDXC_Type *base, const sdxc_config_t *config);

void sdxc_set_speed_mode(SDXC_Type *base, sdxc_speed_mode_t mode);

void sdxc_set_data_bus_width(SDXC_Type *base, sdxc_bus_width_t width);

void sdxc_select_voltage(SDXC_Type *base, sdxc_bus_voltage_option_t option);

bool sdxc_reset(SDXC_Type *base, sdxc_sw_reset_type_t reset_type, uint32_t timeout);

void sdxc_enable_wakeup_event(SDXC_Type *base, sdxc_wakeup_event_t evt, bool enable);

hpm_stat_t sdxc_transfer_blocking(SDXC_Type *base, sdxc_adma_config_t *dma_config, sdxc_xfer_t *xfer);

hpm_stat_t sdxc_error_recovery(SDXC_Type *base);

hpm_stat_t sdxc_perform_tuning_flow_sequence(SDXC_Type *base, uint8_t tuning_cmd);

hpm_stat_t sdxc_perform_software_tuning(SDXC_Type *base, uint8_t tuning_cmd);

hpm_stat_t sdxc_perform_auto_tuning(SDXC_Type *base, uint8_t tuning_cmd);

#if defined(__cplusplus)
}
#endif

#endif /*HPM_SDXC_DRV_H */
