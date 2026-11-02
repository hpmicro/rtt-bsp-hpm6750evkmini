# lwIP PTP Slave V1

## 概述

本示例展示PTP Slave的功能

- Master与Slave通过PTP协议通讯，从而实现Slave端的时钟同步

## 硬件设置

- 使用USB Type-C线缆连接PC USB端口和PWR DEBUG端口（板载 FT2232，不支持外接 J-Link 烧录）
- 使用以太网线缆连接开发板RGMII或者RMII端口和另一块开发板的RGMII或RMII端口

## 编译设置

- 在双网口的开发板上，默认支持的是RGMII接口
- 在双网口的开发板上，仅支持一个网口，若需要使用另一个网口，可以通过如下两种方式之一：
    - RT-Thread Settings->硬件->芯片设备驱动->Enable Ethernet
    - menuconfig->Hardware Drivers Config->On-chip Peripheral Drivers->Enable Ethernet

## 运行示例

- 编译下载程序（OpenOCD + 板载 FT2232）
- 串口终端显示（Slave 与 Master 直连以太网，使能 `LWIP_PTP` 硬件时间戳后）

```console
 \ | /
- RT -     Thread Operating System
 / | \     5.2.2 build Jul 18 2026 13:51:46
 2006 - 2024 Copyright by RT-Thread team
lwIP-2.1.2 initialized!
[4] I/sal.skt: Socket Abstraction Layer initialize success.
(D 0.006485300) event POWER UP
(D 0.009334940) initClock
(D 0.011726300) state PTP_INITIALIZING
(D 0.015248740) manufacturerIdentity: PTPd;1.0.1
(D 0.019641780) netShutdown
(D 0.022191860) netInit
(D 0.024589900) initData
(D 0.026906500) initTimer
(D 0.029282100) initClock
(D 0.031667780) sync message interval: 1000
(D 0.035617300) clock identifier: DFLT
(D 0.039124340) 256*log2(clock variance): -4000
(D 0.043418780) clock stratum: 255
(D 0.046576340) clock preferred?: no
(D 0.049911700) bound interface name:
(D 0.053418420) communication technology: 1
(D 0.057362140) uuid: 98:2c:bc:b1:9f:28
(D 0.060963300) PTP subdomain name: _DFLT
(D 0.064735460) subdomain address: 224.0.1.129
(D 0.068946900) event port address: 3f 1
(D 0.072628300) general port address: 40 1
(D 0.076487220) initClock
(D 0.078852940) state PTP_LISTENING
(D 0.082097940) initClock
(D 0.084466100) state PTP_SLAVE
msh />
[2093] I/NO_TAG: ENET1
[2096] I/NO_TAG: PHY Status: Link up
[2100] I/NO_TAG: PHY Speed: 100Mbps
[2104] I/NO_TAG: PHY Duplex: full duplex

(D 2.631078580) addForeign: new record (0,1) 1 1 98:2c:bc:b1:9f:17
(D 2.637123700) event MASTER_CLOCK_CHANGED
(D 2.640988980) state PTP_UNCALIBRATED
(D 2.644496740) toState: Q = 0, R = 4
(D 87.137507140) updateOffset
(D 87.140260880) one-way delay:           0s       1113ns
(D 87.145443800) offset from master:      0s         99ns
(D 87.150618160) observed drift:          -38351
(D 88.141966080) updateOffset
(D 88.144711660) one-way delay:           0s       1113ns
(D 88.149886380) offset from master:      0s         73ns
(D 88.155055820) observed drift:          -38347
(D 89.138221220) updateOffset
(D 89.140966760) one-way delay:           0s       1113ns
(D 89.146148720) offset from master:      0s         60ns
(D 89.151320640) observed drift:          -38343
(D 90.142464880) updateOffset
(D 90.145208840) one-way delay:           0s       1113ns
(D 90.150384740) offset from master:      0s         94ns
(D 90.155561140) observed drift:          -38337
(D 91.138767800) updateOffset
(D 91.141518220) one-way delay:           0s       1114ns
(D 91.146689380) offset from master:      0s         90ns
(D 91.151860060) observed drift:          -38331
(D 92.143111000) updateOffset
(D 92.145870640) one-way delay:           0s       1114ns
(D 92.151048780) offset from master:      0s         88ns
(D 92.156222780) observed drift:          -38326
(D 93.139447060) updateOffset
(D 93.142198980) one-way delay:           0s       1114ns
(D 93.147376620) offset from master:      0s         77ns
(D 93.152547320) observed drift:          -38321
(D 94.143741560) updateOffset
(D 94.146493420) one-way delay:           0s       1114ns
(D 94.151667180) offset from master:      0s         51ns
(D 94.156837020) observed drift:          -38318
(D 95.140068740) updateOffset
(D 95.142834780) one-way delay:           0s       1113ns
(D 95.148010500) offset from master:      0s         59ns
(D 95.153180960) observed drift:          -38315
(D 96.144453200) updateOffset
(D 96.147207860) one-way delay:           0s       1113ns
(D 96.152381140) offset from master:      0s         53ns
(D 96.157551660) observed drift:          -38312
(D 97.140796380) updateOffset
(D 97.143553620) one-way delay:           0s       1114ns
(D 97.148729000) offset from master:      0s         70ns
```

同步稳定后，`offset from master` 可收敛并维持在约 ±100ns 以内（上例连续多次采样均在 100ns 内）。
