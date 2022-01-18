/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_BOARD_H
#define _HPM_BOARD_H
#include <stdio.h>
#include "hpm_common.h"
#include "hpm_soc.h"
#include "pinmux.h"

#define BOARD_NAME "hpm6750evkmini"

/* uart section */
#ifndef BOARD_RUNNING_CORE
#define BOARD_RUNNING_CORE HPM_CORE0
#endif
#ifndef BOARD_APP_UART_BASE
#define BOARD_APP_UART_BASE HPM_UART0
#define BOARD_APP_UART_IRQ  IRQn_UART0
#else
#ifndef BOARD_APP_UART_IRQ
#warning no IRQ specified for applicaiton uart
#endif
#endif

#define BOARD_APP_UART_SRC_FREQ (24000000UL)
#define BOARD_APP_UART_BAUDRATE (115200UL)

#define BOARD_APP_UART_CLK_NAME clock_uart0
#define BOARD_CONSOLE_TYPE console_type_uart
#ifndef BOARD_CONSOLE_BASE
#define BOARD_CONSOLE_BASE BOARD_APP_UART_BASE
#endif
#define BOARD_CONSOLE_SRC_FREQ BOARD_APP_UART_SRC_FREQ
#define BOARD_CONSOLE_BAUDRATE BOARD_APP_UART_BAUDRATE

/* sdram section */
#define BOARD_SDRAM_ADDRESS  (0x40000000UL)
#define BOARD_SDRAM_SIZE     (32*SIZE_1MB)
#define BOARD_SDRAM_CS       DRAM_SDRAM_CS0
#define BOARD_SDRAM_PORT_SIZE DRAM_SDRAM_PORT_SIZE_32_BITS
#define BOARD_SDRAM_REFRESH_COUNT (8192UL)
#define BOARD_SDRAM_REFRESH_IN_MS (64UL)
#define BOARD_SDRAM_DATA_WIDTH_IN_BYTE (4UL)

/* lcd section */
#define BOARD_LCD_BASE HPM_LCDC
#define BOARD_LCD_IRQ  IRQn_LCDC_D0

/* i2c section */
#define BOARD_APP_I2C_BASE HPM_I2C0
#define BOARD_APP_I2C_CLK_NAME clock_i2c0
#define BOARD_APP_I2C_FREQ (24000000UL)

#define BOARD_CAP_I2C_BASE (HPM_I2C3)
#define BOARD_CAP_I2C_CLK_NAME clock_i2c0
#define BOARD_CAP_I2C_FREQ (24000000UL)
#define BOARD_CAP_INTR_GPIO (HPM_GPIO0)
#define BOARD_CAP_INTR_GPIO_INDEX (GPIO_DI_GPIOY)
#define BOARD_CAP_INTR_GPIO_PIN (9)
#define BOARD_CAP_INTR_GPIO_IRQ (IRQn_GPIO0_Y)

/* dma section */
#define BOARD_APP_XDMA_IRQ IRQn_XDMA
#define BOARD_APP_HDMA_IRQ IRQn_HDMA

/* gpio section */

#define BOARD_LED_GPIO_CTRL HPM_GPIO0

#define BOARD_LED0_GPIO_CTRL HPM_GPIO0
#define BOARD_LED0_GPIO_INDEX GPIO_DI_GPIOB
#define BOARD_LED0_GPIO_PIN 19
#define BOARD_LED1_GPIO_CTRL HPM_GPIO0
#define BOARD_LED1_GPIO_INDEX GPIO_DI_GPIOB
#define BOARD_LED1_GPIO_PIN 18
#define BOARD_LED2_GPIO_CTRL HPM_GPIO0
#define BOARD_LED2_GPIO_INDEX GPIO_DI_GPIOB
#define BOARD_LED2_GPIO_PIN 20
#define BOARD_LED_ON (0)
#define BOARD_LED_OFF (1)


#define BOARD_APP_GPIO_INDEX GPIO_DI_GPIOZ
#define BOARD_APP_GPIO_PIN 7

/* pinmux section */
#define USING_GPIO0_FOR_GPIOZ
#ifndef USING_GPIO0_FOR_GPIOZ
#define BOARD_APP_GPIO_CTRL HPM_BATT_GPIO
#define BOARD_APP_GPIO_IRQ IRQn_BATT_GPIO
#else
#define BOARD_APP_GPIO_CTRL HPM_GPIO0
#define BOARD_APP_GPIO_IRQ IRQn_GPIO0_Z
#endif

/* spi section */
#define BOARD_APP_SPI_BASE HPM_SPI0
#define BOARD_APP_SPI_CLK_SRC_FREQ      (25000000UL)
#define BOARD_APP_SPI_SCLK_FREQ         (1562500UL)
#define BOARD_APP_SPI_ADDR_LEN_IN_BYTES (1U)
#define BOARD_APP_SPI_DATA_LEN_IN_BITS  (8U)

/* mchtimer section */
#define BOARD_MCHTMR_FREQ_IN_HZ (24000000UL)

/* lcd section */
#ifndef BOARD_LCD_WIDTH
#define BOARD_LCD_WIDTH (800)
#endif 
#ifndef BOARD_LCD_HEIGHT
#define BOARD_LCD_HEIGHT (480)
#endif 

/* pdma section */
#define BOARD_PDMA_BASE HPM_PDMA

/* i2s section */
#define BOARD_AUDIO_CLOCK_FREQ_IN_HZ (24000000UL)

/* enet section */
#define BOARD_APP_ENET_BASE HPM_ENET0

/* adc section */
#define BOARD_APP_ADC12_BASE HPM_ADC0
#define BOARD_APP_ADC16_BASE HPM_ADC3
#define BOARD_APP_ADC12_IRQn IRQn_ADC0
#define BOARD_APP_ADC16_IRQn IRQn_ADC3
#define BOARD_APP_ADC_CH                         (0U)
#define BOARD_APP_ADC_SEQ_DMA_SIZE_IN_4BYTES     (1024U)
#define BOARD_APP_ADC_PREEMPT_DMA_SIZE_IN_4BYTES (192U)
#define BOARD_APP_ADC_PREEMPT_TRIG_LEN           (1U)
#define BOARD_APP_ADC_SINGLE_CONV_CNT            (6)
#define BOARD_APP_ADC_TRIG_PWMT0                 HPM_PWM0
#define BOARD_APP_ADC_TRIG_PWMT1                 HPM_PWM1
#define BOARD_APP_ADC_TRIG_TRGM0                 HPM_TRGM0
#define BOARD_APP_ADC_TRIG_TRGM1                 HPM_TRGM1
#define BOARD_APP_ADC_TRIG_PWM_SYNC              HPM_SYNT

/* Flash section */
#define BOARD_APP_XPI_NOR_XPI_BASE            (HPM_XPI0)
#define BOARD_APP_XPI_NOR_CFG_OPT_HDR         (0xfcf90001U)
#define BOARD_APP_XPI_NOR_CFG_OPT_OPT0        (0x00000007U)
#define BOARD_APP_XPI_NOR_CFG_OPT_OPT1        (0x00000000U)

/* SPI WIFI section */
#define RW007_RST_PIN                         (IOC_PAD_PE02)
#define RW007_INT_BUSY_PIN                    (IOC_PAD_PE01)
#define RW007_CS_PIN                          (IOC_PAD_PE03)
#define RW007_CS_GPIO                         (HPM_GPIO0)
#define RW007_SPI_BUS_NAME                    "spi1"

/***************************************************************
 *
 * RT-Thread related definitions
 *
 **************************************************************/
extern unsigned int __heap_start__;
extern unsigned int __heap_end__;

#define RT_HW_HEAP_BEGIN ((void*)&__heap_start__)
#define RT_HW_HEAP_END ((void*)&__heap_end__)


typedef struct {
    uint16_t vdd;
    uint8_t bus_width;
    uint8_t drive_strength;
}sdxc_io_cfg_t;


#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

void board_init(void);
void board_init_console(void);

void board_init_uart(UART_Type *ptr);

void board_init_can(CAN_Type *ptr);

void board_init_sdram_pins(void);
void board_init_gpio_pins(void);
void board_init_spi_pins(void);
void board_init_led_pins(void);

void board_led_write(uint32_t index, bool state);


/* Initialize SoC overall clocks */
void board_init_clock(void);

uint32_t board_init_uart_clock(UART_Type *ptr);
uint32_t board_init_spi_clock(SPI_Type *ptr);
uint32_t board_init_dram_clock(void);

/*
 * @brief Initialize PMP and PMA for but not limited to the following purposes:
 *      -- non-cacheable memory initialization
 */
void board_init_pmp(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* _HPM_BOARD_H */
