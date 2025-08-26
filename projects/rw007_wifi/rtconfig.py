# Copyright 2021-2025 HPMicro
# SPDX-License-Identifier: BSD-3-Clause

import os
import sys

# toolchains options
ARCH='risc-v'
CPU='hpmicro'

SOC_FAMILY='HPM6700'
CHIP_NAME='HPM6750'

CROSS_TOOL='gcc'

# bsp lib config
BSP_LIBRARY_TYPE = None

# Fallback toolchain info
FALLBACK_TOOLCHAIN_VENDOR='RISC-V'
FALLBACK_TOOLCHAIN_PKG='RISC-V-GCC-RV32'
FALLBACK_TOOLCHAIN_VER='2022-04-12'

CROSS_TOOL = 'gcc'
PLATFORM = 'gcc'

if os.getenv('RTT_TOOLCHAIN_PLATFORM'):
    PLATFORM = os.getenv('RTT_TOOLCHAIN_PLATFORM')
    if PLATFORM == 'gcc':
        CROSS_TOOL = 'gcc'
    elif PLATFORM == 'zcc':
        CROSS_TOOL = 'zcc'
    elif PLATFORM == 'segger':
        CROSS_TOOL = 'segger'
else:
    if os.getenv('RTT_CC'):
        CROSS_TOOL = os.getenv('RTT_CC')
    else:
        CROSS_TOOL = 'gcc'

if os.getenv('RV_ARCH'):
    RV_ARCH = os.getenv('RV_ARCH')
else:
    RV_ARCH = 'rv32imac'
if os.getenv('RV_ABI'):
    RV_ABI = os.getenv('RV_ABI')
else:
    RV_ABI = 'ilp32'

RTT_EXEC_PATH = os.getenv('RTT_EXEC_PATH')
if RTT_EXEC_PATH != None and CROSS_TOOL == 'gcc':
    folders = RTT_EXEC_PATH.split(os.sep)
    # If the RT-Thread Env is from the RT-Thread Studio, generate the RTT_EXEC_PATH using `FALLBACK_TOOLCHAIN_INFO`
    if 'arm_gcc' in folders:
        if 'platform' in folders:
            RTT_EXEC_PATH = ''
            for path in folders:
                if path != 'platform':
                    RTT_EXEC_PATH = RTT_EXEC_PATH + path + os.sep
                else:
                    break
            RTT_EXEC_PATH = os.path.join(RTT_EXEC_PATH, 'repo', 'Extract', 'ToolChain_Support_Packages', FALLBACK_TOOLCHAIN_VENDOR, FALLBACK_TOOLCHAIN_PKG, FALLBACK_TOOLCHAIN_VER, 'bin')
            os.environ['RTT_RISCV_TOOLCHAIN'] = RTT_EXEC_PATH
    else:
        riscv_gcc_exe_name = 'riscv32-unknown-elf-gcc'
        if os.name == 'nt':
            riscv_gcc_exe_name = 'riscv32-unknown-elf-gcc.exe'
        if riscv_gcc_exe_name in os.listdir(RTT_EXEC_PATH):
            os.environ['RTT_RISCV_TOOLCHAIN'] = RTT_EXEC_PATH

# cross_tool provides the cross compiler
# EXEC_PATH is the compiler path, for example, GNU RISC-V toolchain, IAR
if  CROSS_TOOL == 'gcc':
    PLATFORM    = 'gcc'
    if os.getenv('RTT_RISCV_TOOLCHAIN'):
        EXEC_PATH = os.getenv('RTT_RISCV_TOOLCHAIN')
    else:
        EXEC_PATH   = r'/opt/riscv-gnu-gcc/bin'
elif CROSS_TOOL == 'zcc':
    PLATFORM    = 'zcc'
    EXEC_PATH = os.getenv('ZCC_TOOLCHAIN_PATH')
elif CROSS_TOOL == 'segger':
    PLATFORM    = 'segger'
    EXEC_PATH = os.getenv('SEGGER_TOOLCHAIN_PATH')
else:
    print("CROSS_TOOL = {} not yet supported" % CROSS_TOOL)

RTT_EXEC_PATH=EXEC_PATH

if os.getenv('RTT_BUILD_TYPE'):
    BUILD = os.getenv('RTT_BUILD_TYPE')
else:
    BUILD = 'flash_debug'

if PLATFORM == 'gcc':
    PREFIX = 'riscv32-unknown-elf-'
    CC = PREFIX + 'gcc'
    CXX = PREFIX + 'g++'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    GDB = PREFIX + 'gdb'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'
    STRIP = PREFIX + 'strip'

    ARCH_ABI = ' -mcmodel=medlow '
    CFLAGS = ARCH_ABI  + ' -DUSE_NONVECTOR_MODE=1  ' + ' -ffunction-sections -fdata-sections -fno-common '
    AFLAGS = CFLAGS
    LFLAGS  = ARCH_ABI + '  --specs=nano.specs --specs=nosys.specs  -u _printf_float -u _scanf_float -nostartfiles -Wl,-Map=rtthread.map,--gc-sections,-print-memory-usage '

    CPATH = ''
    LPATH = ''
    if BUILD == 'ram_debug':
        CFLAGS += ' -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
        CFLAGS += ' -Og'
        LFLAGS += ' -Og'
        LINKER_FILE = 'board/linker_scripts/gcc/ram_rtt.ld'
    elif BUILD == 'ram_release':
        CFLAGS += ' -DNDEBUG -O2'
        LFLAGS += ' -O2'
        LINKER_FILE = 'board/linker_scripts/gcc/ram_rtt.ld'
    elif BUILD == 'flash_debug':
        CFLAGS += ' -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
        CFLAGS += ' -Og'
        LFLAGS += ' -Og'
        CFLAGS += ' -DFLASH_XIP=1'
        LINKER_FILE = 'board/linker_scripts/gcc/flash_rtt.ld'
    elif BUILD == 'flash_release':
        CFLAGS += ' -DNDEBUG -O2'
        LFLAGS += ' -O2'
        CFLAGS += ' -DFLASH_XIP=1'
        LINKER_FILE = 'board/linker_scripts/gcc/flash_rtt.ld'
    else:
        CFLAGS += ' -O2'
        LFLAGS += ' -O2'
        CFLAGS += ' -DFLASH_XIP=1'
        LINKER_FILE = 'board/linker_scripts/gcc/flash_rtt.ld'
    LFLAGS += ' -T ' + LINKER_FILE

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'

    # module setting
    CXXFLAGS = CFLAGS +  ' -Woverloaded-virtual -fno-exceptions -fno-rtti '
    CFLAGS = CFLAGS + ' -std=gnu11'
elif PLATFORM == 'zcc':
    PREFIX = ''
    CC = 'zcc'
    CXX = 'z++'
    AS = 'zcc'
    AR = 'llvm-ar'
    LINK = 'zcc'
    GDB = 'ldb'
    TARGET_EXT = 'elf'
    SIZE = 'llvm-size'
    OBJDUMP = 'llvm-objdump'
    OBJCPY = 'llvm-objcopy'
    STRIP = 'llvm-strip'

    ARCH_ABI = ' --target=riscv32-unknown-elf -march=' + RV_ARCH + ' -mabi=' + RV_ABI + ' '
    CFLAGS = ARCH_ABI  + ' -DUSE_NONVECTOR_MODE=1  ' + ' -mtune=andes-d45-series  -Wall -Wno-undef -Wno-unused-variable -Wno-format -Wno-ignored-attributes -fomit-frame-pointer -fno-builtin -ffunction-sections -fdata-sections  -Wno-implicit-function-declaration'
    AFLAGS = CFLAGS
    LFLAGS  = ARCH_ABI + ' -u _printf_float -u _scanf_float -static -nostartfiles -Wl,-Map=rtthread.map,--gc-sections,--orphan-handling=place,-print-memory-usage '

    CPATH = ''
    LPATH = ''
    if BUILD == 'ram_debug':
        CFLAGS += ' -gdwarf-4'
        AFLAGS += ' -gdwarf-4'
        CFLAGS += ' -Og'
        LFLAGS += ' -Og'
        LINKER_FILE = 'board/linker_scripts/gcc/ram_rtt.ld'
    elif BUILD == 'ram_release':
        CFLAGS += ' -DNDEBUG -Os'
        LFLAGS += ' -Os'
        LINKER_FILE = 'board/linker_scripts/gcc/ram_rtt.ld'
    elif BUILD == 'flash_debug':
        CFLAGS += ' -gdwarf-4'
        AFLAGS += ' -gdwarf-4'
        CFLAGS += ' -Og'
        LFLAGS += ' -Og'
        CFLAGS += ' -DFLASH_XIP=1'
        LINKER_FILE = 'board/linker_scripts/gcc/flash_rtt.ld'
    elif BUILD == 'flash_release':
        CFLAGS += ' -DNDEBUG -Os'
        LFLAGS += ' -Os'
        CFLAGS += ' -DFLASH_XIP=1'
        LINKER_FILE = 'board/linker_scripts/gcc/flash_rtt.ld'
    else:
        CFLAGS += ' -Os'
        LFLAGS += ' -Os'
        CFLAGS += ' -DFLASH_XIP=1'
        LINKER_FILE = 'board/linker_scripts/gcc/flash_rtt.ld'
    LFLAGS += ' -T ' + LINKER_FILE

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'

    # module setting
    CXXFLAGS = CFLAGS +  ' -Woverloaded-virtual -fno-exceptions -fno-rtti '

elif PLATFORM == 'segger':
    # NOTE: below scripts doesn't take effect, they are added to satisfy the scons build system
    PREFIX = 'segger-'
    CC = 'cc'
    CXX = 'cc'
    AS = 'as'
    AR = 'cc'
    LINK = 'ld'
    GDB = 'ldb'
    TARGET_EXT = 'elf'
    SIZE = ''
    OBJDUMP = ''
    OBJCPY = ''
    STRIP = ''

    ARCH_ABI = ' --target=riscv32-unknown-elf -march=' + RV_ARCH + ' -mabi=' + RV_ABI + ' '
    CFLAGS = ARCH_ABI  + ' -DUSE_NONVECTOR_MODE=1  -DMAIN_ENTRY=entry  ' + ' -mtune=andes-d45-series -Wall -Wundef -Wno-format -Wno-ignored-attributes -fomit-frame-pointer -fno-builtin -ffunction-sections -fdata-sections  '
    AFLAGS = CFLAGS
    LFLAGS  = ARCH_ABI + ' -u _printf_float -u _scanf_float -static -nostartfiles -Wl,-Map=rtthread.map,--gc-sections,--orphan-handling=place,-print-memory-usage '

    CPATH = ''
    LPATH = ''
    # Note: DO NOT provide 'FLASH_XIP=1' as this info is provided in the template.emProject already
    if BUILD == 'ram_debug':
        CFLAGS += ' -gdwarf-4'
        AFLAGS += ' -gdwarf-4'
        CFLAGS += ' -Og'
        LFLAGS += ' -Og'
        LINKER_FILE = 'board/linker_scripts/segger/ram_rtt.icf'
    elif BUILD == 'ram_release':
        CFLAGS += ' -O2'
        LFLAGS += ' -O2'
        LINKER_FILE = 'board/linker_scripts/segger/ram_rtt.icf'
    elif BUILD == 'flash_debug':
        CFLAGS += ' -gdwarf-4'
        AFLAGS += ' -gdwarf-4'
        CFLAGS += ' -Og'
        LFLAGS += ' -Og'
        LINKER_FILE = 'board/linker_scripts/segger/flash_rtt.icf'
    elif BUILD == 'flash_release':
        CFLAGS += ' -Os'
        LFLAGS += ' -Os'
        LINKER_FILE = 'board/linker_scripts/segger/flash_rtt.icf'
    else:
        CFLAGS += ' -Os'
        LFLAGS += ' -Os'
        LINKER_FILE = 'board/linker_scripts/segger/flash_rtt.icf'
    LFLAGS += ' -T ' + LINKER_FILE

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'

    # module setting
    CXXFLAGS = CFLAGS +  ' -Woverloaded-virtual -fno-exceptions -fno-rtti '