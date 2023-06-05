#ifndef _BSP_ADC_H
#define _BSP_ADC_H

#include <stdio.h>
#include <stdint.h>
#include "bsp_adc_cfg.h"
#include "../driver/GMtypes.h"

#define ADC_CFG_IS_USE_AIN1            0    //PA0    
#define ADC_CFG_IS_USE_AIN2            0    //PA1
#define ADC_CFG_IS_USE_AIN3            0    //PA2
#define ADC_CFG_IS_USE_AIN4            0    //PA3
#define ADC_CFG_IS_USE_AIN5            0    //PA4
#define ADC_CFG_IS_USE_AIN6            0    //PA5
#define ADC_CFG_IS_USE_AIN7            0    //PA6
#define ADC_CFG_IS_USE_AIN8            0    //PA7
#define ADC_CFG_IS_USE_AIN9            0    //PB0
#define ADC_CFG_IS_USE_AIN10           0    //PB1
#define ADC_CFG_IS_USE_AIN11           0    //PC0
#define ADC_CFG_IS_USE_AIN12           0    //PC1
#define ADC_CFG_IS_USE_AIN13           0    //PC2
#define ADC_CFG_IS_USE_AIN14           0    //PC3
#define ADC_CFG_IS_USE_AIN15           0    //PC4
#define ADC_CFG_IS_USE_AIN16           0    //PC5

#include "bsp_adc_cfg_dabai.h"
#include "n32g43x.h"

void ADC_RCC_Configuration(void);
void ADC_GPIO_Configuration(void);
uint16_t ADC_GetData(uint8_t ADC_Channel);
void ADC_Initial(void);


void bsp_adc_init(void);
uint16_t bsp_adc_get_value_block(uint8_t channel);

#endif