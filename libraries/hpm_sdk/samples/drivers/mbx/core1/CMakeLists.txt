# Copyright 2021 hpmicro
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.13)

find_package(hpm-sdk REQUIRED HINTS $ENV{HPM_SDK_BASE})

project(mbx_example_core1)

sdk_compile_definitions(BOARD_RUNNING_CORE=HPM_CORE1)
sdk_app_src(../src/mbx.c)
generate_ses_project()
