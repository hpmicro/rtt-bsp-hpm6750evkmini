## 概述
***
libjpeg_turbo解码示例工程展示了如何将JPG图片数据通过libjpeg_turbo库转换为RGB数据。
在这个工程中，存储于USB或SD卡内的JPG图片,通过代码库将JPEG数据转换为RGB565数据，
并通过液晶屏显示出解码后的数据。

## 硬件设置
***
1. USB盘连接到开发板"USB0"，或SD内存卡插入到开发板"sd card"，存储介质中存放JPG图片,示例图片可使用jpeg路径下的example.jpg
2. LCD屏连接到开发板"LCD1"

## 工程配置
***
1. 文件CMakeLists.txt中配置set(CONFIG_SDFATFS_MODE 1)，则默认从SD卡中读取JPG图片；配置
set(CONFIG_TINYUSBHOST_MODE 1)，则默认从USB中读取JPG图片

## 运行现象
***
1. SD卡方式(存储示例图片example.jpg)：
当工程正确运行后，LCD屏正确显示存储设备中的图片信息，而串口终端会输出如下信息：
> Read picture data by SD card
> Libjpeg-turbo decode completed

2. USB方式(存储示例图片example.jpg)：
当工程正确运行后，LCD屏正确显示存储设备中的图片信息，而串口终端会输出如下信息：
> Read picture data by usb-mode
> Libjpeg-turbo decode completed

