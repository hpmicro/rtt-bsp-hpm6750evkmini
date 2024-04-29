/*
 * Copyright (c) 2022-2023 HPMicro
 *
 * Change Logs:
 * Date         Author          Notes
 * 2024-04-06   will        first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "rtt_board.h"
#include "board.h"

#define PWM_DEV_NAME        BOARD_PWM_NAME  /* PWM name */
#define PWM_DEV_CHANNEL     BOARD_PWM_CHANNEL

#define PWM_PERIOD  (500000)    /* 0.5ms */
#define PWM_DUTY_STEP   (5000)  /* 5us */

struct rt_device_pwm *pwm_dev;      /* PWM device */

int main(void)
{
    return 0;
}

static int pwm_sample(int argc, char *argv[])
{
    rt_uint32_t period, pulse, dir;

    period = PWM_PERIOD;
    dir = 1;
    pulse = 0;

    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        return RT_ERROR;
    }
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);

    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);

    while (1)
    {
        rt_thread_mdelay(50);
        if (dir)
        {
            pulse += PWM_DUTY_STEP;
        }
        else
        {
            pulse -= PWM_DUTY_STEP;
        }
        if (pulse >= period)
        {
            dir = 0;
        }
        if (0 == pulse)
        {
            dir = 1;
        }

        rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    }
}

MSH_CMD_EXPORT(pwm_sample, pwm sample);
