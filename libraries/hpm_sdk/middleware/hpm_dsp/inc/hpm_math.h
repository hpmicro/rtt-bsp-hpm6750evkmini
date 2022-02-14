/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_MATH_H
#define HPM_MATH_H
/*math mode*/
#define HPM_MATH_MOD_Q_SW               (1) /*Qmath软件*/
#define HPM_MATH_MOD_Q_HW               (2) /*Qmath硬件*/
#define HPM_MATH_MOD_DSP_FP             (3) /*DSP浮点数*/
#define HPM_MATH_MOD_Q_ALL              (4) /*Qmath软件基础、硬件补充*/
#define HPM_MATH_MOD_FP                 (5) /*硬件浮点数  推荐使用该模式获得最佳性能*/

/*Qmath mode*/
#define HPM_QMATH_MOD_Q15               (15)
#define HPM_QMATH_MOD_Q31               (31)
/*用户配置文件*/
#ifdef CONFIG_MATH_HAS_EXTRA_CONFIG
#include CONFIG_MATH_HAS_EXTRA_CONFIG
#endif

#ifdef  __cplusplus
extern "C"
{
#endif

/*定义计算使用的模式，如果不适用QMath那么默认使用 MCU浮点模式*/
#ifndef HPM_MATH_MOD
#define HPM_MATH_MOD                    HPM_MATH_MOD_FP
#endif

#ifndef HPM_QMATH_N
#define HPM_QMATH_N                     HPM_QMATH_MOD_Q31
#endif

#ifndef HPM_SOFT_Q_N
#define HPM_SOFT_Q_N                                (15)
#endif

/*Math method*/
#include "hpm_math_unit.h"
#if HPM_MATH_MOD == HPM_MATH_MOD_Q_SW
    /*软件*/
#if (HPM_QMATH_N != HPM_QMATH_MOD_Q31)
    #error "SOFT Q_MATH only support q31"
#endif
    #include "math.h"
    #define HPM_MATH_FL_MDF(from_f32)                   soft_conv_float_to_q31(from_f32)
    #define HPM_MATH_MDF_FL(from_mdf)                   soft_conv_q31_to_float(from_mdf) 
    #define HPM_MATH_MUL(x,y)                           ((((int64_t)x)*y)>>HPM_SOFT_Q_N)
    #define HPM_MATH_DIV(x,y)                           ((((int64_t)x)<<HPM_SOFT_Q_N)/y)
    #define HPM_MATH_ATAN2(x,y)                         atan2f(x,y)
    #define HPM_MATH_FABS(x)                            abs(x)
#elif  HPM_MATH_MOD == HPM_MATH_MOD_Q_HW
    /*Qmath*/     
    #define HPM_MATH_FL_MDF(from_f32)                  hpm_dsp_hw_f32_q(from_f32)     
    #define HPM_MATH_MDF_FL(from_mdf)                  hpm_dsp_hw_q_f32(from_mdf)       
    #define HPM_MATH_MUL(x,y)                          hpm_dsp_hw_mul_q(x,y) 
    #define HPM_MATH_DIV(x,y)                          hpm_dsp_hw_div_q(x,y) 
    #define HPM_MATH_ATAN2(x,y)                        hpm_dsp_hw_atan2_q(x,y)
    #define HPM_MATH_ATAN(x)                           hpm_dsp_hw_atan_q(x) 
    #define HPM_MATH_FABS(x)                           hpm_dsp_hw_abs_q(x)
  
#elif HPM_MATH_MOD == HPM_MATH_MOD_DSP_FP
    #define HPM_MATH_FL_MDF(from_f32)                   (from_f32)
    #define HPM_MATH_MDF_FL(from_mdf)                   (from_mdf)
    #define HPM_MATH_MUL(x,y)                           hpm_dsp_hw_mul_fp(x,y)
    #define HPM_MATH_DIV(x,y)                           hpm_dsp_hw_div_fp(x,y)
    #define HPM_MATH_ATAN2(x,y)                         hpm_dsp_hw_atan2_fp(x,y)
    #define HPM_MATH_ATAN(x)                            hpm_dsp_hw_atan_fp(x)
    #define HPM_MATH_FABS(x)                            hpm_dsp_hw_abs_fp(x)
#elif HPM_MATH_MOD == HPM_MATH_MOD_FP
    #include "math.h"
    #define HPM_MATH_FL_MDF(from_f32)                   (from_f32)
    #define HPM_MATH_MDF_FL(from_mdf)                   (from_mdf)   
    #define HPM_MATH_MUL(x,y)                           (x*y)  
    #define HPM_MATH_DIV(x,y)                           (x/y)
    #define HPM_MATH_ATAN2(x,y)                         atan2(x,y)
    #define HPM_MATH_ATAN(x)                            atan(x)
    #define HPM_MATH_FABS(x)                            abs(x)
#endif

#ifdef  __cplusplus
}
#endif

#endif