#include "bsp_mult_pwm.h"
#include "N32G43x_Start.h"
#include "app_log.h"
#include "bsp_mult_pwm_cfg.h"
#include "app_softtimer.h"

uint16_t TIMx_pwm;
uint16_t TIM4_change = 0,TIM2_change = 0;

void motol_pwm_change(void)
{
    uint16_t ChannelPulse = 0;
	if(TIM4_change != 0 && TIM2_change == 0)
	{
		ChannelPulse = (uint16_t)(((uint32_t)TIMx_pwm * (200 - 1)) / 100);
		switch(TIM4_change)
		{
		    case 0x01:
			    TIM4->CCDAT1 = ChannelPulse;
			break;
			case 0x02:
				TIM4->CCDAT2 = ChannelPulse;
			break;
			case 0x03:
				TIM4->CCDAT3 = ChannelPulse;
			break;
			case 0x04:
				TIM4->CCDAT4 = ChannelPulse;
			break;
			default:
    break;
		}
		TIM4_change = 0;
	}
	else if(0x80 == TIM2_change)
	{
		ChannelPulse = (uint16_t)(((uint32_t)(100 - TIMx_pwm) * (200 - 1)) / 100);
		TIM2->CCDAT4 = ChannelPulse;
		TIM2_change = 0;
	}
	else{;}
}

void bsp_pwm_init(void)
{
	PWM_TIME();
	PWM_FAN_5();
	PWM_FAN1_4();
	PWM_FAN_1();
}

void bsp_pwm_set_dutycycle_TIM1_8(pwm_channel_t channel, uint8_t dutycycle)
{
    if (dutycycle > MULT_PWM_CFG_DUTY_CYCLE_MAX) {
        dutycycle = MULT_PWM_CFG_DUTY_CYCLE_MAX;
    }
		
    dutycycle = (((uint32_t)dutycycle)*108)/50;

    switch(channel)
    {
        case PWM_CHANNEL_TIM8_CH1:
            if (0 == dutycycle) {
                TIM8->CCDAT1 = 0;
            } else {
                TIM8->CCDAT1 = dutycycle;
            }
        break;

        case PWM_CHANNEL_TIM8_CH2:
            if (0 == dutycycle) {
                TIM8->CCDAT2 = 0;
            } else {
                TIM8->CCDAT2 = dutycycle;
            }
        break;

        case PWM_CHANNEL_TIM8_CH3:
            if (0 == dutycycle) {
                TIM8->CCDAT3 = 0;
            } else {
                TIM8->CCDAT3 = dutycycle;
            }
        break;

        case PWM_CHANNEL_TIM8_CH4:
            if (0 == dutycycle) {
                TIM8->CCDAT4 = 0;
            } else {
                TIM8->CCDAT4 = dutycycle;
            }
        break;
        
        default:break;
    }
}



