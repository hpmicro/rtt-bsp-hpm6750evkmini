/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PLIC_DRV_H
#define HPM_PLIC_DRV_H

#define HPM_PLIC_TARGET_M_MODE 0
#define HPM_PLIC_TARGET_S_MODE 1

/* Feature Register */
#define HPM_PLIC_FEATURE_OFFSET (0x00000000UL)
#define HPM_PLIC_FEATURE_VECTORED_MODE (0x2UL)
#define HPM_PLIC_FEATURE_PREEMPTIVE_PRIORITY_IRQ (0x1UL)

/* Priority Register - 32 bits per irq */
#define HPM_PLIC_PRIORITY_OFFSET (0x00000004UL)
#define HPM_PLIC_PRIORITY_SHIFT_PER_SOURCE 2

/* Pending Register - 1 bit per source */
#define HPM_PLIC_PENDING_OFFSET (0x00001000UL)
#define HPM_PLIC_PENDING_SHIFT_PER_SOURCE 0

/* Enable Register - 0x80 per target */
#define HPM_PLIC_ENABLE_OFFSET (0x00002000UL)
#define HPM_PLIC_ENABLE_SHIFT_PER_TARGET 7

/* Priority Threshold Register - 0x1000 per target */
#define HPM_PLIC_THRESHOLD_OFFSET (0x00200000UL)
#define HPM_PLIC_THRESHOLD_SHIFT_PER_TARGET 12

/* Claim Register - 0x1000 per target */
#define HPM_PLIC_CLAIM_OFFSET (0x00200004UL)
#define HPM_PLIC_CLAIM_SHIFT_PER_TARGET 12

#if !defined(__ASSEMBLER__)
__attribute__((always_inline))
    static inline void __plic_set_feature(uint32_t base, uint32_t feature)
{
    *(volatile uint32_t *)(base + HPM_PLIC_FEATURE_OFFSET) = feature;
}

__attribute__((always_inline))
    static inline void __plic_set_threshold(uint32_t base,
                                            uint32_t target,
                                            uint32_t threshold)
{
    volatile uint32_t *threshold_ptr = (volatile uint32_t *)(base +
            HPM_PLIC_THRESHOLD_OFFSET +
            (target << HPM_PLIC_THRESHOLD_SHIFT_PER_TARGET));
    *threshold_ptr = threshold;
}

__attribute__((always_inline))
    static inline void __plic_set_irq_priority(uint32_t base,
                                               uint32_t irq,
                                               uint32_t priority)
{
    volatile uint32_t *priority_ptr = (volatile uint32_t *)(base +
            HPM_PLIC_PRIORITY_OFFSET + ((irq-1) << HPM_PLIC_PRIORITY_SHIFT_PER_SOURCE));
    *priority_ptr = priority;
}

__attribute__((always_inline))
    static inline void __plic_set_irq_pending(uint32_t base, uint32_t irq)
{
    volatile uint32_t *current_ptr = (volatile uint32_t *)(base +
            HPM_PLIC_PENDING_OFFSET + ((irq >> 5) << 2));
    *current_ptr = (1 << (irq & 0x1F));
}

__attribute__((always_inline))
    static inline void __plic_enable_irq(uint32_t base,
                                         uint32_t target,
                                         uint32_t irq)
{
    volatile uint32_t *current_ptr = (volatile uint32_t *)(base +
            HPM_PLIC_ENABLE_OFFSET +
            (target << HPM_PLIC_ENABLE_SHIFT_PER_TARGET) +
            ((irq >> 5) << 2));
    uint32_t current = *current_ptr;
    current = current | (1 << (irq & 0x1F));
    *current_ptr = current;
}

__attribute__((always_inline))
    static inline void __plic_disable_irq(uint32_t base,
                                          uint32_t target,
                                          uint32_t irq)
{
    volatile uint32_t *current_ptr = (volatile uint32_t *)(base +
            HPM_PLIC_ENABLE_OFFSET +
            (target << HPM_PLIC_ENABLE_SHIFT_PER_TARGET) +
            ((irq >> 5) << 2));
    uint32_t current = *current_ptr;
    current = current & ~((1 << (irq & 0x1F)));
    *current_ptr = current;
}

__attribute__((always_inline))
    static inline uint32_t __plic_claim_irq(uint32_t base, uint32_t target)
{
    volatile uint32_t *claim_addr = (volatile uint32_t *)(base +
            HPM_PLIC_CLAIM_OFFSET +
            (target << HPM_PLIC_CLAIM_SHIFT_PER_TARGET));
    return *claim_addr;
}

__attribute__((always_inline))
    static inline void __plic_complete_irq(uint32_t base,
                                           uint32_t target,
                                           uint32_t irq)
{
    volatile uint32_t *claim_addr = (volatile uint32_t *)(base +
            HPM_PLIC_CLAIM_OFFSET +
            (target << HPM_PLIC_CLAIM_SHIFT_PER_TARGET));
    *claim_addr = irq;
}
#endif /* __ASSEMBLER__ */
#endif	/* HPM_PLIC_DRV_H */
