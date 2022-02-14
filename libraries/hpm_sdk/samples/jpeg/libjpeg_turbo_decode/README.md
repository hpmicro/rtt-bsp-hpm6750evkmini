## Overview
***
libjpeg_Turbo decoding example project shows how to pass JPG image data through libjpeg_turbo library is converted to RGB data.In this project,JPEG images stored in USB or SD card are converted into
rgb565 data through code base, The decoded data is displayed on the LCD screen.

## Board Setting
***
1. Connect the USB disk to the development board "usb0", or insert the SD memory card into the development board "SD card", and store JPG pictures in the storage medium. The example pictures can be used under the JPEG path : example.jpg
2. Connect LCD screen to development board "lcd1"

## Engineering configuration
***
1. File cmakelists.txt. If set (config_sdfatfs_mode 1) is configured, JPG pictures are read from the SD card by default; to configure Set (config_tinyusbhost_mode 1), JPG pictures are read from USB by default

## Running the example
***
1. SD card mode (Store sample pictures : example.jpg):
When the project runs correctly, the LCD screen correctly displays the picture information in the storage device, and the serial port terminal will output the following information:
> Read picture data by SD card
> Libjpeg-turbo decode completed

2. USB mode (Store sample pictures : example.jpg):
When the project runs correctly, the LCD screen correctly displays the picture information in the storage device, and the serial port terminal will output the following information:
> Read picture data by usb-mode
> Libjpeg-turbo decode completed


