# 简介

本示例演示了基于RT-Thread CAN驱动框架的CAN的数据发送和接收。

## 示例展示的功能

- CAN标准帧发送和接收
- CAN扩展帧发送和接收
- CANFD标准帧发送和接收
- CANFD扩展帧发送和接收

### RT-Thread命令

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
canstat          - stat can device status
reset            - reset the board
can_sample       - can device sample
```
测试时请使用 `can_sample` 命令


## 注意

- 该例程中的CAN工作在loopback模式


