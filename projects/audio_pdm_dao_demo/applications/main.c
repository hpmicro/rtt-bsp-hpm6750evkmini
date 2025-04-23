/*
 * Copyright (c) 2022 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "rtt_board.h"
#include "board.h"

#include "wav_header.h"
#include <dfs_fs.h>
#include <dfs_posix.h>

#define BUFF_SIZE 1024
uint8_t data_buff[BUFF_SIZE];
uint32_t dao_buff[BUFF_SIZE];
#define AUDIO_DATA_COUNT 256 /* data count per read from wav */

#define DAO_DEV_NAME              "dao"
#define PDM_DEV_NAME              "pdm"
#define RECORD_TIME_MS            10000

static void wavheader_init(wav_header_t *header, uint32_t sample_rate, uint8_t channels, uint8_t sample_bits, uint32_t datasize)
{
    memcpy(header->riff_chunk.id, "RIFF", 4);
    header->riff_chunk.datasize = datasize + 44 - 8;
    memcpy(header->riff_chunk.type, "WAVE", 4);
    memcpy(header->fmt_chunk.id, "fmt ", 4);
    header->fmt_chunk.datasize = 16;
    header->fmt_chunk.compression_code = 1;
    header->fmt_chunk.channels = channels;
    header->fmt_chunk.sample_rate = sample_rate;
    header->fmt_chunk.bit_per_sample = sample_bits;
    header->fmt_chunk.avg_bytes_per_sec = header->fmt_chunk.sample_rate * header->fmt_chunk.channels * header->fmt_chunk.bit_per_sample / 8;
    header->fmt_chunk.block_align = header->fmt_chunk.bit_per_sample * header->fmt_chunk.channels / 8;
    memcpy(header->data_chunk.id, "data", 4);
    header->data_chunk.datasize = datasize;
}

/* PDM share clock with I2S0, using I2S0 RX0 FIFO to receive data */
static int pdm_recordwav(int argc, char *argv[])
{
    int fd = -1;
    wav_header_t header;
    uint32_t data_size = 0;
    uint32_t target_data_size = 0;

    rt_device_t pdm_dev;
    struct rt_audio_caps pdm_caps = {0};


    if (argc != 2)
    {
        rt_kprintf("Usage:\n");
        rt_kprintf("pdm_recordwav /test.wav\n");
        goto __exit;
    }

    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC);
    if (fd < 0)
    {
        rt_kprintf("open file failed!\n");
        goto __exit;
    }

    write(fd, &header, sizeof(wav_header_t));

    /* get pdm device */
    pdm_dev = rt_device_find(PDM_DEV_NAME);
    if (!pdm_dev)
    {
        rt_kprintf("find %s failed!\n", PDM_DEV_NAME);
        goto __exit;
    }

    if (RT_EOK != rt_device_open(pdm_dev, RT_DEVICE_OFLAG_RDONLY))
    {
        rt_kprintf("open %s failed!\n", PDM_DEV_NAME);
        goto __exit;
    }

    /* get pdm_dev capability */
    pdm_caps.main_type               = AUDIO_TYPE_INPUT;
    pdm_caps.sub_type                = AUDIO_DSP_PARAM;
    rt_device_control(pdm_dev, AUDIO_CTL_GETCAPS, &pdm_caps);

    /* print record wav parameter */
    rt_kprintf("record %ds audio data to wav file:\n", RECORD_TIME_MS/1000);
    rt_kprintf("samplerate: %d\n", pdm_caps.udata.config.samplerate);
    rt_kprintf("samplebits: %d\n", pdm_caps.udata.config.samplebits);
    rt_kprintf("channel number: %d\n", pdm_caps.udata.config.channels);

    target_data_size = pdm_caps.udata.config.samplerate * (pdm_caps.udata.config.samplebits / 8U)
                        * pdm_caps.udata.config.channels * RECORD_TIME_MS / 1000;

    while (1)
    {
        int length;

        /* get audio data from device */
        length = rt_device_read(pdm_dev, 0, data_buff, BUFF_SIZE);

        if (length)
        {
            write(fd, data_buff, length);
            data_size += length;
        }

        if (data_size >= target_data_size)
            break;
    }

    /* rewrite wav header */
    wavheader_init(&header, pdm_caps.udata.config.samplerate, pdm_caps.udata.config.channels, pdm_caps.udata.config.samplebits, data_size);
    lseek(fd, 0, SEEK_SET);
    write(fd, &header, sizeof(wav_header_t));
    close(fd);

    rt_device_close(pdm_dev);

    __exit:

        if (fd >= 0)
            close(fd);

        return 0;
}
MSH_CMD_EXPORT(pdm_recordwav, pdm record sound to wav file);

/* DAO share clock with I2S1, using I2S1 TX0 FIFO to send data */
static int dao_playwav(int argc, char *argv[])
{
    int fd = -1;
    wav_header_t *info = NULL;
    uint32_t time;
    uint8_t audio_byte;
    uint8_t channel_multiples;

    rt_device_t dao_dev;
    struct rt_audio_caps dao_caps = {0};

    if (argc != 2)
    {
        rt_kprintf("Usage:\n");
        rt_kprintf("dao_playwav /test.wav\n");
        goto __exit;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        rt_kprintf("open file failed!\n");
        goto __exit;
    }

    info = (wav_header_t *) rt_malloc(sizeof * info);
    if (info == RT_NULL)
        goto __exit;
    if (read(fd, &(info->riff_chunk), sizeof(riff_chunk_t)) <= 0)
        goto __exit;
    if (read(fd, &(info->fmt_chunk),  sizeof(fmt_chunk_t)) <= 0)
        goto __exit;
    if (read(fd, &(info->data_chunk), sizeof(data_chunk_t)) <= 0)
        goto __exit;

    /* print wave parameter */
    time = info->data_chunk.datasize / (info->fmt_chunk.sample_rate * (info->fmt_chunk.bit_per_sample / 8U) * info->fmt_chunk.channels);
    rt_kprintf("wav information:\n");
    rt_kprintf("time: %ds\n", time);
    rt_kprintf("samplerate: %d\n", info->fmt_chunk.sample_rate);
    rt_kprintf("samplebits: %d\n", info->fmt_chunk.bit_per_sample);
    rt_kprintf("channel: %d\n", info->fmt_chunk.channels);

    dao_dev = rt_device_find(DAO_DEV_NAME);
    if (!dao_dev)
    {
        rt_kprintf("find %s failed!\n", DAO_DEV_NAME);
        goto __exit;
    }

    if (RT_EOK != rt_device_open(dao_dev, RT_DEVICE_OFLAG_WRONLY))
    {
        rt_kprintf("open %s failed!\n", DAO_DEV_NAME);
        goto __exit;
    }

    /* adjust I2S MCLK according to sample rate */
    board_config_i2s_clock(DAO_I2S, info->fmt_chunk.sample_rate);

    /* only support configure samplerate */
    dao_caps.main_type               = AUDIO_TYPE_OUTPUT;
    dao_caps.sub_type                = AUDIO_DSP_SAMPLERATE;
    dao_caps.udata.config.samplerate = info->fmt_chunk.sample_rate;
    rt_device_control(dao_dev, AUDIO_CTL_CONFIGURE, &dao_caps);

    /* get dao dev parameter */
    dao_caps.main_type               = AUDIO_TYPE_OUTPUT;
    dao_caps.sub_type                = AUDIO_DSP_PARAM;
    rt_device_control(dao_dev, AUDIO_CTL_GETCAPS, &dao_caps);

    /* DAO use 2 channel data */
    channel_multiples = dao_caps.udata.config.channels / info->fmt_chunk.channels;

    audio_byte = info->fmt_chunk.bit_per_sample / 8U; /* origin audio data length in byte */

    while (1)
    {
        int length;
        uint32_t data;
        uint32_t n;

        assert(BUFF_SIZE >= audio_byte * AUDIO_DATA_COUNT); /* check data_buff not overflow */
        assert(BUFF_SIZE >= AUDIO_DATA_COUNT * channel_multiples); /* check dao_buff not overflow */

        /* read audio data in wav file */
        length = read(fd, data_buff, audio_byte * AUDIO_DATA_COUNT);

        if (length <= 0)
            break;

        /* convert audio data to meet DAO requirement */
        n = 0;
        for (uint32_t i = 0; i < length;) {
            data = 0;
            /* get audio data according samplebits */
            for (uint8_t j = 0; j < audio_byte; j++) {
                data += data_buff[i++] << (8 * j);
            }
            /* move audio data to high positionin of 32bit */
            data <<= (dao_caps.udata.config.samplebits - info->fmt_chunk.bit_per_sample);
            for(uint32_t m = 0; m < channel_multiples; m++) {
                dao_buff[n++] = data;
            }
        }
        rt_device_write(dao_dev, 0, dao_buff, n * 4);
    }

    rt_device_close(dao_dev);

    __exit:

        if (fd >= 0)
            close(fd);

        if (info)
            rt_free(info);

        return 0;
}
MSH_CMD_EXPORT(dao_playwav, dao play wav file);


int main(void)
{
    rt_thread_mdelay(2000);

    if (dfs_mount(BOARD_SD_NAME, "/", "elm", 0, NULL) == 0)
    {
        rt_kprintf("%s mounted to /\n", BOARD_SD_NAME);
    }
    else
    {
        rt_kprintf("%s mount to / failed\n", BOARD_SD_NAME);
    }
    return 0;
}

