
#include "rtthread.h"

#ifndef __HWCONFIG_H__

#ifndef RT_VERSION_CHECK
#define RT_VERSION_CHECK(major, minor, revise)          ((major * 10000) + (minor * 100) + revise)
#endif

#ifdef SOC_IMXRT1060_SERIES
#define WL_REGON_PORT	0 //GPIO1
#define WL_REGON_PIN	3
#define WL_HWOOB_PORT	0 //GPIO1
#define WL_HWOOB_PIN	2
#endif
#ifdef SOC_IMXRT1170_SERIES
#define WL_REGON_PORT	2 //GPIO3
#define WL_REGON_PIN	6
#define WL_HWOOB_PORT	2 //GPIO3
#define WL_HWOOB_PIN	0
#endif
#ifdef SOC_STM32H743ZI
#define WL_REGON_PORT	1 //GPIOB
#define WL_REGON_PIN	8 //GPIO_PIN_8
#define WL_HWOOB_PORT	2 //GPIOC
#define WL_HWOOB_PIN	6 //GPIO_PIN_6
#endif

#if 0 //def SOC_HPM6000 //HPM6750
#define WL_REGON_PORT	3  //PD19
#define WL_REGON_PIN	19
#define WL_HWOOB_PORT	3  //PD24
#define WL_HWOOB_PIN	24
#endif

#ifdef SOC_HPM6000 //HPM6800
#define WL_REGON_PORT	4  //PE17
#define WL_REGON_PIN	17
#define WL_HWOOB_PORT	4  //PE16
#define WL_HWOOB_PIN	16
#endif


#endif