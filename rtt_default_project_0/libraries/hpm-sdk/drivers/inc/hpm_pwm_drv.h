/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PWM_DRV_H
#define HPM_PWM_DRV_H

#include "hpm_common.h"
#include "hpm_pwm_regs.h"

#define PWM_UNLOCK_KEY (0xB0382607UL)

/* IRQ enable bit mask */
#define PWM_IRQ_FAULT PWM_IRQEN_FAULTIRQE_MASK
#define PWM_IRQ_EX_RELOAD PWM_IRQEN_XRLDIRQE_MASK
#define PWM_IRQ_HALF_RELOAD PWM_IRQEN_HALFRLDIRQE_MASK
#define PWM_IRQ_RELOAD PWM_IRQEN_RLDIRQE_MASK
#define PWM_IRQ_CMP(x) PWM_IRQEN_CMPIRQEX_SET((1 << x))

/* PWM force output mask */
#define PWM_FORCE_OUTPUT(pwm_index, force_output) \
    (force_output << (pwm_index << 1))

#define PWM_DUTY_CYCLE_FP_MAX ((1U << 24) - 1)

typedef enum pwm_counter_type {
    pwm_counter_type_capture_rising_edge,
    pwm_counter_type_capture_falling_edge,
} pwm_counter_type_t;

typedef enum pwm_cmp_mode {
    pwm_cmp_mode_output_compare = 0,
    pwm_cmp_mode_input_capture = 1,
} pwm_cmp_mode_t;

typedef enum pwm_register_update {
    pwm_shadow_register_update_on_shlk = 0,
    pwm_shadow_register_update_on_modify = 1,
    pwm_shadow_register_update_on_hw_event = 2,
    pwm_shadow_register_update_on_sh_synci = 3,
} pwm_shadow_register_update_trigger_t;

typedef enum pwm_fault_mode {
    pwm_fault_mode_force_output_0 = 0,
    pwm_fault_mode_force_output_1 = 1,
    pwm_fault_mode_force_output_highz = 2,
} pwm_fault_mode_t;

typedef enum pwm_fault_recovery_trigger {
    pwm_fault_recovery_immediately = 0,
    pwm_fault_recovery_on_reload = 1,
    pwm_fault_recovery_on_hw_event = 2,
    pwm_fault_recovery_on_fault_clear = 3,
} pwm_fault_recovery_trigger_t;

typedef enum pwm_force_source {
    pwm_force_source_force_input = 0,
    pwm_force_source_software = 1,
} pwm_force_source_t;

typedef enum pwm_force_cmd_timing {
    pwm_force_immediately = 0,
    pwm_force_at_reload = 1,
    pwm_force_at_synci = 2,
    pwm_force_none = 3,
} pwm_force_cmd_timing_t;

typedef enum pwm_fault_source {
    pwm_fault_source_internal_0 = PWM_GCR_FAULTI0EN_MASK,
    pwm_fault_source_internal_1 = PWM_GCR_FAULTI1EN_MASK,
    pwm_fault_source_internal_2 = PWM_GCR_FAULTI2EN_MASK,
    pwm_fault_source_internal_3 = PWM_GCR_FAULTI3EN_MASK,
    pwm_fault_source_external_0 = PWM_GCR_FAULTE0EN_MASK,
    pwm_fault_source_external_1 = PWM_GCR_FAULTE1EN_MASK,
} pwm_fault_source_t;

typedef enum pwm_output_type {
    pwm_output_0 = 0,
    pwm_output_1 = 1,
    pwm_output_high_z = 2,
    pwm_output_no_force = 3,
} pwm_output_type_t;

typedef struct pwm_cmp_config {
    uint32_t cmp;         /* compare value */
    bool enable_ex_cmp;   /* enable extended compare value */
    uint8_t mode;         /* compare work mode: pwm_cmp_mode_output_compare or pwm_cmp_mode_input_capture */
    uint8_t update_trigger;  /* compare configuration update trigger */
    uint8_t ex_cmp;       /* extended compare value */
    uint8_t half_clock_cmp; /* half clock compare value*/
    uint8_t jitter_cmp;     /* jitter compare value */
} pwm_cmp_config_t;

typedef struct pwm_output_channel {
    uint8_t cmp_start_index; /* output channel compare start index */
    uint8_t cmp_end_index;   /* output channel compare end index */
    bool invert_output;      /* invert output */
} pwm_output_channel_t;

typedef struct pwm_fault_source_config {
    uint32_t source_mask;               /* fault source mask*/
    bool fault_recover_at_rising_edge;  /* recover fault at rising edge */
    bool external_fault_active_low;
    uint8_t fault_output_recovery_trigger;
} pwm_fault_source_config_t;

typedef struct pwm_config {
    bool enable_output;                 /* enable pwm output */
    bool invert_output;                 /* invert pwm output level */
    uint8_t update_trigger;             /* pwm config update trigger */
    uint8_t fault_mode;                 /* fault mode */
    uint8_t fault_recovery_trigger;     /* fault recoverty trigger */
    uint8_t force_source;               /* fault source */
    uint32_t dead_zone_in_half_cycle;   /* dead zone in half cycle*/
} pwm_config_t;

typedef struct pwm_pair_config {
    pwm_config_t pwm[2];
} pwm_pair_config_t;

#ifdef __cplusplus
extern "C" {
#endif

static inline void pwm_issue_shadow_register_lock_event(PWM_Type *ptr)
{
    if (ptr->SHCR & PWM_SHCR_SHLKEN_MASK) {
        /* 
         * if lock shadow register has been enabled in SHCR, it has to set
         * the lock bit twice to issue shadow register lock event.
         */
        ptr->SHLK = PWM_SHLK_SHLK_MASK;
    }
    ptr->SHLK = PWM_SHLK_SHLK_MASK;
}

static inline void pwm_shadow_register_lock(PWM_Type *ptr)
{
    ptr->SHCR |= PWM_SHCR_SHLKEN_MASK;
    ptr->SHLK = PWM_SHLK_SHLK_MASK;
}
    
static inline void pwm_shadow_register_unlock(PWM_Type *ptr)
{
    ptr->UNLK = PWM_UNLOCK_KEY;
}

static inline void pwm_set_start_count(PWM_Type *ptr,
                                        uint8_t ex_start,
                                        uint32_t start)
{
    ptr->STA = PWM_STA_XSTA_SET(ex_start)
        | PWM_STA_STA_SET(start);
}

static inline void pwm_set_reload(PWM_Type *ptr,
                                   uint8_t ex_reload,
                                   uint32_t reload)
{
    pwm_shadow_register_unlock(ptr);
    ptr->RLD = PWM_RLD_XRLD_SET(ex_reload)
        | PWM_RLD_RLD_SET(reload);
}

static inline void pwm_clear_status(PWM_Type *ptr, uint32_t mask)
{
    ptr->SR |= mask;
}

static inline uint32_t pwm_get_status(PWM_Type *ptr)
{
    return ptr->SR;
}

static inline void pwm_disable_irq(PWM_Type *ptr, uint32_t mask)
{
    ptr->IRQEN &= ~mask;
}

static inline void pwm_enable_irq(PWM_Type *ptr, uint32_t mask)
{
    ptr->IRQEN |= mask;
}

static inline void pwm_disable_dma_request(PWM_Type *ptr, uint32_t mask)
{
    ptr->DMAEN &= ~mask;
}

static inline void pwm_enable_dma_request(PWM_Type *ptr, uint32_t mask)
{
    ptr->DMAEN |= mask;
}

/*
 * set target cmp as hardware event to trigger force cmd output
 */
static inline void pwm_set_force_cmd_shadow_register_hwevent(PWM_Type *ptr,
                                                    uint8_t target_cmp_index)
{
    ptr->SHCR = ((ptr->SHCR & ~(PWM_SHCR_FRCSHDWSEL_MASK))
                    | PWM_SHCR_FRCSHDWSEL_SET(target_cmp_index));
}

/*
 * Note: if trigger is not set to hardware event, target_cmp_index can be
 * passed with any value
 */
static inline void pwm_config_load_counter_shadow_register_trigger(PWM_Type *ptr,
                                pwm_shadow_register_update_trigger_t trigger,
                                uint8_t target_cmp_index)
{
    if (trigger == pwm_shadow_register_update_on_hw_event) {
        ptr->SHCR = ((ptr->SHCR & ~(PWM_SHCR_CNTSHDWSEL_MASK
                        | PWM_SHCR_CNTSHDWUPT_MASK))
                | PWM_SHCR_CNTSHDWSEL_SET(target_cmp_index)
                | PWM_SHCR_CNTSHDWUPT_SET(trigger));
    } else {
        ptr->SHCR = ((ptr->SHCR & ~(PWM_SHCR_CNTSHDWUPT_MASK))
                | PWM_SHCR_CNTSHDWUPT_SET(trigger));
    }
}

static inline void pwm_load_cmp_shadow_on_capture(PWM_Type *ptr,
                                                   uint8_t index,
                                                   bool active_falling_edge)
{
    ptr->CMPCFG[index] |= PWM_CMPCFG_CMPMODE_MASK;
    ptr->GCR = ((ptr->GCR & ~(PWM_GCR_CMPSHDWSEL_MASK | PWM_GCR_HWSHDWEDG_MASK))
            | PWM_GCR_CMPSHDWSEL_SET(index)
            | PWM_GCR_HWSHDWEDG_SET(active_falling_edge));
}

static inline void pwm_cmp_disable_half_clock(PWM_Type *ptr, uint8_t index)
{
    ptr->CMP[index] &= ~PWM_CMP_CMPHLF_MASK;
}

static inline void pwm_cmp_enable_half_clock(PWM_Type *ptr, uint8_t index)
{
    ptr->CMP[index] |= PWM_CMP_CMPHLF_MASK;
}

static inline void pwm_cmp_update_jitter_value(PWM_Type *ptr, uint8_t index, uint8_t jitter)
{
    ptr->CMP[index] = (ptr->CMP[index] & ~PWM_CMP_CMPJIT_MASK) | PWM_CMP_CMPJIT_SET(jitter);
}

static inline void pwm_cmp_update_cmp_value(PWM_Type *ptr, uint8_t index,
                                            uint32_t cmp, uint16_t ex_cmp)
{
    ptr->CMP[index] = (ptr->CMP[index] & ~(PWM_CMP_CMP_MASK | PWM_CMP_XCMP_MASK))
        | PWM_CMP_CMP_SET(cmp) | PWM_CMP_XCMP_SET(ex_cmp);
}

static inline void pwm_config_cmp(PWM_Type *ptr, uint8_t index, pwm_cmp_config_t *config)
{
    pwm_shadow_register_unlock(ptr);
    if (config->mode == pwm_cmp_mode_output_compare) {
        ptr->CMPCFG[index] = PWM_CMPCFG_XCNTCMPEN_SET(config->enable_ex_cmp)
                        | PWM_CMPCFG_CMPSHDWUPT_SET(config->update_trigger);
        ptr->CMP[index] = PWM_CMP_CMP_SET(config->cmp)
                        | PWM_CMP_XCMP_SET(config->ex_cmp)
                        | PWM_CMP_CMPHLF_SET(config->half_clock_cmp)
                        | PWM_CMP_CMPJIT_SET(config->jitter_cmp); 
    } else {
        ptr->CMPCFG[index] |= PWM_CMPCFG_CMPMODE_MASK;
    }
}

static inline void pwm_config_output_channel(PWM_Type *ptr, uint8_t index, pwm_output_channel_t *config)
{
    ptr->CHCFG[index] = PWM_CHCFG_CMPSELBEG_SET(config->cmp_start_index)
                            | PWM_CHCFG_CMPSELEND_SET(config->cmp_end_index)
                            | PWM_CHCFG_OUTPOL_SET(config->invert_output);
}

static inline void pwm_config_fault_source(PWM_Type *ptr, pwm_fault_source_config_t *config)
{
    ptr->GCR = (ptr->GCR & ~(PWM_GCR_FAULTI0EN_MASK | PWM_GCR_FAULTI1EN_MASK
                | PWM_GCR_FAULTI2EN_MASK | PWM_GCR_FAULTI3EN_MASK
                | PWM_GCR_FAULTE0EN_MASK | PWM_GCR_FAULTE1EN_MASK
                | PWM_GCR_FAULTRECEDG_MASK | PWM_GCR_FAULTEXPOL_MASK
                | PWM_GCR_FAULTRECHWSEL_MASK))
        | config->source_mask
        | PWM_GCR_FAULTEXPOL_SET(config->external_fault_active_low)
        | PWM_GCR_FAULTRECEDG_SET(config->fault_recover_at_rising_edge)
        | PWM_GCR_FAULTRECHWSEL_SET(config->fault_output_recovery_trigger);
}

static inline void pwm_clear_fault(PWM_Type *ptr)
{
    ptr->GCR |= PWM_GCR_FAULTCLR_MASK;
}

static inline void pwm_stop_counter(PWM_Type *ptr)
{
    ptr->GCR &= ~PWM_GCR_CEN_MASK;
}

static inline void pwm_start_counter(PWM_Type *ptr)
{
    ptr->GCR |= PWM_GCR_CEN_MASK;
}

static inline void pwm_enable_sw_force(PWM_Type *ptr)
{
    ptr->GCR |= PWM_GCR_SWFRC_MASK;
}

static inline void pwm_disable_sw_force(PWM_Type *ptr)
{
    ptr->GCR &= ~PWM_GCR_SWFRC_MASK;
}

static inline void pwm_enable_reload_at_synci(PWM_Type *ptr)
{
    ptr->GCR |= PWM_GCR_XRLDSYNCEN_MASK | PWM_GCR_RLDSYNCEN_MASK;
}

static inline void pwm_disable_output(PWM_Type *ptr, uint8_t index)
{
    ptr->PWMCFG[index] &= ~PWM_PWMCFG_OEN_MASK;
}

static inline void pwm_enable_output(PWM_Type *ptr, uint8_t index)
{
    ptr->PWMCFG[index] |= PWM_PWMCFG_OEN_MASK;
}

/*
 * @brief config pwm force output level per output channel
 * @param ptr PWM base address
 * @param output_mask PWM output channel force level, set it using the macro
 * PWM_FORCE_OUTPUT(pwm_index, force_output)
 */
static inline void pwm_set_force_output(PWM_Type *ptr, uint32_t output_mask)
{
    ptr->FRCMD = PWM_FRCMD_FRCMD_SET(output_mask);
}

static inline void pwm_config_force_polarity(PWM_Type *ptr, bool active_low)
{
    ptr->GCR = (ptr->GCR & ~(PWM_GCR_FRCPOL_MASK)) | PWM_GCR_FRCPOL_SET(active_low);
}

static inline void pwm_config_force_cmd_timing(PWM_Type *ptr, pwm_force_cmd_timing_t timing)
{
    ptr->GCR = (ptr->GCR & ~(PWM_GCR_FRCTIME_MASK)) | PWM_GCR_FRCTIME_SET(timing);
}

static inline void pwm_enable_pwm_sw_force_output(PWM_Type *ptr, uint8_t index)
{
    ptr->PWMCFG[index] |= PWM_PWMCFG_OEN_MASK | PWM_PWMCFG_FRCSRCSEL_MASK
        | PWM_PWMCFG_FRCSHDWUPT_SET(pwm_shadow_register_update_on_modify);
}

static inline void pwm_disable_pwm_sw_force_output(PWM_Type *ptr, uint8_t index)
{
    ptr->PWMCFG[index] &= ~PWM_PWMCFG_FRCSRCSEL_MASK;
}

static inline void pwm_config_pwm(PWM_Type *ptr, uint8_t index,
                                  pwm_config_t *config, bool enable_pair_mode)
{
    ptr->PWMCFG[index] = PWM_PWMCFG_OEN_SET(config->enable_output)
        | PWM_PWMCFG_FRCSHDWUPT_SET(config->update_trigger)
        | PWM_PWMCFG_FAULTMODE_SET(config->fault_mode)
        | PWM_PWMCFG_FAULTRECTIME_SET(config->fault_recovery_trigger)
        | PWM_PWMCFG_FRCSRCSEL_SET(config->force_source)
        | PWM_PWMCFG_PAIR_SET(enable_pair_mode)
        | PWM_PWMCFG_DEADAREA_SET(config->dead_zone_in_half_cycle);
}

hpm_stat_t pwm_load_cmp_shadow_on_match(PWM_Type *ptr,
                                         uint8_t index,
                                         pwm_cmp_config_t *config);

void pwm_get_captured_count(PWM_Type *ptr, uint32_t *buf, pwm_counter_type_t counter, uint8_t start_index, uint8_t num);

void pwm_get_default_cmp_config(PWM_Type *ptr, pwm_cmp_config_t *config);

void pwm_get_default_output_channel_config(PWM_Type *ptr, pwm_output_channel_t *config);

void pwm_get_default_pwm_config(PWM_Type *ptr, pwm_config_t *config);

void pwm_get_default_pwm_pair_config(PWM_Type *ptr, pwm_pair_config_t *config);

hpm_stat_t pwm_setup_waveform(PWM_Type *ptr,
                        uint8_t pwm_index, pwm_config_t *pwm_config,
                        uint8_t cmp_start_index, pwm_cmp_config_t *cmp, uint8_t cmp_num);
/*
 * setup pwm waveform in pair
 */
hpm_stat_t pwm_setup_waveform_in_pair(PWM_Type *ptr,
                        uint8_t pwm_index, pwm_pair_config_t *pwm_pair_config,
                        uint8_t cmp_start_index, pwm_cmp_config_t *cmp, uint8_t cmp_num);

/*
 * @brief update duty cycle for edge aligned waveform
 * @param ptr PWM base address
 * @param cmp_index index of cmp to be adjusted
 * @param duty value [0, PWM_DUTY_CYCLE_FP_MAX] represents [0, 100%]
 * @param update_trigger trigger to update pwm shadow registers
 */
hpm_stat_t pwm_update_duty_cycle_edge_aligned(PWM_Type *ptr, uint8_t cmp_index,
        uint32_t duty, pwm_shadow_register_update_trigger_t update_trigger);

/*
 * @brief update raw compare value for edge aligned waveform
 * @param ptr PWM base address
 * @param cmp_index index of cmp to be adjusted
 * @param target_cmp target compare value
 * @param update_trigger trigger to update pwm shadow registers
 */
hpm_stat_t pwm_update_raw_cmp_edge_aligned(PWM_Type *ptr, uint8_t cmp_index,
                                uint32_t target_cmp, pwm_shadow_register_update_trigger_t update_trigger);

/*
 * @brief update raw compare value for central aligned waveform
 * @param ptr PWM base address
 * @param cmp1_index index of cmp1 to be adjusted
 * @param cmp2_index index of cmp2 to be adjusted
 * @param target_cmp1 target compare value for cmp1
 * @param target_cmp2 target compare value for cmp2
 * @param update_trigger trigger to update pwm shadow registers
 */
hpm_stat_t pwm_update_raw_cmp_central_aligned(PWM_Type *ptr, uint8_t cmp1_index,
                                       uint8_t cmp2_index, uint32_t target_cmp1, uint32_t target_cmp2,
                                       pwm_shadow_register_update_trigger_t update_trigger);
#ifdef __cplusplus
}
#endif

#endif /* HPM_PWM_DRV_H */
