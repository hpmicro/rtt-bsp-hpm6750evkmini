# 简介

本例程演示基于RT-Thread驱动框架的 hwtimer和watchdog驱动以及RTC驱动。

## 演示的功能

- watchdog 复位
- hwtimer 周期性中断
- RTC 闹钟

## 支持的命令

```console
RT-Thread shell commands:
del_alarm_sample - delete alarm sample
alarm_sample     - alarm sample
wdt_reset        - wdt reset
wdt_sample       - wdt sample
hwtimer_sample   - hwtimer_sample
reset            - reset the board
list             - list objects
version          - show RT-Thread version information
clear            - clear the terminal screen
free             - Show the memory usage in the system.
ps               - List threads in the system.
help             - RT-Thread shell help.
pin              - pin [option]
list_alarm       - list alarm info
date             - get date and time or set (local timezone) [year month day hour min sec]

```

其中：

- hwtimer_sample 开启一个5s的周期性事件
- wdt_sample开启看门狗
- wdt_reset 停止看门狗，看门狗会在约1秒后复位

- alarm_sample RTC闹钟例子
  - 比如需要开启一个10S的闹钟，执行命令：
  ```console
    alarm_sample 10
  ```
  - 开启后会显示设置闹钟时间时的当前时间和设置的闹钟时间
  ```console
    current time: 2026-01-01 08:42:44
    alarm use local time
    set alarm time: 2026-01-01 08:42:54
  ```
  - 执行后会在10S后打印，可以看到打印的时间跟设置的闹钟时间一致
  ```console
    user alarm callback function.
    current time: 2026-01-01 08:42:54
  ```
- del_alarm_sample 删除全部闹钟

- list_alarm 查看闹钟列表
  - 会显示：
  ```console
        | hh:mm:ss | week | flag | en | timezone     |
        +----------+------+------+----+--------------+
        | 15:36:09 |   3  |   O  |  0 | UTC+08:00:00 |
        +----------+------+------+----+--------------+
  ```
- date 查看时间
  - 会显示：
  ```console
        local time: Wed Jun  4 15:38:16 2025
        timestamps: 1749022696
        timezone: UTC+08:00:00
  ```

- 如果需要使用UTC时间，可以menuconfig关闭 `RT-Thread Components -> Device Drivers -> Using RTC device drivers-> Using RTC alarm -> Using local time for the alarm calculation` 选项，然后重新编译。
