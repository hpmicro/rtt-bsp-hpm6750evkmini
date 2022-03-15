/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */



#include "hpm_common.h"
#include "hpm_soc.h"

#define MCAUSE_INSTR_ADDR_MISALIGNED (0U)       //!< Instruction Address misaligned
#define MCAUSE_INSTR_ACCESS_FAULT (1U)          //!< Instruction access fault
#define MCAUSE_ILLEGAL_INSTR (2U)               //!< Illegal instruction
#define MCAUSE_BREAKPOINT (3U)                  //!< Breakpoint
#define MCAUSE_LOAD_ADDR_MISALIGNED (4U)        //!< Load address misaligned
#define MCAUSE_LOAD_ACCESS_FAULT (5U)           //!< Load access fault
#define MCAUSE_STORE_AMO_ADDR_MISALIGNED (6U)   //!< Store/AMO address misaligned
#define MCAUSE_STORE_AMO_ACCESS_FAULT (7U)      //!< Store/AMO access fault
#define MCAUSE_ECALL_FROM_USER_MODE (8U)        //!< Environment call from User mode
#define MCAUSE_ECALL_FROM_SUPERVISOR_MODE (9U)  //!< Environment call from Supervisor mode
#define MCAUSE_ECALL_FROM_MACHINE_MODE (11U)    //!< Environment call from machine mode
#define MCAUSE_INSTR_PAGE_FAULT (12U)           //!< Instruction page fault
#define MCAUSE_LOAD_PAGE_FAULT (13)             //!< Load page fault
#define MCAUSE_STORE_AMO_PAGE_FAULT (15U)       //!< Store/AMO page fault

#define IRQ_S_SOFT              1
#define IRQ_H_SOFT              2
#define IRQ_M_SOFT              3
#define IRQ_S_TIMER             5
#define IRQ_H_TIMER             6
#define IRQ_M_TIMER             7
#define IRQ_S_EXT               9
#define IRQ_H_EXT               10
#define IRQ_M_EXT               11
#define IRQ_COP                 12
#define IRQ_HOST                13


typedef void (*isr_func_t)(void);

__attribute((weak)) void mchtmr_isr(void)
{
}

__attribute__((weak)) void mswi_isr(void)
{
}

__attribute__((weak)) void syscall_handler(uint32_t n, uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3)
{
}

__attribute__((weak)) uint32_t exception_handler(uint32_t cause, uint32_t epc)
{
    /* Unhandled Trap */
    return epc;
}

void trap_entry(void) __attribute__((section(".isr_vector")));

void trap_entry(void)
{
    uint32_t mcause = read_csr(CSR_MCAUSE);
    uint32_t mepc = read_csr(CSR_MEPC);
    uint32_t mstatus = read_csr(CSR_MSTATUS);
#if SUPPORT_PFT_ARCH
    uint32_t mxstatus = read_csr(CSR_MXSTATUS);
#endif
#ifdef __riscv_dsp
    int ucode = read_csr(CSR_UCODE);
#endif
#ifdef __riscv_flen
    int fcsr = read_fcsr();
#endif

    /* clobbers list for ecall */
#ifdef __riscv_32e
    __asm volatile("" : : :"t0", "a0", "a1", "a2", "a3");
#else
    __asm volatile("" : : :"a7", "a0", "a1", "a2", "a3");
#endif

    /* Do your trap handling */
    uint32_t cause_type = mcause & CSR_MCAUSE_EXCEPTION_CODE_MASK;
    uint32_t irq_index;
    if (mcause & CSR_MCAUSE_INTERRUPT_MASK) {
        switch(cause_type) {
            /* Machine timer interrupt */
        case IRQ_M_TIMER:
            mchtmr_isr();
            break;
            /* Machine EXT interrupt */
        case IRQ_M_EXT:
            /* Claim interrupt */
            irq_index = __plic_claim_irq(HPM_PLIC_BASE, HPM_PLIC_TARGET_M_MODE);
            /* Execute EXT interrupt handler */
            ((isr_func_t)__vector_table[irq_index])();
            /* Complete interrupt */
            __plic_complete_irq(HPM_PLIC_BASE, HPM_PLIC_TARGET_M_MODE, irq_index);
            break;
            /* Machine SWI interrupt */
        case IRQ_M_SOFT:
            mswi_isr();
            intc_m_complete_swi();
            break;
        }
    }
    else if (cause_type == MCAUSE_ECALL_FROM_MACHINE_MODE) {
               /* Machine Syscal call */
        __asm volatile(
                "mv a4, a3\n"
                "mv a3, a2\n"
                "mv a2, a1\n"
                "mv a1, a0\n"
#ifdef __riscv_32e
                "mv a0, t0\n"
#else
                "mv a0, a7\n"
#endif
                "call syscall_handler\n"
                : : : "a4"
        );
        mepc += 4;
    }
    else {
        mepc = exception_handler(mcause, mepc);
    }

    /* Restore CSR */
    write_csr(CSR_MSTATUS, mstatus);
    write_csr(CSR_MEPC, mepc);
#if SUPPORT_PFT_ARCH
    write_csr(CSR_MXSTATUS, mxstatus);
#endif
#ifdef __riscv_dsp
    write_csr(CSR_UCODE, ucode);
#endif
#ifdef __riscv_flen
    write_fcsr(fcsr);
#endif
}
