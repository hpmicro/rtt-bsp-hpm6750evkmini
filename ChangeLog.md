# Change Log

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
### Update:
- Added examples:
  - blink_led
  - lv_demo_widgets
  - rw007_wifi
  - ethernet_demo
- Switched default target to FLASH XIP
- Integrated the SDK v0.7.1 release
    - Note: the yaml files in SDK were removed, the doxygen files were removed

## V0.2.0
### Update:
- Added support for RW007 WIFI module
- Integrated the SDK v0.7.0 release

## V0.1.0
### Update:
- First RT-Thread BSP package for HPM6750EVKMINI board
- Integrated the SDK v0.6.0 release
