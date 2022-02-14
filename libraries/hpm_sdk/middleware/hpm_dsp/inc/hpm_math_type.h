/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_MATH_TYPE_H
#define HPM_MATH_TYPE_H
/*Math type*/
#include <stdint.h>
#if HPM_MATH_MOD == HPM_MATH_MOD_Q_SW
    typedef     int32_t     HPM_MATH_TYPE;
#elif  HPM_MATH_MOD == HPM_MATH_MOD_Q_HW
    #ifndef HPM_QMATH_N
    #define HPM_QMATH_N                 HPM_QMATH_MOD_Q31
    #endif
    #if (HPM_QMATH_N == HPM_QMATH_MOD_Q15)
    typedef     int16_t     HPM_MATH_TYPE;/*Q15格式*/
    #elif (HPM_QMATH_N == HPM_QMATH_MOD_Q31)
    typedef     int32_t     HPM_MATH_TYPE;/*Q31格式*/
    #endif
#elif HPM_MATH_MOD == HPM_MATH_MOD_DSP_FP
    typedef    float                                    HPM_MATH_TYPE;  
#elif HPM_MATH_MOD == HPM_MATH_MOD_FP
    typedef    float                                    HPM_MATH_TYPE;
#endif

#endif