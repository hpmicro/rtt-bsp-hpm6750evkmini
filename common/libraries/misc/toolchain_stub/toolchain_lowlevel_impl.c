/*
 * Copyright (c) 2026 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
 #ifdef __SES_RISCV
 #include <stdio.h>
 #ifdef __SEGGER_RTL_VERSION
 #include "__SEGGER_RTL_Int.h"
 #include <rtthread.h>

 #include <ctype.h>
 __attribute__((used)) int _impure_ptr; /* Workaround for fixing compiling error with SES */
 /* Workaround for fixing compiling error that the _ctype_ array is missing in SES toolchain */
 const char _ctype_[] = { 00,
                         20, 20, 20, 20, 20, 20, 20, 20, 20, 28, 28, 28, 28, 28, 20, 20,
                         20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
                         88, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
                         04, 04, 04, 04, 04, 04, 04, 04, 04, 04, 10, 10, 10, 10, 10, 10,
                         10, 41, 41, 41, 41, 41, 41, 01, 01, 01, 01, 01, 01, 01, 01, 01,
                         01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 10, 10, 10, 10, 10,
                         10, 42, 42, 42, 42, 42, 42, 02, 02, 02, 02, 02, 02, 02, 02, 02,
                         02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 02, 10, 10, 10, 10, 20
 };


void * __SEGGER_RTL_alloc(size_t sz)
{
    return rt_malloc(sz);
}

void __SEGGER_RTL_free(void *ptr)
{
    rt_free(ptr);
}

void * __SEGGER_RTL_aligned_alloc(size_t align, size_t sz)
{
    return rt_malloc_align(align, sz);
}

void * __SEGGER_RTL_realloc(void *ptr, size_t sz)
{
    return rt_realloc(ptr, sz);
}
 
 __attribute__((used)) int __SEGGER_RTL_X_file_write(__SEGGER_RTL_FILE *file, const char *data, unsigned int size)
{
    (void) file;
 
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_device_t console_device = rt_console_get_device();
    if (console_device != RT_NULL) {
        rt_device_write(console_device, 0, data, size);
    }
#endif
    return size;
}
#endif
#else
#include <stdio.h>
#include <rtthread.h>
int _write(int file, char *data, int size)
{
    (void) file;
 
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_device_t console_device = rt_console_get_device();
    if (console_device != RT_NULL) {
        rt_device_write(console_device, 0, data, size);
    }
#endif
    return size;
}

int _read(int file, char *s, int size)
{
    (void) file;
    int ret = 1;
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_device_t console_device = rt_console_get_device();
    if (console_device != RT_NULL) {
        ret = rt_device_read(console_device, 0, s, size);
    }
#endif
    return ret;
}

#if defined(__zcc__)

__attribute__((used)) int _impure_ptr; /* Workaround for fixing compiling error with zcc */

void *malloc(size_t size)
{
    return rt_malloc(size);
}

void free(void *ptr)
{
    rt_free(ptr);
}

void *realloc(void *ptr, size_t size)
{
    return rt_realloc(ptr, size);
}

void *calloc(size_t nmemb, size_t size)
{
    return rt_calloc(nmemb, size);
}

/* Aligned allocation functions */
void *aligned_alloc(size_t alignment, size_t size)
{
    return rt_malloc_align(size, alignment);
}

void *memalign(size_t alignment, size_t size)
{
    return rt_malloc_align(size, alignment);
}

int posix_memalign(void **memptr, size_t alignment, size_t size)
{
    if (memptr == NULL) {
        return 22; /* EINVAL */
    }
    
    /* alignment must be a power of 2 and multiple of sizeof(void*) */
    if ((alignment % sizeof(void*)) != 0 || (alignment & (alignment - 1)) != 0) {
        return 22; /* EINVAL */
    }
    
    *memptr = rt_malloc_align(size, alignment);
    if (*memptr == NULL) {
        return 12; /* ENOMEM */
    }
    
    return 0;
}
#endif

#endif