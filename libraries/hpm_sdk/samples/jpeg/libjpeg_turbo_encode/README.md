## Overview
***
libjpeg_turbo coding example project shows how to pass the rgb565 data collected by the camera through libjpeg_turbo library is converted into JPG data and saved in the storage medium. In this project, the rgb565 data is obtained through the camera, the rgb565 data is converted into JPEG data through the code base, and the JPG pictures are stored in USB or SD card

## Board Setting
***
1. Connect the USB disk to the development board "usb0", or insert the SD memory card into the development board "SD card"
2. Cam camera connected to development board "cam"

## Engineering configuration
***
1. File cmakelists.txt. If set (config_sdfatfs_mode 1) is configured, Jpg pictures are stored in SD card by default; to configure Set (config_tinyusbhost_mode 1), Jpg pictures are stored in USB by default

## Running the example
***
1. SD card mode:
When the project runs correctly, the pictures captured by the camera are stored in the SD card and named camera Jpg, and the serial terminal will output the following information:
> storage picture data by SD card
> File Name: Camera.jpg
> Libjpeg-turbo encode completed

1. USB mode:
When the project runs correctly, the pictures captured by the camera are stored in USB and named camera Jpg, and the serial terminal will output the following information
:
> storage picture data by tinyusb mode
> File Name: Camera.jpg
> Libjpeg-turbo encode completed