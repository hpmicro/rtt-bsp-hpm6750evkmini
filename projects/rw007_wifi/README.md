# 简介

本例程演示基于RT-Thread各大网络组件的网络通信。

## 支持的功能

本例程提供wifi联网和常见的网络命令。

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

其中，如下命令与网络相关：

- wifi 命令用于WIFI相关的操作
- ifconfig 显示网络相关的信息
- dns
- ping
- iperf
- netstat
- ntp_sync

## 完整的测试步骤

- wifi 联网

```console
wifi join <SSID> <PASSWORD>
```

- 查询当前节点的网络信息

```console
ifconfig
```

- ping 其他网络节点

```console
ping www.baidu.com
```

- 测试网络性能(iperf)

- 详见[链接](https://github.com/RT-Thread-packages/netutils/blob/master/iperf/README.md)
