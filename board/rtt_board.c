/*
 * Copyright (c) 2021-2022 HPMicro
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "board.h"
#include "rtt_board.h"
#include "hpm_uart_drv.h"
#include "hpm_gpio_drv.h"
#include "hpm_pmp_drv.h"
#include "assert.h"
#include "hpm_clock_drv.h"
#include "hpm_sysctl_drv.h"
#include <rthw.h>
#include <rtthread.h>
#include "hpm_dma_mgr.h"
#include "hpm_rtt_os_tick.h"
#include "hpm_l1c_drv.h"

extern int rt_hw_uart_init(void);

void rtt_os_tick_clock(void)
{
#ifdef HPM_USING_VECTOR_PREEMPTED_MODE
    clock_add_to_group(BOARD_OS_TIMER_CLK_NAME, 0);
#else
    clock_add_to_group(clock_mchtmr0, 0);
#endif
}

void rtt_board_init(void)
{
    rtt_os_tick_clock();
    board_init_clock();
    board_init_console();
    board_init_pmp();

    dma_mgr_init();

    /* initialize memory system */
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);

    /* Configure the OS Tick */
    os_tick_config();

    /* Initialize the UART driver first, because later driver initialization may require the rt_kprintf */
    rt_hw_uart_init();

    /* Set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
}

void app_init_led_pins(void)
{
    gpio_set_pin_output(APP_LED0_GPIO_CTRL, APP_LED0_GPIO_INDEX, APP_LED0_GPIO_PIN);
    gpio_set_pin_output(APP_LED1_GPIO_CTRL, APP_LED1_GPIO_INDEX, APP_LED1_GPIO_PIN);
    gpio_set_pin_output(APP_LED2_GPIO_CTRL, APP_LED2_GPIO_INDEX, APP_LED2_GPIO_PIN);

    gpio_write_pin(APP_LED0_GPIO_CTRL, APP_LED0_GPIO_INDEX, APP_LED0_GPIO_PIN, APP_LED_OFF);
    gpio_write_pin(APP_LED1_GPIO_CTRL, APP_LED1_GPIO_INDEX, APP_LED1_GPIO_PIN, APP_LED_OFF);
    gpio_write_pin(APP_LED2_GPIO_CTRL, APP_LED2_GPIO_INDEX, APP_LED2_GPIO_PIN, APP_LED_OFF);
}

void app_led_write(uint32_t index, bool state)
{
    switch (index)
    {
    case 0:
        gpio_write_pin(APP_LED0_GPIO_CTRL, APP_LED0_GPIO_INDEX, APP_LED0_GPIO_PIN, state);
        break;
    case 1:
        gpio_write_pin(APP_LED1_GPIO_CTRL, APP_LED1_GPIO_INDEX, APP_LED1_GPIO_PIN, state);
        break;
    case 2:
        gpio_write_pin(APP_LED2_GPIO_CTRL, APP_LED2_GPIO_INDEX, APP_LED2_GPIO_PIN, state);
        break;
    default:
        /* Suppress the toolchain warnings */
        break;
    }
}

void rt_hw_console_output(const char *str)
{
    while (*str != '\0')
    {
        uart_send_byte(BOARD_APP_UART_BASE, *str++);
    }
}

void app_init_usb_pins(void)
{
    board_init_usb(HPM_USB0);
}

void rt_hw_cpu_reset(void)
{
    HPM_PPOR->RESET_ENABLE = (1UL << 31);
    HPM_PPOR->RESET_HOT &= ~(1UL << 31);
    HPM_PPOR->RESET_COLD |= (1UL << 31);

    HPM_PPOR->SOFTWARE_RESET = 1000U;
    while(1) {

    }
}

MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_reset, reset, reset the board);

#ifdef RT_USING_CACHE
void rt_hw_cpu_dcache_ops(int ops, void *addr, int size)
{
    if (ops == RT_HW_CACHE_FLUSH) {
        l1c_dc_flush((uint32_t)addr, size);
    } else {
        l1c_dc_invalidate((uint32_t)addr, size);
    }
}
#endif

uint32_t rtt_board_init_adc12_clock(ADC12_Type *ptr, bool clk_src_ahb)
{
    uint32_t freq = 0;

    if (ptr == HPM_ADC0) {
        if (clk_src_ahb) {
            /* Configure the ADC clock from AHB (@200MHz by default)*/
            clock_set_adc_source(clock_adc0, clk_adc_src_ahb0);
        } else {
            /* Configure the ADC clock from pll1_clk1 divided by 2 (@200MHz by default) */
            clock_set_adc_source(clock_adc0, clk_adc_src_ana0);
            clock_set_source_divider(clock_ana0, clk_src_pll1_clk1, 2U);
        }
        clock_add_to_group(clock_adc0, 0);
        freq = clock_get_frequency(clock_adc0);
    } else if (ptr == HPM_ADC1) {
        if (clk_src_ahb) {
            /* Configure the ADC clock from AHB (@200MHz by default)*/
            clock_set_adc_source(clock_adc1, clk_adc_src_ahb0);
        } else {
            /* Configure the ADC clock from pll1_clk1 divided by 2 (@200MHz by default) */
            clock_set_adc_source(clock_adc1, clk_adc_src_ana1);
            clock_set_source_divider(clock_ana1, clk_src_pll1_clk1, 2U);
        }
        clock_add_to_group(clock_adc1, 0);
        freq = clock_get_frequency(clock_adc1);
    } else if (ptr == HPM_ADC2) {
        if (clk_src_ahb) {
            /* Configure the ADC clock from AHB (@200MHz by default)*/
            clock_set_adc_source(clock_adc2, clk_adc_src_ahb0);
        } else {
            /* Configure the ADC clock from pll1_clk1 divided by 2 (@200MHz by default) */
            clock_set_adc_source(clock_adc2, clk_adc_src_ana2);
            clock_set_source_divider(clock_ana2, clk_src_pll1_clk1, 2U);
        }
        clock_add_to_group(clock_adc2, 0);
        freq = clock_get_frequency(clock_adc2);
    }

    return freq;
}

uint32_t rtt_board_init_adc16_clock(ADC16_Type *ptr, bool clk_src_ahb)
{
    uint32_t freq = 0;

    if (ptr == HPM_ADC3) {
        if (clk_src_ahb) {
            /* Configure the ADC clock from AHB (@200MHz by default)*/
            clock_set_adc_source(clock_adc3, clk_adc_src_ahb0);
        } else {
            /* Configure the ADC clock from pll1_clk1 divided by 2 (@200MHz by default) */
            clock_set_adc_source(clock_adc3, clk_adc_src_ana2);
            clock_set_source_divider(clock_ana2, clk_src_pll1_clk1, 2U);
        }
        clock_add_to_group(clock_adc3, 0);
        freq = clock_get_frequency(clock_adc3);
    }

    return freq;
}

uint32_t rtt_board_init_i2s_clock(I2S_Type *ptr)
{
    uint32_t freq = 0;

    if (ptr == HPM_I2S0) {
        clock_add_to_group(clock_i2s0, 0);

        sysctl_config_clock(HPM_SYSCTL, clock_node_aud0, clock_source_pll3_clk0, 25);
        sysctl_set_adc_i2s_clock_mux(HPM_SYSCTL, clock_node_i2s0, clock_source_i2s_aud0_clk);

        freq = clock_get_frequency(clock_i2s0);
    } else if (ptr == HPM_I2S1) {
        clock_add_to_group(clock_i2s1, 0);

        sysctl_config_clock(HPM_SYSCTL, clock_node_aud1, clock_source_pll3_clk0, 25);
        sysctl_set_adc_i2s_clock_mux(HPM_SYSCTL, clock_node_i2s1, clock_source_i2s_aud1_clk);

        freq = clock_get_frequency(clock_i2s1);
    } else {
        ;
    }

    return freq;
}

uint32_t rtt_board_init_pwm_clock(PWM_Type *ptr)
{
    uint32_t freq = 0;
    if (ptr == HPM_PWM0) {
        clock_add_to_group(clock_mot0, 0);
        freq = clock_get_frequency(clock_mot0);
    } else if (ptr == HPM_PWM1) {
        clock_add_to_group(clock_mot1, 0);
        freq = clock_get_frequency(clock_mot1);
    } else if (ptr == HPM_PWM2) {
        clock_add_to_group(clock_mot2, 0);
        freq = clock_get_frequency(clock_mot2);
    } else if (ptr == HPM_PWM3) {
        clock_add_to_group(clock_mot3, 0);
        freq = clock_get_frequency(clock_mot3);
    } else {

    }
    return freq;
}

