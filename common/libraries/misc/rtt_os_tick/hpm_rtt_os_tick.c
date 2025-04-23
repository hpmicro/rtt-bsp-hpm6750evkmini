/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-24     HPMicro      the first version
 */
#include "board.h"
#include "rtt_board.h"
#include "assert.h"
#include "hpm_clock_drv.h"
#include "hpm_sysctl_drv.h"
#include <rthw.h>
#include <rtthread.h>
#ifdef HPM_USING_VECTOR_PREEMPTED_MODE
#include "hpm_gptmr_drv.h"
#include <rtdevice.h>
#include "drv_hwtimer.h"
#include "hpm_rtt_interrupt_util.h"
#include "hpm_rtt_os_tick.h"
#else
#include "hpm_mchtmr_drv.h"
#endif

extern void rtt_board_init(void);

#ifdef HPM_USING_VECTOR_PREEMPTED_MODE
extern volatile rt_ubase_t  rt_interrupt_from_thread;
extern volatile rt_ubase_t  rt_interrupt_to_thread;
extern volatile rt_uint32_t rt_thread_switch_interrupt_flag;
volatile rt_thread_t  rt_interrupt_from_thread_thread = 0;
volatile rt_thread_t  rt_interrupt_to_thread_thread   = 0;

void rt_trigger_software_interrupt(void)
{
    __plic_set_irq_pending(HPM_PLIC_BASE, IRQn_PendSV);
}

void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to, rt_thread_t from_thread, rt_thread_t to_thread)
{
    if (rt_thread_switch_interrupt_flag == 0) {
        rt_interrupt_from_thread_thread = from_thread;
        rt_interrupt_from_thread = from;
    }

    rt_interrupt_to_thread = to;
    rt_interrupt_to_thread_thread = to_thread;
    rt_thread_switch_interrupt_flag = 1;

    rt_trigger_software_interrupt();
}

void rtt_context_switch_init()
{
    intc_m_enable_irq_with_priority(IRQn_PendSV, 1);
}
rt_uint32_t rt_context_switch_flag;
rt_uint32_t sp_before_addr;
rt_uint32_t sp_from_addr;
void debug0_isr(void)
{
    rt_base_t level;

    rt_uint32_t stack_addr = (rt_uint32_t)((rt_thread_t *)rt_interrupt_from_thread_thread->stack_addr);
    rt_uint32_t stack_size = (rt_uint32_t)((rt_thread_t *)rt_interrupt_from_thread_thread->stack_size);
    rt_context_switch_flag =0;

    if(rt_thread_switch_interrupt_flag)
    {
        if(sp_before_addr > stack_addr && sp_before_addr < (stack_addr + stack_size)) {
            rt_context_switch_flag = 1;
        }
        else {
            printf("sp not matched with from_stack,sp:%d,from_satck_addr:%d,from_stack_size:%d\n",sp_before_addr,stack_addr,stack_size);
        }
    }
    rt_thread_switch_interrupt_flag = 0;
}
RTT_DECLARE_EXT_ISR_M(IRQn_PendSV, debug0_isr);

void os_gtimer_isr(void)
{
    if (gptmr_check_status(BOARD_OS_TIMER, GPTMR_CH_RLD_STAT_MASK(BOARD_OS_TIMER_CH))) {
        rt_tick_increase();
        gptmr_clear_status(BOARD_OS_TIMER, GPTMR_CH_RLD_STAT_MASK(BOARD_OS_TIMER_CH));
    }
}
RTT_DECLARE_EXT_ISR_M(BOARD_OS_TIMER_IRQ, os_gtimer_isr);
#endif

void os_tick_config(void)
{
#ifdef HPM_USING_VECTOR_PREEMPTED_MODE
    uint32_t gptmr_freq;
    gptmr_channel_config_t config;

    gptmr_channel_get_default_config(BOARD_OS_TIMER, &config);

    gptmr_freq = clock_get_frequency(BOARD_OS_TIMER_CLK_NAME);
    config.reload = gptmr_freq / RT_TICK_PER_SECOND;
    gptmr_channel_config(BOARD_OS_TIMER, BOARD_OS_TIMER_CH, &config, false);
    gptmr_start_counter(BOARD_OS_TIMER, BOARD_OS_TIMER_CH);

    gptmr_enable_irq(BOARD_OS_TIMER, GPTMR_CH_RLD_IRQ_MASK(BOARD_OS_TIMER_CH));
    intc_m_enable_irq_with_priority(BOARD_OS_TIMER_IRQ, 1);
#else
    sysctl_config_clock(HPM_SYSCTL, clock_node_mchtmr0, clock_source_osc0_clk0, 1);
    sysctl_add_resource_to_cpu0(HPM_SYSCTL, sysctl_resource_mchtmr0);

    mchtmr_set_compare_value(HPM_MCHTMR, BOARD_MCHTMR_FREQ_IN_HZ / RT_TICK_PER_SECOND);

    enable_mchtmr_irq();
#endif
}

void rt_hw_board_init(void)
{
    rtt_board_init();

#ifdef HPM_USING_VECTOR_PREEMPTED_MODE
    rtt_context_switch_init();
#endif

    /* Call the RT-Thread Component Board Initialization */
    rt_components_board_init();
}

#ifndef HPM_USING_VECTOR_PREEMPTED_MODE
ATTR_PLACE_AT(".isr_vector") void mchtmr_isr(void)
{
    HPM_MCHTMR->MTIMECMP = HPM_MCHTMR->MTIME + BOARD_MCHTMR_FREQ_IN_HZ / RT_TICK_PER_SECOND;

    rt_tick_increase();
}
#endif
