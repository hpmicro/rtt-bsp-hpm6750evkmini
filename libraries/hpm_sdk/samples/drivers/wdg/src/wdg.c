/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "board.h"
#include "hpm_wdg_drv.h"
#include "hpm_sysctl_drv.h"

/***********************************************************************************
 *
 *  Definitions
 *
 **********************************************************************************/
#define RESET_SOURCE_WDG0 (1UL << 16)
#define RESET_SOURCE_WDG1 (1UL << 17)
#define RESET_SOURCE_WDG2 (1UL << 18)
#define RESET_SOURCE_WDG3 (1UL << 19)
#define RESET_SOURCE_WDG4 (1UL << 20)

#define WDG_INTERRUPT_INTERVAL_US (1000UL * 1000UL) /* WDG interrupt interval: 1s  */
#define WDG_RESET_INTERVAL_US (1000UL) /* WDOG reset interal:1ms */


/***********************************************************************************
 *
 *  Prototypes
 *
 **********************************************************************************/

/***********************************************************************************
 *
 *  Variables
 *
 **********************************************************************************/


/***********************************************************************************
 *
 *  Codes
 *
 **********************************************************************************/
int main(void)
{
    board_init();
    printf("wdg test\n");

    if ((HPM_PPOR->RESET_FLAG & RESET_SOURCE_WDG0) != 0U) {
        printf("The last reset was triggered by WDG0 reset\n");
    }
    else {

        /**
         * NOTE: The application should determine the following configuration based on the real need
         *       WDG reset time = WDG interrupt interval + WDG reset interval
         */
        wdg_control_t wdg_ctrl = {
            .reset_enable = true,
            .interrupt_enable = false,
            .wdg_enable = true,
        };
        wdg_ctrl.reset_interval = wdg_get_reset_interval(WDG_EXT_CLK_FREQ, WDG_RESET_INTERVAL_US);
        wdg_ctrl.interrupt_interval = wdg_get_interrupt_interval(WDG_EXT_CLK_FREQ, WDG_INTERRUPT_INTERVAL_US);

        /* Initialize the WDG */
        wdg_init(HPM_WDG0, &wdg_ctrl);
        /* Service WDG */
        wdg_restart(HPM_WDG0);
    }

    while (1) {
    }

    return 0;
}