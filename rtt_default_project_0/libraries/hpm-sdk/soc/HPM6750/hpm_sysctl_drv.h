/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_SYSCTL_DRV_H
#define HPM_SYSCTL_DRV_H

#include "hpm_common.h"
#include "hpm_sysctl_regs.h"

typedef enum {
    sysctl_retention_domain_sys = 0,
    sysctl_retention_domain_cpu0 = 2,
    sysctl_retention_domain_cpu1 = 4,
    sysctl_retention_domain_conn = 6,
    sysctl_retention_domain_vis = 8,
    sysctl_retention_domain_xtal24m = 10,
    sysctl_retention_domain_pll0 = 11,
    sysctl_retention_domain_pll1 = 12,
    sysctl_retention_domain_pll2 = 13,
    sysctl_retention_domain_pll3 = 14,
    sysctl_retention_domain_pll4 = 15,
} sysctl_retention_domain_t;

typedef enum {
    sysctl_preset_0 = 1 << 0,
    sysctl_preset_1 = 1 << 1,
    sysctl_preset_2 = 1 << 2,
    sysctl_preset_3 = 1 << 3,
} sysctl_preset_t;

typedef enum {
    sysctl_reset_domain_soc = 0,
    sysctl_reset_domain_con,
    sysctl_reset_domain_vis,
    sysctl_reset_domain_cpu0,
    sysctl_reset_domain_cpu1,
} sysctl_reset_domain_t;

typedef enum {
    sysctl_resource_cpu0 = 0,
    sysctl_resource_cpx0 = 1,
    sysctl_resource_exe0 = 2,
    sysctl_resource_wak0 = 3,
    sysctl_resource_cpu0_per = 4,
    sysctl_resource_cpu1 = 8,
    sysctl_resource_cpx1 = 9,
    sysctl_resource_exe1 = 10,
    sysctl_resource_wak1 = 11,
    sysctl_resource_cpu1_per = 12,
    sysctl_resource_logic0 = 16,
    sysctl_resource_logic1 = 17,
    sysctl_resource_logic2 = 18,
    sysctl_resource_logic3 = 19,
    sysctl_resource_pmic = 20,
    sysctl_resource_pow_con = 21,
    sysctl_resource_pow_vis = 22,
    sysctl_resource_pow_cpu0 = 23,
    sysctl_resource_pow_cpu1 = 24,
    sysctl_resource_rst_soc = 25,
    sysctl_resource_rst_con = 26,
    sysctl_resource_rst_vis = 27,
    sysctl_resource_rst_cpu0 = 28,
    sysctl_resource_rst_cpu1 = 29,
    sysctl_resource_xtal = 32,
    sysctl_resource_pll0 = 33,
    sysctl_resource_clk0_pll0 = 34,
    sysctl_resource_pll1 = 35,
    sysctl_resource_clk0_pll1 = 36,
    sysctl_resource_clk1_pll1 = 37,
    sysctl_resource_pll2 = 38,
    sysctl_resource_clk0_pll2 = 39,
    sysctl_resource_clk1_pll2 = 40,
    sysctl_resource_pll3 = 41,
    sysctl_resource_clk0_pll3 = 42,
    sysctl_resource_pll4 = 43,
    sysctl_resource_clk0_pll4 = 44,
    sysctl_resource_mbist_soc = 48,
    sysctl_resource_mbist_cpu = 49,
    sysctl_resource_mbist_cpu1 = 50,
    sysctl_resource_mbist_con = 51,
    sysctl_resource_mbist_vis = 52,
    sysctl_resource_clk_top_cpu0 = 64,
    sysctl_resource_clk_top_mchtmr0 = 65,
    sysctl_resource_clk_top_cpu1 = 66,
    sysctl_resource_clk_top_mchtmr1 = 67,
    sysctl_resource_clk_top_axi0 = 68,
    sysctl_resource_clk_top_axi1 = 69,
    sysctl_resource_clk_top_axi2 = 70,
    sysctl_resource_clk_top_ahb0 = 71,
    sysctl_resource_clk_top_dram = 72,
    sysctl_resource_clk_top_xpi0 = 73,
    sysctl_resource_clk_top_xpi1 = 74,
    sysctl_resource_clk_top_gptmr0 = 75,
    sysctl_resource_clk_top_gptmr1 = 76,
    sysctl_resource_clk_top_gptmr2 = 77,
    sysctl_resource_clk_top_gptmr3 = 78,
    sysctl_resource_clk_top_gptmr4 = 79,
    sysctl_resource_clk_top_gptmr5 = 80,
    sysctl_resource_clk_top_gptmr6 = 81,
    sysctl_resource_clk_top_gptmr7 = 82,
    sysctl_resource_clk_top_uart0 = 83,
    sysctl_resource_clk_top_uart1 = 84,
    sysctl_resource_clk_top_uart2 = 85,
    sysctl_resource_clk_top_uart3 = 86,
    sysctl_resource_clk_top_uart4 = 87,
    sysctl_resource_clk_top_uart5 = 88,
    sysctl_resource_clk_top_uart6 = 89,
    sysctl_resource_clk_top_uart7 = 90,
    sysctl_resource_clk_top_uart8 = 91,
    sysctl_resource_clk_top_uart9 = 92,
    sysctl_resource_clk_top_uarta = 93,
    sysctl_resource_clk_top_uartb = 94,
    sysctl_resource_clk_top_uartc = 95,
    sysctl_resource_clk_top_uartd = 96,
    sysctl_resource_clk_top_uarte = 97,
    sysctl_resource_clk_top_uartf = 98,
    sysctl_resource_clk_top_i2c0 = 99,
    sysctl_resource_clk_top_i2c1 = 100,
    sysctl_resource_clk_top_i2c2 = 101,
    sysctl_resource_clk_top_i2c3 = 102,
    sysctl_resource_clk_top_spi0 = 103,
    sysctl_resource_clk_top_spi1 = 104,
    sysctl_resource_clk_top_spi2 = 105,
    sysctl_resource_clk_top_spi3 = 106,
    sysctl_resource_clk_top_can0 = 107,
    sysctl_resource_clk_top_can1 = 108,
    sysctl_resource_clk_top_can2 = 109,
    sysctl_resource_clk_top_can3 = 110,
    sysctl_resource_clk_top_ptpc = 111,
    sysctl_resource_clk_top_ana0 = 112,
    sysctl_resource_clk_top_ana1 = 113,
    sysctl_resource_clk_top_ana2 = 114,
    sysctl_resource_clk_top_aud0 = 115,
    sysctl_resource_clk_top_aud1 = 116,
    sysctl_resource_clk_top_aud2 = 117,
    sysctl_resource_clk_top_dis0 = 118,
    sysctl_resource_clk_top_cam0 = 119,
    sysctl_resource_clk_top_cam1 = 120,
    sysctl_resource_clk_top_eth0 = 121,
    sysctl_resource_clk_top_eth1 = 122,
    sysctl_resource_clk_top_ptp0 = 123,
    sysctl_resource_clk_top_ptp1 = 124,
    sysctl_resource_clk_top_ref0 = 125,
    sysctl_resource_clk_top_ref1 = 126,
    sysctl_resource_clk_top_ntmr0 = 127,
    sysctl_resource_clk_top_ntmr1 = 128,
    sysctl_resource_clk_top_sdxc0 = 129,
    sysctl_resource_clk_top_sdxc1 = 130,
    sysctl_resource_clk_top_adc0 = 192,
    sysctl_resource_clk_top_adc1 = 193,
    sysctl_resource_clk_top_adc2 = 194,
    sysctl_resource_clk_top_adc3 = 195,
    sysctl_resource_clk_top_i2s0 = 196,
    sysctl_resource_clk_top_i2s1 = 197,
    sysctl_resource_clk_top_i2s2 = 198,
    sysctl_resource_clk_top_i2s3 = 199,

    sysctl_resource_linkable_start = 256,
    sysctl_resource_ahbp = 256,
    sysctl_resource_axis = 257,
    sysctl_resource_axic = 258,
    sysctl_resource_axiv = 259,
    sysctl_resource_dram = 260,
    sysctl_resource_rom0 = 261,
    sysctl_resource_lmm0 = 262,
    sysctl_resource_lmm1 = 263,
    sysctl_resource_mchtmr0 = 264,
    sysctl_resource_mchtmr1 = 265,
    sysctl_resource_ram0 = 266,
    sysctl_resource_ram1 = 267,
    sysctl_resource_xpi0 = 268,
    sysctl_resource_xpi1 = 269,
    sysctl_resource_sdp0 = 270,
    sysctl_resource_rng0 = 271,
    sysctl_resource_kman = 272,
    sysctl_resource_dma0 = 273,
    sysctl_resource_dma1 = 274,
    sysctl_resource_gpio = 275,
    sysctl_resource_mbx0 = 276,
    sysctl_resource_mbx1 = 277,
    sysctl_resource_wdg0 = 278,
    sysctl_resource_wdg1 = 279,
    sysctl_resource_wdg2 = 280,
    sysctl_resource_wdg3 = 281,
    sysctl_resource_gptmr0 = 282,
    sysctl_resource_gptmr1 = 283,
    sysctl_resource_gptmr2 = 284,
    sysctl_resource_gptmr3 = 285,
    sysctl_resource_gptmr4 = 286,
    sysctl_resource_gptmr5 = 287,
    sysctl_resource_gptmr6 = 288,
    sysctl_resource_gptmr7 = 289,
    sysctl_resource_uart0 = 290,
    sysctl_resource_uart1 = 291,
    sysctl_resource_uart2 = 292,
    sysctl_resource_uart3 = 293,
    sysctl_resource_uart4 = 294,
    sysctl_resource_uart5 = 295,
    sysctl_resource_uart6 = 296,
    sysctl_resource_uart7 = 297,
    sysctl_resource_uart8 = 298,
    sysctl_resource_uart9 = 299,
    sysctl_resource_uarta = 300,
    sysctl_resource_uartb = 301,
    sysctl_resource_uartc = 302,
    sysctl_resource_uartd = 303,
    sysctl_resource_uarte = 304,
    sysctl_resource_uartf = 305,
    sysctl_resource_i2c0 = 306,
    sysctl_resource_i2c1 = 307,
    sysctl_resource_i2c2 = 308,
    sysctl_resource_i2c3 = 309,
    sysctl_resource_spi0 = 310,
    sysctl_resource_spi1 = 311,
    sysctl_resource_spi2 = 312,
    sysctl_resource_spi3 = 313,
    sysctl_resource_can0 = 314,
    sysctl_resource_can1 = 315,
    sysctl_resource_can2 = 316,
    sysctl_resource_can3 = 317,
    sysctl_resource_ptpc = 318,
    sysctl_resource_adc0 = 319,
    sysctl_resource_adc1 = 320,
    sysctl_resource_adc2 = 321,
    sysctl_resource_adc3 = 322,
    sysctl_resource_acmp = 323,
    sysctl_resource_i2s0 = 324,
    sysctl_resource_i2s1 = 325,
    sysctl_resource_i2s2 = 326,
    sysctl_resource_i2s3 = 327,
    sysctl_resource_i2spdm0 = 328,
    sysctl_resource_i2sdao = 329,
    sysctl_resource_msyn = 330,
    sysctl_resource_mot0 = 331,
    sysctl_resource_mot1 = 332,
    sysctl_resource_mot2 = 333,
    sysctl_resource_mot3 = 334,
    sysctl_resource_dis0 = 335,
    sysctl_resource_cam0 = 336,
    sysctl_resource_cam1 = 337,
    sysctl_resource_jpeg = 338,
    sysctl_resource_pdma = 339,
    sysctl_resource_eth0 = 340,
    sysctl_resource_eth1 = 341,
    sysctl_resource_ntmr0 = 342,
    sysctl_resource_ntmr1 = 343,
    sysctl_resource_sdxc0 = 344,
    sysctl_resource_sdxc1 = 345,
    sysctl_resource_usb0 = 346,
    sysctl_resource_usb1 = 347,
    sysctl_resource_ref0 = 348,
    sysctl_resource_ref1 = 349,
    sysctl_resource_linkable_end,
    sysctl_resource_end = sysctl_resource_linkable_end,
} sysctl_resource_t;

typedef enum {
    sysctl_resource_mode_auto = 0,
    sysctl_resource_mode_force_on,
    sysctl_resource_mode_force_off,
} sysctl_resource_mode_t;

typedef enum {
    clock_node_cpu0 = 0,
    clock_node_mchtmr0 = 1,
    clock_node_cpu1 = 2,
    clock_node_mchtmr1 = 3,
    clock_node_axi0 = 4,
    clock_node_axi1 = 5,
    clock_node_axi2 = 6,
    clock_node_ahb0 = 7,
    clock_node_dram = 8,
    clock_node_xpi0 = 9,
    clock_node_xpi1 = 10,
    clock_node_gptmr0 = 11,
    clock_node_gptmr1 = 12,
    clock_node_gptmr2 = 13,
    clock_node_gptmr3 = 14,
    clock_node_gptmr4 = 15,
    clock_node_gptmr5 = 16,
    clock_node_gptmr6 = 17,
    clock_node_gptmr7 = 18,
    clock_node_uart0 = 19,
    clock_node_uart1 = 20,
    clock_node_uart2 = 21,
    clock_node_uart3 = 22,
    clock_node_uart4 = 23,
    clock_node_uart5 = 24,
    clock_node_uart6 = 25,
    clock_node_uart7 = 26,
    clock_node_uart8 = 27,
    clock_node_uart9 = 28,
    clock_node_uarta = 29,
    clock_node_uartb = 30,
    clock_node_uartc = 31,
    clock_node_uartd = 32,
    clock_node_uarte = 33,
    clock_node_uartf = 34,
    clock_node_i2c0 = 35,
    clock_node_i2c1 = 36,
    clock_node_i2c2 = 37,
    clock_node_i2c3 = 38,
    clock_node_spi0 = 39,
    clock_node_spi1 = 40,
    clock_node_spi2 = 41,
    clock_node_spi3 = 42,
    clock_node_can0 = 43,
    clock_node_can1 = 44,
    clock_node_can2 = 45,
    clock_node_can3 = 46,
    clock_node_ptpc = 47,
    clock_node_ana0 = 48,
    clock_node_ana1 = 49,
    clock_node_ana2 = 50,
    clock_node_aud0 = 51,
    clock_node_aud1 = 52,
    clock_node_aud2 = 53,
    clock_node_dis0 = 54,
    clock_node_cam0 = 55,
    clock_node_cam1 = 56,
    clock_node_eth0 = 57,
    clock_node_eth1 = 58,
    clock_node_ptp0 = 59,
    clock_node_ptp1 = 60,
    clock_node_ref0 = 61,
    clock_node_ref1 = 62,
    clock_node_ntmr0 = 63,
    clock_node_ntmr1 = 64,
    clock_node_sdxc0 = 65,
    clock_node_sdxc1 = 66,

    clock_node_adc_i2s_start,
    clock_node_adc0 = clock_node_adc_i2s_start,
    clock_node_adc1,
    clock_node_adc2,
    clock_node_adc3,

    clock_node_i2s0,
    clock_node_i2s1,
    clock_node_i2s2,
    clock_node_i2s3,
    clock_node_end,
} clock_node_t;

typedef enum {
    clock_source_osc0_clk0 = 0,
    clock_source_pll0_clk0 = 1,
    clock_source_pll1_clk0 = 2,
    clock_source_pll1_clk1 = 3,
    clock_source_pll2_clk0 = 4,
    clock_source_pll2_clk1 = 5,
    clock_source_pll3_clk0 = 6,
    clock_source_pll4_clk0 = 7,
    clock_source_general_source_end,
} clock_source_t;


typedef enum {
    clock_source_adc_i2s_ahb_clk = 0,
    clock_source_adc_ana0_clk = 1,
    clock_source_i2s_aud0_clk = 1,
    clock_source_adc_ana1_clk = 2,
    clock_source_i2s_aud1_clk = 2,
    clock_source_adc_ana2_clk = 3,
    clock_source_i2s_aud2_clk = 3,
    clock_source_adc_i2s_clk_end,
} clock_source_adc_i2s_t;

typedef enum {
    cpu_lp_mode_keep_cpu_clock = 0,
    cpu_lp_mode_stop_cpu_clock = 0x2,
    cpu_lp_mode_trigger_system_lp = 0x1,
} cpu_lp_mode_t;

typedef enum {
    monitor_target_clk_32k = 0,
    monitor_target_clk_irc24m = 1,
    monitor_target_clk_xtal_24m = 2,
    monitor_target_clk_usb0_phy = 3,
    monitor_target_clk_usb1_phy = 4,
    monitor_target_osc0_clk0 = 8,
    monitor_target_pll0_clk0 = 9,
    monitor_target_pll1_clk0 = 10,
    monitor_target_pll1_clk1 = 11,
    monitor_target_pll2_clk0 = 12,
    monitor_target_pll2_clk1 = 13,
    monitor_target_pll3_clk0 = 14,
    monitor_target_pll4_clk0 = 15,
    monitor_target_clk_top_cpu0 = 128,
    monitor_target_clk_top_mchtmr0 = 129,
    monitor_target_clk_top_cpu1 = 130,
    monitor_target_clk_top_mchtmr1 = 131,
    monitor_target_clk_top_axi0 = 132,
    monitor_target_clk_top_axi1 = 133,
    monitor_target_clk_top_axi2 = 134,
    monitor_target_clk_top_ahb0 = 135,
    monitor_target_clk_top_dram = 136,
    monitor_target_clk_top_xpi0 = 137,
    monitor_target_clk_top_xpi1 = 138,
    monitor_target_clk_top_gptmr0 = 139,
    monitor_target_clk_top_gptmr1 = 140,
    monitor_target_clk_top_gptmr2 = 141,
    monitor_target_clk_top_gptmr3 = 142,
    monitor_target_clk_top_gptmr4 = 143,
    monitor_target_clk_top_gptmr5 = 144,
    monitor_target_clk_top_gptmr6 = 145,
    monitor_target_clk_top_gptmr7 = 146,
    monitor_target_clk_top_uart0 = 147,
    monitor_target_clk_top_uart1 = 148,
    monitor_target_clk_top_uart2 = 149,
    monitor_target_clk_top_uart3 = 150,
    monitor_target_clk_top_uart4 = 151,
    monitor_target_clk_top_uart5 = 152,
    monitor_target_clk_top_uart6 = 153,
    monitor_target_clk_top_uart7 = 154,
    monitor_target_clk_top_uart8 = 155,
    monitor_target_clk_top_uart9 = 156,
    monitor_target_clk_top_uarta = 157,
    monitor_target_clk_top_uartb = 158,
    monitor_target_clk_top_uartc = 159,
    monitor_target_clk_top_uartd = 160,
    monitor_target_clk_top_uarte = 161,
    monitor_target_clk_top_uartf = 162,
    monitor_target_clk_top_i2c0 = 163,
    monitor_target_clk_top_i2c1 = 164,
    monitor_target_clk_top_i2c2 = 165,
    monitor_target_clk_top_i2c3 = 166,
    monitor_target_clk_top_spi0 = 167,
    monitor_target_clk_top_spi1 = 168,
    monitor_target_clk_top_spi2 = 169,
    monitor_target_clk_top_spi3 = 170,
    monitor_target_clk_top_can0 = 171,
    monitor_target_clk_top_can1 = 172,
    monitor_target_clk_top_can2 = 173,
    monitor_target_clk_top_can3 = 174,
    monitor_target_clk_top_ptpc = 175,
    monitor_target_clk_top_ana0 = 176,
    monitor_target_clk_top_ana1 = 177,
    monitor_target_clk_top_ana2 = 178,
    monitor_target_clk_top_aud0 = 179,
    monitor_target_clk_top_aud1 = 180,
    monitor_target_clk_top_aud2 = 181,
    monitor_target_clk_top_dis0 = 182,
    monitor_target_clk_top_cam0 = 183,
    monitor_target_clk_top_cam1 = 184,
    monitor_target_clk_top_eth0 = 185,
    monitor_target_clk_top_eth1 = 186,
    monitor_target_clk_top_ptp0 = 187,
    monitor_target_clk_top_ptp1 = 188,
    monitor_target_clk_top_ref0 = 189,
    monitor_target_clk_top_ref1 = 190,
    monitor_target_clk_top_ntmr0 = 191,
    monitor_target_clk_top_ntmr1 = 192,
    monitor_target_clk_top_sdxc0 = 193,
    monitor_target_clk_top_sdxc1 = 194,
} monitor_target_t;

typedef enum {
    monitor_work_mode_compare = 0,
    monitor_work_mode_record = 1,
} monitor_work_mode_t;

typedef enum {
    monitor_accuracy_1khz = 0,
    monitor_accuracy_1hz = 1,
} monitor_accuracy_t;

typedef enum {
    monitor_reference_32khz = 0,
    monitor_reference_24mhz = 1,
} monitor_reference_t;

typedef struct monitor_config {
    uint8_t divide_by;
    monitor_work_mode_t mode;
    monitor_accuracy_t accuracy;
    monitor_reference_t reference;
    monitor_target_t target;
    bool start_measure;
    bool enable_output;
    uint32_t high_limit;
    uint32_t low_limit;
} monitor_config_t;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * \fn sysctl_monitor_result_is_valid
 *
 * @param ptr SYSCTL_Type base address
 * @param monitor_index specific monitor instance to be used
 */
static inline bool sysctl_monitor_result_is_valid(SYSCTL_Type *ptr, uint8_t monitor_index)
{
    return SYSCTL_MONITOR_CONTROL_VALID_GET(ptr->MONITOR[monitor_index].CONTROL);
}

/*
 * \fn sysctl_monitor_get_current_result
 *
 * @param ptr SYSCTL_Type base address
 * @param monitor_index specific monitor instance to be used
 * @return value of monitor result measured
 */
static inline uint32_t sysctl_monitor_get_current_result(SYSCTL_Type *ptr,
                                                         uint8_t monitor_index)
{
    while(!sysctl_monitor_result_is_valid(ptr, monitor_index));
    return ptr->MONITOR[monitor_index].CURRENT;
}

/*
 * \fn sysctl_monitor_set_work_mode
 *
 * @param ptr SYSCTL_Type base address
 * @param monitor_index specific monitor instance to be used
 * @param mode monitor_work_mode_compare, monitor_work_mode_record
 */
static inline void sysctl_monitor_set_work_mode(SYSCTL_Type *ptr,
                                                uint8_t monitor_index,
                                                monitor_work_mode_t mode)
{
    ptr->MONITOR[monitor_index].CONTROL =
        (ptr->MONITOR[monitor_index].CONTROL & ~SYSCTL_MONITOR_CONTROL_MODE_MASK)
      | (SYSCTL_MONITOR_CONTROL_MODE_SET(mode));
}

/*
 * \fn sysctl_monitor_set_limit_low
 *
 * @param ptr SYSCTL_Type base address
 * @param monitor_index specific monitor instance to be used
 * @param limit measurement low limit
 */
static inline hpm_stat_t sysctl_monitor_set_limit_low(SYSCTL_Type *ptr,
                                                  uint8_t monitor_index,
                                                  uint32_t limit)
{
    if (ptr->MONITOR[monitor_index].CONTROL & SYSCTL_MONITOR_CONTROL_MODE_MASK) {
        return status_invalid_argument;
    }
    ptr->MONITOR[monitor_index].LOW_LIMIT = SYSCTL_MONITOR_LOW_LIMIT_FREQUENCY_SET(limit);
    return status_success;
}

/*
 * \fn sysctl_monitor_set_limit_high
 *
 * @param ptr SYSCTL_Type base address
 * @param monitor_index specific monitor instance to be used
 * @param limit measurement high limit
 */
static inline hpm_stat_t sysctl_monitor_set_limit_high(SYSCTL_Type *ptr,
                                                  uint8_t monitor_index,
                                                  uint32_t limit)
{
    if (ptr->MONITOR[monitor_index].CONTROL & SYSCTL_MONITOR_CONTROL_MODE_MASK) {
        return status_invalid_argument;
    }
    ptr->MONITOR[monitor_index].HIGH_LIMIT = SYSCTL_MONITOR_HIGH_LIMIT_FREQUENCY_SET(limit);
    return status_success;
}

/*
 * \fn sysctl_monitor_set_limit
 *
 * @param ptr SYSCTL_Type base address
 * @param monitor_index specific monitor instance to be used
 * @param limit_high measurement high limit
 * @param limit_low measurement low limit
 */
static inline hpm_stat_t sysctl_monitor_set_limit(SYSCTL_Type *ptr,
                                                  uint8_t monitor_index,
                                                  uint32_t limit_high,
                                                  uint32_t limit_low)
{
    if (ptr->MONITOR[monitor_index].CONTROL & SYSCTL_MONITOR_CONTROL_MODE_MASK) {
        return status_invalid_argument;
    }
    ptr->MONITOR[monitor_index].HIGH_LIMIT = SYSCTL_MONITOR_HIGH_LIMIT_FREQUENCY_SET(limit_high);
    ptr->MONITOR[monitor_index].LOW_LIMIT = SYSCTL_MONITOR_LOW_LIMIT_FREQUENCY_SET(limit_low);
    return status_success;
}

/*
 * \fn sysctl_monitor_get_limit_high
 *
 * @param ptr SYSCTL_Type base address
 * @param monitor_index specific monitor instance to be used
 * @return current high limit value
 */
static inline uint32_t sysctl_monitor_get_limit_high(SYSCTL_Type *ptr, uint32_t monitor_index)
{
    return SYSCTL_MONITOR_HIGH_LIMIT_FREQUENCY_GET(ptr->MONITOR[monitor_index].HIGH_LIMIT);
}

/*
 * \fn sysctl_monitor_get_limit_low
 *
 * @param ptr SYSCTL_Type base address
 * @param monitor_index specific monitor instance to be used
 * @return current low limit value
 */
static inline uint32_t sysctl_monitor_get_limit_low(SYSCTL_Type *ptr, uint32_t monitor_index)
{
    return SYSCTL_MONITOR_LOW_LIMIT_FREQUENCY_SET(ptr->MONITOR[monitor_index].LOW_LIMIT);
}

/*
 * \fn sysctl_monitor_measure_frequency
 *
 * @param ptr SYSCTL_Type base address
 * @param monitor_index specific monitor instance to be used
 * @param target monitor target to be measured
 * @param enable_output enable clock obs output
 * @return frequency of monitor target measured
 */
uint32_t sysctl_monitor_measure_frequency(SYSCTL_Type *ptr,
                                          uint8_t monitor_index,
                                          monitor_target_t target,
                                          bool enable_output);

/*
 * \fn sysctl_set_enable_cpu_affiliate
 *
 * @param ptr SYSCTL_Type base address
 * @param cpu_index cpu index to enable its own affiliated group
 */
static inline void sysctl_set_enable_cpu_affiliate(SYSCTL_Type *ptr, uint8_t cpu_index)
{
    ptr->AFFILIATE[cpu_index].SET = 1 << cpu_index;
}

/*
 * \fn sysctl_set
 *
 * @param ptr SYSCTL_Type base address
 * @return true if any resource is busy
 */
static inline void sysctl_set_disable_cpu_affiliate(SYSCTL_Type *ptr, uint8_t cpu_index)
{
    ptr->AFFILIATE[cpu_index].CLEAR = 1 << cpu_index;
}

/*
 * \fn sysctl_resource_any_is_busy
 *
 * @param ptr SYSCTL_Type base address
 * @return true if any resource is busy
 */
static inline bool sysctl_resource_any_is_busy(SYSCTL_Type *ptr)
{
    return ptr->RESOURCE[0] & SYSCTL_RESOURCE_GLB_BUSY_MASK;
}

/*
 * \fn sysctl_resource_target_is_busy
 *
 * @param ptr SYSCTL_Type base address
 * @param resource target resource index
 * @return true if target resource is busy
 */
static inline bool sysctl_resource_target_is_busy(SYSCTL_Type *ptr,
                                                  sysctl_resource_t resource)
{
    return ptr->RESOURCE[resource] & SYSCTL_RESOURCE_LOC_BUSY_MASK;
}

/*
 * \fn sysctl_resource_target_set_mode
 *
 * @param ptr SYSCTL_Type base address
 * @param resource target resource index
 * @param mode target resource mode 
 */
static inline void sysctl_resource_target_set_mode(SYSCTL_Type *ptr,
                                                   sysctl_resource_t resource,
                                                   sysctl_resource_mode_t mode)
{
    ptr->RESOURCE[resource] =
        (ptr->RESOURCE[resource] & ~SYSCTL_RESOURCE_MODE_MASK) |
        SYSCTL_RESOURCE_MODE_SET(mode);
}

/*
 * \fn sysctl_cpu_lp_clear_retention_with_mask
 *
 * @param ptr SYSCTL_Type base address
 * @param cpu_index cpu index
 * @param mask bit mask to clear
 */
static inline void sysctl_cpu_lp_clear_retention_with_mask(SYSCTL_Type *ptr,
                                                        uint8_t cpu_index,
                                                        uint32_t mask)
{
    ptr->RETENTION[cpu_index].CLEAR = mask;
}

/*
 * \fn sysctl_cpu_lp_set_retention_with_mask
 *
 * @param ptr SYSCTL_Type base address
 * @param cpu_index cpu index
 * @param mask bit mask to set
 */
static inline void sysctl_cpu_lp_set_retention_with_mask(SYSCTL_Type *ptr,
                                            uint8_t cpu_index,
                                            uint32_t mask)
{
    ptr->RETENTION[cpu_index].SET = mask;
}

/*
 * \fn sysctl_cpu_lp_retain_domain
 *
 * @param ptr SYSCTL_Type base address
 * @param cpu_index CPU index
 * @param domain target domain power to be retained
 * @param retain_mem set true to retain memory/register of target domain
 */
static inline void sysctl_cpu_lp_retain_domain(SYSCTL_Type *ptr,
                                               uint8_t cpu_index,
                                               sysctl_retention_domain_t domain,
                                               bool retain_mem)
{
    uint8_t set_mask = 0x1;
    if (domain < sysctl_retention_domain_xtal24m) {
        set_mask = retain_mem ? 0x3 : 0x1;
    }
    ptr->RETENTION[cpu_index].SET = (set_mask << domain);
}

/*
 * \fn sysctl_clock_any_is_busy
 *
 * @param ptr SYSCTL_Type base address
 * @return true if any clock is busy
 */
static inline bool sysctl_clock_any_is_busy(SYSCTL_Type *ptr)
{
    return ptr->CLOCK[0] & SYSCTL_CLOCK_GLB_BUSY_MASK;
}

/*
 * \fn sysctl_clock_target_is_busy
 *
 * @param ptr SYSCTL_Type base address
 * @param clock target clock
 * @return true if target clock is busy
 */
static inline bool sysctl_clock_target_is_busy(SYSCTL_Type *ptr,
                                               uint32_t clock)
{
    return ptr->CLOCK[clock] & SYSCTL_CLOCK_LOC_BUSY_MASK;
}

/*
 * \fn sysctl_clock_set_preset
 *
 * @param ptr SYSCTL_Type base address
 * @param preset preset
 */
static inline void sysctl_clock_set_preset(SYSCTL_Type *ptr,
                                           sysctl_preset_t preset)
{
    ptr->GLOBAL00 = (ptr->GLOBAL00 & ~SYSCTL_GLOBAL00_PRESET_MASK)
                | SYSCTL_GLOBAL00_PRESET_SET(preset);
}

/*
 * \fn sysctl_reset_check_target_domain_wakeup_flag
 *
 * @param ptr SYSCTL_Type base address
 * @param domain target domain to be checked 
 * @return true if target domain was taken wakeup reset
 */
static inline bool sysctl_reset_check_target_domain_wakeup_flag(SYSCTL_Type *ptr,
                                                                sysctl_reset_domain_t domain)
{
    return ptr->RESET[domain].CONTROL & SYSCTL_RESET_CONTROL_FLAG_WAKE_MASK;
}

/*
 * \fn sysctl_reset_clear_target_domain_wakeup_flag
 *
 * @param ptr SYSCTL_Type base address
 * @param domain target domain to be checked 
 */
static inline void sysctl_reset_clear_target_domain_wakeup_flag(SYSCTL_Type *ptr,
                                                                sysctl_reset_domain_t domain)
{
    ptr->RESET[domain].CONTROL |= SYSCTL_RESET_CONTROL_FLAG_WAKE_MASK;
}

/*
 * \fn sysctl_reset_check_target_domain_flag
 *
 * @param ptr SYSCTL_Type base address
 * @param domain target domain to be checked 
 * @return true if target domain was taken reset
 */
static inline bool sysctl_reset_check_target_domain_flag(SYSCTL_Type *ptr,
                                                         sysctl_reset_domain_t domain)
{
    return ptr->RESET[domain].CONTROL & SYSCTL_RESET_CONTROL_FLAG_MASK;
}

/*
 * \fn sysctl_reset_clear_target_domain_flag
 *
 * @param ptr SYSCTL_Type base address
 * @param domain target domain to be checked 
 */
static inline void sysctl_reset_clear_target_domain_flag(SYSCTL_Type *ptr,
                                                         sysctl_reset_domain_t domain)
{
    ptr->RESET[domain].CONTROL |= SYSCTL_RESET_CONTROL_FLAG_MASK;
}

/*
 * \fn sysctl_reset_clear_target_domain_all_flags
 *
 * @param ptr SYSCTL_Type base address
 * @param domain target domain to be checked 
 */
static inline void sysctl_reset_clear_target_domain_all_flags(SYSCTL_Type *ptr,
                                                              sysctl_reset_domain_t domain)
{
    ptr->RESET[domain].CONTROL |= SYSCTL_RESET_CONTROL_FLAG_MASK | SYSCTL_RESET_CONTROL_FLAG_WAKE_MASK;
}

/*
 * \fn sysctl_get_wakeup_source_status
 * @param ptr SYSCTL_Type base address
 * @param cpu_index CPU index
 * @param status_index wakeup status index 0 - 7
 * @return wakeup status
 */
static inline uint32_t sysctl_get_wakeup_source_status(SYSCTL_Type *ptr,
                                                       uint8_t cpu_index,
                                                       uint8_t status_index)
{
    return ptr->CPU[cpu_index].WAKEUP_STATUS[status_index];
}

/*
 * \fn sysctl_check_wakeup_source_status_with_mask
 *
 * @param ptr SYSCTL_Type base address
 * @param cpu_index CPU index
 * @param status_index wakeup status index 0 - 7
 * @param mask expected status mask in 32-bit
 * @return wakeup status AND given bit mask
 */
static inline
    uint32_t sysctl_check_wakeup_source_status_with_mask(SYSCTL_Type *ptr,
                                                         uint8_t cpu_index,
                                                         uint8_t status_index,
                                                         uint32_t mask)
{
    return ptr->CPU[cpu_index].WAKEUP_STATUS[status_index] & mask;
}

/*
 * \fn sysctl_enable_wakeup_source_status_with_mask
 *
 * @param ptr SYSCTL_Type base address
 * @param cpu_index CPU index
 * @param enable_index wakeup enable index 0 - 7
 * @param mask expected status mask in 32-bit
 */
static inline
    void sysctl_enable_wakeup_source_with_mask(SYSCTL_Type *ptr,
                                               uint8_t cpu_index,
                                               uint8_t enable_index,
                                               uint32_t mask)
{
    ptr->CPU[cpu_index].WAKEUP_ENABLE[enable_index] |= mask;
}

/*
 * \fn sysctl_disable_wakeup_source_status_with_mask
 *
 * @param ptr SYSCTL_Type base address
 * @param cpu_index CPU index
 * @param enable_index wakeup enable index 0 - 7
 * @param mask expected status mask in 32-bit
 */
static inline
    void sysctl_disable_wakeup_source_with_mask(SYSCTL_Type *ptr,
                                                uint8_t cpu_index,
                                                uint8_t enable_index,
                                                uint32_t mask)
{
    ptr->CPU[cpu_index].WAKEUP_ENABLE[enable_index] &= ~mask;
}

/*
 * \fn sysctl_disable_wakeup_source_status_with_irq
 *
 * @param ptr SYSCTL_Type base address
 * @param cpu_index CPU index
 * @param irq_num irq number to be set as wakeup source
 */
static inline void sysctl_disable_wakeup_source_with_irq(SYSCTL_Type *ptr,
                                                         uint8_t cpu_index,
                                                         uint16_t irq_num)
{
    ptr->CPU[cpu_index].WAKEUP_ENABLE[irq_num >> 2] &= ~(1UL << (irq_num % 32));
}

/*
 * \fn sysctl_enable_wakeup_source_status_with_irq
 *
 * @param ptr SYSCTL_Type base address
 * @param cpu_index CPU index
 * @param irq_num irq number to be set as wakeup source
 */
static inline void sysctl_enable_wakeup_source_with_irq(SYSCTL_Type *ptr,
                                                        uint8_t cpu_index,
                                                        uint16_t irq_num)
{
    ptr->CPU[cpu_index].WAKEUP_ENABLE[irq_num / 32] |= 1UL << (irq_num % 32);
}

/*
 * \fn sysctl_cpu0_lock_gpr_with_mask
 *
 * @param ptr SYSCTL_Type base address
 * @param gpr_mask bit mask of gpr registers to be locked
 */
static inline void sysctl_cpu0_lock_gpr_with_mask(SYSCTL_Type *ptr,
                                                 uint16_t gpr_mask)
{
    ptr->CPU[0].LOCK |= SYSCTL_CPU_LOCK_GPR_SET(gpr_mask);
}

/*
 * \fn sysctl_cpu1_lock_gpr_with_mask
 *
 * @param ptr SYSCTL_Type base address
 * @param gpr_mask bit mask of gpr registers to be locked
 */
static inline void sysctl_cpu1_lock_gpr_with_mask(SYSCTL_Type *ptr,
                                                 uint16_t gpr_mask)
{
    ptr->CPU[1].LOCK |= SYSCTL_CPU_LOCK_GPR_SET(gpr_mask);
}

/*
 * \fn sysctl_cpu0_lock
 *
 * @param ptr SYSCTL_Type base address
 */
static inline void sysctl_cpu0_lock(SYSCTL_Type *ptr)
{
    ptr->CPU[0].LOCK |= SYSCTL_CPU_LOCK_LOCK_MASK;
}

/*
 * \fn sysctl_cpu1_lock
 *
 * @param ptr SYSCTL_Type base address
 */
static inline void sysctl_cpu1_lock(SYSCTL_Type *ptr)
{
    ptr->CPU[1].LOCK |= SYSCTL_CPU_LOCK_LOCK_MASK;
}

/*
 * \fn sysctl_config_clock
 *
 * @param ptr SYSCTL_Type base address
 * @param node clock node to be configured
 * @param source clock source to be used
 * @param divide_by clock frequency divider
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_config_clock(SYSCTL_Type *ptr,
                               clock_node_t node,
                               clock_source_t source,
                               uint32_t divide_by);

/*
 * \fn sysctl_set_adc_i2s_clock_mux
 *
 * @param ptr SYSCTL_Type base address
 * @param node clock node to be configured
 * @param source clock source to be used
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_set_adc_i2s_clock_mux(SYSCTL_Type *ptr,
                                        clock_node_t node,
                                        clock_source_adc_i2s_t source);

/*
 * \fn sysctl_cpu_set_lp_mode
 *
 * @param ptr SYSCTL_Type base address
 * @param cpu_index cpu index
 * @param mode target mode to set
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_cpu_set_lp_mode(SYSCTL_Type *ptr,
                                  uint8_t cpu_index,
                                  cpu_lp_mode_t mode);

/*
 * \fn sysctl_enable_group_resource
 *
 * @param ptr SYSCTL_Type base address
 * @param group target group to be modified
 * @param resource target resource to be added/removed from group 
 * @param enable set true to add resource, remove otherwise
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_enable_group_resource(SYSCTL_Type *ptr,
                                        uint8_t group,
                                        sysctl_resource_t resource,
                                        bool enable);
/*
 * \fn sysctl_add_resource_to_cpu0
 *
 * @param ptr SYSCTL_Type base address
 * @param resource resource to be added to cpu0
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_add_resource_to_cpu0(SYSCTL_Type *ptr, sysctl_resource_t resource);

/*
 * \fn sysctl_remove_resource_from_cpu0
 *
 * @param ptr SYSCTL_Type base address
 * @param resource resource to be removed to cpu0
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_remove_resource_from_cpu0(SYSCTL_Type *ptr, sysctl_resource_t resource);

/*
 * \fn sysctl_add_resource_to_cpu1
 *
 * @param ptr SYSCTL_Type base address
 * @param resource resource to be added to cpu0
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_add_resource_to_cpu1(SYSCTL_Type *ptr, sysctl_resource_t resource);

/*
 * \fn sysctl_remove_resource_from_cpu1
 *
 * @param ptr SYSCTL_Type base address
 * @param resource resource to be removed to cpu0
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_remove_resource_from_cpu1(SYSCTL_Type *ptr, sysctl_resource_t resource);

/*
 * \fn sysctl_monitor_get_default_config
 *
 * @param ptr SYSCTL_Type base address
 * @param config monitor config structure pointer
 */
void sysctl_monitor_get_default_config(SYSCTL_Type *ptr, monitor_config_t *config); 

/*
 * \fn sysctl_monitor_init
 *
 * @param ptr SYSCTL_Type base address
 * @param monitor_index monitor instance to be initialized
 * @param config monitor config structure pointer
 */
void sysctl_monitor_init(SYSCTL_Type *ptr,
                         uint8_t monitor_index,
                         monitor_config_t *config);

/*
 * \fn sysctl_cpu0_set_gpr
 * \brief get data saved in GPR starting from given index
 *
 * @param ptr SYSCTL_Type base address
 * @param start start GPR index
 * @param count number of GPR registers to set
 * @param data pointer to data buffer
 * @param lock set true to lock written GPR registers after setting
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_cpu0_set_gpr(SYSCTL_Type *ptr,
                               uint8_t start,
                               uint8_t count,
                               uint32_t *data,
                               bool lock);

/*
 * \fn sysctl_cpu0_get_gpr
 * \brief set data to GPR starting from given index
 *
 * @param ptr SYSCTL_Type base address
 * @param start start GPR index
 * @param count number of GPR registers to set
 * @param data pointer of buffer to save data
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_cpu0_get_gpr(SYSCTL_Type *ptr,
                               uint8_t start,
                               uint8_t count,
                               uint32_t *data);

/*
 * \fn sysctl_cpu1_set_gpr
 * \brief set data to GPR starting from given index
 *
 * @param ptr SYSCTL_Type base address
 * @param start start GPR index
 * @param count number of GPR registers to set
 * @param data pointer to data buffer
 * @param lock set true to lock written GPR registers after setting
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_cpu1_set_gpr(SYSCTL_Type *ptr,
                               uint8_t start,
                               uint8_t count,
                               uint32_t *data,
                               bool lock);

/*
 * \fn sysctl_cpu1_get_gpr
 * \brief get data saved in GPR starting from given index
 *
 * @param ptr SYSCTL_Type base address
 * @param start start GPR index
 * @param count number of GPR registers to set
 * @param data pointer of buffer to save data
 * @return status_success if everything is okay
 */
hpm_stat_t sysctl_get_cpu1_gpr(SYSCTL_Type *ptr,
                               uint8_t start,
                               uint8_t count,
                               uint32_t *data);
/*
 * \fn sysctl_release_cpu1
 * \brief release cpu1
 *
 * @param ptr SYSCTL_Type base address
 */
void sysctl_release_cpu1(SYSCTL_Type *ptr);

/*
 * \fn sysctl_set_cpu0_wakeup_entry
 * \brief set entry point on cpu0 wakeup
 *
 * @param ptr SYSCTL_Type base address
 * @param entry entry for cpu0 on its wakeup
 */
hpm_stat_t sysctl_set_cpu0_wakeup_entry(SYSCTL_Type *ptr, uint32_t entry);

/*
 * \fn sysctl_set_cpu1_entry
 * \brief set entry point on either cpu1 boot or wakeup
 *
 * @param ptr SYSCTL_Type base address
 * @param entry entry for cpu0 on its wakeup
 */
hpm_stat_t sysctl_set_cpu1_entry(SYSCTL_Type *ptr, uint32_t entry);

#ifdef __cplusplus
}
#endif
#endif /* HPM_SYSCTL_DRV_H */
