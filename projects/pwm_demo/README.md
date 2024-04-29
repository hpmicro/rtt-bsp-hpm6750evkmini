# 简介

本例程演示基于RT-Thread PWM 驱动框架的PWM波形输出demo

## 操作步骤

- 板子下载例程并运行
- 若例程被正常下载执行，示波器可以观测到`P1.19`引脚输出0.5ms的周期的波形，占空比从0到100%进行变化

## 支持的命令

```console
RT-Thread shell commands:
clear            - clear the terminal screen
version          - show RT-Thread version information
list             - list objects
help             - RT-Thread shell help.
ps               - List threads in the system.
free             - Show the memory usage in the system.
date             - get date and time or set (local timezone) [year month day hour min sec]
pin              - pin [option]
pwm              - pwm [option]
reset            - reset the board
pwm_sample       - pwm output
```

测试时请使用 `pwm_sample` 命令