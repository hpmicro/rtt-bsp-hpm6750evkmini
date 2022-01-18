/*
 * Copyright (c) 2021 hpmicro
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "board.h"
#include "hpm_uart_drv.h"
#include "hpm_gpio_drv.h"
#include "hpm_mchtmr_drv.h"
#include "hpm_pmp_drv.h"
#include "assert.h"
#include "hpm_clock_drv.h"
#include "hpm_sysctl_drv.h"

#include <rthw.h>
#include <rtthread.h>
#include "drv_uart.h"
#include "drv_spi.h"
#include "drv_gpio.h"

/**
 * @brief FLASH configuration option definitions:
 * option[0]:
 *    [31:16] 0xfcf9 - FLASH configuration option tag
 *    [15:4]  0 - Reserved
 *    [3:0]   option words (exclude option[0])
 * option[1]:
 *    [31:28] Flash probe type
 *      0 - SFDP SDR / 1 - SFDP DDR
 *      2 - 1-4-4 Read (0xEB, 24-bit address) / 3 - 1-2-2 Read(0xBB, 24-bit address)
 *      4 - HyperFLASH 1.8V / 5 - HyperFLASH 3V
 *      6 - OctaBus DDR (SPI -> OPI DDR)
 *      8 - Xccela DDR (SPI -> OPI DDR)
 *      10 - EcoXiP DDR (SPI -> OPI DDR)
 *    [27:24] Command Pads after Power-on Reset
 *      0 - SPI / 1 - DPI / 2 - QPI / 3 - OPI
 *    [23:20] Command Pads after Configuring FLASH
 *      0 - SPI / 1 - DPI / 2 - QPI / 3 - OPI
 *    [19:16] Quad Enable Sequence (for the device support SFDP 1.0 only)
 *      0 - Not needed
 *      1 - QE bit is at bit 6 in Status Register 1
 *      2 - QE bit is at bit1 in Status Register 2
 *      3 - QE bit is at bit7 in Status Register 2
 *      4 - QE bit is at bit1 in Status Register 2 and should be programmed by 0x31
 *    [15:8] Dummy cycles
 *      0 - Auto-probed / detected / default value
 *      Others - User specified value, for DDR read, the dummy cycles should be 2 * cycles on FLASH datasheet
 *    [7:4] Misc.
 *      0 - Not used
 *      1 - SPI mode
 *      2 - Internal loopback
 *      3 - External DQS
 *    [3:0] Frequency option
 *      1 - 30MHz / 2 - 50MHz / 3 - 66MHz / 4 - 80MHz / 5 - 100MHz / 6 - 120MHz / 7 - 133MHz / 8 - 166MHz
 *
 * option[2] (Effective only if the bit[3:0] in option[0] > 1)
 *    [31:20]  Reserved
 *    [19:16] IO voltage
 *      0 - 3V / 1 - 1.8V
 *    [15:12] Pin group
 *      0 - 1st group / 1 - 2nd group
 *    [11:8] Connection selection
 *      0 - CA_CS0 / 1 - CB_CS0 / 2 - CA_CS0 + CB_CS0 (Two FLASH connected to CA and CB respectively)
 *    [7:0] Drive Strength
 *      0 - Default value
 * option[3] (Effective only if the bit[3:0] in option[0] > 2, required only for the QSPI NOR FLASH that not supports
 *              JESD216)
 *    [31:16] reserved
 *    [15:12] Sector Erase Command Option, not required here
 *    [11:8]  Sector Size Option, not required here
 *    [7:0] Flash Size Option
 *      0 - 4MB / 1 - 8MB / 2 - 16MB
 */
#if defined(FLASH_XIP) && FLASH_XIP
__attribute__ ((section(".nor_cfg_option"))) const uint32_t option[4] = {0xfcf90001, 0x00000007, 0x0, 0x0};
#endif

void os_tick_config(void);

void board_init_uart(UART_Type *ptr)
{
    if (ptr == HPM_UART0)
    {
        init_uart_pins(ptr);
        sysctl_config_clock(HPM_SYSCTL, clock_node_uart0, clock_source_osc0_clk0, 1);
        sysctl_add_resource_to_cpu0(HPM_SYSCTL, sysctl_resource_uart0);

        uart_config_t uart_config;
        uart_default_config(BOARD_APP_UART_BASE, &uart_config);
        uart_config.baudrate = BOARD_APP_UART_BAUDRATE;
        uart_config.src_freq_in_hz = BOARD_APP_UART_SRC_FREQ;
        uart_init(BOARD_APP_UART_BASE, &uart_config);
    }
}

void board_init(void)
{
    board_init_clock();
    board_init_pmp();
}

void board_init_sdram_pins(void)
{
    init_sdram_pins();
}

uint32_t board_init_dram_clock(void)
{
    /* Configure the SDRAM to 133MHz */
    clock_set_source_divider(clock_dram, clk_src_pll2_clk0, 2U);

    return clock_get_frequency(clock_dram);
}

void board_init_gpio_pins(void)
{
    init_gpio_pins();
}

void board_init_led_pins(void)
{
    gpio_enable_pin_output(BOARD_LED0_GPIO_CTRL, BOARD_LED0_GPIO_INDEX, BOARD_LED0_GPIO_PIN);
    gpio_enable_pin_output(BOARD_LED1_GPIO_CTRL, BOARD_LED1_GPIO_INDEX, BOARD_LED1_GPIO_PIN);
    gpio_enable_pin_output(BOARD_LED2_GPIO_CTRL, BOARD_LED2_GPIO_INDEX, BOARD_LED2_GPIO_PIN);

    gpio_write_pin(BOARD_LED0_GPIO_CTRL, BOARD_LED0_GPIO_INDEX, BOARD_LED0_GPIO_PIN, BOARD_LED_OFF);
    gpio_write_pin(BOARD_LED1_GPIO_CTRL, BOARD_LED1_GPIO_INDEX, BOARD_LED1_GPIO_PIN, BOARD_LED_OFF);
    gpio_write_pin(BOARD_LED2_GPIO_CTRL, BOARD_LED2_GPIO_INDEX, BOARD_LED2_GPIO_PIN, BOARD_LED_OFF);
}

void board_led_write(uint32_t index, bool state)
{
    switch (index)
    {
    case 0:
        gpio_write_pin(BOARD_LED0_GPIO_CTRL, BOARD_LED0_GPIO_INDEX, BOARD_LED0_GPIO_PIN, state);
        break;
    case 1:
        gpio_write_pin(BOARD_LED1_GPIO_CTRL, BOARD_LED1_GPIO_INDEX, BOARD_LED1_GPIO_PIN, state);
        break;
    case 2:
        gpio_write_pin(BOARD_LED2_GPIO_CTRL, BOARD_LED2_GPIO_INDEX, BOARD_LED2_GPIO_PIN, state);
        break;
    default:
        /* Suppress the toolchain warnings */
        break;
    }

}


void board_init_pmp(void)
{
    extern uint32_t __noncacheable_start__[];
    extern uint32_t __noncacheable_end__[];

    uint32_t start_addr = (uint32_t) __noncacheable_start__;
    uint32_t end_addr = (uint32_t) __noncacheable_end__;
    uint32_t length = end_addr - start_addr;

    if (length == 0) {
        return;
    }

    /* Ensure the address and the length are power of 2 aligned */
    assert((length & (length - 1U)) == 0U);
    assert((start_addr & (length - 1U)) == 0U);

    pmp_entry_t pmp_entry[1];
    pmp_entry[0].pmp_addr = PMP_NAPOT_ADDR(start_addr, length);
    pmp_entry[0].pmp_cfg.val = PMP_CFG(READ_EN, WRITE_EN, EXECUTE_EN, ADDR_MATCH_NAPOT, REG_UNLOCK);
    pmp_entry[0].pma_addr = PMA_NAPOT_ADDR(start_addr, length);
    pmp_entry[0].pma_cfg.val = PMA_CFG(ADDR_MATCH_NAPOT, MEM_TYPE_MEM_NON_CACHE_BUF, AMO_EN);

    pmp_config(&pmp_entry[0], ARRAY_SIZE(pmp_entry));
}

void board_init_clock(void)
{
    uint32_t cpu0_freq = clock_get_frequency(clock_cpu0);
    /* Select clock setting preset1 */
    sysctl_clock_set_preset(HPM_SYSCTL, 2);

    /* Add most Clocks to group 0 */
    clock_add_to_group(clock_cpu0, 0);
    clock_add_to_group(clock_mchtmr0, 0);
    clock_add_to_group(clock_axi0, 0);
    clock_add_to_group(clock_axi1, 0);
    clock_add_to_group(clock_axi2, 0);
    clock_add_to_group(clock_ahb, 0);
    clock_add_to_group(clock_dram, 0);
    clock_add_to_group(clock_xpi0, 0);
    clock_add_to_group(clock_xpi1, 0);
    clock_add_to_group(clock_gptmr0, 0);
    clock_add_to_group(clock_gptmr1, 0);
    clock_add_to_group(clock_gptmr2, 0);
    clock_add_to_group(clock_gptmr3, 0);
    clock_add_to_group(clock_gptmr4, 0);
    clock_add_to_group(clock_gptmr5, 0);
    clock_add_to_group(clock_gptmr6, 0);
    clock_add_to_group(clock_gptmr7, 0);
    clock_add_to_group(clock_uart0, 0);
    clock_add_to_group(clock_uart1, 0);
    clock_add_to_group(clock_uart2, 0);
    clock_add_to_group(clock_uart3, 0);
    clock_add_to_group(clock_i2c0, 0);
    clock_add_to_group(clock_i2c1, 0);
    clock_add_to_group(clock_i2c2, 0);
    clock_add_to_group(clock_i2c3, 0);
    clock_add_to_group(clock_spi0, 0);
    clock_add_to_group(clock_spi1, 0);
    clock_add_to_group(clock_spi2, 0);
    clock_add_to_group(clock_spi3, 0);
    clock_add_to_group(clock_can0, 0);
    clock_add_to_group(clock_can1, 0);
    clock_add_to_group(clock_can2, 0);
    clock_add_to_group(clock_can3, 0);
    clock_add_to_group(clock_display, 0);
    clock_add_to_group(clock_sdxc0, 0);
    clock_add_to_group(clock_sdxc1, 0);
    clock_add_to_group(clock_camera0, 0);
    clock_add_to_group(clock_camera1, 0);
    clock_add_to_group(clock_ptpc, 0);
    clock_add_to_group(clock_ref0, 0);
    clock_add_to_group(clock_ref1, 0);
    clock_add_to_group(clock_watchdog0, 0);
    clock_add_to_group(clock_eth0, 0);
    clock_add_to_group(clock_eth1, 0);
    clock_add_to_group(clock_sdp, 0);
    clock_add_to_group(clock_xdma, 0);
    clock_add_to_group(clock_ram0, 0);
    clock_add_to_group(clock_ram1, 0);
    clock_add_to_group(clock_usb0, 0);
    clock_add_to_group(clock_usb1, 0);
    clock_add_to_group(clock_jpeg, 0);
    clock_add_to_group(clock_pdma, 0);
    clock_add_to_group(clock_kman, 0);
    clock_add_to_group(clock_gpio, 0);
    clock_add_to_group(clock_mbx0, 0);
    clock_add_to_group(clock_hdma, 0);
    clock_add_to_group(clock_rng, 0);
    clock_add_to_group(clock_mot0, 0);
    clock_add_to_group(clock_mot1, 0);
    clock_add_to_group(clock_mot2, 0);
    clock_add_to_group(clock_mot3, 0);
    clock_add_to_group(clock_acmp, 0);
    clock_add_to_group(clock_dao, 0);
    clock_add_to_group(clock_msyn, 0);
    clock_add_to_group(clock_lmm0, 0);
    clock_add_to_group(clock_lmm1, 0);
    clock_add_to_group(clock_pdm, 0);

    clock_add_to_group(clock_adc0, 0);
    clock_add_to_group(clock_adc1, 0);
    clock_add_to_group(clock_adc2, 0);
    clock_add_to_group(clock_adc3, 0);

    clock_add_to_group(clock_i2s0, 0);
    clock_add_to_group(clock_i2s1, 0);
    clock_add_to_group(clock_i2s2, 0);
    clock_add_to_group(clock_i2s3, 0);

    /* Add the CPU1 clock to Group1 */
    clock_add_to_group(clock_mchtmr1, 1);
    clock_add_to_group(clock_mbx1, 1);

    /* Connect Group0 to CPU0 */
    clock_connect_group_to_cpu(0, 0);
    /* Configure CPU0 to 648MHz */
    clock_set_source_divider(clock_cpu0, clk_src_pll0_clk0, 1);
    clock_set_source_divider(clock_cpu1, clk_src_pll0_clk0, 1);
    /* Connect Group1 to CPU1 */
    clock_connect_group_to_cpu(1, 1);
    /* while(!sysctl_resource_is_busy(HPM_SYSCTL, SYSCTL_RESOURCE_CLK_TOP_CPU0)); */
}

uint32_t board_init_uart_clock(UART_Type *ptr)
{
    uint32_t freq = 0;

    if (ptr == HPM_UART0)
    {
        clock_set_source_divider(clock_uart0, clk_src_osc24m, 1);
        freq = clock_get_frequency(clock_uart0);
    }
    else if (ptr == HPM_UART1)
    {
        clock_set_source_divider(clock_uart1, clk_src_osc24m, 1);
        freq = clock_get_frequency(clock_uart1);
    }
    else if (ptr == HPM_UART2)
    {
        clock_set_source_divider(clock_uart2, clk_src_osc24m, 1);
        freq = clock_get_frequency(clock_uart2);
    }
    else if (ptr == HPM_UART3)
    {
        clock_set_source_divider(clock_uart3, clk_src_osc24m, 1);
        freq = clock_get_frequency(clock_uart3);
    }
    else if (ptr == HPM_UART4)
    {
        clock_set_source_divider(clock_uart4, clk_src_osc24m, 1);
        freq = clock_get_frequency(clock_uart4);
    }
    else if (ptr == HPM_UART5)
    {
        clock_set_source_divider(clock_uart5, clk_src_osc24m, 1);
        freq = clock_get_frequency(clock_uart5);
    }
    else if (ptr == HPM_UART6)
    {
        clock_set_source_divider(clock_uart6, clk_src_osc24m, 1);
        freq = clock_get_frequency(clock_uart6);
    }
    else if (ptr == HPM_UART7)
    {
        clock_set_source_divider(clock_uart7, clk_src_osc24m, 1);
        freq = clock_get_frequency(clock_uart7);
    }
    else if (ptr == HPM_UART8)
    {
        clock_set_source_divider(clock_uart8, clk_src_osc24m, 1);
        freq = clock_get_frequency(clock_uart8);
    }
    else if (ptr == HPM_UART9)
    {
        clock_set_source_divider(clock_uart9, clk_src_osc24m, 1);
        freq = clock_get_frequency(clock_uart9);
    }
    else if (ptr == HPM_UART10)
    {
        clock_set_source_divider(clock_uart10, clk_src_osc24m, 1);
        freq = clock_get_frequency(clock_uart10);
    }
    else if (ptr == HPM_UART11)
    {
        clock_set_source_divider(clock_uart11, clk_src_osc24m, 1);
        freq = clock_get_frequency(clock_uart11);
    }
    else if (ptr == HPM_UART12)
    {
        clock_set_source_divider(clock_uart12, clk_src_osc24m, 1);
        freq = clock_get_frequency(clock_uart12);
    }
    else if (ptr == HPM_UART13)
    {
        clock_set_source_divider(clock_uart13, clk_src_osc24m, 1);
        freq = clock_get_frequency(clock_uart13);
    }
    else if (ptr == HPM_UART14)
    {
        clock_set_source_divider(clock_uart14, clk_src_osc24m, 1);
        freq = clock_get_frequency(clock_uart14);
    }
    else if (ptr == HPM_UART15)
    {
        clock_set_source_divider(clock_uart15, clk_src_osc24m, 1);
        freq = clock_get_frequency(clock_uart15);
    }
    else
    {
        /* Unsupported instance */
    }

    return freq;
}

uint32_t board_init_spi_clock(SPI_Type *ptr)
{
    uint32_t freq = 0;

    if (ptr == HPM_SPI0)
    {
        clock_enable(clock_spi0);
        clock_set_source_divider(clock_spi0, clk_src_pll1_clk1, 5);
        freq = clock_get_frequency(clock_spi0);
    }
    else if (ptr == HPM_SPI1)
    {
        clock_enable(clock_spi1);
        clock_set_source_divider(clock_spi1, clk_src_pll1_clk1, 5);
        freq = clock_get_frequency(clock_spi1);
    }
    else if (ptr == HPM_SPI2)
    {
        clock_enable(clock_spi2);
        clock_set_source_divider(clock_spi2, clk_src_pll1_clk1, 5);
        freq = clock_get_frequency(clock_spi2);
    }
    else if (ptr == HPM_SPI3)
    {
        clock_enable(clock_spi3);
        clock_set_source_divider(clock_spi3, clk_src_pll1_clk1, 5);
        freq = clock_get_frequency(clock_spi3);
    }
    else
    {

    }

    return freq;
}

void os_tick_config(void)
{
    sysctl_config_clock(HPM_SYSCTL, clock_node_mchtmr0, clock_source_osc0_clk0, 1);
    sysctl_add_resource_to_cpu0(HPM_SYSCTL, sysctl_resource_mchtmr0);

    mchtmr_set_compare_value(HPM_MCHTMR, BOARD_MCHTMR_FREQ_IN_HZ / RT_TICK_PER_SECOND);

    enable_mchtmr_irq();
}

void rt_hw_board_init(void)
{
    board_init();

    /* Configure the OS Tick */
    os_tick_config();

#ifdef BSP_USING_UART
    /* Initialize UART device */
    rt_hw_uart_init();
#endif

#ifdef BSP_USING_SPI
    /* Initialize SPI device */
    rt_hw_spi_init();
#endif

#ifdef BSP_USING_GPIO
    /* Initialize GPIO device */
    rt_hw_pin_init();
#endif

    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

    /* initialize memory system */
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
}

void rt_hw_console_output(const char *str)
{
    while (*str != '\0')
    {
        uart_send_byte(BOARD_APP_UART_BASE, *str++);
    }
}

void mchtmr_isr(void)
{
    HPM_MCHTMR->MTIMECMP = HPM_MCHTMR->MTIME + BOARD_MCHTMR_FREQ_IN_HZ / RT_TICK_PER_SECOND;

    rt_interrupt_enter();
    rt_tick_increase();
    rt_interrupt_leave();
}
