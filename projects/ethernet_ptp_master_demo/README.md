# lwIP PTP Master V1

## 概述

本示例展示PTP Master的功能

- Master与Slave通过PTP协议通讯，从而实现Slave端的时钟同步

## 硬件设置

* 使用USB Type-C线缆连接PC USB端口和PWR DEBUG端口
* 使用以太网线缆连接开发板RGMII或者RMII端口和另一个块开发板的RGMII或RMII端口

## 运行示例

* 编译下载程序
* 串口终端显示

```console
 \ | /
- RT -     Thread Operating System
 / | \     5.0.1 build Jul 26 2023 09:27:58
 2006 - 2022 Copyright by RT-Thread team
lwIP-2.1.2 initialized!
[4] I/sal.skt: Socket Abstraction Layer initialize success.
(D 0.006532020) event POWER UP
(D 0.009440540) initClock
(D 0.011830510) state PTP_INITIALIZING
(D 0.013590150) manufacturerIdentity: PTPd;1.0.1
(D 0.015780410) netShutdown
(D 0.023862530) netInit
(D 0.025095790) initData
(D 0.026259490) initTimer
(D 0.027440550) initClock
(D 0.028637170) sync message interval: 4000
(D 0.030608510) clock identifier: DFLT
(D 0.032357490) 256*log2(clock variance): -4000
(D 0.034497590) clock stratum: 4
(D 0.035983470) clock preferred?: no
(D 0.037644410) bound interface name:
(D 0.039391930) communication technology: 1
(D 0.041357890) uuid: 0hx:0hx:0hx:0hx:0hx:0hx
(D 0.043414290) PTP subdomain name: _DFLT
(D 0.045291930) subdomain address: 224.0.1.129
(D 0.047390050) event port address: hx hx
(D 0.049269530) general port address: hx hx
(D 0.051237990) initClock
(D 0.052425630) state PTP_LISTENING
(D 0.054047970) initClock
(D 0.055234110) state PTP_MASTER

```
