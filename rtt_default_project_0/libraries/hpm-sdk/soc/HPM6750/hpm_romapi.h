/*
* Copyright (c) 2021 hpmicro
*
* SPDX-License-Identifier: BSD-3-Clause
*
*/

#ifndef HPM_ROMAPI_H
#define HPM_ROMAPI_H

#include "hpm_common.h"
#include "hpm_otp_drv.h"
#include "hpm_romapi_xpi_def.h"
#include "hpm_romapi_xpi_soc_def.h"
#include "hpm_romapi_xpi_nor_def.h"
#include "hpm_romapi_xpi_ram_def.h"
#include "hpm_sdp_drv.h"

/* XPI0 base address */
#define HPM_XPI0_BASE (0xF3040000UL)
/* XPI0 base pointer */
#define HPM_XPI0 ((XPI_Type *) HPM_XPI0_BASE)
/* XPI1 base address */
#define HPM_XPI1_BASE (0xF3044000UL)
/* XPI1 base pointer */
#define HPM_XPI1 ((XPI_Type *) HPM_XPI1_BASE)


/***********************************************************************************************************************
 *
 *
 *      Definitions
 *
 *
 **********************************************************************************************************************/
typedef struct {
    uint32_t version;

    void (*init)(void);

    void (*deinit)(void);

    uint32_t (*read_from_shadow)(uint32_t addr);

    uint32_t (*read_from_ip)(uint32_t addr);

    hpm_stat_t (*program)(uint32_t addr, const uint32_t *src, uint32_t num_of_words);

    hpm_stat_t (*reload)(otp_region_t region);

    hpm_stat_t (*lock)(uint32_t addr, otp_lock_option_t lock_option);

    hpm_stat_t (*lock_shadow)(uint32_t addr, otp_lock_option_t lock_option);

    hpm_stat_t (*set_configurable_region)(uint32_t start, uint32_t num_of_words);

    hpm_stat_t (*write_shadow_register)(uint32_t addr, uint32_t data);

} otp_driver_interface_t;


typedef struct {
    uint32_t version;

    hpm_stat_t (*get_default_config)(xpi_config_t *xpi_config);

    hpm_stat_t (*get_default_device_config)(xpi_device_config_t *dev_config);

    hpm_stat_t (*init)(XPI_Type *base, xpi_config_t *xpi_config);

    hpm_stat_t (*config_ahb_buffer)(XPI_Type *base, xpi_ahb_buffer_cfg_t *ahb_buf_cfg);

    hpm_stat_t (*config_device)(XPI_Type *base, xpi_device_config_t *dev_cfg, xpi_port_t port);

    hpm_stat_t (*update_instr_table)(XPI_Type *base, const uint32_t *inst_base, uint32_t seq_idx, uint32_t num);

    hpm_stat_t (*transfer_blocking)(XPI_Type *base, xpi_xfer_ctx_t *xfer);

    void (*software_reset)(XPI_Type *base);

    bool (*is_idle)(XPI_Type *base);

    void (*update_dllcr)(XPI_Type *base, uint32_t serial_root_clk_freq, uint32_t data_valid_time, xpi_port_t port,
                         uint32_t dly_target);

    hpm_stat_t (*get_abs_apb_xfer_addr)(XPI_Type *base, xpi_xfer_port_t port, uint32_t in_addr, uint32_t *out_addr);

    hpm_stat_t (*iomux_init)(XPI_Type *base, const xpi_io_config_t *io_cfg);

    hpm_stat_t (*clock_init)(XPI_Type *base, const xpi_clk_config_t *clk_cfg);

} xpi_driver_interface_t;

typedef struct {
    uint32_t version;

    hpm_stat_t (*get_config)(XPI_Type *base, xpi_nor_config_t *nor_cfg, xpi_nor_config_option_t *cfg_option);

    hpm_stat_t (*init)(XPI_Type *base, xpi_nor_config_t *nor_config);

    hpm_stat_t (*enable_write)(XPI_Type *base, xpi_xfer_port_t port, const xpi_nor_config_t *nor_config, uint32_t addr);

    hpm_stat_t (*get_status)(XPI_Type *base, xpi_xfer_port_t port, const xpi_nor_config_t *nor_config, uint32_t addr,
                             uint16_t *out_status);

    hpm_stat_t (*wait_busy)(XPI_Type *base, xpi_xfer_port_t port, const xpi_nor_config_t *nor_config, uint32_t addr);

    hpm_stat_t (*erase)(XPI_Type *base, xpi_xfer_port_t port, const xpi_nor_config_t *nor_config, uint32_t start,
                        uint32_t length);

    hpm_stat_t (*erase_chip)(XPI_Type *base, xpi_xfer_port_t port, const xpi_nor_config_t *nor_config);

    hpm_stat_t (*erase_sector)(XPI_Type *base, xpi_xfer_port_t port, const xpi_nor_config_t *nor_config, uint32_t addr);

    hpm_stat_t (*erase_block)(XPI_Type *base, xpi_xfer_port_t port, const xpi_nor_config_t *nor_config, uint32_t addr);

    hpm_stat_t (*program)(XPI_Type *base, xpi_xfer_port_t port, const xpi_nor_config_t *nor_config, const uint32_t *src,
                          uint32_t dst_addr, uint32_t length);

    hpm_stat_t (*read)(XPI_Type *base, xpi_xfer_port_t port, const xpi_nor_config_t *nor_config, uint32_t *dst,
                       uint32_t start, uint32_t length);

    hpm_stat_t (*page_program_nonblocking)(XPI_Type *base, xpi_xfer_port_t port, const xpi_nor_config_t *nor_config,
                                           const uint32_t *src, uint32_t dst_addr, uint32_t length);

    hpm_stat_t (*erase_sector_nonblocking)(XPI_Type *base, xpi_xfer_port_t port, const xpi_nor_config_t *nor_config,
                                           uint32_t addr);

    hpm_stat_t (*erase_block_nonblocking)(XPI_Type *base, xpi_xfer_port_t port, const xpi_nor_config_t *nor_config,
                                          uint32_t addr);

    hpm_stat_t (*erase_chip_nonblocking)(XPI_Type *base, xpi_xfer_port_t port, const xpi_nor_config_t *nor_config);

    hpm_stat_t (*restore_spi_protocol)(XPI_Type *base, xpi_xfer_port_t port, xpi_nor_config_t *config,
                                       flash_run_context_t *run_ctx);

    hpm_stat_t (*write_persistent)(const uint32_t data);

    hpm_stat_t (*read_persistent)(uint32_t *data);

    hpm_stat_t (*auto_config)(XPI_Type *base, xpi_nor_config_t *nor_cfg, xpi_nor_config_option_t *cfg_option);

    hpm_stat_t (*get_property)(XPI_Type *base, xpi_nor_config_t *nor_cfg, uint32_t property_id, uint32_t *value);

    hpm_stat_t (*set_property)(XPI_Type *base, xpi_nor_config_t *nor_cfg, uint32_t property_id, uint32_t value);

} xpi_nor_driver_interface_t;


typedef struct {
    uint32_t version;

    hpm_stat_t (*get_config)(XPI_Type *base, xpi_ram_config_t *ram_cfg, xpi_ram_config_option_t *cfg_option);

    hpm_stat_t (*init)(XPI_Type *base, xpi_ram_config_t *ram_cfg);
} xpi_ram_driver_interface_t;


typedef struct {
    uint32_t version;

    hpm_stat_t (*sdp_ip_init)(void);

    hpm_stat_t (*sdp_ip_deinit)(void);

    hpm_stat_t (*aes_set_key)(sdp_aes_ctx_t *aes_ctx, const uint8_t *key, sdp_aes_key_bits_t keybits, uint32_t key_idx);

    hpm_stat_t (*aes_crypt_ecb)(sdp_aes_ctx_t *aes_ctx, sdp_aes_op_t op, uint32_t len, const uint8_t *in, uint8_t *out);

    hpm_stat_t (*aes_crypt_cbc)(sdp_aes_ctx_t *aes_ctx, sdp_aes_op_t op, uint32_t length, uint8_t iv[16],
                                const uint8_t *input, uint8_t *output);

    hpm_stat_t (*aes_crypt_ctr)(sdp_aes_ctx_t *aes_ctx, uint8_t *nonce_ctr, uint8_t *input, uint8_t *output,
                                uint32_t length);

    hpm_stat_t (*aes_ccm_gen_enc)(sdp_aes_ctx_t *aes_ctx, uint32_t input_len, const uint8_t *nonce, uint32_t nonce_len,
                                  const uint8_t *aad, uint32_t aad_len, const uint8_t *input, uint8_t *output,
                                  uint8_t *tag, uint32_t tag_len);

    hpm_stat_t (*aes_ccm_dec_verify)(sdp_aes_ctx_t *aes_ctx, uint32_t input_len, const uint8_t *nonce,
                                     uint32_t nonce_len, const uint8_t *aad, uint32_t aad_len, const uint8_t *input,
                                     uint8_t *output, const uint8_t *tag, uint32_t tag_len);

    hpm_stat_t (*memcpy)(sdp_dma_ctx_t *dma_ctx, void *dst, const void *src, uint32_t length);

    hpm_stat_t (*memset)(sdp_dma_ctx_t *dma_ctx, void *dst, uint8_t pattern, uint32_t length);

    hpm_stat_t (*hash_init)(sdp_hash_ctx_t *hash_ctx, sdp_hash_alg_t alg);

    hpm_stat_t (*hash_update)(sdp_hash_ctx_t *hash_ctx, const uint8_t *data, uint32_t length);

    hpm_stat_t (*hash_finish)(sdp_hash_ctx_t *hash_ctx, uint8_t *digest);
} sdp_driver_interface_t;

typedef struct {
    const uint32_t version;
    const char *copyright;

    const hpm_stat_t (*run_bootloader)(void *arg);

    const otp_driver_interface_t *otp_driver_if;
    const xpi_driver_interface_t *xpi_driver_if;
    const xpi_nor_driver_interface_t *xpi_nor_driver_if;
    const xpi_ram_driver_interface_t *xpi_ram_driver_if;
    const sdp_driver_interface_t *sdp_driver_if;
} bootloader_api_table_t;

#define ROM_API_TABLE_ROOT ((const bootloader_api_table_t*)0x2001FF00U)


#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************************************************************
 *
 *
 *      Enter bootloader Wrapper
 *
 *
 **********************************************************************************************************************/

static inline hpm_stat_t rom_enter_bootloader(void *ctx)
{
    return ROM_API_TABLE_ROOT->run_bootloader(ctx);
}

/***********************************************************************************************************************
 *
 *
 *      XPI NOR Driver Wrapper
 *
 *
 **********************************************************************************************************************/

static inline hpm_stat_t rom_xpi_nor_get_config(XPI_Type *base, xpi_nor_config_t *nor_cfg,
                                                xpi_nor_config_option_t *cfg_option)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->get_config(base, nor_cfg, cfg_option);
}

static inline hpm_stat_t rom_xpi_nor_init(XPI_Type *base, xpi_nor_config_t *nor_config)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->init(base, nor_config);
}

static inline hpm_stat_t rom_xpi_nor_erase(XPI_Type *base, xpi_xfer_port_t port, const xpi_nor_config_t *nor_config,
                                           uint32_t start, uint32_t length)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase(base, port, nor_config, start, length);
}

static inline hpm_stat_t rom_xpi_nor_erase_sector(XPI_Type *base, xpi_xfer_port_t port,
                                                  const xpi_nor_config_t *nor_config,
                                                  uint32_t start)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase_sector(base, port, nor_config, start);
}

static inline hpm_stat_t rom_xpi_nor_erase_sector_nonblocking(XPI_Type *base, xpi_xfer_port_t port,
                                                              const xpi_nor_config_t *nor_config,
                                                              uint32_t start)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase_sector_nonblocking(base, port, nor_config, start);
}

static inline hpm_stat_t rom_xpi_nor_erase_block(XPI_Type *base, xpi_xfer_port_t port,
                                                 const xpi_nor_config_t *nor_config,
                                                 uint32_t start)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase_block(base, port, nor_config, start);
}

static inline hpm_stat_t rom_xpi_nor_erase_block_nonblocking(XPI_Type *base, xpi_xfer_port_t port,
                                                             const xpi_nor_config_t *nor_config,
                                                             uint32_t start)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase_block_nonblocking(base, port, nor_config, start);
}


static inline hpm_stat_t rom_xpi_nor_erase_chip(XPI_Type *base, xpi_xfer_port_t port,
                                                const xpi_nor_config_t *nor_config)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase_chip(base, port, nor_config);
}

static inline hpm_stat_t rom_xpi_nor_erase_chip_nonblocking(XPI_Type *base, xpi_xfer_port_t port,
                                                            const xpi_nor_config_t *nor_config)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->erase_chip_nonblocking(base, port, nor_config);
}


static inline hpm_stat_t rom_xpi_nor_program(XPI_Type *base, xpi_xfer_port_t port, const xpi_nor_config_t *nor_config,
                                             const uint32_t *src, uint32_t dst_addr, uint32_t length)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->program(base, port, nor_config, src, dst_addr, length);
}

static inline hpm_stat_t rom_xpi_nor_page_program_nonblocking(XPI_Type *base, xpi_xfer_port_t port,
                                                              const xpi_nor_config_t *nor_config, const uint32_t *src,
                                                              uint32_t dst_addr, uint32_t length)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->page_program_nonblocking(base, port, nor_config, src, dst_addr,
                                                                           length);
}


static inline hpm_stat_t rom_xpi_nor_read(XPI_Type *base, xpi_xfer_port_t port, const xpi_nor_config_t *nor_config,
                                          uint32_t *dst, uint32_t start, uint32_t length)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->read(base, port, nor_config, dst, start, length);
}

static inline hpm_stat_t rom_xpi_nor_auto_config(XPI_Type *base, xpi_nor_config_t *config,
                                                 xpi_nor_config_option_t *cfg_option)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->auto_config(base, config, cfg_option);
}

static inline hpm_stat_t rom_xpi_nor_get_property(XPI_Type *base, xpi_nor_config_t *nor_cfg, uint32_t property_id,
                                                  uint32_t *value)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->get_property(base, nor_cfg, property_id, value);
}

static inline hpm_stat_t rom_xpi_nor_set_property(XPI_Type *base, xpi_nor_config_t *nor_cfg, uint32_t property_id,
                                                  uint32_t value)
{
    return ROM_API_TABLE_ROOT->xpi_nor_driver_if->set_property(base, nor_cfg, property_id, value);
}


/***********************************************************************************************************************
 *
 *
 *      XPI RAM Driver Wrapper
 *
 *
 **********************************************************************************************************************/
static inline hpm_stat_t rom_xpi_ram_get_config(XPI_Type *base, xpi_ram_config_t *ram_cfg,
                                                xpi_ram_config_option_t *cfg_option)
{
    return ROM_API_TABLE_ROOT->xpi_ram_driver_if->get_config(base, ram_cfg, cfg_option);
}

static inline hpm_stat_t rom_xpi_ram_init(XPI_Type *base, xpi_ram_config_t *ram_cfg)
{
    return ROM_API_TABLE_ROOT->xpi_ram_driver_if->init(base, ram_cfg);
}

/***********************************************************************************************************************
 *
 *
 *      SDP Driver Wrapper
 *
 *
 **********************************************************************************************************************/
static inline void rom_sdp_init(void)
{
    ROM_API_TABLE_ROOT->sdp_driver_if->sdp_ip_init();
}

static inline void rom_sdp_deinit(void)
{
    ROM_API_TABLE_ROOT->sdp_driver_if->sdp_ip_deinit();
}

static inline hpm_stat_t
rom_sdp_aes_set_key(sdp_aes_ctx_t *aes_ctx, const uint8_t *key, sdp_aes_key_bits_t key_bits, uint32_t key_idx)
{
    return ROM_API_TABLE_ROOT->sdp_driver_if->aes_set_key(aes_ctx, key, key_bits, key_idx);
}

static inline hpm_stat_t
rom_sdp_aes_crypt_ecb(sdp_aes_ctx_t *aes_ctx, sdp_aes_op_t op, uint32_t len, const uint8_t *in, uint8_t *out)
{
    return ROM_API_TABLE_ROOT->sdp_driver_if->aes_crypt_ecb(aes_ctx, op, len, in, out);
}

static inline hpm_stat_t rom_sdp_aes_crypt_cbc(sdp_aes_ctx_t *aes_ctx, sdp_aes_op_t op, uint32_t length, uint8_t iv[16],
                                               const uint8_t *in, uint8_t *out)
{
    return ROM_API_TABLE_ROOT->sdp_driver_if->aes_crypt_cbc(aes_ctx, op, length, iv, in, out);
}

static inline hpm_stat_t rom_sdp_hash_init(sdp_hash_ctx_t *hash_ctx, sdp_hash_alg_t alg)
{
    return ROM_API_TABLE_ROOT->sdp_driver_if->hash_init(hash_ctx, alg);
}

static inline hpm_stat_t rom_sdp_hash_update(sdp_hash_ctx_t *hash_ctx, const uint8_t *data, uint32_t length)
{
    return ROM_API_TABLE_ROOT->sdp_driver_if->hash_update(hash_ctx, data, length);
}

static inline hpm_stat_t rom_sdp_hash_finish(sdp_hash_ctx_t *hash_ctx, uint8_t *digest)
{
    return ROM_API_TABLE_ROOT->sdp_driver_if->hash_finish(hash_ctx, digest);
}

static inline hpm_stat_t rom_sdp_memcpy(sdp_dma_ctx_t *dma_ctx, void *dst, const void *src, uint32_t length)
{
    return ROM_API_TABLE_ROOT->sdp_driver_if->memcpy(dma_ctx, dst, src, length);
}

static inline hpm_stat_t rom_sdp_memset(sdp_dma_ctx_t *dma_ctx, void *dst, uint8_t pattern, uint32_t length)
{
    return ROM_API_TABLE_ROOT->sdp_driver_if->memset(dma_ctx, dst, pattern, length);
}

#ifdef __cplusplus
}
#endif


#endif /* HPM_ROMAPI_H */
