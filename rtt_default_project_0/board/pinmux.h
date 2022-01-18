/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PINMUX_H
#define HPM_PINMUX_H

#ifdef __cplusplus
extern "C" {
#endif
void init_uart_pins(UART_Type *ptr);
void init_i2c_pins(I2C_Type *ptr);
void init_sdram_pins(void);
void init_gpio_pins(void);
void init_spi_pins(SPI_Type *ptr);
void init_wifi_pins(void);


#ifdef __cplusplus
}
#endif
#endif /* HPM_PINMUX_H */

