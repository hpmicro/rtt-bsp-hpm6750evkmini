/*
 * Copyright 2021 hpmicro
 * SPDX-License-Identifier: BSD-3-Clause
 */
ENTRY(_start)

#ifdef CONFIG_HEAP_SIZE
#define HEAP_SIZE CONFIG_HEAP_SIZE
#else
#define HEAP_SIZE 0x1000
#endif

#ifdef CONFIG_STACK_SIZE
#define STACK_SIZE CONFIG_STACK_SIZE
#else
#define STACK_SIZE 0x1000
#endif

#ifdef CONFIG_ILM_ADDR
#define ILM_ADDR CONFIG_ILM_ADDR
#define ILM_SIZE CONFIG_ILM_SIZE
#else
#define ILM_ADDR 0
#define ILM_SIZE 256K
#endif

#ifdef CONFIG_DLM_ADDR
#define DLM_ADDR CONFIG_DLM_ADDR
#define DLM_SIZE CONFIG_DLM_SIZE
#else
#define DLM_ADDR 0x80000
#define DLM_SIZE 256K
#endif

#ifdef CONFIG_SDRAM_ADDR
#define SDRAM_ADDR CONFIG_SDRAM_ADDR
#else
#define SDRAM_ADDR 0x40000000
#endif

#ifdef CONFIG_SDRAM_SIZE
#define SDRAM_SIZE CONFIG_SDRAM_SIZE
#else
#define SDRAM_SIZE 32M
#endif

#define AXI_SRAM_ADDR 0x1080000
#define AXI_SRAM_SIZE 1M

#define XPI0_FLASH_ADDR 0x80000000

#if !defined(CONFIG_ROM_ADDR) && !defined(CONFIG_ROM_SIZE)
#ifdef CONFIG_XIP 
#define ROM_ADDR XPI0_FLASH_ADDR
#define ROM_SIZE CONFIG_FLASH_SIZE
#define NOR_XIP_CFG_OPT_LOAD_ADDR (XPI0_FLASH_ADDR + 0x400)
#define NOR_XIP_BOOTHEADER_LOAD_ADDR (XPI0_FLASH_ADDR + 0x1000)
#define APPLICATION_LOAD_ADDR (XPI0_FLASH_ADDR + 0x3000)
#define RAM_VECTOR_ADDR ILM_ADDR
#elif defined(CONFIG_TEXT_IN_SDRAM)
#define ROM_ADDR SDRAM_ADDR
/* Reserver 1/8 of SDRAM for text use */
#define ROM_SIZE (SDRAM_SIZE >> 3)
#elif defined(CONFIG_TEXT_IN_AXI_SRAM)
#define ROM_ADDR AXI_SRAM_ADDR
#define ROM_SIZE AXI_SRAM_SIZE
#else
#define ROM_ADDR ILM_ADDR
#define ROM_SIZE ILM_SIZE
#define USE_ILM_AS_ROM 1
#endif
#else
#define ROM_ADDR CONFIG_ROM_ADDR
#define ROM_SIZE CONFIG_ROM_SIZE
#endif

#ifndef APPLICATION_LOAD_ADDR
#define APPLICATION_LOAD_ADDR ROM_ADDR
#endif

#if !defined(CONFIG_RAM_ADDR) && !defined(CONFIG_RAM_SIZE)
#ifdef CONFIG_DATA_IN_SDRAM
#ifdef CONFIG_TEXT_IN_SDRAM
#define RAM_ADDR (SDRAM_ADDR + ROM_SIZE)
#define RAM_SIZE (SDRAM_SIZE - ROM_SIZE)
#else
#define RAM_ADDR SDRAM_ADDR
#define RAM_SIZE SDRAM_SIZE
#endif
#else
#define RAM_ADDR AXI_SRAM_ADDR
#define RAM_SIZE AXI_SRAM_SIZE
#define USE_AXI_SRAM_AS_RAM 1
#endif
#else
#define RAM_ADDR CONFIG_RAM_ADDR
#define RAM_SIZE CONFIG_RAM_SIZE
#endif

MEMORY
{
    FLASH (rx) : ORIGIN = ROM_ADDR, LENGTH = ROM_SIZE
#if !defined(USE_ILM_AS_ROM)
    ILM (rx) : ORIGIN = ILM_ADDR, LENGTH = ILM_SIZE
#endif
    DLM (w) : ORIGIN = DLM_ADDR, LENGTH = DLM_SIZE
    RAM (wx) : ORIGIN = RAM_ADDR, LENGTH = RAM_SIZE
#if !defined(CONFIG_DATA_IN_SDRAM) && !defined(CONFIG_TEXT_IN_SDRAM)
    SDRAM (wx) : ORIGIN = SDRAM_ADDR, LENGTH = SDRAM_SIZE
#endif
#if !defined(CONFIG_TEXT_IN_AXI_SRAM) && !defined(USE_AXI_SRAM_AS_RAM)
    AXI_SRAM (wx) : ORIGIN = AXI_SRAM_ADDR, LENGTH = AXI_SRAM_SIZE
#endif
}

SECTIONS
{
#ifdef CONFIG_XIP
#ifndef CONFIG_XIP_NO_BOOTHEADER
    .nor_cfg_option NOR_XIP_CFG_OPT_LOAD_ADDR : {
        KEEP(*(.nor_cfg_option))
    } > FLASH

    .boot_header NOR_XIP_BOOTHEADER_LOAD_ADDR : {
        __boot_header_start__ = .;
        KEEP(*(.boot_header))
        KEEP(*(.fw_info_table))
        KEEP(*(.dc_info))
        __boot_header_end__ = .;
    } > FLASH
    __boot_header_length__ = __boot_header_end__ - __boot_header_start__;

    __app_offset__ = APPLICATION_LOAD_ADDR - NOR_XIP_BOOTHEADER_OFFSET;
#endif
#endif

    .start : AT(APPLICATION_LOAD_ADDR) {
        . = ALIGN(8);
        KEEP(*(.start))
    } > FLASH

    .vectors : {
        . = ALIGN(8);
        __vector_start__ = .;
        KEEP(*(.isr_vector))
        KEEP(*(.vector_table))
        . = ALIGN(8);
        __vector_end__ = .;
    } > FLASH 

    .rel : {
        *(.rel*)
    } > FLASH

    .text : {
        . = ALIGN(8);
        *(.pl*)
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        *(.srodata)
        *(.srodata*)

        *(.hash)
        *(.dyn*)
        *(.gnu*)

        KEEP(*(.eh_frame))
        *(.eh_frame*)

        KEEP (*(.init))
        KEEP (*(.fini))
        . = ALIGN(8);
    } > FLASH

    PROVIDE (__etext = .);
    PROVIDE (_etext = .);
    PROVIDE (etext = .);

    .data : AT(etext) {
        . = ALIGN(8);
        __data_start__ = .;
        __global_pointer$ = . + 0x800;
        *(.data)
        *(.data*)
        *(.sdata)
        *(.sdata*)
        *(.tdata)
        *(.tdata*)

        KEEP(*(.jcr))
        KEEP(*(.dynamic))
        KEEP(*(.got*))
        KEEP(*(.got))
        KEEP(*(.gcc_except_table))
        KEEP(*(.gcc_except_table.*))

        PROVIDE(__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE(__preinit_array_end = .);

        PROVIDE(__init_array_start = .);
        KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE(__init_array_end = .);

        PROVIDE(__finit_array_start = .);
        KEEP(*(SORT_BY_INIT_PRIORITY(.finit_array.*)))
        KEEP(*(.finit_array))
        PROVIDE(__finit_array_end = .);

        KEEP(*crtbegin*.o(.ctors))
        KEEP(*(EXCLUDE_FILE (*crtend*.o) .ctors))
        KEEP(*(SORT(.ctors.*)))
        KEEP(*(.ctors))

        KEEP(*crtbegin*.o(.dtors))
        KEEP(*(EXCLUDE_FILE (*crtend*.o) .dtors))
        KEEP(*(SORT(.dtors.*)))
        KEEP(*(.dtors))

        __data_end__ = .;
        PROVIDE (__edata = .);
        PROVIDE (_edata = .);
        PROVIDE (edata = .);
#ifdef CONFIG_DATA_IN_DLM
    } > DLM
#else
    } > RAM
#endif

#ifdef CONFIG_XIP
    __fw_size__ = __data_end__ - __data_start__ + etext - APPLICATION_LOAD_ADDR;
#endif
    .bss : {
        . = ALIGN(8);
        __bss_start__ = .;
        *(.bss)
        *(.bss*)
        *(.tbss*)
        *(.sbss*)
        *(.scommon)
        *(.scommon*)
        *(.tcommon*)
        *(.dynsbss*)
        *(COMMON)
        . = ALIGN(8);
        _end = .;
        __bss_end__ = .;
    } > RAM

    .noncachable (NOLOAD) : {
        . = ALIGN(8);
        __noncachable_start__ = .;
        KEEP(*(.noncachable))
        . = ALIGN(8);
        __noncachable_end__ = .;
    } > RAM

    .framebuffer (NOLOAD) : {
        KEEP(*(.framebuffer))
#ifdef CONFIG_FB_IN_SDRAM
    } > SDRAM
#else
    } > RAM
#endif

    .heap : {
        . = ALIGN(8);
        __heap_start__ = .;
        . += HEAP_SIZE;
        __heap_end__ = .;
    } > DLM

    .stack : {
        . = ALIGN(8);
        __stack_base__ = .;
        . += STACK_SIZE;
        PROVIDE (_stack = .);
        PROVIDE (_stack_in_dlm = .);
    } > DLM
}
