/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_soc.h"
#include "hpm_mbx_drv.h"
#include "hpm_clock_drv.h"
#include "hpm_ipc_event_mgr.h"
#include "hpm_ipc_event_mgr_mbx_config.h"
#include "hpm_ipc_event_mgr_mbx_internal.h"
#if defined(USE_IPC_EVENT_MGR_DECLARE_EXT_ISR_M) || defined(HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK)
#include "hpm_rtt_interrupt_util.h"
#include <rthw.h>
#endif

/*****************************************************************************************************************
 *
 *  Definitions
 *
 *****************************************************************************************************************/

/*****************************************************************************************************************
 *
 *  Prototypes
 *
 *****************************************************************************************************************/

/*****************************************************************************************************************
 *
 *  Variables
 *
 *****************************************************************************************************************/

/*****************************************************************************************************************
 *
 *  Codes
 *
 *****************************************************************************************************************/
#ifdef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
/* NOTE: when the RT-Thread interrupt framework is used, the ISR is dispatched through the
 * RT-Thread interrupt table, so it is installed in ipc_init_internal() */
void mbx_isr(int vector, void *param);
#endif

void ipc_init_internal(void)
{
    clock_add_to_group(HPM_MBX_CLOCK, 0);
    mbx_init(HPM_MBX);
#ifdef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
    /* Register the MBX ISR into the RT-Thread interrupt table */
    rt_hw_interrupt_install(IRQn_MBX, (rt_isr_handler_t)mbx_isr, RT_NULL, "MBX");
#endif
}

void ipc_enable_event_interrupt_internal(uint32_t priority)
{
    mbx_enable_intr(HPM_MBX, MBX_CR_RWMVIE_MASK);
    intc_m_enable_irq_with_priority(IRQn_MBX, priority);
}

void ipc_disable_event_interrupt_internal(void)
{
    mbx_disable_intr(HPM_MBX, MBX_CR_RWMVIE_MASK);
    intc_m_disable_irq(IRQn_MBX);
}

hpm_stat_t ipc_tigger_event_internal(uint32_t remote_data)
{
    return mbx_send_message(HPM_MBX, remote_data);
}

/*!
 * @brief ISR handler
 *
 * This function is called when data from MBX is received
 */
#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
#ifndef USE_IPC_EVENT_MGR_DECLARE_EXT_ISR_M
SDK_DECLARE_EXT_ISR_M(IRQn_MBX, mbx_isr)
#else
RTT_DECLARE_EXT_ISR_M(IRQn_MBX, mbx_isr)
#endif /* USE_IPC_EVENT_MGR_DECLARE_EXT_ISR_M */
void mbx_isr(void)
#else
void mbx_isr(int vector, void *param)
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */
{
#ifdef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
    (void)vector;
    (void)param;
#endif
    uint32_t data;
    hpm_stat_t state;

    state = mbx_retrieve_message(HPM_MBX, &data);

    if (state == status_success) {
        ipc_event_handler(data);
    }
}
