## 概述
***
JPEG编解码示例工程展示了如何将JPG图片数据转换为RGB数据，以及将RGB数据转换为JPG图片数据。
在这个工程中，存储于USB或SD卡内的JPG图片,通过代码提取相关表格及像素数据，经过硬件JPEG模块
转换为RGB数据，并通过液晶屏显示出解码后的数据；解码后的数据，通过硬件JPEG模块进行编码，
转换为JPG数据，再通过解码转换为RGB数据，并通过液晶屏显示出来。

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
> start decoding
> decoding done
> start encoding and decoding
> complete encoding length 804 bytes
> encoding and decoding done

2. USB方式(存储示例图片example.jpg)：
当工程正确运行后，LCD屏正确显示存储设备中的图片信息，而串口终端会输出如下信息：
> Read picture data by usb-mode
> start decoding
> decoding done
> start encoding and decoding
> complete encoding length 804 bytes
> encoding and decoding done


