/*
 * Copyright (c) 2022-2023 HPMicro
 *
 * Change Logs:
 * Date         Author          Notes
 * 2022-03-10   will        first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "rtt_board.h"
#include "board.h"

#define PWM_DEV_NAME        "pwm3"  /* PWM name */
struct rt_device_pwm *pwm_dev;      /* PWM device */
#define BEEP_VOL_RANGE      (1000)
#define FULL_NOTE_TIME  (1600)
#define NORAML_NOTE_SPACE ((float)4/5)
#define MUSIC_VOICE (50)

static const uint16_t scale_freq_tab[16]  = {0, 0, 262, 277, 294, 311, 330, 330, 349, 370, 392, 415, 440, 466, 494, 494};
static const uint8_t split_note[7] = {1, 2, 4, 8, 16, 32, 64};
static const uint8_t zone_mul[3] = {1, 2, 4};

static const uint8_t the_star_song[] =
{
    21,2, 21,2, 25,2, 25,2, 26,2,
    26,2, 25,1, 24,2, 24,2, 23,2,
    23,2, 22,2, 22,2, 21,1, 25,2,
    25,2, 24,2, 24,2, 23,2, 23,2,
    22,1, 25,2, 25,2, 24,2, 24,2,
    23,2, 23,2, 22,1, 21,2, 21,2,
    25,2, 25,2, 26,2, 26,2, 25,1,
    24,2, 24,2, 23,2, 23,2, 22,2,
    22,2, 21,1, 0,0

};


void thread_entry(void *arg);

void beep_on(void)
{
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    rt_pwm_enable(pwm_dev, BOARD_BEEP_PWM_OUT);
}

void beep_off(void)
{
    rt_pwm_disable(pwm_dev, BOARD_BEEP_PWM_OUT);
}
/**
 *
 * @param vol 0-1000
 * @param freq 20-22khz
 */
void beep_set(uint16_t vol, uint16_t freq)
{
    uint32_t period;
    uint32_t pulse;
    period = 1000000000 / freq;
    pulse = (uint64_t) vol * period / BEEP_VOL_RANGE;
    rt_pwm_set(pwm_dev, BOARD_BEEP_PWM_OUT, period, pulse);
}

static void hpm_play(uint8_t * music, uint16_t length, uint16_t vol)
{
    uint16_t freq;
    uint16_t pos = 0;
    uint8_t phonogram, sound_zone, semitone, note_time, performance_effect, symbol_point;
    uint16_t beep_times = 0;
    uint16_t no_beep_times = 0;
    do {
        phonogram = music[pos] % 10;
        sound_zone = (music[pos] / 10) % 10;
        semitone = (music[pos] / 100) % 10;
        note_time = music[pos + 1] % 10;
        performance_effect = (music[pos + 1] / 10) % 10;
        symbol_point = (music[pos + 1] / 100) % 10;
        freq = scale_freq_tab[phonogram * 2 + semitone] * zone_mul[sound_zone -1];
        beep_times = (FULL_NOTE_TIME / split_note[note_time])*(1 + 0.5 * symbol_point);
        no_beep_times = beep_times;
        switch (performance_effect) {
            case 0: {
                beep_times = beep_times * NORAML_NOTE_SPACE;
                break;
            }
            case 1: {
                break;
            }
            case 2: {
                beep_times /= 2;
                break;
            }
            default:
                break;
        }
        if (freq == 0) {
            vol = 0;
        }
        no_beep_times -= beep_times;
        beep_set(vol, freq);
        rt_thread_mdelay(beep_times);
        beep_set(0, freq);
        rt_thread_mdelay(no_beep_times);
        pos += 2;
    } while (pos < length);
}

int main(void)
{
    init_beep_pwm_pins();

    return 0;
}

void play_music(void)
{
    beep_on();
    hpm_play((uint8_t *)&the_star_song, sizeof(the_star_song), MUSIC_VOICE);
    beep_off();
}
MSH_CMD_EXPORT(play_music, play music via pwm-driven beeper)
