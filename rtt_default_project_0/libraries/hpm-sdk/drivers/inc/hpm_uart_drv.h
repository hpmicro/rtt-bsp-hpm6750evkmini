/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_UART_DRV_H
#define HPM_UART_DRV_H
#include "hpm_uart_regs.h"

typedef enum parity {
    parity_none = 0,
    parity_odd,
    parity_even,
    parity_always_1,
    parity_always_0,
} parity_setting_t;

typedef enum num_of_stop_bits {
    stop_bits_1 = 0,
    stop_bits_1_5,
    stop_bits_2,
} num_of_stop_bits_t;

typedef enum word_length {
    word_length_5_bits = 0,
    word_length_6_bits,
    word_length_7_bits,
    word_length_8_bits,
} word_length_t;

typedef enum uart_fifo_trg_lvl {
    uart_rx_fifo_trg_not_empty = 0,
    uart_rx_fifo_trg_gt_one_quarter = 1,
    uart_rx_fifo_trg_gt_half = 2,
    uart_rx_fifo_trg_gt_three_quarters = 3,

    uart_tx_fifo_trg_not_full = 0,
    uart_tx_fifo_trg_lt_three_quarters = 1,
    uart_tx_fifo_trg_lt_half = 2,
    uart_tx_fifo_trg_lt_one_quarter = 3,
} uart_fifo_trg_lvl_t;

typedef enum uart_signal {
    uart_signal_out1 = UART_MCR_OUT1_MASK,
    uart_signal_out2 = UART_MCR_OUT2_MASK,
    uart_signal_rts = UART_MCR_RTS_MASK,
    uart_signal_dtr = UART_MCR_DTR_MASK,
} uart_signal_t;

typedef enum uart_signal_level {
    uart_signal_level_high,
    uart_signal_level_low,
} uart_signal_level_t;

typedef enum uart_modem_stat {
    uart_modem_stat_dcd = UART_MSR_DCD_MASK,
    uart_modem_stat_ri = UART_MSR_RI_MASK,
    uart_modem_stat_dsr = UART_MSR_DSR_MASK,
    uart_modem_stat_cts = UART_MSR_CTS_MASK,
    uart_modem_stat_dcd_changed = UART_MSR_DDCD_MASK,
    uart_modem_stat_ri_changed = UART_MSR_TERI_MASK,
    uart_modem_stat_dsr_changed = UART_MSR_DDSR_MASK,
    uart_modem_stat_dcts_changed = UART_MSR_DCTS_MASK,
} uart_modem_stat_t;

typedef enum uart_intr_enable {
    uart_intr_rx_data_avail_or_timeout = UART_IER_ERBI_MASK,
    uart_intr_tx_slot_avail = UART_IER_ETHEI_MASK,
    uart_intr_rx_line_stat = UART_IER_ELSI_MASK,
    uart_intr_modem_stat = UART_IER_EMSI_MASK,
} uart_intr_enable_t;

typedef enum uart_intr_id {
    uart_intr_id_modem_stat = 0x0,
    uart_intr_id_tx_slot_avail = 0x2,
    uart_intr_id_rx_data_avail = 0x4,
    uart_intr_id_rx_line_stat = 0x6,
    uart_intr_id_rx_timeout = 0xc,
} uart_intr_id_t;

typedef enum uart_stat {
    uart_stat_data_ready = UART_LSR_DR_MASK,
    uart_stat_overrun_error = UART_LSR_OE_MASK,
    uart_stat_parity_error = UART_LSR_PE_MASK,
    uart_stat_framing_error = UART_LSR_FE_MASK,
    uart_stat_line_break = UART_LSR_LBREAK_MASK,
    uart_stat_tx_slot_avail = UART_LSR_THRE_MASK,
    uart_stat_transmitter_empty = UART_LSR_TEMT_MASK,
    uart_stat_rx_fifo_error = UART_LSR_ERRF_MASK,
} uart_stat_t;

typedef struct uart_modem_config {
    bool auto_flow_ctrl_en;
    bool loop_back_en;
    bool set_out1_high;
    bool set_out2_high;
    bool set_rts_high;
    bool set_dtr_high;
} uart_modem_config_t;

typedef struct uart_config {
    uint32_t src_freq_in_hz;
    uint32_t baudrate;
    uint8_t num_of_stop_bits;
    uint8_t word_length;
    uint8_t parity;
    uint8_t osc;  /* over sample control ratio*/
    uint8_t tx_fifo_level;
    uint8_t rx_fifo_level;
    bool dma_enable;
    bool fifo_enable;
    uart_modem_config_t modem_config;
} uart_config_t;

#ifdef __cplusplus
extern "C" {
#endif

static inline uint8_t uart_get_fifo_size(UART_Type *ptr)
{
    return 16 << ((ptr->CFG & UART_CFG_FIFOSIZE_MASK) >> UART_CFG_FIFOSIZE_SHIFT);
}

static inline void uart_reset_tx_fifo(UART_Type *ptr)
{
    if (ptr->FCR & UART_FCR_FIFOE_MASK) {
        ptr->FCR |= UART_FCR_TFIFORST_MASK;
    }
}

static inline void uart_reset_rx_fifo(UART_Type *ptr)
{
    if (ptr->FCR & UART_FCR_FIFOE_MASK) {
        ptr->FCR |= UART_FCR_RFIFORST_MASK;
    }
}

static inline void uart_reset_all_fifo(UART_Type *ptr)
{
    if (ptr->FCR & UART_FCR_FIFOE_MASK) {
        ptr->FCR |= UART_FCR_RFIFORST_MASK | UART_FCR_TFIFORST_MASK;
    }
}

/*
 * configure modem feature
 */
static inline void uart_modem_enable_loopback(UART_Type *ptr, bool enable)
{
    ptr->MCR = (ptr->MCR & ~UART_MCR_LOOP_MASK) | UART_MCR_LOOP_SET(enable);
}

static inline void uart_modem_enable_auto_flow_control(UART_Type *ptr, bool enable)
{
    ptr->MCR = (ptr->MCR & ~UART_MCR_AFE_MASK) | UART_MCR_AFE_SET(enable);
}

/*
 * configure modem
 */
static inline void uart_modem_config(UART_Type *ptr, uart_modem_config_t *config)
{
    ptr->MCR = UART_MCR_AFE_SET(config->auto_flow_ctrl_en)
        | UART_MCR_LOOP_SET(config->loop_back_en)
        | UART_MCR_OUT1_SET(!config->set_out1_high) 
        | UART_MCR_OUT2_SET(!config->set_out2_high) 
        | UART_MCR_RTS_SET(!config->set_rts_high) 
        | UART_MCR_DTR_SET(!config->set_dtr_high); 
}

/*
 * access uart scratch
 */
static inline uint8_t uart_get_scratch(UART_Type *ptr)
{
    return ptr->SCR & 0xFF;
}

static inline void uart_save_to_scratch(UART_Type *ptr, uint8_t data)
{
    ptr->SCR = data;
}

/*
 * check modem status
 */
static inline uint8_t uart_check_modem_status(UART_Type *ptr, uart_modem_stat_t mask)
{
    return (ptr->MSR & mask) & 0xFF;
}

/*
 * enable/disable interrupt
 */
static inline void uart_enable_irq(UART_Type *ptr, uart_intr_enable_t irq, bool enable)
{
    ptr->IER = ((ptr->IER & ~irq) | (enable ? irq : 0));
}

/*
 * get interrupt identification
 */
static inline uint8_t uart_get_irq_id(UART_Type *ptr)
{
    return (ptr->IIR & UART_IIR_INTRID_MASK);
}

/*
 * check uart status according to the given status mask
 */
static inline bool uart_check_status(UART_Type *ptr, uart_stat_t mask)
{
    return ptr->LSR & mask;
}

void uart_default_config(UART_Type *ptr, uart_config_t *config);

/*
 * initialization
 */
hpm_stat_t uart_init(UART_Type *ptr, uart_config_t *config);

/*
 * put one byte
 */
hpm_stat_t uart_send_byte(UART_Type *ptr, uint8_t c);

/*
 * get one byte
 */
hpm_stat_t uart_receive_byte(UART_Type *ptr, uint8_t *c);

/*
 * set uart signal output level
 */
void uart_set_signal_level(UART_Type *ptr,
                           uart_signal_t singal,
                           uart_signal_level_t level);

/*
 * flush sending buffer/fifo
 */
hpm_stat_t uart_flush(UART_Type *ptr);

/*
 * receive bytes
 */
hpm_stat_t uart_receive_data(UART_Type *ptr, uint8_t *source, uint32_t size_in_byte);

/*
 * send bytes
 */
hpm_stat_t uart_send_data(UART_Type *ptr, uint8_t *source, uint32_t size_in_byte);

#ifdef __cplusplus
}
#endif

#endif    /* HPM_UART_DRV_H */
