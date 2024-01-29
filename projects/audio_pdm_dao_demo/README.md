# 简介

本例程演示基于RT-Thread音频驱动框架使用PDM模块录音和使用DAO模块播放音频。

## 硬件设置

- 安装SD卡或者eMMC转TF卡至开发板SD卡卡槽(U12)
- 连接喇叭至开发板DAO接口(J2)
- PDM模块的麦克风器件为U15与U16，录音时请对此发声
- 下载例程并运行，若卡被成功识别，则例程会打印如下所示的容量等信息

```console
 \ | /
- RT -     Thread Operating System
 / | \     5.0.1 build May 15 2023 17:44:01
 2006 - 2022 Copyright by RT-Thread team
msh />found part[0], begin: 32256, size: 28.907GB

msh />sd0 mounted to /

```

## 注意事项

- SD/eMMC卡必须被格式化FAT32格式


## 支持的命令

```console
RT-Thread shell commands:
pdm_recordwav    - pdm record sound to wav file
dao_playwav      - dao play wav file
reset            - reset the board
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
pin              - pin [option]
date             - get date and time or set (local timezone) [year month day hour min sec]
```

## 运行现象
使用`pdm_recordwav /sample.wav`命令, 对着开发板mic发声，会录制一段音频以wav格式保存在SD卡中
```console
msh />pdm_recordwav /test.wav
record 10s audio data to wav file:
samplerate: 16000
samplebits: 32
channel number: 1
```
使用`dao_playwav /sample.wav`命令, 播放sd卡中的wav，通过喇叭可听到声音
```console
msh />dao_playwav /test.wav
wav information:
time: 10s
samplerate: 16000
samplebits: 32
channel: 1
```

