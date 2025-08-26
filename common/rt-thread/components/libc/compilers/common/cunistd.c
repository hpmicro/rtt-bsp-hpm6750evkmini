/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-08-16     Meco Man     first version
 * 2025-06-17     Fan YANG     Fix compatibility issue with Segger Embedded Studio
 */

#include <rtthread.h>
#include <unistd.h>
#ifdef __SES_VERSION
#include <errno.h>

#else
#include <sys/errno.h>
#endif

int isatty(int fd)
{
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    if(fd == STDOUT_FILENO || fd == STDERR_FILENO)
    {
        return 1;
    }
#endif /* defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE) */

#ifdef RT_USING_POSIX_STDIO
    if(fd == STDIN_FILENO)
    {
        return 1;
    }
#endif /* RT_USING_POSIX_STDIO */

    rt_set_errno(ENOTTY);
    return 0;
}
RTM_EXPORT(isatty);
