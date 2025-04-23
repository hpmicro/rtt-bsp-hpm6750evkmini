/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_ESC_DRV_H
#define HPM_ESC_DRV_H

#include "hpm_common.h"
#include "hpm_esc_regs.h"

/**
 *
 * @brief ESC driver APIs
 * @defgroup esc_interface ESC driver APIs
 * @ingroup esc_interfaces
 * @{
 */

 /**
 * @brief ESC error codes
 */
enum {
    status_esc_eeprom_ack_error      = MAKE_STATUS(status_group_esc, 0),           /**< ESC EEPROM ack error */
    status_esc_eeprom_checksum_error = MAKE_STATUS(status_group_esc, 1),           /**< ESC EEPROM checksum error */
};


typedef enum {
    latch_source_from_ntm = 0,
    latch_source_from_trigger_mux = 1,
} esc_latch_source_t;

typedef enum {
    esc_eeprom_idle_cmd = 0, /* clear error bits */
    esc_eeprom_read_cmd = 1,
    esc_eeprom_write_cmd = 2,
    esc_eeprom_reload_cmd = 4,
} esc_eeprom_cmd_t;

typedef enum  {
    esc_ctrl_signal_func_alt_nmii_link0 = 0,
    esc_ctrl_signal_func_alt_nmii_link1 = 1,
    esc_ctrl_signal_func_alt_nmii_link2 = 2,
    esc_ctrl_signal_func_alt_link_act0  = 3,
    esc_ctrl_signal_func_alt_link_act1  = 4,
    esc_ctrl_signal_func_alt_link_act2  = 5,
    esc_ctrl_signal_func_alt_led_run    = 6,
    esc_ctrl_signal_func_alt_led_err    = 7,
    esc_ctrl_signal_func_alt_reset_out  = 8,
} esc_ctrl_signal_function_t;


typedef struct {
    bool eeprom_emulation;
    bool eeprom_size_over_16kbit;
    bool core_clock_en;
    bool phy_refclk_en;
} esc_eeprom_clock_config_t;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief ESC peripheral clock
 *
 * @param[in] ptr ESC base address
 * @param[in] enable Set true to enable or false to disable
 */
static inline void esc_core_enable_clock(ESC_Type *ptr, bool enable)
{
    if (enable) {
        ptr->GPR_CFG0 |= ESC_GPR_CFG0_CLK100_EN_MASK;
    } else {
        ptr->GPR_CFG0 &= ~ESC_GPR_CFG0_CLK100_EN_MASK;
    }
}

/**
 * @brief ESC PHY clock
 *
 * @param[in] ptr ESC base address
 * @param[in] enable Set true to enable or false to disable
 */
static inline void esc_phy_enable_clock(ESC_Type *ptr, bool enable)
{
    if (enable) {
        ptr->PHY_CFG1 |= ESC_PHY_CFG1_REFCK_25M_OE_MASK;   /*!< enable PHY 25M refck */
    } else {
        ptr->PHY_CFG1 &= ~ESC_PHY_CFG1_REFCK_25M_OE_MASK;   /*!< disable PHY 25M refck */
    }
}

/**
 * @brief ESC config eeprom attributes(emulation and size) and peripheral clock
 *
 * @param[in] ptr ESC base address
 * @param[in] config esc_eeprom_clock_config_t
 */
static inline void esc_config_eeprom_and_clock(ESC_Type *ptr, esc_eeprom_clock_config_t *config)
{
    uint32_t gpr_cfg0 = ptr->GPR_CFG0;

    if (config->eeprom_emulation) {
        gpr_cfg0 |= ESC_GPR_CFG0_EEPROM_EMU_MASK;
        gpr_cfg0 &= ~(ESC_GPR_CFG0_PROM_SIZE_MASK | ESC_GPR_CFG0_I2C_SCLK_EN_MASK);
    } else {
        gpr_cfg0 &= ~ESC_GPR_CFG0_EEPROM_EMU_MASK;
        gpr_cfg0 |= ESC_GPR_CFG0_I2C_SCLK_EN_MASK;
        if (config->eeprom_size_over_16kbit) {
            gpr_cfg0 |= ESC_GPR_CFG0_PROM_SIZE_MASK;
        } else {
            gpr_cfg0 &= ~ESC_GPR_CFG0_PROM_SIZE_MASK;
        }
    }
    ptr->GPR_CFG0 = gpr_cfg0;
    esc_core_enable_clock(ptr, config->core_clock_en);
    esc_phy_enable_clock(ptr, config->phy_refclk_en);
}

/**
 * @brief ESC assign specific function to CTRL signal
 *
 * @param[in] ptr ESC base address
 * @param[in] index CTRL signal index(0-8)
 * @param[in] func specific function
 * @param[in] invert invert signal
 */
static inline void esc_config_ctrl_signal_function(ESC_Type *ptr, uint8_t index, esc_ctrl_signal_function_t func, bool invert)
{
    ptr->IO_CFG[index] = ESC_IO_CFG_FUNC_ALT_SET(func) | ESC_IO_CFG_INVERT_SET(invert);
}

/**
 * @brief ESC config nmii_link signal source
 *
 * @param[in] ptr ESC base address
 * @param[in] link0_from_io true for signal from configured IO; false for signal from register(GPR_CFG2) value
 * @param[in] link1_from_io true for signal from configured IO; false for signal from register(GPR_CFG2) value
 * @param[in] link2_from_io true for signal from configured IO; false for signal from register(GPR_CFG2) value
 */
static inline void esc_config_nmii_link_source(ESC_Type *ptr, bool link0_from_io, bool link1_from_io, bool link2_from_io)
{
    if (link0_from_io) {
        ptr->GPR_CFG2 |= ESC_GPR_CFG2_NMII_LINK0_FROM_IO_MASK;
    } else {
        ptr->GPR_CFG2 &= ~ESC_GPR_CFG2_NMII_LINK0_FROM_IO_MASK;
        ptr->GPR_CFG2 |= ESC_GPR_CFG2_NMII_LINK0_GPR_MASK; /* config GRP to indicate LINK0 is invalid by default */
    }

    if (link1_from_io) {
        ptr->GPR_CFG2 |= ESC_GPR_CFG2_NMII_LINK1_FROM_IO_MASK;
    } else {
        ptr->GPR_CFG2 &= ~ESC_GPR_CFG2_NMII_LINK1_FROM_IO_MASK;
        ptr->GPR_CFG2 |= ESC_GPR_CFG2_NMII_LINK1_GPR_MASK; /* config GRP to indicate LINK1 is invalid by default */
    }

    if (link2_from_io) {
        ptr->GPR_CFG2 |= ESC_GPR_CFG2_NMII_LINK2_FROM_IO_MASK;
    } else {
        ptr->GPR_CFG2 &= ~ESC_GPR_CFG2_NMII_LINK2_FROM_IO_MASK;
        ptr->GPR_CFG2 |= ESC_GPR_CFG2_NMII_LINK2_GPR_MASK; /* config GRP to indicate LINK2 is invalid by default */
    }
}

/* config ESC reset request source: ESC core or GRP_REG value */
/**
 * @brief ESC config reset signal source
 *
 * @param[in] ptr ESC base address
 * @param[in] reset_from_ecat_core true for reset signal from ecat core; false for reset signal from register(GPR_CFG1) value
 */
static inline void esc_config_reset_source(ESC_Type *ptr, bool reset_from_ecat_core)
{
    if (reset_from_ecat_core) {
        ptr->GPR_CFG1 |= ESC_GPR_CFG1_RSTO_OVRD_ENJ_MASK;
    } else {
        ptr->GPR_CFG1 &= ~ESC_GPR_CFG1_RSTO_OVRD_ENJ_MASK;
    }
}

/**
 * @brief ESC generate reset signal to ESC_RESET interrupt and RESET_OUT pin
 * @note the reset signal source should be configured in esc_config_reset_source before
 *
 * @param[in] ptr ESC base address
 */
static inline void esc_pdi_reset(ESC_Type *ptr)
{
    ptr->ESC_RST_PDI = 0x52; /* R */
    ptr->ESC_RST_PDI = 0x45; /* E */
    ptr->ESC_RST_PDI = 0x53; /* S */
}

/**
 * @brief ESC set phy offset
 *
 * @param[in] ptr ESC base address
 * @param[in] offset PHY register offset
 */
static inline void esc_set_phy_offset(ESC_Type *ptr, uint8_t offset)
{
    ptr->PHY_CFG0 = (ptr->PHY_CFG0 & ~ESC_PHY_CFG0_PHY_OFFSET_VAL_MASK) | (offset << ESC_PHY_CFG0_PHY_OFFSET_VAL_SHIFT);
}

/**
 * @brief ESC enable PDI to access MII management
 *
 * @param[in] ptr ESC base address
 */
static inline void esc_enable_pdi_access_mii_management(ESC_Type *ptr)
{
    ptr->MIIM_PDI_ACC_STAT |= ESC_MIIM_PDI_ACC_STAT_ACC_MASK;
}

/**
 * @brief ESC disable PDI to access MII management
 *
 * @param[in] ptr ESC base address
 */
static inline void esc_disable_pdi_access_mii_management(ESC_Type *ptr)
{
    ptr->MIIM_PDI_ACC_STAT &= ~ESC_MIIM_PDI_ACC_STAT_ACC_MASK;
}

/*!
 * @brief ESC read PHY register via ESC MII Management Interface
 *
 * @param[in] ptr ESC base address
 * @param[in] phy_addr PHY address.
 * @param[in] reg_addr Register address.
 * @param[in] data PHY data returned.
 */
hpm_stat_t esc_mdio_read(ESC_Type *ptr, uint8_t phy_addr, uint8_t reg_addr, uint16_t *data);

/*!
 * @brief ESc write PHY register via ESC MII Management Interface
 *
 * @param[in] ptr ESC base address
 * @param[in] phy_addr PHY address.
 * @param[in] reg_addr Register address.
 * @param[in] data Write to PHY register.
 */
hpm_stat_t esc_mdio_write(ESC_Type *ptr, uint8_t phy_addr, uint8_t reg_addr, uint16_t data);

/*!
 * @brief ESC check eeprom loading data status
 * @note EtherCAT communication is possible even if the EEPROM is blank
 *
 * @param[in] ptr ESC base address.
 * @retval status_success: loding data successfully and correctlly.
 * @retval status_esc_eeprom_ack_error: loding  data checksum error(eeprom blank).
 * @retval status_esc_eeprom_checksum_error: no ack error.
 * @retval status_timeout: loding data timeout.
 */
hpm_stat_t esc_check_eeprom_loading(ESC_Type *ptr);

/*!
 * @brief ESC get eeprom cmd, this using in eeprom emulation function
 *
 * @param[in] ptr ESC base address
 * @return uint8_t esc_eeprom_cmd_t.
 */
static inline uint8_t esc_get_eeprom_cmd(ESC_Type *ptr)
{
    return ESC_EEPROM_CTRL_STAT_CMD_GET(ptr->EEPROM_CTRL_STAT);
}

/*!
 * @brief ESC ack eeprom cmd in eeprom emualtion function
 *
 * @param[in] ptr ESC base address
 * @param[in] cmd esc_eeprom_cmd_t
 * @param[in] ack_err eeprom ack error occurrred
 * @param[in] crc_err eeprom checksum error occurrred
 */
static inline void esc_eeprom_emulation_ack(ESC_Type *ptr, esc_eeprom_cmd_t cmd, bool ack_err, bool crc_err)
{
    uint16_t temp = ESC_EEPROM_CTRL_STAT_CMD_SET(cmd);
    if (ack_err) {
        temp |= ESC_EEPROM_CTRL_STAT_ERR_ACK_CMD_MASK;
    }
    if (crc_err) {
        temp |= ESC_EEPROM_CTRL_STAT_CKSM_ERR_MASK;
    }

    ptr->EEPROM_CTRL_STAT = temp;
}

/*!
 * @brief ESC get eeprom byte address
 *
 * @param[in] ptr ESC base address
 * @return byte address
 */
static inline uint32_t esc_get_eeprom_byte_address(ESC_Type *ptr)
{
    return (ptr->EEPROM_ADDR) << 1U;
}

/*!
 * @brief ESC get eeprom word(2 bytes) address
 *
 * @param[in] ptr ESC base address
 * @return word address
 */
static inline uint32_t esc_get_eeprom_word_address(ESC_Type *ptr)
{
    return ptr->EEPROM_ADDR;
}

/*!
 * @brief ESC read eeprom data from register, this function is using in eeprom emulation function
 *
 * @param[in] ptr ESC base address
 * @return eeprom data
 */
static inline uint64_t esc_read_eeprom_data(ESC_Type *ptr)
{
    return ptr->EEPROM_DATA;
}

/*!
 * @brief ESC write eeprom data to register, this function is using in eeprom emulation function
 *
 * @param[in] ptr ESC base address
 * @param[in] data eeprom data
 */
static inline void esc_write_eeprom_data(ESC_Type *ptr, uint64_t data)
{
    ptr->EEPROM_DATA = data;
}

/*!
 * @brief ESC config latch0 signal source
 *
 * @param[in] ptr ESC base address
 * @param[in] latch0_from_ntm true for signal from ntm system, false for signal from IO
 */
static inline void esc_config_latch0_source(ESC_Type *ptr, bool latch0_from_ntm)
{
    if (latch0_from_ntm) {
        ptr->GPR_CFG1 &= ~ESC_GPR_CFG1_LATCH0_FROM_IO_MASK;
    } else {
        ptr->GPR_CFG1 |= ESC_GPR_CFG1_LATCH0_FROM_IO_MASK;
    }
}

/*!
 * @brief ESC config latch1 signal source
 *
 * @param[in] ptr ESC base address
 * @param[in] latch0_from_trigmux true for signal from trigmux system, false for signal from IO
 */
static inline void esc_config_latch1_source(ESC_Type *ptr, bool latch0_from_trigmux)
{
    if (latch0_from_trigmux) {
        ptr->GPR_CFG1 &= ~ESC_GPR_CFG1_LATCH1_FROM_IO_MASK;
    } else {
        ptr->GPR_CFG1 |= ESC_GPR_CFG1_LATCH1_FROM_IO_MASK;
    }
}

#if defined(HPM_IP_FEATURE_ESC_SYNC_IRQ_MASK) && HPM_IP_FEATURE_ESC_SYNC_IRQ_MASK
/*!
 * @brief ESC map sync irq to pdi irq
 *
 * Note: this API will change bit3 and bit7 value of 0x151 register
 *
 * @param[in] ptr ESC base address
 * @param[in] sync0_irq true: map sync0 irq to pdi irq in 0x151 register
 * @param[in] sync1_irq true: map sync1 irq to pdi irq in 0x151 register
 */
static inline void esc_enable_sync_irq_to_pdi_irq(ESC_Type *ptr, bool sync0_irq, bool sync1_irq)
{
    ptr->GPR_CFG0 = (ptr->GPR_CFG0 & ~(ESC_GPR_CFG0_SYNC0_PDI_IRQEN_MASK | ESC_GPR_CFG0_SYNC1_PDI_IRQEN_MASK))
                     | (ESC_GPR_CFG0_SYNC0_PDI_IRQEN_SET(sync0_irq))
                     | (ESC_GPR_CFG0_SYNC1_PDI_IRQEN_SET(sync1_irq));
}
#endif

#if defined(HPM_IP_FEATURE_ESC_PORT_DIS) && HPM_IP_FEATURE_ESC_PORT_DIS
/*!
 * @brief ESC change port implementation description
 *
 * Note: this API will change the value of 0x7 register to change port implementation description
 *
 * @param[in] ptr ESC base address
 * @param[in] port0 true: change port0 to not implemented in port description register
 * @param[in] port1 true: change port1 to not implemented in port description register
 * @param[in] port2 true: change port2 to not implemented in port description register
 */
static inline void esc_change_port_description(ESC_Type *ptr, bool port0, bool port1, bool port2)
{
    ptr->GPR_CFG0 = (ptr->GPR_CFG0 & ~(ESC_GPR_CFG0_PORT0_DIS_MASK | ESC_GPR_CFG0_PORT1_DIS_MASK | ESC_GPR_CFG0_PORT2_DIS_MASK))
                     | (ESC_GPR_CFG0_PORT0_DIS_SET(port0))
                     | (ESC_GPR_CFG0_PORT1_DIS_SET(port1))
                     | (ESC_GPR_CFG0_PORT2_DIS_SET(port2));
}
#endif

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_ESC_DRV_H */
