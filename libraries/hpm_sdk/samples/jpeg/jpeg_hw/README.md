## Overview
***
The JPEG codec example project shows how to convert JPG picture data into RGB data and RGB data into JPG picture data.In this project, the JPG images stored in USB or SD card extract the relevant table and pixel data through the code and pass through the hardware JPEG module Convert to RGB data and display the decoded data through the LCD screen; See the decoded data, which is encoded by the hardware JPEG module,Convert to JPG data, then convert to RGB data through decoding, and display it through LCD.

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
> start decoding
> decoding done
> start encoding and decoding
> complete encoding length 804 bytes
> encoding and decoding done

2. USB mode (Store sample pictures : example.jpg):
When the project runs correctly, the LCD screen correctly displays the picture information in the storage device, and the serial port terminal will output the following information:
> Read picture data by usb-mode
> start decoding
> decoding done
> start encoding and decoding
> complete encoding length 804 bytes
> encoding and decoding done


