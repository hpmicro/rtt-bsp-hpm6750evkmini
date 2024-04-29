# 简介

本例程演示了RT-Thread 中 [FAL](https://github.com/RT-Thread/rt-thread/blob/master/components/fal/docs/fal_api.md) 组件和 [FlashDB](https://github.com/armink/FlashDB/blob/master/README_zh.md) 组件的使用。

## 分区

本例程将FLASH分为4个分区：

- app
- easyflash
- download
- flashdb

分区地址详见 `board/fal_cfg.h`

## 功能

- 例程启动时会尝试初始化 KVDB 数据库，若数据库不存在，会直接初始化数据库，该过程耗时较长

```console
 \ | /
- RT -     Thread Operating System
 / | \     5.0.1 build Aug  3 2023 17:14:20
 2006 - 2022 Copyright by RT-Thread team
[D/FAL] (fal_flash_init:47) Flash device |                norflash0 | addr: 0x80000000 | len: 0x01000000 | blk_size: 0x00001000 |initialized finish.
[I/FAL] ==================== FAL partition table ====================
[I/FAL] | name      | flash_dev |   offset   |    length  |
[I/FAL] -------------------------------------------------------------
[I/FAL] | app       | norflash0 | 0x00000000 | 0x00400000 |
[I/FAL] | easyflash | norflash0 | 0x00400000 | 0x00200000 |
[I/FAL] | download  | norflash0 | 0x00600000 | 0x00100000 |
[I/FAL] | flashdb   | norflash0 | 0x00700000 | 0x00100000 |
[I/FAL] =============================================================
[I/FAL] RT-Thread Flash Abstraction Layer initialize success.
[FlashDB][kv][env] (../packages/FlashDB-v1.1.1/src/fdb_kvdb.c:1638) KVDB size is 1048576 bytes.
[FlashDB][kv][env] (../packages/FlashDB-v1.1.1/src/fdb_kvdb.c:1442) Sector header info is incorrect. Auto format this sector (0x00000000).
[FlashDB][kv][env] (../packages/FlashDB-v1.1.1/src/fdb_kvdb.c:1442) Sector header info is incorrect. Auto format this sector (0x00001000).
[FlashDB][kv][env] (../packages/FlashDB-v1.1.1/src/fdb_kvdb.c:1442) Sector header info is incorrect. Auto format this sector (0x00002000).
[FlashDB][kv][env] (../packages/FlashDB-v1.1.1/src/fdb_kvdb.c:1442) Sector header info is incorrect. Auto format this sector (0x00003000).
[FlashDB][kv][env] (../packages/FlashDB-v1.1.1/src/fdb_kvdb.c:1442) Sector header info is incorrect. Auto format this sector (0x00004000).
[FlashDB][kv][env] (../packages/FlashDB-v1.1.1/src/fdb_kvdb.c:1442) Sector header info is incorrect. Auto format this sector (0x00005000).
[FlashDB][kv][env] (../packages/FlashDB-v1.1.1/src/fdb_kvdb.c:1442) Sector header info is incorrect. Auto format this sector (0x00006000).
[FlashDB][kv][env] (../packages/FlashDB-v1.1.1/src/fdb_kvdb.c:1442) Sector header info is incorrect. Auto format this sector (0x00007000).
[FlashDB][kv][env] (../packages/FlashDB-v1.1.1/src/fdb_kvdb.c:1442) Sector header info is incorrect. Auto format this sector (0x00008000).
[FlashDB][kv][env] (../packages/FlashDB-v1.1.1/src/fdb_kvdb.c:1442) Sector header info is incorrect. Auto format this sector (0x00009000).
[FlashDB][kv][env] (../packages/FlashDB-v1.1.1/src/fdb_kvdb.c:1442) Sector header info is incorrect. Auto format this sector (0x0000A000).
```

- 当数据库初始化好后，会将启动次数+1存入数据库

```console
 \ | /
- RT -     Thread Operating System
 / | \     5.0.1 build Aug  3 2023 16:53:58
 2006 - 2022 Copyright by RT-Thread team
[D/FAL] (fal_flash_init:47) Flash device |                norflash0 | addr: 0x80000000 | len: 0x01000000 | blk_size: 0x00001000 |initialized finish.
[I/FAL] ==================== FAL partition table ====================
[I/FAL] | name      | flash_dev |   offset   |    length  |
[I/FAL] -------------------------------------------------------------
[I/FAL] | app       | norflash0 | 0x00000000 | 0x00400000 |
[I/FAL] | easyflash | norflash0 | 0x00400000 | 0x00200000 |
[I/FAL] | download  | norflash0 | 0x00600000 | 0x00100000 |
[I/FAL] | flashdb   | norflash0 | 0x00700000 | 0x00100000 |
[I/FAL] =============================================================
[I/FAL] RT-Thread Flash Abstraction Layer initialize success.
[FlashDB][kv][env] (../packages/FlashDB-v1.1.1/src/fdb_kvdb.c:1638) KVDB size is 1048576 bytes.
[FlashDB] FlashDB V1.1.1 is initialize success.
[FlashDB] You can get the latest version on https://github.com/armink/FlashDB .
[FlashDB][sample][kvdb][basic] ==================== kvdb_basic_sample ====================
[FlashDB][sample][kvdb][basic] get the 'boot_count' value is 5
[FlashDB][sample][kvdb][basic] set the 'boot_count' value to 6
[FlashDB][sample][kvdb][basic] ===========================================================
```

- 该例程支持的命令如下：

```console
RT-Thread shell commands:
clear            - clear the terminal screen
version          - show RT-Thread version information
list             - list objects
help             - RT-Thread shell help.
ps               - List threads in the system.
free             - Show the memory usage in the system.
fal              - FAL (Flash Abstraction Layer) operate.
date             - get date and time or set (local timezone) [year month day hour min sec]
pin              - pin [option]
kvdb             - FlashDB KVDB command.
reset            - reset the board
```

其中：

- fal 用于测试 `FLASH Abstraction Layer`的功能。

例如：

```console
fal probe easyflash
fal bench 4096 yes
```
注意：由于代码本身放在`app`区域，在`flash_debug`和`flash_release`的构建工程中请不要使用`fal bench`功能。

- kvdb 用于测试 `Key-Value Database` 的功能。例如：

```console
kvdb probe flashdb
kvdb bench
```
