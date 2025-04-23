# 简介

本示例演示了基于英飞凌AIROC™ WiFi+Bluetooch® Combo系列的 WiFi基本测试

## 如何配置WiFi-Host-Driver

打开 `RT-Thread Settings`, 在右上角搜索`WiFi Host Driver(WHD)`, 在下拉框中选择所需要的`WiFi Host Driver(WHD) for RT-Thread`, 按作者给的介绍 __**[链接](https://github.com/Evlers/rt-thread_wifi-host-driver/blob/master/README_CN.md)**__ 来配置。

__测试过的WiFi模块列表__：

- CYWL6302 (WiFi芯片:CYW43012), 联系方式：新联鑫威（杭州）科技有限公司 (<xlx@xlxwlan.com>)
- CYWL6208 (WiFi芯片:CYW43438), 联系方式：新联鑫威（杭州）科技有限公司 (<xlx@xlxwlan.com>)

__注意事项__：

    1. 对于选项 `Select Chips`, 根据使用的模块，将下拉选项改为 `CYW43438`或 `CYW43012`
    2. 对于选项 `Select the pin name or Number` ,将下拉选项改为 `Name`
    3. 该驱动需要通WL_REG_ON 来控制模组的复位，对于选项 `Set the WiFi_REG ON pin` :
      * 场景一：板级SD卡电路支持额外的电源引脚
        - 该选项可以填`None`,模组的 `WL_REG_ON` 可以直接上拉
      * 场景二：板级SD卡电路不支持客户的电源引脚
        - 需要将该引脚连接到板子上的GPIO引脚上，并在该选项处填上GPIO引脚的值，如`PD24`(位于P2-38)
    4. 该驱动默认使用 `WL_HOST_WAKE` 引脚中断来触发WiFI的收发操作，对于选项 `Set the HOST_WAKE_IRQ pin`
      - 请和板子上相应的GPIO相连，并将GPIO引脚的名称填入该选项，如`PD25`(位于P2-40)
    5. 其他配置请保持默认值

## 支持的命令

```shell
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
ntp_sync         - Update time by NTP(Network Time Protocol): ntp_sync [host_name]
iperf            - the network bandwidth measurement tool
reset            - reset the board
```

## 完整的测试步骤

- 连接WiFi:

```shell
wifi scan
wifi join <ssid> <password>
```

当完成WiFi连接后，用户可以测试`ping`, `iperf`等命令
