#ifndef _BSP_MULT_PWM_H_
#define _BSP_MULT_PWM_H_

#include "n32g43x.h"

#define PWM_CHANNEL_NOTHING                      0
#define PWM_CHANNEL_TIM2_CH4                     1        // PWMͨ��0
#define PWM_CHANNEL_TIM3_CH2                     2        // PWMͨ��1
#define PWM_CHANNEL_TIM4_CH1                     3        // PWMͨ��2
#define PWM_CHANNEL_TIM4_CH2                     4        // PWMͨ��3
#define PWM_CHANNEL_TIM4_CH3                     5        // PWMͨ��4
#define PWM_CHANNEL_TIM4_CH4                     6        // PWMͨ��5
#define PWM_CHANNEL_TIM8_CH1                     7        // PWMͨ��5
#define PWM_CHANNEL_TIM8_CH2                     8        // PWMͨ��5
#define PWM_CHANNEL_TIM8_CH3                     9        // PWMͨ��5
#define PWM_CHANNEL_TIM8_CH4                     10       // PWMͨ��5
#define PWM_CHANNEL_TIM9_CH3                     11       // PWMͨ��5
#define PWM_CHANNEL_TIM9_CH4                     12       // PWMͨ��5

typedef uint8_t pwm_channel_t;

void bsp_pwm_init(void);

void bsp_pwm_TIM2_init(void);
void bsp_pwm_TIM3_init(void);
void bsp_pwm_TIM4_init(void);
void bsp_pwm_TIM8_init(void);
void bsp_pwm_TIM9_init(void);
void PWM_TIME(void);
void PWM_FAN_5(void);
void PWM_FAN1_4(void);
void PWM_FAN_1(void);
void PWM_BLED(void);
void pwm_filter();
//void bsp_pwm_TIM3_init();
void bsp_pwm_set_dutycycle(pwm_channel_t channel, uint8_t dutycycle);
void bsp_pwm_set_dutycycle_TIM1_8(pwm_channel_t channel, uint8_t dutycycle);
#endif /* _BSP_MULT_PWM_H_ */
