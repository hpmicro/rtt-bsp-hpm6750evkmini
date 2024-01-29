# USB MSC U 盘

## 概述

本示例工程展示U盘访问操作

- MCU读取并列出U盘根目录文件及目录，并打印测试文件写入结果

## 硬件设置

- 使用USB Type-C线缆连接PC USB端口和PWR DEBUG端口
- 使用USB Type-C转USB-A线缆连接U 盘和开发板USB0端口或者USB1端口

## 运行示例

当工程正确运行后

* 编译下载程序
* 串口终端显示

```console
 \ | /
- RT -     Thread Operating System
 / | \     4.1.0 build Jul 26 2023 14:05:09
 2006 - 2022 Copyright by RT-Thread team
msh />
A MassStorage device is mounted.
Kingston DT 101 G2        rev PMAP
Disk Size: 7632 MB
Block Count = 15630336, Block Size: 512
FatFs mount succeeded!
The USBHost.txt is open.
Directory /:
System Volume Inform<DIR>
USBHost.txt         24
Write the USBHost.txt file successfully!

```

## 注意
- 由于当前使用的tinyusb 协议栈版本的限制，该工程不支持通过USB-HUB连接U盘
