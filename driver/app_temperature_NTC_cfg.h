/*
 * xxxxxx.h
 *
 * Created:
 *  Author:
 */
#ifndef __APP_TEMPERATURE_NTC_CFG_H__
#define __APP_TEMPERATURE_NTC_CFG_H__

#include "utils.h"
#include "bsp_adc.h"
#include "config.h"



// ================ configure(本文件内禁止修改) ===============

// NTC任务轮训周期
#define TEMP_CFG_TASK_POLL_MS                                190u

// NTC 系统（B灯），温度测量是否使用（0-不使用；1-使用）
#define NTC_CFG_LASER_IS_USE                                0
// NTC 环境，温度测量是否使用（0-不使用；1-使用）
#define NTC_CFG_ENV_IS_USE                                  0
// NTC DMD，温度测量是否使用（0-不使用；1-使用）
#define NTC_CFG_DMD_IS_USE                                  0
// NTC 色轮，温度测量是否使用（0-不使用；1-使用）
#define NTC_CFG_CW_IS_USE                                   0
// NTC G灯，温度测量是否使用（0-不使用；1-使用）
#define NTC_CFG_G_LED_IS_USE                                0
// NTC R灯，温度测量是否使用（0-不使用；1-使用）
#define NTC_CFG_R_LED_IS_USE                                0
// NTC BP灯，温度测量是否使用（0-不使用；1-使用）
#define NTC_CFG_BP_LED_IS_USE                               0
// NTC 驱动板，温度测量是否使用（0-不使用；1-使用）
#define NTC_CFG_BOARD_IS_USE                                0

// 配置：NTC ADC 测温通道
// laser(激光系统)
#define NTC_CFG_LASER_ADC_CHANNEL                           (ADC_CH_1_PA0)
// env(环境)
#define NTC_CFG_ENV_ADC_CHANNEL                             (ADC_CH_1_PA0)
// dmd(DMD)
#define NTC_CFG_DMD_ADC_CHANNEL                             (ADC_CH_1_PA0)
// cw(色轮)
#define NTC_CFG_CW_ADC_CHANNEL                              (ADC_CH_1_PA0)
// G_led(G灯)
#define NTC_CFG_G_LED_ADC_CHANNEL                           (ADC_CH_1_PA0)
// R_led(R灯)
#define NTC_CFG_R_LED_ADC_CHANNEL                           (ADC_CH_1_PA0)
// BP_led(BP灯)
#define NTC_CFG_BP_LED_ADC_CHANNEL                          (ADC_CH_1_PA0)
// 驱动板(boardADC_CH_14_PC3
#define NTC_CFG_BOARD_ADC_CHANNEL                          	(ADC_CH_1_PA0)

// 配置：ADC值转换为电压值系数(强制扩大1000倍，提高计算精度)，5000*(1000)/(2^10-1)
#define NTC_CFG_ADC2VOL_FACTOR                              (((uint32_t)1000)*5000/1023)

// 配置：NTC电压-温度表
#define NTC_CFG_LASER_VOL2TEMP_TABLE                        NULL

#define NTC_CFG_ENV_VOL2TEMP_TABLE                          NULL

#define NTC_CFG_DMD_VOL2TEMP_TABLE                          NULL

#define NTC_CFG_CW_VOL2TEMP_TABLE                           NULL

#define NTC_CFG_G_LED_VOL2TEMP_TABLE                        NULL

#define NTC_CFG_R_LED_VOL2TEMP_TABLE                        NULL

#define NTC_CFG_BP_LED_VOL2TEMP_TABLE                       NULL

#define NTC_CFG_BOARD_VOL2TEMP_TABLE                        NULL
// ==================== 包含不同项目的修改 ====================

#include "app_temperature_NTC_cfg_dabai.h"

#endif

