/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_RTL8201_H
#define HPM_RTL8201_H

/*---------------------------------------------------------------------
 * Includes
 *---------------------------------------------------------------------
 */
#include "hpm_enet_phy.h"
#include "hpm_common.h"
#include "hpm_enet_regs.h"
/*---------------------------------------------------------------------
 *  Macro Const Definitions
 *---------------------------------------------------------------------
 */
#ifndef RTL8201_ADDR
#define RTL8201_ADDR (2U)
#endif

#define RTL8201_ID1  (0x001CU)
#define RTL8201_ID2  (0x32U)

/*---------------------------------------------------------------------
 *  Typedef Struct Declarations
 *---------------------------------------------------------------------
 */
typedef struct {
    bool loopback;
    uint8_t speed;
    bool auto_negotiation;
    uint8_t duplex;
    bool txc_input;
} rtl8201_config_t;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
/*---------------------------------------------------------------------
 * Exported Functions
 *---------------------------------------------------------------------
 */
void rtl8201_reset(ENET_Type *ptr);
void rtl8201_basic_mode_default_config(ENET_Type *ptr, rtl8201_config_t *config);
bool rtl8201_basic_mode_init(ENET_Type *ptr, rtl8201_config_t *config);
void rtl8201_get_phy_status(ENET_Type *ptr, enet_phy_status_t *status);

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* HPM_RTL8201_H */
