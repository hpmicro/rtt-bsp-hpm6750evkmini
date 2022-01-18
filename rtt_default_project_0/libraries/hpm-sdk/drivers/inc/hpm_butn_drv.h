/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_BUTN_DRV_H
#define HPM_BUTN_DRV_H

#include "hpm_common.h"
#include "hpm_butn_regs.h"

#define BUTN_EVENT_POWER_PRESS (BUTN_BTN_STATUS_PBTN_MASK)
#define BUTN_EVENT_WAKE_PRESS (BUTN_BTN_STATUS_WBTN_MASK)
#define BUTN_EVENT_DUAL_PRESS (BUTN_BTN_STATUS_DBTN_MASK)
#define BUTN_EVENT_POWER_CLICK (BUTN_BTN_STATUS_PCLICK_MASK)
#define BUTN_EVENT_POWER_CLICK_WHEN_WAKE_HELD (BUTN_BTN_STATUS_XPCLICK_MASK)
#define BUTN_EVENT_WAKE_CLICK (BUTN_BTN_STATUS_WCLICK_MASK)
#define BUTN_EVENT_WAKE_CLICK_WHEN_POWER_HELD (BUTN_BTN_STATUS_XWCLICK_MASK)

#ifdef __cplusplus
extern "C" {
#endif

static inline uint32_t batt_btn_get_status(BUTN_Type *ptr)
{
    return ptr->BTN_STATUS;
}

static inline void batt_btn_enable_irq(BUTN_Type *ptr, uint32_t mask)
{
    ptr->BTN_IRQ_MASK |= mask;
}

static inline void batt_btn_disable_irq(BUTN_Type *ptr, uint32_t mask)
{
    ptr->BTN_IRQ_MASK &= ~mask;
}

static inline void batt_btn_set_debounce(BUTN_Type *ptr, uint8_t debounce)
{
    ptr->LED_INTENSE = BUTN_LED_INTENSE_PLED_SET(debounce)
        | BUTN_LED_INTENSE_RLED_SET(debounce);
}

#ifdef __cplusplus
}
#endif
#endif /* HPM_BUTN_DRV_H */
