# 更新

## v1.1.0

- 整合了hpm_sdk v1.1.0
  - 注：
    - SDK根目录下的docs,middleware,samples, scripts等目录被移除
- 修复：
  - drv_i2c.c 中的拼写错误
  - hw_timer 工作异常
  - 开启C++支持后RT-Thread Studio工程编译失败
  - iperf 作为客户端时性能低下
  - ADC 驱动可能会返回错误的数据
  - PWM 通道可能会工作不正常
  - uart_dma_demo示例不工作
  - eMMC转TF卡无法工作

## v1.0.0

- 整合了hpm_sdk v1.0.0
  - 注：
    - SDK根目录下的docs,middleware,samples, scripts等目录被移除
- 更新：
  - 改善了drv_uart_v2驱动
  - 实现了audio 驱动
  - 迁移到rt-thread v4.1.0
  - 增加了对JLink调试器的支持
- 新增如下示例：
  - audio_pdm_dao_demo

## v0.7.0

- 整合了SDK v0.12.1
  - 注：
    - SDK根目录下的doc等目录被删除
- 更新：
  - Toolchain切换到RISC-V-GCC-RV32
  - 提升了100M以太网吞吐率
  - 增加了i2c驱动
- 修复：
  - flashdb_demo中fal bench 命令可能会报写错误
  - sd卡 multi-block read/write 错误
- 增加了如下示例：
  - usb_host_msc_udisk

## v0.5.0

- 整合了SDK v0.10.0
  - 注：
    - SDK根目录下的doc目录被删除
- 更新：
  - Tolchain升级到GCC 11.1.0
- 增加了如下示例：
  - can_example
  - ethernet_ptp_master_demo
  - ethernet_ptp_slave_demo

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

### 更新

- 增加了如下示例:
  - blink_led
  - lv_demo_widgets
  - rw007_wifi
  - ethernet_demo
- 将默认构建切换到FLASH_XIP
- 整合了SDK v0.7.1
  - 注意：SDK中的yaml和doxygen文档已删除

## V0.2.0

### 更新

- 增加了rw007_wifi的支持
- 整合了SDK v0.7.0

## V0.1.0

### 更新

- 第一个HPM6750EVKMINI开发板的板级支持包
  - 添加了blink_led 模板
- 整合了SDK v0.6.0
