# Copyright 2021 hpmicro
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.13)
set(CONFIG_FREEMASTER 1)
set(CONFIG_MOTORCTRL 1)
set(CONFIG_HPM_DSP 1)

find_package(hpm-sdk REQUIRED HINTS $ENV{HPM_SDK_BASE})
project(bldc_block)

sdk_app_inc(src)
sdk_app_src(src/bldc_block_callback.c)
sdk_app_src(src/bldc_block.c)
generate_ses_project()
