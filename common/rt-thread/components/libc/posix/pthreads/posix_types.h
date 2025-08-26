/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-12-23     Bernard      Add the checking for ESHUTDOWN
 * 2025-06-26     RCSN         fix compatibility issue with Segger Embedded Studio
 */

#ifndef __POSIX_TYPES_H__
#define __POSIX_TYPES_H__

#include <rtthread.h>

#include <stddef.h>
#include <stdarg.h>
#include <string.h>

#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#ifdef __SES_VERSION
#include <errno.h>
#else
#include <sys/errno.h>
#endif
#include <fcntl.h>

#endif
