/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/11/30     Bernard      The first version.
 * 2025-06-26     RCSN         fix compatibility issue with Segger Embedded Studio
 */

#include <stdint.h>
#include <stdio.h>

#include <rtthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#ifdef __SES_VERSION
#include <errno.h>
#else
#include <sys/errno.h>
#endif

#include "sys/mman.h"

void *mmap(void *addr, size_t length, int prot, int flags,
    int fd, off_t offset)
{
    uint8_t *mem;

    if (addr)
    {
        mem = addr;
    }
    else mem = (uint8_t *)malloc(length);

    if (mem)
    {
        off_t cur;
        size_t read_bytes;

        cur = lseek(fd, 0, SEEK_SET);

        lseek(fd, offset, SEEK_SET);
        read_bytes = read(fd, mem, length);
        if (read_bytes != length)
        {
            if (addr == RT_NULL)
            {
                /* read failed */
                free(mem);
                mem = RT_NULL;
            }
        }
        lseek(fd, cur, SEEK_SET);

        return mem;
    }

    errno = ENOMEM;

    return MAP_FAILED;
}

int munmap(void *addr, size_t length)
{
    if (addr)
    {
        free(addr);
        return 0;
    }

    return -1;
}
