# 简介

本示例演示了基于RT-Thread 串口V2驱动框架的串口的的数据发送和接收。

## 示例展示的功能

- 串口的发送和接收，串口接收到的PC串口助手的数据会返回给PC串口助手，数据并显示在msh终端。

## 硬件设置
* 使用USB转TTL模块连接到开发板对应的串口引脚

| 功能       | 位置   |  引脚  |
| ----------| ------ | ------ |
| UART13.TXD | P1[8] | PZ[09] |
| UART13.RXD | P1[10] | PZ[08] |

### RT-Thread命令

```console
RT-Thread shell commands:
uart_dma_sample  - uart device dma sample
reset            - reset the board
clear            - clear the terminal screen
version          - show RT-Thread version information
list             - list objects
help             - RT-Thread shell help.
ps               - List threads in the system.
free             - Show the memory usage in the system.
pin              - pin [option]
date             - get date and time or set (local timezone) [year month day hour min sec]
```
测试时请使用 `uart_dma_sample` 命令

## 运行现象
```console
 \ | /
- RT -     Thread Operating System
 / | \     5.0.1 build Jul 28 2023 10:58:35
 2006 - 2022 Copyright by RT-Thread team
msh >
msh >
msh >
msh >uart_dma_sample
msh >
msh >hello hpmicro~~~
hello hpmicro123456789
```

## 注意

- 该例程中的串口波特率使用rtthread默认115200
- 对于RT_DEVICE_FLAG_RX_NON_BLOCKING，使用DMA接收，但只能定长接收，定长长度取决于BSP_UART13_RX_BUFSIZE，需要开启BSP_UART13_RX_USING_DMA
- 对于RT_DEVICE_FLAG_RX_BLOCKING，使用硬件FIFO接收并使用超时机制，可以不定长接收，最大接收长度取决于BSP_UART13_RX_BUFSIZE，需要关闭BSP_UART13_RX_USING_DMA



