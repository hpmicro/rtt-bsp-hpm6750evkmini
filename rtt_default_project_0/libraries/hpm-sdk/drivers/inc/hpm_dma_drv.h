/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_DMA_DRV_H
#define HPM_DMA_DRV_H
#include "hpm_common.h"
#include "hpm_soc_feature.h"
#include "hpm_dma_regs.h"

#define DMA_NUM_TRANSFER_PER_BURST_1T           (0U)
#define DMA_NUM_TRANSFER_PER_BURST_2T           (1U)
#define DMA_NUM_TRANSFER_PER_BURST_4T           (2U)
#define DMA_NUM_TRANSFER_PER_BURST_8T           (3U)
#define DMA_NUM_TRANSFER_PER_BURST_16T          (4U)
#define DMA_NUM_TRANSFER_PER_BURST_32T          (5U)
#define DMA_NUM_TRANSFER_PER_BURST_64T          (6U)
#define DMA_NUM_TRANSFER_PER_BURST_128T         (7U)
#define DMA_NUM_TRANSFER_PER_BURST_256T         (8U)
#define DMA_NUM_TRANSFER_PER_BURST_512T         (9U)
#define DMA_NUM_TRANSFER_PER_BURST_1024T        (10U)

#define DMA_TRANSFER_WIDTH_BYTE                 (0U)
#define DMA_TRANSFER_WIDTH_HALF_WORD            (1U)
#define DMA_TRANSFER_WIDTH_WORD                 (2U)
#define DMA_TRANSFER_WIDTH_DOUBLE_WORD          (3U)
#define DMA_TRANSFER_WIDTH_QUAD_WORD            (4U)
#define DMA_TRANSFER_WIDTH_EIGHT_WORD           (5U)

#define DMA_STATUS_ERROR_SHIFT                  (0U)
#define DMA_STATUS_ABORT_SHIFT                  (8U)
#define DMA_STATUS_TC_SHIFT                     (16U)

#define DMA_HANDSHAKE_MODE_HANDSHAKE (1U)
#define DMA_HANDSHAKE_MODE_NORMAL (0U)

#define DMA_ADDRESS_CONTROL_INCREMENT (0U)
#define DMA_ADDRESS_CONTROL_DECREMENT (1U)
#define DMA_ADDRESS_CONTROL_FIXED (2U)

#define DMA_INTERRUPT_MASK_NONE (0U)
#define DMA_INTERRUPT_MASK_ERROR  DMA_CHCTRL_CTRL_INTERRMASK_MASK
#define DMA_INTERRUPT_MASK_ABORT  DMA_CHCTRL_CTRL_INTABTMASK_MASK
#define DMA_INTERRUPT_MASK_TERMINAL_COUNT DMA_CHCTRL_CTRL_INTTCMASK_MASK
#define DMA_INTERRUPT_MASK_ALL \
    (uint8_t)(DMA_INTERRUPT_MASK_TERMINAL_COUNT \
            | DMA_INTERRUPT_MASK_ABORT \
            | DMA_INTERRUPT_MASK_ERROR)

#ifndef DMA_SUPPORT_64BIT_ADDR
#define DMA_SUPPORT_64BIT_ADDR (0)
#endif

typedef struct dma_linked_descriptor {
    uint32_t ctrl;
    uint32_t trans_size;
    uint32_t src_addr;
    uint32_t src_addr_high;
    uint32_t dst_addr;
    uint32_t dst_addr_high;
    uint32_t linked_ptr;
    uint32_t linked_ptr_high;
} dma_linked_descriptor_t;

typedef struct dma_channel_config {
    uint8_t priority;               /* channel priority */
    uint8_t src_burst_size;         /* source burst size */
    uint8_t dma_mode;               /* source work mode */
    uint8_t src_width;              /* source width */
    uint8_t dst_width;              /* destination width */
    uint8_t src_addr_ctrl;          /* source address control */
    uint8_t dst_addr_ctrl;          /* destination address control */
    uint16_t interrupt_mask;        /* interrupt mask */
    uint32_t src_addr;              /* source address */
    uint32_t dst_addr;              /* destination address */
    uint32_t linked_ptr;            /* next linked descriptor */
    uint32_t size_in_byte;          /* total size to be transfered in byte */
#if DMA_SUPPORT_64BIT_ADDR
    uint32_t src_addr_high;
    uint32_t dst_addr_high;
    uint32_t linked_ptr_high;
#endif
} dma_channel_config_t;

enum {
    status_dma_transfer_done = MAKE_STATUS(status_group_dma, 0),
    status_dma_transfer_error = MAKE_STATUS(status_group_dma, 1),
    status_dma_transfer_abort = MAKE_STATUS(status_group_dma, 2),
    status_dma_transfer_ongoing = MAKE_STATUS(status_group_dma, 3),
    status_dma_alignment_error = MAKE_STATUS(status_group_dma, 4),
};

#ifdef __cplusplus
extern "C" {
#endif

static inline void dma_reset(DMA_Type *ptr)
{
    ptr->DMACTRL |= DMA_DMACTRL_RESET_MASK;
}

static inline hpm_stat_t dma_enable_channel(DMA_Type *ptr, uint32_t ch_num)
{
    ptr->CHCTRL[ch_num].CTRL |= DMA_CHCTRL_CTRL_ENABLE_MASK;

    if ((ptr->CHEN == 0) || !(ptr->CHEN & 1 << ch_num)) {
        return status_fail;
    }
    return status_success;
}

static inline void dma_abort_channel(DMA_Type *ptr, uint32_t ch_num_mask)
{
    ptr->CHABORT |= DMA_CHABORT_CHABORT_SET(ch_num_mask);
}

static inline uint32_t dma_check_enabled_channel(DMA_Type *ptr,
                                                  uint32_t ch_num_mask)
{
    return (ch_num_mask & ptr->CHEN);
}

static inline bool dma_has_linked_pointer_configured(DMA_Type *ptr, uint32_t ch_num)
{
    return ptr->CHCTRL[ch_num].LLPOINTER != 0;
}

static inline hpm_stat_t dma_check_transfer_status(DMA_Type *ptr, uint8_t ch_num)
{
    volatile uint32_t tmp = ptr->INTSTATUS;
    ptr->INTSTATUS = tmp;
    if (tmp & (1 << (DMA_STATUS_TC_SHIFT + ch_num))) {
        return status_dma_transfer_done;
    }
    if (tmp & (1 << (DMA_STATUS_ERROR_SHIFT + ch_num))) {
        return status_dma_transfer_error;
    }
    if (tmp & (1 << (DMA_STATUS_ABORT_SHIFT + ch_num))) {
        return status_dma_transfer_abort;
    }
    return status_dma_transfer_ongoing;
}

void dma_default_channel_config(DMA_Type *ptr, dma_channel_config_t *ch);

hpm_stat_t dma_setup_channel(DMA_Type *ptr, uint32_t ch_num,
                            dma_channel_config_t *ch);

/*
 * start memory copy
 * note: dst, src, size should be aligned with burst_len_in_byte
 */
hpm_stat_t dma_start_memcpy(DMA_Type *ptr, uint8_t ch_num,
                               uint32_t dst, uint32_t src,
                               uint32_t size, uint32_t burst_len_in_byte);

#ifdef __cplusplus
}
#endif
#endif /* HPM_DMA_DRV_H */
