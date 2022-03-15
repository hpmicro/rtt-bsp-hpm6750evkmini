# JPEG编解码器
## 概述
***
**jpeg_hw**编解码示例工程展示了如何将JPG图片数据转换为RGB数据，以及将RGB数据转换为YUV数据。
- 存储于**USB**或**SD卡**内的JPG图片,通过本代码工程，提取**huffmin**、**huffbase**、**huffsymb**、**huffenc**表格及像素数据，经过硬件JPEG模块，转换为RGB数据，并通过**液晶屏**显示图片
- RGB数据，通过硬件JPEG模块进行编码，转换为YUV数据，再通过解码转换为RGB数据，并通过**液晶屏**显示图片。

## 硬件设置
***
-  **USB盘**连接到开发板``USB0``，或**SD内存卡**插入到开发板``sd card``，存储介质中存放JPG图片,示例图片可使用jpeg路径下的**example.jpg**
-  **LCD屏**连接到开发板``LCD1``

## 工程配置
***
-  文件[CMakeLists.txt](./CmakeLists.txt)中配置``set(CONFIG_SDFATFS_MODE 1)``，则默认从**SD卡**中读取JPG图片；配置
``set(CONFIG_TINYUSBHOST_MODE 1)``，则默认从**USB**中读取JPG图片

## 运行现象
***
-  SD卡方式(存储示例图片example.jpg)：
当工程正确运行后，LCD屏正确显示存储设备中的图片信息，而串口终端会输出如下信息：
```
> Read picture data by SD card
> start decoding
> decoding done
> start encoding and decoding
> complete encoding length 804 bytes
> encoding and decoding done
```

-  USB方式(存储示例图片example.jpg)：
当工程正确运行后，LCD屏正确显示存储设备中的图片信息，而串口终端会输出如下信息：
```
> Read picture data by usb-mode
> start decoding
> decoding done
> start encoding and decoding
> complete encoding length 804 bytes
> encoding and decoding done
```


