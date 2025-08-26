# 网络连通性及吞吐性能测试

## 概述

本示例演示了基于RT-Thread 网络连通性测试和吞吐性能测试

## 硬件设置

* 使用USB Type-C线缆连接PC USB端口和PWR DEBUG端口
* 使用以太网线缆连接PC以太网端口和开发板RGMII或RMII端口

## 软件设置

* 使用flash_release编译运行，可以获得更好的网络性能

## 运行示例

* 编译下载程序
* 串口终端显示

```console
 \ | /
- RT -     Thread Operating System
 / | \     5.0.2 build Apr 19 2025 10:18:07
 2006 - 2022 Copyright by RT-Thread team
lwIP-2.1.2 initialized!
[27] I/sal.skt: Socket Abstraction Layer initialize success.
msh />[4067] I/NO_TAG: ENET0
[4070] I/NO_TAG: PHY Status: Link up
[4074] I/NO_TAG: PHY Speed: 1000Mbps
[4078] I/NO_TAG: PHY Duplex: full duplex
```

## 功能验证

### 1. IP分配查询及DHCP状态确认

```console
msh />ifconfig
network interface device: ET (Default)
MTU: 1500
MAC: 98 2c bc b1 9f 17
FLAGS: UP LINK_UP INTERNET_DOWN DHCP_ENABLE ETHARP BROADCAST
ip address: 192.168.100.6
gw address: 192.168.100.1
net mask  : 255.255.255.0
dns server #0: 192.168.100.1
dns server #1: 0.0.0.0

```

**注： 若DHCP开启，则DHCP状态为“DHCP_ENABLE”，需要将网口连接至路由器或具有DHCP服务的PC  **   

### 2. PING测试

  （1）Windows系统中，打开cmd, 运行ping

```console
C:\Users>ping 192.168.100.6

正在 Ping 192.168.100.6 具有 32 字节的数据:
来自 192.168.100.6 的回复: 字节=32 时间<1ms TTL=255
来自 192.168.100.6 的回复: 字节=32 时间<1ms TTL=255
来自 192.168.100.6 的回复: 字节=32 时间<1ms TTL=255
来自 192.168.100.6 的回复: 字节=32 时间<1ms TTL=255

192.168.100.6 的 Ping 统计信息:
    数据包: 已发送 = 4，已接收 = 4，丢失 = 0 (0% 丢失)，
往返行程的估计时间(以毫秒为单位):
    最短 = 0ms，最长 = 0ms，平均 = 0ms
```

  （2）开发板Ping PC

```console
msh />ping 192.168.100.5
ping: not found specified netif, using default netdev ET.
60 bytes from 192.168.100.5 icmp_seq=0 ttl=64 time=0 ms
60 bytes from 192.168.100.5 icmp_seq=1 ttl=64 time=0 ms
60 bytes from 192.168.100.5 icmp_seq=2 ttl=64 time=0 ms
60 bytes from 192.168.100.5 icmp_seq=3 ttl=64 time=0 ms

```

### 3. **iperf测试**

- **TCP服务端模式**

  - MCU端输入命令

    ```console
    msh /> iperf -s
    ```

  -  PC端输入命令

    ```console
    C:\Users>iperf -c 192.168.100.6 -i 1
    ```

  - 观察PC端结果

    ```console
    ------------------------------------------------------------
    Client connecting to 192.168.100.6, TCP port 5001
    TCP window size: 64.0 KByte (default)
    ------------------------------------------------------------
    [360] local 192.168.100.5 port 60831 connected with 192.168.100.6 port 5001
    [ ID] Interval       Transfer     Bandwidth
    [360]  0.0- 1.0 sec  11.3 MBytes  94.4 Mbits/sec
    [360]  1.0- 2.0 sec  11.1 MBytes  93.3 Mbits/sec
    [360]  2.0- 3.0 sec  11.2 MBytes  94.1 Mbits/sec
    [360]  3.0- 4.0 sec  11.1 MBytes  92.9 Mbits/sec
    [360]  4.0- 5.0 sec  11.2 MBytes  94.2 Mbits/sec
    [360]  5.0- 6.0 sec  11.2 MBytes  94.0 Mbits/sec
    [360]  6.0- 7.0 sec  11.2 MBytes  93.9 Mbits/sec
    [360]  7.0- 8.0 sec  11.1 MBytes  92.8 Mbits/sec
    [360]  8.0- 9.0 sec  11.2 MBytes  94.1 Mbits/sec
    [360]  9.0-10.0 sec  11.3 MBytes  94.4 Mbits/sec
    [360]  0.0-10.0 sec   112 MBytes  93.7 Mbits/sec
    ```

  - 观察MCU端结果

    ```console
    msh />[85630] I/iperf: new client connected from (192.168.100.5, 60831)
    [90637] I/iperf: iperfd01: 93.8310 Mbps!
    [95632] W/iperf: client disconnected (192.168.100.5, 60831)
    ```

    

- **TCP客户端模式**

  - PC端输入命令

    ```console
    C:\Users>iperf -s -i 1
    ```

  - MCU端输入命令

    ```console
    msh />iperf -c 192.168.100.5
    ```

  - 观察PC端结果

    ```console
    ------------------------------------------------------------
    Server listening on TCP port 5001
    TCP window size: 64.0 KByte (default)
    ------------------------------------------------------------
    [412] local 192.168.100.5 port 5001 connected with 192.168.100.6 port 52432
    [ ID] Interval       Transfer     Bandwidth
    [412]  0.0- 1.0 sec  10.9 MBytes  91.8 Mbits/sec
    [412]  1.0- 2.0 sec  10.9 MBytes  91.1 Mbits/sec
    [412]  2.0- 3.0 sec  10.9 MBytes  91.7 Mbits/sec
    [412]  3.0- 4.0 sec  10.9 MBytes  91.8 Mbits/sec
    [412]  4.0- 5.0 sec  10.8 MBytes  90.9 Mbits/sec
    [412]  5.0- 6.0 sec  10.9 MBytes  91.5 Mbits/sec
    [412]  6.0- 7.0 sec  10.2 MBytes  85.6 Mbits/sec
    [412]  7.0- 8.0 sec  10.8 MBytes  91.0 Mbits/sec
    [412]  8.0- 9.0 sec  11.0 MBytes  91.9 Mbits/sec
    [412]  9.0-10.0 sec  10.9 MBytes  91.3 Mbits/sec
    [412] 10.0-11.0 sec  10.9 MBytes  91.4 Mbits/sec
    [412] 11.0-12.0 sec  11.0 MBytes  91.9 Mbits/sec
    [412] 12.0-13.0 sec  10.9 MBytes  91.8 Mbits/sec
    [412] 13.0-14.0 sec  10.9 MBytes  91.7 Mbits/sec
    [412] 14.0-15.0 sec  10.8 MBytes  90.3 Mbits/sec
    [412] 15.0-16.0 sec  10.9 MBytes  91.5 Mbits/sec
    [412] 16.0-17.0 sec  10.9 MBytes  91.2 Mbits/sec
    [412] 17.0-18.0 sec  10.9 MBytes  91.3 Mbits/sec
    [412] 18.0-19.0 sec  10.9 MBytes  91.7 Mbits/sec
    [412] 19.0-20.0 sec  10.8 MBytes  90.9 Mbits/sec
    ```

  - 观察MCU端结果

    ```console
    msh />[156267] I/iperf: Connect to iperf server successful!
    [161272] I/iperf: iperfc01: 91.4810 Mbps!
    [166272] I/iperf: iperfc01: 90.2620 Mbps!
    [171272] I/iperf: iperfc01: 91.4350 Mbps!
    [176272] I/iperf: iperfc01: 91.3240 Mbps!
    ```

- **UDP服务端模式**

  - MCU端输入命令

    ```console
    msh />iperf -u -s
    ```

  - PC端输入命令

    ```console
    C:\Users>iperf -u -c 192.168.100.6 -i 1 -b 100M -t 20
    ```

  - 观察PC端结果

    ```console
    ------------------------------------------------------------
    Client connecting to 192.168.100.6, UDP port 5001
    Sending 1470 byte datagrams
    UDP buffer size: 64.0 KByte (default)
    ------------------------------------------------------------
    [360] local 192.168.100.5 port 56315 connected with 192.168.100.6 port 5001
    [ ID] Interval       Transfer     Bandwidth
    [360]  0.0- 1.0 sec  11.4 MBytes  95.4 Mbits/sec
    [360]  1.0- 2.0 sec  11.2 MBytes  93.8 Mbits/sec
    [360]  2.0- 3.0 sec  11.4 MBytes  95.5 Mbits/sec
    [360]  3.0- 4.0 sec  11.2 MBytes  94.1 Mbits/sec
    [360]  4.0- 5.0 sec  11.3 MBytes  95.0 Mbits/sec
    [360]  5.0- 6.0 sec  11.4 MBytes  95.4 Mbits/sec
    [360]  6.0- 7.0 sec  11.2 MBytes  93.5 Mbits/sec
    [360]  7.0- 8.0 sec  11.4 MBytes  95.3 Mbits/sec
    [360]  8.0- 9.0 sec  11.2 MBytes  94.0 Mbits/sec
    [360]  9.0-10.0 sec  11.4 MBytes  95.3 Mbits/sec
    [360] 10.0-11.0 sec  11.2 MBytes  94.2 Mbits/sec
    [360] 11.0-12.0 sec  11.2 MBytes  93.8 Mbits/sec
    [360] 12.0-13.0 sec  11.2 MBytes  94.2 Mbits/sec
    [360] 13.0-14.0 sec  11.4 MBytes  95.4 Mbits/sec
    [360] 14.0-15.0 sec  11.4 MBytes  95.2 Mbits/sec
    [360] 15.0-16.0 sec  11.3 MBytes  95.1 Mbits/sec
    [360] 16.0-17.0 sec  10.9 MBytes  91.3 Mbits/sec
    [360] 17.0-18.0 sec  11.2 MBytes  94.2 Mbits/sec
    [360] 18.0-19.0 sec  11.3 MBytes  94.9 Mbits/sec
    [360] 19.0-20.0 sec  11.2 MBytes  94.2 Mbits/sec
    [ ID] Interval       Transfer     Bandwidth
    [360]  0.0-20.0 sec   225 MBytes  94.5 Mbits/sec
    [360] WARNING: did not receive ack of last datagram after 10 tries.
    [360] Sent 160686 datagrams
    ```

  - 观察MCU端结果

    ```console
    msh />[40878] I/iperf: iperfd01: 85.4620 Mbps! lost:0 total:36335
    
    [45884] I/iperf: iperfd01: 94.7400 Mbps! lost:32 total:40313
    
    [50890] I/iperf: iperfd01: 94.5990 Mbps! lost:33 total:40254
    
    [55896] I/iperf: iperfd01: 94.0470 Mbps! lost:32 total:40018
    
    [62679] I/iperf: iperfd01: 6.4950 Mbps! lost:-321340 total:-317606
    ```

    

- UDP客户端模式

  - PC端输入命令

    ```console
    C:\Users>iperf -u -s -i 1
    ```

  - MCU端输入命令

    ```console
    msh />iperf -u -c 192.168.100.5
    ```

  - 观察MCU端结果

    ```console
    ------------------------------------------------------------
    Server listening on UDP port 5001
    Receiving 1470 byte datagrams
    UDP buffer size: 64.0 KByte (default)
    ------------------------------------------------------------
    [356] local 192.168.100.5 port 5001 connected with 192.168.100.6 port 62510
    [ ID] Interval       Transfer     Bandwidth       Jitter   Lost/Total Datagrams
    [356]  0.0- 1.0 sec  11.3 MBytes  95.0 Mbits/sec  0.304 ms 1431/ 9513 (15%)
    [356]  1.0- 2.0 sec  11.3 MBytes  94.9 Mbits/sec  0.232 ms    0/ 8070 (0%)
    [356]  2.0- 3.0 sec  11.3 MBytes  94.9 Mbits/sec  0.048 ms    0/ 8066 (0%)
    [356]  3.0- 4.0 sec  11.3 MBytes  94.9 Mbits/sec  0.210 ms    0/ 8067 (0%)
    [356]  4.0- 5.0 sec  11.3 MBytes  94.9 Mbits/sec  0.243 ms    0/ 8067 (0%)
    [356]  5.0- 6.0 sec  11.3 MBytes  94.9 Mbits/sec  0.048 ms    0/ 8068 (0%)
    [356]  6.0- 7.0 sec  11.3 MBytes  94.9 Mbits/sec  0.214 ms    0/ 8068 (0%)
    [356]  7.0- 8.0 sec  11.3 MBytes  94.9 Mbits/sec  0.148 ms    0/ 8066 (0%)
    [356]  8.0- 9.0 sec  11.3 MBytes  94.9 Mbits/sec  0.176 ms    0/ 8066 (0%)
    [356]  9.0-10.0 sec  11.3 MBytes  94.9 Mbits/sec  0.223 ms    0/ 8069 (0%)
    [356] 10.0-11.0 sec  11.3 MBytes  94.9 Mbits/sec  0.194 ms    0/ 8068 (0%)
    [356] 11.0-12.0 sec  11.3 MBytes  94.9 Mbits/sec  0.234 ms    0/ 8068 (0%)
    [356] 12.0-13.0 sec  11.3 MBytes  94.9 Mbits/sec  0.008 ms    0/ 8066 (0%)
    [356] 13.0-14.0 sec  11.3 MBytes  94.8 Mbits/sec  0.234 ms    0/ 8064 (0%)
    [356] 14.0-15.0 sec  11.3 MBytes  94.9 Mbits/sec  0.213 ms    0/ 8071 (0%)
    [356] 15.0-16.0 sec  11.3 MBytes  94.8 Mbits/sec  0.185 ms    0/ 8064 (0%)
    [356] 16.0-17.0 sec  11.3 MBytes  94.9 Mbits/sec  0.209 ms    0/ 8066 (0%)
    [356] 17.0-18.0 sec  11.3 MBytes  94.9 Mbits/sec  0.215 ms    0/ 8068 (0%)
    [356] 18.0-19.0 sec  11.3 MBytes  94.8 Mbits/sec  0.197 ms    0/ 8065 (0%)
    [356] 19.0-20.0 sec  11.3 MBytes  94.8 Mbits/sec  0.250 ms    0/ 8065 (0%)
    ```

    

  - 观察MCU端结果

    ```console
    [66131] I/iperf: iperf udp mode run...
    ```

    **注：此模式下，MCU端无统计信息输出，且无退出机制，需要按reset键重启MCU。**

  

  

