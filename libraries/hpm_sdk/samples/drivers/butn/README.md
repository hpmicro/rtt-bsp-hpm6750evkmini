# BUTN
## Overview

The butn example shows the PLED/WLED status when PBUTN/WBUTN input level change.

## Board Setting

No special settings are required

## Running the example

When the example runs successfully, press the PBUTN/WBUTN, PLED/WLED flashing according to the following rules.
1. when butn input high level, led off
2. when butn input low level(keep 0.5s), led flashes quickly
3. when butn input low level(keep 4s), led flashes slowly
4. when butn input low level(keep 16s), led off again

The following message is displayed in the terminal and board will send back received characters:
```
> hello world
```
