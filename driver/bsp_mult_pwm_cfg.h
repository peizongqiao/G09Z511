#ifndef BSP_MULT_PWM_CFG_H_
#define BSP_MULT_PWM_CFG_H_


#include "GMtypes.h"
#include "config.h"

// ============= configure(本文件内禁止修改) ===============
// 配置：根据MCU，配置硬件时钟源频率Hz
#define MULT_PWM_CFG_SYS_CLK_H_TIM                    (MCU_CLK_HZ)
#define MULT_PWM_CFG_SYS_CLK_L_TIM                    (MCU_CLK_HZ/2)

#define MULT_PWM_CFG_DUTY_CYCLE_MAX             255u

// 配置：PWM波形频率(Hz)
#define MULT_PWM_CFG_DUTY_CYCLE_FREQUENCY_TIM2       (20*1000u)

#define MULT_PWM_CFG_DUTY_CYCLE_FREQUENCY_TIM3       (20*1000u)

#define MULT_PWM_CFG_DUTY_CYCLE_FREQUENCY_TIM4       (20*1000u)

#define MULT_PWM_CFG_DUTY_CYCLE_FREQUENCY_TIM8       (20*1000u)

#define MULT_PWM_CFG_DUTY_CYCLE_FREQUENCY_TIM9       (20*1000u)

#define PWM_TIM2_CH4_IS_USE                      0
#define PWM_TIM3_CH2_IS_USE                      0
#define PWM_TIM4_CH1_IS_USE                      0
#define PWM_TIM4_CH2_IS_USE                      0
#define PWM_TIM4_CH3_IS_USE                      0
#define PWM_TIM4_CH4_IS_USE                      0
#define PWM_TIM8_CH1_IS_USE                      0
#define PWM_TIM8_CH2_IS_USE                      0
#define PWM_TIM8_CH3_IS_USE                      0
#define PWM_TIM8_CH4_IS_USE                      0
#define PWM_TIM9_CH3_IS_USE                      0
#define PWM_TIM9_CH4_IS_USE                      0

#endif
