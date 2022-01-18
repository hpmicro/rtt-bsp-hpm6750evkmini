/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_GPIO_DRV_H
#define HPM_GPIO_DRV_H

#include "hpm_gpio_regs.h"

typedef enum gpio_pin_level {
    gpio_pin_level_low = 0,
    gpio_pin_level_high,
} gpio_pin_level_t;

typedef enum gpio_interrupt_trigger {
    gpio_interrupt_trigger_level_high = 0,
    gpio_interrupt_trigger_level_low,
    gpio_interrupt_trigger_edge_rising,
    gpio_interrupt_trigger_edge_falling,
} gpio_interrupt_trigger_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * get gpio pin level
 */
static inline gpio_pin_level_t gpio_read_pin(GPIO_Type *ptr,
                                             uint32_t gpio_index,
                                             uint8_t pin_index)
{
    return ptr->DI[gpio_index].VALUE & (1 << pin_index)
            ? gpio_pin_level_high : gpio_pin_level_low;
}

static inline void gpio_toggle_pin(GPIO_Type *ptr,
                                         uint32_t gpio_index,
                                         uint8_t pin_index)
{
    ptr->DO[gpio_index].TOGGLE = 1 << pin_index;
}

static inline void gpio_write_pin(GPIO_Type *ptr,
                                  uint32_t gpio_index,
                                  uint8_t pin_index,
                                  gpio_pin_level_t level)
{
    if (level == gpio_pin_level_high) {
        ptr->DO[gpio_index].SET = 1 << pin_index;
    } else {
        ptr->DO[gpio_index].CLEAR = 1 << pin_index;
    }
}

static inline void gpio_disable_pin_output(GPIO_Type *ptr,
                                      uint32_t gpio_index,
                                      uint8_t pin_index)
{
    ptr->OE[gpio_index].CLEAR = 1 << pin_index;
}

static inline void gpio_enable_pin_output(GPIO_Type *ptr,
                                      uint32_t gpio_index,
                                      uint8_t pin_index)
{
    ptr->OE[gpio_index].SET = 1 << pin_index;
}

static inline bool gpio_check_interrupt_flag(GPIO_Type *ptr,
                                       uint32_t gpio_index,
                                       uint8_t pin_index)
{
    return ptr->IF[gpio_index].VALUE & (1 << pin_index);
}

static inline void gpio_clear_interrupt_flag(GPIO_Type *ptr,
                                       uint32_t gpio_index,
                                       uint8_t pin_index)
{
    ptr->IF[gpio_index].VALUE |= 1 << pin_index;
}

static inline uint32_t gpio_read_pins_with_mask(GPIO_Type *ptr,
                                               uint32_t gpio_index,
                                               uint32_t pin_mask)
{
    return ptr->DI[gpio_index].VALUE & pin_mask;
}

static inline void gpio_toggle_pins_with_mask(GPIO_Type *ptr,
                                         uint32_t gpio_index,
                                         uint32_t pin_mask)
{
    ptr->DO[gpio_index].TOGGLE = pin_mask;
}

static inline void gpio_write_pins_with_mask(GPIO_Type *ptr,
                                      uint32_t gpio_index,
                                      uint32_t pin_mask,
                                      gpio_pin_level_t level)
{
    if (level == gpio_pin_level_high) {
        ptr->DO[gpio_index].SET = pin_mask;
    } else {
        ptr->DO[gpio_index].CLEAR = pin_mask;
    }
}

static inline void gpio_enable_pins_output_with_mask(GPIO_Type *ptr,
                                      uint32_t gpio_index,
                                      uint32_t pin_mask)
{
    ptr->OE[gpio_index].SET = pin_mask;
}

static inline void gpio_disable_pins_output_with_mask(GPIO_Type *ptr,
                                      uint32_t gpio_index,
                                      uint32_t pin_mask)
{
    ptr->OE[gpio_index].CLEAR = pin_mask;
}

static inline bool gpio_check_pin_interrupt_flag_with_mask(GPIO_Type *ptr,
                                       uint32_t gpio_index,
                                       uint32_t pin_mask)
{
    return ptr->IF[gpio_index].VALUE & pin_mask;
}

static inline void gpio_clear_pin_interrupt_flag_with_mask(GPIO_Type *ptr,
                                       uint32_t gpio_index,
                                       uint32_t pin_mask)
{
    ptr->IF[gpio_index].SET = pin_mask;
}

static inline void gpio_enable_pins_interrupt_with_mask(GPIO_Type *ptr,
                                          uint32_t gpio_index,
                                          uint8_t pin_mask)
{
    ptr->IE[gpio_index].SET = pin_mask;
}

static inline void gpio_disable_pins_interrupt_with_mask(GPIO_Type *ptr,
                                          uint32_t gpio_index,
                                          uint8_t pin_mask)
{
    ptr->IE[gpio_index].CLEAR = pin_mask;
}

static inline uint32_t gpio_get_interrupt_flag(GPIO_Type *ptr,
                                          uint32_t gpio_index)
{
    return ptr->IF[gpio_index].VALUE;
}

static inline bool gpio_is_pin_interrupt_enabled(GPIO_Type *ptr,
                                          uint32_t gpio_index,
                                          uint8_t pin_index)
{
    return (ptr->IE[gpio_index].VALUE & (1 << pin_index)) == (1 << pin_index);
}

static inline void gpio_enable_pin_interrupt(GPIO_Type *ptr,
                                          uint32_t gpio_index,
                                          uint8_t pin_index)
{
    ptr->IE[gpio_index].SET = 1 << pin_index;
}

static inline void gpio_disable_pin_interrupt(GPIO_Type *ptr,
                                          uint32_t gpio_index,
                                          uint8_t pin_index)
{
    ptr->IE[gpio_index].CLEAR = 1 << pin_index;
}


/*
 * check if interrupt flag is set for specific pin, if so, clear it and return true,
 * otherwise, return false
 */
static inline bool gpio_check_clear_interrupt_flag(GPIO_Type *ptr,
                                             uint32_t gpio_index,
                                             uint8_t pin_index)
{
    if (!gpio_check_interrupt_flag(ptr, gpio_index, pin_index)) {
        return false;
    }
    gpio_clear_interrupt_flag(ptr, gpio_index, pin_index);
    return true;
}

void gpio_config_pin_interrupt(GPIO_Type *ptr, uint32_t gpio_index,
                         uint8_t pin_index, gpio_interrupt_trigger_t trigger);


void gpio_toggle_pin_interrupt_trigger_polarity(GPIO_Type *ptr,
                                                 uint32_t gpio_index,
                                                 uint8_t pin_index);

void gpio_toggle_pin_interrupt_trigger_type(GPIO_Type *ptr,
                                                 uint32_t gpio_index,
                                                 uint8_t pin_index);
#ifdef __cplusplus
}
#endif
#endif /* HPM_GPIO_DRV_H */
