/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stdarg.h>
#include <stdio.h>
#include "board.h"
#include "hpm_clock_drv.h"
#include "hpm_mchtmr_drv.h"
#include "hpm_dma_drv.h"
#include "hpm_dram_drv.h"
#include "hpm_sysctl_drv.h"
#include "hpm_l1c_drv.h"

#define SIZE_PER_TEST   (0x00100000UL)
#define DST_ADDRESS     (0x40000000UL)
#define SRC_ADDRESS     (0x01080000UL)
#define TEST_DATA_LENGTH_IN_BYTE (0x2000000UL)

#ifndef TEST_DMA_CONTROLLER 
#define TEST_DMA_CONTROLLER HPM_XDMA
#endif

#ifndef TEST_DMA_IRQ
#define TEST_DMA_IRQ BOARD_APP_XDMA_IRQ 
#endif

#ifndef TEST_DMA_CHANNEL
#define TEST_DMA_CHANNEL (0U)
#endif

#ifndef USE_IRQ
#define USE_IRQ (1)
#endif

#ifndef DRAM_CLOCK_NAME
#define DRAM_CLOCK_NAME clock_dram
#endif

#ifndef TIMER_CLOCK_NAME
#define TIMER_CLOCK_NAME clock_mchtmr0
#endif

uint32_t timer_freq_in_hz;

volatile bool dma_transfer_done = false;
volatile bool dma_transfer_error = false;

static void reset_transfer_status(void)
{
    dma_transfer_done = false;
    dma_transfer_error = false;
}

static void prepare_test_data(uint8_t *buffer, uint32_t size_in_byte)
{
    uint32_t i = 0;
    for (i = 0; i < size_in_byte; i++) {
        buffer[i] = i;
    }
    if (l1c_dc_is_enabled()) {
        l1c_dc_flush((uint32_t) buffer, size_in_byte);
    }
}

static uint32_t compare_buffers(uint8_t *expected, uint8_t *actual, uint32_t size, bool verbose)
{
    uint32_t i, errors;
    printf("compare data between source address 0x%x and destination address 0x%x: ",
            (uint32_t *)expected, (uint32_t *)actual);
    if (verbose) {
        printf("\n");
    }
    if (l1c_dc_is_enabled()) {
        l1c_dc_invalidate((uint32_t)actual, size);
    }
    for(i = 0, errors = 0; i < size; i++) {
        if (*(expected + i) != *(actual + i)) {
            if (verbose) {
                printf("[%x]: expected: 0x%x, actual: 0x%x\n",
                        i, *(expected + i), *(actual + i));
            }
            errors++;
        }
    }
    if (errors) {
        printf(" ! [%d] errors encounted in total\n",errors);
    } else {
        printf(" all data matches\n");
    }
    return errors;
}

static void init_sdram()
{
    uint32_t dram_clk_in_hz;
    board_init_sdram_pins();
    dram_clk_in_hz = board_init_dram_clock();

    dram_config_t config = {0};
    dram_sdram_config_t sdram_config = {0};

    dram_default_config(HPM_DRAM, &config);
    config.dqs = DRAM_DQS_INTERNAL;
    dram_init(HPM_DRAM, &config);

    sdram_config.bank_num = DRAM_SDRAM_BANK_NUM_4;
    sdram_config.prescaler = 0x3;
    sdram_config.burst_len_in_byte = 8;
    sdram_config.auto_refresh_count_in_one_burst = 1;
    sdram_config.col_addr_bits = DRAM_SDRAM_COLUMN_ADDR_9_BITS;
    sdram_config.cas_latency = DRAM_SDRAM_CAS_LATENCY_3;

    sdram_config.precharge_to_act_in_ns = 18;   /* Trp */
    sdram_config.act_to_rw_in_ns = 18;          /* Trcd */
    sdram_config.refresh_recover_in_ns = 70;     /* Trfc/Trc */
    sdram_config.write_recover_in_ns = 12;      /* Twr/Tdpl */
    sdram_config.cke_off_in_ns = 42;             /* Trcd */
    sdram_config.act_to_precharge_in_ns = 42;   /* Tras */

    sdram_config.self_refresh_recover_in_ns = 66;   /* Txsr */
    sdram_config.refresh_to_refresh_in_ns = 66;     /* Trfc/Trc */
    sdram_config.act_to_act_in_ns = 12;             /* Trrd */
    sdram_config.idle_timeout_in_ns = 6;
    sdram_config.cs_mux_pin = DRAM_IO_MUX_NOT_USED;

    sdram_config.cs = BOARD_SDRAM_CS;
    sdram_config.base_address = BOARD_SDRAM_ADDRESS;
    sdram_config.size_in_byte = BOARD_SDRAM_SIZE;
    sdram_config.port_size = BOARD_SDRAM_PORT_SIZE;
    sdram_config.refresh_count = BOARD_SDRAM_REFRESH_COUNT;
    sdram_config.refresh_in_ms = BOARD_SDRAM_REFRESH_IN_MS;
    sdram_config.data_width_in_byte = BOARD_SDRAM_DATA_WIDTH_IN_BYTE;
    sdram_config.delay_cell_value = 29;

    dram_config_sdram(HPM_DRAM, dram_clk_in_hz, &sdram_config);
    printf("dram has been configured @ %dHz\n", dram_clk_in_hz);
}

/* descriptor should be 8-byte aligned */
dma_linked_descriptor_t descriptors[4] __attribute__ ((aligned(8)));

void isr_dma(void)
{
    volatile hpm_stat_t stat;
    dma_transfer_done = true;
    stat = dma_check_transfer_status(TEST_DMA_CONTROLLER, TEST_DMA_CHANNEL);
    if (stat != status_dma_transfer_done) {
        dma_transfer_error = true;
    }
}

SDK_DECLARE_EXT_ISR_M(TEST_DMA_IRQ, isr_dma)

#define OFFSET_PER_DESCRIPTOR 0x1000
void test_chained_transfer(bool verbose)
{
    uint32_t i, errors;
    dma_channel_config_t ch_config = {0};

    intc_m_enable_irq_with_priority(TEST_DMA_IRQ, 1);

    prepare_test_data((uint8_t *)SRC_ADDRESS, SIZE_PER_TEST);
    for (i = 0; i < ARRAY_SIZE(descriptors); i++) {
        descriptors[i].trans_size = (SIZE_PER_TEST / ARRAY_SIZE(descriptors)) >> DMA_TRANSFER_WIDTH_BYTE;
        descriptors[i].src_addr = core_local_mem_to_sys_address(HPM_CORE0, SRC_ADDRESS + i * OFFSET_PER_DESCRIPTOR);
        descriptors[i].dst_addr = core_local_mem_to_sys_address(HPM_CORE0, DST_ADDRESS + i * SIZE_PER_TEST);
        descriptors[i].ctrl = DMA_CHCTRL_CTRL_SRCWIDTH_SET(DMA_TRANSFER_WIDTH_BYTE)
                | DMA_CHCTRL_CTRL_DSTWIDTH_SET(DMA_TRANSFER_WIDTH_BYTE)
                | DMA_CHCTRL_CTRL_SRCBURSTSIZE_SET(DMA_NUM_TRANSFER_PER_BURST_8T);
        if (i == ARRAY_SIZE(descriptors) - 1) {
            descriptors[i].linked_ptr = 0;
        } else {
            descriptors[i].linked_ptr = core_local_mem_to_sys_address(HPM_CORE0, (uint32_t)&descriptors[i+1]);
        }
    }
    ch_config.src_addr = core_local_mem_to_sys_address(HPM_CORE0, SRC_ADDRESS);
    ch_config.dst_addr = core_local_mem_to_sys_address(HPM_CORE0, DST_ADDRESS);
    ch_config.src_burst_size = DMA_NUM_TRANSFER_PER_BURST_8T;
    ch_config.src_width = DMA_TRANSFER_WIDTH_BYTE;
    ch_config.dst_width = DMA_TRANSFER_WIDTH_BYTE;
    ch_config.size_in_byte = SIZE_PER_TEST / ARRAY_SIZE(descriptors);
    ch_config.linked_ptr = core_local_mem_to_sys_address(HPM_CORE0, (uint32_t)&descriptors[0]);

    reset_transfer_status();
    if (status_success != dma_setup_channel(TEST_DMA_CONTROLLER, TEST_DMA_CHANNEL, &ch_config)) {
        printf(" dma setup channel failed\n");
        return;
    }
    printf(" dma setup channel done\n");

    while (!dma_transfer_done) {
        __asm("nop");
    }
    
    if (dma_transfer_error) {
        printf(" chained transfer failed\n");
        return;
    }
    for (i = 0; i < ARRAY_SIZE(descriptors); i++) {
        errors = compare_buffers((uint8_t *)descriptors[i].src_addr, (uint8_t *)descriptors[i].dst_addr, descriptors[i].trans_size << DMA_TRANSFER_WIDTH_BYTE, false);
        if (!errors) {
            printf(" [%d]: data match\n", i);
        } else {
            printf(" [%d]: !!! data mismatch\n", i);
        }
    }
}

void test_unchained_transfer(uint32_t src, uint32_t dst, bool verbose)
{
    uint64_t elapsed = 0, now;
    hpm_stat_t stat;
    uint32_t errors, burst_len_in_byte;
#if USE_IRQ
    intc_m_enable_irq_with_priority(TEST_DMA_IRQ, 1);
#endif

    for (int32_t i = DMA_NUM_TRANSFER_PER_BURST_1024T; i >= 0; i--) {
        reset_transfer_status();
        burst_len_in_byte = (1 << i) * (1 << DMA_SOC_TRANSFER_WIDTH_MAX);
        src += burst_len_in_byte;
        prepare_test_data((uint8_t *)src, SIZE_PER_TEST);

        printf("dma transferring data from 0x%x to 0x%x, burst size: %d bytes\n",
                src, dst, burst_len_in_byte);
        now = mchtmr_get_count(HPM_MCHTMR);
        stat = dma_start_memcpy(TEST_DMA_CONTROLLER, 0,
                (uint32_t)core_local_mem_to_sys_address(HPM_CORE0, dst),
                (uint32_t)core_local_mem_to_sys_address(HPM_CORE0, src),
                SIZE_PER_TEST, burst_len_in_byte);
        if (stat != status_success) {
            printf("failed to start dma transfer\n");
            continue;
        }

#if USE_IRQ
        while (!dma_transfer_done) {
            __asm("nop");
        }
#else
        hpm_stat_t stat;
        do {
            stat = dma_check_transfer_status(TEST_DMA_CONTROLLER, TEST_DMA_CHANNEL);
        } while ((stat == status_dma_transfer_ongoing));
        if (stat != status_dma_transfer_done) {
            dma_transfer_error = true;
        }
#endif
        elapsed += (mchtmr_get_count(HPM_MCHTMR) - now);
        printf("rw throughput: %.2f KB/s\n",
                (double) (SIZE_PER_TEST >> 10) * timer_freq_in_hz / elapsed);

        if (dma_transfer_error) {
            printf(" dma transfer failed\n");
            continue;
        }

        errors = compare_buffers((uint8_t *)src, (uint8_t *)dst, SIZE_PER_TEST, false);
        if (errors) {
            printf("compare failed: %d errors\n", errors);
            continue;
        }
    }
}

int main(void)
{
    board_init();
    board_init_console();

    timer_freq_in_hz = clock_get_frequency(TIMER_CLOCK_NAME);
    init_sdram();

    printf("dma example start\n");

    printf("unchained transfer\n");
    printf("write testing\n");
    test_unchained_transfer(SRC_ADDRESS, DST_ADDRESS, false);
    printf("read testing\n");
    test_unchained_transfer(DST_ADDRESS, SRC_ADDRESS, false);

    printf("chained transfer\n");
    test_chained_transfer(false);

    printf("dma example end\n");
    return 0;
}
