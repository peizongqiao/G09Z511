#ifndef ADC_BASIC_H_INCLUDED
#define ADC_BASIC_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g43x.h"

void ADC_RCC_Configuration(void);
void ADC_GPIO_Configuration(void);
uint16_t ADC_GetData(uint8_t ADC_Channel);
void ADC_Initial(void);


#ifdef __cplusplus
}
#endif

#endif /* ADC_BASIC_H_INCLUDED */