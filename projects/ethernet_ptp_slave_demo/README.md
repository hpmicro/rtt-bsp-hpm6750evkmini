# lwIP PTP Slave V1

## 概述

本示例展示PTP Slave的功能

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
 / | \     5.0.1 build Jul 26 2023 09:20:43
 2006 - 2022 Copyright by RT-Thread team
lwIP-2.1.2 initialized!
[15] I/sal.skt: Socket Abstraction Layer initialize success.
(D 0.006532950) event POWER UP
(D 0.009440910) initClock
(D 0.011833750) state PTP_INITIALIZING
(D 0.013588990) manufacturerIdentity: PTPd;1.0.1
(D 0.015774790) netShutdown
(D 0.023853030) netInit
(D 0.025080450) initData
(D 0.026240430) initTimer
(D 0.027421070) initClock
(D 0.028616910) sync message interval: 4000
(D 0.030585670) clock identifier: DFLT
(D 0.032332170) 256*log2(clock variance): -4000
(D 0.034470150) clock stratum: 255
(D 0.036040910) clock preferred?: no
(D 0.037699890) bound interface name:
(D 0.039446270) communication technology: 1
(D 0.041409710) uuid: 0hx:0hx:0hx:0hx:0hx:0hx
(D 0.043461610) PTP subdomain name: _DFLT
(D 0.045338350) subdomain address: 224.0.1.129
(D 0.047433430) event port address: hx hx
(D 0.049330250) general port address: hx hx
(D 0.051296110) initClock
(D 0.052480050) state PTP_LISTENING
(D 0.054098030) initClock
(D 0.055277250) state PTP_SLAVE
msh />[2118] I/NO_TAG: PHY Status: Link up
[2122] I/NO_TAG: PHY Speed: 100Mbps
[2126] I/NO_TAG: PHY Duplex: full duplex

(D 2.802780510) addForeign: new record (0,1) 1 1 0hx:0hx:0hx:0hx:0hx:0hx
(D 2.806070330) event MASTER_CLOCK_CHANGED
(D 2.807996890) state PTP_UNCALIBRATED
(D 2.809746910) toState: Q = 0, R = 5
(D 4.803559730) updateOffset
(D 4.804896850) updateClock seconds
(D 6.081331250) setTime: resetting system clock to 6s 81331110ns
(D 6.084218510) initClock
(D 6.085406310) one-way delay:           0s          0ns
(D 6.087941810) offset from master:      -1s -274817140ns
(D 6.090516470) observed drift:          0
(D 8.079369490) updateOffset
(D 8.080712410) one-way delay:           0s          0ns
(D 8.083246140) offset from master:      0s     103520ns
(D 8.085776460) observed drift:          1725
(D 10.079879940) updateOffset
(D 10.081262300) one-way delay:           0s          0ns
(D 10.083849210) offset from master:      0s     -97545ns
(D 10.086424400) observed drift:          100
(D 12.080866000) updateOffset
(D 12.082244270) one-way delay:           0s          0ns
(D 12.084819130) offset from master:      0s    -164298ns
(D 12.087393750) observed drift:          -2638
(D 14.081810370) handleSync: Q = 0, R = 7
(D 14.083733900) updateOffset
(D 14.085106490) one-way delay:           0s          0ns
(D 14.087681920) offset from master:      0s    -177979ns
(D 14.090257250) observed drift:          -5604
(D 16.083137760) updateOffset
(D 16.084516780) one-way delay:           0s          0ns
(D 16.087094130) offset from master:      0s    -121674ns
(D 16.089670050) observed drift:          -7631
(D 18.083978180) updateOffset
(D 18.085359030) one-way delay:           0s          0ns
(D 18.087938040) offset from master:      0s    -119872ns
(D 18.090512600) observed drift:          -9628
(D 20.084961650) updateOffset
(D 20.086339420) one-way delay:           0s          0ns
(D 20.088915490) offset from master:      0s      -3436ns
(D 20.091491130) observed drift:          -9685
(D 20.093910900) event MASTER_CLOCK_SELECTED
(D 20.095921700) state PTP_SLAVE
(D 22.086235170) updateOffset
(D 22.087617360) one-way delay:           0s          0ns
(D 22.090194610) offset from master:      0s     -11668ns
(D 22.092768540) observed drift:          -9879
(D 24.088011820) updateOffset
(D 24.089389560) one-way delay:           0s          0ns
(D 24.091965620) offset from master:      0s     172641ns
(D 24.094539580) observed drift:          -7002
(D 26.089021210) updateOffset
(D 26.090403550) one-way delay:           0s          0ns
(D 26.092979720) offset from master:      0s      66990ns
(D 26.095554170) observed drift:          -5886
(D 28.090828770) handleSync: Q = 0, R = 7
(D 28.092855330) updateOffset
(D 28.094237900) one-way delay:           0s          0ns
(D 28.096816940) offset from master:      0s      49325ns
(D 28.099391060) observed drift:          -5064
(D 28.101558180) updateDelay
(D 30.092235300) updateOffset
(D 30.093614680) one-way delay:           0s     160300ns
(D 30.096192050) offset from master:      0s       2808ns

```
