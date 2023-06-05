#include "../driver/bsp_adc.h"
//#include "../driver/driver_init.h"
//#include "N32G43x_Start.h"
//#include "config.h"
#include "app_log.h"
#include "../driver/adc_basic.h"

void bsp_adc_init()
{
        ADC_RCC_Configuration();
	
		ADC_GPIO_Configuration();  
	
		ADC_Initial();
}

uint16_t bsp_adc_get_value_block(uint8_t ADC_Channel)
{
    uint16_t i = 0;
    #define ADC_BLOCK_CONVERSION_TIMEOUT_US         1000u
		ADC_ConfigRegularChannel(ADC, ADC_Channel, 1, ADC_SAMP_TIME_55CYCLES5);
		ADC_EnableSoftwareStartConv(ADC,ENABLE);
	
    while(i++ < ADC_BLOCK_CONVERSION_TIMEOUT_US) {
        if (ADC_GetFlagStatus(ADC,ADC_FLAG_ENDC)!=0) {
            break;
        }
    }
    if(i >= ADC_BLOCK_CONVERSION_TIMEOUT_US) {
        return 0;
    }
    uint16_t res;
		ADC_ClearFlag(ADC,ADC_FLAG_ENDC);
    ADC_ClearFlag(ADC,ADC_FLAG_STR);
		
    res = ADC_GetDat(ADC);
		
    return res;
}

