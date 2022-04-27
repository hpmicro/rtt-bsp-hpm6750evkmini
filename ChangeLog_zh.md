# 更新日志

## v0.4.1
- 更新
    - 为每个示例增加了ram_debug 配置
    - 默认串口驱动切换到serial_v2
- 修复
    - serial_v2 在不使能POSIX接口时会崩溃
    - 不支持FPU上下文切换
    - rw007_wifi 示例在某些情况下会崩溃
## v0.4.0
- 整合了SDK v0.9.0
  - 注：
    - SDK根目录下的doc目录被删除
- 增加了如下示例：
    - timer_demo
- 更新
    - 优化了ethernet PHY 接口

## v0.3.0
- 整合了SDK v0.8.0
  - 注：
    - SDK根目录下的doc目录被删除
    - UART和DMA驱动有细微的改动
- 增加了如下示例：
    - flashdb_demo
    - sdcard_demo
    - pwmbeep_demo
    - usb_device_generic_hid
    - uart_dma_demo

## v0.2.1
### 更新:
- 增加了如下示例:
  - blink_led
  - lv_demo_widgets
  - rw007_wifi
  - ethernet_demo
- 将默认构建切换到FLASH_XIP
- 整合了SDK v0.7.1
    - 注意：SDK中的yaml和doxygen文档已删除

## V0.2.0
### 更新:
- 增加了rw007_wifi的支持
- 整合了SDK v0.7.0

## V0.1.0
### 更新:
- 第一个HPM6750EVKMINI开发板的板级支持包
  - 添加了blink_led 模板
- 整合了SDK v0.6.0
