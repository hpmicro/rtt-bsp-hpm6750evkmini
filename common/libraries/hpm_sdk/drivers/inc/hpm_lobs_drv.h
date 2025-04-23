/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_LOBS_DRV_H
#define HPM_LOBS_DRV_H

#include "hpm_common.h"
#include "hpm_soc_ip_feature.h"
#include "hpm_lobs_regs.h"

/**
 * @brief LOBS driver APIs
 * @defgroup lobs_interface LOBS driver APIs
 * @ingroup lobs_interfaces
 * @{
 */

#define LOBS_UNLOCK_KEY 0xc5acce55u

#define LOBS_PIN_DO(x) (x * 3)
#define LOBS_PIN_OE(x) (x * 3 + 1)
#define LOBS_PIN_DI(x) (x * 3 + 2)

/**
 * @brief signal group number
 *
 */
typedef enum {
    lobs_signal_group_PA = 0,
    lobs_signal_group_PB,
    lobs_signal_group_PC,
    lobs_signal_group_PD,
    lobs_signal_group_PE,
    lobs_signal_group_PF,
    lobs_signal_group_PV,
    lobs_signal_group_PW,
    lobs_signal_group_PX,
    lobs_signal_group_PY,
    lobs_signal_group_PZ,
} lobs_signal_group_t;    /**< lobs_signal_group_t */

/**
 * @brief group mode selection
 *
 */
typedef enum {
    lobs_one_group_96_bits = 0,
    lobs_two_group_8_bits
} lobs_group_mode_t;    /**< lobs_group_mode_t */

/**
 * @brief sample rate selection
 *
 */
typedef enum {
    lobs_sample_1_per_5 = 4,
    lobs_sample_1_per_6 = 5,
    lobs_sample_1_per_7 = 6,
#if defined(HPM_IP_FEATURE_LOBS_SAMPLE_RATE_EXT) && HPM_IP_FEATURE_LOBS_SAMPLE_RATE_EXT
    lobs_sample_1_per_10 = 9,
    lobs_sample_1_per_50 = 49,
    lobs_sample_1_per_100 = 99,
    lobs_sample_1_per_500 = 499,
    lobs_sample_1_per_1000 = 999,
#endif
} lobs_sample_rate_t;    /**< lobs_sample_rate_t */

/**
 * @brief burst selection
 *
 */
typedef enum {
    lobs_burst_4 = 3,
    lobs_burst_8 = 5,
    lobs_burst_16 = 7,
} lobs_burst_t;    /**< lobs_burst_t */

/**
 * @brief two group selection
 *
 */
typedef enum {
    lobs_two_group_1 = 0,
    lobs_two_group_2,
} lobs_two_group_sel_t;    /**< lobs_two_group_sel_t */

/**
 * @brief state selection
 *
 */
typedef enum {
    lobs_state_0 = 0,
    lobs_state_1,
    lobs_state_2,
    lobs_state_3,
    lobs_state_4,
} lobs_state_sel_t;    /**< lobs_state_sel_t */

/**
 * @brief compare mode
 *
 */
typedef enum {
    lobs_sig_cmp_mode = 0,
    lobs_cnt_cmp_mode,
} lobs_cmp_mode_t;    /**< lobs_cmp_mode_t */

/**
 * @brief compare condition
 *
 */
typedef enum {
    lobs_cnt_matched = 0,
    lobs_sig_equal_golden,
    lobs_sig_greater_golden,
    lobs_sig_greater_equal_golden,
    lobs_sig_not_equal_golden,
    lobs_sig_less_golden,
    lobs_sig_less_equal_golden,
} lobs_state_chg_condition_t;    /**< lobs_state_chg_condition_t */

/**
 * @brief next state
 *
 */
typedef enum {
    lobs_next_state_finish = 0x00,
    lobs_next_state_0 = 0x01,
    lobs_next_state_1 = 0x02,
    lobs_next_state_2 = 0x04,
    lobs_next_state_3 = 0x08,
    lobs_next_state_4 = 0x10,
} lobs_next_state_t;    /**< lobs_next_state_t */

#if defined(HPM_IP_FEATURE_LOBS_IRQ_CTRL) && (HPM_IP_FEATURE_LOBS_IRQ_CTRL)
/**
 * @brief irq mask
 *
 */
typedef enum {
    lobs_irq_final_mask = LOBS_IRQ_EN_FINAL_EN_MASK,
    lobs_irq_full_mask = LOBS_IRQ_EN_FULL_EN_MASK,
} lobs_irq_mask_t;    /**< lobs_irq_mask_t */
#endif

#if defined(HPM_IP_FEATURE_LOBS_COMP_LOGIC) && (HPM_IP_FEATURE_LOBS_COMP_LOGIC)
/**
 * @brief compare logic
 *
 */
typedef enum {
    lobs_cmp_logic_and = 0,
    lobs_cmp_logic_or,
} lobs_cmp_logic_t;    /**< lobs_cmp_logic_t */
#endif

#if defined(HPM_IP_FEATURE_LOBS_TRIG_ADDR) && (HPM_IP_FEATURE_LOBS_TRIG_ADDR)
/**
 * @brief trig address index
 *
 */
typedef enum {
    lobs_trig_addr_idx_1 = 0,
    lobs_trig_addr_idx_2,
    lobs_trig_addr_idx_3,
    lobs_trig_addr_idx_4,
} lobs_trig_addr_idx_t;    /**< lobs_trig_addr_idx_t */
#endif

/**
 * @brief ctrl config structure
 *
 */
typedef struct {
    lobs_group_mode_t group_mode;
    lobs_sample_rate_t sample_rate;
    uint32_t start_addr;
    uint32_t end_addr;
} lobs_ctrl_config_t;    /**< lobs_ctrl_config_t */

/**
 * @brief two group mode config structure
 *
 */
typedef struct {
    bool group_enable;
    lobs_signal_group_t sig_group_num;
    uint8_t sample_sig_bit[4];
    bool sample_sig_en[4];
} lobs_two_group_mode_config_t;    /**< lobs_two_group_mode_config_t */

/**
 * @brief two group mode config structure
 *
 */
typedef struct {
    lobs_signal_group_t sig_group_num;
    lobs_cmp_mode_t cmp_mode;
    lobs_state_chg_condition_t state_chg_condition;
    lobs_next_state_t next_state;
    uint32_t cmp_counter;
    uint8_t cmp_sig_bit[4];
    bool cmp_sig_en[4];
    bool cmp_golden_value[4];
#if defined(HPM_IP_FEATURE_LOBS_COMP_LOGIC) && (HPM_IP_FEATURE_LOBS_COMP_LOGIC)
    lobs_cmp_logic_t cmp_logic;
#endif
} lobs_state_config_t;    /**< lobs_state_config_t */

/**
 * @brief trace data structure
 *
 */
typedef struct {
    uint8_t header;
    uint8_t cnt_L;
    uint8_t cnt_M;
    uint8_t cnt_H;
    union {
        uint32_t u32_data[3];
        struct {
            uint32_t pin00_do : 1;
            uint32_t pin00_oe : 1;
            uint32_t pin00_di : 1;
            uint32_t pin01_do : 1;
            uint32_t pin01_oe : 1;
            uint32_t pin01_di : 1;
            uint32_t pin02_do : 1;
            uint32_t pin02_oe : 1;
            uint32_t pin02_di : 1;
            uint32_t pin03_do : 1;
            uint32_t pin03_oe : 1;
            uint32_t pin03_di : 1;
            uint32_t pin04_do : 1;
            uint32_t pin04_oe : 1;
            uint32_t pin04_di : 1;
            uint32_t pin05_do : 1;
            uint32_t pin05_oe : 1;
            uint32_t pin05_di : 1;
            uint32_t pin06_do : 1;
            uint32_t pin06_oe : 1;
            uint32_t pin06_di : 1;
            uint32_t pin07_do : 1;
            uint32_t pin07_oe : 1;
            uint32_t pin07_di : 1;
            uint32_t pin08_do : 1;
            uint32_t pin08_oe : 1;
            uint32_t pin08_di : 1;
            uint32_t pin09_do : 1;
            uint32_t pin09_oe : 1;
            uint32_t pin09_di : 1;
            uint32_t pin10_do : 1;
            uint32_t pin10_oe : 1;

            uint32_t pin10_di : 1;
            uint32_t pin11_do : 1;
            uint32_t pin11_oe : 1;
            uint32_t pin11_di : 1;
            uint32_t pin12_do : 1;
            uint32_t pin12_oe : 1;
            uint32_t pin12_di : 1;
            uint32_t pin13_do : 1;
            uint32_t pin13_oe : 1;
            uint32_t pin13_di : 1;
            uint32_t pin14_do : 1;
            uint32_t pin14_oe : 1;
            uint32_t pin14_di : 1;
            uint32_t pin15_do : 1;
            uint32_t pin15_oe : 1;
            uint32_t pin15_di : 1;
            uint32_t pin16_do : 1;
            uint32_t pin16_oe : 1;
            uint32_t pin16_di : 1;
            uint32_t pin17_do : 1;
            uint32_t pin17_oe : 1;
            uint32_t pin17_di : 1;
            uint32_t pin18_do : 1;
            uint32_t pin18_oe : 1;
            uint32_t pin18_di : 1;
            uint32_t pin19_do : 1;
            uint32_t pin19_oe : 1;
            uint32_t pin19_di : 1;
            uint32_t pin20_do : 1;
            uint32_t pin20_oe : 1;
            uint32_t pin20_di : 1;
            uint32_t pin21_do : 1;

            uint32_t pin21_oe : 1;
            uint32_t pin21_di : 1;
            uint32_t pin22_do : 1;
            uint32_t pin22_oe : 1;
            uint32_t pin22_di : 1;
            uint32_t pin23_do : 1;
            uint32_t pin23_oe : 1;
            uint32_t pin23_di : 1;
            uint32_t pin24_do : 1;
            uint32_t pin24_oe : 1;
            uint32_t pin24_di : 1;
            uint32_t pin25_do : 1;
            uint32_t pin25_oe : 1;
            uint32_t pin25_di : 1;
            uint32_t pin26_do : 1;
            uint32_t pin26_oe : 1;
            uint32_t pin26_di : 1;
            uint32_t pin27_do : 1;
            uint32_t pin27_oe : 1;
            uint32_t pin27_di : 1;
            uint32_t pin28_do : 1;
            uint32_t pin28_oe : 1;
            uint32_t pin28_di : 1;
            uint32_t pin29_do : 1;
            uint32_t pin29_oe : 1;
            uint32_t pin29_di : 1;
            uint32_t pin30_do : 1;
            uint32_t pin30_oe : 1;
            uint32_t pin30_di : 1;
            uint32_t pin31_do : 1;
            uint32_t pin31_oe : 1;
            uint32_t pin31_di : 1;
        } str_data;
    } trace_data;
} lobs_trace_data_t;    /**< lobs_trace_data_t */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief set lobs unlock
 *
 * @param[in] lobs LOBS base address
 */
static inline void lobs_unlock(LOBS_Type *lobs)
{
    lobs->LAR = LOBS_UNLOCK_KEY;
}

/**
 * @brief set lobs lock
 *
 * @param[in] lobs LOBS base address
 */
static inline void lobs_lock(LOBS_Type *lobs)
{
    lobs->LAR = 0;
}

/**
 * @brief set lobs enable or disable
 *
 * @param[in] lobs LOBS base address
 * @param[in] enable true - enable; false - disable.
 */
static inline void lobs_set_enable(LOBS_Type *lobs, bool enable)
{
    lobs->CTRL = (lobs->CTRL & ~LOBS_CTRL_RUN_MASK) | LOBS_CTRL_RUN_SET(enable);
}

/**
 * @brief set lobs pre-trig enable or disable
 *
 * @param[in] lobs LOBS base address
 * @param[in] enable true - enable; false - disable.
 */
static inline void lobs_set_pre_trig_enable(LOBS_Type *lobs, bool enable)
{
    lobs->PTACTION = (lobs->PTACTION & ~LOBS_PTACTION_TRACE_MASK) | LOBS_PTACTION_TRACE_SET(enable);
}

/**
 * @brief set lobs state enable or disable
 *
 * @param[in] lobs LOBS base address
 * @param[in] state one of state, @ref lobs_state_sel_t
 * @param[in] enable true - enable; false - disable.
 */
static inline void lobs_set_state_enable(LOBS_Type *lobs, lobs_state_sel_t state, bool enable)
{
    lobs->STATE[state].ACTION = (lobs->STATE[state].ACTION & ~LOBS_STATE_ACTION_TRACE_MASK) | LOBS_STATE_ACTION_TRACE_SET(enable);
}

/**
 * @brief get lobs final address
 *
 * @param[in] lobs LOBS base address
 *
 * @return uint32_t trace final address
 */
static inline uint32_t lobs_get_final_address(LOBS_Type *lobs)
{
    return lobs->FINALADDR;
}

/**
 * @brief check lobs trace finish
 *
 * @param[in] lobs LOBS base address
 *
 * @return bool true - trace finish; false - trace not finish
 */
static inline bool lobs_is_trace_finish(LOBS_Type *lobs)
{
    return (LOBS_CTSR_FINALSTATE_GET(lobs->CTSR) != 0) ? true : false;
}

#if defined(HPM_IP_FEATURE_LOBS_IRQ_CTRL) && (HPM_IP_FEATURE_LOBS_IRQ_CTRL)
/**
 * @brief set lobs irq enable
 *
 * @param[in] lobs LOBS base address
 * @param[in] mask irq mask, @ref lobs_irq_mask_t
 */
static inline void lobs_set_irq_enable(LOBS_Type *lobs, uint32_t mask)
{
    lobs->IRQ_EN |= mask;
}

/**
 * @brief set lobs irq disable
 *
 * @param[in] lobs LOBS base address
 * @param[in] mask irq mask, @ref lobs_irq_mask_t
 */
static inline void lobs_set_irq_disable(LOBS_Type *lobs, uint32_t mask)
{
    lobs->IRQ_EN &= ~mask;
}

/**
 * @brief get lobs irq enable status
 *
 * @param[in] lobs LOBS base address
 * @retval irq enable status, @ref lobs_irq_mask_t
 */
static inline uint32_t lobs_get_irq_enable_status(LOBS_Type *lobs)
{
    return lobs->IRQ_EN;
}

/**
 * @brief get lobs irq status
 *
 * @param[in] lobs LOBS base address
 * @retval irq status, @ref lobs_irq_mask_t
 */
static inline uint32_t lobs_get_irq_status(LOBS_Type *lobs)
{
    return lobs->IRQ_STS;
}

/**
 * @brief clear lobs irq flag
 *
 * @param[in] lobs LOBS base address
 * @param[in] mask irq mask, @ref lobs_irq_mask_t
 */
static inline void lobs_clear_irq_flag(LOBS_Type *lobs, uint32_t mask)
{
    lobs->IRQ_STS = mask;
}
#else
/**
 * @brief clear lobs fifo overflow flag
 *
 * @param[in] lobs LOBS base address
 *
 */
static inline void lobs_clear_fifo_overflow_flag(LOBS_Type *lobs)
{
    lobs->STREAMCTRL |= LOBS_STREAMCTRL_FULL_CLEAR_MASK;
}
#endif

/**
 * @brief lobs deinit
 *
 * @param[in] lobs LOBS base address
 */
void lobs_deinit(LOBS_Type *lobs);

/**
 * @brief lobs control config
 *
 * @param[in] lobs LOBS base address
 * @param[in] config control config structure pointer
 */
void lobs_ctrl_config(LOBS_Type *lobs, lobs_ctrl_config_t *config);

/**
 * @brief lobs two group mode config
 *
 * @param[in] lobs LOBS base address
 * @param[in] group one of the two group, @ref lobs_two_group_sel_t
 * @param[in] config two group mode config structure pointer
 */
void lobs_two_group_mode_config(LOBS_Type *lobs, lobs_two_group_sel_t group, lobs_two_group_mode_config_t *config);

/**
 * @brief lobs state config
 *
 * @param[in] lobs LOBS base address
 * @param[in] state one of state, @ref lobs_state_sel_t
 * @param[in] config state config structure pointer
 */
void lobs_state_config(LOBS_Type *lobs, lobs_state_sel_t state, lobs_state_config_t *config);

#if defined(HPM_IP_FEATURE_LOBS_TRIG_ADDR) && (HPM_IP_FEATURE_LOBS_TRIG_ADDR)
/**
 * @brief get lobs trig address
 *
 * @param[in] lobs LOBS base address
 *
 * @return uint32_t trace trig address
 */
uint32_t lobs_get_trig_address(LOBS_Type *lobs, lobs_trig_addr_idx_t idx);
#endif

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_LOBS_DRV_H */
