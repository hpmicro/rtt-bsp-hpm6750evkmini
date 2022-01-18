/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_SDXC_H
#define HPM_SDXC_H

typedef struct {
    __RW uint32_t SDMASA;                      /* 0x0:  */
    __RW uint32_t BLK_ATTR;                    /* 0x4:  */
    __RW uint32_t CMD_ARG;                     /* 0x8:  */
    __RW uint32_t CMD_XFER;                    /* 0xC:  */
    __R  uint32_t RESP[4];                     /* 0x10 - 0x1C:  */
    __RW uint32_t BUF_DATA;                    /* 0x20:  */
    __R  uint32_t PSTATE;                      /* 0x24:  */
    __RW uint32_t PROT_CTRL;                   /* 0x28:  */
    __RW uint32_t SYS_CTRL;                    /* 0x2C:  */
    __RW uint32_t INT_STAT;                    /* 0x30:  */
    __RW uint32_t INT_STAT_EN;                 /* 0x34:  */
    __RW uint32_t INT_SIGNAL_EN;               /* 0x38:  */
    __RW uint32_t AC_HOST_CTRL;                /* 0x3C:  */
    __R  uint32_t CAPABILITIES1;               /* 0x40:  */
    __R  uint32_t CAPABILITIES2;               /* 0x44:  */
    __R  uint32_t CURR_CAPABILITIES1;          /* 0x48:  */
    __R  uint32_t CURR_CAPABILITIES2;          /* 0x4C:  */
    __RW uint32_t FORCE_EVENT;                 /* 0x50:  */
    __R  uint32_t ADMA_ERR_STAT;               /* 0x54:  */
    __RW uint32_t ADMA_SYS_ADDR;               /* 0x58:  */
    __R  uint8_t  RESERVED0[4];                /* 0x5C - 0x5F: Reserved */
    __R  uint16_t PRESET[11];                  /* 0x60 - 0x74:  */
    __R  uint8_t  RESERVED1[2];                /* 0x76 - 0x77: Reserved */
    __RW uint32_t ADMA_ID_ADDR;                /* 0x78:  */
    __R  uint8_t  RESERVED2[106];              /* 0x7C - 0xE5: Reserved */
    __R  uint16_t P_EMBEDDED_CNTRL;            /* 0xE6:  */
    __R  uint16_t P_VENDOR_SPECIFIC_AREA;      /* 0xE8:  */
    __R  uint16_t P_VENDOR2_SPECIFIC_AREA;     /* 0xEA:  */
    __R  uint8_t  RESERVED3[16];               /* 0xEC - 0xFB: Reserved */
    __R  uint16_t SLOT_INTR_STATUS;            /* 0xFC:  */
    __R  uint16_t HOST_CTRL_VERS;              /* 0xFE:  */
    __R  uint8_t  RESERVED4[128];              /* 0x100 - 0x17F: Reserved */
    __R  uint32_t CQVER;                       /* 0x180:  */
    __R  uint32_t CQCAP;                       /* 0x184:  */
    __RW uint32_t CQCFG;                       /* 0x188:  */
    __RW uint32_t CQCTL;                       /* 0x18C:  */
    __RW uint32_t CQIS;                        /* 0x190:  */
    __RW uint32_t CQISE;                       /* 0x194:  */
    __RW uint32_t CQISGE;                      /* 0x198:  */
    __RW uint32_t CQIC;                        /* 0x19C:  */
    __RW uint32_t CQTDLBA;                     /* 0x1A0:  */
    __R  uint8_t  RESERVED5[4];                /* 0x1A4 - 0x1A7: Reserved */
    __RW uint32_t CQTDBR;                      /* 0x1A8:  */
    __RW uint32_t CQTCN;                       /* 0x1AC:  */
    __RW uint32_t CQDQS;                       /* 0x1B0:  */
    __RW uint32_t CQDPT;                       /* 0x1B4:  */
    __RW uint32_t CQTCLR;                      /* 0x1B8:  */
    __R  uint8_t  RESERVED6[4];                /* 0x1BC - 0x1BF: Reserved */
    __RW uint32_t CQSSC1;                      /* 0x1C0:  */
    __RW uint32_t CQSSC2;                      /* 0x1C4:  */
    __R  uint32_t CQCRDCT;                     /* 0x1C8:  */
    __R  uint8_t  RESERVED7[4];                /* 0x1CC - 0x1CF: Reserved */
    __RW uint32_t CQRMEM;                      /* 0x1D0:  */
    __R  uint32_t CQTERRI;                     /* 0x1D4:  */
    __R  uint32_t CQCRI;                       /* 0x1D8:  */
    __R  uint32_t CQCRA;                       /* 0x1DC:  */
    __R  uint8_t  RESERVED8[800];              /* 0x1E0 - 0x4FF: Reserved */
    __R  uint32_t MSHC_VER_ID;                 /* 0x500:  */
    __R  uint32_t MSHC_VER_TYPE;               /* 0x504:  */
    __RW uint32_t MSHC_CTRL;                   /* 0x508:  */
    __R  uint8_t  RESERVED9[4];                /* 0x50C - 0x50F: Reserved */
    __RW uint32_t MBIU_CTRL;                   /* 0x510:  */
    __R  uint8_t  RESERVED10[24];              /* 0x514 - 0x52B: Reserved */
    __RW uint32_t EMMC_BOOT_CTRL;              /* 0x52C:  */
    __R  uint8_t  RESERVED11[16];              /* 0x530 - 0x53F: Reserved */
    __RW uint32_t AUTO_TUNING_CTRL;            /* 0x540:  */
    __RW uint32_t AUTO_TUNING_STAT;            /* 0x544:  */
    __R  uint8_t  RESERVED12[2596];            /* 0x548 - 0xF6B: Reserved */
    __RW uint32_t EMBEDDED_CTRL;               /* 0xF6C:  */
} SDXC_Type;


/* Bitfield definition for register: SDMASA */
/*
 * BLOCKCNT_SDMASA (RW)
 *
 * 32-bit Block Count (SDMA System Address)
 * - SDMA System Address (Host Version 4 Enable = 0): This register contains the system memory address for an SDMA transfer in the 32-bit addressing mode. When the Host Controller stops an SDMA transfer, this register points to the system address of the next contiguous data position. It can be accessed only if no transaction is executing. Reading this register during data transfers may
 * return an invalid value.
 * - 32-bit Block Count (Host Version 4 Enable = 1): From the Host Controller Version 4.10 specification, this register is redefined as 32-bit Block Count. The Host Controller decrements the block count of this register for every block transfer and the data transfer stops when the count reaches zero. This register must be accessed when no transaction is executing. Reading this register during data transfers may return invalid value.
 * Following are the values for BLOCKCNT_SDMASA:
 * - 0xFFFF_FFFF: 4G - 1 Block 
 * - 
 * - 0x0000_0002: 2 Blocks
 * - 0x0000_0001: 1 Block
 * - 0x0000_0000: Stop Count
 * Note: 
 * - For Host Version 4 Enable = 0, the Host driver does not program the system address in this register while operating in ADMA mode. The system address must be programmed in the ADMA System Address register.
 * - For Host Version 4 Enable = 0, the Host driver programs a non-zero 32-bit block count value in this register when Auto CMD23 is enabled for non-DMA and ADMA modes. Auto CMD23 cannot be used with SDMA.
 * - This register must be programmed with a non-zero value for data transfer if the 32-bit Block count register is used instead of the 16-bit Block count register.
 */
#define SDXC_SDMASA_BLOCKCNT_SDMASA_MASK (0xFFFFFFFFUL)
#define SDXC_SDMASA_BLOCKCNT_SDMASA_SHIFT (0U)
#define SDXC_SDMASA_BLOCKCNT_SDMASA_SET(x) (((uint32_t)(x) << SDXC_SDMASA_BLOCKCNT_SDMASA_SHIFT) & SDXC_SDMASA_BLOCKCNT_SDMASA_MASK)
#define SDXC_SDMASA_BLOCKCNT_SDMASA_GET(x) (((uint32_t)(x) & SDXC_SDMASA_BLOCKCNT_SDMASA_MASK) >> SDXC_SDMASA_BLOCKCNT_SDMASA_SHIFT)

/* Bitfield definition for register: BLK_ATTR */
/*
 * BLOCK_CNT (RW)
 *
 * 16-bit Block Count
 * - If the Host Version 4 Enable bit is set 0 or the 16-bit Block Count register is set to non-zero, the 16-bit Block Count register is selected.
 * - If the Host Version 4 Enable bit is set 1 and the 16-bit Block Count register is set to zero, the 32-bit Block Count register is selected.
 * Following are the values for BLOCK_CNT:
 * - 0x0: Stop Count
 * - 0x1: 1 Block
 * - 0x2: 2 Blocks 
 * - .
 * - 0xFFFF: 65535 Blocks
 * Note: For Host Version 4 Enable = 0, this register must be set to 0000h before programming the 32-bit block count register when Auto CMD23 is enabled for non-DMA and ADMA modes.
 */
#define SDXC_BLK_ATTR_BLOCK_CNT_MASK (0xFFFF0000UL)
#define SDXC_BLK_ATTR_BLOCK_CNT_SHIFT (16U)
#define SDXC_BLK_ATTR_BLOCK_CNT_SET(x) (((uint32_t)(x) << SDXC_BLK_ATTR_BLOCK_CNT_SHIFT) & SDXC_BLK_ATTR_BLOCK_CNT_MASK)
#define SDXC_BLK_ATTR_BLOCK_CNT_GET(x) (((uint32_t)(x) & SDXC_BLK_ATTR_BLOCK_CNT_MASK) >> SDXC_BLK_ATTR_BLOCK_CNT_SHIFT)

/*
 * SDMA_BUF_BDARY (RW)
 *
 * SDMA Buffer Boundary
 * These bits specify the size of contiguous buffer in system memory. The SDMA transfer waits at every boundary specified by these fields and the Host Controller generates the DMA interrupt to request the Host Driver to update the SDMA System Address register.
 * Values: 
 * - 0x0 (BYTES_4K): 4K bytes SDMA Buffer Boundary
 * - 0x1 (BYTES_8K): 8K bytes SDMA Buffer Boundary
 * - 0x2 (BYTES_16K): 16K bytes SDMA Buffer Boundary
 * - 0x3 (BYTES_32K): 32K bytes SDMA Buffer Boundary
 * - 0x4 (BYTES_64K): 64K bytes SDMA Buffer Boundary
 * - 0x5 (BYTES_128K): 128K bytes SDMA Buffer Boundary
 * - 0x6 (BYTES_256K): 256K bytes SDMA Buffer Boundary
 * - 0x7 (BYTES_512K): 512K bytes SDMA Buffer Boundary
 */
#define SDXC_BLK_ATTR_SDMA_BUF_BDARY_MASK (0x7000U)
#define SDXC_BLK_ATTR_SDMA_BUF_BDARY_SHIFT (12U)
#define SDXC_BLK_ATTR_SDMA_BUF_BDARY_SET(x) (((uint32_t)(x) << SDXC_BLK_ATTR_SDMA_BUF_BDARY_SHIFT) & SDXC_BLK_ATTR_SDMA_BUF_BDARY_MASK)
#define SDXC_BLK_ATTR_SDMA_BUF_BDARY_GET(x) (((uint32_t)(x) & SDXC_BLK_ATTR_SDMA_BUF_BDARY_MASK) >> SDXC_BLK_ATTR_SDMA_BUF_BDARY_SHIFT)

/*
 * XFER_BLOCK_SIZE (RW)
 *
 * Transfer Block Size
 * These bits specify the block size of data transfers. In case of memory, it is set to 512 bytes. It can be accessed only if no transaction is executing. Read operations during transfers may return an invalid value, and write operations are ignored. Following are the values for XFER_BLOCK_SIZE:
 * - 0x1: 1 byte
 * - 0x2: 2 bytes
 * - 0x3: 3 bytes
 * - .
 * - 0x1FF: 511 byte
 * - 0x200: 512 byt es
 * - .
 * - 0x800: 2048 bytes
 * Note: This register must be programmed with a non-zero value for data transfer.
 */
#define SDXC_BLK_ATTR_XFER_BLOCK_SIZE_MASK (0xFFFU)
#define SDXC_BLK_ATTR_XFER_BLOCK_SIZE_SHIFT (0U)
#define SDXC_BLK_ATTR_XFER_BLOCK_SIZE_SET(x) (((uint32_t)(x) << SDXC_BLK_ATTR_XFER_BLOCK_SIZE_SHIFT) & SDXC_BLK_ATTR_XFER_BLOCK_SIZE_MASK)
#define SDXC_BLK_ATTR_XFER_BLOCK_SIZE_GET(x) (((uint32_t)(x) & SDXC_BLK_ATTR_XFER_BLOCK_SIZE_MASK) >> SDXC_BLK_ATTR_XFER_BLOCK_SIZE_SHIFT)

/* Bitfield definition for register: CMD_ARG */
/*
 * ARGUMNET (RW)
 *
 * Command Argument
 * These bits specify the SD/eMMC command argument that is specified in bits 39-8 of the Command format.
 */
#define SDXC_CMD_ARG_ARGUMNET_MASK (0xFFFFFFFFUL)
#define SDXC_CMD_ARG_ARGUMNET_SHIFT (0U)
#define SDXC_CMD_ARG_ARGUMNET_SET(x) (((uint32_t)(x) << SDXC_CMD_ARG_ARGUMNET_SHIFT) & SDXC_CMD_ARG_ARGUMNET_MASK)
#define SDXC_CMD_ARG_ARGUMNET_GET(x) (((uint32_t)(x) & SDXC_CMD_ARG_ARGUMNET_MASK) >> SDXC_CMD_ARG_ARGUMNET_SHIFT)

/* Bitfield definition for register: CMD_XFER */
/*
 * CMD_INDEX (RW)
 *
 * Command Index
 * These bits are set to the command number that is specified in bits 45-40 of the Command Format.
 */
#define SDXC_CMD_XFER_CMD_INDEX_MASK (0x3F000000UL)
#define SDXC_CMD_XFER_CMD_INDEX_SHIFT (24U)
#define SDXC_CMD_XFER_CMD_INDEX_SET(x) (((uint32_t)(x) << SDXC_CMD_XFER_CMD_INDEX_SHIFT) & SDXC_CMD_XFER_CMD_INDEX_MASK)
#define SDXC_CMD_XFER_CMD_INDEX_GET(x) (((uint32_t)(x) & SDXC_CMD_XFER_CMD_INDEX_MASK) >> SDXC_CMD_XFER_CMD_INDEX_SHIFT)

/*
 * CMD_TYPE (RW)
 *
 * Command Type
 * These bits indicate the command type. 
 * Note: While issuing Abort CMD using CMD12/CMD52 or reset CMD using CMD0/CMD52, CMD_TYPE field shall be set to 0x3.
 * Values: 
 * 0x3 (ABORT_CMD): Abort
 * 0x2 (RESUME_CMD): Resume
 * 0x1 (SUSPEND_CMD): Suspend
 * 0x0 (NORMAL_CMD): Normal
 */
#define SDXC_CMD_XFER_CMD_TYPE_MASK (0xC00000UL)
#define SDXC_CMD_XFER_CMD_TYPE_SHIFT (22U)
#define SDXC_CMD_XFER_CMD_TYPE_SET(x) (((uint32_t)(x) << SDXC_CMD_XFER_CMD_TYPE_SHIFT) & SDXC_CMD_XFER_CMD_TYPE_MASK)
#define SDXC_CMD_XFER_CMD_TYPE_GET(x) (((uint32_t)(x) & SDXC_CMD_XFER_CMD_TYPE_MASK) >> SDXC_CMD_XFER_CMD_TYPE_SHIFT)

/*
 * DATA_PRESENT_SEL (RW)
 *
 * Data Present Select
 * This bit is set to 1 to indicate that data is present and that the data is transferred using the DAT line. This bit is set to 0 in the following instances:
 * Command using the CMD line
 * Command with no data transfer but using busy signal on the DAT[0] line
 * Resume Command 
 * Values: 
 * 0x0 (NO_DATA): No Data Present
 * 0x1 (DATA): Data Present
 */
#define SDXC_CMD_XFER_DATA_PRESENT_SEL_MASK (0x200000UL)
#define SDXC_CMD_XFER_DATA_PRESENT_SEL_SHIFT (21U)
#define SDXC_CMD_XFER_DATA_PRESENT_SEL_SET(x) (((uint32_t)(x) << SDXC_CMD_XFER_DATA_PRESENT_SEL_SHIFT) & SDXC_CMD_XFER_DATA_PRESENT_SEL_MASK)
#define SDXC_CMD_XFER_DATA_PRESENT_SEL_GET(x) (((uint32_t)(x) & SDXC_CMD_XFER_DATA_PRESENT_SEL_MASK) >> SDXC_CMD_XFER_DATA_PRESENT_SEL_SHIFT)

/*
 * CMD_IDX_CHK_ENABLE (RW)
 *
 * Command Index Check Enable
 * This bit enables the Host Controller to check the index field in the response to verify if it has the same value as the command index. If the value is not the same, it is reported as a Command Index error.
 * Note: 
 * Index Check enable must be set to 0 for the command with no response, R2 response, R3 response and R4 response.
 * For the tuning command, this bit must always be set to enable the index check.
 * Values: 
 * 0x0 (DISABLED): Disable
 * 0x1 (ENABLED): Enable
 */
#define SDXC_CMD_XFER_CMD_IDX_CHK_ENABLE_MASK (0x100000UL)
#define SDXC_CMD_XFER_CMD_IDX_CHK_ENABLE_SHIFT (20U)
#define SDXC_CMD_XFER_CMD_IDX_CHK_ENABLE_SET(x) (((uint32_t)(x) << SDXC_CMD_XFER_CMD_IDX_CHK_ENABLE_SHIFT) & SDXC_CMD_XFER_CMD_IDX_CHK_ENABLE_MASK)
#define SDXC_CMD_XFER_CMD_IDX_CHK_ENABLE_GET(x) (((uint32_t)(x) & SDXC_CMD_XFER_CMD_IDX_CHK_ENABLE_MASK) >> SDXC_CMD_XFER_CMD_IDX_CHK_ENABLE_SHIFT)

/*
 * CMD_CRC_CHK_ENABLE (RW)
 *
 * Command CRC Check Enable
 * This bit enables the Host Controller to check the CRC field in the response. If an error is detected, it is reported as a Command CRC error.
 * Note: 
 * CRC Check enable must be set to 0 for the command with no response, R3 response, and R4 response.
 * For the tuning command, this bit must always be set to 1 to enable the CRC check.
 * Values: 
 * 0x0 (DISABLED): Disable
 * 0x1 (ENABLED): Enable
 */
#define SDXC_CMD_XFER_CMD_CRC_CHK_ENABLE_MASK (0x80000UL)
#define SDXC_CMD_XFER_CMD_CRC_CHK_ENABLE_SHIFT (19U)
#define SDXC_CMD_XFER_CMD_CRC_CHK_ENABLE_SET(x) (((uint32_t)(x) << SDXC_CMD_XFER_CMD_CRC_CHK_ENABLE_SHIFT) & SDXC_CMD_XFER_CMD_CRC_CHK_ENABLE_MASK)
#define SDXC_CMD_XFER_CMD_CRC_CHK_ENABLE_GET(x) (((uint32_t)(x) & SDXC_CMD_XFER_CMD_CRC_CHK_ENABLE_MASK) >> SDXC_CMD_XFER_CMD_CRC_CHK_ENABLE_SHIFT)

/*
 * SUB_CMD_FLAG (RW)
 *
 * Sub Command Flag
 * This bit distinguishes between a main command and a sub command.
 * Values: 
 * 0x0 (MAIN): Main Command
 * 0x1 (SUB): Sub Command
 */
#define SDXC_CMD_XFER_SUB_CMD_FLAG_MASK (0x40000UL)
#define SDXC_CMD_XFER_SUB_CMD_FLAG_SHIFT (18U)
#define SDXC_CMD_XFER_SUB_CMD_FLAG_SET(x) (((uint32_t)(x) << SDXC_CMD_XFER_SUB_CMD_FLAG_SHIFT) & SDXC_CMD_XFER_SUB_CMD_FLAG_MASK)
#define SDXC_CMD_XFER_SUB_CMD_FLAG_GET(x) (((uint32_t)(x) & SDXC_CMD_XFER_SUB_CMD_FLAG_MASK) >> SDXC_CMD_XFER_SUB_CMD_FLAG_SHIFT)

/*
 * RESP_TYPE_SELECT (RW)
 *
 * Response Type Select
 * This bit indicates the type of response expected from the card.
 * Values: 
 * 0x0 (NO_RESP): No Response
 * 0x1 (RESP_LEN_136): Response Length 136
 * 0x2 (RESP_LEN_48): Response Length 48
 * 0x3 (RESP_LEN_48B): Response Length 48; Check Busy after response
 */
#define SDXC_CMD_XFER_RESP_TYPE_SELECT_MASK (0x30000UL)
#define SDXC_CMD_XFER_RESP_TYPE_SELECT_SHIFT (16U)
#define SDXC_CMD_XFER_RESP_TYPE_SELECT_SET(x) (((uint32_t)(x) << SDXC_CMD_XFER_RESP_TYPE_SELECT_SHIFT) & SDXC_CMD_XFER_RESP_TYPE_SELECT_MASK)
#define SDXC_CMD_XFER_RESP_TYPE_SELECT_GET(x) (((uint32_t)(x) & SDXC_CMD_XFER_RESP_TYPE_SELECT_MASK) >> SDXC_CMD_XFER_RESP_TYPE_SELECT_SHIFT)

/*
 * RESP_INT_DISABLE (RW)
 *
 * Response Interrupt Disable
 * The Host Controller supports response check function to avoid overhead of response error check by the Host driver. Response types of only R1 and R5 can be checked by the Controller.
 * If Host Driver checks the response error, set this bit to 0 and wait for Command Complete Interrupt and then check the response register.
 * If the Host Controller checks the response error, set this bit to 1 and set the Response Error Check Enable bit to 1. The Command Complete Interrupt is disabled by this bit regardless of the Command Complete Signal Enable.
 * Note: During tuning (when the Execute Tuning bit in the Host Control2 register is set), the Command Complete Interrupt is not generated irrespective of the Response Interrupt Disable setting.
 * Values: 
 * - 0x0 (ENABLED): Response Interrupt is enabled
 * - 0x1 (DISABLED): Response Interrupt is disabled
 */
#define SDXC_CMD_XFER_RESP_INT_DISABLE_MASK (0x100U)
#define SDXC_CMD_XFER_RESP_INT_DISABLE_SHIFT (8U)
#define SDXC_CMD_XFER_RESP_INT_DISABLE_SET(x) (((uint32_t)(x) << SDXC_CMD_XFER_RESP_INT_DISABLE_SHIFT) & SDXC_CMD_XFER_RESP_INT_DISABLE_MASK)
#define SDXC_CMD_XFER_RESP_INT_DISABLE_GET(x) (((uint32_t)(x) & SDXC_CMD_XFER_RESP_INT_DISABLE_MASK) >> SDXC_CMD_XFER_RESP_INT_DISABLE_SHIFT)

/*
 * RESP_ERR_CHK_ENABLE (RW)
 *
 * Response Error Check Enable
 * The Host Controller supports response check function to avoid overhead of response error check by Host driver. Response types of only R1 and R5 can be checked by the Controller. If the Host Controller checks the response error, set this bit to 1 and set Response Interrupt Disable to 1. If an error is detected, the Response Error interrupt is generated in the Error Interrupt Status register.
 * Note: 
 * - Response error check must not be enabled for any response type other than R1 and R5. 
 * - Response check must not be enabled for the tuning command.
 * Values: 
 * - 0x0 (DISABLED): Response Error Check is disabled
 * - 0x1 (ENABLED): Response Error Check is enabled
 */
#define SDXC_CMD_XFER_RESP_ERR_CHK_ENABLE_MASK (0x80U)
#define SDXC_CMD_XFER_RESP_ERR_CHK_ENABLE_SHIFT (7U)
#define SDXC_CMD_XFER_RESP_ERR_CHK_ENABLE_SET(x) (((uint32_t)(x) << SDXC_CMD_XFER_RESP_ERR_CHK_ENABLE_SHIFT) & SDXC_CMD_XFER_RESP_ERR_CHK_ENABLE_MASK)
#define SDXC_CMD_XFER_RESP_ERR_CHK_ENABLE_GET(x) (((uint32_t)(x) & SDXC_CMD_XFER_RESP_ERR_CHK_ENABLE_MASK) >> SDXC_CMD_XFER_RESP_ERR_CHK_ENABLE_SHIFT)

/*
 * RESP_TYPE (RW)
 *
 * Response Type R1/R5
 * This bit selects either R1 or R5 as a response type when the Response Error Check is selected.
 * Error statuses checked in R1:
 * OUT_OF_RANGE
 * ADDRESS_ERROR
 * BLOCK_LEN_ERROR
 * WP_VIOLATION
 * CARD_IS_LOCKED
 * COM_CRC_ERROR
 * CARD_ECC_FAILED
 * CC_ERROR
 * ERROR
 * Response Flags checked in R5:
 * COM_CRC_ERROR
 * ERROR
 * FUNCTION_NUMBER
 * OUT_OF_RANGE
 * Values: 
 * 0x0 (RESP_R1): R1 (Memory)
 * 0x1 (RESP_R5): R5 (SDIO)
 */
#define SDXC_CMD_XFER_RESP_TYPE_MASK (0x40U)
#define SDXC_CMD_XFER_RESP_TYPE_SHIFT (6U)
#define SDXC_CMD_XFER_RESP_TYPE_SET(x) (((uint32_t)(x) << SDXC_CMD_XFER_RESP_TYPE_SHIFT) & SDXC_CMD_XFER_RESP_TYPE_MASK)
#define SDXC_CMD_XFER_RESP_TYPE_GET(x) (((uint32_t)(x) & SDXC_CMD_XFER_RESP_TYPE_MASK) >> SDXC_CMD_XFER_RESP_TYPE_SHIFT)

/*
 * MULTI_BLK_SEL (RW)
 *
 * Multi/Single Block Select
 * This bit is set when issuing multiple-block transfer commands using the DAT line. If this bit is set to 0, it is not necessary to set the Block Count register.
 * Values: 
 * 0x0 (SINGLE): Single Block
 * 0x1 (MULTI): Multiple Block
 */
#define SDXC_CMD_XFER_MULTI_BLK_SEL_MASK (0x20U)
#define SDXC_CMD_XFER_MULTI_BLK_SEL_SHIFT (5U)
#define SDXC_CMD_XFER_MULTI_BLK_SEL_SET(x) (((uint32_t)(x) << SDXC_CMD_XFER_MULTI_BLK_SEL_SHIFT) & SDXC_CMD_XFER_MULTI_BLK_SEL_MASK)
#define SDXC_CMD_XFER_MULTI_BLK_SEL_GET(x) (((uint32_t)(x) & SDXC_CMD_XFER_MULTI_BLK_SEL_MASK) >> SDXC_CMD_XFER_MULTI_BLK_SEL_SHIFT)

/*
 * DATA_XFER_DIR (RW)
 *
 * Data Transfer Direction Select
 * This bit defines the direction of DAT line data transfers. This bit is set to 1 by the Host Driver to transfer data from the SD/eMMC card to the Host Controller and it is set to 0 for all other commands.
 * Values: 
 * 0x1 (READ): Read (Card to Host)
 * 0x0 (WRITE): Write (Host to Card)
 */
#define SDXC_CMD_XFER_DATA_XFER_DIR_MASK (0x10U)
#define SDXC_CMD_XFER_DATA_XFER_DIR_SHIFT (4U)
#define SDXC_CMD_XFER_DATA_XFER_DIR_SET(x) (((uint32_t)(x) << SDXC_CMD_XFER_DATA_XFER_DIR_SHIFT) & SDXC_CMD_XFER_DATA_XFER_DIR_MASK)
#define SDXC_CMD_XFER_DATA_XFER_DIR_GET(x) (((uint32_t)(x) & SDXC_CMD_XFER_DATA_XFER_DIR_MASK) >> SDXC_CMD_XFER_DATA_XFER_DIR_SHIFT)

/*
 * AUTO_CMD_ENABLE (RW)
 *
 * Auto Command Enable
 * This field determines use of Auto Command functions.
 * Note: In SDIO, this field must be set as 00b (Auto Command Disabled).
 * Values: 
 * 0x0 (AUTO_CMD_DISABLED): Auto Command Disabled
 * 0x1 (AUTO_CMD12_ENABLED): Auto CMD12 Enable
 * 0x2 (AUTO_CMD23_ENABLED): Auto CMD23 Enable
 * 0x3 (AUTO_CMD_AUTO_SEL): Auto CMD Auto Sel
 */
#define SDXC_CMD_XFER_AUTO_CMD_ENABLE_MASK (0xCU)
#define SDXC_CMD_XFER_AUTO_CMD_ENABLE_SHIFT (2U)
#define SDXC_CMD_XFER_AUTO_CMD_ENABLE_SET(x) (((uint32_t)(x) << SDXC_CMD_XFER_AUTO_CMD_ENABLE_SHIFT) & SDXC_CMD_XFER_AUTO_CMD_ENABLE_MASK)
#define SDXC_CMD_XFER_AUTO_CMD_ENABLE_GET(x) (((uint32_t)(x) & SDXC_CMD_XFER_AUTO_CMD_ENABLE_MASK) >> SDXC_CMD_XFER_AUTO_CMD_ENABLE_SHIFT)

/*
 * BLOCK_COUNT_ENABLE (RW)
 *
 * Block Count Enable
 * This bit is used to enable the Block Count register, which is relevant for multiple block transfers. If this bit is set to 0, the Block Count register is disabled, which is useful in executing an infinite transfer. The Host Driver must set this bit to 0 when ADMA is used.
 * Values: 
 * 0x1 (ENABLED): Enable
 * 0x0 (DISABLED): Disable
 */
#define SDXC_CMD_XFER_BLOCK_COUNT_ENABLE_MASK (0x2U)
#define SDXC_CMD_XFER_BLOCK_COUNT_ENABLE_SHIFT (1U)
#define SDXC_CMD_XFER_BLOCK_COUNT_ENABLE_SET(x) (((uint32_t)(x) << SDXC_CMD_XFER_BLOCK_COUNT_ENABLE_SHIFT) & SDXC_CMD_XFER_BLOCK_COUNT_ENABLE_MASK)
#define SDXC_CMD_XFER_BLOCK_COUNT_ENABLE_GET(x) (((uint32_t)(x) & SDXC_CMD_XFER_BLOCK_COUNT_ENABLE_MASK) >> SDXC_CMD_XFER_BLOCK_COUNT_ENABLE_SHIFT)

/*
 * DMA_ENABLE (RW)
 *
 * DMA Enable
 * This bit enables the DMA functionality. If this bit is set to 1, a DMA operation begins when the Host Driver writes to the Command register. You can select one of the DMA modes by using DMA Select in the Host Control 1 register.
 * Values: 
 * 0x1 (ENABLED): DMA Data transfer
 * 0x0 (DISABLED): No data transfer or Non-DMA data transfer
 */
#define SDXC_CMD_XFER_DMA_ENABLE_MASK (0x1U)
#define SDXC_CMD_XFER_DMA_ENABLE_SHIFT (0U)
#define SDXC_CMD_XFER_DMA_ENABLE_SET(x) (((uint32_t)(x) << SDXC_CMD_XFER_DMA_ENABLE_SHIFT) & SDXC_CMD_XFER_DMA_ENABLE_MASK)
#define SDXC_CMD_XFER_DMA_ENABLE_GET(x) (((uint32_t)(x) & SDXC_CMD_XFER_DMA_ENABLE_MASK) >> SDXC_CMD_XFER_DMA_ENABLE_SHIFT)

/* Bitfield definition for register array: RESP */
/*
 * RESP01 (R)
 *
 * Command Response 
 * These bits reflect 39-8 bits of SD/eMMC Response Field. In UHS-II mode, it stores the response of the TRANS_ABORT CCMD.
 * Note: For Auto CMD, the 32-bit response (bits 39-8 of the Response Field) is updated in the RESP67_R register.
 */
#define SDXC_RESP_RESP01_MASK (0xFFFFFFFFUL)
#define SDXC_RESP_RESP01_SHIFT (0U)
#define SDXC_RESP_RESP01_GET(x) (((uint32_t)(x) & SDXC_RESP_RESP01_MASK) >> SDXC_RESP_RESP01_SHIFT)

/* Bitfield definition for register: BUF_DATA */
/*
 * BUF_DATA (RW)
 *
 * 
 * Buffer Data
 * These bits enable access to the Host Controller packet buffer.
 * 
 */
#define SDXC_BUF_DATA_BUF_DATA_MASK (0xFFFFFFFFUL)
#define SDXC_BUF_DATA_BUF_DATA_SHIFT (0U)
#define SDXC_BUF_DATA_BUF_DATA_SET(x) (((uint32_t)(x) << SDXC_BUF_DATA_BUF_DATA_SHIFT) & SDXC_BUF_DATA_BUF_DATA_MASK)
#define SDXC_BUF_DATA_BUF_DATA_GET(x) (((uint32_t)(x) & SDXC_BUF_DATA_BUF_DATA_MASK) >> SDXC_BUF_DATA_BUF_DATA_SHIFT)

/* Bitfield definition for register: PSTATE */
/*
 * UHS2_IF_DETECT (R)
 *
 * UHS-II Interface Detection
 * This bit indicates whether a card supports the UHS-II interface. For SD/eMMC mode, this bit always returns 0.
 * Values: 
 * 0x0 (FALSE): UHS-II interface is not detected
 * 0x1 (TRUE): UHS-II interface is detected
 */
#define SDXC_PSTATE_UHS2_IF_DETECT_MASK (0x80000000UL)
#define SDXC_PSTATE_UHS2_IF_DETECT_SHIFT (31U)
#define SDXC_PSTATE_UHS2_IF_DETECT_GET(x) (((uint32_t)(x) & SDXC_PSTATE_UHS2_IF_DETECT_MASK) >> SDXC_PSTATE_UHS2_IF_DETECT_SHIFT)

/*
 * LANE_SYNC (R)
 *
 * Lane Synchronization
 * This bit indicates whether a lane is synchronized in the UHS-II mode. For SD/eMMC mode, this bit always returns 0.
 * Values: 
 * 0x0 (FALSE): UHS-II PHY is not initialized
 * 0x1 (TRUE): UHS-II PHY is initialized
 */
#define SDXC_PSTATE_LANE_SYNC_MASK (0x40000000UL)
#define SDXC_PSTATE_LANE_SYNC_SHIFT (30U)
#define SDXC_PSTATE_LANE_SYNC_GET(x) (((uint32_t)(x) & SDXC_PSTATE_LANE_SYNC_MASK) >> SDXC_PSTATE_LANE_SYNC_SHIFT)

/*
 * IN_DORMANT_ST (R)
 *
 * In Dormant Status
 * This bit indicates whether UHS-II lanes enter Dormant state in the UHS-II mode. For SD/eMMC mode, this bit always returns 0. 
 * Values: 
 * 0x0 (FALSE): Not in DORMANT state
 * 0x1 (TRUE): In DORMANT state
 */
#define SDXC_PSTATE_IN_DORMANT_ST_MASK (0x20000000UL)
#define SDXC_PSTATE_IN_DORMANT_ST_SHIFT (29U)
#define SDXC_PSTATE_IN_DORMANT_ST_GET(x) (((uint32_t)(x) & SDXC_PSTATE_IN_DORMANT_ST_MASK) >> SDXC_PSTATE_IN_DORMANT_ST_SHIFT)

/*
 * SUB_CMD_STAT (R)
 *
 * Sub Command Status
 * This bit is used to distinguish between a main command and a sub command status.
 * Values: 
 * 0x0 (FALSE): Main Command Status
 * 0x1 (TRUE): Sub Command Status
 */
#define SDXC_PSTATE_SUB_CMD_STAT_MASK (0x10000000UL)
#define SDXC_PSTATE_SUB_CMD_STAT_SHIFT (28U)
#define SDXC_PSTATE_SUB_CMD_STAT_GET(x) (((uint32_t)(x) & SDXC_PSTATE_SUB_CMD_STAT_MASK) >> SDXC_PSTATE_SUB_CMD_STAT_SHIFT)

/*
 * CMD_ISSUE_ERR (R)
 *
 * Command Not Issued by Error
 * This bit is set if a command cannot be issued after setting the command register due to an error except the Auto CMD12 error.
 * Values: 
 * 0x0 (FALSE): No error for issuing a command
 * 0x1 (TRUE): Command cannot be issued
 */
#define SDXC_PSTATE_CMD_ISSUE_ERR_MASK (0x8000000UL)
#define SDXC_PSTATE_CMD_ISSUE_ERR_SHIFT (27U)
#define SDXC_PSTATE_CMD_ISSUE_ERR_GET(x) (((uint32_t)(x) & SDXC_PSTATE_CMD_ISSUE_ERR_MASK) >> SDXC_PSTATE_CMD_ISSUE_ERR_SHIFT)

/*
 * HOST_REG_VOL (R)
 *
 * Host Regulator Voltage Stable
 * This bit is used to check whether the host regulator voltage is stable for switching the voltage of UHS-I mode. This bit reflects the synchronized value of the host_reg_vol_stable signal. 
 * Values: 
 * 0x0 (FALSE): Host Regulator Voltage is not stable
 * 0x1 (TRUE): Host Regulator Voltage is stable
 */
#define SDXC_PSTATE_HOST_REG_VOL_MASK (0x2000000UL)
#define SDXC_PSTATE_HOST_REG_VOL_SHIFT (25U)
#define SDXC_PSTATE_HOST_REG_VOL_GET(x) (((uint32_t)(x) & SDXC_PSTATE_HOST_REG_VOL_MASK) >> SDXC_PSTATE_HOST_REG_VOL_SHIFT)

/*
 * CMD_LINE_LVL (R)
 *
 * Command-Line Signal Level
 * This bit is used to check the CMD line level to recover from errors and for debugging. These bits reflect the value of the sd_cmd_in signal. This bit is irrelevant for an UHS-II mode and always returns 0.
 */
#define SDXC_PSTATE_CMD_LINE_LVL_MASK (0x1000000UL)
#define SDXC_PSTATE_CMD_LINE_LVL_SHIFT (24U)
#define SDXC_PSTATE_CMD_LINE_LVL_GET(x) (((uint32_t)(x) & SDXC_PSTATE_CMD_LINE_LVL_MASK) >> SDXC_PSTATE_CMD_LINE_LVL_SHIFT)

/*
 * DAT_3_0 (R)
 *
 * DAT[3:0] Line Signal Level
 * This bit is used to check the DAT line level to recover from errors and for debugging. These bits reflect the value of the sd_dat_in (lower nibble) signal. These bits are irrelevant for the UHS-II mode and always returns 0.
 */
#define SDXC_PSTATE_DAT_3_0_MASK (0xF00000UL)
#define SDXC_PSTATE_DAT_3_0_SHIFT (20U)
#define SDXC_PSTATE_DAT_3_0_GET(x) (((uint32_t)(x) & SDXC_PSTATE_DAT_3_0_MASK) >> SDXC_PSTATE_DAT_3_0_SHIFT)

/*
 * WR_PROTECT_SW_LVL (R)
 *
 * Write Protect Switch Pin Level
 * This bit is supported only for memory and combo cards. This bit reflects the synchronized value of the card_write_prot signal.
 * Values: 
 * 0x0 (FALSE): Write protected
 * 0x1 (TRUE): Write enabled
 */
#define SDXC_PSTATE_WR_PROTECT_SW_LVL_MASK (0x80000UL)
#define SDXC_PSTATE_WR_PROTECT_SW_LVL_SHIFT (19U)
#define SDXC_PSTATE_WR_PROTECT_SW_LVL_GET(x) (((uint32_t)(x) & SDXC_PSTATE_WR_PROTECT_SW_LVL_MASK) >> SDXC_PSTATE_WR_PROTECT_SW_LVL_SHIFT)

/*
 * CARD_DETECT_PIN_LEVEL (R)
 *
 * Card Detect Pin Level
 * This bit reflects the inverse synchronized value of the card_detect_n signal.
 * Values: 
 * 0x0 (FALSE): No card present
 * 0x1 (TRUE): Card Present
 */
#define SDXC_PSTATE_CARD_DETECT_PIN_LEVEL_MASK (0x40000UL)
#define SDXC_PSTATE_CARD_DETECT_PIN_LEVEL_SHIFT (18U)
#define SDXC_PSTATE_CARD_DETECT_PIN_LEVEL_GET(x) (((uint32_t)(x) & SDXC_PSTATE_CARD_DETECT_PIN_LEVEL_MASK) >> SDXC_PSTATE_CARD_DETECT_PIN_LEVEL_SHIFT)

/*
 * CARD_STABLE (R)
 *
 * Card Stable
 * This bit indicates the stability of the Card Detect Pin Level. A card is not detected if this bit is set to 1 and the value of the CARD_INSERTED bit is 0.
 * Values: 
 * 0x0 (FALSE): Reset or Debouncing
 * 0x1 (TRUE): No Card or Inserted
 */
#define SDXC_PSTATE_CARD_STABLE_MASK (0x20000UL)
#define SDXC_PSTATE_CARD_STABLE_SHIFT (17U)
#define SDXC_PSTATE_CARD_STABLE_GET(x) (((uint32_t)(x) & SDXC_PSTATE_CARD_STABLE_MASK) >> SDXC_PSTATE_CARD_STABLE_SHIFT)

/*
 * CARD_INSERTED (R)
 *
 * Card Inserted
 * This bit indicates whether a card has been inserted. The Host Controller debounces this signal so that Host Driver need not wait for it to stabilize.
 * Values: 
 * 0x0 (FALSE): Reset, Debouncing, or No card
 * 0x1 (TRUE): Card Inserted
 */
#define SDXC_PSTATE_CARD_INSERTED_MASK (0x10000UL)
#define SDXC_PSTATE_CARD_INSERTED_SHIFT (16U)
#define SDXC_PSTATE_CARD_INSERTED_GET(x) (((uint32_t)(x) & SDXC_PSTATE_CARD_INSERTED_MASK) >> SDXC_PSTATE_CARD_INSERTED_SHIFT)

/*
 * BUF_RD_ENABLE (R)
 *
 * Buffer Read Enable
 * This bit is used for non-DMA transfers. This bit is set if valid data exists in the Host buffer.
 * Values: 
 * 0x0 (DISABLED): Read disable
 * 0x1 (ENABLED): Read enable
 */
#define SDXC_PSTATE_BUF_RD_ENABLE_MASK (0x800U)
#define SDXC_PSTATE_BUF_RD_ENABLE_SHIFT (11U)
#define SDXC_PSTATE_BUF_RD_ENABLE_GET(x) (((uint32_t)(x) & SDXC_PSTATE_BUF_RD_ENABLE_MASK) >> SDXC_PSTATE_BUF_RD_ENABLE_SHIFT)

/*
 * BUF_WR_ENABLE (R)
 *
 * Buffer Write Enable
 * This bit is used for non-DMA transfers. This bit is set if space is available for writing data.
 * Values: 
 * 0x0 (DISABLED): Write disable
 * 0x1 (ENABLED): Write enable
 */
#define SDXC_PSTATE_BUF_WR_ENABLE_MASK (0x400U)
#define SDXC_PSTATE_BUF_WR_ENABLE_SHIFT (10U)
#define SDXC_PSTATE_BUF_WR_ENABLE_GET(x) (((uint32_t)(x) & SDXC_PSTATE_BUF_WR_ENABLE_MASK) >> SDXC_PSTATE_BUF_WR_ENABLE_SHIFT)

/*
 * RD_XFER_ACTIVE (R)
 *
 * Read Transfer Active 
 * This bit indicates whether a read transfer is active for SD/eMMC mode. This bit irrelevant for the UHS-II mode and always returns 0.
 * Values: 
 * 0x0 (INACTIVE): No valid data
 * 0x1 (ACTIVE): Transferring data
 */
#define SDXC_PSTATE_RD_XFER_ACTIVE_MASK (0x200U)
#define SDXC_PSTATE_RD_XFER_ACTIVE_SHIFT (9U)
#define SDXC_PSTATE_RD_XFER_ACTIVE_GET(x) (((uint32_t)(x) & SDXC_PSTATE_RD_XFER_ACTIVE_MASK) >> SDXC_PSTATE_RD_XFER_ACTIVE_SHIFT)

/*
 * WR_XFER_ACTIVE (R)
 *
 * Write Transfer Active 
 * This status indicates whether a write transfer is active for SD/eMMC mode. It is irrelevant for UHS-II mode and always returns 0.
 * Values: 
 * 0x0 (INACTIVE): No valid data
 * 0x1 (ACTIVE): Transferring data
 */
#define SDXC_PSTATE_WR_XFER_ACTIVE_MASK (0x100U)
#define SDXC_PSTATE_WR_XFER_ACTIVE_SHIFT (8U)
#define SDXC_PSTATE_WR_XFER_ACTIVE_GET(x) (((uint32_t)(x) & SDXC_PSTATE_WR_XFER_ACTIVE_MASK) >> SDXC_PSTATE_WR_XFER_ACTIVE_SHIFT)

/*
 * DAT_7_4 (R)
 *
 * DAT[7:4] Line Signal Level
 * This bit is used to check the DAT line level to recover from errors and for debugging. These bits reflect the value of the sd_dat_in (upper nibble) signal. These bits are irrelevant for the UHS-II mode and always return 0.
 */
#define SDXC_PSTATE_DAT_7_4_MASK (0xF0U)
#define SDXC_PSTATE_DAT_7_4_SHIFT (4U)
#define SDXC_PSTATE_DAT_7_4_GET(x) (((uint32_t)(x) & SDXC_PSTATE_DAT_7_4_MASK) >> SDXC_PSTATE_DAT_7_4_SHIFT)

/*
 * RE_TUNE_REQ (R)
 *
 * 
 * Re-Tuning Request
 * DWC_mshc does not generate retuning request. The software must maintain the Retuning timer. 
 * 
 */
#define SDXC_PSTATE_RE_TUNE_REQ_MASK (0x8U)
#define SDXC_PSTATE_RE_TUNE_REQ_SHIFT (3U)
#define SDXC_PSTATE_RE_TUNE_REQ_GET(x) (((uint32_t)(x) & SDXC_PSTATE_RE_TUNE_REQ_MASK) >> SDXC_PSTATE_RE_TUNE_REQ_SHIFT)

/*
 * DAT_LINE_ACTIVE (R)
 *
 * DAT Line Active (SD/eMMC Mode only)
 * This bit indicates whether one of the DAT lines on the SD/eMMC bus is in use. This bit is irrelevant for the UHS-II mode.
 * In the case of read transactions, this bit indicates whether a read transfer is executing on the SD/eMMC bus.
 * In the case of write transactions, this bit indicates whether a write transfer is executing on the SD/eMMC bus.
 * For a command with busy, this status indicates whether the command executing busy is executing on an SD or eMMC bus.
 * Values: 
 * 0x0 (INACTIVE): DAT Line Inactive
 * 0x1 (ACTIVE): DAT Line Active
 */
#define SDXC_PSTATE_DAT_LINE_ACTIVE_MASK (0x4U)
#define SDXC_PSTATE_DAT_LINE_ACTIVE_SHIFT (2U)
#define SDXC_PSTATE_DAT_LINE_ACTIVE_GET(x) (((uint32_t)(x) & SDXC_PSTATE_DAT_LINE_ACTIVE_MASK) >> SDXC_PSTATE_DAT_LINE_ACTIVE_SHIFT)

/*
 * DAT_INHIBIT (R)
 *
 * Command Inhibit (DAT)
 * This bit is applicable for SD/eMMC mode and is generated if either DAT line active or Read transfer active is set to 1. If this bit is set to 0, it indicates that the Host Controller can issue subsequent SD/eMMC commands. For the UHS-II mode, this bit is irrelevant and always returns 0.
 * Values: 
 * 0x0 (READY): Can issue command which used DAT line
 * 0x1 (NOT_READY): Cannot issue command which used DAT line
 */
#define SDXC_PSTATE_DAT_INHIBIT_MASK (0x2U)
#define SDXC_PSTATE_DAT_INHIBIT_SHIFT (1U)
#define SDXC_PSTATE_DAT_INHIBIT_GET(x) (((uint32_t)(x) & SDXC_PSTATE_DAT_INHIBIT_MASK) >> SDXC_PSTATE_DAT_INHIBIT_SHIFT)

/*
 * CMD_INHIBIT (R)
 *
 * Command Inhibit (CMD)
 * This bit indicates the following : 
 * SD/eMMC mode: If this bit is set to 0, it indicates that the CMD line is not in use and the Host controller can issue an SD/eMMC command using the CMD line. This bit is set when the command register is written. This bit is cleared when the command response is received. This bit is not cleared by the response of auto CMD12/23 but cleared by the response of read/write command.
 * UHS-II mode: If this bit is set to 0, it indicates that a command packet can be issued by the Host Controller.
 * Values: 
 * 0x0 (READY): Host Controller is ready to issue a command
 * 0x1 (NOT_READY): Host Controller is not ready to issue a command
 */
#define SDXC_PSTATE_CMD_INHIBIT_MASK (0x1U)
#define SDXC_PSTATE_CMD_INHIBIT_SHIFT (0U)
#define SDXC_PSTATE_CMD_INHIBIT_GET(x) (((uint32_t)(x) & SDXC_PSTATE_CMD_INHIBIT_MASK) >> SDXC_PSTATE_CMD_INHIBIT_SHIFT)

/* Bitfield definition for register: PROT_CTRL */
/*
 * CARD_REMOVAL (RW)
 *
 * Wakeup Event Enable on SD Card Removal
 * This bit enables wakeup event through Card Removal assertion in the Normal Interrupt Status register. For the SDIO card, Wake Up Support (FN_WUS) in the Card Information Structure (CIS) register does not affect this bit.
 * Values: 
 * 0x0 (DISABLED): Disable
 * 0x1 (ENABLED): Enable
 */
#define SDXC_PROT_CTRL_CARD_REMOVAL_MASK (0x4000000UL)
#define SDXC_PROT_CTRL_CARD_REMOVAL_SHIFT (26U)
#define SDXC_PROT_CTRL_CARD_REMOVAL_SET(x) (((uint32_t)(x) << SDXC_PROT_CTRL_CARD_REMOVAL_SHIFT) & SDXC_PROT_CTRL_CARD_REMOVAL_MASK)
#define SDXC_PROT_CTRL_CARD_REMOVAL_GET(x) (((uint32_t)(x) & SDXC_PROT_CTRL_CARD_REMOVAL_MASK) >> SDXC_PROT_CTRL_CARD_REMOVAL_SHIFT)

/*
 * CARD_INSERT (RW)
 *
 * Wakeup Event Enable on SD Card Insertion
 * This bit enables wakeup event through Card Insertion assertion in the Normal Interrupt Status register. FN_WUS (Wake Up Support) in CIS does not affect this bit.
 * Values: 
 * 0x0 (DISABLED): Disable
 * 0x1 (ENABLED): Enable
 */
#define SDXC_PROT_CTRL_CARD_INSERT_MASK (0x2000000UL)
#define SDXC_PROT_CTRL_CARD_INSERT_SHIFT (25U)
#define SDXC_PROT_CTRL_CARD_INSERT_SET(x) (((uint32_t)(x) << SDXC_PROT_CTRL_CARD_INSERT_SHIFT) & SDXC_PROT_CTRL_CARD_INSERT_MASK)
#define SDXC_PROT_CTRL_CARD_INSERT_GET(x) (((uint32_t)(x) & SDXC_PROT_CTRL_CARD_INSERT_MASK) >> SDXC_PROT_CTRL_CARD_INSERT_SHIFT)

/*
 * CARD_INT (RW)
 *
 * Wakeup Event Enable on Card Interrupt 
 * This bit enables wakeup event through a Card Interrupt assertion in the Normal Interrupt Status register. This bit can be set to 1 if FN_WUS (Wake Up Support) in CIS is set to 1.
 * Values: 
 * 0x0 (DISABLED): Disable
 * 0x1 (ENABLED): Enable
 */
#define SDXC_PROT_CTRL_CARD_INT_MASK (0x1000000UL)
#define SDXC_PROT_CTRL_CARD_INT_SHIFT (24U)
#define SDXC_PROT_CTRL_CARD_INT_SET(x) (((uint32_t)(x) << SDXC_PROT_CTRL_CARD_INT_SHIFT) & SDXC_PROT_CTRL_CARD_INT_MASK)
#define SDXC_PROT_CTRL_CARD_INT_GET(x) (((uint32_t)(x) & SDXC_PROT_CTRL_CARD_INT_MASK) >> SDXC_PROT_CTRL_CARD_INT_SHIFT)

/*
 * INT_AT_BGAP (RW)
 *
 * Interrupt At Block Gap 
 * This bit is valid only in the 4-bit mode of an SDIO card and is used to select a sample point in the interrupt cycle. Setting to 1 enables interrupt detection at the block gap for a multiple block transfer. In UHS-II mode, this bit is disabled. 
 * Values: 
 * 0x0 (DISABLE): Disabled
 * 0x1 (ENABLE): Enabled
 */
#define SDXC_PROT_CTRL_INT_AT_BGAP_MASK (0x80000UL)
#define SDXC_PROT_CTRL_INT_AT_BGAP_SHIFT (19U)
#define SDXC_PROT_CTRL_INT_AT_BGAP_SET(x) (((uint32_t)(x) << SDXC_PROT_CTRL_INT_AT_BGAP_SHIFT) & SDXC_PROT_CTRL_INT_AT_BGAP_MASK)
#define SDXC_PROT_CTRL_INT_AT_BGAP_GET(x) (((uint32_t)(x) & SDXC_PROT_CTRL_INT_AT_BGAP_MASK) >> SDXC_PROT_CTRL_INT_AT_BGAP_SHIFT)

/*
 * RD_WAIT_CTRL (RW)
 *
 * Read Wait Control
 * This bit is used to enable the read wait protocol to stop read data using DAT[2] line if the card supports read wait. Otherwise, the Host Controller has to stop the card clock to hold the read data. In UHS-II mode, Read Wait is disabled.
 * Values: 
 * 0x0 (DISABLE): Disable Read Wait Control
 * 0x1 (ENABLE): Enable Read Wait Control
 */
#define SDXC_PROT_CTRL_RD_WAIT_CTRL_MASK (0x40000UL)
#define SDXC_PROT_CTRL_RD_WAIT_CTRL_SHIFT (18U)
#define SDXC_PROT_CTRL_RD_WAIT_CTRL_SET(x) (((uint32_t)(x) << SDXC_PROT_CTRL_RD_WAIT_CTRL_SHIFT) & SDXC_PROT_CTRL_RD_WAIT_CTRL_MASK)
#define SDXC_PROT_CTRL_RD_WAIT_CTRL_GET(x) (((uint32_t)(x) & SDXC_PROT_CTRL_RD_WAIT_CTRL_MASK) >> SDXC_PROT_CTRL_RD_WAIT_CTRL_SHIFT)

/*
 * CONTINUE_REQ (RW)
 *
 * Continue Request
 * This bit is used to restart the transaction, which was stopped using the Stop At Block Gap Request. The Host Controller automatically clears this bit when the transaction restarts. If stop at block gap request is set to 1, any write to this bit is ignored. 
 * Values: 
 * 0x0 (NO_AFFECT): No Affect
 * 0x1 (RESTART): Restart
 */
#define SDXC_PROT_CTRL_CONTINUE_REQ_MASK (0x20000UL)
#define SDXC_PROT_CTRL_CONTINUE_REQ_SHIFT (17U)
#define SDXC_PROT_CTRL_CONTINUE_REQ_SET(x) (((uint32_t)(x) << SDXC_PROT_CTRL_CONTINUE_REQ_SHIFT) & SDXC_PROT_CTRL_CONTINUE_REQ_MASK)
#define SDXC_PROT_CTRL_CONTINUE_REQ_GET(x) (((uint32_t)(x) & SDXC_PROT_CTRL_CONTINUE_REQ_MASK) >> SDXC_PROT_CTRL_CONTINUE_REQ_SHIFT)

/*
 * STOP_BG_REQ (RW)
 *
 * Stop At Block Gap Request
 * This bit is used to stop executing read and write transactions at the next block gap for non-DMA, SDMA, and ADMA transfers.
 * Values: 
 * 0x0 (XFER): Transfer
 * 0x1 (STOP): Stop
 */
#define SDXC_PROT_CTRL_STOP_BG_REQ_MASK (0x10000UL)
#define SDXC_PROT_CTRL_STOP_BG_REQ_SHIFT (16U)
#define SDXC_PROT_CTRL_STOP_BG_REQ_SET(x) (((uint32_t)(x) << SDXC_PROT_CTRL_STOP_BG_REQ_SHIFT) & SDXC_PROT_CTRL_STOP_BG_REQ_MASK)
#define SDXC_PROT_CTRL_STOP_BG_REQ_GET(x) (((uint32_t)(x) & SDXC_PROT_CTRL_STOP_BG_REQ_MASK) >> SDXC_PROT_CTRL_STOP_BG_REQ_SHIFT)

/*
 * SD_BUS_VOL_VDD1 (RW)
 *
 * SD Bus Voltage Select for VDD1/eMMC Bus Voltage Select for VDD
 * These bits enable the Host Driver to select the voltage level for an SD/eMMC card. Before setting this register, the Host Driver checks the Voltage Support bits in the Capabilities register. If an unsupported voltage is selected, the Host System does not supply the SD Bus voltage. The value set in this field is available on the DWC_mshc output signal (sd_vdd1_sel), which is used by the voltage switching circuitry.
 * SD Bus Voltage Select options:
 * 0x7 : 3.3V(Typical)
 * 0x6 : 3.0V(Typical)
 * 0x5 : 1.8V(Typical) for Embedded
 * 0x4 : 0x0 - Reserved
 * eMMC Bus Voltage Select options:
 * 0x7 : 3.3V(Typical)
 * 0x6 : 1.8V(Typical)
 * 0x5 : 1.2V(Typical)
 * 0x4 : 0x0 - Reserved
 * Values: 
 * 0x7 (V_3_3): 3.3V (Typ.)
 * 0x6 (V_3_0): 3.0V (Typ.)
 * 0x5 (V_1_8): 1.8V (Typ.) for Embedded
 * 0x4 (RSVD4): Reserved
 * 0x3 (RSVD3): Reserved
 * 0x2 (RSVD2): Reserved
 * 0x1 (RSVD1): Reserved
 * 0x0 (RSVD0): Reserved
 */
#define SDXC_PROT_CTRL_SD_BUS_VOL_VDD1_MASK (0xE00U)
#define SDXC_PROT_CTRL_SD_BUS_VOL_VDD1_SHIFT (9U)
#define SDXC_PROT_CTRL_SD_BUS_VOL_VDD1_SET(x) (((uint32_t)(x) << SDXC_PROT_CTRL_SD_BUS_VOL_VDD1_SHIFT) & SDXC_PROT_CTRL_SD_BUS_VOL_VDD1_MASK)
#define SDXC_PROT_CTRL_SD_BUS_VOL_VDD1_GET(x) (((uint32_t)(x) & SDXC_PROT_CTRL_SD_BUS_VOL_VDD1_MASK) >> SDXC_PROT_CTRL_SD_BUS_VOL_VDD1_SHIFT)

/*
 * SD_BUS_PWR_VDD1 (RW)
 *
 * SD Bus Power for VDD1
 * This bit enables VDD1 power of the card. This setting is available on the sd_vdd1_on output of DWC_mshc so that it can be used to control the VDD1 power supply of the card. Before setting this bit, the SD Host Driver sets the SD Bus Voltage Select bit. If the Host Controller detects a No Card state, this bit is cleared.
 * In SD mode, if this bit is cleared, the Host Controller stops the SD Clock by clearing the SD_CLK_IN bit in the CLK_CTRL_R register.
 * In UHS-II mode, before clearing this bit, the Host Driver clears the SD_CLK_IN bit in the CLK_CTRL_R register.
 * Values: 
 * 0x0 (OFF): Power off
 * 0x1 (ON): Power on
 */
#define SDXC_PROT_CTRL_SD_BUS_PWR_VDD1_MASK (0x100U)
#define SDXC_PROT_CTRL_SD_BUS_PWR_VDD1_SHIFT (8U)
#define SDXC_PROT_CTRL_SD_BUS_PWR_VDD1_SET(x) (((uint32_t)(x) << SDXC_PROT_CTRL_SD_BUS_PWR_VDD1_SHIFT) & SDXC_PROT_CTRL_SD_BUS_PWR_VDD1_MASK)
#define SDXC_PROT_CTRL_SD_BUS_PWR_VDD1_GET(x) (((uint32_t)(x) & SDXC_PROT_CTRL_SD_BUS_PWR_VDD1_MASK) >> SDXC_PROT_CTRL_SD_BUS_PWR_VDD1_SHIFT)

/*
 * CARD_DETECT_SIG_SEL (RW)
 *
 * Card Detect Signal Selection
 * This bit selects a source for card detection. When the source for the card detection is switched, the interrupt must be disabled during the switching period.
 * Values: 
 * 0x1 (CARD_DT_TEST_LEVEL): Card Detect Test Level is selected (for test purpose)
 * 0x0 (SDCD_PIN): SDCD# (card_detect_n signal) is selected (for normal use)
 */
#define SDXC_PROT_CTRL_CARD_DETECT_SIG_SEL_MASK (0x80U)
#define SDXC_PROT_CTRL_CARD_DETECT_SIG_SEL_SHIFT (7U)
#define SDXC_PROT_CTRL_CARD_DETECT_SIG_SEL_SET(x) (((uint32_t)(x) << SDXC_PROT_CTRL_CARD_DETECT_SIG_SEL_SHIFT) & SDXC_PROT_CTRL_CARD_DETECT_SIG_SEL_MASK)
#define SDXC_PROT_CTRL_CARD_DETECT_SIG_SEL_GET(x) (((uint32_t)(x) & SDXC_PROT_CTRL_CARD_DETECT_SIG_SEL_MASK) >> SDXC_PROT_CTRL_CARD_DETECT_SIG_SEL_SHIFT)

/*
 * CARD_DETECT_TEST_LVL (RW)
 *
 * Card Detect Test Level
 * This bit is enabled while the Card Detect Signal Selection is set to 1 and it indicates whether a card inserted or not.
 * Values: 
 * 0x1 (CARD_INSERTED): Card Inserted
 * 0x0 (No_CARD): No Card
 */
#define SDXC_PROT_CTRL_CARD_DETECT_TEST_LVL_MASK (0x40U)
#define SDXC_PROT_CTRL_CARD_DETECT_TEST_LVL_SHIFT (6U)
#define SDXC_PROT_CTRL_CARD_DETECT_TEST_LVL_SET(x) (((uint32_t)(x) << SDXC_PROT_CTRL_CARD_DETECT_TEST_LVL_SHIFT) & SDXC_PROT_CTRL_CARD_DETECT_TEST_LVL_MASK)
#define SDXC_PROT_CTRL_CARD_DETECT_TEST_LVL_GET(x) (((uint32_t)(x) & SDXC_PROT_CTRL_CARD_DETECT_TEST_LVL_MASK) >> SDXC_PROT_CTRL_CARD_DETECT_TEST_LVL_SHIFT)

/*
 * EXT_DAT_XFER (RW)
 *
 * Extended Data Transfer Width 
 * This bit controls 8-bit bus width mode of embedded device. This bit is not applicable for UHS-II mode.
 * Values: 
 * 0x1 (EIGHT_BIT): 8-bit Bus Width
 * 0x0 (DEFAULT): Bus Width is selected by the Data Transfer Width
 */
#define SDXC_PROT_CTRL_EXT_DAT_XFER_MASK (0x20U)
#define SDXC_PROT_CTRL_EXT_DAT_XFER_SHIFT (5U)
#define SDXC_PROT_CTRL_EXT_DAT_XFER_SET(x) (((uint32_t)(x) << SDXC_PROT_CTRL_EXT_DAT_XFER_SHIFT) & SDXC_PROT_CTRL_EXT_DAT_XFER_MASK)
#define SDXC_PROT_CTRL_EXT_DAT_XFER_GET(x) (((uint32_t)(x) & SDXC_PROT_CTRL_EXT_DAT_XFER_MASK) >> SDXC_PROT_CTRL_EXT_DAT_XFER_SHIFT)

/*
 * DMA_SEL (RW)
 *
 * DMA Select
 * This field is used to select the DMA type.
 * When Host Version 4 Enable is 1 in Host Control 2 register:
 * 0x0 : SDMA is selected
 * 0x1 : Reserved
 * 0x2 : ADMA2 is selected
 * 0x3 : ADMA2 or ADMA3 is selected
 * When Host Version 4 Enable is 0 in Host Control 2 register:
 * 0x0 : SDMA is selected
 * 0x1 : Reserved
 * 0x2 : 32-bit Address ADMA2 is selected
 * 0x3 : 64-bit Address ADMA2 is selected
 * Values: 
 * 0x0 (SDMA): SDMA is selected
 * 0x1 (RSVD_BIT): Reserved
 * 0x2 (ADMA2): ADMA2 is selected
 * 0x3 (ADMA2_3): ADMA2 or ADMA3 is selected
 */
#define SDXC_PROT_CTRL_DMA_SEL_MASK (0x18U)
#define SDXC_PROT_CTRL_DMA_SEL_SHIFT (3U)
#define SDXC_PROT_CTRL_DMA_SEL_SET(x) (((uint32_t)(x) << SDXC_PROT_CTRL_DMA_SEL_SHIFT) & SDXC_PROT_CTRL_DMA_SEL_MASK)
#define SDXC_PROT_CTRL_DMA_SEL_GET(x) (((uint32_t)(x) & SDXC_PROT_CTRL_DMA_SEL_MASK) >> SDXC_PROT_CTRL_DMA_SEL_SHIFT)

/*
 * HIGH_SPEED_EN (RW)
 *
 * High Speed Enable (SD/eMMC Mode only)
 * In SD/eMMC mode, this bit is used to determine the selection of preset value for High Speed mode. Before setting this bit, the Host Driver checks the High Speed Support in the Capabilities register.
 * Note: DWC_MSHC always outputs the sd_cmd_out and sd_dat_out lines at the rising edge of cclk_tx clock irrespective of this bit.Please refer the section Connecting the Clock IO interface in the Mobile Storage Host Controller user guide on clocking requirement for an SD/eMMC card.
 * In UHS-II mode, this bit is irrelevant.
 * Values: 
 * 0x1 (HIGH_SPEED): High Speed mode
 * 0x0 (NORMAL_SPEED): Normal Speed mode
 */
#define SDXC_PROT_CTRL_HIGH_SPEED_EN_MASK (0x4U)
#define SDXC_PROT_CTRL_HIGH_SPEED_EN_SHIFT (2U)
#define SDXC_PROT_CTRL_HIGH_SPEED_EN_SET(x) (((uint32_t)(x) << SDXC_PROT_CTRL_HIGH_SPEED_EN_SHIFT) & SDXC_PROT_CTRL_HIGH_SPEED_EN_MASK)
#define SDXC_PROT_CTRL_HIGH_SPEED_EN_GET(x) (((uint32_t)(x) & SDXC_PROT_CTRL_HIGH_SPEED_EN_MASK) >> SDXC_PROT_CTRL_HIGH_SPEED_EN_SHIFT)

/*
 * DAT_XFER_WIDTH (RW)
 *
 * Data Transfer Width 
 * For SD/eMMC mode,this bit selects the data transfer width of the Host Controller. The Host Driver sets it to match the data width of the SD/eMMC card. In UHS-II mode, this bit is irrelevant.
 * Values: 
 * 0x1 (FOUR_BIT): 4-bit mode
 * 0x0 (ONE_BIT): 1-bit mode
 */
#define SDXC_PROT_CTRL_DAT_XFER_WIDTH_MASK (0x2U)
#define SDXC_PROT_CTRL_DAT_XFER_WIDTH_SHIFT (1U)
#define SDXC_PROT_CTRL_DAT_XFER_WIDTH_SET(x) (((uint32_t)(x) << SDXC_PROT_CTRL_DAT_XFER_WIDTH_SHIFT) & SDXC_PROT_CTRL_DAT_XFER_WIDTH_MASK)
#define SDXC_PROT_CTRL_DAT_XFER_WIDTH_GET(x) (((uint32_t)(x) & SDXC_PROT_CTRL_DAT_XFER_WIDTH_MASK) >> SDXC_PROT_CTRL_DAT_XFER_WIDTH_SHIFT)

/*
 * LED_CTRL (RW)
 *
 * LED Control
 * This bit is used to caution the user not to remove the card while the SD card is being accessed. The value is reflected on the led_control signal.
 * Values: 
 * 0x0 (OFF): LED off
 * 0x1 (ON): LED on
 */
#define SDXC_PROT_CTRL_LED_CTRL_MASK (0x1U)
#define SDXC_PROT_CTRL_LED_CTRL_SHIFT (0U)
#define SDXC_PROT_CTRL_LED_CTRL_SET(x) (((uint32_t)(x) << SDXC_PROT_CTRL_LED_CTRL_SHIFT) & SDXC_PROT_CTRL_LED_CTRL_MASK)
#define SDXC_PROT_CTRL_LED_CTRL_GET(x) (((uint32_t)(x) & SDXC_PROT_CTRL_LED_CTRL_MASK) >> SDXC_PROT_CTRL_LED_CTRL_SHIFT)

/* Bitfield definition for register: SYS_CTRL */
/*
 * SW_RST_DAT (RW)
 *
 * Software Reset For DAT line 
 * This bit is used in SD/eMMC mode and it resets only a part of the data circuit and the DMA circuit is also reset.
 * The following registers and bits are cleared by this bit:
 * Buffer Data Port register
 * -Buffer is cleared and initialized. 
 * Present state register
 * -Buffer Read Enable
 * -Buffer Write Enable
 * -Read Transfer Active
 * -Write Transfer Active
 * -DAT Line Active
 * -Command Inhibit (DAT)
 * Block Gap Control register
 * -Continue Request 
 * -Stop At Block Gap Request
 * Normal Interrupt status register
 * -Buffer Read Ready
 * -Buffer Write Ready
 * -DMA Interrupt
 * -Block Gap Event
 * -Transfer Complete 
 * In UHS-II mode, this bit shall be set to 0 
 * Values: 
 * 0x0 (FALSE): Work
 * 0x1 (TRUE): Reset
 */
#define SDXC_SYS_CTRL_SW_RST_DAT_MASK (0x4000000UL)
#define SDXC_SYS_CTRL_SW_RST_DAT_SHIFT (26U)
#define SDXC_SYS_CTRL_SW_RST_DAT_SET(x) (((uint32_t)(x) << SDXC_SYS_CTRL_SW_RST_DAT_SHIFT) & SDXC_SYS_CTRL_SW_RST_DAT_MASK)
#define SDXC_SYS_CTRL_SW_RST_DAT_GET(x) (((uint32_t)(x) & SDXC_SYS_CTRL_SW_RST_DAT_MASK) >> SDXC_SYS_CTRL_SW_RST_DAT_SHIFT)

/*
 * SW_RST_CMD (RW)
 *
 * Software Reset For CMD line
 * This bit resets only a part of the command circuit to be able to issue a command. It bit is also used to initialize a UHS-II command circuit. This reset is effective only for a command issuing circuit (including response error statuses related to Command Inhibit (CMD) control) and does not affect the data transfer circuit. Host Controller can continue data transfer even after this reset is executed while handling subcommand-response errors.
 * The following registers and bits are cleared by this bit:
 * Present State register : Command Inhibit (CMD) bit
 * Normal Interrupt Status register : Command Complete bit
 * Error Interrupt Status : Response error statuses related to Command Inhibit (CMD) bit
 * Values: 
 * 0x0 (FALSE): Work
 * 0x1 (TRUE): Reset
 */
#define SDXC_SYS_CTRL_SW_RST_CMD_MASK (0x2000000UL)
#define SDXC_SYS_CTRL_SW_RST_CMD_SHIFT (25U)
#define SDXC_SYS_CTRL_SW_RST_CMD_SET(x) (((uint32_t)(x) << SDXC_SYS_CTRL_SW_RST_CMD_SHIFT) & SDXC_SYS_CTRL_SW_RST_CMD_MASK)
#define SDXC_SYS_CTRL_SW_RST_CMD_GET(x) (((uint32_t)(x) & SDXC_SYS_CTRL_SW_RST_CMD_MASK) >> SDXC_SYS_CTRL_SW_RST_CMD_SHIFT)

/*
 * SW_RST_ALL (RW)
 *
 * Software Reset For All
 * This reset affects the entire Host Controller except for the card detection circuit. During its initialization, the Host Driver sets this bit to 1 to reset the Host Controller. All registers are reset except the capabilities register. If this bit is set to 1, the Host Driver must issue reset command and reinitialize the card.
 * Values: 
 * 0x0 (FALSE): Work
 * 0x1 (TRUE): Reset
 */
#define SDXC_SYS_CTRL_SW_RST_ALL_MASK (0x1000000UL)
#define SDXC_SYS_CTRL_SW_RST_ALL_SHIFT (24U)
#define SDXC_SYS_CTRL_SW_RST_ALL_SET(x) (((uint32_t)(x) << SDXC_SYS_CTRL_SW_RST_ALL_SHIFT) & SDXC_SYS_CTRL_SW_RST_ALL_MASK)
#define SDXC_SYS_CTRL_SW_RST_ALL_GET(x) (((uint32_t)(x) & SDXC_SYS_CTRL_SW_RST_ALL_MASK) >> SDXC_SYS_CTRL_SW_RST_ALL_SHIFT)

/*
 * TOUT_CNT (RW)
 *
 * Data Timeout Counter Value.
 * This value determines the interval by which DAT line timeouts are detected. The Timeout clock frequency is generated by dividing the base clock TMCLK value by this value. When setting this register, prevent inadvertent timeout events by clearing the Data Timeout Error Status Enable (in the Error Interrupt Status Enable register). The values for these bits are:
 * 0xF : Reserved
 * 0xE : TMCLK x 2^27
 * .........
 * 0x1 : TMCLK x 2^14
 * 0x0 : TMCLK x 2^13
 * Note: During a boot operating in an eMMC mode, an application must configure the boot data timeout value (approximately 1 sec) in this bit.
 */
#define SDXC_SYS_CTRL_TOUT_CNT_MASK (0xF0000UL)
#define SDXC_SYS_CTRL_TOUT_CNT_SHIFT (16U)
#define SDXC_SYS_CTRL_TOUT_CNT_SET(x) (((uint32_t)(x) << SDXC_SYS_CTRL_TOUT_CNT_SHIFT) & SDXC_SYS_CTRL_TOUT_CNT_MASK)
#define SDXC_SYS_CTRL_TOUT_CNT_GET(x) (((uint32_t)(x) & SDXC_SYS_CTRL_TOUT_CNT_MASK) >> SDXC_SYS_CTRL_TOUT_CNT_SHIFT)

/*
 * FREQ_SEL (RW)
 *
 * SDCLK/RCLK Frequency Select
 * These bits are used to select the frequency of the SDCLK signal. These bits depend on setting of Preset Value Enable in the Host Control 2 register. If Preset Value Enable = 0, these bits are set by the Host Driver. If Preset Value Enable = 1, these bits are automatically set to a value specified in one of the Preset Value register. The value is reflected on the lower 8-bit of the card_clk_freq_selsignal. 
 * 10-bit Divided Clock Mode:
 * 0x3FF : 1/2046 Divided clock
 * ..........
 * N : 1/2N Divided Clock
 * ..........
 * 0x002 : 1/4 Divided Clock
 * 0x001 : 1/2 Divided Clock
 * 0x000 : Base clock (10MHz - 255 MHz)
 * Programmable Clock Mode : Enables the Host System to select a fine grain SD clock frequency: 
 * 0x3FF : Base clock * M /1024
 * ..........
 * N-1 : Base clock * M /N
 * ..........
 * 0x002 : Base clock * M /3
 * 0x001 : Base clock * M /2
 * 0x000 : Base clock * M
 */
#define SDXC_SYS_CTRL_FREQ_SEL_MASK (0xFF00U)
#define SDXC_SYS_CTRL_FREQ_SEL_SHIFT (8U)
#define SDXC_SYS_CTRL_FREQ_SEL_SET(x) (((uint32_t)(x) << SDXC_SYS_CTRL_FREQ_SEL_SHIFT) & SDXC_SYS_CTRL_FREQ_SEL_MASK)
#define SDXC_SYS_CTRL_FREQ_SEL_GET(x) (((uint32_t)(x) & SDXC_SYS_CTRL_FREQ_SEL_MASK) >> SDXC_SYS_CTRL_FREQ_SEL_SHIFT)

/*
 * UPPER_FREQ_SEL (RW)
 *
 * These bits specify the upper 2 bits of 10-bit SDCLK/RCLK Frequency Select control. The value is reflected on the upper 2 bits of the card_clk_freq_sel signal.
 */
#define SDXC_SYS_CTRL_UPPER_FREQ_SEL_MASK (0xC0U)
#define SDXC_SYS_CTRL_UPPER_FREQ_SEL_SHIFT (6U)
#define SDXC_SYS_CTRL_UPPER_FREQ_SEL_SET(x) (((uint32_t)(x) << SDXC_SYS_CTRL_UPPER_FREQ_SEL_SHIFT) & SDXC_SYS_CTRL_UPPER_FREQ_SEL_MASK)
#define SDXC_SYS_CTRL_UPPER_FREQ_SEL_GET(x) (((uint32_t)(x) & SDXC_SYS_CTRL_UPPER_FREQ_SEL_MASK) >> SDXC_SYS_CTRL_UPPER_FREQ_SEL_SHIFT)

/*
 * CLK_GEN_SELECT (RW)
 *
 * Clock Generator Select
 * This bit is used to select the clock generator mode in SDCLK/RCLK Frequency Select. If Preset Value Enable = 0, this bit is set by the Host Driver. If Preset Value Enable = 1, this bit is automatically set to a value specified in one of the Preset Value registers. The value is reflected on the card_clk_gen_sel signal.
 * Values: 
 * 0x0 (FALSE): Divided Clock Mode
 * 0x1 (TRUE): Programmable Clock Mode
 */
#define SDXC_SYS_CTRL_CLK_GEN_SELECT_MASK (0x20U)
#define SDXC_SYS_CTRL_CLK_GEN_SELECT_SHIFT (5U)
#define SDXC_SYS_CTRL_CLK_GEN_SELECT_SET(x) (((uint32_t)(x) << SDXC_SYS_CTRL_CLK_GEN_SELECT_SHIFT) & SDXC_SYS_CTRL_CLK_GEN_SELECT_MASK)
#define SDXC_SYS_CTRL_CLK_GEN_SELECT_GET(x) (((uint32_t)(x) & SDXC_SYS_CTRL_CLK_GEN_SELECT_MASK) >> SDXC_SYS_CTRL_CLK_GEN_SELECT_SHIFT)

/*
 * PLL_ENABLE (RW)
 *
 * PLL Enable
 * This bit is used to activate the PLL (applicable when Host Version 4 Enable = 1). When Host Version 4 Enable = 0, INTERNAL_CLK_EN bit may be used to activate PLL. The value is reflected on the card_clk_en signal.
 * Note: If this bit is not used to to active the PLL when Host Version 4 Enable = 1, it is recommended to set this bit to '1' .
 * Values: 
 * 0x0 (FALSE): PLL is in low power mode
 * 0x1 (TRUE): PLL is enabled
 */
#define SDXC_SYS_CTRL_PLL_ENABLE_MASK (0x8U)
#define SDXC_SYS_CTRL_PLL_ENABLE_SHIFT (3U)
#define SDXC_SYS_CTRL_PLL_ENABLE_SET(x) (((uint32_t)(x) << SDXC_SYS_CTRL_PLL_ENABLE_SHIFT) & SDXC_SYS_CTRL_PLL_ENABLE_MASK)
#define SDXC_SYS_CTRL_PLL_ENABLE_GET(x) (((uint32_t)(x) & SDXC_SYS_CTRL_PLL_ENABLE_MASK) >> SDXC_SYS_CTRL_PLL_ENABLE_SHIFT)

/*
 * SD_CLK_EN (RW)
 *
 * SD/eMMC Clock Enable
 * This bit stops the SDCLK or RCLK when set to 0. The SDCLK/RCLK Frequency Select bit can be changed when this bit is set to 0. The value is reflected on the clk2card_on pin.
 * Values: 
 * 0x0 (FALSE): Disable providing SDCLK/RCLK
 * 0x1 (TRUE): Enable providing SDCLK/RCLK
 */
#define SDXC_SYS_CTRL_SD_CLK_EN_MASK (0x4U)
#define SDXC_SYS_CTRL_SD_CLK_EN_SHIFT (2U)
#define SDXC_SYS_CTRL_SD_CLK_EN_SET(x) (((uint32_t)(x) << SDXC_SYS_CTRL_SD_CLK_EN_SHIFT) & SDXC_SYS_CTRL_SD_CLK_EN_MASK)
#define SDXC_SYS_CTRL_SD_CLK_EN_GET(x) (((uint32_t)(x) & SDXC_SYS_CTRL_SD_CLK_EN_MASK) >> SDXC_SYS_CTRL_SD_CLK_EN_SHIFT)

/*
 * INTERNAL_CLK_STABLE (RW)
 *
 * Internal Clock Stable
 * This bit enables the Host Driver to check the clock stability twice after the Internal Clock Enable bit is set and after the PLL Enable bit is set. This bit reflects the synchronized value of the intclk_stable signal after the Internal Clock Enable bit is set to 1 and also reflects the synchronized value of the card_clk_stable signal after the PLL Enable bit is set to 1.
 * Values: 
 * 0x0 (FALSE): Not Ready
 * 0x1 (TRUE): Ready
 */
#define SDXC_SYS_CTRL_INTERNAL_CLK_STABLE_MASK (0x2U)
#define SDXC_SYS_CTRL_INTERNAL_CLK_STABLE_SHIFT (1U)
#define SDXC_SYS_CTRL_INTERNAL_CLK_STABLE_SET(x) (((uint32_t)(x) << SDXC_SYS_CTRL_INTERNAL_CLK_STABLE_SHIFT) & SDXC_SYS_CTRL_INTERNAL_CLK_STABLE_MASK)
#define SDXC_SYS_CTRL_INTERNAL_CLK_STABLE_GET(x) (((uint32_t)(x) & SDXC_SYS_CTRL_INTERNAL_CLK_STABLE_MASK) >> SDXC_SYS_CTRL_INTERNAL_CLK_STABLE_SHIFT)

/*
 * INTERNAL_CLK_EN (RW)
 *
 * Internal Clock Enable
 * This bit is set to 0 when the Host Driver is not using the Host Controller or the Host Controller awaits a wakeup interrupt. The Host Controller must stop its internal clock to enter a very low power state. However, registers can still be read and written to. The value is reflected on the intclk_en signal.
 * Note: If this bit is not used to control the internal clock (base clock and master clock), it is recommended to set this bit to '1' .
 * Values: 
 * 0x0 (FALSE): Stop
 * 0x1 (TRUE): Oscillate
 */
#define SDXC_SYS_CTRL_INTERNAL_CLK_EN_MASK (0x1U)
#define SDXC_SYS_CTRL_INTERNAL_CLK_EN_SHIFT (0U)
#define SDXC_SYS_CTRL_INTERNAL_CLK_EN_SET(x) (((uint32_t)(x) << SDXC_SYS_CTRL_INTERNAL_CLK_EN_SHIFT) & SDXC_SYS_CTRL_INTERNAL_CLK_EN_MASK)
#define SDXC_SYS_CTRL_INTERNAL_CLK_EN_GET(x) (((uint32_t)(x) & SDXC_SYS_CTRL_INTERNAL_CLK_EN_MASK) >> SDXC_SYS_CTRL_INTERNAL_CLK_EN_SHIFT)

/* Bitfield definition for register: INT_STAT */
/*
 * BOOT_ACK_ERR (R/W1C)
 *
 * Boot Acknowledgement Error 
 * This bit is set when there is a timeout for boot acknowledgement or when detecting boot ack status having a value other than 010. This is applicable only when boot acknowledgement is expected in eMMC mode. 
 * In SD/UHS-II mode, this bit is irrelevant.
 */
#define SDXC_INT_STAT_BOOT_ACK_ERR_MASK (0x10000000UL)
#define SDXC_INT_STAT_BOOT_ACK_ERR_SHIFT (28U)
#define SDXC_INT_STAT_BOOT_ACK_ERR_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_BOOT_ACK_ERR_SHIFT) & SDXC_INT_STAT_BOOT_ACK_ERR_MASK)
#define SDXC_INT_STAT_BOOT_ACK_ERR_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_BOOT_ACK_ERR_MASK) >> SDXC_INT_STAT_BOOT_ACK_ERR_SHIFT)

/*
 * RESP_ERR (R/W1C)
 *
 * Response Error 
 * Host Controller Version 4.00 supports response error check function to avoid overhead of response error check by Host Driver during DMA execution. If Response Error Check Enable is set to 1 in the Transfer Mode register, Host Controller Checks R1 or R5 response. If an error is detected in a response, this bit is set to 1.This is applicable in SD/eMMC mode. 
 * In UHS-II mode, this bit is irrelevant. 
 * Values: 
 * 0x0 (FALSE): No error
 * 0x1 (TRUE): Error
 */
#define SDXC_INT_STAT_RESP_ERR_MASK (0x8000000UL)
#define SDXC_INT_STAT_RESP_ERR_SHIFT (27U)
#define SDXC_INT_STAT_RESP_ERR_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_RESP_ERR_SHIFT) & SDXC_INT_STAT_RESP_ERR_MASK)
#define SDXC_INT_STAT_RESP_ERR_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_RESP_ERR_MASK) >> SDXC_INT_STAT_RESP_ERR_SHIFT)

/*
 * TUNING_ERR (R/W1C)
 *
 * Tuning Error
 * This bit is set when an unrecoverable error is detected in a tuning circuit except during the tuning procedure (occurrence of an error during tuning procedure is indicated by Sampling Clock Select in the Host Control 2 register). By detecting Tuning Error, Host Driver needs to abort a command executing and perform tuning. To reset tuning circuit, Sampling Clock Select is set to 0 before executing tuning procedure. The Tuning Error is higher priority than the other error interrupts generated during data transfer. By detecting Tuning Error, the Host Driver must discard data transferred by a current read/write command and retry data transfer after the Host Controller retrieved from the tuning circuit error. This is applicable in SD/eMMC mode. 
 * In UHS-II mode, this bit is irrelevant. 
 * Values: 
 * 0x0 (FALSE): No error
 * 0x1 (TRUE): Error
 */
#define SDXC_INT_STAT_TUNING_ERR_MASK (0x4000000UL)
#define SDXC_INT_STAT_TUNING_ERR_SHIFT (26U)
#define SDXC_INT_STAT_TUNING_ERR_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_TUNING_ERR_SHIFT) & SDXC_INT_STAT_TUNING_ERR_MASK)
#define SDXC_INT_STAT_TUNING_ERR_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_TUNING_ERR_MASK) >> SDXC_INT_STAT_TUNING_ERR_SHIFT)

/*
 * ADMA_ERR (R/W1C)
 *
 * ADMA Error
 * This bit is set when the Host Controller detects error during ADMA-based data transfer. The error could be due to following reasons:
 * Error response received from System bus (Master I/F)
 * ADMA3,ADMA2 Descriptors invalid
 * CQE Task or Transfer descriptors invalid
 * When the error occurs, the state of the ADMA is saved in the ADMA Error Status register.
 * In eMMC CQE mode: 
 * The Host Controller generates this Interrupt when it detects an invalid descriptor data (Valid=0) at the ST_FDS state. ADMA Error State in the ADMA Error Status indicates that an error has occurred in ST_FDS state. The Host Driver may find that Valid bit is not set at the error descriptor.
 * Values: 
 * 0x0 (FALSE): No error
 * 0x1 (TRUE): Error
 */
#define SDXC_INT_STAT_ADMA_ERR_MASK (0x2000000UL)
#define SDXC_INT_STAT_ADMA_ERR_SHIFT (25U)
#define SDXC_INT_STAT_ADMA_ERR_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_ADMA_ERR_SHIFT) & SDXC_INT_STAT_ADMA_ERR_MASK)
#define SDXC_INT_STAT_ADMA_ERR_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_ADMA_ERR_MASK) >> SDXC_INT_STAT_ADMA_ERR_SHIFT)

/*
 * AUTO_CMD_ERR (R/W1C)
 *
 * Auto CMD Error 
 * This error status is used by Auto CMD12 and Auto CMD23 in SD/eMMC mode. This bit is set when detecting that any of the bits D00 to D05 in Auto CMD Error Status register has changed from 0 to 1. D07 is effective in case of Auto CMD12. Auto CMD Error Status register is valid while this bit is set to 1 and may be cleared by clearing of this bit. 
 * In UHS-II mode, this bit is irrelevant. 
 * Values: 
 * 0x0 (FALSE): No error
 * 0x1 (TRUE): Error
 */
#define SDXC_INT_STAT_AUTO_CMD_ERR_MASK (0x1000000UL)
#define SDXC_INT_STAT_AUTO_CMD_ERR_SHIFT (24U)
#define SDXC_INT_STAT_AUTO_CMD_ERR_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_AUTO_CMD_ERR_SHIFT) & SDXC_INT_STAT_AUTO_CMD_ERR_MASK)
#define SDXC_INT_STAT_AUTO_CMD_ERR_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_AUTO_CMD_ERR_MASK) >> SDXC_INT_STAT_AUTO_CMD_ERR_SHIFT)

/*
 * CUR_LMT_ERR (R/W1C)
 *
 * Current Limit Error 
 * By setting the SD Bus Power bit in the Power Control register, the Host Controller is requested to supply power for the SD Bus. If the Host Controller supports the Current Limit function, it can be protected from an illegal card by stopping power supply to the card in which case this bit indicates a failure status. A reading of 1 for this bit means that the Host Controller is not supplying power to the SD card due to some failure. A reading of 0 for this bit means that the Host Controller is supplying power and no error has occurred. The Host Controller may require some sampling time to detect the current limit. DWC_mshc Host Controller does not support this function, this bit is always set to 0.
 * Values: 
 * 0x0 (FALSE): No error
 * 0x1 (TRUE): Power Fail
 */
#define SDXC_INT_STAT_CUR_LMT_ERR_MASK (0x800000UL)
#define SDXC_INT_STAT_CUR_LMT_ERR_SHIFT (23U)
#define SDXC_INT_STAT_CUR_LMT_ERR_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_CUR_LMT_ERR_SHIFT) & SDXC_INT_STAT_CUR_LMT_ERR_MASK)
#define SDXC_INT_STAT_CUR_LMT_ERR_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_CUR_LMT_ERR_MASK) >> SDXC_INT_STAT_CUR_LMT_ERR_SHIFT)

/*
 * DATA_END_BIT_ERR (R/W1C)
 *
 * Data End Bit Error 
 * This error occurs in SD/eMMC mode either when detecting 0 at the end bit position of read data that uses the DAT line or at the end bit position of the CRC status. 
 * In UHS-II mode, this bit is irrelevant. 
 * Values: 
 * 0x0 (FALSE): No error
 * 0x1 (TRUE): Error
 */
#define SDXC_INT_STAT_DATA_END_BIT_ERR_MASK (0x400000UL)
#define SDXC_INT_STAT_DATA_END_BIT_ERR_SHIFT (22U)
#define SDXC_INT_STAT_DATA_END_BIT_ERR_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_DATA_END_BIT_ERR_SHIFT) & SDXC_INT_STAT_DATA_END_BIT_ERR_MASK)
#define SDXC_INT_STAT_DATA_END_BIT_ERR_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_DATA_END_BIT_ERR_MASK) >> SDXC_INT_STAT_DATA_END_BIT_ERR_SHIFT)

/*
 * DATA_CRC_ERR (R/W1C)
 *
 * Data CRC Error
 * This error occurs in SD/eMMC mode when detecting CRC error when transferring read data which uses the DAT line, when detecting the Write CRC status having a value of other than 010 or when write CRC status timeout. 
 * In UHS-II mode, this bit is irrelevant. 
 * Values: 
 * 0x0 (FALSE): No error
 * 0x1 (TRUE): Error
 */
#define SDXC_INT_STAT_DATA_CRC_ERR_MASK (0x200000UL)
#define SDXC_INT_STAT_DATA_CRC_ERR_SHIFT (21U)
#define SDXC_INT_STAT_DATA_CRC_ERR_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_DATA_CRC_ERR_SHIFT) & SDXC_INT_STAT_DATA_CRC_ERR_MASK)
#define SDXC_INT_STAT_DATA_CRC_ERR_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_DATA_CRC_ERR_MASK) >> SDXC_INT_STAT_DATA_CRC_ERR_SHIFT)

/*
 * DATA_TOUT_ERR (R/W1C)
 *
 * Data Timeout Error
 * This bit is set in SD/eMMC mode when detecting one of the following timeout conditions:
 * Busy timeout for R1b, R5b type
 * Busy timeout after Write CRC status
 * Write CRC Status timeout
 * Read Data timeout
 * In UHS-II mode, this bit is irrelevant. 
 * Values: 
 * 0x0 (FALSE): No error
 * 0x1 (TRUE): Time out
 */
#define SDXC_INT_STAT_DATA_TOUT_ERR_MASK (0x100000UL)
#define SDXC_INT_STAT_DATA_TOUT_ERR_SHIFT (20U)
#define SDXC_INT_STAT_DATA_TOUT_ERR_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_DATA_TOUT_ERR_SHIFT) & SDXC_INT_STAT_DATA_TOUT_ERR_MASK)
#define SDXC_INT_STAT_DATA_TOUT_ERR_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_DATA_TOUT_ERR_MASK) >> SDXC_INT_STAT_DATA_TOUT_ERR_SHIFT)

/*
 * CMD_IDX_ERR (R/W1C)
 *
 * Command Index Error
 * This bit is set if a Command Index error occurs in the command respons in SD/eMMC mode. 
 * In UHS-II mode, this bit is irrelevant. 
 * Values: 
 * 0x0 (FALSE): No error
 * 0x1 (TRUE): Error
 */
#define SDXC_INT_STAT_CMD_IDX_ERR_MASK (0x80000UL)
#define SDXC_INT_STAT_CMD_IDX_ERR_SHIFT (19U)
#define SDXC_INT_STAT_CMD_IDX_ERR_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_CMD_IDX_ERR_SHIFT) & SDXC_INT_STAT_CMD_IDX_ERR_MASK)
#define SDXC_INT_STAT_CMD_IDX_ERR_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_CMD_IDX_ERR_MASK) >> SDXC_INT_STAT_CMD_IDX_ERR_SHIFT)

/*
 * CMD_END_BIT_ERR (R/W1C)
 *
 * Command End Bit Error
 * This bit is set when detecting that the end bit of a command response is 0 in SD/eMMC mode. 
 * In UHS-II mode, this bit is irrelevant. 
 * Values: 
 * 0x0 (FALSE): No error
 * 0x1 (TRUE): End Bit error generated
 */
#define SDXC_INT_STAT_CMD_END_BIT_ERR_MASK (0x40000UL)
#define SDXC_INT_STAT_CMD_END_BIT_ERR_SHIFT (18U)
#define SDXC_INT_STAT_CMD_END_BIT_ERR_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_CMD_END_BIT_ERR_SHIFT) & SDXC_INT_STAT_CMD_END_BIT_ERR_MASK)
#define SDXC_INT_STAT_CMD_END_BIT_ERR_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_CMD_END_BIT_ERR_MASK) >> SDXC_INT_STAT_CMD_END_BIT_ERR_SHIFT)

/*
 * CMD_CRC_ERR (R/W1C)
 *
 * Command CRC Error 
 * Command CRC Error is generated in SD/eMMC mode for following two cases.
 * If a response is returned and the Command Timeout Error is set to 0 (indicating no timeout), this bit is set to 1 when detecting a CRC error in the command response.
 * The Host Controller detects a CMD line conflict by monitoring the CMD line when a command is issued. If the Host Controller drives the CMD line to 1 level, but detects 0 level on the CMD line at the next SD clock edge, then the Host Controller aborts the command (stop driving CMD line) and set this bit to 1. The Command Timeout Error is also set to 1 to distinguish a CMD line conflict.
 * In UHS-II mode, this bit is irrelevant. 
 * Values: 
 * 0x0 (FALSE): No error
 * 0x1 (TRUE): CRC error generated
 */
#define SDXC_INT_STAT_CMD_CRC_ERR_MASK (0x20000UL)
#define SDXC_INT_STAT_CMD_CRC_ERR_SHIFT (17U)
#define SDXC_INT_STAT_CMD_CRC_ERR_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_CMD_CRC_ERR_SHIFT) & SDXC_INT_STAT_CMD_CRC_ERR_MASK)
#define SDXC_INT_STAT_CMD_CRC_ERR_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_CMD_CRC_ERR_MASK) >> SDXC_INT_STAT_CMD_CRC_ERR_SHIFT)

/*
 * CMD_TOUT_ERR (R/W1C)
 *
 * Command Timeout Error 
 * In SD/eMMC Mode,this bit is set only if no response is returned within 64 SD clock cycles from the end bit of the command. If the Host Controller detects a CMD line conflict, along with Command CRC Error bit, this bit is set to 1, without waiting for 64 SD/eMMC card clock cycles. In UHS-II mode, this bit is irrelevant. 
 * Values: 
 * 0x0 (FALSE): No error
 * 0x1 (TRUE): Time out
 */
#define SDXC_INT_STAT_CMD_TOUT_ERR_MASK (0x10000UL)
#define SDXC_INT_STAT_CMD_TOUT_ERR_SHIFT (16U)
#define SDXC_INT_STAT_CMD_TOUT_ERR_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_CMD_TOUT_ERR_SHIFT) & SDXC_INT_STAT_CMD_TOUT_ERR_MASK)
#define SDXC_INT_STAT_CMD_TOUT_ERR_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_CMD_TOUT_ERR_MASK) >> SDXC_INT_STAT_CMD_TOUT_ERR_SHIFT)

/*
 * ERR_INTERRUPT (R)
 *
 * Error Interrupt
 * If any of the bits in the Error Interrupt Status register are set, then this bit is set.
 * Values: 
 * 0x0 (FALSE): No Error
 * 0x1 (TRUE): Error
 */
#define SDXC_INT_STAT_ERR_INTERRUPT_MASK (0x8000U)
#define SDXC_INT_STAT_ERR_INTERRUPT_SHIFT (15U)
#define SDXC_INT_STAT_ERR_INTERRUPT_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_ERR_INTERRUPT_MASK) >> SDXC_INT_STAT_ERR_INTERRUPT_SHIFT)

/*
 * CQE_EVENT (R/W1C)
 *
 * Command Queuing Event
 * This status is set if Command Queuing/Crypto related event has occurred in eMMC/SD mode. Read CQHCI's CQIS/CRNQIS register for more details. In UHS-II Mode, this bit is irrelevant. 
 * Values: 
 * 0x0 (FALSE): No Event
 * 0x1 (TRUE): Command Queuing Event is detected
 */
#define SDXC_INT_STAT_CQE_EVENT_MASK (0x4000U)
#define SDXC_INT_STAT_CQE_EVENT_SHIFT (14U)
#define SDXC_INT_STAT_CQE_EVENT_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_CQE_EVENT_SHIFT) & SDXC_INT_STAT_CQE_EVENT_MASK)
#define SDXC_INT_STAT_CQE_EVENT_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_CQE_EVENT_MASK) >> SDXC_INT_STAT_CQE_EVENT_SHIFT)

/*
 * FX_EVENT (R)
 *
 * FX Event
 * This status is set when R[14] of response register is set to 1 and Response Type R1/R5 is set to 0 in Transfer Mode register. This interrupt is used with response check function.
 * Values: 
 * 0x0 (FALSE): No Event
 * 0x1 (TRUE): FX Event is detected
 */
#define SDXC_INT_STAT_FX_EVENT_MASK (0x2000U)
#define SDXC_INT_STAT_FX_EVENT_SHIFT (13U)
#define SDXC_INT_STAT_FX_EVENT_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_FX_EVENT_MASK) >> SDXC_INT_STAT_FX_EVENT_SHIFT)

/*
 * RE_TUNE_EVENT (R)
 *
 * Re-tuning Event 
 * This bit is set if the Re-Tuning Request changes from 0 to 1. Re-Tuning request is not supported.
 */
#define SDXC_INT_STAT_RE_TUNE_EVENT_MASK (0x1000U)
#define SDXC_INT_STAT_RE_TUNE_EVENT_SHIFT (12U)
#define SDXC_INT_STAT_RE_TUNE_EVENT_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_RE_TUNE_EVENT_MASK) >> SDXC_INT_STAT_RE_TUNE_EVENT_SHIFT)

/*
 * CARD_INTERRUPT (R)
 *
 * Card Interrupt
 * This bit reflects the synchronized value of:
 * DAT[1] Interrupt Input for SD Mode
 * DAT[2] Interrupt Input for UHS-II Mode
 * Values: 
 * 0x0 (FALSE): No Card Interrupt
 * 0x1 (TRUE): Generate Card Interrupt
 */
#define SDXC_INT_STAT_CARD_INTERRUPT_MASK (0x100U)
#define SDXC_INT_STAT_CARD_INTERRUPT_SHIFT (8U)
#define SDXC_INT_STAT_CARD_INTERRUPT_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_CARD_INTERRUPT_MASK) >> SDXC_INT_STAT_CARD_INTERRUPT_SHIFT)

/*
 * CARD_REMOVAL (R/W1C)
 *
 * Card Removal
 * This bit is set if the Card Inserted in the Present State register changes from 1 to 0.
 * Values: 
 * 0x0 (FALSE): Card state stable or Debouncing
 * 0x1 (TRUE): Card Removed
 */
#define SDXC_INT_STAT_CARD_REMOVAL_MASK (0x80U)
#define SDXC_INT_STAT_CARD_REMOVAL_SHIFT (7U)
#define SDXC_INT_STAT_CARD_REMOVAL_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_CARD_REMOVAL_SHIFT) & SDXC_INT_STAT_CARD_REMOVAL_MASK)
#define SDXC_INT_STAT_CARD_REMOVAL_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_CARD_REMOVAL_MASK) >> SDXC_INT_STAT_CARD_REMOVAL_SHIFT)

/*
 * CARD_INSERTION (R/W1C)
 *
 * Card Insertion
 * This bit is set if the Card Inserted in the Present State register changes from 0 to 1.
 * Values: 
 * 0x0 (FALSE): Card state stable or Debouncing
 * 0x1 (TRUE): Card Inserted
 */
#define SDXC_INT_STAT_CARD_INSERTION_MASK (0x40U)
#define SDXC_INT_STAT_CARD_INSERTION_SHIFT (6U)
#define SDXC_INT_STAT_CARD_INSERTION_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_CARD_INSERTION_SHIFT) & SDXC_INT_STAT_CARD_INSERTION_MASK)
#define SDXC_INT_STAT_CARD_INSERTION_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_CARD_INSERTION_MASK) >> SDXC_INT_STAT_CARD_INSERTION_SHIFT)

/*
 * BUF_RD_READY (R/W1C)
 *
 * Buffer Read Ready
 * This bit is set if the Buffer Read Enable changes from 0 to 1.
 * Values: 
 * 0x0 (FALSE): Not ready to read buffer
 * 0x1 (TRUE): Ready to read buffer
 */
#define SDXC_INT_STAT_BUF_RD_READY_MASK (0x20U)
#define SDXC_INT_STAT_BUF_RD_READY_SHIFT (5U)
#define SDXC_INT_STAT_BUF_RD_READY_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_BUF_RD_READY_SHIFT) & SDXC_INT_STAT_BUF_RD_READY_MASK)
#define SDXC_INT_STAT_BUF_RD_READY_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_BUF_RD_READY_MASK) >> SDXC_INT_STAT_BUF_RD_READY_SHIFT)

/*
 * BUF_WR_READY (R/W1C)
 *
 * Buffer Write Ready
 * This bit is set if the Buffer Write Enable changes from 0 to 1.
 * Values: 
 * 0x0 (FALSE): Not ready to write buffer
 * 0x1 (TRUE): Ready to write buffer
 */
#define SDXC_INT_STAT_BUF_WR_READY_MASK (0x10U)
#define SDXC_INT_STAT_BUF_WR_READY_SHIFT (4U)
#define SDXC_INT_STAT_BUF_WR_READY_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_BUF_WR_READY_SHIFT) & SDXC_INT_STAT_BUF_WR_READY_MASK)
#define SDXC_INT_STAT_BUF_WR_READY_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_BUF_WR_READY_MASK) >> SDXC_INT_STAT_BUF_WR_READY_SHIFT)

/*
 * DMA_INTERRUPT (R/W1C)
 *
 * DMA Interrupt
 * This bit is set if the Host Controller detects the SDMA Buffer Boundary during transfer. In case of ADMA, by setting the Int field in the descriptor table, the Host controller generates this interrupt. This interrupt is not generated after a Transfer Complete.
 * Values: 
 * 0x0 (FALSE): No DMA Interrupt
 * 0x1 (TRUE): DMA Interrupt is generated
 */
#define SDXC_INT_STAT_DMA_INTERRUPT_MASK (0x8U)
#define SDXC_INT_STAT_DMA_INTERRUPT_SHIFT (3U)
#define SDXC_INT_STAT_DMA_INTERRUPT_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_DMA_INTERRUPT_SHIFT) & SDXC_INT_STAT_DMA_INTERRUPT_MASK)
#define SDXC_INT_STAT_DMA_INTERRUPT_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_DMA_INTERRUPT_MASK) >> SDXC_INT_STAT_DMA_INTERRUPT_SHIFT)

/*
 * BGAP_EVENT (R/W1C)
 *
 * Block Gap Event
 * This bit is set when both read/write transaction is stopped at block gap due to a Stop at Block Gap Request.
 * Values: 
 * 0x0 (FALSE): No Block Gap Event
 * 0x1 (TRUE): Transaction stopped at block gap
 */
#define SDXC_INT_STAT_BGAP_EVENT_MASK (0x4U)
#define SDXC_INT_STAT_BGAP_EVENT_SHIFT (2U)
#define SDXC_INT_STAT_BGAP_EVENT_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_BGAP_EVENT_SHIFT) & SDXC_INT_STAT_BGAP_EVENT_MASK)
#define SDXC_INT_STAT_BGAP_EVENT_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_BGAP_EVENT_MASK) >> SDXC_INT_STAT_BGAP_EVENT_SHIFT)

/*
 * XFER_COMPLETE (R/W1C)
 *
 * Transfer Complete
 * This bit is set when a read/write transfer and a command with status busy is completed.
 * Values: 
 * 0x0 (FALSE): Not complete
 * 0x1 (TRUE): Command execution is completed
 */
#define SDXC_INT_STAT_XFER_COMPLETE_MASK (0x2U)
#define SDXC_INT_STAT_XFER_COMPLETE_SHIFT (1U)
#define SDXC_INT_STAT_XFER_COMPLETE_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_XFER_COMPLETE_SHIFT) & SDXC_INT_STAT_XFER_COMPLETE_MASK)
#define SDXC_INT_STAT_XFER_COMPLETE_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_XFER_COMPLETE_MASK) >> SDXC_INT_STAT_XFER_COMPLETE_SHIFT)

/*
 * CMD_COMPLETE (R/W1C)
 *
 * Command Complete 
 * In an SD/eMMC Mode, this bit is set when the end bit of a response except for Auto CMD12 and Auto CMD23. In UHS-II Mode, this bit is set when response packet is received. 
 * This interrupt is not generated when the Response Interrupt Disable in Transfer Mode Register is set to 1.
 * Values: 
 * 0x0 (FALSE): No command complete
 * 0x1 (TRUE): Command Complete
 */
#define SDXC_INT_STAT_CMD_COMPLETE_MASK (0x1U)
#define SDXC_INT_STAT_CMD_COMPLETE_SHIFT (0U)
#define SDXC_INT_STAT_CMD_COMPLETE_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_CMD_COMPLETE_SHIFT) & SDXC_INT_STAT_CMD_COMPLETE_MASK)
#define SDXC_INT_STAT_CMD_COMPLETE_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_CMD_COMPLETE_MASK) >> SDXC_INT_STAT_CMD_COMPLETE_SHIFT)

/* Bitfield definition for register: INT_STAT_EN */
/*
 * BOOT_ACK_ERR_STAT_EN (RW)
 *
 * Boot Acknowledgment Error (eMMC Mode only) 
 * Setting this bit to 1 enables setting of Boot Acknowledgment Error in Error Interrupt Status register (ERROR_INT_STAT_R).
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_BOOT_ACK_ERR_STAT_EN_MASK (0x10000000UL)
#define SDXC_INT_STAT_EN_BOOT_ACK_ERR_STAT_EN_SHIFT (28U)
#define SDXC_INT_STAT_EN_BOOT_ACK_ERR_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_BOOT_ACK_ERR_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_BOOT_ACK_ERR_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_BOOT_ACK_ERR_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_BOOT_ACK_ERR_STAT_EN_MASK) >> SDXC_INT_STAT_EN_BOOT_ACK_ERR_STAT_EN_SHIFT)

/*
 * RESP_ERR_STAT_EN (RW)
 *
 * Response Error Status Enable (SD Mode only)
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_RESP_ERR_STAT_EN_MASK (0x8000000UL)
#define SDXC_INT_STAT_EN_RESP_ERR_STAT_EN_SHIFT (27U)
#define SDXC_INT_STAT_EN_RESP_ERR_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_RESP_ERR_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_RESP_ERR_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_RESP_ERR_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_RESP_ERR_STAT_EN_MASK) >> SDXC_INT_STAT_EN_RESP_ERR_STAT_EN_SHIFT)

/*
 * TUNING_ERR_STAT_EN (RW)
 *
 * Tuning Error Status Enable (UHS-I Mode only)
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_TUNING_ERR_STAT_EN_MASK (0x4000000UL)
#define SDXC_INT_STAT_EN_TUNING_ERR_STAT_EN_SHIFT (26U)
#define SDXC_INT_STAT_EN_TUNING_ERR_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_TUNING_ERR_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_TUNING_ERR_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_TUNING_ERR_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_TUNING_ERR_STAT_EN_MASK) >> SDXC_INT_STAT_EN_TUNING_ERR_STAT_EN_SHIFT)

/*
 * ADMA_ERR_STAT_EN (RW)
 *
 * ADMA Error Status Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_ADMA_ERR_STAT_EN_MASK (0x2000000UL)
#define SDXC_INT_STAT_EN_ADMA_ERR_STAT_EN_SHIFT (25U)
#define SDXC_INT_STAT_EN_ADMA_ERR_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_ADMA_ERR_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_ADMA_ERR_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_ADMA_ERR_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_ADMA_ERR_STAT_EN_MASK) >> SDXC_INT_STAT_EN_ADMA_ERR_STAT_EN_SHIFT)

/*
 * AUTO_CMD_ERR_STAT_EN (RW)
 *
 * Auto CMD Error Status Enable (SD/eMMC Mode only).
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_AUTO_CMD_ERR_STAT_EN_MASK (0x1000000UL)
#define SDXC_INT_STAT_EN_AUTO_CMD_ERR_STAT_EN_SHIFT (24U)
#define SDXC_INT_STAT_EN_AUTO_CMD_ERR_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_AUTO_CMD_ERR_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_AUTO_CMD_ERR_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_AUTO_CMD_ERR_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_AUTO_CMD_ERR_STAT_EN_MASK) >> SDXC_INT_STAT_EN_AUTO_CMD_ERR_STAT_EN_SHIFT)

/*
 * CUR_LMT_ERR_STAT_EN (RW)
 *
 * Current Limit Error Status Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_CUR_LMT_ERR_STAT_EN_MASK (0x800000UL)
#define SDXC_INT_STAT_EN_CUR_LMT_ERR_STAT_EN_SHIFT (23U)
#define SDXC_INT_STAT_EN_CUR_LMT_ERR_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_CUR_LMT_ERR_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_CUR_LMT_ERR_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_CUR_LMT_ERR_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_CUR_LMT_ERR_STAT_EN_MASK) >> SDXC_INT_STAT_EN_CUR_LMT_ERR_STAT_EN_SHIFT)

/*
 * DATA_END_BIT_ERR_STAT_EN (RW)
 *
 * Data End Bit Error Status Enable (SD/eMMC Mode only).
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_DATA_END_BIT_ERR_STAT_EN_MASK (0x400000UL)
#define SDXC_INT_STAT_EN_DATA_END_BIT_ERR_STAT_EN_SHIFT (22U)
#define SDXC_INT_STAT_EN_DATA_END_BIT_ERR_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_DATA_END_BIT_ERR_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_DATA_END_BIT_ERR_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_DATA_END_BIT_ERR_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_DATA_END_BIT_ERR_STAT_EN_MASK) >> SDXC_INT_STAT_EN_DATA_END_BIT_ERR_STAT_EN_SHIFT)

/*
 * DATA_CRC_ERR_STAT_EN (RW)
 *
 * Data CRC Error Status Enable (SD/eMMC Mode only)
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_DATA_CRC_ERR_STAT_EN_MASK (0x200000UL)
#define SDXC_INT_STAT_EN_DATA_CRC_ERR_STAT_EN_SHIFT (21U)
#define SDXC_INT_STAT_EN_DATA_CRC_ERR_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_DATA_CRC_ERR_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_DATA_CRC_ERR_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_DATA_CRC_ERR_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_DATA_CRC_ERR_STAT_EN_MASK) >> SDXC_INT_STAT_EN_DATA_CRC_ERR_STAT_EN_SHIFT)

/*
 * DATA_TOUT_ERR_STAT_EN (RW)
 *
 * Data Timeout Error Status Enable (SD/eMMC Mode only)
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_DATA_TOUT_ERR_STAT_EN_MASK (0x100000UL)
#define SDXC_INT_STAT_EN_DATA_TOUT_ERR_STAT_EN_SHIFT (20U)
#define SDXC_INT_STAT_EN_DATA_TOUT_ERR_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_DATA_TOUT_ERR_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_DATA_TOUT_ERR_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_DATA_TOUT_ERR_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_DATA_TOUT_ERR_STAT_EN_MASK) >> SDXC_INT_STAT_EN_DATA_TOUT_ERR_STAT_EN_SHIFT)

/*
 * CMD_IDX_ERR_STAT_EN (RW)
 *
 * Command Index Error Status Enable (SD/eMMC Mode only)
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_CMD_IDX_ERR_STAT_EN_MASK (0x80000UL)
#define SDXC_INT_STAT_EN_CMD_IDX_ERR_STAT_EN_SHIFT (19U)
#define SDXC_INT_STAT_EN_CMD_IDX_ERR_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_CMD_IDX_ERR_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_CMD_IDX_ERR_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_CMD_IDX_ERR_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_CMD_IDX_ERR_STAT_EN_MASK) >> SDXC_INT_STAT_EN_CMD_IDX_ERR_STAT_EN_SHIFT)

/*
 * CMD_END_BIT_ERR_STAT_EN (RW)
 *
 * Command End Bit Error Status Enable (SD/eMMC Mode only)
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_CMD_END_BIT_ERR_STAT_EN_MASK (0x40000UL)
#define SDXC_INT_STAT_EN_CMD_END_BIT_ERR_STAT_EN_SHIFT (18U)
#define SDXC_INT_STAT_EN_CMD_END_BIT_ERR_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_CMD_END_BIT_ERR_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_CMD_END_BIT_ERR_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_CMD_END_BIT_ERR_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_CMD_END_BIT_ERR_STAT_EN_MASK) >> SDXC_INT_STAT_EN_CMD_END_BIT_ERR_STAT_EN_SHIFT)

/*
 * CMD_CRC_ERR_STAT_EN (RW)
 *
 * Command CRC Error Status Enable (SD/eMMC Mode only)
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_CMD_CRC_ERR_STAT_EN_MASK (0x20000UL)
#define SDXC_INT_STAT_EN_CMD_CRC_ERR_STAT_EN_SHIFT (17U)
#define SDXC_INT_STAT_EN_CMD_CRC_ERR_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_CMD_CRC_ERR_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_CMD_CRC_ERR_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_CMD_CRC_ERR_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_CMD_CRC_ERR_STAT_EN_MASK) >> SDXC_INT_STAT_EN_CMD_CRC_ERR_STAT_EN_SHIFT)

/*
 * CMD_TOUT_ERR_STAT_EN (RW)
 *
 * Command Timeout Error Status Enable (SD/eMMC Mode only).
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_CMD_TOUT_ERR_STAT_EN_MASK (0x10000UL)
#define SDXC_INT_STAT_EN_CMD_TOUT_ERR_STAT_EN_SHIFT (16U)
#define SDXC_INT_STAT_EN_CMD_TOUT_ERR_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_CMD_TOUT_ERR_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_CMD_TOUT_ERR_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_CMD_TOUT_ERR_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_CMD_TOUT_ERR_STAT_EN_MASK) >> SDXC_INT_STAT_EN_CMD_TOUT_ERR_STAT_EN_SHIFT)

/*
 * CQE_EVENT_STAT_EN (RW)
 *
 * CQE Event Status Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_CQE_EVENT_STAT_EN_MASK (0x4000U)
#define SDXC_INT_STAT_EN_CQE_EVENT_STAT_EN_SHIFT (14U)
#define SDXC_INT_STAT_EN_CQE_EVENT_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_CQE_EVENT_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_CQE_EVENT_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_CQE_EVENT_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_CQE_EVENT_STAT_EN_MASK) >> SDXC_INT_STAT_EN_CQE_EVENT_STAT_EN_SHIFT)

/*
 * FX_EVENT_STAT_EN (RW)
 *
 * FX Event Status Enable
 * This bit is added from Version 4.10.
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_FX_EVENT_STAT_EN_MASK (0x2000U)
#define SDXC_INT_STAT_EN_FX_EVENT_STAT_EN_SHIFT (13U)
#define SDXC_INT_STAT_EN_FX_EVENT_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_FX_EVENT_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_FX_EVENT_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_FX_EVENT_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_FX_EVENT_STAT_EN_MASK) >> SDXC_INT_STAT_EN_FX_EVENT_STAT_EN_SHIFT)

/*
 * RE_TUNE_EVENT_STAT_EN (RW)
 *
 * Re-Tuning Event (UHS-I only) Status Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_RE_TUNE_EVENT_STAT_EN_MASK (0x1000U)
#define SDXC_INT_STAT_EN_RE_TUNE_EVENT_STAT_EN_SHIFT (12U)
#define SDXC_INT_STAT_EN_RE_TUNE_EVENT_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_RE_TUNE_EVENT_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_RE_TUNE_EVENT_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_RE_TUNE_EVENT_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_RE_TUNE_EVENT_STAT_EN_MASK) >> SDXC_INT_STAT_EN_RE_TUNE_EVENT_STAT_EN_SHIFT)

/*
 * CARD_INTERRUPT_STAT_EN (RW)
 *
 * Card Interrupt Status Enable
 * If this bit is set to 0, the Host Controller clears the interrupt request to the System. The Card Interrupt detection is stopped when this bit is cleared and restarted when this bit is set to 1. The Host Driver may clear the Card Interrupt Status Enable before servicing the Card Interrupt and may set this bit again after all interrupt requests from the card are cleared to prevent inadvertent interrupts.
 * By setting this bit to 0, interrupt input must be masked by implementation so that the interrupt input is not affected by external signal in any state (for example, floating).
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_CARD_INTERRUPT_STAT_EN_MASK (0x100U)
#define SDXC_INT_STAT_EN_CARD_INTERRUPT_STAT_EN_SHIFT (8U)
#define SDXC_INT_STAT_EN_CARD_INTERRUPT_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_CARD_INTERRUPT_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_CARD_INTERRUPT_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_CARD_INTERRUPT_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_CARD_INTERRUPT_STAT_EN_MASK) >> SDXC_INT_STAT_EN_CARD_INTERRUPT_STAT_EN_SHIFT)

/*
 * CARD_REMOVAL_STAT_EN (RW)
 *
 * Card Removal Status Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_CARD_REMOVAL_STAT_EN_MASK (0x80U)
#define SDXC_INT_STAT_EN_CARD_REMOVAL_STAT_EN_SHIFT (7U)
#define SDXC_INT_STAT_EN_CARD_REMOVAL_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_CARD_REMOVAL_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_CARD_REMOVAL_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_CARD_REMOVAL_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_CARD_REMOVAL_STAT_EN_MASK) >> SDXC_INT_STAT_EN_CARD_REMOVAL_STAT_EN_SHIFT)

/*
 * CARD_INSERTION_STAT_EN (RW)
 *
 * Card Insertion Status Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_CARD_INSERTION_STAT_EN_MASK (0x40U)
#define SDXC_INT_STAT_EN_CARD_INSERTION_STAT_EN_SHIFT (6U)
#define SDXC_INT_STAT_EN_CARD_INSERTION_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_CARD_INSERTION_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_CARD_INSERTION_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_CARD_INSERTION_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_CARD_INSERTION_STAT_EN_MASK) >> SDXC_INT_STAT_EN_CARD_INSERTION_STAT_EN_SHIFT)

/*
 * BUF_RD_READY_STAT_EN (RW)
 *
 * Buffer Read Ready Status Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_BUF_RD_READY_STAT_EN_MASK (0x20U)
#define SDXC_INT_STAT_EN_BUF_RD_READY_STAT_EN_SHIFT (5U)
#define SDXC_INT_STAT_EN_BUF_RD_READY_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_BUF_RD_READY_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_BUF_RD_READY_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_BUF_RD_READY_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_BUF_RD_READY_STAT_EN_MASK) >> SDXC_INT_STAT_EN_BUF_RD_READY_STAT_EN_SHIFT)

/*
 * BUF_WR_READY_STAT_EN (RW)
 *
 * Buffer Write Ready Status Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_BUF_WR_READY_STAT_EN_MASK (0x10U)
#define SDXC_INT_STAT_EN_BUF_WR_READY_STAT_EN_SHIFT (4U)
#define SDXC_INT_STAT_EN_BUF_WR_READY_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_BUF_WR_READY_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_BUF_WR_READY_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_BUF_WR_READY_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_BUF_WR_READY_STAT_EN_MASK) >> SDXC_INT_STAT_EN_BUF_WR_READY_STAT_EN_SHIFT)

/*
 * DMA_INTERRUPT_STAT_EN (RW)
 *
 * DMA Interrupt Status Enable 
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_DMA_INTERRUPT_STAT_EN_MASK (0x8U)
#define SDXC_INT_STAT_EN_DMA_INTERRUPT_STAT_EN_SHIFT (3U)
#define SDXC_INT_STAT_EN_DMA_INTERRUPT_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_DMA_INTERRUPT_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_DMA_INTERRUPT_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_DMA_INTERRUPT_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_DMA_INTERRUPT_STAT_EN_MASK) >> SDXC_INT_STAT_EN_DMA_INTERRUPT_STAT_EN_SHIFT)

/*
 * BGAP_EVENT_STAT_EN (RW)
 *
 * Block Gap Event Status Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_BGAP_EVENT_STAT_EN_MASK (0x4U)
#define SDXC_INT_STAT_EN_BGAP_EVENT_STAT_EN_SHIFT (2U)
#define SDXC_INT_STAT_EN_BGAP_EVENT_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_BGAP_EVENT_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_BGAP_EVENT_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_BGAP_EVENT_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_BGAP_EVENT_STAT_EN_MASK) >> SDXC_INT_STAT_EN_BGAP_EVENT_STAT_EN_SHIFT)

/*
 * XFER_COMPLETE_STAT_EN (RW)
 *
 * Transfer Complete Status Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_XFER_COMPLETE_STAT_EN_MASK (0x2U)
#define SDXC_INT_STAT_EN_XFER_COMPLETE_STAT_EN_SHIFT (1U)
#define SDXC_INT_STAT_EN_XFER_COMPLETE_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_XFER_COMPLETE_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_XFER_COMPLETE_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_XFER_COMPLETE_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_XFER_COMPLETE_STAT_EN_MASK) >> SDXC_INT_STAT_EN_XFER_COMPLETE_STAT_EN_SHIFT)

/*
 * CMD_COMPLETE_STAT_EN (RW)
 *
 * Command Complete Status Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_STAT_EN_CMD_COMPLETE_STAT_EN_MASK (0x1U)
#define SDXC_INT_STAT_EN_CMD_COMPLETE_STAT_EN_SHIFT (0U)
#define SDXC_INT_STAT_EN_CMD_COMPLETE_STAT_EN_SET(x) (((uint32_t)(x) << SDXC_INT_STAT_EN_CMD_COMPLETE_STAT_EN_SHIFT) & SDXC_INT_STAT_EN_CMD_COMPLETE_STAT_EN_MASK)
#define SDXC_INT_STAT_EN_CMD_COMPLETE_STAT_EN_GET(x) (((uint32_t)(x) & SDXC_INT_STAT_EN_CMD_COMPLETE_STAT_EN_MASK) >> SDXC_INT_STAT_EN_CMD_COMPLETE_STAT_EN_SHIFT)

/* Bitfield definition for register: INT_SIGNAL_EN */
/*
 * BOOT_ACK_ERR_SIGNAL_EN (RW)
 *
 * Boot Acknowledgment Error (eMMC Mode only).
 * Setting this bit to 1 enables generating interrupt signal when Boot Acknowledgement Error in Error Interrupt Status register is set.
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_BOOT_ACK_ERR_SIGNAL_EN_MASK (0x10000000UL)
#define SDXC_INT_SIGNAL_EN_BOOT_ACK_ERR_SIGNAL_EN_SHIFT (28U)
#define SDXC_INT_SIGNAL_EN_BOOT_ACK_ERR_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_BOOT_ACK_ERR_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_BOOT_ACK_ERR_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_BOOT_ACK_ERR_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_BOOT_ACK_ERR_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_BOOT_ACK_ERR_SIGNAL_EN_SHIFT)

/*
 * RESP_ERR_SIGNAL_EN (RW)
 *
 * Response Error Signal Enable (SD Mode only)
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_RESP_ERR_SIGNAL_EN_MASK (0x8000000UL)
#define SDXC_INT_SIGNAL_EN_RESP_ERR_SIGNAL_EN_SHIFT (27U)
#define SDXC_INT_SIGNAL_EN_RESP_ERR_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_RESP_ERR_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_RESP_ERR_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_RESP_ERR_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_RESP_ERR_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_RESP_ERR_SIGNAL_EN_SHIFT)

/*
 * TUNING_ERR_SIGNAL_EN (RW)
 *
 * Tuning Error Signal Enable (UHS-I Mode only)
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_TUNING_ERR_SIGNAL_EN_MASK (0x4000000UL)
#define SDXC_INT_SIGNAL_EN_TUNING_ERR_SIGNAL_EN_SHIFT (26U)
#define SDXC_INT_SIGNAL_EN_TUNING_ERR_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_TUNING_ERR_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_TUNING_ERR_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_TUNING_ERR_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_TUNING_ERR_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_TUNING_ERR_SIGNAL_EN_SHIFT)

/*
 * ADMA_ERR_SIGNAL_EN (RW)
 *
 * ADMA Error Signal Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_ADMA_ERR_SIGNAL_EN_MASK (0x2000000UL)
#define SDXC_INT_SIGNAL_EN_ADMA_ERR_SIGNAL_EN_SHIFT (25U)
#define SDXC_INT_SIGNAL_EN_ADMA_ERR_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_ADMA_ERR_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_ADMA_ERR_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_ADMA_ERR_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_ADMA_ERR_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_ADMA_ERR_SIGNAL_EN_SHIFT)

/*
 * AUTO_CMD_ERR_SIGNAL_EN (RW)
 *
 * Auto CMD Error Signal Enable (SD/eMMC Mode only)
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_AUTO_CMD_ERR_SIGNAL_EN_MASK (0x1000000UL)
#define SDXC_INT_SIGNAL_EN_AUTO_CMD_ERR_SIGNAL_EN_SHIFT (24U)
#define SDXC_INT_SIGNAL_EN_AUTO_CMD_ERR_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_AUTO_CMD_ERR_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_AUTO_CMD_ERR_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_AUTO_CMD_ERR_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_AUTO_CMD_ERR_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_AUTO_CMD_ERR_SIGNAL_EN_SHIFT)

/*
 * CUR_LMT_ERR_SIGNAL_EN (RW)
 *
 * Current Limit Error Signal Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_CUR_LMT_ERR_SIGNAL_EN_MASK (0x800000UL)
#define SDXC_INT_SIGNAL_EN_CUR_LMT_ERR_SIGNAL_EN_SHIFT (23U)
#define SDXC_INT_SIGNAL_EN_CUR_LMT_ERR_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_CUR_LMT_ERR_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_CUR_LMT_ERR_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_CUR_LMT_ERR_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_CUR_LMT_ERR_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_CUR_LMT_ERR_SIGNAL_EN_SHIFT)

/*
 * DATA_END_BIT_ERR_SIGNAL_EN (RW)
 *
 * Data End Bit Error Signal Enable (SD/eMMC Mode only)
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_DATA_END_BIT_ERR_SIGNAL_EN_MASK (0x400000UL)
#define SDXC_INT_SIGNAL_EN_DATA_END_BIT_ERR_SIGNAL_EN_SHIFT (22U)
#define SDXC_INT_SIGNAL_EN_DATA_END_BIT_ERR_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_DATA_END_BIT_ERR_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_DATA_END_BIT_ERR_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_DATA_END_BIT_ERR_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_DATA_END_BIT_ERR_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_DATA_END_BIT_ERR_SIGNAL_EN_SHIFT)

/*
 * DATA_CRC_ERR_SIGNAL_EN (RW)
 *
 * Data CRC Error Signal Enable (SD/eMMC Mode only)
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_DATA_CRC_ERR_SIGNAL_EN_MASK (0x200000UL)
#define SDXC_INT_SIGNAL_EN_DATA_CRC_ERR_SIGNAL_EN_SHIFT (21U)
#define SDXC_INT_SIGNAL_EN_DATA_CRC_ERR_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_DATA_CRC_ERR_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_DATA_CRC_ERR_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_DATA_CRC_ERR_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_DATA_CRC_ERR_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_DATA_CRC_ERR_SIGNAL_EN_SHIFT)

/*
 * DATA_TOUT_ERR_SIGNAL_EN (RW)
 *
 * Data Timeout Error Signal Enable (SD/eMMC Mode only)
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_DATA_TOUT_ERR_SIGNAL_EN_MASK (0x100000UL)
#define SDXC_INT_SIGNAL_EN_DATA_TOUT_ERR_SIGNAL_EN_SHIFT (20U)
#define SDXC_INT_SIGNAL_EN_DATA_TOUT_ERR_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_DATA_TOUT_ERR_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_DATA_TOUT_ERR_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_DATA_TOUT_ERR_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_DATA_TOUT_ERR_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_DATA_TOUT_ERR_SIGNAL_EN_SHIFT)

/*
 * CMD_IDX_ERR_SIGNAL_EN (RW)
 *
 * Command Index Error Signal Enable (SD/eMMC Mode only)
 * Values: 
 * 0x0 (FALSE): No error
 * 0x1 (TRUE): Error
 */
#define SDXC_INT_SIGNAL_EN_CMD_IDX_ERR_SIGNAL_EN_MASK (0x80000UL)
#define SDXC_INT_SIGNAL_EN_CMD_IDX_ERR_SIGNAL_EN_SHIFT (19U)
#define SDXC_INT_SIGNAL_EN_CMD_IDX_ERR_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_CMD_IDX_ERR_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_CMD_IDX_ERR_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_CMD_IDX_ERR_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_CMD_IDX_ERR_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_CMD_IDX_ERR_SIGNAL_EN_SHIFT)

/*
 * CMD_END_BIT_ERR_SIGNAL_EN (RW)
 *
 * Command End Bit Error Signal Enable (SD/eMMC Mode only)
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_CMD_END_BIT_ERR_SIGNAL_EN_MASK (0x40000UL)
#define SDXC_INT_SIGNAL_EN_CMD_END_BIT_ERR_SIGNAL_EN_SHIFT (18U)
#define SDXC_INT_SIGNAL_EN_CMD_END_BIT_ERR_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_CMD_END_BIT_ERR_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_CMD_END_BIT_ERR_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_CMD_END_BIT_ERR_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_CMD_END_BIT_ERR_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_CMD_END_BIT_ERR_SIGNAL_EN_SHIFT)

/*
 * CMD_CRC_ERR_SIGNAL_EN (RW)
 *
 * Command CRC Error Signal Enable (SD/eMMC Mode only)
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_CMD_CRC_ERR_SIGNAL_EN_MASK (0x20000UL)
#define SDXC_INT_SIGNAL_EN_CMD_CRC_ERR_SIGNAL_EN_SHIFT (17U)
#define SDXC_INT_SIGNAL_EN_CMD_CRC_ERR_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_CMD_CRC_ERR_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_CMD_CRC_ERR_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_CMD_CRC_ERR_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_CMD_CRC_ERR_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_CMD_CRC_ERR_SIGNAL_EN_SHIFT)

/*
 * CMD_TOUT_ERR_SIGNAL_EN (RW)
 *
 * Command Timeout Error Signal Enable (SD/eMMC Mode only)
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_CMD_TOUT_ERR_SIGNAL_EN_MASK (0x10000UL)
#define SDXC_INT_SIGNAL_EN_CMD_TOUT_ERR_SIGNAL_EN_SHIFT (16U)
#define SDXC_INT_SIGNAL_EN_CMD_TOUT_ERR_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_CMD_TOUT_ERR_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_CMD_TOUT_ERR_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_CMD_TOUT_ERR_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_CMD_TOUT_ERR_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_CMD_TOUT_ERR_SIGNAL_EN_SHIFT)

/*
 * CQE_EVENT_SIGNAL_EN (RW)
 *
 * Command Queuing Engine Event Signal Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_CQE_EVENT_SIGNAL_EN_MASK (0x4000U)
#define SDXC_INT_SIGNAL_EN_CQE_EVENT_SIGNAL_EN_SHIFT (14U)
#define SDXC_INT_SIGNAL_EN_CQE_EVENT_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_CQE_EVENT_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_CQE_EVENT_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_CQE_EVENT_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_CQE_EVENT_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_CQE_EVENT_SIGNAL_EN_SHIFT)

/*
 * FX_EVENT_SIGNAL_EN (RW)
 *
 * FX Event Signal Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_FX_EVENT_SIGNAL_EN_MASK (0x2000U)
#define SDXC_INT_SIGNAL_EN_FX_EVENT_SIGNAL_EN_SHIFT (13U)
#define SDXC_INT_SIGNAL_EN_FX_EVENT_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_FX_EVENT_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_FX_EVENT_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_FX_EVENT_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_FX_EVENT_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_FX_EVENT_SIGNAL_EN_SHIFT)

/*
 * RE_TUNE_EVENT_SIGNAL_EN (RW)
 *
 * Re-Tuning Event (UHS-I only) Signal Enable.
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_RE_TUNE_EVENT_SIGNAL_EN_MASK (0x1000U)
#define SDXC_INT_SIGNAL_EN_RE_TUNE_EVENT_SIGNAL_EN_SHIFT (12U)
#define SDXC_INT_SIGNAL_EN_RE_TUNE_EVENT_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_RE_TUNE_EVENT_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_RE_TUNE_EVENT_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_RE_TUNE_EVENT_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_RE_TUNE_EVENT_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_RE_TUNE_EVENT_SIGNAL_EN_SHIFT)

/*
 * CARD_INTERRUPT_SIGNAL_EN (RW)
 *
 * Card Interrupt Signal Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_CARD_INTERRUPT_SIGNAL_EN_MASK (0x100U)
#define SDXC_INT_SIGNAL_EN_CARD_INTERRUPT_SIGNAL_EN_SHIFT (8U)
#define SDXC_INT_SIGNAL_EN_CARD_INTERRUPT_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_CARD_INTERRUPT_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_CARD_INTERRUPT_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_CARD_INTERRUPT_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_CARD_INTERRUPT_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_CARD_INTERRUPT_SIGNAL_EN_SHIFT)

/*
 * CARD_REMOVAL_SIGNAL_EN (RW)
 *
 * Card Removal Signal Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_CARD_REMOVAL_SIGNAL_EN_MASK (0x80U)
#define SDXC_INT_SIGNAL_EN_CARD_REMOVAL_SIGNAL_EN_SHIFT (7U)
#define SDXC_INT_SIGNAL_EN_CARD_REMOVAL_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_CARD_REMOVAL_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_CARD_REMOVAL_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_CARD_REMOVAL_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_CARD_REMOVAL_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_CARD_REMOVAL_SIGNAL_EN_SHIFT)

/*
 * CARD_INSERTION_SIGNAL_EN (RW)
 *
 * Card Insertion Signal Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_CARD_INSERTION_SIGNAL_EN_MASK (0x40U)
#define SDXC_INT_SIGNAL_EN_CARD_INSERTION_SIGNAL_EN_SHIFT (6U)
#define SDXC_INT_SIGNAL_EN_CARD_INSERTION_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_CARD_INSERTION_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_CARD_INSERTION_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_CARD_INSERTION_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_CARD_INSERTION_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_CARD_INSERTION_SIGNAL_EN_SHIFT)

/*
 * BUF_RD_READY_SIGNAL_EN (RW)
 *
 * Buffer Read Ready Signal Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_BUF_RD_READY_SIGNAL_EN_MASK (0x20U)
#define SDXC_INT_SIGNAL_EN_BUF_RD_READY_SIGNAL_EN_SHIFT (5U)
#define SDXC_INT_SIGNAL_EN_BUF_RD_READY_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_BUF_RD_READY_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_BUF_RD_READY_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_BUF_RD_READY_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_BUF_RD_READY_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_BUF_RD_READY_SIGNAL_EN_SHIFT)

/*
 * BUF_WR_READY_SIGNAL_EN (RW)
 *
 * Buffer Write Ready Signal Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_BUF_WR_READY_SIGNAL_EN_MASK (0x10U)
#define SDXC_INT_SIGNAL_EN_BUF_WR_READY_SIGNAL_EN_SHIFT (4U)
#define SDXC_INT_SIGNAL_EN_BUF_WR_READY_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_BUF_WR_READY_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_BUF_WR_READY_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_BUF_WR_READY_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_BUF_WR_READY_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_BUF_WR_READY_SIGNAL_EN_SHIFT)

/*
 * DMA_INTERRUPT_SIGNAL_EN (RW)
 *
 * DMA Interrupt Signal Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_DMA_INTERRUPT_SIGNAL_EN_MASK (0x8U)
#define SDXC_INT_SIGNAL_EN_DMA_INTERRUPT_SIGNAL_EN_SHIFT (3U)
#define SDXC_INT_SIGNAL_EN_DMA_INTERRUPT_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_DMA_INTERRUPT_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_DMA_INTERRUPT_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_DMA_INTERRUPT_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_DMA_INTERRUPT_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_DMA_INTERRUPT_SIGNAL_EN_SHIFT)

/*
 * BGAP_EVENT_SIGNAL_EN (RW)
 *
 * Block Gap Event Signal Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_BGAP_EVENT_SIGNAL_EN_MASK (0x4U)
#define SDXC_INT_SIGNAL_EN_BGAP_EVENT_SIGNAL_EN_SHIFT (2U)
#define SDXC_INT_SIGNAL_EN_BGAP_EVENT_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_BGAP_EVENT_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_BGAP_EVENT_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_BGAP_EVENT_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_BGAP_EVENT_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_BGAP_EVENT_SIGNAL_EN_SHIFT)

/*
 * XFER_COMPLETE_SIGNAL_EN (RW)
 *
 * Transfer Complete Signal Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_XFER_COMPLETE_SIGNAL_EN_MASK (0x2U)
#define SDXC_INT_SIGNAL_EN_XFER_COMPLETE_SIGNAL_EN_SHIFT (1U)
#define SDXC_INT_SIGNAL_EN_XFER_COMPLETE_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_XFER_COMPLETE_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_XFER_COMPLETE_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_XFER_COMPLETE_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_XFER_COMPLETE_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_XFER_COMPLETE_SIGNAL_EN_SHIFT)

/*
 * CMD_COMPLETE_SIGNAL_EN (RW)
 *
 * Command Complete Signal Enable
 * Values: 
 * 0x0 (FALSE): Masked
 * 0x1 (TRUE): Enabled
 */
#define SDXC_INT_SIGNAL_EN_CMD_COMPLETE_SIGNAL_EN_MASK (0x1U)
#define SDXC_INT_SIGNAL_EN_CMD_COMPLETE_SIGNAL_EN_SHIFT (0U)
#define SDXC_INT_SIGNAL_EN_CMD_COMPLETE_SIGNAL_EN_SET(x) (((uint32_t)(x) << SDXC_INT_SIGNAL_EN_CMD_COMPLETE_SIGNAL_EN_SHIFT) & SDXC_INT_SIGNAL_EN_CMD_COMPLETE_SIGNAL_EN_MASK)
#define SDXC_INT_SIGNAL_EN_CMD_COMPLETE_SIGNAL_EN_GET(x) (((uint32_t)(x) & SDXC_INT_SIGNAL_EN_CMD_COMPLETE_SIGNAL_EN_MASK) >> SDXC_INT_SIGNAL_EN_CMD_COMPLETE_SIGNAL_EN_SHIFT)

/* Bitfield definition for register: AC_HOST_CTRL */
/*
 * PRESET_VAL_ENABLE (RW)
 *
 * Preset Value Enable
 * This bit enables automatic selection of SDCLK frequency and Driver strength Preset Value registers. When Preset Value Enable is set, SDCLK frequency generation (Frequency Select and Clock Generator Select) and the driver strength selection are performed by the controller. These values are selected from set of Preset Value registers based on selected speed mode.
 * Note: For more information, see the FAQ on Preset Register in the DWC_mshc Databook.
 * Values: 
 * 0x0 (FALSE): SDCLK and Driver Strength are controlled by Host Driver
 * 0x1 (TRUE): Automatic Selection by Preset Value are Enabled
 */
#define SDXC_AC_HOST_CTRL_PRESET_VAL_ENABLE_MASK (0x80000000UL)
#define SDXC_AC_HOST_CTRL_PRESET_VAL_ENABLE_SHIFT (31U)
#define SDXC_AC_HOST_CTRL_PRESET_VAL_ENABLE_SET(x) (((uint32_t)(x) << SDXC_AC_HOST_CTRL_PRESET_VAL_ENABLE_SHIFT) & SDXC_AC_HOST_CTRL_PRESET_VAL_ENABLE_MASK)
#define SDXC_AC_HOST_CTRL_PRESET_VAL_ENABLE_GET(x) (((uint32_t)(x) & SDXC_AC_HOST_CTRL_PRESET_VAL_ENABLE_MASK) >> SDXC_AC_HOST_CTRL_PRESET_VAL_ENABLE_SHIFT)

/*
 * ASYNC_INT_ENABLE (RW)
 *
 * Asynchronous Interrupt Enable
 * This bit can be set if a card supports asynchronous interrupts and Asynchronous Interrupt Support is set to 1 in the Capabilities register.
 * Values: 
 * 0x0 (FALSE): Disabled
 * 0x1 (TRUE): Enabled
 */
#define SDXC_AC_HOST_CTRL_ASYNC_INT_ENABLE_MASK (0x40000000UL)
#define SDXC_AC_HOST_CTRL_ASYNC_INT_ENABLE_SHIFT (30U)
#define SDXC_AC_HOST_CTRL_ASYNC_INT_ENABLE_SET(x) (((uint32_t)(x) << SDXC_AC_HOST_CTRL_ASYNC_INT_ENABLE_SHIFT) & SDXC_AC_HOST_CTRL_ASYNC_INT_ENABLE_MASK)
#define SDXC_AC_HOST_CTRL_ASYNC_INT_ENABLE_GET(x) (((uint32_t)(x) & SDXC_AC_HOST_CTRL_ASYNC_INT_ENABLE_MASK) >> SDXC_AC_HOST_CTRL_ASYNC_INT_ENABLE_SHIFT)

/*
 * ADDRESSING (RW)
 *
 * 64-bit Addressing
 * This bit is effective when Host Version 4 Enable is set to 1.
 * Values: 
 * 0x0 (FALSE): 32 bits addressing
 * 0x1 (TRUE): 64 bits addressing
 */
#define SDXC_AC_HOST_CTRL_ADDRESSING_MASK (0x20000000UL)
#define SDXC_AC_HOST_CTRL_ADDRESSING_SHIFT (29U)
#define SDXC_AC_HOST_CTRL_ADDRESSING_SET(x) (((uint32_t)(x) << SDXC_AC_HOST_CTRL_ADDRESSING_SHIFT) & SDXC_AC_HOST_CTRL_ADDRESSING_MASK)
#define SDXC_AC_HOST_CTRL_ADDRESSING_GET(x) (((uint32_t)(x) & SDXC_AC_HOST_CTRL_ADDRESSING_MASK) >> SDXC_AC_HOST_CTRL_ADDRESSING_SHIFT)

/*
 * HOST_VER4_ENABLE (RW)
 *
 * Host Version 4 Enable
 * This bit selects either Version 3.00 compatible mode or Version 4 mode.
 * Functions of following fields are modified for Host Version 4 mode:
 * SDMA Address: SDMA uses ADMA System Address (05Fh-058h) instead of SDMA System Address register (003h-000h)
 * ADMA2/ADMA3 selection: ADMA3 is selected by DMA select in Host Control 1 register
 * 64-bit ADMA Descriptor Size: 128-bit descriptor is used instead of 96-bit descriptor when 64-bit Addressing is set to 1
 * Selection of 32-bit/64-bit System Addressing: Either 32-bit or 64-bit system addressing is selected by 64-bit Addressing bit in this register
 * 32-bit Block Count: SDMA System Address register (003h-000h) is modified to 32-bit Block Count register
 * Note: It is recommended not to program ADMA3 Integrated Descriptor Address registers, UHS-II registers and Command Queuing registers (if applicable) while operating in Host version less than 4 mode (Host Version 4 Enable = 0).
 * Values: 
 * 0x0 (FALSE): Version 3.00 compatible mode
 * 0x1 (TRUE): Version 4 mode
 */
#define SDXC_AC_HOST_CTRL_HOST_VER4_ENABLE_MASK (0x10000000UL)
#define SDXC_AC_HOST_CTRL_HOST_VER4_ENABLE_SHIFT (28U)
#define SDXC_AC_HOST_CTRL_HOST_VER4_ENABLE_SET(x) (((uint32_t)(x) << SDXC_AC_HOST_CTRL_HOST_VER4_ENABLE_SHIFT) & SDXC_AC_HOST_CTRL_HOST_VER4_ENABLE_MASK)
#define SDXC_AC_HOST_CTRL_HOST_VER4_ENABLE_GET(x) (((uint32_t)(x) & SDXC_AC_HOST_CTRL_HOST_VER4_ENABLE_MASK) >> SDXC_AC_HOST_CTRL_HOST_VER4_ENABLE_SHIFT)

/*
 * CMD23_ENABLE (RW)
 *
 * CMD23 Enable
 * If the card supports CMD23, this bit is set to 1. This bit is used to select Auto CMD23 or Auto CMD12 for ADMA3 data transfer.
 * Values: 
 * 0x0 (FALSE): Auto CMD23 is disabled
 * 0x1 (TRUE): Auto CMD23 is enabled
 */
#define SDXC_AC_HOST_CTRL_CMD23_ENABLE_MASK (0x8000000UL)
#define SDXC_AC_HOST_CTRL_CMD23_ENABLE_SHIFT (27U)
#define SDXC_AC_HOST_CTRL_CMD23_ENABLE_SET(x) (((uint32_t)(x) << SDXC_AC_HOST_CTRL_CMD23_ENABLE_SHIFT) & SDXC_AC_HOST_CTRL_CMD23_ENABLE_MASK)
#define SDXC_AC_HOST_CTRL_CMD23_ENABLE_GET(x) (((uint32_t)(x) & SDXC_AC_HOST_CTRL_CMD23_ENABLE_MASK) >> SDXC_AC_HOST_CTRL_CMD23_ENABLE_SHIFT)

/*
 * ADMA2_LEN_MODE (RW)
 *
 * ADMA2 Length Mode
 * This bit selects ADMA2 Length mode to be either 16-bit or 26-bit.
 * Values: 
 * 0x0 (FALSE): 16-bit Data Length Mode
 * 0x1 (TRUE): 26-bit Data Length Mode
 */
#define SDXC_AC_HOST_CTRL_ADMA2_LEN_MODE_MASK (0x4000000UL)
#define SDXC_AC_HOST_CTRL_ADMA2_LEN_MODE_SHIFT (26U)
#define SDXC_AC_HOST_CTRL_ADMA2_LEN_MODE_SET(x) (((uint32_t)(x) << SDXC_AC_HOST_CTRL_ADMA2_LEN_MODE_SHIFT) & SDXC_AC_HOST_CTRL_ADMA2_LEN_MODE_MASK)
#define SDXC_AC_HOST_CTRL_ADMA2_LEN_MODE_GET(x) (((uint32_t)(x) & SDXC_AC_HOST_CTRL_ADMA2_LEN_MODE_MASK) >> SDXC_AC_HOST_CTRL_ADMA2_LEN_MODE_SHIFT)

/*
 * UHS2_IF_ENABLE (RW)
 *
 * UHS-II Interface Enable
 * This bit is used to enable the UHS-II Interface. The value is reflected on the uhs2_if_en pin.
 * Values: 
 * 0x0 (FALSE): SD/eMMC Interface Enabled
 * 0x1 (TRUE): UHS-II Interface Enabled
 */
#define SDXC_AC_HOST_CTRL_UHS2_IF_ENABLE_MASK (0x1000000UL)
#define SDXC_AC_HOST_CTRL_UHS2_IF_ENABLE_SHIFT (24U)
#define SDXC_AC_HOST_CTRL_UHS2_IF_ENABLE_SET(x) (((uint32_t)(x) << SDXC_AC_HOST_CTRL_UHS2_IF_ENABLE_SHIFT) & SDXC_AC_HOST_CTRL_UHS2_IF_ENABLE_MASK)
#define SDXC_AC_HOST_CTRL_UHS2_IF_ENABLE_GET(x) (((uint32_t)(x) & SDXC_AC_HOST_CTRL_UHS2_IF_ENABLE_MASK) >> SDXC_AC_HOST_CTRL_UHS2_IF_ENABLE_SHIFT)

/*
 * SAMPLE_CLK_SEL (RW)
 *
 * Sampling Clock Select 
 * This bit is used by the Host Controller to select the sampling clock in SD/eMMC mode to receive CMD and DAT. This bit is set by the tuning procedure and is valid after the completion of tuning (when Execute Tuning is cleared). Setting this bit to 1 means that tuning is completed successfully and setting this bit to 0 means that tuning has failed. The value is reflected on the sample_cclk_sel pin.This bit is irrelevant in UHS-II mode 
 * Values: 
 * 0x0 (FALSE): Fixed clock is used to sample data
 * 0x1 (TRUE): Tuned clock is used to sample data
 */
#define SDXC_AC_HOST_CTRL_SAMPLE_CLK_SEL_MASK (0x800000UL)
#define SDXC_AC_HOST_CTRL_SAMPLE_CLK_SEL_SHIFT (23U)
#define SDXC_AC_HOST_CTRL_SAMPLE_CLK_SEL_SET(x) (((uint32_t)(x) << SDXC_AC_HOST_CTRL_SAMPLE_CLK_SEL_SHIFT) & SDXC_AC_HOST_CTRL_SAMPLE_CLK_SEL_MASK)
#define SDXC_AC_HOST_CTRL_SAMPLE_CLK_SEL_GET(x) (((uint32_t)(x) & SDXC_AC_HOST_CTRL_SAMPLE_CLK_SEL_MASK) >> SDXC_AC_HOST_CTRL_SAMPLE_CLK_SEL_SHIFT)

/*
 * EXEC_TUNING (RW)
 *
 * Execute Tuning 
 * This bit is set to 1 to start the tuning procedure in UHS-I/eMMC speed modes and this bit is automatically cleared when tuning procedure is completed.This bit is irrelevant in UHS-II mode
 * Values: 
 * 0x0 (FALSE): Not Tuned or Tuning completed
 * 0x1 (TRUE): Execute Tuning
 */
#define SDXC_AC_HOST_CTRL_EXEC_TUNING_MASK (0x400000UL)
#define SDXC_AC_HOST_CTRL_EXEC_TUNING_SHIFT (22U)
#define SDXC_AC_HOST_CTRL_EXEC_TUNING_SET(x) (((uint32_t)(x) << SDXC_AC_HOST_CTRL_EXEC_TUNING_SHIFT) & SDXC_AC_HOST_CTRL_EXEC_TUNING_MASK)
#define SDXC_AC_HOST_CTRL_EXEC_TUNING_GET(x) (((uint32_t)(x) & SDXC_AC_HOST_CTRL_EXEC_TUNING_MASK) >> SDXC_AC_HOST_CTRL_EXEC_TUNING_SHIFT)

/*
 * DRV_STRENGTH_SEL (RW)
 *
 * Driver Strength Select
 * This bit is used to select the Host Controller output driver in 1.8V signaling UHS-I/eMMC speed modes. The bit depends on setting of Preset Value Enable. The value is reflected on the uhs1_drv_sth pin.This bit is irrelevant in UHS-II mode
 * Values: 
 * 0x0 (TYPEB): Driver TYPEB is selected
 * 0x1 (TYPEA): Driver TYPEA is selected
 * 0x2 (TYPEC): Driver TYPEC is selected
 * 0x3 (TYPED): Driver TYPED is selected
 */
#define SDXC_AC_HOST_CTRL_DRV_STRENGTH_SEL_MASK (0x300000UL)
#define SDXC_AC_HOST_CTRL_DRV_STRENGTH_SEL_SHIFT (20U)
#define SDXC_AC_HOST_CTRL_DRV_STRENGTH_SEL_SET(x) (((uint32_t)(x) << SDXC_AC_HOST_CTRL_DRV_STRENGTH_SEL_SHIFT) & SDXC_AC_HOST_CTRL_DRV_STRENGTH_SEL_MASK)
#define SDXC_AC_HOST_CTRL_DRV_STRENGTH_SEL_GET(x) (((uint32_t)(x) & SDXC_AC_HOST_CTRL_DRV_STRENGTH_SEL_MASK) >> SDXC_AC_HOST_CTRL_DRV_STRENGTH_SEL_SHIFT)

/*
 * SIGNALING_EN (RW)
 *
 * 1.8V Signaling Enable 
 * This bit controls voltage regulator for I/O cell in UHS-I/eMMC speed modes. Setting this bit from 0 to 1 starts changing the signal voltage from 3.3V to 1.8V. Host Controller clears this bit if switching to 1.8 signaling fails. The value is reflected on the uhs1_swvolt_en pin.This bit shall be set to 0 in UHS-II mode
 * Note: This bit must be set for all UHS-I speed modes (SDR12/SDR25/SDR50/SDR104/DDR50).
 * Values: 
 * 0x0 (V_3_3): 3.3V Signalling
 * 0x1 (V_1_8): 1.8V Signalling
 */
#define SDXC_AC_HOST_CTRL_SIGNALING_EN_MASK (0x80000UL)
#define SDXC_AC_HOST_CTRL_SIGNALING_EN_SHIFT (19U)
#define SDXC_AC_HOST_CTRL_SIGNALING_EN_SET(x) (((uint32_t)(x) << SDXC_AC_HOST_CTRL_SIGNALING_EN_SHIFT) & SDXC_AC_HOST_CTRL_SIGNALING_EN_MASK)
#define SDXC_AC_HOST_CTRL_SIGNALING_EN_GET(x) (((uint32_t)(x) & SDXC_AC_HOST_CTRL_SIGNALING_EN_MASK) >> SDXC_AC_HOST_CTRL_SIGNALING_EN_SHIFT)

/*
 * UHS_MODE_SEL (RW)
 *
 * UHS Mode/eMMC Speed Mode Select
 * These bits are used to select UHS mode in the SD mode of operation. In eMMC mode, these bits are used to select eMMC Speed mode.
 * UHS Mode (SD/UHS-II mode only):
 * 0x0: SDR12
 * 0x1: SDR25
 * 0x2: SDR50
 * 0x3: SDR104
 * 0x4: DDR50
 * 0x5: Reserved
 * 0x6: Reserved
 * 0x7: UHS-II 
 * eMMC Speed Mode (eMMC mode only):
 * 0x0: Legacy
 * 0x1: High Speed SDR
 * 0x2: Reserved
 * 0x3: HS200
 * 0x4: High Speed DDR
 * 0x5: Reserved
 * 0x6: Reserved
 * 0x7: HS400 
 * Values: 
 * 0x0 (SDR12): SDR12/Legacy
 * 0x1 (SDR25): SDR25/High Speed SDR
 * 0x2 (SDR50): SDR50
 * 0x3 (SDR104): SDR104/HS200
 * 0x4 (DDR50): DDR50/High Speed DDR
 * 0x5 (RSVD5): Reserved
 * 0x6 (RSVD6): Reserved
 * 0x7 (UHS2): UHS-II/HS400
 */
#define SDXC_AC_HOST_CTRL_UHS_MODE_SEL_MASK (0x70000UL)
#define SDXC_AC_HOST_CTRL_UHS_MODE_SEL_SHIFT (16U)
#define SDXC_AC_HOST_CTRL_UHS_MODE_SEL_SET(x) (((uint32_t)(x) << SDXC_AC_HOST_CTRL_UHS_MODE_SEL_SHIFT) & SDXC_AC_HOST_CTRL_UHS_MODE_SEL_MASK)
#define SDXC_AC_HOST_CTRL_UHS_MODE_SEL_GET(x) (((uint32_t)(x) & SDXC_AC_HOST_CTRL_UHS_MODE_SEL_MASK) >> SDXC_AC_HOST_CTRL_UHS_MODE_SEL_SHIFT)

/*
 * CMD_NOT_ISSUED_AUTO_CMD12 (R)
 *
 * Command Not Issued By Auto CMD12 Error 
 * If this bit is set to 1, CMD_wo_DAT is not executed due to an Auto CMD12 Error (D04-D01) in this register.
 * This bit is set to 0 when Auto CMD Error is generated by Auto CMD23.
 * Values: 
 * 0x1 (TRUE): Not Issued
 * 0x0 (FALSE): No Error
 */
#define SDXC_AC_HOST_CTRL_CMD_NOT_ISSUED_AUTO_CMD12_MASK (0x80U)
#define SDXC_AC_HOST_CTRL_CMD_NOT_ISSUED_AUTO_CMD12_SHIFT (7U)
#define SDXC_AC_HOST_CTRL_CMD_NOT_ISSUED_AUTO_CMD12_GET(x) (((uint32_t)(x) & SDXC_AC_HOST_CTRL_CMD_NOT_ISSUED_AUTO_CMD12_MASK) >> SDXC_AC_HOST_CTRL_CMD_NOT_ISSUED_AUTO_CMD12_SHIFT)

/*
 * AUTO_CMD_RESP_ERR (R)
 *
 * Auto CMD Response Error 
 * This bit is set when Response Error Check Enable in the Transfer Mode register is set to 1 and an error is detected in R1 response of either Auto CMD12 or CMD13. This status is ignored if any bit between D00 to D04 is set to 1.
 * Values: 
 * 0x1 (TRUE): Error
 * 0x0 (FALSE): No Error
 */
#define SDXC_AC_HOST_CTRL_AUTO_CMD_RESP_ERR_MASK (0x20U)
#define SDXC_AC_HOST_CTRL_AUTO_CMD_RESP_ERR_SHIFT (5U)
#define SDXC_AC_HOST_CTRL_AUTO_CMD_RESP_ERR_GET(x) (((uint32_t)(x) & SDXC_AC_HOST_CTRL_AUTO_CMD_RESP_ERR_MASK) >> SDXC_AC_HOST_CTRL_AUTO_CMD_RESP_ERR_SHIFT)

/*
 * AUTO_CMD_IDX_ERR (R)
 *
 * Auto CMD Index Error 
 * This bit is set if the command index error occurs in response to a command.
 * Values: 
 * 0x1 (TRUE): Error
 * 0x0 (FALSE): No Error
 */
#define SDXC_AC_HOST_CTRL_AUTO_CMD_IDX_ERR_MASK (0x10U)
#define SDXC_AC_HOST_CTRL_AUTO_CMD_IDX_ERR_SHIFT (4U)
#define SDXC_AC_HOST_CTRL_AUTO_CMD_IDX_ERR_GET(x) (((uint32_t)(x) & SDXC_AC_HOST_CTRL_AUTO_CMD_IDX_ERR_MASK) >> SDXC_AC_HOST_CTRL_AUTO_CMD_IDX_ERR_SHIFT)

/*
 * AUTO_CMD_EBIT_ERR (R)
 *
 * Auto CMD End Bit Error 
 * This bit is set when detecting that the end bit of command response is 0.
 * Values: 
 * 0x1 (TRUE): End Bit Error Generated
 * 0x0 (FALSE): No Error
 */
#define SDXC_AC_HOST_CTRL_AUTO_CMD_EBIT_ERR_MASK (0x8U)
#define SDXC_AC_HOST_CTRL_AUTO_CMD_EBIT_ERR_SHIFT (3U)
#define SDXC_AC_HOST_CTRL_AUTO_CMD_EBIT_ERR_GET(x) (((uint32_t)(x) & SDXC_AC_HOST_CTRL_AUTO_CMD_EBIT_ERR_MASK) >> SDXC_AC_HOST_CTRL_AUTO_CMD_EBIT_ERR_SHIFT)

/*
 * AUTO_CMD_CRC_ERR (R)
 *
 * Auto CMD CRC Error 
 * This bit is set when detecting a CRC error in the command response.
 * Values: 
 * 0x1 (TRUE): CRC Error Generated
 * 0x0 (FALSE): No Error
 */
#define SDXC_AC_HOST_CTRL_AUTO_CMD_CRC_ERR_MASK (0x4U)
#define SDXC_AC_HOST_CTRL_AUTO_CMD_CRC_ERR_SHIFT (2U)
#define SDXC_AC_HOST_CTRL_AUTO_CMD_CRC_ERR_GET(x) (((uint32_t)(x) & SDXC_AC_HOST_CTRL_AUTO_CMD_CRC_ERR_MASK) >> SDXC_AC_HOST_CTRL_AUTO_CMD_CRC_ERR_SHIFT)

/*
 * AUTO_CMD_TOUT_ERR (R)
 *
 * Auto CMD Timeout Error 
 * This bit is set if no response is returned with 64 SDCLK cycles from the end bit of the command.
 * If this bit is set to 1, error status bits (D04-D01) are meaningless.
 * Values: 
 * 0x1 (TRUE): Time out
 * 0x0 (FALSE): No Error
 */
#define SDXC_AC_HOST_CTRL_AUTO_CMD_TOUT_ERR_MASK (0x2U)
#define SDXC_AC_HOST_CTRL_AUTO_CMD_TOUT_ERR_SHIFT (1U)
#define SDXC_AC_HOST_CTRL_AUTO_CMD_TOUT_ERR_GET(x) (((uint32_t)(x) & SDXC_AC_HOST_CTRL_AUTO_CMD_TOUT_ERR_MASK) >> SDXC_AC_HOST_CTRL_AUTO_CMD_TOUT_ERR_SHIFT)

/*
 * AUTO_CMD12_NOT_EXEC (R)
 *
 * Auto CMD12 Not Executed 
 * If multiple memory block data transfer is not started due to a command error, this bit is not set because it is not necessary to issue an Auto CMD12. Setting this bit to 1 means that the Host Controller cannot issue Auto CMD12 to stop multiple memory block data transfer, due to some error. If this bit is set to 1, error status bits (D04-D01) is meaningless.
 * This bit is set to 0 when Auto CMD Error is generated by Auto CMD23.
 * Values: 
 * 0x1 (TRUE): Not Executed
 * 0x0 (FALSE): Executed
 */
#define SDXC_AC_HOST_CTRL_AUTO_CMD12_NOT_EXEC_MASK (0x1U)
#define SDXC_AC_HOST_CTRL_AUTO_CMD12_NOT_EXEC_SHIFT (0U)
#define SDXC_AC_HOST_CTRL_AUTO_CMD12_NOT_EXEC_GET(x) (((uint32_t)(x) & SDXC_AC_HOST_CTRL_AUTO_CMD12_NOT_EXEC_MASK) >> SDXC_AC_HOST_CTRL_AUTO_CMD12_NOT_EXEC_SHIFT)

/* Bitfield definition for register: CAPABILITIES1 */
/*
 * SLOT_TYPE_R (R)
 *
 * Slot Type 
 * These bits indicate usage of a slot by a specific Host System.
 * Values: 
 * 0x0 (REMOVABLE_SLOT): Removable Card Slot
 * 0x1 (EMBEDDED_SLOT): Embedded Slot for one Device
 * 0x2 (SHARED_SLOT): Shared Bus Slot (SD mode)
 * 0x3 (UHS2_EMBEDDED_SLOT): UHS-II Multiple Embedded Devices
 */
#define SDXC_CAPABILITIES1_SLOT_TYPE_R_MASK (0xC0000000UL)
#define SDXC_CAPABILITIES1_SLOT_TYPE_R_SHIFT (30U)
#define SDXC_CAPABILITIES1_SLOT_TYPE_R_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES1_SLOT_TYPE_R_MASK) >> SDXC_CAPABILITIES1_SLOT_TYPE_R_SHIFT)

/*
 * ASYNC_INT_SUPPORT (R)
 *
 * Asynchronous Interrupt Support (SD Mode only)
 * Values: 
 * 0x0 (FALSE): Asynchronous Interrupt Not Supported
 * 0x1 (TRUE): Asynchronous Interrupt Supported
 */
#define SDXC_CAPABILITIES1_ASYNC_INT_SUPPORT_MASK (0x20000000UL)
#define SDXC_CAPABILITIES1_ASYNC_INT_SUPPORT_SHIFT (29U)
#define SDXC_CAPABILITIES1_ASYNC_INT_SUPPORT_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES1_ASYNC_INT_SUPPORT_MASK) >> SDXC_CAPABILITIES1_ASYNC_INT_SUPPORT_SHIFT)

/*
 * SYS_ADDR_64_V3 (R)
 *
 * 64-bit System Address Support for V3
 * This bit sets the Host controller to support 64-bit System Addressing of V3 mode. 
 * SDMA cannot be used in 64-bit Addressing in Version 3 Mode. 
 * If this bit is set to 1, 64-bit ADMA2 with using 96-bit Descriptor can be enabled by setting Host Version 4 Enable (HOST_VER4_ENABLE = 0) and DMA select (DMA_SEL = 11b).
 * Values: 
 * 0x0 (FALSE): 64-bit System Address for V3 is Not Supported
 * 0x1 (TRUE): 64-bit System Address for V3 is Supported
 */
#define SDXC_CAPABILITIES1_SYS_ADDR_64_V3_MASK (0x10000000UL)
#define SDXC_CAPABILITIES1_SYS_ADDR_64_V3_SHIFT (28U)
#define SDXC_CAPABILITIES1_SYS_ADDR_64_V3_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES1_SYS_ADDR_64_V3_MASK) >> SDXC_CAPABILITIES1_SYS_ADDR_64_V3_SHIFT)

/*
 * SYS_ADDR_64_V4 (R)
 *
 * 64-bit System Address Support for V4
 * This bit sets the Host Controller to support 64-bit System Addressing of V4 mode. When this bit is set to 1, full or part of 64-bit address must be used to decode the Host Controller Registers so that Host Controller Registers can be placed above system memory area. 64-bit address decode of Host Controller registers is effective regardless of setting to 64-bit Addressing in Host Control 2.
 * If this bit is set to 1, 64-bit DMA Addressing for version 4 is enabled by setting Host Version 4 Enable (HOST_VER4_ENABLE = 1) and by setting 64-bit Addressing (ADDRESSING =1) in the Host Control 2 register. SDMA can be used and ADMA2 uses 128-bit Descriptor.
 * Values: 
 * 0x0 (FALSE): 64-bit System Address for V4 is Not Supported
 * 0x1 (TRUE): 64-bit System Address for V4 is Supported
 */
#define SDXC_CAPABILITIES1_SYS_ADDR_64_V4_MASK (0x8000000UL)
#define SDXC_CAPABILITIES1_SYS_ADDR_64_V4_SHIFT (27U)
#define SDXC_CAPABILITIES1_SYS_ADDR_64_V4_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES1_SYS_ADDR_64_V4_MASK) >> SDXC_CAPABILITIES1_SYS_ADDR_64_V4_SHIFT)

/*
 * VOLT_18 (R)
 *
 * Voltage Support for 1.8V
 * Values: 
 * 0x0 (FALSE): 1.8V Not Supported
 * 0x1 (TRUE): 1.8V Supported
 */
#define SDXC_CAPABILITIES1_VOLT_18_MASK (0x4000000UL)
#define SDXC_CAPABILITIES1_VOLT_18_SHIFT (26U)
#define SDXC_CAPABILITIES1_VOLT_18_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES1_VOLT_18_MASK) >> SDXC_CAPABILITIES1_VOLT_18_SHIFT)

/*
 * VOLT_30 (R)
 *
 * Voltage Support for SD 3.0V or Embedded 1.2V
 * Values: 
 * 0x0 (FALSE): SD 3.0V or Embedded 1.2V Not Supported
 * 0x1 (TRUE): SD 3.0V or Embedded Supported
 */
#define SDXC_CAPABILITIES1_VOLT_30_MASK (0x2000000UL)
#define SDXC_CAPABILITIES1_VOLT_30_SHIFT (25U)
#define SDXC_CAPABILITIES1_VOLT_30_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES1_VOLT_30_MASK) >> SDXC_CAPABILITIES1_VOLT_30_SHIFT)

/*
 * VOLT_33 (R)
 *
 * Voltage Support for 3.3V
 * Values: 
 * 0x0 (FALSE): 3.3V Not Supported
 * 0x1 (TRUE): 3.3V Supported
 */
#define SDXC_CAPABILITIES1_VOLT_33_MASK (0x1000000UL)
#define SDXC_CAPABILITIES1_VOLT_33_SHIFT (24U)
#define SDXC_CAPABILITIES1_VOLT_33_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES1_VOLT_33_MASK) >> SDXC_CAPABILITIES1_VOLT_33_SHIFT)

/*
 * SUS_RES_SUPPORT (R)
 *
 * Suspense/Resume Support
 * This bit indicates whether the Host Controller supports Suspend/Resume functionality. If this bit is 0, the Host Driver does not issue either Suspend or Resume commands because the Suspend and Resume mechanism is not supported.
 * Values: 
 * 0x0 (FALSE): Not Supported
 * 0x1 (TRUE): Supported
 */
#define SDXC_CAPABILITIES1_SUS_RES_SUPPORT_MASK (0x800000UL)
#define SDXC_CAPABILITIES1_SUS_RES_SUPPORT_SHIFT (23U)
#define SDXC_CAPABILITIES1_SUS_RES_SUPPORT_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES1_SUS_RES_SUPPORT_MASK) >> SDXC_CAPABILITIES1_SUS_RES_SUPPORT_SHIFT)

/*
 * SDMA_SUPPORT (R)
 *
 * SDMA Support
 * This bit indicates whether the Host Controller is capable of using SDMA to transfer data between the system memory and the Host Controller directly.
 * Values: 
 * 0x0 (FALSE): SDMA not Supported
 * 0x1 (TRUE): SDMA Supported
 */
#define SDXC_CAPABILITIES1_SDMA_SUPPORT_MASK (0x400000UL)
#define SDXC_CAPABILITIES1_SDMA_SUPPORT_SHIFT (22U)
#define SDXC_CAPABILITIES1_SDMA_SUPPORT_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES1_SDMA_SUPPORT_MASK) >> SDXC_CAPABILITIES1_SDMA_SUPPORT_SHIFT)

/*
 * HIGH_SPEED_SUPPORT (R)
 *
 * High Speed Support 
 * This bit indicates whether the Host Controller and the Host System supports High Speed mode and they can supply the SD Clock frequency from 25 MHz to 50 MHz.
 * Values: 
 * 0x0 (FALSE): High Speed not Supported
 * 0x1 (TRUE): High Speed Supported
 */
#define SDXC_CAPABILITIES1_HIGH_SPEED_SUPPORT_MASK (0x200000UL)
#define SDXC_CAPABILITIES1_HIGH_SPEED_SUPPORT_SHIFT (21U)
#define SDXC_CAPABILITIES1_HIGH_SPEED_SUPPORT_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES1_HIGH_SPEED_SUPPORT_MASK) >> SDXC_CAPABILITIES1_HIGH_SPEED_SUPPORT_SHIFT)

/*
 * ADMA2_SUPPORT (R)
 *
 * ADMA2 Support
 * This bit indicates whether the Host Controller is capable of using ADMA2.
 * Values: 
 * 0x0 (FALSE): ADMA2 not Supported
 * 0x1 (TRUE): ADMA2 Supported
 */
#define SDXC_CAPABILITIES1_ADMA2_SUPPORT_MASK (0x80000UL)
#define SDXC_CAPABILITIES1_ADMA2_SUPPORT_SHIFT (19U)
#define SDXC_CAPABILITIES1_ADMA2_SUPPORT_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES1_ADMA2_SUPPORT_MASK) >> SDXC_CAPABILITIES1_ADMA2_SUPPORT_SHIFT)

/*
 * EMBEDDED_8_BIT (R)
 *
 * 8-bit Support for Embedded Device
 * This bit indicates whether the Host Controller is capable of using an 8-bit bus width mode. This bit is not effective when the Slot Type is set to 10b.
 * Values: 
 * 0x0 (FALSE): 8-bit Bus Width not Supported
 * 0x1 (TRUE): 8-bit Bus Width Supported
 */
#define SDXC_CAPABILITIES1_EMBEDDED_8_BIT_MASK (0x40000UL)
#define SDXC_CAPABILITIES1_EMBEDDED_8_BIT_SHIFT (18U)
#define SDXC_CAPABILITIES1_EMBEDDED_8_BIT_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES1_EMBEDDED_8_BIT_MASK) >> SDXC_CAPABILITIES1_EMBEDDED_8_BIT_SHIFT)

/*
 * MAX_BLK_LEN (R)
 *
 * Maximum Block Length 
 * This bit indicates the maximum block size that the Host driver can read and write to the buffer in the Host Controller. The buffer transfers this block size without wait cycles. The transfer block length is always 512 bytes for the SD Memory irrespective of this bit
 * Values: 
 * 0x0 (ZERO): 512 Byte
 * 0x1 (ONE): 1024 Byte
 * 0x2 (TWO): 2048 Byte
 * 0x3 (THREE): Reserved
 */
#define SDXC_CAPABILITIES1_MAX_BLK_LEN_MASK (0x30000UL)
#define SDXC_CAPABILITIES1_MAX_BLK_LEN_SHIFT (16U)
#define SDXC_CAPABILITIES1_MAX_BLK_LEN_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES1_MAX_BLK_LEN_MASK) >> SDXC_CAPABILITIES1_MAX_BLK_LEN_SHIFT)

/*
 * BASE_CLK_FREQ (R)
 *
 * Base Clock Frequency for SD clock 
 * These bits indicate the base (maximum) clock frequency for the SD Clock. The definition of these bits depend on the Host Controller Version.
 * 6-Bit Base Clock Frequency: This mode is supported by the Host Controller version 1.00 and 2.00. The upper 2 bits are not effective and are always 0. The unit values are 1 MHz. The supported clock range is 10 MHz to 63 MHz.
 * -0x00 : Get information through another method 
 * -0x01 : 1 MHz
 * -0x02 : 2 MHz
 * -.............
 * -0x3F : 63 MHz
 * -0x40-0xFF : Not Supported 
 * 8-Bit Base Clock Frequency: This mode is supported by the Host Controller version 3.00. The unit values are 1 MHz. The supported clock range is 10 MHz to 255 MHz.
 * -0x00 : Get information through another method 
 * -0x01 : 1 MHz
 * -0x02 : 2 MHz
 * -............
 * -0xFF : 255 MHz
 * If the frequency is 16.5 MHz, the larger value is set to 0001001b (17 MHz) because the Host Driver uses this value to calculate the clock divider value and it does not exceed the upper limit of the SD Clock frequency. If these bits are all 0, the Host system has to get information using a different method.
 */
#define SDXC_CAPABILITIES1_BASE_CLK_FREQ_MASK (0xFF00U)
#define SDXC_CAPABILITIES1_BASE_CLK_FREQ_SHIFT (8U)
#define SDXC_CAPABILITIES1_BASE_CLK_FREQ_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES1_BASE_CLK_FREQ_MASK) >> SDXC_CAPABILITIES1_BASE_CLK_FREQ_SHIFT)

/*
 * TOUT_CLK_UNIT (R)
 *
 * Timeout Clock Unit 
 * This bit shows the unit of base clock frequency used to detect Data TImeout Error.
 * Values: 
 * 0x0 (KHZ): KHz
 * 0x1 (MHZ): MHz
 */
#define SDXC_CAPABILITIES1_TOUT_CLK_UNIT_MASK (0x80U)
#define SDXC_CAPABILITIES1_TOUT_CLK_UNIT_SHIFT (7U)
#define SDXC_CAPABILITIES1_TOUT_CLK_UNIT_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES1_TOUT_CLK_UNIT_MASK) >> SDXC_CAPABILITIES1_TOUT_CLK_UNIT_SHIFT)

/*
 * TOUT_CLK_FREQ (R)
 *
 * Timeout Clock Frequency 
 * This bit shows the base clock frequency used to detect Data Timeout Error. The Timeout Clock unit defines the unit of timeout clock frequency. It can be KHz or MHz.
 * 0x00 : Get information through another method
 * 0x01 : 1KHz / 1MHz
 * 0x02 : 2KHz / 2MHz
 * 0x03 : 3KHz / 3MHz
 *  ...........
 * 0x3F : 63KHz / 63MHz
 */
#define SDXC_CAPABILITIES1_TOUT_CLK_FREQ_MASK (0x3FU)
#define SDXC_CAPABILITIES1_TOUT_CLK_FREQ_SHIFT (0U)
#define SDXC_CAPABILITIES1_TOUT_CLK_FREQ_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES1_TOUT_CLK_FREQ_MASK) >> SDXC_CAPABILITIES1_TOUT_CLK_FREQ_SHIFT)

/* Bitfield definition for register: CAPABILITIES2 */
/*
 * VDD2_18V_SUPPORT (R)
 *
 * 1.8V VDD2 Support
 * This bit indicates support of VDD2 for the Host System.
 * Values: 
 * 0x0 (FALSE): 1.8V VDD2 is not Supported
 * 0x1 (TRUE): 1.8V VDD2 is Supported
 */
#define SDXC_CAPABILITIES2_VDD2_18V_SUPPORT_MASK (0x10000000UL)
#define SDXC_CAPABILITIES2_VDD2_18V_SUPPORT_SHIFT (28U)
#define SDXC_CAPABILITIES2_VDD2_18V_SUPPORT_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES2_VDD2_18V_SUPPORT_MASK) >> SDXC_CAPABILITIES2_VDD2_18V_SUPPORT_SHIFT)

/*
 * ADMA3_SUPPORT (R)
 *
 * ADMA3 Support 
 * This bit indicates whether the Host Controller is capable of using ADMA3.
 * Values: 
 * 0x0 (FALSE): ADMA3 not Supported
 * 0x1 (TRUE): ADMA3 Supported
 */
#define SDXC_CAPABILITIES2_ADMA3_SUPPORT_MASK (0x8000000UL)
#define SDXC_CAPABILITIES2_ADMA3_SUPPORT_SHIFT (27U)
#define SDXC_CAPABILITIES2_ADMA3_SUPPORT_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES2_ADMA3_SUPPORT_MASK) >> SDXC_CAPABILITIES2_ADMA3_SUPPORT_SHIFT)

/*
 * CLK_MUL (R)
 *
 * Clock Multiplier
 * These bits indicate the clock multiplier of the programmable clock generator. Setting these bits to 0 means that the Host Controller does not support a programmable clock generator.
 * 0x0: Clock Multiplier is not Supported
 * 0x1: Clock Multiplier M = 2
 * 0x2: Clock Multiplier M = 3
 *  .........
 * 0xFF: Clock Multiplier M = 256
 */
#define SDXC_CAPABILITIES2_CLK_MUL_MASK (0xFF0000UL)
#define SDXC_CAPABILITIES2_CLK_MUL_SHIFT (16U)
#define SDXC_CAPABILITIES2_CLK_MUL_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES2_CLK_MUL_MASK) >> SDXC_CAPABILITIES2_CLK_MUL_SHIFT)

/*
 * RE_TUNING_MODES (R)
 *
 * Re-Tuning Modes (UHS-I only)
 * These bits select the re-tuning method and limit the maximum data length.
 * Values: 
 * 0x0 (MODE1): Timer
 * 0x1 (MODE2): Timer and Re-Tuning Request (Not supported)
 * 0x2 (MODE3): Auto Re-Tuning (for transfer)
 * 0x3 (RSVD_MODE): Reserved
 */
#define SDXC_CAPABILITIES2_RE_TUNING_MODES_MASK (0xC000U)
#define SDXC_CAPABILITIES2_RE_TUNING_MODES_SHIFT (14U)
#define SDXC_CAPABILITIES2_RE_TUNING_MODES_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES2_RE_TUNING_MODES_MASK) >> SDXC_CAPABILITIES2_RE_TUNING_MODES_SHIFT)

/*
 * USE_TUNING_SDR50 (R)
 *
 * Use Tuning for SDR50 (UHS-I only)
 * Values: 
 * 0x0 (ZERO): SDR50 does not require tuning
 * 0x1 (ONE): SDR50 requires tuning
 */
#define SDXC_CAPABILITIES2_USE_TUNING_SDR50_MASK (0x2000U)
#define SDXC_CAPABILITIES2_USE_TUNING_SDR50_SHIFT (13U)
#define SDXC_CAPABILITIES2_USE_TUNING_SDR50_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES2_USE_TUNING_SDR50_MASK) >> SDXC_CAPABILITIES2_USE_TUNING_SDR50_SHIFT)

/*
 * RETUNE_CNT (R)
 *
 * Timer Count for Re-Tuning (UHS-I only)
 * 0x0: Re-Tuning Timer disabled
 * 0x1: 1 seconds
 * 0x2: 2 seconds
 * 0x3: 4 seconds
 *  ........
 * 0xB: 1024 seconds
 * 0xC: Reserved
 * 0xD: Reserved
 * 0xE: Reserved
 * 0xF: Get information from other source
 */
#define SDXC_CAPABILITIES2_RETUNE_CNT_MASK (0xF00U)
#define SDXC_CAPABILITIES2_RETUNE_CNT_SHIFT (8U)
#define SDXC_CAPABILITIES2_RETUNE_CNT_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES2_RETUNE_CNT_MASK) >> SDXC_CAPABILITIES2_RETUNE_CNT_SHIFT)

/*
 * DRV_TYPED (R)
 *
 * Driver Type D Support (UHS-I only) 
 * This bit indicates support of Driver Type D for 1.8 Signaling.
 * Values: 
 * 0x0 (FALSE): Driver Type D is not supported
 * 0x1 (TRUE): Driver Type D is supported
 */
#define SDXC_CAPABILITIES2_DRV_TYPED_MASK (0x40U)
#define SDXC_CAPABILITIES2_DRV_TYPED_SHIFT (6U)
#define SDXC_CAPABILITIES2_DRV_TYPED_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES2_DRV_TYPED_MASK) >> SDXC_CAPABILITIES2_DRV_TYPED_SHIFT)

/*
 * DRV_TYPEC (R)
 *
 * Driver Type C Support (UHS-I only)
 * This bit indicates support of Driver Type C for 1.8 Signaling.
 * Values: 
 * 0x0 (FALSE): Driver Type C is not supported
 * 0x1 (TRUE): Driver Type C is supported
 */
#define SDXC_CAPABILITIES2_DRV_TYPEC_MASK (0x20U)
#define SDXC_CAPABILITIES2_DRV_TYPEC_SHIFT (5U)
#define SDXC_CAPABILITIES2_DRV_TYPEC_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES2_DRV_TYPEC_MASK) >> SDXC_CAPABILITIES2_DRV_TYPEC_SHIFT)

/*
 * DRV_TYPEA (R)
 *
 * Driver Type A Support (UHS-I only)
 * This bit indicates support of Driver Type A for 1.8 Signaling.
 * Values: 
 * 0x0 (FALSE): Driver Type A is not supported
 * 0x1 (TRUE): Driver Type A is supported
 */
#define SDXC_CAPABILITIES2_DRV_TYPEA_MASK (0x10U)
#define SDXC_CAPABILITIES2_DRV_TYPEA_SHIFT (4U)
#define SDXC_CAPABILITIES2_DRV_TYPEA_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES2_DRV_TYPEA_MASK) >> SDXC_CAPABILITIES2_DRV_TYPEA_SHIFT)

/*
 * UHS2_SUPPORT (R)
 *
 * UHS-II Support (UHS-II only)
 * This bit indicates whether Host Controller supports UHS-II.
 * Values: 
 * 0x0 (FALSE): UHS-II is not supported
 * 0x1 (TRUE): UHS-II is supported
 */
#define SDXC_CAPABILITIES2_UHS2_SUPPORT_MASK (0x8U)
#define SDXC_CAPABILITIES2_UHS2_SUPPORT_SHIFT (3U)
#define SDXC_CAPABILITIES2_UHS2_SUPPORT_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES2_UHS2_SUPPORT_MASK) >> SDXC_CAPABILITIES2_UHS2_SUPPORT_SHIFT)

/*
 * DDR50_SUPPORT (R)
 *
 * DDR50 Support (UHS-I only)
 * Values: 
 * 0x0 (FALSE): DDR50 is not supported
 * 0x1 (TRUE): DDR50 is supported
 */
#define SDXC_CAPABILITIES2_DDR50_SUPPORT_MASK (0x4U)
#define SDXC_CAPABILITIES2_DDR50_SUPPORT_SHIFT (2U)
#define SDXC_CAPABILITIES2_DDR50_SUPPORT_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES2_DDR50_SUPPORT_MASK) >> SDXC_CAPABILITIES2_DDR50_SUPPORT_SHIFT)

/*
 * SDR104_SUPPORT (R)
 *
 * SDR104 Support (UHS-I only)
 * This bit mentions that SDR104 requires tuning.
 * Values: 
 * 0x0 (FALSE): SDR104 is not supported
 * 0x1 (TRUE): SDR104 is supported
 */
#define SDXC_CAPABILITIES2_SDR104_SUPPORT_MASK (0x2U)
#define SDXC_CAPABILITIES2_SDR104_SUPPORT_SHIFT (1U)
#define SDXC_CAPABILITIES2_SDR104_SUPPORT_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES2_SDR104_SUPPORT_MASK) >> SDXC_CAPABILITIES2_SDR104_SUPPORT_SHIFT)

/*
 * SDR50_SUPPORT (R)
 *
 * SDR50 Support (UHS-I only)
 * Thsi bit indicates that SDR50 is supported. The bit 13 (USE_TUNING_SDR50) indicates whether SDR50 requires tuning or not.
 * Values: 
 * 0x0 (FALSE): SDR50 is not supported
 * 0x1 (TRUE): SDR50 is supported
 */
#define SDXC_CAPABILITIES2_SDR50_SUPPORT_MASK (0x1U)
#define SDXC_CAPABILITIES2_SDR50_SUPPORT_SHIFT (0U)
#define SDXC_CAPABILITIES2_SDR50_SUPPORT_GET(x) (((uint32_t)(x) & SDXC_CAPABILITIES2_SDR50_SUPPORT_MASK) >> SDXC_CAPABILITIES2_SDR50_SUPPORT_SHIFT)

/* Bitfield definition for register: CURR_CAPABILITIES1 */
/*
 * MAX_CUR_18V (R)
 *
 * Maximum Current for 1.8V
 * This bit specifies the Maximum Current for 1.8V VDD1 power supply for the card.
 * 0: Get information through another method
 * 1: 4mA
 * 2: 8mA
 * 3: 13mA
 * .......
 * 255: 1020mA
 */
#define SDXC_CURR_CAPABILITIES1_MAX_CUR_18V_MASK (0xFF0000UL)
#define SDXC_CURR_CAPABILITIES1_MAX_CUR_18V_SHIFT (16U)
#define SDXC_CURR_CAPABILITIES1_MAX_CUR_18V_GET(x) (((uint32_t)(x) & SDXC_CURR_CAPABILITIES1_MAX_CUR_18V_MASK) >> SDXC_CURR_CAPABILITIES1_MAX_CUR_18V_SHIFT)

/*
 * MAX_CUR_30V (R)
 *
 * Maximum Current for 3.0V
 * This bit specifies the Maximum Current for 3.0V VDD1 power supply for the card.
 * 0: Get information through another method
 * 1: 4mA
 * 2: 8mA
 * 3: 13mA
 * .......
 * 255: 1020mA
 */
#define SDXC_CURR_CAPABILITIES1_MAX_CUR_30V_MASK (0xFF00U)
#define SDXC_CURR_CAPABILITIES1_MAX_CUR_30V_SHIFT (8U)
#define SDXC_CURR_CAPABILITIES1_MAX_CUR_30V_GET(x) (((uint32_t)(x) & SDXC_CURR_CAPABILITIES1_MAX_CUR_30V_MASK) >> SDXC_CURR_CAPABILITIES1_MAX_CUR_30V_SHIFT)

/*
 * MAX_CUR_33V (R)
 *
 * Maximum Current for 3.3V
 * This bit specifies the Maximum Current for 3.3V VDD1 power supply for the card.
 * 0: Get information through another method
 * 1: 4mA
 * 2: 8mA
 * 3: 13mA
 * .......
 * 255: 1020mA
 */
#define SDXC_CURR_CAPABILITIES1_MAX_CUR_33V_MASK (0xFFU)
#define SDXC_CURR_CAPABILITIES1_MAX_CUR_33V_SHIFT (0U)
#define SDXC_CURR_CAPABILITIES1_MAX_CUR_33V_GET(x) (((uint32_t)(x) & SDXC_CURR_CAPABILITIES1_MAX_CUR_33V_MASK) >> SDXC_CURR_CAPABILITIES1_MAX_CUR_33V_SHIFT)

/* Bitfield definition for register: CURR_CAPABILITIES2 */
/*
 * MAX_CUR_VDD2_18V (R)
 *
 * Maximum Current for 1.8V VDD2
 * This bit specifies the Maximum Current for 1.8V VDD2 power supply for the UHS-II card.
 * 0: Get information through another method
 * 1: 4mA
 * 2: 8mA
 * 3: 13mA
 * .......
 * 255: 1020mA
 */
#define SDXC_CURR_CAPABILITIES2_MAX_CUR_VDD2_18V_MASK (0xFFU)
#define SDXC_CURR_CAPABILITIES2_MAX_CUR_VDD2_18V_SHIFT (0U)
#define SDXC_CURR_CAPABILITIES2_MAX_CUR_VDD2_18V_GET(x) (((uint32_t)(x) & SDXC_CURR_CAPABILITIES2_MAX_CUR_VDD2_18V_MASK) >> SDXC_CURR_CAPABILITIES2_MAX_CUR_VDD2_18V_SHIFT)

/* Bitfield definition for register: FORCE_EVENT */
/*
 * FORCE_VENDOR_ERR3 (W)
 *
 * This bit (FORCE_VENDOR_ERR3) of the FORCE_ERROR_INT_STAT_R register is reserved. It always returns 0.
 */
#define SDXC_FORCE_EVENT_FORCE_VENDOR_ERR3_MASK (0x80000000UL)
#define SDXC_FORCE_EVENT_FORCE_VENDOR_ERR3_SHIFT (31U)
#define SDXC_FORCE_EVENT_FORCE_VENDOR_ERR3_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_VENDOR_ERR3_SHIFT) & SDXC_FORCE_EVENT_FORCE_VENDOR_ERR3_MASK)
#define SDXC_FORCE_EVENT_FORCE_VENDOR_ERR3_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_VENDOR_ERR3_MASK) >> SDXC_FORCE_EVENT_FORCE_VENDOR_ERR3_SHIFT)

/*
 * FORCE_VENDOR_ERR2 (W)
 *
 * This bit (FORCE_VENDOR_ERR2) of the FORCE_ERROR_INT_STAT_R register is reserved. It always returns 0.
 */
#define SDXC_FORCE_EVENT_FORCE_VENDOR_ERR2_MASK (0x40000000UL)
#define SDXC_FORCE_EVENT_FORCE_VENDOR_ERR2_SHIFT (30U)
#define SDXC_FORCE_EVENT_FORCE_VENDOR_ERR2_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_VENDOR_ERR2_SHIFT) & SDXC_FORCE_EVENT_FORCE_VENDOR_ERR2_MASK)
#define SDXC_FORCE_EVENT_FORCE_VENDOR_ERR2_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_VENDOR_ERR2_MASK) >> SDXC_FORCE_EVENT_FORCE_VENDOR_ERR2_SHIFT)

/*
 * FORCE_VENDOR_ERR1 (W)
 *
 * This bit (FORCE_VENDOR_ERR1) of the FORCE_ERROR_INT_STAT_R register is reserved. It always returns 0.
 */
#define SDXC_FORCE_EVENT_FORCE_VENDOR_ERR1_MASK (0x20000000UL)
#define SDXC_FORCE_EVENT_FORCE_VENDOR_ERR1_SHIFT (29U)
#define SDXC_FORCE_EVENT_FORCE_VENDOR_ERR1_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_VENDOR_ERR1_SHIFT) & SDXC_FORCE_EVENT_FORCE_VENDOR_ERR1_MASK)
#define SDXC_FORCE_EVENT_FORCE_VENDOR_ERR1_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_VENDOR_ERR1_MASK) >> SDXC_FORCE_EVENT_FORCE_VENDOR_ERR1_SHIFT)

/*
 * FORCE_BOOT_ACK_ERR (W)
 *
 * Force Event for Boot Ack error 
 * Values: 
 * 0x0 (FALSE): Not Affected
 * 0x1 (TRUE): Boot ack Error Status is set
 */
#define SDXC_FORCE_EVENT_FORCE_BOOT_ACK_ERR_MASK (0x10000000UL)
#define SDXC_FORCE_EVENT_FORCE_BOOT_ACK_ERR_SHIFT (28U)
#define SDXC_FORCE_EVENT_FORCE_BOOT_ACK_ERR_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_BOOT_ACK_ERR_SHIFT) & SDXC_FORCE_EVENT_FORCE_BOOT_ACK_ERR_MASK)
#define SDXC_FORCE_EVENT_FORCE_BOOT_ACK_ERR_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_BOOT_ACK_ERR_MASK) >> SDXC_FORCE_EVENT_FORCE_BOOT_ACK_ERR_SHIFT)

/*
 * FORCE_RESP_ERR (W)
 *
 * Force Event for Response Error (SD Mode only) 
 * Values: 
 * 0x0 (FALSE): Not Affected
 * 0x1 (TRUE): Response Error Status is set
 */
#define SDXC_FORCE_EVENT_FORCE_RESP_ERR_MASK (0x8000000UL)
#define SDXC_FORCE_EVENT_FORCE_RESP_ERR_SHIFT (27U)
#define SDXC_FORCE_EVENT_FORCE_RESP_ERR_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_RESP_ERR_SHIFT) & SDXC_FORCE_EVENT_FORCE_RESP_ERR_MASK)
#define SDXC_FORCE_EVENT_FORCE_RESP_ERR_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_RESP_ERR_MASK) >> SDXC_FORCE_EVENT_FORCE_RESP_ERR_SHIFT)

/*
 * FORCE_TUNING_ERR (W)
 *
 * Force Event for Tuning Error (UHS-I Mode only) 
 * Values: 
 * 0x0 (FALSE): Not Affected
 * 0x1 (TRUE): Tuning Error Status is set
 */
#define SDXC_FORCE_EVENT_FORCE_TUNING_ERR_MASK (0x4000000UL)
#define SDXC_FORCE_EVENT_FORCE_TUNING_ERR_SHIFT (26U)
#define SDXC_FORCE_EVENT_FORCE_TUNING_ERR_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_TUNING_ERR_SHIFT) & SDXC_FORCE_EVENT_FORCE_TUNING_ERR_MASK)
#define SDXC_FORCE_EVENT_FORCE_TUNING_ERR_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_TUNING_ERR_MASK) >> SDXC_FORCE_EVENT_FORCE_TUNING_ERR_SHIFT)

/*
 * FORCE_ADMA_ERR (W)
 *
 * Force Event for ADMA Error
 * Values: 
 * 0x0 (FALSE): Not Affected
 * 0x1 (TRUE): ADMA Error Status is set
 */
#define SDXC_FORCE_EVENT_FORCE_ADMA_ERR_MASK (0x2000000UL)
#define SDXC_FORCE_EVENT_FORCE_ADMA_ERR_SHIFT (25U)
#define SDXC_FORCE_EVENT_FORCE_ADMA_ERR_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_ADMA_ERR_SHIFT) & SDXC_FORCE_EVENT_FORCE_ADMA_ERR_MASK)
#define SDXC_FORCE_EVENT_FORCE_ADMA_ERR_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_ADMA_ERR_MASK) >> SDXC_FORCE_EVENT_FORCE_ADMA_ERR_SHIFT)

/*
 * FORCE_AUTO_CMD_ERR (W)
 *
 * Force Event for Auto CMD Error (SD/eMMC Mode only)
 * Values: 
 * 0x0 (FALSE): Not Affected
 * 0x1 (TRUE): Auto CMD Error Status is set
 */
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_ERR_MASK (0x1000000UL)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_ERR_SHIFT (24U)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_ERR_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_AUTO_CMD_ERR_SHIFT) & SDXC_FORCE_EVENT_FORCE_AUTO_CMD_ERR_MASK)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_ERR_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_AUTO_CMD_ERR_MASK) >> SDXC_FORCE_EVENT_FORCE_AUTO_CMD_ERR_SHIFT)

/*
 * FORCE_CUR_LMT_ERR (W)
 *
 * Force Event for Current Limit Error 
 * Values: 
 * 0x0 (FALSE): Not Affected
 * 0x1 (TRUE): Current Limit Error Status is set
 */
#define SDXC_FORCE_EVENT_FORCE_CUR_LMT_ERR_MASK (0x800000UL)
#define SDXC_FORCE_EVENT_FORCE_CUR_LMT_ERR_SHIFT (23U)
#define SDXC_FORCE_EVENT_FORCE_CUR_LMT_ERR_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_CUR_LMT_ERR_SHIFT) & SDXC_FORCE_EVENT_FORCE_CUR_LMT_ERR_MASK)
#define SDXC_FORCE_EVENT_FORCE_CUR_LMT_ERR_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_CUR_LMT_ERR_MASK) >> SDXC_FORCE_EVENT_FORCE_CUR_LMT_ERR_SHIFT)

/*
 * FORCE_DATA_END_BIT_ERR (W)
 *
 * Force Event for Data End Bit Error (SD/eMMC Mode only) 
 * Values: 
 * 0x0 (FALSE): Not Affected
 * 0x1 (TRUE): Data End Bit Error Status is set
 */
#define SDXC_FORCE_EVENT_FORCE_DATA_END_BIT_ERR_MASK (0x400000UL)
#define SDXC_FORCE_EVENT_FORCE_DATA_END_BIT_ERR_SHIFT (22U)
#define SDXC_FORCE_EVENT_FORCE_DATA_END_BIT_ERR_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_DATA_END_BIT_ERR_SHIFT) & SDXC_FORCE_EVENT_FORCE_DATA_END_BIT_ERR_MASK)
#define SDXC_FORCE_EVENT_FORCE_DATA_END_BIT_ERR_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_DATA_END_BIT_ERR_MASK) >> SDXC_FORCE_EVENT_FORCE_DATA_END_BIT_ERR_SHIFT)

/*
 * FORCE_DATA_CRC_ERR (W)
 *
 * Force Event for Data CRC Error (SD/eMMC Mode only) 
 * Values: 
 * 0x0 (FALSE): Not Affected
 * 0x1 (TRUE): Data CRC Error Status is set
 */
#define SDXC_FORCE_EVENT_FORCE_DATA_CRC_ERR_MASK (0x200000UL)
#define SDXC_FORCE_EVENT_FORCE_DATA_CRC_ERR_SHIFT (21U)
#define SDXC_FORCE_EVENT_FORCE_DATA_CRC_ERR_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_DATA_CRC_ERR_SHIFT) & SDXC_FORCE_EVENT_FORCE_DATA_CRC_ERR_MASK)
#define SDXC_FORCE_EVENT_FORCE_DATA_CRC_ERR_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_DATA_CRC_ERR_MASK) >> SDXC_FORCE_EVENT_FORCE_DATA_CRC_ERR_SHIFT)

/*
 * FORCE_DATA_TOUT_ERR (W)
 *
 * Force Event for Data Timeout Error (SD/eMMC Mode only) 
 * Values: 
 * 0x0 (FALSE): Not Affected
 * 0x1 (TRUE): Data Timeout Error Status is set
 */
#define SDXC_FORCE_EVENT_FORCE_DATA_TOUT_ERR_MASK (0x100000UL)
#define SDXC_FORCE_EVENT_FORCE_DATA_TOUT_ERR_SHIFT (20U)
#define SDXC_FORCE_EVENT_FORCE_DATA_TOUT_ERR_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_DATA_TOUT_ERR_SHIFT) & SDXC_FORCE_EVENT_FORCE_DATA_TOUT_ERR_MASK)
#define SDXC_FORCE_EVENT_FORCE_DATA_TOUT_ERR_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_DATA_TOUT_ERR_MASK) >> SDXC_FORCE_EVENT_FORCE_DATA_TOUT_ERR_SHIFT)

/*
 * FORCE_CMD_IDX_ERR (W)
 *
 * Force Event for Command Index Error (SD/eMMC Mode only)
 * Values: 
 * 0x0 (FALSE): Not Affected
 * 0x1 (TRUE): Command Index Error Status is set
 */
#define SDXC_FORCE_EVENT_FORCE_CMD_IDX_ERR_MASK (0x80000UL)
#define SDXC_FORCE_EVENT_FORCE_CMD_IDX_ERR_SHIFT (19U)
#define SDXC_FORCE_EVENT_FORCE_CMD_IDX_ERR_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_CMD_IDX_ERR_SHIFT) & SDXC_FORCE_EVENT_FORCE_CMD_IDX_ERR_MASK)
#define SDXC_FORCE_EVENT_FORCE_CMD_IDX_ERR_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_CMD_IDX_ERR_MASK) >> SDXC_FORCE_EVENT_FORCE_CMD_IDX_ERR_SHIFT)

/*
 * FORCE_CMD_END_BIT_ERR (W)
 *
 * Force Event for Command End Bit Error (SD/eMMC Mode only)
 * Values: 
 * 0x0 (FALSE): Not Affected
 * 0x1 (TRUE): Command End Bit Error Status is set
 */
#define SDXC_FORCE_EVENT_FORCE_CMD_END_BIT_ERR_MASK (0x40000UL)
#define SDXC_FORCE_EVENT_FORCE_CMD_END_BIT_ERR_SHIFT (18U)
#define SDXC_FORCE_EVENT_FORCE_CMD_END_BIT_ERR_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_CMD_END_BIT_ERR_SHIFT) & SDXC_FORCE_EVENT_FORCE_CMD_END_BIT_ERR_MASK)
#define SDXC_FORCE_EVENT_FORCE_CMD_END_BIT_ERR_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_CMD_END_BIT_ERR_MASK) >> SDXC_FORCE_EVENT_FORCE_CMD_END_BIT_ERR_SHIFT)

/*
 * FORCE_CMD_CRC_ERR (W)
 *
 * Force Event for Command CRC Error (SD/eMMC Mode only) 
 * Values: 
 * 0x0 (FALSE): Not Affected
 * 0x1 (TRUE): Command CRC Error Status is set
 */
#define SDXC_FORCE_EVENT_FORCE_CMD_CRC_ERR_MASK (0x20000UL)
#define SDXC_FORCE_EVENT_FORCE_CMD_CRC_ERR_SHIFT (17U)
#define SDXC_FORCE_EVENT_FORCE_CMD_CRC_ERR_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_CMD_CRC_ERR_SHIFT) & SDXC_FORCE_EVENT_FORCE_CMD_CRC_ERR_MASK)
#define SDXC_FORCE_EVENT_FORCE_CMD_CRC_ERR_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_CMD_CRC_ERR_MASK) >> SDXC_FORCE_EVENT_FORCE_CMD_CRC_ERR_SHIFT)

/*
 * FORCE_CMD_TOUT_ERR (W)
 *
 * Force Event for Command Timeout Error (SD/eMMC Mode only)
 * Values: 
 * 0x0 (FALSE): Not Affected
 * 0x1 (TRUE): Command Timeout Error Status is set
 */
#define SDXC_FORCE_EVENT_FORCE_CMD_TOUT_ERR_MASK (0x10000UL)
#define SDXC_FORCE_EVENT_FORCE_CMD_TOUT_ERR_SHIFT (16U)
#define SDXC_FORCE_EVENT_FORCE_CMD_TOUT_ERR_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_CMD_TOUT_ERR_SHIFT) & SDXC_FORCE_EVENT_FORCE_CMD_TOUT_ERR_MASK)
#define SDXC_FORCE_EVENT_FORCE_CMD_TOUT_ERR_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_CMD_TOUT_ERR_MASK) >> SDXC_FORCE_EVENT_FORCE_CMD_TOUT_ERR_SHIFT)

/*
 * FORCE_CMD_NOT_ISSUED_AUTO_CMD12 (W)
 *
 * Force Event for Command Not Issued By Auto CMD12 Error
 * Values: 
 * 0x1 (TRUE): Command Not Issued By Auto CMD12 Error Status is set
 * 0x0 (FALSE): Not Affected
 */
#define SDXC_FORCE_EVENT_FORCE_CMD_NOT_ISSUED_AUTO_CMD12_MASK (0x80U)
#define SDXC_FORCE_EVENT_FORCE_CMD_NOT_ISSUED_AUTO_CMD12_SHIFT (7U)
#define SDXC_FORCE_EVENT_FORCE_CMD_NOT_ISSUED_AUTO_CMD12_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_CMD_NOT_ISSUED_AUTO_CMD12_SHIFT) & SDXC_FORCE_EVENT_FORCE_CMD_NOT_ISSUED_AUTO_CMD12_MASK)
#define SDXC_FORCE_EVENT_FORCE_CMD_NOT_ISSUED_AUTO_CMD12_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_CMD_NOT_ISSUED_AUTO_CMD12_MASK) >> SDXC_FORCE_EVENT_FORCE_CMD_NOT_ISSUED_AUTO_CMD12_SHIFT)

/*
 * FORCE_AUTO_CMD_RESP_ERR (W)
 *
 * Force Event for Auto CMD Response Error
 * Values: 
 * 0x1 (TRUE): Auto CMD Response Error Status is set
 * 0x0 (FALSE): Not Affected
 */
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_RESP_ERR_MASK (0x20U)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_RESP_ERR_SHIFT (5U)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_RESP_ERR_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_AUTO_CMD_RESP_ERR_SHIFT) & SDXC_FORCE_EVENT_FORCE_AUTO_CMD_RESP_ERR_MASK)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_RESP_ERR_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_AUTO_CMD_RESP_ERR_MASK) >> SDXC_FORCE_EVENT_FORCE_AUTO_CMD_RESP_ERR_SHIFT)

/*
 * FORCE_AUTO_CMD_IDX_ERR (W)
 *
 * Force Event for Auto CMD Index Error
 * Values: 
 * 0x1 (TRUE): Auto CMD Index Error Status is set
 * 0x0 (FALSE): Not Affected
 */
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_IDX_ERR_MASK (0x10U)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_IDX_ERR_SHIFT (4U)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_IDX_ERR_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_AUTO_CMD_IDX_ERR_SHIFT) & SDXC_FORCE_EVENT_FORCE_AUTO_CMD_IDX_ERR_MASK)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_IDX_ERR_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_AUTO_CMD_IDX_ERR_MASK) >> SDXC_FORCE_EVENT_FORCE_AUTO_CMD_IDX_ERR_SHIFT)

/*
 * FORCE_AUTO_CMD_EBIT_ERR (W)
 *
 * Force Event for Auto CMD End Bit Error
 * Values: 
 * 0x1 (TRUE): Auto CMD End Bit Error Status is set
 * 0x0 (FALSE): Not Affected
 */
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_EBIT_ERR_MASK (0x8U)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_EBIT_ERR_SHIFT (3U)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_EBIT_ERR_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_AUTO_CMD_EBIT_ERR_SHIFT) & SDXC_FORCE_EVENT_FORCE_AUTO_CMD_EBIT_ERR_MASK)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_EBIT_ERR_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_AUTO_CMD_EBIT_ERR_MASK) >> SDXC_FORCE_EVENT_FORCE_AUTO_CMD_EBIT_ERR_SHIFT)

/*
 * FORCE_AUTO_CMD_CRC_ERR (W)
 *
 * Force Event for Auto CMD CRC Error
 * Values: 
 * 0x1 (TRUE): Auto CMD CRC Error Status is set
 * 0x0 (FALSE): Not Affected
 */
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_CRC_ERR_MASK (0x4U)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_CRC_ERR_SHIFT (2U)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_CRC_ERR_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_AUTO_CMD_CRC_ERR_SHIFT) & SDXC_FORCE_EVENT_FORCE_AUTO_CMD_CRC_ERR_MASK)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_CRC_ERR_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_AUTO_CMD_CRC_ERR_MASK) >> SDXC_FORCE_EVENT_FORCE_AUTO_CMD_CRC_ERR_SHIFT)

/*
 * FORCE_AUTO_CMD_TOUT_ERR (W)
 *
 * Force Event for Auto CMD Timeout Error
 * Values: 
 * 0x1 (TRUE): Auto CMD Timeout Error Status is set
 * 0x0 (FALSE): Not Affected
 */
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_TOUT_ERR_MASK (0x2U)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_TOUT_ERR_SHIFT (1U)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_TOUT_ERR_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_AUTO_CMD_TOUT_ERR_SHIFT) & SDXC_FORCE_EVENT_FORCE_AUTO_CMD_TOUT_ERR_MASK)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD_TOUT_ERR_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_AUTO_CMD_TOUT_ERR_MASK) >> SDXC_FORCE_EVENT_FORCE_AUTO_CMD_TOUT_ERR_SHIFT)

/*
 * FORCE_AUTO_CMD12_NOT_EXEC (W)
 *
 * Force Event for Auto CMD12 Not Executed
 * Values: 
 * 0x1 (TRUE): Auto CMD12 Not Executed Status is set
 * 0x0 (FALSE): Not Affected
 */
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD12_NOT_EXEC_MASK (0x1U)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD12_NOT_EXEC_SHIFT (0U)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD12_NOT_EXEC_SET(x) (((uint32_t)(x) << SDXC_FORCE_EVENT_FORCE_AUTO_CMD12_NOT_EXEC_SHIFT) & SDXC_FORCE_EVENT_FORCE_AUTO_CMD12_NOT_EXEC_MASK)
#define SDXC_FORCE_EVENT_FORCE_AUTO_CMD12_NOT_EXEC_GET(x) (((uint32_t)(x) & SDXC_FORCE_EVENT_FORCE_AUTO_CMD12_NOT_EXEC_MASK) >> SDXC_FORCE_EVENT_FORCE_AUTO_CMD12_NOT_EXEC_SHIFT)

/* Bitfield definition for register: ADMA_ERR_STAT */
/*
 * ADMA_LEN_ERR (R)
 *
 * ADMA Length Mismatch Error States
 * This error occurs in the following instances:
 * While the Block Count Enable is being set, the total data length specified by the Descriptor table is different from that specified by the Block Count and Block Length
 * When the total data length cannot be divided by the block length
 * Values: 
 * 0x0 (NO_ERR): No Error
 * 0x1 (ERROR): Error
 */
#define SDXC_ADMA_ERR_STAT_ADMA_LEN_ERR_MASK (0x4U)
#define SDXC_ADMA_ERR_STAT_ADMA_LEN_ERR_SHIFT (2U)
#define SDXC_ADMA_ERR_STAT_ADMA_LEN_ERR_GET(x) (((uint32_t)(x) & SDXC_ADMA_ERR_STAT_ADMA_LEN_ERR_MASK) >> SDXC_ADMA_ERR_STAT_ADMA_LEN_ERR_SHIFT)

/*
 * ADMA_ERR_STATES (R)
 *
 * ADMA Error States
 * These bits indicate the state of ADMA when an error occurs during ADMA data transfer.
 * Values: 
 * 0x0 (ST_STOP): Stop DMA - SYS_ADR register points to a location next to the error descriptor
 * 0x1 (ST_FDS): Fetch Descriptor - SYS_ADR register points to the error descriptor
 * 0x2 (UNUSED): Never set this state
 * 0x3 (ST_TFR): Transfer Data - SYS_ADR register points to a location next to the error descriptor
 */
#define SDXC_ADMA_ERR_STAT_ADMA_ERR_STATES_MASK (0x3U)
#define SDXC_ADMA_ERR_STAT_ADMA_ERR_STATES_SHIFT (0U)
#define SDXC_ADMA_ERR_STAT_ADMA_ERR_STATES_GET(x) (((uint32_t)(x) & SDXC_ADMA_ERR_STAT_ADMA_ERR_STATES_MASK) >> SDXC_ADMA_ERR_STAT_ADMA_ERR_STATES_SHIFT)

/* Bitfield definition for register: ADMA_SYS_ADDR */
/*
 * ADMA_SA (RW)
 *
 * ADMA System Address
 * These bits indicate the lower 32 bits of the ADMA system address.
 * SDMA: If Host Version 4 Enable is set to 1, this register stores the system address of the data location
 * ADMA2: This register stores the byte address of the executing command of the descriptor table
 * ADMA3: This register is set by ADMA3. ADMA2 increments the address of this register that points to the next line, every time a Descriptor line is fetched.
 */
#define SDXC_ADMA_SYS_ADDR_ADMA_SA_MASK (0xFFFFFFFFUL)
#define SDXC_ADMA_SYS_ADDR_ADMA_SA_SHIFT (0U)
#define SDXC_ADMA_SYS_ADDR_ADMA_SA_SET(x) (((uint32_t)(x) << SDXC_ADMA_SYS_ADDR_ADMA_SA_SHIFT) & SDXC_ADMA_SYS_ADDR_ADMA_SA_MASK)
#define SDXC_ADMA_SYS_ADDR_ADMA_SA_GET(x) (((uint32_t)(x) & SDXC_ADMA_SYS_ADDR_ADMA_SA_MASK) >> SDXC_ADMA_SYS_ADDR_ADMA_SA_SHIFT)

/* Bitfield definition for register array: PRESET */
/*
 * DRV_SEL_VAL (R)
 *
 * Driver Strength Select Value
 * These bits indicate that the Driver strength is supported by 1.8V signaling bus speed modes. These bits are meaningless for 3.3V signaling.
 * Values: 
 * 0x0 (TYPEB): Driver Type B is selected
 * 0x1 (TYPEA): Driver Type A is selected
 * 0x2 (TYPEC): Driver Type C is selected
 * 0x3 (TYPED): Driver Type D is selected
 */
#define SDXC_PRESET_DRV_SEL_VAL_MASK (0xC000U)
#define SDXC_PRESET_DRV_SEL_VAL_SHIFT (14U)
#define SDXC_PRESET_DRV_SEL_VAL_GET(x) (((uint16_t)(x) & SDXC_PRESET_DRV_SEL_VAL_MASK) >> SDXC_PRESET_DRV_SEL_VAL_SHIFT)

/*
 * CLK_GEN_SEL_VAL (R)
 *
 * Clock Generator Select Value
 * This bit is effective when the Host Controller supports a programmable clock generator.
 * Values: 
 * 0x0 (FALSE): Host Controller Ver2.0 Compatible Clock Generator
 * 0x1 (PROG): Programmable Clock Generator
 */
#define SDXC_PRESET_CLK_GEN_SEL_VAL_MASK (0x400U)
#define SDXC_PRESET_CLK_GEN_SEL_VAL_SHIFT (10U)
#define SDXC_PRESET_CLK_GEN_SEL_VAL_GET(x) (((uint16_t)(x) & SDXC_PRESET_CLK_GEN_SEL_VAL_MASK) >> SDXC_PRESET_CLK_GEN_SEL_VAL_SHIFT)

/*
 * FREQ_SEL_VAL (R)
 *
 * SDCLK/RCLK Frequency Select Value
 * 10-bit preset value to be set in SDCLK/RCLK Frequency Select field of the Clock Control register described by a Host System.
 */
#define SDXC_PRESET_FREQ_SEL_VAL_MASK (0x3FFU)
#define SDXC_PRESET_FREQ_SEL_VAL_SHIFT (0U)
#define SDXC_PRESET_FREQ_SEL_VAL_GET(x) (((uint16_t)(x) & SDXC_PRESET_FREQ_SEL_VAL_MASK) >> SDXC_PRESET_FREQ_SEL_VAL_SHIFT)

/* Bitfield definition for register: ADMA_ID_ADDR */
/*
 * ADMA_ID_ADDR (RW)
 *
 * ADMA Integrated Descriptor Address
 * These bits indicate the lower 32-bit of the ADMA Integrated Descriptor address. The start address of Integrated Descriptor is set to these register bits. The ADMA3 fetches one Descriptor Address and increments these bits to indicate the next Descriptor address.
 */
#define SDXC_ADMA_ID_ADDR_ADMA_ID_ADDR_MASK (0xFFFFFFFFUL)
#define SDXC_ADMA_ID_ADDR_ADMA_ID_ADDR_SHIFT (0U)
#define SDXC_ADMA_ID_ADDR_ADMA_ID_ADDR_SET(x) (((uint32_t)(x) << SDXC_ADMA_ID_ADDR_ADMA_ID_ADDR_SHIFT) & SDXC_ADMA_ID_ADDR_ADMA_ID_ADDR_MASK)
#define SDXC_ADMA_ID_ADDR_ADMA_ID_ADDR_GET(x) (((uint32_t)(x) & SDXC_ADMA_ID_ADDR_ADMA_ID_ADDR_MASK) >> SDXC_ADMA_ID_ADDR_ADMA_ID_ADDR_SHIFT)

/* Bitfield definition for register: P_EMBEDDED_CNTRL */
/*
 * REG_OFFSET_ADDR (R)
 *
 * 
 * Offset Address of Embedded Control register. 
 * 
 */
#define SDXC_P_EMBEDDED_CNTRL_REG_OFFSET_ADDR_MASK (0xFFFU)
#define SDXC_P_EMBEDDED_CNTRL_REG_OFFSET_ADDR_SHIFT (0U)
#define SDXC_P_EMBEDDED_CNTRL_REG_OFFSET_ADDR_GET(x) (((uint16_t)(x) & SDXC_P_EMBEDDED_CNTRL_REG_OFFSET_ADDR_MASK) >> SDXC_P_EMBEDDED_CNTRL_REG_OFFSET_ADDR_SHIFT)

/* Bitfield definition for register: P_VENDOR_SPECIFIC_AREA */
/*
 * REG_OFFSET_ADDR (R)
 *
 * 
 * Base offset Address for Vendor-Specific registers. 
 * 
 */
#define SDXC_P_VENDOR_SPECIFIC_AREA_REG_OFFSET_ADDR_MASK (0xFFFU)
#define SDXC_P_VENDOR_SPECIFIC_AREA_REG_OFFSET_ADDR_SHIFT (0U)
#define SDXC_P_VENDOR_SPECIFIC_AREA_REG_OFFSET_ADDR_GET(x) (((uint16_t)(x) & SDXC_P_VENDOR_SPECIFIC_AREA_REG_OFFSET_ADDR_MASK) >> SDXC_P_VENDOR_SPECIFIC_AREA_REG_OFFSET_ADDR_SHIFT)

/* Bitfield definition for register: P_VENDOR2_SPECIFIC_AREA */
/*
 * REG_OFFSET_ADDR (R)
 *
 * 
 * Base offset Address for Command Queuing registers. 
 * 
 */
#define SDXC_P_VENDOR2_SPECIFIC_AREA_REG_OFFSET_ADDR_MASK (0xFFFFU)
#define SDXC_P_VENDOR2_SPECIFIC_AREA_REG_OFFSET_ADDR_SHIFT (0U)
#define SDXC_P_VENDOR2_SPECIFIC_AREA_REG_OFFSET_ADDR_GET(x) (((uint16_t)(x) & SDXC_P_VENDOR2_SPECIFIC_AREA_REG_OFFSET_ADDR_MASK) >> SDXC_P_VENDOR2_SPECIFIC_AREA_REG_OFFSET_ADDR_SHIFT)

/* Bitfield definition for register: SLOT_INTR_STATUS */
/*
 * INTR_SLOT (R)
 *
 * Interrupt signal for each Slot 
 * These status bits indicate the logical OR of Interrupt signal and Wakeup signal for each slot. A maximum of 8 slots can be defined. If one interrupt signal is associated with multiple slots, the Host Driver can identify the interrupt that is generated by reading these bits. By a power on reset or by setting Software Reset For All bit, the interrupt signals are de-asserted and this status reads 00h.
 * Bit 00: Slot 1
 * Bit 01: Slot 2
 * Bit 02: Slot 3
 * .......... 
 * .......... 
 * Bit 07: Slot 8
 * Note: MSHC Host Controller support single card slot. This register shall always return 0.
 */
#define SDXC_SLOT_INTR_STATUS_INTR_SLOT_MASK (0xFFU)
#define SDXC_SLOT_INTR_STATUS_INTR_SLOT_SHIFT (0U)
#define SDXC_SLOT_INTR_STATUS_INTR_SLOT_GET(x) (((uint16_t)(x) & SDXC_SLOT_INTR_STATUS_INTR_SLOT_MASK) >> SDXC_SLOT_INTR_STATUS_INTR_SLOT_SHIFT)

/* Bitfield definition for register: HOST_CTRL_VERS */
/*
 * VENDOR_VERSION_NUM (R)
 *
 * 
 * Vendor Version Number 
 * This field is reserved for the vendor version number. Host Driver must not use this status.
 * 
 */
#define SDXC_HOST_CTRL_VERS_VENDOR_VERSION_NUM_MASK (0xFF00U)
#define SDXC_HOST_CTRL_VERS_VENDOR_VERSION_NUM_SHIFT (8U)
#define SDXC_HOST_CTRL_VERS_VENDOR_VERSION_NUM_GET(x) (((uint16_t)(x) & SDXC_HOST_CTRL_VERS_VENDOR_VERSION_NUM_MASK) >> SDXC_HOST_CTRL_VERS_VENDOR_VERSION_NUM_SHIFT)

/*
 * SPEC_VERSION_NUM (R)
 *
 * Specification Version Number 
 * These bits indicate the Host controller specification version. The upper and lower 4-bits indicate the version. Values 0x06-0xFF are reserved.
 * Values: 
 * 0x0 (VER_1_00): SD Host Controller Specification Version 1.00
 * 0x1 (VER_2_00): SD Host Controller Specification Version 2.00
 * 0x2 (VER_3_00): SD Host Controller Specification Version 3.00
 * 0x3 (VER_4_00): SD Host Controller Specification Version 4.00
 * 0x4 (VER_4_10): SD Host Controller Specification Version 4.10
 * 0x5 (VER_4_20): SD Host Controller Specification Version 4.20
 */
#define SDXC_HOST_CTRL_VERS_SPEC_VERSION_NUM_MASK (0xFFU)
#define SDXC_HOST_CTRL_VERS_SPEC_VERSION_NUM_SHIFT (0U)
#define SDXC_HOST_CTRL_VERS_SPEC_VERSION_NUM_GET(x) (((uint16_t)(x) & SDXC_HOST_CTRL_VERS_SPEC_VERSION_NUM_MASK) >> SDXC_HOST_CTRL_VERS_SPEC_VERSION_NUM_SHIFT)

/* Bitfield definition for register: CQVER */
/*
 * EMMC_VER_MAHOR (R)
 *
 * 
 */
#define SDXC_CQVER_EMMC_VER_MAHOR_MASK (0xF00U)
#define SDXC_CQVER_EMMC_VER_MAHOR_SHIFT (8U)
#define SDXC_CQVER_EMMC_VER_MAHOR_GET(x) (((uint32_t)(x) & SDXC_CQVER_EMMC_VER_MAHOR_MASK) >> SDXC_CQVER_EMMC_VER_MAHOR_SHIFT)

/*
 * EMMC_VER_MINOR (R)
 *
 * 
 */
#define SDXC_CQVER_EMMC_VER_MINOR_MASK (0xF0U)
#define SDXC_CQVER_EMMC_VER_MINOR_SHIFT (4U)
#define SDXC_CQVER_EMMC_VER_MINOR_GET(x) (((uint32_t)(x) & SDXC_CQVER_EMMC_VER_MINOR_MASK) >> SDXC_CQVER_EMMC_VER_MINOR_SHIFT)

/*
 * EMMC_VER_SUFFIX (R)
 *
 * 
 */
#define SDXC_CQVER_EMMC_VER_SUFFIX_MASK (0xFU)
#define SDXC_CQVER_EMMC_VER_SUFFIX_SHIFT (0U)
#define SDXC_CQVER_EMMC_VER_SUFFIX_GET(x) (((uint32_t)(x) & SDXC_CQVER_EMMC_VER_SUFFIX_MASK) >> SDXC_CQVER_EMMC_VER_SUFFIX_SHIFT)

/* Bitfield definition for register: CQCAP */
/*
 * CRYPTO_SUPPORT (R)
 *
 * 
 */
#define SDXC_CQCAP_CRYPTO_SUPPORT_MASK (0x10000000UL)
#define SDXC_CQCAP_CRYPTO_SUPPORT_SHIFT (28U)
#define SDXC_CQCAP_CRYPTO_SUPPORT_GET(x) (((uint32_t)(x) & SDXC_CQCAP_CRYPTO_SUPPORT_MASK) >> SDXC_CQCAP_CRYPTO_SUPPORT_SHIFT)

/*
 * ITCFMUL (R)
 *
 * 
 */
#define SDXC_CQCAP_ITCFMUL_MASK (0xF000U)
#define SDXC_CQCAP_ITCFMUL_SHIFT (12U)
#define SDXC_CQCAP_ITCFMUL_GET(x) (((uint32_t)(x) & SDXC_CQCAP_ITCFMUL_MASK) >> SDXC_CQCAP_ITCFMUL_SHIFT)

/*
 * ITCFVAL (R)
 *
 * 
 */
#define SDXC_CQCAP_ITCFVAL_MASK (0x3FFU)
#define SDXC_CQCAP_ITCFVAL_SHIFT (0U)
#define SDXC_CQCAP_ITCFVAL_GET(x) (((uint32_t)(x) & SDXC_CQCAP_ITCFVAL_MASK) >> SDXC_CQCAP_ITCFVAL_SHIFT)

/* Bitfield definition for register: CQCFG */
/*
 * DCMD_EN (RW)
 *
 * 
 */
#define SDXC_CQCFG_DCMD_EN_MASK (0x1000U)
#define SDXC_CQCFG_DCMD_EN_SHIFT (12U)
#define SDXC_CQCFG_DCMD_EN_SET(x) (((uint32_t)(x) << SDXC_CQCFG_DCMD_EN_SHIFT) & SDXC_CQCFG_DCMD_EN_MASK)
#define SDXC_CQCFG_DCMD_EN_GET(x) (((uint32_t)(x) & SDXC_CQCFG_DCMD_EN_MASK) >> SDXC_CQCFG_DCMD_EN_SHIFT)

/*
 * TASK_DESC_SIZE (RW)
 *
 * 
 */
#define SDXC_CQCFG_TASK_DESC_SIZE_MASK (0x100U)
#define SDXC_CQCFG_TASK_DESC_SIZE_SHIFT (8U)
#define SDXC_CQCFG_TASK_DESC_SIZE_SET(x) (((uint32_t)(x) << SDXC_CQCFG_TASK_DESC_SIZE_SHIFT) & SDXC_CQCFG_TASK_DESC_SIZE_MASK)
#define SDXC_CQCFG_TASK_DESC_SIZE_GET(x) (((uint32_t)(x) & SDXC_CQCFG_TASK_DESC_SIZE_MASK) >> SDXC_CQCFG_TASK_DESC_SIZE_SHIFT)

/*
 * CQ_EN (RW)
 *
 * 
 */
#define SDXC_CQCFG_CQ_EN_MASK (0x1U)
#define SDXC_CQCFG_CQ_EN_SHIFT (0U)
#define SDXC_CQCFG_CQ_EN_SET(x) (((uint32_t)(x) << SDXC_CQCFG_CQ_EN_SHIFT) & SDXC_CQCFG_CQ_EN_MASK)
#define SDXC_CQCFG_CQ_EN_GET(x) (((uint32_t)(x) & SDXC_CQCFG_CQ_EN_MASK) >> SDXC_CQCFG_CQ_EN_SHIFT)

/* Bitfield definition for register: CQCTL */
/*
 * CLR_ALL_TASKS (RW)
 *
 * 
 */
#define SDXC_CQCTL_CLR_ALL_TASKS_MASK (0x100U)
#define SDXC_CQCTL_CLR_ALL_TASKS_SHIFT (8U)
#define SDXC_CQCTL_CLR_ALL_TASKS_SET(x) (((uint32_t)(x) << SDXC_CQCTL_CLR_ALL_TASKS_SHIFT) & SDXC_CQCTL_CLR_ALL_TASKS_MASK)
#define SDXC_CQCTL_CLR_ALL_TASKS_GET(x) (((uint32_t)(x) & SDXC_CQCTL_CLR_ALL_TASKS_MASK) >> SDXC_CQCTL_CLR_ALL_TASKS_SHIFT)

/*
 * HALT (RW)
 *
 * 
 */
#define SDXC_CQCTL_HALT_MASK (0x1U)
#define SDXC_CQCTL_HALT_SHIFT (0U)
#define SDXC_CQCTL_HALT_SET(x) (((uint32_t)(x) << SDXC_CQCTL_HALT_SHIFT) & SDXC_CQCTL_HALT_MASK)
#define SDXC_CQCTL_HALT_GET(x) (((uint32_t)(x) & SDXC_CQCTL_HALT_MASK) >> SDXC_CQCTL_HALT_SHIFT)

/* Bitfield definition for register: CQIS */
/*
 * TCL (RW)
 *
 * 
 */
#define SDXC_CQIS_TCL_MASK (0x8U)
#define SDXC_CQIS_TCL_SHIFT (3U)
#define SDXC_CQIS_TCL_SET(x) (((uint32_t)(x) << SDXC_CQIS_TCL_SHIFT) & SDXC_CQIS_TCL_MASK)
#define SDXC_CQIS_TCL_GET(x) (((uint32_t)(x) & SDXC_CQIS_TCL_MASK) >> SDXC_CQIS_TCL_SHIFT)

/*
 * RED (RW)
 *
 * 
 */
#define SDXC_CQIS_RED_MASK (0x4U)
#define SDXC_CQIS_RED_SHIFT (2U)
#define SDXC_CQIS_RED_SET(x) (((uint32_t)(x) << SDXC_CQIS_RED_SHIFT) & SDXC_CQIS_RED_MASK)
#define SDXC_CQIS_RED_GET(x) (((uint32_t)(x) & SDXC_CQIS_RED_MASK) >> SDXC_CQIS_RED_SHIFT)

/*
 * TCC (RW)
 *
 * 
 */
#define SDXC_CQIS_TCC_MASK (0x2U)
#define SDXC_CQIS_TCC_SHIFT (1U)
#define SDXC_CQIS_TCC_SET(x) (((uint32_t)(x) << SDXC_CQIS_TCC_SHIFT) & SDXC_CQIS_TCC_MASK)
#define SDXC_CQIS_TCC_GET(x) (((uint32_t)(x) & SDXC_CQIS_TCC_MASK) >> SDXC_CQIS_TCC_SHIFT)

/*
 * HAC (RW)
 *
 * 
 */
#define SDXC_CQIS_HAC_MASK (0x1U)
#define SDXC_CQIS_HAC_SHIFT (0U)
#define SDXC_CQIS_HAC_SET(x) (((uint32_t)(x) << SDXC_CQIS_HAC_SHIFT) & SDXC_CQIS_HAC_MASK)
#define SDXC_CQIS_HAC_GET(x) (((uint32_t)(x) & SDXC_CQIS_HAC_MASK) >> SDXC_CQIS_HAC_SHIFT)

/* Bitfield definition for register: CQISE */
/*
 * TCL_STE (RW)
 *
 * 
 */
#define SDXC_CQISE_TCL_STE_MASK (0x8U)
#define SDXC_CQISE_TCL_STE_SHIFT (3U)
#define SDXC_CQISE_TCL_STE_SET(x) (((uint32_t)(x) << SDXC_CQISE_TCL_STE_SHIFT) & SDXC_CQISE_TCL_STE_MASK)
#define SDXC_CQISE_TCL_STE_GET(x) (((uint32_t)(x) & SDXC_CQISE_TCL_STE_MASK) >> SDXC_CQISE_TCL_STE_SHIFT)

/*
 * RED_STE (RW)
 *
 * 
 */
#define SDXC_CQISE_RED_STE_MASK (0x4U)
#define SDXC_CQISE_RED_STE_SHIFT (2U)
#define SDXC_CQISE_RED_STE_SET(x) (((uint32_t)(x) << SDXC_CQISE_RED_STE_SHIFT) & SDXC_CQISE_RED_STE_MASK)
#define SDXC_CQISE_RED_STE_GET(x) (((uint32_t)(x) & SDXC_CQISE_RED_STE_MASK) >> SDXC_CQISE_RED_STE_SHIFT)

/*
 * TCC_STE (RW)
 *
 * 
 */
#define SDXC_CQISE_TCC_STE_MASK (0x2U)
#define SDXC_CQISE_TCC_STE_SHIFT (1U)
#define SDXC_CQISE_TCC_STE_SET(x) (((uint32_t)(x) << SDXC_CQISE_TCC_STE_SHIFT) & SDXC_CQISE_TCC_STE_MASK)
#define SDXC_CQISE_TCC_STE_GET(x) (((uint32_t)(x) & SDXC_CQISE_TCC_STE_MASK) >> SDXC_CQISE_TCC_STE_SHIFT)

/*
 * HAC_STE (RW)
 *
 * 
 */
#define SDXC_CQISE_HAC_STE_MASK (0x1U)
#define SDXC_CQISE_HAC_STE_SHIFT (0U)
#define SDXC_CQISE_HAC_STE_SET(x) (((uint32_t)(x) << SDXC_CQISE_HAC_STE_SHIFT) & SDXC_CQISE_HAC_STE_MASK)
#define SDXC_CQISE_HAC_STE_GET(x) (((uint32_t)(x) & SDXC_CQISE_HAC_STE_MASK) >> SDXC_CQISE_HAC_STE_SHIFT)

/* Bitfield definition for register: CQISGE */
/*
 * TCL_SGE (RW)
 *
 * 
 */
#define SDXC_CQISGE_TCL_SGE_MASK (0x8U)
#define SDXC_CQISGE_TCL_SGE_SHIFT (3U)
#define SDXC_CQISGE_TCL_SGE_SET(x) (((uint32_t)(x) << SDXC_CQISGE_TCL_SGE_SHIFT) & SDXC_CQISGE_TCL_SGE_MASK)
#define SDXC_CQISGE_TCL_SGE_GET(x) (((uint32_t)(x) & SDXC_CQISGE_TCL_SGE_MASK) >> SDXC_CQISGE_TCL_SGE_SHIFT)

/*
 * RED_SGE (RW)
 *
 * 
 */
#define SDXC_CQISGE_RED_SGE_MASK (0x4U)
#define SDXC_CQISGE_RED_SGE_SHIFT (2U)
#define SDXC_CQISGE_RED_SGE_SET(x) (((uint32_t)(x) << SDXC_CQISGE_RED_SGE_SHIFT) & SDXC_CQISGE_RED_SGE_MASK)
#define SDXC_CQISGE_RED_SGE_GET(x) (((uint32_t)(x) & SDXC_CQISGE_RED_SGE_MASK) >> SDXC_CQISGE_RED_SGE_SHIFT)

/*
 * TCC_SGE (RW)
 *
 * 
 */
#define SDXC_CQISGE_TCC_SGE_MASK (0x2U)
#define SDXC_CQISGE_TCC_SGE_SHIFT (1U)
#define SDXC_CQISGE_TCC_SGE_SET(x) (((uint32_t)(x) << SDXC_CQISGE_TCC_SGE_SHIFT) & SDXC_CQISGE_TCC_SGE_MASK)
#define SDXC_CQISGE_TCC_SGE_GET(x) (((uint32_t)(x) & SDXC_CQISGE_TCC_SGE_MASK) >> SDXC_CQISGE_TCC_SGE_SHIFT)

/*
 * HAC_SGE (RW)
 *
 * 
 */
#define SDXC_CQISGE_HAC_SGE_MASK (0x1U)
#define SDXC_CQISGE_HAC_SGE_SHIFT (0U)
#define SDXC_CQISGE_HAC_SGE_SET(x) (((uint32_t)(x) << SDXC_CQISGE_HAC_SGE_SHIFT) & SDXC_CQISGE_HAC_SGE_MASK)
#define SDXC_CQISGE_HAC_SGE_GET(x) (((uint32_t)(x) & SDXC_CQISGE_HAC_SGE_MASK) >> SDXC_CQISGE_HAC_SGE_SHIFT)

/* Bitfield definition for register: CQIC */
/*
 * INTC_EN (RW)
 *
 * 
 */
#define SDXC_CQIC_INTC_EN_MASK (0x80000000UL)
#define SDXC_CQIC_INTC_EN_SHIFT (31U)
#define SDXC_CQIC_INTC_EN_SET(x) (((uint32_t)(x) << SDXC_CQIC_INTC_EN_SHIFT) & SDXC_CQIC_INTC_EN_MASK)
#define SDXC_CQIC_INTC_EN_GET(x) (((uint32_t)(x) & SDXC_CQIC_INTC_EN_MASK) >> SDXC_CQIC_INTC_EN_SHIFT)

/*
 * INTC_STAT (R)
 *
 * 
 */
#define SDXC_CQIC_INTC_STAT_MASK (0x100000UL)
#define SDXC_CQIC_INTC_STAT_SHIFT (20U)
#define SDXC_CQIC_INTC_STAT_GET(x) (((uint32_t)(x) & SDXC_CQIC_INTC_STAT_MASK) >> SDXC_CQIC_INTC_STAT_SHIFT)

/*
 * INTC_RST (W)
 *
 * 
 */
#define SDXC_CQIC_INTC_RST_MASK (0x10000UL)
#define SDXC_CQIC_INTC_RST_SHIFT (16U)
#define SDXC_CQIC_INTC_RST_SET(x) (((uint32_t)(x) << SDXC_CQIC_INTC_RST_SHIFT) & SDXC_CQIC_INTC_RST_MASK)
#define SDXC_CQIC_INTC_RST_GET(x) (((uint32_t)(x) & SDXC_CQIC_INTC_RST_MASK) >> SDXC_CQIC_INTC_RST_SHIFT)

/*
 * INTC_TH_WEN (W)
 *
 * 
 */
#define SDXC_CQIC_INTC_TH_WEN_MASK (0x8000U)
#define SDXC_CQIC_INTC_TH_WEN_SHIFT (15U)
#define SDXC_CQIC_INTC_TH_WEN_SET(x) (((uint32_t)(x) << SDXC_CQIC_INTC_TH_WEN_SHIFT) & SDXC_CQIC_INTC_TH_WEN_MASK)
#define SDXC_CQIC_INTC_TH_WEN_GET(x) (((uint32_t)(x) & SDXC_CQIC_INTC_TH_WEN_MASK) >> SDXC_CQIC_INTC_TH_WEN_SHIFT)

/*
 * INTC_TH (W)
 *
 * 
 */
#define SDXC_CQIC_INTC_TH_MASK (0x1F00U)
#define SDXC_CQIC_INTC_TH_SHIFT (8U)
#define SDXC_CQIC_INTC_TH_SET(x) (((uint32_t)(x) << SDXC_CQIC_INTC_TH_SHIFT) & SDXC_CQIC_INTC_TH_MASK)
#define SDXC_CQIC_INTC_TH_GET(x) (((uint32_t)(x) & SDXC_CQIC_INTC_TH_MASK) >> SDXC_CQIC_INTC_TH_SHIFT)

/*
 * TOUT_VAL_WEN (W)
 *
 * 
 */
#define SDXC_CQIC_TOUT_VAL_WEN_MASK (0x80U)
#define SDXC_CQIC_TOUT_VAL_WEN_SHIFT (7U)
#define SDXC_CQIC_TOUT_VAL_WEN_SET(x) (((uint32_t)(x) << SDXC_CQIC_TOUT_VAL_WEN_SHIFT) & SDXC_CQIC_TOUT_VAL_WEN_MASK)
#define SDXC_CQIC_TOUT_VAL_WEN_GET(x) (((uint32_t)(x) & SDXC_CQIC_TOUT_VAL_WEN_MASK) >> SDXC_CQIC_TOUT_VAL_WEN_SHIFT)

/*
 * TOUT_VAL (RW)
 *
 * 
 */
#define SDXC_CQIC_TOUT_VAL_MASK (0x7FU)
#define SDXC_CQIC_TOUT_VAL_SHIFT (0U)
#define SDXC_CQIC_TOUT_VAL_SET(x) (((uint32_t)(x) << SDXC_CQIC_TOUT_VAL_SHIFT) & SDXC_CQIC_TOUT_VAL_MASK)
#define SDXC_CQIC_TOUT_VAL_GET(x) (((uint32_t)(x) & SDXC_CQIC_TOUT_VAL_MASK) >> SDXC_CQIC_TOUT_VAL_SHIFT)

/* Bitfield definition for register: CQTDLBA */
/*
 * TDLBA (RW)
 *
 * 
 */
#define SDXC_CQTDLBA_TDLBA_MASK (0xFFFFFFFFUL)
#define SDXC_CQTDLBA_TDLBA_SHIFT (0U)
#define SDXC_CQTDLBA_TDLBA_SET(x) (((uint32_t)(x) << SDXC_CQTDLBA_TDLBA_SHIFT) & SDXC_CQTDLBA_TDLBA_MASK)
#define SDXC_CQTDLBA_TDLBA_GET(x) (((uint32_t)(x) & SDXC_CQTDLBA_TDLBA_MASK) >> SDXC_CQTDLBA_TDLBA_SHIFT)

/* Bitfield definition for register: CQTDBR */
/*
 * DBR (RW)
 *
 * 
 */
#define SDXC_CQTDBR_DBR_MASK (0xFFFFFFFFUL)
#define SDXC_CQTDBR_DBR_SHIFT (0U)
#define SDXC_CQTDBR_DBR_SET(x) (((uint32_t)(x) << SDXC_CQTDBR_DBR_SHIFT) & SDXC_CQTDBR_DBR_MASK)
#define SDXC_CQTDBR_DBR_GET(x) (((uint32_t)(x) & SDXC_CQTDBR_DBR_MASK) >> SDXC_CQTDBR_DBR_SHIFT)

/* Bitfield definition for register: CQTCN */
/*
 * TCN (RW)
 *
 * 
 */
#define SDXC_CQTCN_TCN_MASK (0xFFFFFFFFUL)
#define SDXC_CQTCN_TCN_SHIFT (0U)
#define SDXC_CQTCN_TCN_SET(x) (((uint32_t)(x) << SDXC_CQTCN_TCN_SHIFT) & SDXC_CQTCN_TCN_MASK)
#define SDXC_CQTCN_TCN_GET(x) (((uint32_t)(x) & SDXC_CQTCN_TCN_MASK) >> SDXC_CQTCN_TCN_SHIFT)

/* Bitfield definition for register: CQDQS */
/*
 * DQS (RW)
 *
 * 
 */
#define SDXC_CQDQS_DQS_MASK (0xFFFFFFFFUL)
#define SDXC_CQDQS_DQS_SHIFT (0U)
#define SDXC_CQDQS_DQS_SET(x) (((uint32_t)(x) << SDXC_CQDQS_DQS_SHIFT) & SDXC_CQDQS_DQS_MASK)
#define SDXC_CQDQS_DQS_GET(x) (((uint32_t)(x) & SDXC_CQDQS_DQS_MASK) >> SDXC_CQDQS_DQS_SHIFT)

/* Bitfield definition for register: CQDPT */
/*
 * DPT (RW)
 *
 * 
 */
#define SDXC_CQDPT_DPT_MASK (0xFFFFFFFFUL)
#define SDXC_CQDPT_DPT_SHIFT (0U)
#define SDXC_CQDPT_DPT_SET(x) (((uint32_t)(x) << SDXC_CQDPT_DPT_SHIFT) & SDXC_CQDPT_DPT_MASK)
#define SDXC_CQDPT_DPT_GET(x) (((uint32_t)(x) & SDXC_CQDPT_DPT_MASK) >> SDXC_CQDPT_DPT_SHIFT)

/* Bitfield definition for register: CQTCLR */
/*
 * TCLR (RW)
 *
 * 
 */
#define SDXC_CQTCLR_TCLR_MASK (0xFFFFFFFFUL)
#define SDXC_CQTCLR_TCLR_SHIFT (0U)
#define SDXC_CQTCLR_TCLR_SET(x) (((uint32_t)(x) << SDXC_CQTCLR_TCLR_SHIFT) & SDXC_CQTCLR_TCLR_MASK)
#define SDXC_CQTCLR_TCLR_GET(x) (((uint32_t)(x) & SDXC_CQTCLR_TCLR_MASK) >> SDXC_CQTCLR_TCLR_SHIFT)

/* Bitfield definition for register: CQSSC1 */
/*
 * SQSCMD_BLK_CNT (RW)
 *
 * 
 */
#define SDXC_CQSSC1_SQSCMD_BLK_CNT_MASK (0xF0000UL)
#define SDXC_CQSSC1_SQSCMD_BLK_CNT_SHIFT (16U)
#define SDXC_CQSSC1_SQSCMD_BLK_CNT_SET(x) (((uint32_t)(x) << SDXC_CQSSC1_SQSCMD_BLK_CNT_SHIFT) & SDXC_CQSSC1_SQSCMD_BLK_CNT_MASK)
#define SDXC_CQSSC1_SQSCMD_BLK_CNT_GET(x) (((uint32_t)(x) & SDXC_CQSSC1_SQSCMD_BLK_CNT_MASK) >> SDXC_CQSSC1_SQSCMD_BLK_CNT_SHIFT)

/*
 * SQSCMD_IDLE_TMR (RW)
 *
 * 
 */
#define SDXC_CQSSC1_SQSCMD_IDLE_TMR_MASK (0xFFFFU)
#define SDXC_CQSSC1_SQSCMD_IDLE_TMR_SHIFT (0U)
#define SDXC_CQSSC1_SQSCMD_IDLE_TMR_SET(x) (((uint32_t)(x) << SDXC_CQSSC1_SQSCMD_IDLE_TMR_SHIFT) & SDXC_CQSSC1_SQSCMD_IDLE_TMR_MASK)
#define SDXC_CQSSC1_SQSCMD_IDLE_TMR_GET(x) (((uint32_t)(x) & SDXC_CQSSC1_SQSCMD_IDLE_TMR_MASK) >> SDXC_CQSSC1_SQSCMD_IDLE_TMR_SHIFT)

/* Bitfield definition for register: CQSSC2 */
/*
 * SQSCMD_RCA (RW)
 *
 * 
 */
#define SDXC_CQSSC2_SQSCMD_RCA_MASK (0xFFFFU)
#define SDXC_CQSSC2_SQSCMD_RCA_SHIFT (0U)
#define SDXC_CQSSC2_SQSCMD_RCA_SET(x) (((uint32_t)(x) << SDXC_CQSSC2_SQSCMD_RCA_SHIFT) & SDXC_CQSSC2_SQSCMD_RCA_MASK)
#define SDXC_CQSSC2_SQSCMD_RCA_GET(x) (((uint32_t)(x) & SDXC_CQSSC2_SQSCMD_RCA_MASK) >> SDXC_CQSSC2_SQSCMD_RCA_SHIFT)

/* Bitfield definition for register: CQCRDCT */
/*
 * DCMD_RESP (R)
 *
 * 
 */
#define SDXC_CQCRDCT_DCMD_RESP_MASK (0xFFFFFFFFUL)
#define SDXC_CQCRDCT_DCMD_RESP_SHIFT (0U)
#define SDXC_CQCRDCT_DCMD_RESP_GET(x) (((uint32_t)(x) & SDXC_CQCRDCT_DCMD_RESP_MASK) >> SDXC_CQCRDCT_DCMD_RESP_SHIFT)

/* Bitfield definition for register: CQRMEM */
/*
 * RESP_ERR_MASK (RW)
 *
 * 
 */
#define SDXC_CQRMEM_RESP_ERR_MASK_MASK (0xFFFFFFFFUL)
#define SDXC_CQRMEM_RESP_ERR_MASK_SHIFT (0U)
#define SDXC_CQRMEM_RESP_ERR_MASK_SET(x) (((uint32_t)(x) << SDXC_CQRMEM_RESP_ERR_MASK_SHIFT) & SDXC_CQRMEM_RESP_ERR_MASK_MASK)
#define SDXC_CQRMEM_RESP_ERR_MASK_GET(x) (((uint32_t)(x) & SDXC_CQRMEM_RESP_ERR_MASK_MASK) >> SDXC_CQRMEM_RESP_ERR_MASK_SHIFT)

/* Bitfield definition for register: CQTERRI */
/*
 * TRANS_ERR_TASKID (R)
 *
 * 
 */
#define SDXC_CQTERRI_TRANS_ERR_TASKID_MASK (0x1F000000UL)
#define SDXC_CQTERRI_TRANS_ERR_TASKID_SHIFT (24U)
#define SDXC_CQTERRI_TRANS_ERR_TASKID_GET(x) (((uint32_t)(x) & SDXC_CQTERRI_TRANS_ERR_TASKID_MASK) >> SDXC_CQTERRI_TRANS_ERR_TASKID_SHIFT)

/*
 * TRANS_ERR_CMD_INDX (R)
 *
 * 
 */
#define SDXC_CQTERRI_TRANS_ERR_CMD_INDX_MASK (0x3F0000UL)
#define SDXC_CQTERRI_TRANS_ERR_CMD_INDX_SHIFT (16U)
#define SDXC_CQTERRI_TRANS_ERR_CMD_INDX_GET(x) (((uint32_t)(x) & SDXC_CQTERRI_TRANS_ERR_CMD_INDX_MASK) >> SDXC_CQTERRI_TRANS_ERR_CMD_INDX_SHIFT)

/*
 * RESP_ERR_FIELDS_VALID (R)
 *
 * 
 */
#define SDXC_CQTERRI_RESP_ERR_FIELDS_VALID_MASK (0x8000U)
#define SDXC_CQTERRI_RESP_ERR_FIELDS_VALID_SHIFT (15U)
#define SDXC_CQTERRI_RESP_ERR_FIELDS_VALID_GET(x) (((uint32_t)(x) & SDXC_CQTERRI_RESP_ERR_FIELDS_VALID_MASK) >> SDXC_CQTERRI_RESP_ERR_FIELDS_VALID_SHIFT)

/*
 * RESP_ERR_TASKID (R)
 *
 * 
 */
#define SDXC_CQTERRI_RESP_ERR_TASKID_MASK (0x1F00U)
#define SDXC_CQTERRI_RESP_ERR_TASKID_SHIFT (8U)
#define SDXC_CQTERRI_RESP_ERR_TASKID_GET(x) (((uint32_t)(x) & SDXC_CQTERRI_RESP_ERR_TASKID_MASK) >> SDXC_CQTERRI_RESP_ERR_TASKID_SHIFT)

/*
 * RESP_ERR_CMD_INDX (R)
 *
 * 
 */
#define SDXC_CQTERRI_RESP_ERR_CMD_INDX_MASK (0x3FU)
#define SDXC_CQTERRI_RESP_ERR_CMD_INDX_SHIFT (0U)
#define SDXC_CQTERRI_RESP_ERR_CMD_INDX_GET(x) (((uint32_t)(x) & SDXC_CQTERRI_RESP_ERR_CMD_INDX_MASK) >> SDXC_CQTERRI_RESP_ERR_CMD_INDX_SHIFT)

/* Bitfield definition for register: CQCRI */
/*
 * CMD_RESP_INDX (R)
 *
 * 
 */
#define SDXC_CQCRI_CMD_RESP_INDX_MASK (0x3FU)
#define SDXC_CQCRI_CMD_RESP_INDX_SHIFT (0U)
#define SDXC_CQCRI_CMD_RESP_INDX_GET(x) (((uint32_t)(x) & SDXC_CQCRI_CMD_RESP_INDX_MASK) >> SDXC_CQCRI_CMD_RESP_INDX_SHIFT)

/* Bitfield definition for register: CQCRA */
/*
 * CMD_RESP_ARG (R)
 *
 * 
 */
#define SDXC_CQCRA_CMD_RESP_ARG_MASK (0xFFFFFFFFUL)
#define SDXC_CQCRA_CMD_RESP_ARG_SHIFT (0U)
#define SDXC_CQCRA_CMD_RESP_ARG_GET(x) (((uint32_t)(x) & SDXC_CQCRA_CMD_RESP_ARG_MASK) >> SDXC_CQCRA_CMD_RESP_ARG_SHIFT)

/* Bitfield definition for register: MSHC_VER_ID */
/*
 * VER_ID (R)
 *
 * 
 */
#define SDXC_MSHC_VER_ID_VER_ID_MASK (0xFFFFFFFFUL)
#define SDXC_MSHC_VER_ID_VER_ID_SHIFT (0U)
#define SDXC_MSHC_VER_ID_VER_ID_GET(x) (((uint32_t)(x) & SDXC_MSHC_VER_ID_VER_ID_MASK) >> SDXC_MSHC_VER_ID_VER_ID_SHIFT)

/* Bitfield definition for register: MSHC_VER_TYPE */
/*
 * VER_TYPE (R)
 *
 * 
 */
#define SDXC_MSHC_VER_TYPE_VER_TYPE_MASK (0xFFFFFFFFUL)
#define SDXC_MSHC_VER_TYPE_VER_TYPE_SHIFT (0U)
#define SDXC_MSHC_VER_TYPE_VER_TYPE_GET(x) (((uint32_t)(x) & SDXC_MSHC_VER_TYPE_VER_TYPE_MASK) >> SDXC_MSHC_VER_TYPE_VER_TYPE_SHIFT)

/* Bitfield definition for register: MSHC_CTRL */
/*
 * NEDGE_SMPL_EN (RW)
 *
 * 
 */
#define SDXC_MSHC_CTRL_NEDGE_SMPL_EN_MASK (0x80U)
#define SDXC_MSHC_CTRL_NEDGE_SMPL_EN_SHIFT (7U)
#define SDXC_MSHC_CTRL_NEDGE_SMPL_EN_SET(x) (((uint32_t)(x) << SDXC_MSHC_CTRL_NEDGE_SMPL_EN_SHIFT) & SDXC_MSHC_CTRL_NEDGE_SMPL_EN_MASK)
#define SDXC_MSHC_CTRL_NEDGE_SMPL_EN_GET(x) (((uint32_t)(x) & SDXC_MSHC_CTRL_NEDGE_SMPL_EN_MASK) >> SDXC_MSHC_CTRL_NEDGE_SMPL_EN_SHIFT)

/*
 * PEDGE_DRV_EN (RW)
 *
 * 
 */
#define SDXC_MSHC_CTRL_PEDGE_DRV_EN_MASK (0x40U)
#define SDXC_MSHC_CTRL_PEDGE_DRV_EN_SHIFT (6U)
#define SDXC_MSHC_CTRL_PEDGE_DRV_EN_SET(x) (((uint32_t)(x) << SDXC_MSHC_CTRL_PEDGE_DRV_EN_SHIFT) & SDXC_MSHC_CTRL_PEDGE_DRV_EN_MASK)
#define SDXC_MSHC_CTRL_PEDGE_DRV_EN_GET(x) (((uint32_t)(x) & SDXC_MSHC_CTRL_PEDGE_DRV_EN_MASK) >> SDXC_MSHC_CTRL_PEDGE_DRV_EN_SHIFT)

/*
 * SW_CG_DIS (RW)
 *
 * 
 */
#define SDXC_MSHC_CTRL_SW_CG_DIS_MASK (0x10U)
#define SDXC_MSHC_CTRL_SW_CG_DIS_SHIFT (4U)
#define SDXC_MSHC_CTRL_SW_CG_DIS_SET(x) (((uint32_t)(x) << SDXC_MSHC_CTRL_SW_CG_DIS_SHIFT) & SDXC_MSHC_CTRL_SW_CG_DIS_MASK)
#define SDXC_MSHC_CTRL_SW_CG_DIS_GET(x) (((uint32_t)(x) & SDXC_MSHC_CTRL_SW_CG_DIS_MASK) >> SDXC_MSHC_CTRL_SW_CG_DIS_SHIFT)

/* Bitfield definition for register: MBIU_CTRL */
/*
 * BURST_INCR16_EN (RW)
 *
 * 
 */
#define SDXC_MBIU_CTRL_BURST_INCR16_EN_MASK (0x8U)
#define SDXC_MBIU_CTRL_BURST_INCR16_EN_SHIFT (3U)
#define SDXC_MBIU_CTRL_BURST_INCR16_EN_SET(x) (((uint32_t)(x) << SDXC_MBIU_CTRL_BURST_INCR16_EN_SHIFT) & SDXC_MBIU_CTRL_BURST_INCR16_EN_MASK)
#define SDXC_MBIU_CTRL_BURST_INCR16_EN_GET(x) (((uint32_t)(x) & SDXC_MBIU_CTRL_BURST_INCR16_EN_MASK) >> SDXC_MBIU_CTRL_BURST_INCR16_EN_SHIFT)

/*
 * BURST_INCR8_EN (RW)
 *
 * 
 */
#define SDXC_MBIU_CTRL_BURST_INCR8_EN_MASK (0x4U)
#define SDXC_MBIU_CTRL_BURST_INCR8_EN_SHIFT (2U)
#define SDXC_MBIU_CTRL_BURST_INCR8_EN_SET(x) (((uint32_t)(x) << SDXC_MBIU_CTRL_BURST_INCR8_EN_SHIFT) & SDXC_MBIU_CTRL_BURST_INCR8_EN_MASK)
#define SDXC_MBIU_CTRL_BURST_INCR8_EN_GET(x) (((uint32_t)(x) & SDXC_MBIU_CTRL_BURST_INCR8_EN_MASK) >> SDXC_MBIU_CTRL_BURST_INCR8_EN_SHIFT)

/*
 * BUSRT_INCR4_EN (RW)
 *
 * 
 */
#define SDXC_MBIU_CTRL_BUSRT_INCR4_EN_MASK (0x2U)
#define SDXC_MBIU_CTRL_BUSRT_INCR4_EN_SHIFT (1U)
#define SDXC_MBIU_CTRL_BUSRT_INCR4_EN_SET(x) (((uint32_t)(x) << SDXC_MBIU_CTRL_BUSRT_INCR4_EN_SHIFT) & SDXC_MBIU_CTRL_BUSRT_INCR4_EN_MASK)
#define SDXC_MBIU_CTRL_BUSRT_INCR4_EN_GET(x) (((uint32_t)(x) & SDXC_MBIU_CTRL_BUSRT_INCR4_EN_MASK) >> SDXC_MBIU_CTRL_BUSRT_INCR4_EN_SHIFT)

/*
 * UNDEFL_INCR_EN (RW)
 *
 * 
 */
#define SDXC_MBIU_CTRL_UNDEFL_INCR_EN_MASK (0x1U)
#define SDXC_MBIU_CTRL_UNDEFL_INCR_EN_SHIFT (0U)
#define SDXC_MBIU_CTRL_UNDEFL_INCR_EN_SET(x) (((uint32_t)(x) << SDXC_MBIU_CTRL_UNDEFL_INCR_EN_SHIFT) & SDXC_MBIU_CTRL_UNDEFL_INCR_EN_MASK)
#define SDXC_MBIU_CTRL_UNDEFL_INCR_EN_GET(x) (((uint32_t)(x) & SDXC_MBIU_CTRL_UNDEFL_INCR_EN_MASK) >> SDXC_MBIU_CTRL_UNDEFL_INCR_EN_SHIFT)

/* Bitfield definition for register: EMMC_BOOT_CTRL */
/*
 * BOOT_TOUT_CNT (RW)
 *
 * 
 */
#define SDXC_EMMC_BOOT_CTRL_BOOT_TOUT_CNT_MASK (0xF0000000UL)
#define SDXC_EMMC_BOOT_CTRL_BOOT_TOUT_CNT_SHIFT (28U)
#define SDXC_EMMC_BOOT_CTRL_BOOT_TOUT_CNT_SET(x) (((uint32_t)(x) << SDXC_EMMC_BOOT_CTRL_BOOT_TOUT_CNT_SHIFT) & SDXC_EMMC_BOOT_CTRL_BOOT_TOUT_CNT_MASK)
#define SDXC_EMMC_BOOT_CTRL_BOOT_TOUT_CNT_GET(x) (((uint32_t)(x) & SDXC_EMMC_BOOT_CTRL_BOOT_TOUT_CNT_MASK) >> SDXC_EMMC_BOOT_CTRL_BOOT_TOUT_CNT_SHIFT)

/*
 * BOOT_ACK_ENABLE (RW)
 *
 * 
 */
#define SDXC_EMMC_BOOT_CTRL_BOOT_ACK_ENABLE_MASK (0x1000000UL)
#define SDXC_EMMC_BOOT_CTRL_BOOT_ACK_ENABLE_SHIFT (24U)
#define SDXC_EMMC_BOOT_CTRL_BOOT_ACK_ENABLE_SET(x) (((uint32_t)(x) << SDXC_EMMC_BOOT_CTRL_BOOT_ACK_ENABLE_SHIFT) & SDXC_EMMC_BOOT_CTRL_BOOT_ACK_ENABLE_MASK)
#define SDXC_EMMC_BOOT_CTRL_BOOT_ACK_ENABLE_GET(x) (((uint32_t)(x) & SDXC_EMMC_BOOT_CTRL_BOOT_ACK_ENABLE_MASK) >> SDXC_EMMC_BOOT_CTRL_BOOT_ACK_ENABLE_SHIFT)

/*
 * VALIDATE_BOOT (W)
 *
 * 
 */
#define SDXC_EMMC_BOOT_CTRL_VALIDATE_BOOT_MASK (0x800000UL)
#define SDXC_EMMC_BOOT_CTRL_VALIDATE_BOOT_SHIFT (23U)
#define SDXC_EMMC_BOOT_CTRL_VALIDATE_BOOT_SET(x) (((uint32_t)(x) << SDXC_EMMC_BOOT_CTRL_VALIDATE_BOOT_SHIFT) & SDXC_EMMC_BOOT_CTRL_VALIDATE_BOOT_MASK)
#define SDXC_EMMC_BOOT_CTRL_VALIDATE_BOOT_GET(x) (((uint32_t)(x) & SDXC_EMMC_BOOT_CTRL_VALIDATE_BOOT_MASK) >> SDXC_EMMC_BOOT_CTRL_VALIDATE_BOOT_SHIFT)

/*
 * MAN_BOOT_EN (RW)
 *
 * 
 */
#define SDXC_EMMC_BOOT_CTRL_MAN_BOOT_EN_MASK (0x10000UL)
#define SDXC_EMMC_BOOT_CTRL_MAN_BOOT_EN_SHIFT (16U)
#define SDXC_EMMC_BOOT_CTRL_MAN_BOOT_EN_SET(x) (((uint32_t)(x) << SDXC_EMMC_BOOT_CTRL_MAN_BOOT_EN_SHIFT) & SDXC_EMMC_BOOT_CTRL_MAN_BOOT_EN_MASK)
#define SDXC_EMMC_BOOT_CTRL_MAN_BOOT_EN_GET(x) (((uint32_t)(x) & SDXC_EMMC_BOOT_CTRL_MAN_BOOT_EN_MASK) >> SDXC_EMMC_BOOT_CTRL_MAN_BOOT_EN_SHIFT)

/*
 * CQE_PREFETCH_DISABLE (RW)
 *
 * 
 */
#define SDXC_EMMC_BOOT_CTRL_CQE_PREFETCH_DISABLE_MASK (0x400U)
#define SDXC_EMMC_BOOT_CTRL_CQE_PREFETCH_DISABLE_SHIFT (10U)
#define SDXC_EMMC_BOOT_CTRL_CQE_PREFETCH_DISABLE_SET(x) (((uint32_t)(x) << SDXC_EMMC_BOOT_CTRL_CQE_PREFETCH_DISABLE_SHIFT) & SDXC_EMMC_BOOT_CTRL_CQE_PREFETCH_DISABLE_MASK)
#define SDXC_EMMC_BOOT_CTRL_CQE_PREFETCH_DISABLE_GET(x) (((uint32_t)(x) & SDXC_EMMC_BOOT_CTRL_CQE_PREFETCH_DISABLE_MASK) >> SDXC_EMMC_BOOT_CTRL_CQE_PREFETCH_DISABLE_SHIFT)

/*
 * CQE_ALGO_SEL (RW)
 *
 * 
 */
#define SDXC_EMMC_BOOT_CTRL_CQE_ALGO_SEL_MASK (0x200U)
#define SDXC_EMMC_BOOT_CTRL_CQE_ALGO_SEL_SHIFT (9U)
#define SDXC_EMMC_BOOT_CTRL_CQE_ALGO_SEL_SET(x) (((uint32_t)(x) << SDXC_EMMC_BOOT_CTRL_CQE_ALGO_SEL_SHIFT) & SDXC_EMMC_BOOT_CTRL_CQE_ALGO_SEL_MASK)
#define SDXC_EMMC_BOOT_CTRL_CQE_ALGO_SEL_GET(x) (((uint32_t)(x) & SDXC_EMMC_BOOT_CTRL_CQE_ALGO_SEL_MASK) >> SDXC_EMMC_BOOT_CTRL_CQE_ALGO_SEL_SHIFT)

/*
 * ENH_STROBE_ENABLE (RW)
 *
 * 
 */
#define SDXC_EMMC_BOOT_CTRL_ENH_STROBE_ENABLE_MASK (0x100U)
#define SDXC_EMMC_BOOT_CTRL_ENH_STROBE_ENABLE_SHIFT (8U)
#define SDXC_EMMC_BOOT_CTRL_ENH_STROBE_ENABLE_SET(x) (((uint32_t)(x) << SDXC_EMMC_BOOT_CTRL_ENH_STROBE_ENABLE_SHIFT) & SDXC_EMMC_BOOT_CTRL_ENH_STROBE_ENABLE_MASK)
#define SDXC_EMMC_BOOT_CTRL_ENH_STROBE_ENABLE_GET(x) (((uint32_t)(x) & SDXC_EMMC_BOOT_CTRL_ENH_STROBE_ENABLE_MASK) >> SDXC_EMMC_BOOT_CTRL_ENH_STROBE_ENABLE_SHIFT)

/*
 * EMMC_RST_N_OE (RW)
 *
 * 
 */
#define SDXC_EMMC_BOOT_CTRL_EMMC_RST_N_OE_MASK (0x8U)
#define SDXC_EMMC_BOOT_CTRL_EMMC_RST_N_OE_SHIFT (3U)
#define SDXC_EMMC_BOOT_CTRL_EMMC_RST_N_OE_SET(x) (((uint32_t)(x) << SDXC_EMMC_BOOT_CTRL_EMMC_RST_N_OE_SHIFT) & SDXC_EMMC_BOOT_CTRL_EMMC_RST_N_OE_MASK)
#define SDXC_EMMC_BOOT_CTRL_EMMC_RST_N_OE_GET(x) (((uint32_t)(x) & SDXC_EMMC_BOOT_CTRL_EMMC_RST_N_OE_MASK) >> SDXC_EMMC_BOOT_CTRL_EMMC_RST_N_OE_SHIFT)

/*
 * EMMC_RST_N (RW)
 *
 * 
 */
#define SDXC_EMMC_BOOT_CTRL_EMMC_RST_N_MASK (0x4U)
#define SDXC_EMMC_BOOT_CTRL_EMMC_RST_N_SHIFT (2U)
#define SDXC_EMMC_BOOT_CTRL_EMMC_RST_N_SET(x) (((uint32_t)(x) << SDXC_EMMC_BOOT_CTRL_EMMC_RST_N_SHIFT) & SDXC_EMMC_BOOT_CTRL_EMMC_RST_N_MASK)
#define SDXC_EMMC_BOOT_CTRL_EMMC_RST_N_GET(x) (((uint32_t)(x) & SDXC_EMMC_BOOT_CTRL_EMMC_RST_N_MASK) >> SDXC_EMMC_BOOT_CTRL_EMMC_RST_N_SHIFT)

/*
 * DISABLE_DATA_CRC_CHK (RW)
 *
 * 
 */
#define SDXC_EMMC_BOOT_CTRL_DISABLE_DATA_CRC_CHK_MASK (0x2U)
#define SDXC_EMMC_BOOT_CTRL_DISABLE_DATA_CRC_CHK_SHIFT (1U)
#define SDXC_EMMC_BOOT_CTRL_DISABLE_DATA_CRC_CHK_SET(x) (((uint32_t)(x) << SDXC_EMMC_BOOT_CTRL_DISABLE_DATA_CRC_CHK_SHIFT) & SDXC_EMMC_BOOT_CTRL_DISABLE_DATA_CRC_CHK_MASK)
#define SDXC_EMMC_BOOT_CTRL_DISABLE_DATA_CRC_CHK_GET(x) (((uint32_t)(x) & SDXC_EMMC_BOOT_CTRL_DISABLE_DATA_CRC_CHK_MASK) >> SDXC_EMMC_BOOT_CTRL_DISABLE_DATA_CRC_CHK_SHIFT)

/*
 * CARD_IS_EMMC (RW)
 *
 * 
 */
#define SDXC_EMMC_BOOT_CTRL_CARD_IS_EMMC_MASK (0x1U)
#define SDXC_EMMC_BOOT_CTRL_CARD_IS_EMMC_SHIFT (0U)
#define SDXC_EMMC_BOOT_CTRL_CARD_IS_EMMC_SET(x) (((uint32_t)(x) << SDXC_EMMC_BOOT_CTRL_CARD_IS_EMMC_SHIFT) & SDXC_EMMC_BOOT_CTRL_CARD_IS_EMMC_MASK)
#define SDXC_EMMC_BOOT_CTRL_CARD_IS_EMMC_GET(x) (((uint32_t)(x) & SDXC_EMMC_BOOT_CTRL_CARD_IS_EMMC_MASK) >> SDXC_EMMC_BOOT_CTRL_CARD_IS_EMMC_SHIFT)

/* Bitfield definition for register: AUTO_TUNING_CTRL */
/*
 * SWIN_TH_VAL (RW)
 *
 * 
 */
#define SDXC_AUTO_TUNING_CTRL_SWIN_TH_VAL_MASK (0x7F000000UL)
#define SDXC_AUTO_TUNING_CTRL_SWIN_TH_VAL_SHIFT (24U)
#define SDXC_AUTO_TUNING_CTRL_SWIN_TH_VAL_SET(x) (((uint32_t)(x) << SDXC_AUTO_TUNING_CTRL_SWIN_TH_VAL_SHIFT) & SDXC_AUTO_TUNING_CTRL_SWIN_TH_VAL_MASK)
#define SDXC_AUTO_TUNING_CTRL_SWIN_TH_VAL_GET(x) (((uint32_t)(x) & SDXC_AUTO_TUNING_CTRL_SWIN_TH_VAL_MASK) >> SDXC_AUTO_TUNING_CTRL_SWIN_TH_VAL_SHIFT)

/*
 * POST_CHANGE_DLY (RW)
 *
 * 
 */
#define SDXC_AUTO_TUNING_CTRL_POST_CHANGE_DLY_MASK (0x180000UL)
#define SDXC_AUTO_TUNING_CTRL_POST_CHANGE_DLY_SHIFT (19U)
#define SDXC_AUTO_TUNING_CTRL_POST_CHANGE_DLY_SET(x) (((uint32_t)(x) << SDXC_AUTO_TUNING_CTRL_POST_CHANGE_DLY_SHIFT) & SDXC_AUTO_TUNING_CTRL_POST_CHANGE_DLY_MASK)
#define SDXC_AUTO_TUNING_CTRL_POST_CHANGE_DLY_GET(x) (((uint32_t)(x) & SDXC_AUTO_TUNING_CTRL_POST_CHANGE_DLY_MASK) >> SDXC_AUTO_TUNING_CTRL_POST_CHANGE_DLY_SHIFT)

/*
 * PRE_CHANGE_DLY (RW)
 *
 * 
 */
#define SDXC_AUTO_TUNING_CTRL_PRE_CHANGE_DLY_MASK (0x60000UL)
#define SDXC_AUTO_TUNING_CTRL_PRE_CHANGE_DLY_SHIFT (17U)
#define SDXC_AUTO_TUNING_CTRL_PRE_CHANGE_DLY_SET(x) (((uint32_t)(x) << SDXC_AUTO_TUNING_CTRL_PRE_CHANGE_DLY_SHIFT) & SDXC_AUTO_TUNING_CTRL_PRE_CHANGE_DLY_MASK)
#define SDXC_AUTO_TUNING_CTRL_PRE_CHANGE_DLY_GET(x) (((uint32_t)(x) & SDXC_AUTO_TUNING_CTRL_PRE_CHANGE_DLY_MASK) >> SDXC_AUTO_TUNING_CTRL_PRE_CHANGE_DLY_SHIFT)

/*
 * TUNE_CLK_STOP_EN (RW)
 *
 * 
 */
#define SDXC_AUTO_TUNING_CTRL_TUNE_CLK_STOP_EN_MASK (0x10000UL)
#define SDXC_AUTO_TUNING_CTRL_TUNE_CLK_STOP_EN_SHIFT (16U)
#define SDXC_AUTO_TUNING_CTRL_TUNE_CLK_STOP_EN_SET(x) (((uint32_t)(x) << SDXC_AUTO_TUNING_CTRL_TUNE_CLK_STOP_EN_SHIFT) & SDXC_AUTO_TUNING_CTRL_TUNE_CLK_STOP_EN_MASK)
#define SDXC_AUTO_TUNING_CTRL_TUNE_CLK_STOP_EN_GET(x) (((uint32_t)(x) & SDXC_AUTO_TUNING_CTRL_TUNE_CLK_STOP_EN_MASK) >> SDXC_AUTO_TUNING_CTRL_TUNE_CLK_STOP_EN_SHIFT)

/*
 * WIN_EDGE_SEL (RW)
 *
 * 
 */
#define SDXC_AUTO_TUNING_CTRL_WIN_EDGE_SEL_MASK (0xF00U)
#define SDXC_AUTO_TUNING_CTRL_WIN_EDGE_SEL_SHIFT (8U)
#define SDXC_AUTO_TUNING_CTRL_WIN_EDGE_SEL_SET(x) (((uint32_t)(x) << SDXC_AUTO_TUNING_CTRL_WIN_EDGE_SEL_SHIFT) & SDXC_AUTO_TUNING_CTRL_WIN_EDGE_SEL_MASK)
#define SDXC_AUTO_TUNING_CTRL_WIN_EDGE_SEL_GET(x) (((uint32_t)(x) & SDXC_AUTO_TUNING_CTRL_WIN_EDGE_SEL_MASK) >> SDXC_AUTO_TUNING_CTRL_WIN_EDGE_SEL_SHIFT)

/*
 * SW_TUNE_EN (RW)
 *
 * 
 */
#define SDXC_AUTO_TUNING_CTRL_SW_TUNE_EN_MASK (0x10U)
#define SDXC_AUTO_TUNING_CTRL_SW_TUNE_EN_SHIFT (4U)
#define SDXC_AUTO_TUNING_CTRL_SW_TUNE_EN_SET(x) (((uint32_t)(x) << SDXC_AUTO_TUNING_CTRL_SW_TUNE_EN_SHIFT) & SDXC_AUTO_TUNING_CTRL_SW_TUNE_EN_MASK)
#define SDXC_AUTO_TUNING_CTRL_SW_TUNE_EN_GET(x) (((uint32_t)(x) & SDXC_AUTO_TUNING_CTRL_SW_TUNE_EN_MASK) >> SDXC_AUTO_TUNING_CTRL_SW_TUNE_EN_SHIFT)

/*
 * RPT_TUNE_ERR (RW)
 *
 * 
 */
#define SDXC_AUTO_TUNING_CTRL_RPT_TUNE_ERR_MASK (0x8U)
#define SDXC_AUTO_TUNING_CTRL_RPT_TUNE_ERR_SHIFT (3U)
#define SDXC_AUTO_TUNING_CTRL_RPT_TUNE_ERR_SET(x) (((uint32_t)(x) << SDXC_AUTO_TUNING_CTRL_RPT_TUNE_ERR_SHIFT) & SDXC_AUTO_TUNING_CTRL_RPT_TUNE_ERR_MASK)
#define SDXC_AUTO_TUNING_CTRL_RPT_TUNE_ERR_GET(x) (((uint32_t)(x) & SDXC_AUTO_TUNING_CTRL_RPT_TUNE_ERR_MASK) >> SDXC_AUTO_TUNING_CTRL_RPT_TUNE_ERR_SHIFT)

/*
 * SWIN_TH_EN (RW)
 *
 * 
 */
#define SDXC_AUTO_TUNING_CTRL_SWIN_TH_EN_MASK (0x4U)
#define SDXC_AUTO_TUNING_CTRL_SWIN_TH_EN_SHIFT (2U)
#define SDXC_AUTO_TUNING_CTRL_SWIN_TH_EN_SET(x) (((uint32_t)(x) << SDXC_AUTO_TUNING_CTRL_SWIN_TH_EN_SHIFT) & SDXC_AUTO_TUNING_CTRL_SWIN_TH_EN_MASK)
#define SDXC_AUTO_TUNING_CTRL_SWIN_TH_EN_GET(x) (((uint32_t)(x) & SDXC_AUTO_TUNING_CTRL_SWIN_TH_EN_MASK) >> SDXC_AUTO_TUNING_CTRL_SWIN_TH_EN_SHIFT)

/*
 * CI_SEL (RW)
 *
 * 
 */
#define SDXC_AUTO_TUNING_CTRL_CI_SEL_MASK (0x2U)
#define SDXC_AUTO_TUNING_CTRL_CI_SEL_SHIFT (1U)
#define SDXC_AUTO_TUNING_CTRL_CI_SEL_SET(x) (((uint32_t)(x) << SDXC_AUTO_TUNING_CTRL_CI_SEL_SHIFT) & SDXC_AUTO_TUNING_CTRL_CI_SEL_MASK)
#define SDXC_AUTO_TUNING_CTRL_CI_SEL_GET(x) (((uint32_t)(x) & SDXC_AUTO_TUNING_CTRL_CI_SEL_MASK) >> SDXC_AUTO_TUNING_CTRL_CI_SEL_SHIFT)

/*
 * AT_EN (RW)
 *
 * 
 */
#define SDXC_AUTO_TUNING_CTRL_AT_EN_MASK (0x1U)
#define SDXC_AUTO_TUNING_CTRL_AT_EN_SHIFT (0U)
#define SDXC_AUTO_TUNING_CTRL_AT_EN_SET(x) (((uint32_t)(x) << SDXC_AUTO_TUNING_CTRL_AT_EN_SHIFT) & SDXC_AUTO_TUNING_CTRL_AT_EN_MASK)
#define SDXC_AUTO_TUNING_CTRL_AT_EN_GET(x) (((uint32_t)(x) & SDXC_AUTO_TUNING_CTRL_AT_EN_MASK) >> SDXC_AUTO_TUNING_CTRL_AT_EN_SHIFT)

/* Bitfield definition for register: AUTO_TUNING_STAT */
/*
 * L_EDGE_PH_CODE (R)
 *
 * 
 */
#define SDXC_AUTO_TUNING_STAT_L_EDGE_PH_CODE_MASK (0xFF0000UL)
#define SDXC_AUTO_TUNING_STAT_L_EDGE_PH_CODE_SHIFT (16U)
#define SDXC_AUTO_TUNING_STAT_L_EDGE_PH_CODE_GET(x) (((uint32_t)(x) & SDXC_AUTO_TUNING_STAT_L_EDGE_PH_CODE_MASK) >> SDXC_AUTO_TUNING_STAT_L_EDGE_PH_CODE_SHIFT)

/*
 * R_EDGE_PH_CODE (R)
 *
 * 
 */
#define SDXC_AUTO_TUNING_STAT_R_EDGE_PH_CODE_MASK (0xFF00U)
#define SDXC_AUTO_TUNING_STAT_R_EDGE_PH_CODE_SHIFT (8U)
#define SDXC_AUTO_TUNING_STAT_R_EDGE_PH_CODE_GET(x) (((uint32_t)(x) & SDXC_AUTO_TUNING_STAT_R_EDGE_PH_CODE_MASK) >> SDXC_AUTO_TUNING_STAT_R_EDGE_PH_CODE_SHIFT)

/*
 * CENTER_PH_CODE (RW)
 *
 * 
 */
#define SDXC_AUTO_TUNING_STAT_CENTER_PH_CODE_MASK (0xFFU)
#define SDXC_AUTO_TUNING_STAT_CENTER_PH_CODE_SHIFT (0U)
#define SDXC_AUTO_TUNING_STAT_CENTER_PH_CODE_SET(x) (((uint32_t)(x) << SDXC_AUTO_TUNING_STAT_CENTER_PH_CODE_SHIFT) & SDXC_AUTO_TUNING_STAT_CENTER_PH_CODE_MASK)
#define SDXC_AUTO_TUNING_STAT_CENTER_PH_CODE_GET(x) (((uint32_t)(x) & SDXC_AUTO_TUNING_STAT_CENTER_PH_CODE_MASK) >> SDXC_AUTO_TUNING_STAT_CENTER_PH_CODE_SHIFT)

/* Bitfield definition for register: EMBEDDED_CTRL */
/*
 * BACK_END_PWR_CTRL (RW)
 *
 * 
 */
#define SDXC_EMBEDDED_CTRL_BACK_END_PWR_CTRL_MASK (0x7F000000UL)
#define SDXC_EMBEDDED_CTRL_BACK_END_PWR_CTRL_SHIFT (24U)
#define SDXC_EMBEDDED_CTRL_BACK_END_PWR_CTRL_SET(x) (((uint32_t)(x) << SDXC_EMBEDDED_CTRL_BACK_END_PWR_CTRL_SHIFT) & SDXC_EMBEDDED_CTRL_BACK_END_PWR_CTRL_MASK)
#define SDXC_EMBEDDED_CTRL_BACK_END_PWR_CTRL_GET(x) (((uint32_t)(x) & SDXC_EMBEDDED_CTRL_BACK_END_PWR_CTRL_MASK) >> SDXC_EMBEDDED_CTRL_BACK_END_PWR_CTRL_SHIFT)

/*
 * INT_PIN_SEL (RW)
 *
 * 
 */
#define SDXC_EMBEDDED_CTRL_INT_PIN_SEL_MASK (0x700000UL)
#define SDXC_EMBEDDED_CTRL_INT_PIN_SEL_SHIFT (20U)
#define SDXC_EMBEDDED_CTRL_INT_PIN_SEL_SET(x) (((uint32_t)(x) << SDXC_EMBEDDED_CTRL_INT_PIN_SEL_SHIFT) & SDXC_EMBEDDED_CTRL_INT_PIN_SEL_MASK)
#define SDXC_EMBEDDED_CTRL_INT_PIN_SEL_GET(x) (((uint32_t)(x) & SDXC_EMBEDDED_CTRL_INT_PIN_SEL_MASK) >> SDXC_EMBEDDED_CTRL_INT_PIN_SEL_SHIFT)

/*
 * CLK_PIN_SEL (RW)
 *
 * 
 */
#define SDXC_EMBEDDED_CTRL_CLK_PIN_SEL_MASK (0x70000UL)
#define SDXC_EMBEDDED_CTRL_CLK_PIN_SEL_SHIFT (16U)
#define SDXC_EMBEDDED_CTRL_CLK_PIN_SEL_SET(x) (((uint32_t)(x) << SDXC_EMBEDDED_CTRL_CLK_PIN_SEL_SHIFT) & SDXC_EMBEDDED_CTRL_CLK_PIN_SEL_MASK)
#define SDXC_EMBEDDED_CTRL_CLK_PIN_SEL_GET(x) (((uint32_t)(x) & SDXC_EMBEDDED_CTRL_CLK_PIN_SEL_MASK) >> SDXC_EMBEDDED_CTRL_CLK_PIN_SEL_SHIFT)

/*
 * BUS_WIDTH_PRESET (R)
 *
 * 
 */
#define SDXC_EMBEDDED_CTRL_BUS_WIDTH_PRESET_MASK (0x7F00U)
#define SDXC_EMBEDDED_CTRL_BUS_WIDTH_PRESET_SHIFT (8U)
#define SDXC_EMBEDDED_CTRL_BUS_WIDTH_PRESET_GET(x) (((uint32_t)(x) & SDXC_EMBEDDED_CTRL_BUS_WIDTH_PRESET_MASK) >> SDXC_EMBEDDED_CTRL_BUS_WIDTH_PRESET_SHIFT)

/*
 * NUM_INT_PIN (R)
 *
 * 
 */
#define SDXC_EMBEDDED_CTRL_NUM_INT_PIN_MASK (0x30U)
#define SDXC_EMBEDDED_CTRL_NUM_INT_PIN_SHIFT (4U)
#define SDXC_EMBEDDED_CTRL_NUM_INT_PIN_GET(x) (((uint32_t)(x) & SDXC_EMBEDDED_CTRL_NUM_INT_PIN_MASK) >> SDXC_EMBEDDED_CTRL_NUM_INT_PIN_SHIFT)

/*
 * NUM_CLK_PIN (R)
 *
 * 
 */
#define SDXC_EMBEDDED_CTRL_NUM_CLK_PIN_MASK (0x7U)
#define SDXC_EMBEDDED_CTRL_NUM_CLK_PIN_SHIFT (0U)
#define SDXC_EMBEDDED_CTRL_NUM_CLK_PIN_GET(x) (((uint32_t)(x) & SDXC_EMBEDDED_CTRL_NUM_CLK_PIN_MASK) >> SDXC_EMBEDDED_CTRL_NUM_CLK_PIN_SHIFT)



/* RESP register group index macro definition */
#define SDXC_RESP_RESP01 (0UL)
#define SDXC_RESP_RESP23 (1UL)
#define SDXC_RESP_RESP45 (2UL)
#define SDXC_RESP_RESP67 (3UL)

/* PRESET register group index macro definition */
#define SDXC_PRESET_INIT (0UL)
#define SDXC_PRESET_DS (1UL)
#define SDXC_PRESET_HS (2UL)
#define SDXC_PRESET_SDR12 (3UL)
#define SDXC_PRESET_SDR25 (4UL)
#define SDXC_PRESET_SDR50 (5UL)
#define SDXC_PRESET_SDR104 (6UL)
#define SDXC_PRESET_DDR50 (7UL)
#define SDXC_PRESET_UHS2 (10UL)


#endif /* HPM_SDXC_H */