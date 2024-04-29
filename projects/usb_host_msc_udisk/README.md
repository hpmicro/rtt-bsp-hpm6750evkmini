# USB MSC U 盘

## 概述

本示例工程展示rtthread DFS文件系统挂载U盘进行访问操作

- DFS文件系统挂载U盘成功后，可以使用文件操作命令操作U盘

## 硬件设置

- 使用USB Type-C线缆连接PC USB端口和PWR DEBUG端口
- 使用USB Type-C转USB-A线缆连接U 盘和开发板USB0端口或者USB1端口

## 运行示例

当工程正确运行后

* 编译下载程序, 并插入U盘
* 串口终端显示U盘挂载成功

```console
 \ | /
- RT -     Thread Operating System
 / | \     5.0.2 build Mar 29 2024 13:42:52
 2006 - 2022 Copyright by RT-Thread team
msh />[I/usbh_hub] New high-speed device on Bus 0, Hub 1, Port 1 connected
[I/usbh_core] New device found,idVendor:090c,idProduct:1000,bcdDevice:1100
[I/usbh_core] The device has 1 interfaces
[I/usbh_core] Enumeration success, start loading class driver
[I/usbh_core] Loading msc class driver
[I/usbh_msc] Get max LUN:1
[I/usbh_msc] Ep=81 Attr=02 Mps=512 Interval=255 Mult=00
[I/usbh_msc] Ep=02 Attr=02 Mps=512 Interval=255 Mult=00
[I/usbh_msc] Capacity info:
[I/usbh_msc] Block num:60416000,block size:512
[I/usbh_msc] Register MSC Class:/dev/sda
found part[0], begin: 4194304, size: 28.824GB
Found partition 0: type = 12, offet=0x2000, size=0x399c000
udisk: /sda mount successfully

```

## 支持的命令

```console
RT-Thread shell commands:
reset            - reset the board
list             - list objects
version          - show RT-Thread version information
clear            - clear the terminal screen
free             - Show the memory usage in the system.
ps               - List threads in the system.
help             - RT-Thread shell help.
tail             - print the last N - lines data of the given file
echo             - echo string to file
df               - disk free
umount           - Unmount the mountpoint
mount            - mount <device> <mountpoint> <fstype>
mkfs             - format disk with file system
mkdir            - Create the DIRECTORY.
pwd              - Print the name of the current working directory.
cd               - Change the shell working directory.
rm               - Remove(unlink) the FILE(s).
cat              - Concatenate FILE(s)
mv               - Rename SOURCE to DEST.
cp               - Copy SOURCE to DEST.
ls               - List information about the FILEs.
pin              - pin [option]
date             - get date and time or set (local timezone) [year month day hour min sec]

```

* 使用ls命令查看显示当前目录下的文件和文件夹

```console
msh />ls
Directory /:
System Volume Inform<DIR>
test                <DIR>
hpmicro.txt         7

```

* 使用echo命令将指定内容写入指定文件，当文件存在时，就写入该文件，当文件不存在时就创建新的文件并且写入
```console

msh />echo "hpmicro cherryusb" usb.txt

```

* 使用cat展示文件内容

```console

msh />cat usb.txt
hpmicro cherryusb
msh />
msh />

```

