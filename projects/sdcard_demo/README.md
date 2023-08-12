# 简介

本例程演示基于RT-Thread SDIO 驱动框架的 SD/MMC 卡挂载

## 操作步骤

- 提前插好 SD 卡或者 eMMC转TF卡：
- 板子下载例程并运行
- 若卡被成功识别，则例程会打印如下所示的容量等信息

```console
 \ | /
- RT -     Thread Operating System
 / | \     5.0.1 build May 15 2023 17:44:01
 2006 - 2022 Copyright by RT-Thread team
msh />found part[0], begin: 32256, size: 28.907GB

msh />sd0 mounted to /

```

## 支持的命令

```console
RT-Thread shell commands:
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
date             - get date and time or set (local timezone) [year month day hour min sec]
pin              - pin [option]
reset            - reset the board
```

其中，如下命令可做文件系统相关的测试：

- `ls`
- `cd`
- `cat`
- `pwd`
- `mkdir`
- `mkfs`
- `tail`

## 注意事项

- SD/eMMC卡必须被格式化FAT32格式
