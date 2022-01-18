/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_INTERRUPT_H
#define HPM_INTERRUPT_H
#include "riscv/riscv_core.h"

#include "hpm_plic_drv.h"

#define M_MODE 0    /*!< Machine mode */
#define S_MODE 1    /*!< Supervisor mode */

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((always_inline))
    static inline void enable_global_irq(uint32_t mask)
{
    set_csr(CSR_MSTATUS, mask);
}

__attribute__((always_inline))
    static inline void disable_global_irq(uint32_t mask)
{
    clear_csr(CSR_MSTATUS, mask);
}

__attribute__((always_inline)) static inline void enable_irq_from_intc(void)
{
    set_csr(CSR_MIE, CSR_MIP_MEIP_MASK);
}

__attribute__((always_inline)) static inline void disable_irq_from_intc(void)
{
    clear_csr(CSR_MIE, CSR_MIP_MEIP_MASK);
}

/*
 * CPU Machine timer control
 */
__attribute__((always_inline)) static inline void enable_mchtmr_irq(void)
{
    set_csr(CSR_MIE, CSR_MIP_MTIP_MASK);
}

__attribute__((always_inline)) static inline void disable_mchtmr_irq(void)
{
    clear_csr(CSR_MIE, CSR_MIP_MTIP_MASK);
}

/*
 * CPU Machine SWI control
 *
 * Machine SWI (MSIP) is connected to PLICSW irq 1.
 */
#define PLICSWI 1
__attribute__((always_inline)) static inline void intc_m_init_swi(void)
{
    __plic_set_irq_priority(HPM_PLICSW_BASE, PLICSWI, 1);
    __plic_enable_irq(HPM_PLICSW_BASE, HPM_PLIC_TARGET_M_MODE, PLICSWI);
}

__attribute__((always_inline)) static inline void intc_m_enable_swi(void)
{
    set_csr(CSR_MIE, CSR_MIP_MSIP_MASK);
}

__attribute__((always_inline)) static inline void intc_m_disable_swi(void)
{
    clear_csr(CSR_MIE, CSR_MIP_MSIP_MASK);
}

__attribute__((always_inline))
    static inline void intc_m_trigger_swi(void)
{
    __plic_set_irq_pending(HPM_PLICSW_BASE, PLICSWI);
}

__attribute__((always_inline))
    static inline void intc_m_complete_swi(void)
{
    __plic_complete_irq(HPM_PLICSW_BASE, HPM_PLIC_TARGET_M_MODE, PLICSWI);
}

#define intc_m_enable_irq(irq) \
    intc_enable_irq(HPM_PLIC_TARGET_M_MODE, irq)

#define intc_m_disable_irq(irq) \
    intc_disable_irq(HPM_PLIC_TARGET_M_MODE, irq)

#define intc_m_set_threshold(threshold) \
    intc_set_threshold(HPM_PLIC_TARGET_M_MODE, threshold)

#define intc_m_complete_irq(irq) \
    intc_complete_irq(HPM_PLIC_TARGET_M_MODE, irq)

#define intc_m_claim_irq() intc_claim_irq(HPM_PLIC_TARGET_M_MODE)

#define intc_m_enable_irq_with_priority(irq, priority) \
    do { \
        intc_set_irq_priority(irq, priority); \
        intc_m_enable_irq(irq); \
    } while(0);

/*
 * Platform defined irq controller access
 *
 * This uses the vectored PLIC scheme.
 */
__attribute__((always_inline))
    static inline void intc_enable_irq(uint32_t target, uint32_t irq)
{
    __plic_enable_irq(HPM_PLIC_BASE, target, irq);
}

__attribute__((always_inline))
    static inline void intc_set_irq_priority(uint32_t irq, uint32_t priority)
{
    __plic_set_irq_priority(HPM_PLIC_BASE, irq, priority);
}

__attribute__((always_inline))
    static inline void intc_disable_irq(uint32_t target, uint32_t irq)
{
    __plic_disable_irq(HPM_PLIC_BASE, target, irq);
}

__attribute__((always_inline))
    static inline void intc_set_threshold(uint32_t target, uint32_t threshold)
{
    __plic_set_threshold(HPM_PLIC_BASE, target, threshold);
}

__attribute__((always_inline))
    static inline uint32_t intc_claim_irq(uint32_t target)
{
    return __plic_claim_irq(HPM_PLIC_BASE, target);
}

__attribute__((always_inline))
    static inline void intc_complete_irq(uint32_t target, uint32_t irq)
{
    __plic_complete_irq(HPM_PLIC_BASE, target, irq);
}

/*
 * Vectored based irq install and uninstall
 */
extern int __vector_table[];
extern void default_irq_entry(void);

__attribute__((always_inline)) static inline void install_isr(uint32_t irq, uint32_t isr)
{
    __vector_table[irq] = isr;
}

__attribute__((always_inline)) static inline void uninstall_isr(uint32_t irq)
{
    __vector_table[irq] = (int)default_irq_entry;
}

/*
 * Inline nested irq entry/exit macros
 */
/* Save/Restore macro */
#define SAVE_CSR(r)                                     register long __##r = read_csr(r);
#define RESTORE_CSR(r)                                  write_csr(r, __##r);

#if SUPPORT_PFT_ARCH
#define SAVE_MXSTATUS()                                 SAVE_CSR(CSR_MXSTATUS)
#define RESTORE_MXSTATUS()                              RESTORE_CSR(CSR_MXSTATUS)
#else
#define SAVE_MXSTATUS()
#define RESTORE_MXSTATUS()
#endif

#ifdef __riscv_flen
#define SAVE_FCSR()                                     register int __fcsr = read_fcsr();
#define RESTORE_FCSR()                                  write_fcsr(__fcsr);
#else
#define SAVE_FCSR()
#define RESTORE_FCSR()
#endif

#ifdef __riscv_dsp
#define SAVE_UCODE()                                    SAVE_CSR(CSR_UCODE)
#define RESTORE_UCODE()                                 RESTORE_CSR(CSR_UCODE)
#else
#define SAVE_UCODE()
#define RESTORE_UCODE()
#endif

#ifdef __riscv_flen
/* RV32I caller registers + MCAUSE + MEPC + MSTATUS +MXSTATUS + UCODE (DSP) + 21 FPU caller registers */
#define CONTEXT_REG_NUM (4*(16 + 4 + 1 + 21))
#else
/* RV32I caller registers + MCAUSE + MEPC + MSTATUS +MXSTATUS + UCODE (DSP)*/
#define CONTEXT_REG_NUM (4*(16 + 4 + 1))
#endif

#ifdef __riscv_flen
/*
 * Save FPU caller registers:
 * NOTE: To simplify the logic, the FPU caller registers are always stored at word offset 21 in the stack
 */
#define SAVE_FPU_CONTEXT()  { \
    __asm volatile("fsw ft0, 21*4(sp) \n\
             fsw ft1, 22*4(sp) \n\
             fsw ft2, 23*4(sp) \n\
             fsw ft3, 24*4(sp) \n\
             fsw ft4, 25*4(sp) \n\
             fsw ft5, 26*4(sp) \n\
             fsw ft6, 27*4(sp) \n\
             fsw ft7, 28*4(sp) \n\
             fsw fa0, 29*4(sp) \n\
             fsw fa1, 30*4(sp) \n\
             fsw fa2, 31*4(sp) \n\
             fsw fa3, 32*4(sp) \n\
             fsw fa4, 33*4(sp) \n\
             fsw fa5, 34*4(sp) \n\
             fsw fa6, 35*4(sp) \n\
             fsw fa7, 36*4(sp) \n\
             fsw ft8, 37*4(sp) \n\
             fsw ft9, 38*4(sp) \n\
             fsw ft10, 39*4(sp) \n\
             fsw ft11, 40*4(sp) \n\
             frsr t6 \n\
             sw t6, 41*4(sp) \n");\
}

/*
 * Restore FPU caller registers:
 * NOTE: To simplify the logic, the FPU caller registers are always stored at word offset 21 in the stack
 */
#define RESTORE_FPU_CONTEXT() { \
    __asm volatile("flw ft0, 21*4(sp) \n\
             flw ft1, 22*4(sp) \n\
             flw ft2, 23*4(sp) \n\
             flw ft3, 24*4(sp) \n\
             flw ft4, 25*4(sp) \n\
             flw ft5, 26*4(sp) \n\
             flw ft6, 27*4(sp) \n\
             flw ft7, 28*4(sp) \n\
             flw fa0, 29*4(sp) \n\
             flw fa1, 30*4(sp) \n\
             flw fa2, 31*4(sp) \n\
             flw fa3, 32*4(sp) \n\
             flw fa4, 33*4(sp) \n\
             flw fa5, 34*4(sp) \n\
             flw fa6, 35*4(sp) \n\
             flw fa7, 36*4(sp) \n\
             flw ft8, 37*4(sp) \n\
             flw ft9, 38*4(sp) \n\
             flw ft10, 39*4(sp) \n\
             flw ft11, 40*4(sp) \n\
             lw t6, 41*4(sp) \n\
             fssr t6, t6 \n");\
}
#else
#define SAVE_FPU_CONTEXT()
#define RESTORE_FPU_CONTEXT()
#endif

/**
 * @brief Save the caller registers based on the RISC-V ABI specification
 */
#define SAVE_CALLER_CONTEXT()   { \
    __asm volatile("addi sp, sp, %0" : : "i"(-CONTEXT_REG_NUM) :);\
    __asm volatile("sw ra,  0*4(sp) \n\
            sw t0,  1*4(sp) \n\
            sw t1,  2*4(sp) \n\
            sw t2,  3*4(sp) \n\
            sw a0,  4*4(sp) \n\
            sw a1,  5*4(sp) \n\
            sw a2,  6*4(sp) \n\
            sw a3,  7*4(sp) \n\
            sw a4,  8*4(sp) \n\
            sw a5,  9*4(sp) \n\
            sw a6, 10*4(sp) \n\
            sw a7, 11*4(sp) \n\
            sw t3, 12*4(sp) \n\
            sw t4, 13*4(sp) \n\
            sw t5, 14*4(sp) \n\
            sw t6, 15*4(sp)"); \
            SAVE_FPU_CONTEXT(); \
}

/**
 * @brief Restore the caller registers based on the RISC-V ABI specification
 */
#define RESTORE_CALLER_CONTEXT() { \
        __asm volatile("lw ra,  0*4(sp) \n\
            lw t0,  1*4(sp) \n\
            lw t1,  2*4(sp) \n\
            lw t2,  3*4(sp) \n\
            lw a0,  4*4(sp) \n\
            lw a1,  5*4(sp) \n\
            lw a2,  6*4(sp) \n\
            lw a3,  7*4(sp) \n\
            lw a4,  8*4(sp) \n\
            lw a5,  9*4(sp) \n\
            lw a6, 10*4(sp) \n\
            lw a7, 11*4(sp) \n\
            lw t3, 12*4(sp) \n\
            lw t4, 13*4(sp) \n\
            lw t5, 14*4(sp) \n\
            lw t6, 15*4(sp) \n");\
            RESTORE_FPU_CONTEXT(); \
        __asm volatile("addi sp, sp, %0" : : "i"(CONTEXT_REG_NUM) :);\
}

#ifdef __riscv_dsp
/*
 * Save DSP context
 * NOTE: To simplify the logic, DSP context registers are always stored at word offset 20 in the stack
 */
#define SAVE_DSP_CONTEXT() { \
    __asm volatile("csrr t6, ucode\n\
            sw t6, 20*4(sp)\n");  \
}
/*
 * Restore DSP context
 * NOTE: To simplify the logic, DSP context registers are always stored at word offset 20 in the stack
 */
#define RESTORE_DSP_CONTEXT() {\
    __asm volatile("lw t6, 20*4(sp)\n\
            csrw ucode, t6 \n"); \
}
#else
#define SAVE_DSP_CONTEXT()
#define RESTORE_DSP_CONTEXT()
#endif

/*
 * Enter Nested IRQ Handling
 * NOTE: To simplify the logic, Nested IRQ related registers are stored in the stack as below:
 *       MCAUSE - word offset 16 (not used in the vectored mode)
 *       EPC - word offset 17
 *       MSTATUS = word offset 18
 *       MXSTATUS = word offset 19
 */
#define ENTER_NESTED_IRQ_HANDLING_M() {\
    __asm volatile("csrr t6, mepc \n\
            sw t6, 17*4(sp) \n\
            csrr t6, mstatus \n\
            sw t6, 18*4(sp) \n\
            csrr t6, %0\n\
            sw t6, 19*4(sp) \n\
    " : : "i" CSR_MSTATUS);\
    SAVE_DSP_CONTEXT(); \
    __asm volatile("li t6, %0\n" : : "i" (CSR_MSTATUS_MIE_MASK)); \
    __asm volatile("csrrs t6, mstatus, t6\n"); \
}
#define COMPLETE_IRQ_HANDLING_M(irq_num) {\
    __asm volatile("li t0, 0xe4000000 \n\
            li t1, 0x200004 \n\
            add t0, t0, t1 \n\
            lui t1, 0 \n\
            slli t2, t1, 0xc \n\
            add t0, t0, t2 \n");\
    __asm volatile("li t1, %0" : : "i" (irq_num) :); \
    __asm volatile("sw t1, 0(t0) \n\
            fence io, io \n\
            li t6, 1\n\
            addi t6, t6, -0x800\n\
            csrrs t6, mie, t6 \n"); \
}

/*
 * Exit Nested IRQ Handling
 * NOTE: To simplify the logic, Nested IRQ related registers are stored in the stack as below:
 *       MCAUSE - word offset 16 (not used in the vectored mode)
 *       EPC - word offset 17
 *       MSTATUS = word offset 18
 *       MXSTATUS = word offset 19
 */
#define EXIT_NESTED_IRQ_HANDLING_M() { \
    __asm volatile("csrrci t6, mstatus, 8 \n\
            lw t6, 18*4(sp) \n\
            csrw mstatus, t6 \n\
            lw t6, 17*4(sp) \n\
            csrw mepc, t6 \n\
            lw t6, 19*4(sp) \n\
            csrw %0, t6 \n" : : "i" CSR_MSTATUS);\
            RESTORE_DSP_CONTEXT(); \
}


/* Nested IRQ entry macro : Save CSRs and enable global irq. */
#define NESTED_IRQ_ENTER()                              \
        SAVE_CSR(CSR_MEPC)                              \
        SAVE_CSR(CSR_MSTATUS)                           \
        SAVE_MXSTATUS()                                 \
        SAVE_FCSR()                                     \
        SAVE_UCODE()                                    \
        set_csr(CSR_MSTATUS, CSR_MSTATUS_MIE_MASK);

/* Nested IRQ exit macro : Restore CSRs */
#define NESTED_IRQ_EXIT()                               \
        clear_csr(CSR_MSTATUS, CSR_MSTATUS_MIE_MASK);            \
        RESTORE_CSR(CSR_MSTATUS)                        \
        RESTORE_CSR(CSR_MEPC)                           \
        RESTORE_MXSTATUS()                              \
        RESTORE_FCSR()                                  \
        RESTORE_UCODE()

#define NESTED_VPLIC_COMPLETE_INTERRUPT(irq)            \
do {                                                    \
    clear_csr(CSR_MIE, CSR_MIP_MEIP_MASK);                       \
    __plic_complete_irq(HPM_PLIC_BASE, HPM_PLIC_TARGET_M_MODE, irq);  \
    __asm volatile("fence io, io");                     \
    set_csr(CSR_MIE, CSR_MIP_MEIP_MASK);                         \
} while(0)


#ifdef __cplusplus
#define EXTERN_C extern "C" 
#else
#define EXTERN_C
#endif

#define ISR_NAME_M(irq_num) default_isr_##irq_num
/**
 * @brief Declare an external interrupt handler for machine mode
 *
 * @param irq_num - IRQ number index
 * @param isr - Application IRQ handler function pointer
 */
#ifndef USE_NONVECTOR_MODE
#define SDK_DECLARE_EXT_ISR_M(irq_num, isr) \
void isr(void) __attribute__((section(".isr_vector")));\
EXTERN_C void ISR_NAME_M(irq_num)(void) __attribute__((section(".isr_vector")));\
void ISR_NAME_M(irq_num)(void) {\
    SAVE_CALLER_CONTEXT(); \
    ENTER_NESTED_IRQ_HANDLING_M();\
    __asm volatile("la t1, %0\n\t" : : "i" (isr) : );\
    __asm volatile("jalr t1\n");\
    EXIT_NESTED_IRQ_HANDLING_M();\
    COMPLETE_IRQ_HANDLING_M(irq_num);\
    RESTORE_CALLER_CONTEXT();\
    __asm volatile("mret\n");\
}
#else
#define SDK_DECLARE_EXT_ISR_M(irq_num, isr) \
void ISR_NAME_M(irq_num)(void)  {           \
    isr();                                            \
}
#endif


/**
 * @brief Declare machine timer interrupt handler
 *
 * @param isr - MCHTMR IRQ handler function pointer
 */
#define SDK_DECLARE_MCHTMR_ISR(isr) \
void isr(void) __attribute__((section(".isr_vector")));\
void mchtmr_isr(void) {\
    isr();\
}

/**
 * @brief Declare machine software interrupt handler
 *
 * @param isr - SWI IRQ handler function pointer
 */
#define SDK_DECLARE_MSWI_ISR(isr)\
void isr(void) __attribute__((section(".isr_vector")));\
void mswi_isr(void) {\
    isr();\
}


#ifdef __cplusplus
}
#endif

#endif /* HPM_INTERRUPT_H */
