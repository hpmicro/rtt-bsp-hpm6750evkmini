# 简介

本示例基于LVGL 8.3.5 创建，展示了基于RT-Thread运行的 LVGL Music 示例。

# menuconfig配置

- 需要使能panel，该实例默认开启。
    - 配置路径如下：
        - 若在rtthread studio环境，打开 `RT-Thread Settings`，选择 `Hardware Drivers Config --> On-chip Peripheral Drivers --> Enable panel`
        - 若在ENV环境，执行 `menuconfig`，选择 `Hardware Drivers Config --> On-chip Peripheral Drivers --> Enable panel`

## 硬件连接

- 支持的LCD屏：ZLG LCD-800480W070TC，menuconfig的panel选择TM070RDH13
- 将LCD屏排线连接到HPM6750EVKMINI的LCD接口
###  注意事项

- 请在插入屏幕前确认LCD接口以及显示屏是否匹配，插错屏幕或接口可能会导致器件烧坏

## 运行现象

- 当程序正确下载执行后，屏幕会循环执行 `LVGL Music` 示例
