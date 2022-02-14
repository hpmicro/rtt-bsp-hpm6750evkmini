# Copyright 2021 hpmicro
# SPDX-License-Identifier: BSD-3-Clause

add_subdirectory_ifdef(CONFIG_LVGL littlevgl)
add_subdirectory_ifdef(CONFIG_TINYUSB tinyusb)
add_subdirectory_ifdef(CONFIG_TINYCRYPT tinycrypt)
add_subdirectory_ifdef(CONFIG_FATFS fatfs)
add_subdirectory_ifdef(CONFIG_FREERTOS FreeRTOS)
add_subdirectory_ifdef(CONFIG_FREEMASTER freemaster)
add_subdirectory_ifdef(CONFIG_MOTORCTRL motor_ctrl)
add_subdirectory_ifdef(CONFIG_SDMMC sdmmc)
add_subdirectory_ifdef(CONFIG_LIBJPEG libjpeg-turbo)
add_subdirectory_ifdef(CONFIG_HPM_DSP hpm_dsp)
add_subdirectory_ifdef(CONFIG_LWIP lwip)
