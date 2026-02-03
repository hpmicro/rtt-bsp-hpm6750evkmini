#ifndef __RT_LOG_PRINT_H__
#define __RT_LOG_PRINT_H__

#include "rtthread.h"

#define COLOR_RED     "\033[1;31m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_BLUE    "\033[1;34m"
#define COLOR_MAGENTA "\033[1;35m"
#define COLOR_CYAN    "\033[1;36m"
#define COLOR_RESET   "\033[0m"

#define LOG_ERROR(fmt, ...)                                        \
    rt_kprintf(COLOR_RED "[ERROR][%s:%d] " fmt COLOR_RESET "\r\n", \
               __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define LOG_WARN(fmt, ...)                                           \
    rt_kprintf(COLOR_YELLOW "[WARN][%s:%d] " fmt COLOR_RESET "\r\n", \
               __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define LOG_INFO(fmt, ...)                                         \
    rt_kprintf(COLOR_BLUE "[INFO][%s:%d] " fmt COLOR_RESET "\r\n", \
               __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define LOG_DEBUG(fmt, ...)                                         \
    rt_kprintf(COLOR_CYAN "[DEBUG][%s:%d] " fmt COLOR_RESET "\r\n", \
               __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define LOG_TRACE(fmt, ...)                                            \
    rt_kprintf(COLOR_MAGENTA "[TRACE][%s:%d] " fmt COLOR_RESET "\r\n", \
               __FUNCTION__, __LINE__, ##__VA_ARGS__)

#endif // __RT_LOG_PRINT_H__
