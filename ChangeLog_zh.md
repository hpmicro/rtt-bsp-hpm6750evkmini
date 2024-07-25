# 更新

## v1.6.0

- 整合了hpm_sdk v1.6.0
- 修复:
    - UART7 和 UART8 TX DMA 相关的宏定义错误问题
    - uart_v2 中的内存泄露问题
- 更新：
    - 优化CANFD帧的BRS位控制
    - 升级CherryUSB协议栈到1.3.1
    - 为USB例程增加了全速模式相关的描述符
    - 芯片的数据手册
    - 优化了SDIO驱动，增加了SDIO的`BUS_WIDTH`等配置选项，增加eMMC HS400支持，增加SD UHS-I 速度模式支持
    - 在`sdcard_demo`示例中增加了性能测试命令
- 新增:
    - SPI 的CS引脚控制选项
    - 适配了RT-Thread Cache 驱动
- 新增示例：
  - airoc_wifi_demo （英飞凌 AIROC 系列WiFi）

## v1.5.0

- 整合了hpm_sdk v1.5.0
- 更新:
    - USB相关sample协议栈切换为cherryUSB
    - ETH PHY 抽象层多实例支持和优化
- 修复:
    - CAN sample开启硬件过滤器读取数据错误的问题
- 新增:
    - 增加中断向量模式和可抢占模式
    - pwm sample
    - systemView组件
    - rtt lcd driver驱动

## v1.4.1
- 修复：
  - I2C开启DMA后传输出错的问题
  - 默认模板工程创建出错的问题

## v1.4.0

- 整合了hpm_sdk v1.4.0
- 升级RT-Thread 到 v5.0.2
- 更新
    - 增强了 SPI 驱动
    - 增强了 I2C 驱动
    - 增加了 SDIO驱动对多SDXC实例的支持
    - 增加了对 `rt_pin_get` API的支持
    - 统一了ethernet phy驱动
    - 增加了i2s驱动
    - RTC驱动中默认使能电池域掉电保持
- 修复：
    - 修复了`pwm`驱动返回值类型不匹配的问题
- 新增示例
    - wifi_web_camera_demo

## v1.3.0

- 整合了hpm_sdk v1.3.0
    - 注：
        - SDK根目录下的docs,middleware,samples, scripts等目录被移除
- 更新
    - 增加了SVD文件的支持
    - CAN: 增加了硬件过滤器支持
    - 默认禁用了PWM输出反向
- 修复：
    - RT-Thread Studio生成的elf文件无法被`Ozone`正确的识别
    - 在线包`i2c tools`不工作
    - 以太网在网络风暴产生后工作不正常
    - 音频声道控制在产生上溢/下溢后产生异常
    - 当开启`ADC12`后编译失败
    - GPIO在配置为开漏极并上拉模式后无法正确的读出引脚的电平

## v1.2.0

- 整合了hpm_sdk v1.2.0
    - 注：
        - SDK根目录下的docs,middleware,samples, scripts等目录被移除
- 更新
    - 迁移到rt-thread v5.0.1
    - 优化了lvgl demo的性能
    - 增加了sample README
    - 增加了 `flash_release` 和 `ram_release` 工程
    - 增加了 UART RXFIFO timeout 中断支持
- 修复：
    - sd card 性能慢
    - uart 在低波特率下丢数据

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