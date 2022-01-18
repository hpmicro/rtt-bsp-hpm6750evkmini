/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef HPM_OTP_DRV_H
#define HPM_OTP_DRV_H

#include "hpm_common.h"

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
typedef enum {
    otp_region0_mask = 1U,  /*!< Address range: [0, 7]  */
    otp_region1_mask = 2U,  /*!< Address range: [8, 15] */
    otp_region2_mask = 4U,  /*!< Address range: [16, 127] */
    otp_region3_mask = 8U,  /*!< Address range: user defined */
}otp_region_t;

typedef enum {
    otp_no_lock = 0,
    otp_read_only = 1,
    otp_permanent_no_lock = 2,
    otp_disable_access = 3,
    otp_lock_option_max = otp_disable_access,
}otp_lock_option_t;


enum
{
    otp_write_disallowed = MAKE_STATUS(status_group_otp, 0),
};

/***********************************************************************************************************************
 * Prototypes
 **********************************************************************************************************************/
#ifdef __cpluscplus
extern "C" {
#endif

    /**
     * @brief Initialize OTP controller
     */
    void otp_init(void);

    /**
     * @brief De-initialize OTP controller
     */
    void otp_deinit(void);

    /**
     * @brief Read the FUSE world from shadow register
     * @param index
     * @param word
     * @return
     */
     uint32_t otp_read_from_shadow(uint32_t addr);

    /**
     * @brief Read the specified OTP word from OTP IP bus
     * @param index
     * @param word
     * @return
     */
    uint32_t otp_read_from_ip(uint32_t addr);

    /**
     * @brief Program a word to specified OTP field
     * @param index
     * @param word
     * @return
     */
    hpm_stat_t otp_program(uint32_t addr, const uint32_t *src, uint32_t num_of_words);

    /**
     * @brief Reload a OTP region
     * @param region
     * @return
     */
    hpm_stat_t otp_reload(otp_region_t region);

    /**
     * @brief Change the Software lock permission
     * @param addr
     * @param lock_option
     * @return
     */
    hpm_stat_t otp_lock_otp(uint32_t addr, otp_lock_option_t lock_option);


    hpm_stat_t otp_lock_shadow(uint32_t addr, otp_lock_option_t lock_option);

    /**
     * @brief Set the configurable region range
     * @param start
     * @param num_of_words
     * @return status_out_of_range - Invalid range
     *         status_success - Operation is successful
     */
    hpm_stat_t otp_set_configurable_region(uint32_t start, uint32_t num_of_words);

    /**
     * @return Write data to OTP shadow register
     * @param addr
     * @param val
     * @return
     */
    hpm_stat_t otp_write_shadow_register(uint32_t addr, uint32_t val);


#ifdef __cpluscplus
};
#endif





#endif

