# Copyright (c) 2024 HPMicro
# SPDX-License-Identifier: BSD-3-Clause

sdk_compile_definitions(-D__USE_JL1111=1)

sdk_inc(.)
sdk_inc(../)
sdk_src(hpm_jl1111.c)
