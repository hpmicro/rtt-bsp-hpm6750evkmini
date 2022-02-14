/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "board.h"
#include "hpm_sdmmc_sd.h"

static sd_card_t g_sd;

ATTR_PLACE_AT_NONCACHEABLE static uint32_t s_write_buf[4096];
ATTR_PLACE_AT_NONCACHEABLE static uint32_t s_read_buf[4096];


int main(void)
{
    board_init();

    printf("SD Card low-level demo...\n");

    if (sd_init(&g_sd) != status_success) {
        printf("SD Card initialization failed\n");
        return status_fail;
    }
    printf("SD Card initialization succeeded\n");

    printf("Card Info:\n-----------------------------------------------\n");
    printf("Card Size in GBytes:    %.2fGB\n", g_sd.card_size_in_bytes * 1.0f / 1024UL / 1024UL / 1024UL);
    printf("Total Block Counts: %u\n", g_sd.block_count);
    printf("Block Size: %d Bytes\n", g_sd.block_size);
    printf("Maximum supported frequency: %uMHz\n", g_sd.max_freq / 1000000UL);


    hpm_stat_t status = sd_erase_blocks(&g_sd, 0, 1023);
    printf("SD card erase completed, status=%d\n", status);

    for (uint32_t i = 0; i < ARRAY_SIZE(s_write_buf); i++) {
        s_write_buf[i] = i << 16 | i;
    }

    bool result = false;
    uint32_t step = sizeof(s_write_buf) / 512;
    for (uint32_t i = 0; i < 1024; i += step) {
        result = false;
        status = sd_write_blocks(&g_sd, (uint8_t *) s_write_buf, i, step);
        if (status != status_success) {
            break;
        }
        status = sd_read_blocks(&g_sd, (uint8_t *) s_read_buf, i, step);
        if (status != status_success) {
            break;
        }
        result = (memcmp(s_write_buf, s_read_buf, sizeof(s_write_buf)) == 0);
        printf("SD write-read-verify block range %d-%d %s\n", i, i + step - 1U, result ? "PASSED" : "FAILED");
        if (!result) {
            break;
        }
    }
    printf("Test completed, %s\n", result ? "PASSED" : "FAILED");

    while (1) {

    }

    return 0;
}
