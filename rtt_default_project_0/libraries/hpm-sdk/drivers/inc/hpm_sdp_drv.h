/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_SDP_DRV_H
#define HPM_SDP_DRV_H

#include "hpm_common.h"
#include "hpm_sdp_regs.h"

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
typedef enum {
    sdp_aes_keybits_128,
    sdp_aes_keybits_256,
} sdp_aes_key_bits_t;


typedef enum {
    sdp_aes_op_encrypt,
    sdp_aes_op_decrypt,
} sdp_aes_op_t;

typedef enum {
    sdp_hash_alg_sha1,
    sdp_hash_alg_crc32,
    sdp_hash_alg_sha256,
    sdp_hash_alg_max = sdp_hash_alg_sha256,
} sdp_hash_alg_t;


#define HASH_BLOCK_SIZE (64U)
#define AES_BLOCK_SIZE (16U)
#define AES_128_KEY_SIZE (0x10U)
#define AES_256_KEY_SIZE (0x20U)
/**
 * @brief Bitfield definitions for the PKT_CTRL
 */
#define SDP_PKT_CTRL_DERSEMA_MASK (1U << 2)
#define SDP_PKT_CTRL_CHAIN_MASK (1U << 3)
#define SDP_PKT_CTRL_HASHINIT_MASK (1U << 4)
#define SDP_PKT_CTRL_HASHFINISH_MASK (1U << 5)
#define SDP_PKT_CTRL_CIPHIV_MASK (1U << 6)

typedef struct _sdp_packet_struct {
    struct _sdp_packet_struct *next_cmd;
    union {
        struct {
            uint32_t RESERVED0: 1;
            uint32_t PKTINT: 1;
            uint32_t DCRSEMA: 1;
            uint32_t CHAIN: 1;
            uint32_t HASHINIT: 1;
            uint32_t HASHFINISH: 1;
            uint32_t CIPHIV: 1;
            uint32_t RESERVED1: 17;
            uint32_t PKTTAG: 8;
        };
        uint32_t PKT_CTRL;
    } pkt_ctrl;
    uint32_t src_addr;
    uint32_t dst_addr;
    uint32_t buf_size;
    uint32_t reserved[3];
} sdp_pkt_struct_t;


typedef struct {
    uint8_t key_idx;
    uint8_t key_bits;
    uint16_t reserved;
    sdp_pkt_struct_t sdp_pkt;
    uint32_t buf0[AES_BLOCK_SIZE / sizeof(uint32_t)];
    uint32_t buf1[AES_BLOCK_SIZE / sizeof(uint32_t)];
    uint32_t buf2[AES_BLOCK_SIZE / sizeof(uint32_t)];
    uint32_t buf3[AES_BLOCK_SIZE / sizeof(uint32_t)];
} sdp_aes_ctx_t;


typedef struct {
    sdp_pkt_struct_t sdp_pkt;
} sdp_dma_ctx_t;

typedef struct {
    sdp_pkt_struct_t sdp_pkt;
    uint32_t internal[64];
} sdp_hash_ctx_t;


enum {
    status_sdp_no_crypto_support = MAKE_STATUS(status_group_sdp, 0),
    status_sdp_no_hash_support = MAKE_STATUS(status_group_sdp, 1),
    status_sdp_invalid_key_src = MAKE_STATUS(status_group_sdp, 2),
    status_sdp_error_packet = MAKE_STATUS(status_group_sdp, 3),
    status_sdp_aes_busy = MAKE_STATUS(status_group_sdp, 4),
    status_sdp_hash_busy = MAKE_STATUS(status_group_sdp, 5),
    status_sdp_error_setup = MAKE_STATUS(status_group_sdp, 6),
    status_sdp_error_src = MAKE_STATUS(status_group_sdp, 7),
    status_sdp_error_dst = MAKE_STATUS(status_group_sdp, 8),
    status_sdp_error_hash = MAKE_STATUS(status_group_sdp, 9),
    status_sdp_error_chain = MAKE_STATUS(status_group_sdp, 10),
    status_sdp_error_invalid_mac,

};

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************************************************************
 * Prototypes
 **********************************************************************************************************************/
/**
 * @brief Initialize the SDP controller
 * @param base
 * @return status_success
 *         status_invalid_argument
 */
hpm_stat_t sdp_init(SDP_Type *base);

/**
 * @brief De-initialize the SDP controller
 * @param base
 * @return
 */
hpm_stat_t sdp_deinit(SDP_Type *base);


/**
 * @brief Set the AES key for the SDP AES operation
 * @param base
 * @param hw_ctx
 * @param aes_ctx
 * @return
 */
hpm_stat_t sdp_aes_set_key(SDP_Type *base, sdp_aes_ctx_t *aes_ctx, const uint8_t *key, sdp_aes_key_bits_t key_bits,
                           uint32_t key_idx);

/**
 * @brief Perform the basic AES ECB operation
 * @param base
 * @param hw_ctx
 * @param op
 * @param input
 * @param output
 * @return
 */
hpm_stat_t sdp_aes_crypt_ecb(SDP_Type *base, sdp_aes_ctx_t *aes_ctx, sdp_aes_op_t op, uint32_t len, const uint8_t *in,
                             uint8_t *out);

/**
 * @brief Perform the AES CBC operation
 * @param base
 * @param hw_ctx
 * @param op
 * @param iv
 * @param input
 * @param output
 * @return
 */
hpm_stat_t sdp_aes_crypt_cbc(SDP_Type *base, sdp_aes_ctx_t *aes_ctx, sdp_aes_op_t op, uint32_t length,
                             const uint8_t iv[16], const uint8_t *input, uint8_t *output);


/**
 * @brief Perform the AES-CTR operation
 *        See NIST Special Publication800-38A for more details
 * @param base
 * @param aes_ctx
 * @param nonce_counter
 * @param input
 * @param output
 * @param length
 * @return
 */
hpm_stat_t sdp_aes_crypt_ctr(SDP_Type *base, sdp_aes_ctx_t *aes_ctx, uint8_t *nonce_counter, uint8_t *input,
                             uint8_t *output, uint32_t length);


/**
 * @brief Perform the AES-CCM generate and encrypt
 *        See NIST Special Publication 800-38C for more details
 * @param base
 * @param aes_ctx
 * @param input_len
 * @param iv
 * @param iv_len
 * @param aad
 * @param aad_len
 * @param input
 * @param output
 * @param tag
 * @param tag_len
 * @return
 */
hpm_stat_t sdp_aes_ccm_generate_encrypt(SDP_Type *base, sdp_aes_ctx_t *aes_ctx, uint32_t input_len, const uint8_t *iv,
                                       uint32_t iv_len, const uint8_t *aad, uint32_t aad_len, const uint8_t *input,
                                       uint8_t *output, uint8_t *tag, uint32_t tag_len);

/**
 * @brief Perform the AES-CCM decrypt and verify
 *        See NIST Special Publication 800-38C for more details
 * @param base
 * @param aes_ctx
 * @param input_len
 * @param iv
 * @param iv_len
 * @param aad
 * @param aad_len
 * @param input
 * @param output
 * @param tag
 * @param tag_len
 * @return
 */
hpm_stat_t sdp_aes_ccm_decrypt_verify(SDP_Type *base, sdp_aes_ctx_t *aes_ctx, uint32_t input_len, const uint8_t *iv,
                                    uint32_t iv_len, const uint8_t *aad, uint32_t aad_len, const uint8_t *input,
                                    uint8_t *output, const uint8_t *tag, uint32_t tag_len);

/**
 * @brief Perform the DMA accelerated memcpy
 * @param base
 * @param sdp_ctx
 * @param dst
 * @param src
 * @param length
 * @return
 */
hpm_stat_t sdp_memcpy(SDP_Type *base, sdp_dma_ctx_t *sdp_ctx, void *dst, const void *src, uint32_t length);

/**
 * @brief Perform the DMA accelerated memset
 * @param base
 * @param sdp_ctx
 * @param dst
 * @param pattern
 * @param length
 * @return
 */
hpm_stat_t sdp_memset(SDP_Type *base, sdp_dma_ctx_t *sdp_ctx, void *dst, uint8_t pattern, uint32_t length);

/**
 * @brief Initialize the HASH engine
 * @param base
 * @param alg
 * @return
 */
hpm_stat_t sdp_hash_init(SDP_Type *base, sdp_hash_ctx_t *hash_ctx, sdp_hash_alg_t alg);

/**
 * @brief Compute the HASH digest
 * @param base
 * @param alg
 * @param data
 * @param length
 * @return
 */
hpm_stat_t sdp_hash_update(SDP_Type *base, sdp_hash_ctx_t *hash_ctx, const uint8_t *data, uint32_t length);

/**
 * @brief Finish the HASH calculation and output the digest
 * @param base
 * @param sdp_ctx
 * @param digest
 * @return
 */
hpm_stat_t sdp_hash_finish(SDP_Type *base, sdp_hash_ctx_t *hash_ctx, uint8_t *digest);

hpm_stat_t sdp_wait_done(SDP_Type *base);

#ifdef __cplusplus
}
#endif

#endif
