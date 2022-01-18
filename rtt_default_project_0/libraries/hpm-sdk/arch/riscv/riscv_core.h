/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef RISCV_CORE_H
#define RISCV_CORE_H

#include "hpm_common.h"

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((always_inline)) static inline void write_fcsr(uint32_t v)
{
    __asm volatile("fscsr %0" : : "r"(v));
}

__attribute__((always_inline)) static inline void clear_csr(const uint32_t csr_num, uint32_t bit)
{
    __asm volatile("csrc %0, %1" : : "i"(csr_num), "r"(bit));
}

__attribute__((always_inline)) static inline void set_csr(const uint32_t csr_num, uint32_t bit)
{
    __asm volatile("csrs %0, %1" : : "i"(csr_num), "r"(bit));
}

__attribute__((always_inline)) static inline void write_csr(const uint32_t csr_num, uint32_t v)
{
    __asm volatile("csrw %0, %1" : : "i"(csr_num), "r"(v));
}

__attribute__((always_inline)) static inline uint32_t read_csr(const uint32_t csr_num)
{
    uint32_t v;
    __asm volatile("csrr %0, %1" : "=r"(v) : "i"(csr_num));
    return v;
}

__attribute__((always_inline)) static inline uint32_t read_fcsr(void)
{
    uint32_t v;
    __asm volatile("frcsr %0" : "=r"(v));
    return v;
}

__attribute__((always_inline)) static inline void fencei(void)
{
    __asm volatile("fence.i");
}


#ifdef __cplusplus
}
#endif


#endif /* RISCV_CORE_H */
