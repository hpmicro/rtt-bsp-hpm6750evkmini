/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stdio.h>
#include "board.h"
#include "hpm_debug_console.h"
#include "hpm_butn_drv.h"

int main(void)
{
    uint8_t u;
    board_init();
    init_butn_pins();

    printf("hello world\n");
    while(1)
    {
        u = console_receive_byte();
        printf("%c", u);
    }
    return 0;
}
