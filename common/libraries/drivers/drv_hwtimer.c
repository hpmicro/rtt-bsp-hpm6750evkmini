/*
 * Copyright (c) 2022-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * @file drv_hwtimer.c
 * @brief Hardware Timer driver implementation for RT-Thread
 *
 * This file implements the hardware timer driver for HPMicro microcontrollers,
 * providing a complete interface between RT-Thread's hardware timer framework
 * and the HPM GPTMR (General Purpose Timer) hardware.
 *
 * Features:
 * - Support for up to 8 GPTMR controllers (GPTMR0-GPTMR7)
 * - High-precision timer operations with configurable frequency
 * - Interrupt-driven timer events
 * - Multiple timer modes (one-shot, periodic)
 * - Configurable interrupt priorities
 * - Real-time counter operations
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-16     HPMicro      the first version
 * 2025-09-01     HPMicro      Revised the code, reduced repetitive codes, added comments
 */

#include "rtconfig.h"

#ifdef RT_USING_HWTIMER

/* RT-Thread includes */
#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>

/* HPM SDK includes */
#include "drv_hwtimer.h"
#include "board.h"
#include "hpm_gptmr_drv.h"
#include "hpm_rtt_interrupt_util.h"
#include "hpm_clock_drv.h"

/* ============================================================================
 * Configuration Macros
 * ============================================================================ */

/*
 * Interrupt Priority Configuration Macros
 * These macros handle the configuration of interrupt priorities for each GPTMR controller.
 * If a specific priority is defined in the board configuration, it will be used;
 * otherwise, a default priority of 1 is applied.
 */
#ifdef BSP_GPTMR0_IRQ_PRIORITY
#define GPTMR_IRQ_PRI_VAL_0 BSP_GPTMR0_IRQ_PRIORITY
#else
#define GPTMR_IRQ_PRI_VAL_0 1
#endif

#ifdef BSP_GPTMR1_IRQ_PRIORITY
#define GPTMR_IRQ_PRI_VAL_1 BSP_GPTMR1_IRQ_PRIORITY
#else
#define GPTMR_IRQ_PRI_VAL_1 1
#endif

#ifdef BSP_GPTMR2_IRQ_PRIORITY
#define GPTMR_IRQ_PRI_VAL_2 BSP_GPTMR2_IRQ_PRIORITY
#else
#define GPTMR_IRQ_PRI_VAL_2 1
#endif

#ifdef BSP_GPTMR3_IRQ_PRIORITY
#define GPTMR_IRQ_PRI_VAL_3 BSP_GPTMR3_IRQ_PRIORITY
#else
#define GPTMR_IRQ_PRI_VAL_3 1
#endif

#ifdef BSP_GPTMR4_IRQ_PRIORITY
#define GPTMR_IRQ_PRI_VAL_4 BSP_GPTMR4_IRQ_PRIORITY
#else
#define GPTMR_IRQ_PRI_VAL_4 1
#endif

#ifdef BSP_GPTMR5_IRQ_PRIORITY
#define GPTMR_IRQ_PRI_VAL_5 BSP_GPTMR5_IRQ_PRIORITY
#else
#define GPTMR_IRQ_PRI_VAL_5 1
#endif

#ifdef BSP_GPTMR6_IRQ_PRIORITY
#define GPTMR_IRQ_PRI_VAL_6 BSP_GPTMR6_IRQ_PRIORITY
#else
#define GPTMR_IRQ_PRI_VAL_6 1
#endif

#ifdef BSP_GPTMR7_IRQ_PRIORITY
#define GPTMR_IRQ_PRI_VAL_7 BSP_GPTMR7_IRQ_PRIORITY
#else
#define GPTMR_IRQ_PRI_VAL_7 1
#endif

/* Macro to select the appropriate priority value based on GPTMR controller number */
#define GPTMR_IRQ_PRI_VAL(n) GPTMR_IRQ_PRI_VAL_##n

/*
 * GPTMR Device Definition Macro
 * This macro creates a complete GPTMR device structure with all necessary
 * configuration including base address, clock source, and interrupt settings.
 *
 * @param n GPTMR controller number (0-7)
 */
#define GPTMR_DEVICE_DEFINE(n)                               \
    static hpm_gptimer_t timer##n =                          \
    {                                                         \
        .name = "GPT" #n,                                    \
        .base = HPM_GPTMR##n,                                \
        .clock_name = clock_gptmr##n,                        \
        .irq_num = IRQn_GPTMR##n,                            \
        .irq_priority = GPTMR_IRQ_PRI_VAL(n),                \
    }

#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
/*
 * GPTMR ISR Definition Macro
 * This macro creates the interrupt service routine function and its declaration
 * for a specific GPTMR controller.
 *
 * @param n GPTMR controller number (0-7)
 */
#define GPTMR_ISR_DEFINE(n)                                  \
    RTT_DECLARE_EXT_ISR_M(IRQn_GPTMR##n, gptmr##n##_isr)     \
    void gptmr##n##_isr(void)                                \
    {                                                        \
        hpm_hwtmr_isr(&timer##n);                            \
    }
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */

/*
 * GPTMR Context Extraction Macro
 * This macro extracts the GPTMR driver context and base address from the
 * RT-Thread timer device structure.
 *
 * @param timer Pointer to RT-Thread timer device structure
 */
#define GPTMR_GET_CTX(timer)                                 \
    hpm_gptimer_t *hpm_gptmr = (hpm_gptimer_t*)timer->parent.user_data; \
    GPTMR_Type *base = hpm_gptmr->base

/* ============================================================================
 * Data Structures
 * ============================================================================ */

/**
 * @brief HPM GPTMR driver context structure
 *
 * This structure contains all the necessary information to manage a GPTMR controller,
 * including hardware registers, configuration, and RT-Thread timer interface.
 */
typedef struct _hpm_gptimer
{
    GPTMR_Type *base;                    /**< GPTMR hardware base address */
    const char *name;                    /**< Timer device name (e.g., "GPT0", "GPT1") */
    rt_hwtimer_t timer;                  /**< RT-Thread hardware timer structure */
    uint32_t channel;                    /**< GPTMR channel number (typically 0) */
    clock_name_t clock_name;             /**< GPTMR clock source name */
    int32_t irq_num;                     /**< GPTMR interrupt number */
    uint8_t irq_priority;                /**< GPTMR interrupt priority */
} hpm_gptimer_t;

/* ============================================================================
 * Function Declarations
 * ============================================================================ */

/**
 * @brief Initialize hardware timer
 * @param [in/out] timer Pointer to RT-Thread hardware timer structure
 * @param [in] state Initialization state (1 = enable, 0 = disable)
 */
static void hpm_hwtimer_init(rt_hwtimer_t *timer, rt_uint32_t state);

/**
 * @brief Start hardware timer with specified count and mode
 * @param [in/out] timer Pointer to RT-Thread hardware timer structure
 * @param [in] cnt Timer count value
 * @param [in] mode Timer mode (one-shot or periodic)
 * @retval RT_EOK Timer started successfully
 * @retval -RT_ERROR Timer start failed
 */
static rt_err_t hpm_hwtimer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode);

/**
 * @brief Stop hardware timer
 * @param [in/out] timer Pointer to RT-Thread hardware timer structure
 */
static void hpm_hwtimer_stop(rt_hwtimer_t *timer);

/**
 * @brief Get current timer count value
 * @param [in] timer Pointer to RT-Thread hardware timer structure
 * @return Current timer count value
 */
static rt_uint32_t hpm_hwtimer_count_get(rt_hwtimer_t *timer);

/**
 * @brief Control hardware timer operations
 * @param [in/out] timer Pointer to RT-Thread hardware timer structure
 * @param [in] cmd Control command
 * @param [in/out] args Command arguments
 * @retval RT_EOK Command executed successfully
 * @retval -RT_ERROR Invalid command or execution failed
 */
static rt_err_t hpm_hwtimer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args);

/**
 * @brief GPTMR interrupt service routine
 * @param [in] gptmr Pointer to GPTMR driver context
 */
#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
static void hpm_hwtmr_isr(hpm_gptimer_t *gptmr);
#else
static void hpm_hwtmr_isr(int vector, hpm_gptimer_t *gptmr);
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */

/* ============================================================================
 * RT-Thread Interface Structures
 * ============================================================================ */

/* RT-Thread hardware timer operations structure - defines the interface between RT-Thread and this driver */
static const struct rt_hwtimer_ops hpm_hwtimer_ops = {
        .init = hpm_hwtimer_init,         /* Initialize timer */
        .start = hpm_hwtimer_start,       /* Start timer */
        .stop = hpm_hwtimer_stop,         /* Stop timer */
        .count_get = hpm_hwtimer_count_get, /* Get current count */
        .control = hpm_hwtimer_control    /* Control timer operations */
};

/* Hardware timer information structure - defines timer capabilities */
static const struct rt_hwtimer_info hpm_hwtimer_info = {
        .maxfreq = 100000000UL,           /* Maximum frequency: 100 MHz */
        .minfreq = 93750UL,               /* Minimum frequency: ~93.75 kHz */
        .maxcnt = 0xFFFFFFFFUL,           /* Maximum count value: 32-bit */
        .cntmode = HWTIMER_CNTMODE_UP     /* Counter mode: count up */
};


/* ============================================================================
 * GPTMR Device Instances
 * ============================================================================ */

/* GPTMR0 device instance - created if BSP_USING_GPTMR0 is enabled */
#ifdef BSP_USING_GPTMR0
GPTMR_DEVICE_DEFINE(0);
#endif

/* GPTMR1 device instance - created if BSP_USING_GPTMR1 is enabled */
#ifdef BSP_USING_GPTMR1
GPTMR_DEVICE_DEFINE(1);
#endif

/* GPTMR2 device instance - created if BSP_USING_GPTMR2 is enabled */
#ifdef BSP_USING_GPTMR2
GPTMR_DEVICE_DEFINE(2);
#endif

/* GPTMR3 device instance - created if BSP_USING_GPTMR3 is enabled */
#ifdef BSP_USING_GPTMR3
GPTMR_DEVICE_DEFINE(3);
#endif

/* GPTMR4 device instance - created if BSP_USING_GPTMR4 is enabled */
#ifdef BSP_USING_GPTMR4
GPTMR_DEVICE_DEFINE(4);
#endif

/* GPTMR5 device instance - created if BSP_USING_GPTMR5 is enabled */
#ifdef BSP_USING_GPTMR5
GPTMR_DEVICE_DEFINE(5);
#endif

/* GPTMR6 device instance - created if BSP_USING_GPTMR6 is enabled */
#ifdef BSP_USING_GPTMR6
GPTMR_DEVICE_DEFINE(6);
#endif

/* GPTMR7 device instance - created if BSP_USING_GPTMR7 is enabled */
#ifdef BSP_USING_GPTMR7
GPTMR_DEVICE_DEFINE(7);
#endif

#ifdef BSP_USING_PTMR
static hpm_gptimer_t timer_ptmr = {
    .name = "PTMR",
    .base = HPM_PTMR,
    .clock_name = clock_ptmr,
    .irq_num = IRQn_PTMR,
    .irq_priority = BSP_PTMR_IRQ_PRIORITY,
};
#endif

/* Array of GPTMR device pointers - used for initialization and management */
static hpm_gptimer_t *s_gptimers[] = {
#ifdef BSP_USING_GPTMR0
       &timer0,
#endif
#ifdef BSP_USING_GPTMR1
       &timer1,
#endif
#ifdef BSP_USING_GPTMR2
       &timer2,
#endif
#ifdef BSP_USING_GPTMR3
       &timer3,
#endif
#ifdef BSP_USING_GPTMR4
       &timer4,
#endif
#ifdef BSP_USING_GPTMR5
       &timer5,
#endif
#ifdef BSP_USING_GPTMR6
       &timer6,
#endif
#ifdef BSP_USING_GPTMR7
       &timer7,
#endif
#ifdef BSP_USING_PTMR
       &timer_ptmr,
#endif
};

#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
/* GPTMR0 ISR - created if BSP_USING_GPTMR0 is enabled */
#ifdef BSP_USING_GPTMR0
GPTMR_ISR_DEFINE(0);
#endif

/* GPTMR1 ISR - created if BSP_USING_GPTMR1 is enabled */
#ifdef BSP_USING_GPTMR1
GPTMR_ISR_DEFINE(1);
#endif

/* GPTMR2 ISR - created if BSP_USING_GPTMR2 is enabled */
#ifdef BSP_USING_GPTMR2
GPTMR_ISR_DEFINE(2);
#endif

/* GPTMR3 ISR - created if BSP_USING_GPTMR3 is enabled */
#ifdef BSP_USING_GPTMR3
GPTMR_ISR_DEFINE(3);
#endif

/* GPTMR4 ISR - created if BSP_USING_GPTMR4 is enabled */
#ifdef BSP_USING_GPTMR4
GPTMR_ISR_DEFINE(4);
#endif

/* GPTMR5 ISR - created if BSP_USING_GPTMR5 is enabled */
#ifdef BSP_USING_GPTMR5
GPTMR_ISR_DEFINE(5);
#endif

/* GPTMR6 ISR - created if BSP_USING_GPTMR6 is enabled */
#ifdef BSP_USING_GPTMR6
GPTMR_ISR_DEFINE(6);
#endif

/* GPTMR7 ISR - created if BSP_USING_GPTMR7 is enabled */
#ifdef BSP_USING_GPTMR7
GPTMR_ISR_DEFINE(7);
#endif

#ifdef BSP_USING_PTMR
RTT_DECLARE_EXT_ISR_M(IRQn_PTMR, ptmr_isr)     \
void ptmr_isr(void)                                \
{                                                        \
    hpm_hwtmr_isr(&timer_ptmr);                            \
}
#endif
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */

/* ============================================================================
 * Function Implementations
 * ============================================================================ */

/**
 * @brief GPTMR interrupt service routine
 *
 * This function is called when a GPTMR interrupt occurs. It handles timer
 * reload events and notifies the RT-Thread hardware timer framework.
 *
 * @param [in] timer Pointer to GPTMR driver context
 */
#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
static void hpm_hwtmr_isr(hpm_gptimer_t *timer)
#else
static void hpm_hwtmr_isr(int vector, hpm_gptimer_t *timer)
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */
{
    /* Read interrupt status from hardware */
    uint32_t hwtmr_stat = gptmr_get_status(timer->base);

    /* Check if reload interrupt occurred for this channel */
    if ((hwtmr_stat & GPTMR_CH_RLD_STAT_MASK(timer->channel)) != 0U)
    {
        /* Notify RT-Thread hardware timer framework */
        rt_device_hwtimer_isr(&timer->timer);

        /* Clear the interrupt status */
        gptmr_clear_status(timer->base, GPTMR_CH_RLD_STAT_MASK(timer->channel));
    }
}

/**
 * @brief Initialize hardware timer
 *
 * This function initializes the GPTMR hardware with default configuration
 * and sets up the timer frequency based on the clock source.
 *
 * @param [in/out] timer Pointer to RT-Thread hardware timer structure
 * @param [in] state Initialization state (1 = enable, 0 = disable)
 */
static void hpm_hwtimer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    GPTMR_GET_CTX(timer);
    gptmr_channel_config_t config;

    if (state == 1)
    {
        /* Add clock to the running core group */
        clock_add_to_group(hpm_gptmr->clock_name, BOARD_RUNNING_CORE & 0x1);

        /* Get and set the timer frequency from clock source */
        hpm_gptmr->timer.freq = clock_get_frequency(hpm_gptmr->clock_name);

        /* Get default channel configuration */
        gptmr_channel_get_default_config(base, &config);

        /* Configure the GPTMR channel (without starting) */
        gptmr_channel_config(base, hpm_gptmr->channel, &config, false);
    }
}

/**
 * @brief Start hardware timer with specified count and mode
 *
 * This function configures and starts the GPTMR timer with the specified
 * count value and mode (one-shot or periodic).
 *
 * @param [in/out] timer Pointer to RT-Thread hardware timer structure
 * @param [in] cnt Timer count value (reload value)
 * @param [in] mode Timer mode (HWTIMER_MODE_ONESHOT or HWTIMER_MODE_PERIOD)
 * @retval RT_EOK Timer started successfully
 * @retval -RT_ERROR Timer start failed
 */
static rt_err_t hpm_hwtimer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
    GPTMR_GET_CTX(timer);

    /* Get default channel configuration */
    gptmr_channel_config_t config;
    gptmr_channel_get_default_config(base, &config);

    /* Configure timer parameters */
    config.cmp[0] = 0;           /* Compare value (not used in this mode) */
    config.reload = cnt;         /* Reload value (timer count) */

    /* Store timer mode */
    timer->mode = mode;

    /* Configure the GPTMR channel and start it */
    gptmr_channel_config(base, hpm_gptmr->channel, &config, true);

    /* Clear any pending interrupt status */
    gptmr_clear_status(base, 0xFU);

    /* Enable reload interrupt for this channel */
    gptmr_enable_irq(base, GPTMR_CH_RLD_IRQ_MASK(hpm_gptmr->channel));

    /* Reset counter to 0 and start counting */
    gptmr_channel_update_count(base, hpm_gptmr->channel, 0);
    gptmr_start_counter(base, hpm_gptmr->channel);

    /* Enable interrupt with configured priority */
    intc_m_enable_irq_with_priority(hpm_gptmr->irq_num, hpm_gptmr->irq_priority);

    return RT_EOK;
}

/**
 * @brief Stop hardware timer
 *
 * This function stops the GPTMR counter from counting.
 *
 * @param [in/out] timer Pointer to RT-Thread hardware timer structure
 */
static void hpm_hwtimer_stop(rt_hwtimer_t *timer)
{
    GPTMR_GET_CTX(timer);

    /* Stop the GPTMR counter */
    gptmr_stop_counter(base, hpm_gptmr->channel);
}

/**
 * @brief Get current timer count value
 *
 * This function reads the current count value from the GPTMR hardware.
 *
 * @param [in] timer Pointer to RT-Thread hardware timer structure
 * @return Current timer count value
 */
static rt_uint32_t hpm_hwtimer_count_get(rt_hwtimer_t *timer)
{
    GPTMR_GET_CTX(timer);

    /* Read current counter value from hardware */
    rt_uint32_t current_cnt = gptmr_channel_get_counter(base, hpm_gptmr->channel, gptmr_counter_type_normal);

    return current_cnt;
}

/**
 * @brief Control hardware timer operations
 *
 * This function handles various control commands for the hardware timer
 * including frequency setting, information retrieval, mode setting, and stopping.
 *
 * @param [in/out] timer Pointer to RT-Thread hardware timer structure
 * @param [in] cmd Control command (HWTIMER_CTRL_*)
 * @param [in/out] args Command arguments (input/output depending on command)
 * @retval RT_EOK Command executed successfully
 * @retval -RT_ERROR Invalid command or execution failed
 */
static rt_err_t hpm_hwtimer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t err = RT_EOK;
    GPTMR_GET_CTX(timer);

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
        /* Frequency setting is not supported (frequency is fixed by clock source) */
        err = -RT_ERROR;
        break;

    case HWTIMER_CTRL_INFO_GET:
        /* Return timer information structure */
        *(rt_hwtimer_t*)args = hpm_gptmr->timer;
        break;

    case HWTIMER_CTRL_MODE_SET:
        /* Set timer mode (one-shot or periodic) */
        hpm_gptmr->timer.mode = *(rt_uint32_t*)args;
        break;

    case HWTIMER_CTRL_STOP:
        /* Stop the timer counter */
        gptmr_stop_counter(base, hpm_gptmr->channel);
        break;
    }

    return err;
}


/* ============================================================================
 * Driver Initialization
 * ============================================================================ */

/**
 * @brief Initialize hardware timer drivers
 *
 * This function initializes all available GPTMR controllers and registers them
 * with the RT-Thread device framework. It sets up the timer information and
 * operations structures for each timer.
 *
 * @retval RT_EOK Initialization successful
 * @retval -RT_ERROR Initialization failed
 */
int rt_hw_hwtimer_init(void)
{
    int ret = RT_EOK;

    /* Initialize each available GPTMR controller */
    for (uint32_t i = 0; i < ARRAY_SIZE(s_gptimers); i++)
    {
        /* Set timer information (capabilities) */
        s_gptimers[i]->timer.info = &hpm_hwtimer_info;

        /* Set timer operations (function pointers) */
        s_gptimers[i]->timer.ops = &hpm_hwtimer_ops;

        /* Register timer device with RT-Thread */
        ret = rt_device_hwtimer_register(&s_gptimers[i]->timer, s_gptimers[i]->name, s_gptimers[i]);
        if (ret != RT_EOK)
        {
            LOG_E("%s register failed\n", s_gptimers[i]->name);
        }
#ifdef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
        /* Register HWTIMER device to irq table */
        rt_hw_interrupt_install(s_gptimers[i]->irq_num, (rt_isr_handler_t)hpm_hwtmr_isr, s_gptimers[i], s_gptimers[i]->name);
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */
    }

    return ret;
}

/* Register initialization function to be called during system startup */
INIT_BOARD_EXPORT(rt_hw_hwtimer_init);

#endif /* RT_USING_HWTIMER */
