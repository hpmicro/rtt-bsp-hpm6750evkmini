# Copyright 2021 hpmicro
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.13)

find_package(hpm-sdk REQUIRED HINTS $ENV{HPM_SDK_BASE})

project(dsp_demo)

sdk_compile_options("-mext-dsp")

sdk_ld_options("-lm -ldsp")

sdk_app_src(src/dsp_demo.c)
generate_ses_project()
