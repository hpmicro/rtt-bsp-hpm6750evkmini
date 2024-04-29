/*
 * Copyright (c) 2022 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef WAV_HEADER_H
#define WAV_HEADER_H

typedef struct riff_chunk
{
    char       id[4];              /* "RIFF" */
    uint32_t   datasize;           /* RIFF chunk data size,exclude riff_id[4] and riff_datasize,total - 8 */
    char       type[4];            /* "WAVE" */
} riff_chunk_t;

typedef struct fmt_chunk
{
    char       id[4];               /* "fmt " */
    uint32_t   datasize;            /* fmt chunk data size,16 for pcm */
    uint16_t   compression_code;    /* 1 for PCM */
    uint16_t   channels;            /* 1(mono) or 2(stereo) */
    uint32_t   sample_rate;         /* samples per second */
    uint32_t   avg_bytes_per_sec;   /* sample_rate * channels * bit_per_sample / 8 */
    uint16_t   block_align;         /* number bytes per sample, bit_per_sample * channels / 8 */
    uint16_t   bit_per_sample;      /* bits of each sample(8,16,32). */
} fmt_chunk_t;

typedef struct data_chunk
{
    char       id[4];              /* "data" */
    uint32_t   datasize;           /* data chunk size,pcm_size - 44 */
} data_chunk_t;


typedef struct wav_header
{
    riff_chunk_t riff_chunk;
    fmt_chunk_t  fmt_chunk;
    data_chunk_t data_chunk;
} wav_header_t;


#endif /* WAV_HEADER_H */
