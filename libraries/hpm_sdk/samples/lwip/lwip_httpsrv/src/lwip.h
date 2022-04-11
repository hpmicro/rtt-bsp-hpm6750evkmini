/*
 * Copyright (c) 2022 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef LWIP_H
#define LWIP_H

/* Includes ------------------------------------------------------------------*/
#include "hpm_enet_drv.h"

/* Exported Macros------------------------------------------------------------*/
#define ENET_CONCTL     HPM_CONCTL

#if RGMII
#define ENET_INF_TYPE   enet_inf_rgmii
#define ENET            HPM_ENET0
#define ENET_ID         (0UL)
#define ENET_TX_DLY     (0U)
#define ENET_RX_DLY     (21U)
#else
#define ENET_INF_TYPE    enet_inf_rmii
#define ENET             HPM_ENET1
#define ENET_ID          (1UL)
#define ENET_INT_REF_CLK (1UL)
#endif

#define ENET_TX_BUFF_COUNT  (10U)
#define ENET_RX_BUFF_COUNT  (20U)
#define ENET_RX_BUFF_SIZE   ENET_MAX_FRAME_SIZE
#define ENET_TX_BUFF_SIZE   ENET_MAX_FRAME_SIZE

/* Exported Variables ------------------------------------------------------*/
extern enet_desc_t desc;

#endif /* LWIP_H */
