/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_RTC_DRV_H
#define HPM_RTC_DRV_H

#include "hpm_common.h"
#include "hpm_rtc_regs.h"
#include <time.h>

typedef struct {
    uint16_t index;
    uint16_t type;
    time_t period;
} rtc_alarm_config_t;

/**
 * @brief RTC Alarm type
 */
#define RTC_ALARM_TYPE_ONE_SHOT (0U) //!< The RTC alarm will be triggered only once
#define RTC_ALARM_TYPE_PERIODIC (1U) //!< The RTC alarm will be triggered periodically

/**
 * @brief Typical RTC alarm period definitions
 */
#define ALARM_PERIOD_ONE_SEC  (1UL)
#define ALARM_PERIOD_ONE_MIN  (60UL)
#define ALARM_PERIOD_ONE_HOUR (3600U)
#define ALARM_PERIOD_ONE_DAY  (ALARM_PERIOD_ONE_HOUR * 24UL)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Configure the RTC time
 * @param base Base address of RTC module
 * @param time seconds since 1970.1.1, 0:0:0
 * @return #status_success
 *         #status_invalid_argument
 */
hpm_stat_t rtc_config_time(RTC_Type *base, time_t time);

/**
 * @brief Configure RTC Alarm
 * @param base Base address of RTC module
 * @param config RTC alarm configuration pointer
 * @return #status_success
 *         #status_invalid_arugment;
 */
hpm_stat_t rtc_config_alarm(RTC_Type *base, rtc_alarm_config_t *config);

/**
 * @brief Get the time returned by RTC module
 * @param base Base address of RTC module
 * @return RTC time
 */
time_t rtc_get_time(RTC_Type *base);

/**
 * @brief Enable RTC alarm interrupt
 * @param base Base address of RTC module
 * @param index RTC alarm index, valid value is 0 or 1
 * @param enable #true - Enable specified RTC alarm
 *               #false - Disable specified RTC alarm
 */
static inline void rtc_enable_alarm_interrupt(RTC_Type *base, uint32_t index, bool enable)
{
    if (index > 1) {
        return;
    }

    uint32_t mask = (index == 0U) ? RTC_ALARM_EN_ENABLE0_MASK : RTC_ALARM_EN_ENABLE0_MASK;

    if (enable) {
        base->ALARM_EN |= mask;
    }
    else {
        base->ALARM_EN &= ~mask;
    }
}

static inline void rtc_clear_alarm_flag(RTC_Type *base, uint32_t index)
{
    if (index > 1) {
        return;
    }
    uint32_t mask = (index == 0U) ? RTC_ALARM_FLAG_ALARM0_MASK : RTC_ALARM_FLAG_ALARM1_MASK;

    base->ALARM_FLAG = mask;
}

static inline bool rtc_is_alarm_flag_asserted(RTC_Type *base, uint32_t index)
{
    if (index > 1) {
        return false;
    }
    uint32_t mask = (index == 0U) ? RTC_ALARM_FLAG_ALARM0_MASK : RTC_ALARM_FLAG_ALARM1_MASK;

    return IS_HPM_BITMASK_SET(base->ALARM_FLAG, mask);
}


#ifdef __cplusplus
}
#endif

#endif // HPM_RTC_DRV_H
