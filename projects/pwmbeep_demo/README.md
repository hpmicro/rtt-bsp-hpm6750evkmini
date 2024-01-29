# 简介

本例程演示基于RT-Thread PWM 驱动框架的PWM驱动蜂鸣器播放音乐

## 操作步骤

- 板子下载例程并运行
- 若例程被正常下载执行，则会打印如下信息

```console
 \ | /
- RT -     Thread Operating System
 / | \     5.0.1 build Jul 27 2023 19:21:29
 2006 - 2022 Copyright by RT-Thread team
Type play_music to play music
```

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
play_music       - play music via pwm-driven beeper
```