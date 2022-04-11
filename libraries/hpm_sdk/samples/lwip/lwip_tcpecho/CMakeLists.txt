# Copyright 2021 hpmicro
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.13)

set(CONFIG_LWIP 1)
#set(CONFIG_ENET_DP83867_MASTER 1)
set(CONFIG_ENET_DP83848_MASTER 1)

find_package(hpm-sdk REQUIRED HINTS $ENV{HPM_SDK_BASE})

sdk_compile_definitions(-DENET_MCU_CORE=BOARD_RUNNING_CORE)

if(${CONFIG_ENET_DP83867_MASTER})
    sdk_compile_definitions(-DRGMII=1)
endif()

if(${CONFIG_ENET_DP83848_MASTER})
    sdk_compile_definitions(-DRGMII=0)
endif()

project(lwip_tcpecho_example)

sdk_inc(src)
sdk_inc(../common)
sdk_inc(../common/eth)
sdk_inc(../common/arch)
sdk_inc(src/app)

sdk_app_src(src/lwip.c)
sdk_app_src(../common/arch/ethernetif.c)
sdk_app_src(../common/eth/netconf.c)
sdk_app_src(src/app/tcp_echo.c)
generate_ses_project()


