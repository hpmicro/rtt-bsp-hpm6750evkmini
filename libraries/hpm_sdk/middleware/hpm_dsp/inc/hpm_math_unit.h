/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_MATH_UNIT_H
#define HPM_MATH_UNIT_H

#ifdef  __cplusplus
extern "C"
{
#endif
#include "hpm_math_type.h"
HPM_MATH_TYPE hpm_dsp_hw_f32_q(float from_f32);
float hpm_dsp_hw_q_f32(HPM_MATH_TYPE from_mdf);
HPM_MATH_TYPE hpm_dsp_hw_mul_q(HPM_MATH_TYPE x , HPM_MATH_TYPE y);
HPM_MATH_TYPE hpm_dsp_hw_div_q(HPM_MATH_TYPE x , HPM_MATH_TYPE y);
HPM_MATH_TYPE hpm_dsp_hw_atan_q(HPM_MATH_TYPE x);
HPM_MATH_TYPE hpm_dsp_hw_atan2_q(HPM_MATH_TYPE x , HPM_MATH_TYPE y);
HPM_MATH_TYPE hpm_dsp_hw_abs_q(HPM_MATH_TYPE x);

HPM_MATH_TYPE hpm_dsp_hw_mul_fp(HPM_MATH_TYPE x , HPM_MATH_TYPE y);
HPM_MATH_TYPE hpm_dsp_hw_div_fp(HPM_MATH_TYPE x , HPM_MATH_TYPE y);
HPM_MATH_TYPE hpm_dsp_hw_atan_fp(HPM_MATH_TYPE x);
HPM_MATH_TYPE hpm_dsp_hw_atan2_fp(HPM_MATH_TYPE x , HPM_MATH_TYPE y);
HPM_MATH_TYPE hpm_dsp_hw_abs_fp(HPM_MATH_TYPE x);

static inline HPM_MATH_TYPE soft_conv_float_to_q31(float x)
{
    HPM_MATH_TYPE q31;
    int64_t q64;
    double x1 =x;
    x1 *= (1<< HPM_SOFT_Q_N);
    x1 += (x < 0.0f ? -0.5f : 0.5f);
    q64 = (HPM_MATH_TYPE)x1;
    if (q64 >= INT32_MAX){
        q64 = INT32_MAX;
    }
    else if (q64 <= INT32_MIN){
        q64 = INT32_MIN;
    }
    else{
        q31 = (HPM_MATH_TYPE)q64;
    }
    return q31;
}
static inline float soft_conv_q31_to_float(HPM_MATH_TYPE x)
{
    float val;
    val= (double)x/(1<<HPM_SOFT_Q_N);
    return val;
}
#ifdef  __cplusplus
}
#endif

#endif
