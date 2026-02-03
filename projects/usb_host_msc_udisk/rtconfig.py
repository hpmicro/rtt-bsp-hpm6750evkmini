# Copyright 2021-2026 HPMicro
# SPDX-License-Identifier: BSD-3-Clause

import os
import sys

from hpm_toolchain_helper import get_compiler_info
from hpm_toolchain_helper import find_gcc_and_extract_triplet
from hpm_toolchain_helper import find_rt_thread_studio

# toolchains options
ARCH='risc-v'
CPU='hpmicro'

SOC_FAMILY='HPM6700'
CHIP_NAME='HPM6750'

SOC_SUPPORT_B_EXTENSION=False

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
if CROSS_TOOL == 'gcc':
    if RTT_EXEC_PATH != None:
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
    else:
        # Find rt-thread studio installation path
        if RTT_EXEC_PATH is None and os.getenv('RTT_RISCV_TOOLCHAIN') is None:
            studio_install_dir = find_rt_thread_studio()
            if studio_install_dir is not None:
                os.environ['RTT_RISCV_TOOLCHAIN'] = os.path.join(studio_install_dir, 'repo', 'Extract', 'ToolChain_Support_Packages', FALLBACK_TOOLCHAIN_VENDOR, FALLBACK_TOOLCHAIN_PKG, FALLBACK_TOOLCHAIN_VER, 'bin')

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

if EXEC_PATH is None:
    print("Error: EXEC_PATH variable is None")
    print("Please set the appropriate toolchain environment variable:")
    if CROSS_TOOL == 'gcc':
        print("  - RTT_RISCV_TOOLCHAIN for GCC toolchain")
    elif CROSS_TOOL == 'zcc':
        print("  - ZCC_TOOLCHAIN_PATH for ZCC toolchain")
    elif CROSS_TOOL == 'segger':
        print("  - SEGGER_TOOLCHAIN_PATH for Segger toolchain")
    sys.exit(1)

RTT_EXEC_PATH=EXEC_PATH

if os.getenv('RTT_BUILD_TYPE'):
    BUILD = os.getenv('RTT_BUILD_TYPE')
else:
    BUILD = 'flash_debug'

# Control the omit frame pointer option
# Note: for the ses protect, users should change the "Omit Frame Pointer" option to "No" manually
NO_OMIT_FRAME_POINTER = False

# First check .config file for CONFIG_HPM_ENABLE_RTTHREAD_BACKTRACE_PORT
config_file_path = '.config'
if os.path.exists(config_file_path):
    try:
        with open(config_file_path, 'r') as f:
            for line in f:
                line = line.strip()
                # Check if 'CONFIG_HPM_ENABLE_RTTHREAD_BACKTRACE_PORT=y' is set
                if 'CONFIG_HPM_ENABLE_RTTHREAD_BACKTRACE_PORT' in line:
                    if '=y' in line:
                        NO_OMIT_FRAME_POINTER = True
                    else:
                        NO_OMIT_FRAME_POINTER = False
                    break

    except Exception:
        # ignore the exception
        pass

if PLATFORM == 'gcc':
    triplet = find_gcc_and_extract_triplet(EXEC_PATH)
    if triplet['triplet']:
        PREFIX = triplet['triplet'] + '-'
    else:
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

    # Dynamic detect the compiler information
    info = get_compiler_info(PLATFORM, EXEC_PATH, CC)
    if info is not None and info['nds32_toolchain'] is not None and 'is_nds32' in info['nds32_toolchain'].keys():
        is_nds32_toolchain = info['nds32_toolchain']['is_nds32']
    else:
        is_nds32_toolchain = False
    default_arch = info['default_arch']
    default_abi = info['default_abi']


    if is_nds32_toolchain:
        toolchain_support_b_extension = True
        toolchain_support_zbc_extensions = True
        RV_ARCH = info['default_arch']
        RV_ABI = info['default_abi']
    else:
        if info['b_extension_support'] is not None:
            toolchain_support_b_extension = info['b_extension_support']['has_b_extension']
            toolchain_support_zbc_extensions = 'zbc' in info['b_extension_support']['supported_b_extensions']
            isa_spec = info['isa_spec_support']['isa_spec']
        else:
            toolchain_support_b_extension = False
            toolchain_support_zbc_extensions = False
            isa_spec = '2.2'

        if isa_spec is not None:
            if isa_spec >= '20191213':
                if RV_ARCH == 'rv32imac':
                    RV_ARCH += '_zicsr_zifencei'
                elif RV_ARCH == 'rv32imafc':
                    RV_ARCH += '_zifencei'
                elif RV_ARCH == 'rv32imafdc' or RV_ARCH == 'rv32gc':
                    pass
                else:
                    exit(1)
        else:
            RV_ARCH += '_zicsr_zifencei'
        if toolchain_support_b_extension and SOC_SUPPORT_B_EXTENSION:
            if toolchain_support_zbc_extensions:
                RV_ARCH += '_zba_zbb_zbc_zbs'
            else:
                RV_ARCH += '_zba_zbb_zbs'
    ARCH_ABI = ' -mcmodel=medlow -march=' + RV_ARCH + ' -mabi=' + RV_ABI + ' '


    DEVICE = ARCH_ABI  + ' -DUSE_NONVECTOR_MODE=1  -DUSB_HOST_MCU_CORE=HPM_CORE0 -DCONFIG_NOT_ENABLE_DCACHE -DRT_DFS_ELM_USE_EXFAT=1 -D__USE_EXT_DISKIO -DUSB_FATFS_ENABLE=1 -DCONFIG_USB_DCACHE_ENABLE=1 -DCONFIG_CHERRYUSB_CUSTOM_IRQ_HANDLER=1 -DCONFIG_NDEBUG_CONSOLE=1 ' + ' -ffunction-sections -fdata-sections -fno-common -fno-omit-frame-pointer'
    CFLAGS = DEVICE
    AFLAGS = CFLAGS
    CFLAGS += ' -Wno-incompatible-pointer-types '

    if NO_OMIT_FRAME_POINTER:
        CFLAGS += ' -fno-omit-frame-pointer '
    else:
        CFLAGS += ' -fomit-frame-pointer '

    if is_nds32_toolchain:
        if SOC_SUPPORT_B_EXTENSION:
            CFLAGS += ' -mext-zbabcs'
        CFLAGS += ' -mcpu=d45 '
        LFLAGS = ' -nostartfiles -Wl,-Map=rtthread.map,--gc-sections,-print-memory-usage,-z,max-page-size=0x8 '
    else:
        LFLAGS  = ARCH_ABI + '  --specs=nano.specs --specs=nosys.specs  -u _printf_float -u _scanf_float -nostartfiles -Wl,-Map=rtthread.map,--gc-sections,-print-memory-usage,-z,max-page-size=0x8 '

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
    if SOC_SUPPORT_B_EXTENSION:
        RV_ARCH += 'b_zbc' # Note: all HPMicro SoCs support zba,zbb,zbc,zbs extensions
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
    DEVICE = ARCH_ABI  + ' -DUSE_NONVECTOR_MODE=1  -DUSB_HOST_MCU_CORE=HPM_CORE0 -DCONFIG_NOT_ENABLE_DCACHE -DRT_DFS_ELM_USE_EXFAT=1 -D__USE_EXT_DISKIO -DUSB_FATFS_ENABLE=1 -DCONFIG_USB_DCACHE_ENABLE=1 -DCONFIG_CHERRYUSB_CUSTOM_IRQ_HANDLER=1 -DCONFIG_NDEBUG_CONSOLE=1 ' + ' -mtune=andes-d45-series  -Wall -Wno-undef -Wno-unused-variable -Wno-format -Wno-ignored-attributes -fno-builtin -ffunction-sections -fdata-sections  -Wno-implicit-function-declaration -Wno-incompatible-function-pointer-types '
    CFLAGS = DEVICE
    AFLAGS = CFLAGS
    if NO_OMIT_FRAME_POINTER:
        CFLAGS += ' -fno-omit-frame-pointer '
    else:
        CFLAGS += ' -fomit-frame-pointer '


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
    DEVICE = ARCH_ABI  + ' -DUSE_NONVECTOR_MODE=1  -DMAIN_ENTRY=entry  -DUSB_HOST_MCU_CORE=HPM_CORE0 -DCONFIG_NOT_ENABLE_DCACHE -DRT_DFS_ELM_USE_EXFAT=1 -D__USE_EXT_DISKIO -DUSB_FATFS_ENABLE=1 -DCONFIG_USB_DCACHE_ENABLE=1 -DCONFIG_CHERRYUSB_CUSTOM_IRQ_HANDLER=1 -DCONFIG_NDEBUG_CONSOLE=1 ' + ' -mtune=andes-d45-series -Wall -Wundef -Wno-format -Wno-ignored-attributes -fomit-frame-pointer -fno-builtin -ffunction-sections -fdata-sections  '
    CFLAGS = DEVICE
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