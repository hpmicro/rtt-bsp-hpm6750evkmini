/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-25     quanzhao     the first version
 */
#ifndef __CACHE_H__
#define __CACHE_H__

unsigned long rt_cpu_get_smp_id(void);

void rt_cpu_mmu_disable(void);
void rt_cpu_mmu_enable(void);
void rt_cpu_tlb_set(volatile unsigned long*);

void rt_cpu_dcache_clean_flush(void);
void rt_cpu_icache_flush(void);

void rt_cpu_vector_set_base(unsigned int addr);

#endif
