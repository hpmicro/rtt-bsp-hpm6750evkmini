/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_ROMAPI_XPI_DEF_H
#define HPM_ROMAPI_XPI_DEF_H


#include "hpm_common.h"

/* For compatibility */
typedef uint32_t XPI_Type;

/**
 * @brief XPI Read Sample Clock source definitions
 */
typedef enum
{
    xpi_rxclksrc_internal_loopback = 0, /*!< Internal loopback */
    xpi_rxclksrc_dqs_loopback = 1,      /*!< Loopback from DQS pad */
    xpi_rxclksrc_external_dqs = 3,      /*!< Read is driven by External DQS pad */
}xpi_rxclksrc_type_t;


/**
 * @brief XPI pad definitions
 */
#define XPI_1PAD    (0U)
#define XPI_2PADS   (1U)
#define XPI_4PADS   (2U)
#define XPI_8PADS   (3U)

typedef enum
{
    xpi_data_pads_single,
    xpi_data_pads_dual,
    xpi_data_pads_quad,
    xpi_data_pads_octal,
}xpi_data_pad_t;

typedef enum
{
    xpi_io_1st_group,
    xpi_io_2nd_group,
}xpi_io_group_t;

/**
 * @brief XPI Port type definitions
 */
typedef enum
{
    xpi_xfer_port_a1,                    /*!< The address is based on the device connected to PORT A1 */
    xpi_xfer_port_a2,                    /*!< The address is based on the device connected to PORT A2 */
    xpi_xfer_port_b1,                    /*!< The address is based on the device connected to PORT B1 */
    xpi_xfer_port_b2,                    /*!< The address is based on the device connected to PORT B2 */
    xpi_xfer_port_auto,                  /*!< The port is auto determined based on the address and CR0 configuration */
    xpi_xfer_port_auto_parallel_mode,    /*!< The port is auto determined based on the address and CR0 configuration in parallel mode */
}xpi_xfer_port_t;

typedef enum
{
    xpi_port_a1,
    xpi_port_a2,
    xpi_port_b1,
    xpi_port_b2,
}xpi_port_t;

/**
 * @brief XPI APB Error type definitions
 */
enum
{
    xpi_apb_error_type_jump_on_cs,
    xpi_apb_error_type_unknown_inst,
    xpi_apb_error_type_sdr_dummy_in_ddr_seq,
    xpi_apb_error_type_ddr_dummy_in_sdr_seq,
    xpi_apb_error_type_exceed_addr_range,
    xpi_apb_error_type_seq_timeout,
    xpi_apb_error_type_cross_boundary,
};

/**
 * XPI APB Transfer type
 */
typedef enum
{
    xpi_apb_xfer_type_cmd,
    xpi_apb_xfer_type_config,
    xpi_apb_xfer_type_read,
    xpi_apb_xfer_type_write,
}xpi_apb_xfer_type_t;

/**
 * @brief XPI Xfer Mode
 */
typedef enum
{
    xpi_xfer_mode_polling,
    xpi_xfer_mode_dma,
    xpi_xfer_mode_interrupt,
}xpi_xfer_mode_t;

/**
 * @brief XPI Xfer context
 */
typedef struct
{
    uint32_t addr;
    uint8_t port;
    uint8_t cmd_type;
    uint8_t seq_idx;
    uint8_t seq_num;
    uint32_t *buf;
    uint32_t xfer_size;
}xpi_xfer_ctx_t;


typedef struct
{
    uint32_t entry[4];
}xpi_instr_seq_t;

/**
 * @brief XPI INSTRUCTION Set
 */
#define XPI_PHASE_STOP            (0x00U)
#define XPI_PHASE_CMD_SDR         (0x01U)
#define XPI_PHASE_RADDR_SDR       (0x02U)
#define XPI_PHASE_CADDR_SDR       (0x03U)
#define XPI_PHASE_MODE4_SDR       (0x06U)
#define XPI_PHASE_MODE8_SDR       (0x07U)
#define XPI_PHASE_WRITE_SDR       (0x08U)
#define XPI_PHASE_READ_SDR        (0x09U)
#define XPI_PHASE_DUMMY_SDR       (0X0CU)
#define XPI_PHASE_DUMMY_RWDS_SDR  (0x0DU)

#define XPI_PHASE_JUMP_ON_CS      (0x1FU)

#define XPI_PHASE_CMD_DDR         (0x21U)
#define XPI_PHASE_RADDR_DDR       (0x22U)
#define XPI_PHASE_CADDR_DDR       (0x23U)
#define XPI_PHASE_MODE4_DDR       (0x26U)
#define XPI_PHASE_MODE8_DDR       (0x27U)
#define XPI_PHASE_WRITE_DDR       (0x28U)
#define XPI_PHASE_READ_DDR        (0x29U)
#define XPI_PHASE_DUMMY_DDR       (0x2CU)
#define XPI_PHASE_DUMMY_RWDS_DDR  (0x2DU)

enum
{
    status_xpi_apb_jump_on_cs = MAKE_STATUS(status_group_xpi, 1),
    status_xpi_apb_unknown_inst = MAKE_STATUS(status_group_xpi, 2),
    status_xpi_apb_dummy_sdr_in_ddr_seq = MAKE_STATUS(status_group_xpi, 3),
    status_xpi_apb_dummy_ddr_in_sdr_seq = MAKE_STATUS(status_group_xpi, 4),
    status_xpi_apb_exceed_addr_range = MAKE_STATUS(status_group_xpi, 5),
    status_xpi_apb_seq_timeout = MAKE_STATUS(status_group_xpi, 6),
    status_xpi_apb_cross_boundary = MAKE_STATUS(status_group_xpi, 7),
};

enum
{
    xpi_dll_half_cycle = 0xFU,
    xpi_dll_quarter_cycle = 0x7U,
    xpi_dll_sdr_default_cycle = xpi_dll_half_cycle,
    xpi_dll_ddr_default_cycle = xpi_dll_quarter_cycle,
};


typedef struct
{
    uint8_t rxclk_src;                      /* Offset: 0x00 */
    uint8_t reserved0[7];                   /* Offset: 0x01 */
    uint8_t tx_watermark_in_dwords;         /* Offset: 0x08 */
    uint8_t rx_watermark_in_dwords;         /* Offset: 0x09 */
    uint8_t enable_differential_clk;        /* Offset: 0x0a */
    uint8_t reserved1[5];                   /* Offset: 0x0b */
    uint32_t access_flags;                  /* Offset: 0x10 */
}xpi_config_t;

typedef struct
{
    uint32_t size_in_kbytes;
    uint32_t serial_root_clk_freq;

    uint8_t enable_write_mask;
    uint8_t data_valid_time;    /*!< Unit 0.1ns */
    uint8_t reserved0[2];

    uint8_t cs_hold_time;
    uint8_t cs_setup_time;
    uint16_t cs_interval;

    uint8_t reserved1;
    uint8_t column_addr_size;
    uint8_t enable_word_address;
    uint8_t dly_target;

    uint8_t ahb_write_seq_idx;
    uint8_t ahb_write_seq_num;
    uint8_t ahb_read_seq_idx;
    uint8_t ahb_read_seq_num;

    uint8_t ahb_write_wait_interval;
    uint8_t ahb_write_wait_unit;
    uint8_t reserved2[2];
} xpi_device_config_t;


#define SUB_INSTR(phase,pad,op) ((uint32_t)(((uint16_t)(phase)<<10) | ((uint16_t)(pad)<<8) | ((uint16_t)(op))))
/**
 * @brief Generate a single word INSTRUCTION sequence word
 * @note  Here intentionally use the MACRO because when the arguments are constant value, the compiler
 *        can generate the const entry word during pre-processing
 */
#define XPI_INSTR_SEQ(phase0,pad0,op0,phase1,pad1,op1) (SUB_INSTR(phase0,pad0,op0) | (SUB_INSTR(phase1,pad1,op1)<<16))

#endif /* HPM_ROMAPI_XPI_DEF_H */
