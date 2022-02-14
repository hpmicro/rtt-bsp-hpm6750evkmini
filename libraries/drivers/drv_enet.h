/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef DRV_ENET_H
#define DRV_ENET_H

/* MAC ADDRESS */
#define MAC_ADDR0   (0x98U)
#define MAC_ADDR1   (0x2CU)
#define MAC_ADDR2   (0xBCU)
#define MAC_ADDR3   (0xB1U)
#define MAC_ADDR4   (0x9FU)
#define MAC_ADDR5   (0x17U)

int rt_hw_eth_init(void);

#endif /* DRV_ENET_H */

/* DRV_GPIO_H */
