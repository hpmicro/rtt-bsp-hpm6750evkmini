# 简介

本例程演示wifi网页摄像头功能

## 示例展示的功能

本例程使用OV5640摄像头并内置简易网页服务器，PC浏览器通过访问网页服务器获取jpeg图像流进行显示

## 支持的命令

```console
RT-Thread shell commands:
ifconfig         - list the information of all network interfaces
ping             - ping network host
dns              - list and set the information of dns
netstat          - list the information of TCP / IP
clear            - clear the terminal screen
version          - show RT-Thread version information
list             - list objects
help             - RT-Thread shell help.
ps               - List threads in the system.
free             - Show the memory usage in the system.
ls               - List information about the FILEs.
cp               - Copy SOURCE to DEST.
mv               - Rename SOURCE to DEST.
cat              - Concatenate FILE(s)
rm               - Remove(unlink) the FILE(s).
cd               - Change the shell working directory.
pwd              - Print the name of the current working directory.
mkdir            - Create the DIRECTORY.
mkfs             - format disk with file system
mount            - mount <device> <mountpoint> <fstype>
umount           - Unmount the mountpoint
df               - disk free
echo             - echo string to file
tail             - print the last N - lines data of the given file
wifi             - wifi command
date             - get date and time or set (local timezone) [year month day hour min sec]
pin              - pin [option]
rw007_ble        - ble command.
tcpdump          - test optparse_short cmd.
ntp_sync         - Update time by NTP(Network Time Protocol): ntp_sync [host_name]
iperf            - the network bandwidth measurement tool
reset            - reset the board
rw007_update     - rw007_update
```

## 完整的测试步骤

- 等待lwip和rw007、网页服务器相关初始化成功，若成功会出现以下Log

```console
 \ | /
- RT -     Thread Operating System
 / | \     5.0.1 build Dec 14 2023 10:54:48
 2006 - 2022 Copyright by RT-Thread team
lwIP-2.1.2 initialized!
msh />[E/[RW007]] The wifi Stage 1 status 0 0 0 1

rw007  sn: [rw00700000000fc584a2c4817]
rw007 ver: [RW007_2.1.0-a7a0d089-57]

I2C bus is ready
http_mjpeg_server...

```

- wifi 联网

```console
wifi join <SSID> <PASSWORD>
```

- 等待wifi连接成功后，网页服务器开启，若成功会出现以下log，若长时间无出现请检查输入的wifi账号和密码是否正确

```console
web IP address has find....
WebServer Waiting for client on port 80...
```

- 完成后，查询当前节点的网络信息，记住本IP地址

```console
msh />ifconfig
network interface device: w0 (Default)
MTU: 1500
MAC: fc 58 4a 2c 48 17
FLAGS: UP LINK_UP INTERNET_UP DHCP_ENABLE ETHARP BROADCAST IGMP
ip address: 192.168.0.101
gw address: 192.168.0.1
net mask  : 255.255.255.0
dns server #0: 192.168.1.1
dns server #1: 192.168.0.1
```

- 若以上已就绪，在PC浏览器上，输入本IP:80，比如本机: 192.168.0.101:80， 就可以在网页上看到图像流,同时会有相关Log打印

```console
msh />
StreamConnected=4,192.168.0.107 , 58737

uri=GET / HTTP/1.1

bytes_received <= 0,lwip close...

StreamConnected=4,192.168.0.107 , 58738

uri=GET /?hpm6750evkmini=mjpeg HTTP/1.1

 Now Ok!!

```
