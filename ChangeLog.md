# Change Log

## v1.9.0

- Integrated hpm_sdk v1.9.0

- Updated:
    - Upgrade `CherryUSB` stack to 1.4.3
    - `sdio` driver supports configurable IRQ priority
    - `uart/uart_v2` driver supports configurable IRQ priority
    - `spi` driver supports for configurable IRQ priority for 
    - `i2c` driver support for configurable IRQ priority
    - `gpio` driver support for configurable IRQ priority
    - `lcd` driver supports for configurable IRQ priority
    - `can` driver supports configurable IRQ priority


- Fixed:
    - Fixed the issue of the same MAC address between the master and slave devices in `thernet_ptp_slave_demo`

- Added:
    - The `sdio` driver has added interrupt-driven mode
    - DSPI/QSPI mode added for `spi` driver

## v1.6.0

- Integrated hpm_sdk v1.6.0
- Updated:
    - Optimized the control of `BRS` bit in CANFD frame
    - Upgraded the `cherryUSB` stack to v1.3.1
    - Added USB descriptor for Full-speed mode to USB examples
    - Upgraded the SoC Datasheet
    - Optimized SDIO driver, added new configuration options such as `BUS_WDITH`，Added eMMC HS400 support, Added SD UHS-I speed mode support
- Fixed:
    - Macro definition errors related to  TX DMA for UART7 & UART7
    - Memory leakage issue in uart_v2 driver
- Added:
    - SPI CS pin control option
    - Adapted RT-Thread Cache API
    - Added performance test command to `sdcard_demo`
- New Examples:
    - airoc_wifi_demo (Infinieon AIROC WiFi series)

## v1.5.0

- Integrated hpm_sdk v1.5.0
- Updated:
    - usb stack switched to cherryUSB for usb samples
    - ETH PHY abstraction layer multi-instance support and optimization
- Fixed:
    - CAN sample read data error when enable RT_CAN_USING_HDR
- Added:
    - added interrupt vector mode and preemptive mode
    - pwm sample
    - systemView component
    - rtt lcd driver

## 1.4.1
- Fixed:
  - Transmission error while enabling DMA in I2C driver
  - Failed to create template project

## v1.4.0

- Integrated hpm_sdk v1.4.0
- Upgraded RT-Thread to v5.0.2
- Updated:
    - Improved SPI driver
    - Improved I2C driver
    - Added multiple SDXC instance support to sdio driver
    - Added support for `rt_pin_get` API
    - Unified the ethernet phy driver
    - Improved the i2s driver
    - Enabled retention mode for battery domain in RTC driver
- Fixed:
    - Fixed the mismatch data type issue for return value of API in `pwm` driver
- Added examples:
    - web_camera_demo

## v1.3.0
- Integrated hpm_sdk v1.3.0
  - Note:
    - the docs, middleware, scripts, samples folder in SDK root directory were removed
- Updated:
    - Added SVD support
    - Added hardware filter support to `CAN` driver
    - Disable PWM invert output by default
  - Fixed:
    - elf file generated by RT-Thread Studio cannot be recognized by Ozone properly
    - online package `i2c tools` cannot work
    - ethernet may fail to work when network storm happened
    - audio channel control may be unexpected if i2s overflow/underflow happened
    - compiling error if `ADC12` is enabled
    - GPIO cannot read back pin level correctly if it is configured as Open-Drain Pull-up mode
## v1.2.0
- Integrated hpm_sdk v1.2.0
  - Note:
    - the docs, middleware, scripts, samples folder in SDK root directory were removed
- Updated:
    - Upgraded rt-thread to v5.0.1
    - Optimized the performance of LVGL demo
    - Added `README.md` for all samples
    - Added UART RXFIFO timeout interrupt support
    - Added `flash_release` build and `ram_release` build
  - Fixed:
    - SD card performance is slow
    - Uart lost data when working in low baudrate

## v1.1.0

- Integrated hpm_sdk v1.1.0
  - Note:
    - the docs, middleware, scripts, samples folder in SDK root directory were removed
- Fixed:
  - typos in the drv_i2c.c
  - hw_timer cannot work due to SDK driver update
  - RT-Thread Studio project compiling error after enabling C++ support
  - iperf performance is low if working as client mode
  - adc driver may return incorrect value
  - pwm channel may not work as expected
  - uart_dma_demo doesn't work
  - eMMC to TF card doesn't work

## v1.0.0

- Integrated hpm_sdk v1.0.0
  - Note:
    - the docs, middleware, scripts, samples folder in SDK root directory were removed
- Updated:
  - Improved drv_uart_v2 implementation
  - Implemented audio driver
  - Migrated to rt-thread v4.1.0
  - Added support for JLink Probe
- Added examples:
  - audio_pdm_dao_demo

## v0.7.0

- Integrated the SDK v0.12.1 release
  - Note:
    - The docs,middleware folder in SDK root directory were removed
- Updated:
  - Switched toolchain to RISC-V-GCC-RV32
  - Improved the throughput for 100M Ethernet
  - Implemented i2c driver
- Fixed:
  - flashdb_demo: "fal bench" command may report error
  - SD card multi-block read/write issue
- Added examples:
  - usb_host_msc_udisk

## v0.5.0

- Integrated the SDK v0.10.0 release
  - Note:
    - The docs folder in SDK root directory were removed
- Updated
  - Upgraded toolchain to GCC 11.1.0
- Added examples:
  - can_example
  - ethernet_ptp_master_demo
  - ethernet_ptp_slave_demo

## v0.4.1

- Updated
  - Added ram_debug for each demo
  - Switched default UART driver to serial_v2
- Fixed
  - serial_v2 crashes if POSIX interface is not enabled
  - FPU context switch is not supported
  - rw007_wifi demo may crash in certain cases

## v0.4.0

- Integrated the SDK v0.9.0 release
  - Note:
    - The docs folder in SDK root directory were removed
- Added examples:
  - timer_demo
- Updated
  - Optimized ethernet phy interface

## v0.3.0

- Integrated the SDK v0.8.0 release
  - Note:
    - The docs folder in SDK root directory were removed
    - There are small changes in uart and dma driver
- Added examples:
  - flashdb_demo
  - sdcard_demo
  - pwmbeep_demo
  - usb_device_generic_hid
  - uart_dma_demo

## v0.2.1

### Update

- Added examples:
  - blink_led
  - lv_demo_widgets
  - rw007_wifi
  - ethernet_demo
- Switched default target to FLASH XIP
- Integrated the SDK v0.7.1 release
  - Note: the yaml files in SDK were removed, the doxygen files were removed

## V0.2.0

### Update

- Added support for RW007 WIFI module
- Integrated the SDK v0.7.0 release

## V0.1.0

### Update

- First RT-Thread BSP package for HPM6750EVKMINI board
- Integrated the SDK v0.6.0 release