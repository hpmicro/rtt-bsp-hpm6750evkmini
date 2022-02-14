/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "board.h"
#include "hpm_common.h"
#include "hpm_l1c_drv.h"
#include "hpm_romapi.h"

#define XPI0_MEM_START (0x80000000UL)
#define XPI1_MEM_START (0x90000000UL)

typedef struct {
    uint32_t total_sz_in_bytes;
    uint32_t sector_sz_in_bytes;
} hpm_flash_info_t;

__attribute__ ((section(".flash_algo.data"))) xpi_nor_config_t nor_config;
__attribute__ ((section(".flash_algo.data"))) bool xpi_inited = false;

__attribute__ ((section(".flash_algo.text"))) uint32_t flash_init(uint32_t flash_base)
{
    uint32_t i = 0;
    XPI_Type *xpi_base;
    xpi_nor_config_option_t cfg_option;
    hpm_stat_t stat = status_success;

    if (flash_base == XPI0_MEM_START) {
        xpi_base = HPM_XPI0;
    } else if (flash_base == XPI1_MEM_START) {
        xpi_base = HPM_XPI1;
    } else {
        return status_invalid_argument;
    }

    if (xpi_inited) {
        return stat;
    }

    for (i = 0; i < sizeof(cfg_option); i++) {
        *((uint8_t *)&cfg_option + i) = 0;
    }

    for (i = 0; i < sizeof(nor_config); i++) {
        *((uint8_t *)&nor_config + i) = 0;
    }

    cfg_option.header.tag = XPI_NOR_CFG_OPTION_TAG;
    cfg_option.header.words = 1;
    cfg_option.option0.probe_type = xpi_nor_probe_sfdp_sdr;
    cfg_option.option0.freq_opt = XPI_CLK_OUT_FREQ_OPTION_30MHz;
    cfg_option.option0.misc = xpi_nor_option_misc_internal_loopback;

    stat = ROM_API_TABLE_ROOT->xpi_nor_driver_if->auto_config(xpi_base, &nor_config, &cfg_option);
    if (stat) {
        return stat;
    }
    nor_config.device_info.clk_freq_for_non_read_cmd = 0;
    if (!xpi_inited) {
        xpi_inited = true;
    }
    return stat;
}

__attribute__ ((section(".flash_algo.text"))) uint32_t flash_erase(uint32_t flash_base, uint32_t address, uint32_t size)
{
    XPI_Type *xpi_base;
    hpm_stat_t stat;
    uint32_t left, start, block_size, align;
    if (flash_base == XPI0_MEM_START) {
        xpi_base = HPM_XPI0;
    } else if (flash_base == XPI1_MEM_START) {
        xpi_base = HPM_XPI1;
    } else {
        return status_invalid_argument;
    }

    stat = flash_init(flash_base);
    if (stat != status_success) {
        return stat;
    }

    left = size;
    start = address;
    block_size = nor_config.device_info.block_size_kbytes * 1024;
    if (left >= block_size) {
        align = block_size - (start % block_size);
        if (align != block_size) {
            stat = ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase(xpi_base, xpi_channel_a1, &nor_config, start, align);
            if (stat != status_success) {
                return stat;
            }
            left -= align;
            start += align;
        }
        while (left > block_size) {
            stat = ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase_block(xpi_base, xpi_channel_a1, &nor_config, start);
            if (stat != status_success) {
                break;
            }
            left -= block_size;
            start += block_size;
        }
    }
    if ((stat == status_success) && left) {
        stat = ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase(xpi_base, xpi_channel_a1, &nor_config, start, left);
    }
    return stat;
}

__attribute__ ((section(".flash_algo.text"))) uint32_t flash_program(uint32_t flash_base, uint32_t address, uint32_t *buf, uint32_t size)
{
    XPI_Type *xpi_base;
    hpm_stat_t stat;

    if (flash_base == XPI0_MEM_START) {
        xpi_base = HPM_XPI0;
    } else if (flash_base == XPI1_MEM_START) {
        xpi_base = HPM_XPI1;
    } else {
        return status_invalid_argument;
    }

    stat = flash_init(flash_base);
    if (stat != status_success) {
        return stat;
    }

    stat = ROM_API_TABLE_ROOT->xpi_nor_driver_if->program(xpi_base, xpi_channel_a1, &nor_config, buf, address, size);
    return stat;
}

__attribute__ ((section(".flash_algo.text"))) uint32_t flash_read(uint32_t flash_base, uint32_t *buf, uint32_t address, uint32_t size)
{
    XPI_Type *xpi_base;
    hpm_stat_t stat;
    if (flash_base == XPI0_MEM_START) {
        xpi_base = HPM_XPI0;
    } else if (flash_base == XPI1_MEM_START) {
        xpi_base = HPM_XPI1;
    } else {
        return status_invalid_argument;
    }

    stat = flash_init(flash_base);
    if (stat != status_success) {
        return stat;
    }

    stat = rom_xpi_nor_read(xpi_base, xpi_channel_a1, &nor_config, buf, address, size);
    return stat;
}

__attribute__ ((section(".flash_algo.text"))) uint32_t flash_get_info(uint32_t flash_base, hpm_flash_info_t *flash_info)
{
    hpm_stat_t stat;
    if (!flash_info) {
        return status_invalid_argument;
    }

    if (nor_config.tag != XPI_NOR_CFG_TAG) {
        stat = flash_init(flash_base);
        if (stat != status_success) {
            return stat;
        }
    }

    flash_info->total_sz_in_bytes = nor_config.device_info.size_in_kbytes << 10;
    flash_info->sector_sz_in_bytes = nor_config.device_info.sector_size_kbytes << 10;
    return status_success;
}

__attribute__ ((section(".flash_algo.text"))) uint32_t flash_erase_chip(uint32_t flash_base)
{
    hpm_stat_t stat;
    XPI_Type *xpi_base;
    if (flash_base == XPI0_MEM_START) {
        xpi_base = HPM_XPI0;
    } else if (flash_base == XPI1_MEM_START) {
        xpi_base = HPM_XPI1;
    } else {
        return status_invalid_argument;
    }

    stat = flash_init(flash_base);
    if (stat != status_success) {
        return stat;
    }

    return rom_xpi_nor_erase_chip(xpi_base, xpi_channel_a1, &nor_config);
}

__attribute__ ((section(".flash_algo.text"))) void flash_deinit(void)
{
    return;
}
