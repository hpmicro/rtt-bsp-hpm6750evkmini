# JPEG Codec
## Overview
***
**jpeg_hw** JPEG codec example project shows how to convert JPG picture data into RGB data and RGB data into JPG picture data.
- For JPG pictures stored in **USB** or **SD card**, through this code project, extract **huffmin**, **huffbase**, **huffsymbol**, **huffenc** tables and pixel data, convert them into RGB data through hardware JPEG module, and display the pictures through **LCD** .
- RGB data is encoded through the hardware JPEG module, converted into YUV data,  then converted into RGB data through decoding, and the picture is displayed through **LCD**

## Board Setting
***
- Connect the **USB disk** to the development board ``usb0``, or insert the **SD memory card** into the development board ``SD card``, and store JPG pictures in the storage medium. The example pictures can be used under the JPEG path : **example.jpg**
- Connect **LCD screen** to development board ``lcd1``

## Engineering configuration
***
- File [cmakelists.txt](./CmakeLists.txt). If ``set (config_sdfatfs_mode 1)`` is configured, JPG pictures are read from the **SD card** by default; to configure ``set (config_tinyusbhost_mode 1)``, JPG pictures are read from **USB** by default

## Running the example
***
- SD card mode (Store sample pictures : example.jpg):
When the project runs correctly, the LCD screen correctly displays the picture information in the storage device, and the serial port terminal will output the following information:
```
> Read picture data by SD card
> start decoding
> decoding done
> start encoding and decoding
> complete encoding length 804 bytes
> encoding and decoding done
```

- USB mode (Store sample pictures : example.jpg):
When the project runs correctly, the LCD screen correctly displays the picture information in the storage device, and the serial port terminal will output the following information:
```
> Read picture data by usb-mode
> start decoding
> decoding done
> start encoding and decoding
> complete encoding length 804 bytes
> encoding and decoding done
```


