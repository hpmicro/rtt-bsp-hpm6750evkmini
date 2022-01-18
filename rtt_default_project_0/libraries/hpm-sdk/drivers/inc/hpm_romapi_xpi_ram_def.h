#ifndef HPM_ROMAPI_XPI_RAM_DRV_H
#define HPM_ROMAPI_XPI_RAM_DRV_H
#include "hpm_common.h"
#include "hpm_romapi_xpi_def.h"

/**********************************************************************************************************************
 * Definitions
 *********************************************************************************************************************/

#define XPI_RAM_CFG_OPTION_TAG (0xfcf91U)
#define XPI_RAM_CFG_TAG (0x4D415258U)

enum {
    xpi_ram_safe_clk_freq = 1,
};

/**
 * @brief XPI NOR configuration option
 *        The ROM SW can detect the FLASH configuration based on the following structure specified by the end-user
 */
typedef struct {
    union {
        struct {
            uint32_t words: 4;       /*!< Option words, exclude the header itself */
            uint32_t instance: 4;    /*!< 0 - Instance 0, 1 - Instance 1 */
            uint32_t reserved: 4;    /*!< Reserved for future use */
            uint32_t tag: 20;        /*!< Must be 0xfcf91 */
        };
        uint32_t U;
    } header;
    union {
        struct {
            uint32_t freq_opt: 4;                /*!< 1 - 30MHz, others, SoC specific setting */
            uint32_t misc: 4;                    /*!< Not used for now */
            uint32_t ram_size : 8;               /*!< 0 - Auto detected, others - User specified size in MB */
            uint32_t pin_group: 4;               /*!< Pin group, 0 - 1st group, 1 - 2nd group */
            uint32_t read_dummy_cycles: 4;       /*!< Dummy cycyles for read command, 0 - default, 1 - user specified value  */
            uint32_t write_dummy_cycles:4;       /*!< Dummy cycyles for write command, 0 - default, 1 - user specified value  */
            uint32_t probe_type: 4;              /*!< 0 - HyperRAM 1 - APMemory X8 devices */
        };
        uint32_t U;
    } option0;
    union {
        struct {
            uint32_t drive_strength: 4;
            uint32_t max_cs_low_time: 4;
            uint32_t pin_group_sel: 4;
            uint32_t port: 4;
            uint32_t skip_ahb_buf_cfg:4;
            uint32_t reserved: 12;
        };
        uint32_t U;
    } option1;
} xpi_ram_config_option_t;


enum
{
    xpi_ram_type_apmemory_x8 = 0,
    xpi_ram_type_hyperram = 1,
    xpi_ram_type_apmemory_x4 = 2,
};

enum
{
    xpi_ram_option_misc_hyperram_3v0,
    xpi_ram_option_misc_hyperram_1v8,
};

enum
{
   xpi_ram_default_max_cs_low_time_us = 4, //!< Default Maximum CS low internal is 4us
};


enum {
    xpi_ram_opi = XPI_8PADS,
    xpi_ram_qpi = XPI_4PADS,
};

enum {
    xpi_ram_cfg_cmd_type_generic = 1,
    xpi_ram_cfg_cmd_type_spi2xpi = 2,
};

typedef struct {
    uint8_t cmd_type;
    uint8_t param_size;
}device_config_t;

typedef struct {
    uint32_t size_in_kbytes;                /*!< Device Size in Kilobytes, offset 0x00 */
    uint8_t data_pads;                      /*!< Device Size in Kilobytes, offset 0x04 */
    uint8_t en_ddr_mode;                    /*!< Enable DDR mode, offset 0x05 */
    uint8_t clk_freq_for_device_cfg;        /*!< Clk frequency for device configuration, offset 0x6 */
    uint8_t working_mode_por;               /*!< Offset 0x7 */
    uint8_t working_mode;                   /*!< The device working mode, offset 0x08 */
    uint8_t en_diff_clk;                    /*!< Enable Differential clock, offset 0x09 */
    uint8_t data_valid_time;                /*!< Data valid time, in 0.1ns, offset 0x0a */
    uint8_t cs_hold_time;                   /*!< CS hold time, 0 - default value, others - user specified value, offset 0xb */
    uint8_t cs_setup_time;                  /*!< CS setup time, 0 - default value, others - user specified value, offset 0xc */
    uint8_t cs_interval;                    /*!< CS interval, intervals between to CS active, offset 0x0d */
    uint8_t io_voltage;                     /*!< Device IO voltage, offset 0x0e*/
    uint8_t reserved0;                   /*!< Reserved for future use, offset 0xf */
    device_config_t device_cfg_list[2];     /*!< Device configuration list, offset 0x10 */
    uint32_t reserved1;                     /*!< Reserved, offset 0x14 */
    uint32_t device_config_params[2];       /*!< device config params, offset 0x18 */
    xpi_instr_seq_t device_cfg_instr_seq[2];/*!< Device configuration instruction sequence, offset 0x20 */
    uint32_t device_cfg_addr[2];            /*!< Device Configuration address, offset 0x40 */
    uint32_t reserved2[2];                  /*!< Reserved for future use, offset 0x48 */
} xpi_ram_info_t;

typedef struct {
    uint32_t tag;                         /*!< Must be "XRAM", offset 0x000 */
    uint32_t reserved0;                   /*!< Reserved for future use, offset 0x004 */
    uint8_t rxclk_src;                    /*!< RXCLKSRC value, offset 0x008 */
    uint8_t clk_freq;                     /*!< Clock frequency, offset 0x009 */
    uint8_t drive_strength;               /*!< Drive strength, offset 0x0a */
    uint8_t column_addr_size;             /*!< Column address size, offset 0x0b */
    uint8_t rxclk_src_for_init;           /*!< RXCLKSRC during initialization, offset 0x0c */
    uint8_t enable_word_addr;             /*!< Enable word address mode, offset 0x0d */
    uint8_t max_cs_low_time;              /*!< Max CS low time in terms of us, offset 0x0e */
    uint8_t skip_ahb_buf_cfg;             /*!< Skip Configuring AHB buffer, offset 0x0f */
    struct {
        uint8_t enable;                   /*!< Enable the port, 0 - disable, 1 - enable */
        uint8_t group;                    /*!< 0 - 1st IO group, 1 - 2nd IO group */
        uint8_t reserved[2];
    } port_info[4];                        /*!< Device connection information */
    xpi_ram_info_t device_info;       /*!< Device info, offset 0x20 */
    xpi_instr_seq_t instr_set[2];           /*!< XPI RAM read and write instruction sequences */
} xpi_ram_config_t;

#endif /* HPM_ROMAPI_XPI_RAM_DRV_H */
