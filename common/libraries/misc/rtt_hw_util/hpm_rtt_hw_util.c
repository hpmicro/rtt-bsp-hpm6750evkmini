/*
 * Copyright (c) 2026 HPMicro
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-15     HPMicro      Add RISC-V RV32 backtrace support
 */
#include "hpm_rtt_hw_util.h"
#include "board.h"
#include "hpm_soc.h"
#include "hpm_l1c_drv.h"
#include "hpm_csr_drv.h"
#include <rtthread.h>
#include <rthw.h>

#ifdef HPM_ENABLE_RTTHREAD_BACKTRACE_PORT

#define DBG_TAG "hw.backtrace"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define WORD                            sizeof(rt_base_t)

/* RISC-V context switch frame indices */
#ifndef RT_HW_SWITCH_CONTEXT_RA
#define RT_HW_SWITCH_CONTEXT_RA  0  /* Return address (x1) */
#endif

#ifndef RT_HW_SWITCH_CONTEXT_S0
#define RT_HW_SWITCH_CONTEXT_S0  8  /* Frame pointer (x8/s0) */
#endif


/**
 * @brief Unwind the target frame for RISC-V
 *
 * This function unwinds one level of the call stack for RISC-V architecture.
 * It retrieves the previous frame pointer and return address from the current frame
 * following the standard RISC-V calling convention with frame pointers.
 *
 * RISC-V calling convention (with -fno-omit-frame-pointer):
 * - Frame pointer (fp/s0/x8) points to the current frame base
 * - *(fp - 1*WORD) = return address (where WORD is 4 for RV32, 8 for RV64)
 * - *(fp - 2*WORD) = previous frame pointer
 *
 * Stack grows downward, so deeper frames have lower addresses.
 *
 * @param thread the thread which frame belongs to
 * @param frame the specified frame to be unwound
 * @return rt_err_t RT_EOK on success, negative error code on failure
 */
rt_err_t rt_hw_backtrace_frame_unwind(rt_thread_t thread, struct rt_hw_backtrace_frame *frame)
{
    rt_err_t rc = -RT_ERROR;
    rt_ubase_t *fp = (rt_ubase_t *)frame->fp;

    /* Validate frame pointer:
     * - Must be non-null
     * - Must be properly aligned (4-byte for RV32, 8-byte for RV64 via WORD)
     */
    if (fp && !((rt_ubase_t)fp & (WORD - 1)))
    {
        /* Optional: validate frame is within thread's stack bounds for extra safety */
        if (thread && thread->stack_addr)
        {
            rt_ubase_t stack_start = (rt_ubase_t)(uintptr_t)thread->stack_addr;
            rt_ubase_t stack_end = (rt_ubase_t)(uintptr_t)(thread->stack_addr + thread->stack_size);
            
            if ((rt_ubase_t)fp < stack_start || (rt_ubase_t)fp >= stack_end)
            {
                return -RT_EFAULT;
            }
        }

        /* Extract caller's frame pointer and return address following RISC-V convention:
         * *(fp - 2*WORD) = previous frame pointer (where to unwind to)
         * *(fp - 1*WORD) = return address (PC in caller's context)
         */
        rt_ubase_t caller_fp = *(fp - 2);
        rt_ubase_t caller_pc = *(fp - 1);

        /* Detect stack bottom: if new fp equals old fp, we've reached the end */
        if ((rt_ubase_t)fp == caller_fp)
        {
            rc = -RT_ERROR;
        }
        else
        {
            frame->fp = caller_fp;
            frame->pc = caller_pc;
            rc = RT_EOK;
        }
    }
    else
    {
        rc = -RT_EFAULT;
    }
    return rc;
}

/**
 * @brief Get the innermost frame of target thread for RISC-V
 *
 * This function retrieves the innermost (current/innermost) frame information
 * for a given thread. It extracts the frame pointer and program counter from
 * the thread's saved context when the thread was switched out.
 *
 * For RISC-V:
 * - Frame pointer (s0/x8) represents the base of the current stack frame
 * - Return address (ra/x1) is the next instruction to execute after return
 *
 * @param thread the thread which frame belongs to
 * @param frame pointer to store the retrieved frame information
 * @return rt_err_t RT_EOK on success, negative error code on failure
 */
rt_err_t rt_hw_backtrace_frame_get(rt_thread_t thread, struct rt_hw_backtrace_frame *frame)
{
    rt_err_t rc;

    if (!thread || !frame)
    {
        rc = -RT_EINVAL;
    }
    else
    {
        /* Get the saved context from thread's stack pointer when thread was switched out.
         * thread->sp points to the saved register context array.
         * For RISC-V, registers are saved in a fixed order defined by context_gcc.S
         */
        rt_ubase_t *psp = (rt_ubase_t *)thread->sp;
        
        /* Extract return address from saved context
         * RT_HW_SWITCH_CONTEXT_RA is the index where ra (x1) is saved
         */
        frame->pc = psp[RT_HW_SWITCH_CONTEXT_RA];
        
        /* Extract frame pointer from saved context
         * RT_HW_SWITCH_CONTEXT_S0 is the index where s0 (x8/fp) is saved
         */
        frame->fp = psp[RT_HW_SWITCH_CONTEXT_S0];
        
        rc = RT_EOK;
    }
    return rc;
}
#endif

void rt_hw_us_delay(rt_uint32_t us)
{
    uint64_t expected_ticks = hpm_csr_get_core_cycle() + (uint64_t)clock_get_core_clock_ticks_per_us() * (uint64_t)us;
    while (hpm_csr_get_core_cycle() < expected_ticks) {
    }
}

void rt_hw_cpu_reset(void)
{
    HPM_PPOR->RESET_ENABLE |= (1UL << 31);
    HPM_PPOR->SOFTWARE_RESET = 1000U;
    while(1) {
        /* Wait for reset */
    }
}

#ifdef RT_USING_CACHE
void rt_hw_cpu_dcache_ops(int ops, void *addr, int size)
{
    if (ops == RT_HW_CACHE_FLUSH) {
        l1c_dc_flush((uint32_t)addr, size);
    } else {
        l1c_dc_invalidate((uint32_t)addr, size);
    }
}
#endif
