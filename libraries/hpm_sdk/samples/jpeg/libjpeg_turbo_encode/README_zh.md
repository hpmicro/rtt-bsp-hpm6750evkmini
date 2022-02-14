## 概述
***
libjpeg_turbo编码示例工程展示了如何将摄像头采集的RGB565数据通过libjpeg_turbo库转换为JPG数据并保存在存储介质中。在这个工程中，通过摄像头获取RGB565数据，通过代码库将RGB565数据转换为JPEG数据，并将JPG图片存储于USB或SD卡内。

## 硬件设置
***
1. USB盘连接到开发板"USB0"，或SD内存卡插入到开发板"sd card"
2. CAM摄像头连接到开发板"CAM"

## 工程配置
***
1. 文件CMakeLists.txt中配置set(CONFIG_SDFATFS_MODE 1)，则默认将JPG图片存储在SD卡内；配置
set(CONFIG_TINYUSBHOST_MODE 1)，则默认将JPG图片存储在USB内

## 运行现象
***
1. SD卡方式：
当工程正确运行后，摄像头捕获的图片，存储在SD卡中，命名为Camera.jpg，而串口终端会输出如下信息：
> storage picture data by SD card
> File Name: Camera.jpg
> Libjpeg-turbo encode completed

2. USB方式：
当工程正确运行后，摄像头捕获的图片，存储在USB中，命名为Camera.jpg，而串口终端会输出如下信息：
> storage picture data by tinyusb mode
> File Name: Camera.jpg
> Libjpeg-turbo encode completed


