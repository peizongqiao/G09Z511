#ifndef PWM_BASIC_H_INCLUDED
#define PWM_BASIC_H_INCLUDED

#include "N32G43x_Start.h"

#ifdef __cplusplus
extern "C" {
#endif

void PWM_RCC_Configuration(TIM_Module* TIMx);
void PWM_GPIO_Configuration(TIM_Module* TIMx);
void PWM_Init_TIMEBASE(TIM_Module* TIMx,uint8_t FREQUENCY);
void PWM_Init_OCInit(TIM_Module* TIMx);

#ifdef __cplusplus
}
#endif

#endif /* PWM_BASIC_H_INCLUDED */