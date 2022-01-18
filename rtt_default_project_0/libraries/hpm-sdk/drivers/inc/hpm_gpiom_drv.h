/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_GPIOM_DRV_H
#define HPM_GPIOM_DRV_H

#include "hpm_gpiom_regs.h"

typedef enum gpiom_gpio {
    gpiom_soc_gpio0 = 0,
    gpiom_soc_gpio1 = 1,
    gpiom_core0_fast = 2,
    gpiom_core1_fast = 3,
} gpiom_gpio_t;

typedef enum gpiom_pin_visibility {
    gpiom_pin_visible = 0,
    gpiom_pin_invisible = 1,
} gpiom_pin_visibility_t;

#ifdef __cplusplus
extern "C" {
#endif

static inline gpiom_gpio_t gpiom_pin_get_selected_gpio(GPIOM_Type *ptr,
                                                      uint8_t gpio_index,
                                                      uint8_t pin_index)
{
    return (gpiom_gpio_t)((ptr->ASSIGN[gpio_index].PIN[pin_index]
            & (GPIOM_PIN_SELECT_MASK)) >> GPIOM_PIN_SELECT_SHIFT);
}

static inline void gpiom_pin_select_gpio(GPIOM_Type *ptr,
                              uint8_t gpio_index,
                              uint8_t pin_index,
                              gpiom_gpio_t gpio)
{
    ptr->ASSIGN[gpio_index].PIN[pin_index] = 
        (ptr->ASSIGN[gpio_index].PIN[pin_index] & ~(GPIOM_PIN_SELECT_MASK))
      | GPIOM_PIN_SELECT_SET(gpio);
}

static inline uint8_t gpiom_pin_get_visibility(GPIOM_Type *ptr,
                              uint8_t gpio_index,
                              uint8_t pin_index)
{
    return (ptr->ASSIGN[gpio_index].PIN[pin_index] & (GPIOM_PIN_HIDE_MASK))
        >> GPIOM_PIN_HIDE_SHIFT;
}


static inline void gpiom_pin_enable_visibility(GPIOM_Type *ptr,
                              uint8_t gpio_index,
                              uint8_t pin_index,
                              uint8_t visibility)
{
    ptr->ASSIGN[gpio_index].PIN[pin_index] = 
        (ptr->ASSIGN[gpio_index].PIN[pin_index] & ~(GPIOM_PIN_HIDE_MASK))
      | GPIOM_PIN_HIDE_SET(visibility);
}

static inline bool gpiom_pin_si_open_access(GPIOM_Type *ptr,
                              uint8_t gpio_index,
                              uint8_t pin_index)
{
    return (ptr->ASSIGN[gpio_index].PIN[pin_index] & GPIOM_PIN_NON_SEC_MASK)
        >> GPIOM_PIN_NON_SEC_SHIFT; 
}

static inline void gpiom_pin_enable_open_access(GPIOM_Type *ptr,
                              uint8_t gpio_index,
                              uint8_t pin_index,
                              bool open_access)
{
    ptr->ASSIGN[gpio_index].PIN[pin_index] = 
        (ptr->ASSIGN[gpio_index].PIN[pin_index] & ~(GPIOM_PIN_NON_SEC_MASK))
      | GPIOM_PIN_NON_SEC_SET(open_access);
}

static inline bool gpiom_pin_is_locked(GPIOM_Type *ptr,
                              uint8_t gpio_index,
                              uint8_t pin_index)
{
    return (ptr->ASSIGN[gpio_index].PIN[pin_index] & GPIOM_PIN_LOCK_MASK)
        == GPIOM_PIN_LOCK_MASK;
}

static inline void gpiom_pin_lock(GPIOM_Type *ptr,
                              uint8_t gpio_index,
                              uint8_t pin_index)
{
    ptr->ASSIGN[gpio_index].PIN[pin_index] |= GPIOM_PIN_LOCK_MASK;
}

#ifdef __cplusplus
}
#endif

#endif /* HPM_GPIOM_DRV_H */

