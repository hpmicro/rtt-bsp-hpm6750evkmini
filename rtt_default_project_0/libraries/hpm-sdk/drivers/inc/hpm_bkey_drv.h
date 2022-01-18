/**
* @file
* @brief BATT_KEY driver public API header file
*/
/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_BATT_KEY_DRV_H
#define HPM_BATT_KEY_DRV_H

#include "hpm_common.h"
#include "hpm_batt_key_regs.h"

typedef enum batt_key_lock_type {
    batt_key_lock_write = BATT_KEY_ECC_WLOCK_MASK,
    batt_key_lock_read = BATT_KEY_ECC_RLOCK_MASK,
    batt_key_lock_both = BATT_KEY_ECC_RLOCK_MASK | BATT_KEY_ECC_WLOCK_MASK,
} batt_key_lock_type_t;

/**
 *
 * @brief BATT_KEY driver APIs
 * @defgroup dramc_interface DRAMC driver APIs
 * @ingroup io_interfaces
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief batt_key set key content
 *
 * Program key content
 *
 * @param ptr BATT_KEY base address
 * @param key key index
 * @param start key content data start index
 * @param data pointer of actual data to be programmed
 * @param size data total size in 32-bit
 */
static inline void batt_key_set_key_data(BATT_KEY_Type *ptr, uint8_t key, uint8_t start, uint32_t *data, uint8_t size_in_4bytes)
{
    for (uint8_t i = 0; i < size_in_4bytes; i++) {
        ptr->KEY[key].DATA[start + i] = *(data + i);
    }
}

/**
 * @brief batt_key fetch key content
 *
 * Fetch key content
 *
 * @param ptr BATT_KEY base address
 * @param key key index
 * @param start key content data start index
 * @param data pointer of buffer to received key content
 * @param size data total size in 32-bit
 */
static inline void batt_key_get_key_data(BATT_KEY_Type *ptr, uint8_t key, uint8_t start, uint32_t *data, uint8_t size_in_4bytes)
{
    for (uint8_t i = 0; i < size_in_4bytes; i++) {
        *(data + i) = ptr->KEY[key].DATA[start + i];
    }
}

/**
 * @brief batt_key lock key
 *
 * Feed correct ecc data of current key content and lock it
 *
 * @param ptr BATT_KEY base address
 * @param key key index
 * @param lock lock type
 * @param ecc ecc value of current key content
 */
static inline void batt_key_lock(BATT_KEY_Type *ptr, uint8_t key, batt_key_lock_type_t lock, uint16_t ecc)
{
    ptr->ECC[key] = BATT_KEY_ECC_ECC_SET(ecc) | lock;
}

/**
 * @brief batt_key select key
 *
 * Select which key to use
 *
 * @param ptr BATT_KEY base address
 * @param key key index
 */

static inline void batt_key_select_key(BATT_KEY_Type *ptr, uint8_t key)
{
    ptr->SELECT = BATT_KEY_SELECT_SELECT_SET(key);
}

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* HPM_BATT_KEY_DRV_H */
