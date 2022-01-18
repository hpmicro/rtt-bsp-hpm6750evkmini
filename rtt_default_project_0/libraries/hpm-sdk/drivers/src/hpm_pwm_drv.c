/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_soc_feature.h"
#include "hpm_pwm_drv.h"

hpm_stat_t pwm_load_cmp_shadow_on_match(PWM_Type *ptr,
                                         uint8_t index,
                                         pwm_cmp_config_t *config)
{
    if (config->mode != pwm_cmp_mode_output_compare) {
        return status_invalid_argument;
    }
    pwm_config_cmp(ptr, index, config);
    pwm_issue_shadow_register_lock_event(ptr);
    ptr->GCR = ((ptr->GCR & ~(PWM_GCR_CMPSHDWSEL_MASK)) | PWM_GCR_CMPSHDWSEL_SET(index));
    return status_success;
}

void pwm_get_count(PWM_Type *ptr, uint32_t *buf, pwm_counter_type_t counter, uint8_t start_index, uint8_t num)
{
    uint32_t i;
    if (counter == pwm_counter_type_capture_falling_edge) {
        for (i = start_index; i < num; i++) {
            *buf = ptr->CAPNEG[i];
        }
    } else {
        for (i = start_index; i < num; i++) {
            *buf = ptr->CAPPOS[i];
        }
    }
}

void pwm_get_default_cmp_config(PWM_Type *ptr, pwm_cmp_config_t *config)
{
    config->mode = pwm_cmp_mode_output_compare;
    config->update_trigger = pwm_shadow_register_update_on_modify;
    config->enable_ex_cmp = false;
    config->cmp = 0;
    config->ex_cmp = 0;
    config->half_clock_cmp = 0;
    config->jitter_cmp = 0;
}

void pwm_get_default_output_channel_config(PWM_Type *ptr, pwm_output_channel_t *config)
{
    config->cmp_start_index = 0;
    config->cmp_end_index = 0;
    config->invert_output = false;
}

void pwm_get_default_pwm_config(PWM_Type *ptr, pwm_config_t *config)
{
    config->enable_output = false;
    config->update_trigger = pwm_shadow_register_update_on_modify;
    config->fault_mode = pwm_fault_mode_force_output_highz;
    config->fault_recovery_trigger = pwm_fault_recovery_on_fault_clear;
    config->force_source = pwm_force_source_software;
    config->dead_zone_in_half_cycle = 0;
}

void pwm_get_default_pwm_pair_config(PWM_Type *ptr, pwm_pair_config_t *config)
{
    pwm_get_default_pwm_config(ptr, &config->pwm[0]);
    pwm_get_default_pwm_config(ptr, &config->pwm[1]);
}

hpm_stat_t pwm_setup_waveform_in_pair(PWM_Type *ptr, uint8_t pwm_index,
                        pwm_pair_config_t *pwm_pair_config, uint8_t cmp_start_index,
                        pwm_cmp_config_t *cmp, uint8_t cmp_num)
{
    uint8_t i;
    pwm_output_channel_t ch_config;

    if ((pwm_index > PWM_SOC_PWM_MAX_COUNT)
        || !cmp_num
        || (cmp_start_index > PWM_SOC_CMP_MAX_COUNT)
        || (cmp_start_index + cmp_num > PWM_SOC_CMP_MAX_COUNT)
        || ((pwm_index > (PWM_SOC_PWM_MAX_COUNT - 1))
                    || (pwm_index & 0x1))) {
        return status_invalid_argument;
    }

    ptr->PWMCFG[pwm_index] &= ~PWM_PWMCFG_OEN_MASK;
    ptr->PWMCFG[pwm_index + 1] &= ~PWM_PWMCFG_OEN_MASK;

    for (i =  0; i < cmp_num; i++) {
        pwm_config_cmp(ptr, cmp_start_index + i, &cmp[i]);
    }
    ch_config.cmp_start_index = cmp_start_index;
    ch_config.cmp_end_index = cmp_start_index + cmp_num - 1;
    ch_config.invert_output = pwm_pair_config->pwm[0].invert_output;
    pwm_config_output_channel(ptr, pwm_index, &ch_config);

    ch_config.invert_output = pwm_pair_config->pwm[1].invert_output;
    pwm_config_output_channel(ptr, pwm_index + 1, &ch_config);

    pwm_config_pwm(ptr, pwm_index, &pwm_pair_config->pwm[0], true);
    pwm_config_pwm(ptr, pwm_index + 1, &pwm_pair_config->pwm[1], true);

    return status_success;
}

hpm_stat_t pwm_setup_waveform(PWM_Type *ptr,
                        uint8_t pwm_index, pwm_config_t *pwm_config,
                        uint8_t cmp_start_index, pwm_cmp_config_t *cmp, uint8_t cmp_num)
{
    uint8_t i;
    pwm_output_channel_t ch_config;
    if (!cmp_num
        || (cmp_start_index > PWM_SOC_CMP_MAX_COUNT)
        || (cmp_start_index + cmp_num > PWM_SOC_CMP_MAX_COUNT)) {
        return status_invalid_argument;
    }

    for (i =  0; i < cmp_num; i++) {
        pwm_config_cmp(ptr, cmp_start_index + i, &cmp[i]);
    }
    ch_config.cmp_start_index = cmp_start_index;
    ch_config.cmp_end_index = cmp_start_index + cmp_num - 1;
    ch_config.invert_output = pwm_config->invert_output;
    pwm_config_output_channel(ptr, pwm_index, &ch_config);
    if (pwm_index < PWM_SOC_PWM_MAX_COUNT) {
        pwm_config_pwm(ptr, pwm_index, pwm_config, false);
    }
    return status_success;
}

hpm_stat_t pwm_update_raw_cmp_edge_aligned(PWM_Type *ptr, uint8_t cmp_index, uint32_t target_cmp, pwm_shadow_register_update_trigger_t update_trigger)
{
    pwm_cmp_config_t cmp = {0};
    cmp.mode = pwm_cmp_mode_output_compare;
    cmp.cmp = target_cmp;
    cmp.update_trigger = update_trigger;
    pwm_config_cmp(ptr, cmp_index, &cmp);
    return status_success;
}

hpm_stat_t pwm_update_raw_cmp_central_aligned(PWM_Type *ptr, uint8_t cmp1_index,
                                       uint8_t cmp2_index, uint32_t target_cmp1, uint32_t target_cmp2,
                                       pwm_shadow_register_update_trigger_t update_trigger)
{
    pwm_cmp_config_t cmp1 = {0}, cmp2 = {0};
    uint32_t reload = PWM_RLD_RLD_GET(ptr->RLD);

    cmp1.mode = pwm_cmp_mode_output_compare;
    cmp2.mode = pwm_cmp_mode_output_compare;
    if (!target_cmp1) {
        cmp1.cmp = reload + 1;
    } else {
        cmp1.cmp = target_cmp1;
    }
    if (!target_cmp2) {
        cmp2.cmp = reload + 1;
    } else {
        cmp2.cmp = target_cmp2;
    }

    cmp1.update_trigger = update_trigger;
    cmp2.update_trigger = update_trigger;
    pwm_config_cmp(ptr, cmp1_index, &cmp1);
    pwm_config_cmp(ptr, cmp2_index, &cmp2);
    return status_success;
}