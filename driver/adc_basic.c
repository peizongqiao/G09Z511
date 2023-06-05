#include "../driver/adc_basic.h"
#include "../driver/driver_init.h"
//#include "config.h"
#include "app_log.h"
#include "../driver/bsp_adc.h"

ADC_InitType ADC_InitStructure;
GPIO_InitType ADC_GPIO_InitStructure;

void ADC_RCC_Configuration(void)
{
		
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOC, ENABLE);
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC, ENABLE);

    /* RCC_ADCHCLK_DIV16*/
    ADC_ConfigClk(ADC_CTRL3_CKMOD_AHB, RCC_ADCHCLK_DIV16);
    RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI , RCC_ADC1MCLK_DIV8); 
}

void ADC_GPIO_Configuration(void)
{
	GPIO_InitType GPIO_InitStructure;
    GPIO_InitStruct(&ADC_GPIO_InitStructure);
    /* Configure GPIO as analog input -------------------------*/
    ADC_GPIO_InitStructure.Pin       = GPIO_PIN_0;
    ADC_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Analog;
    GPIO_InitPeripheral(GPIOA, &ADC_GPIO_InitStructure);

	ADC_GPIO_InitStructure.Pin       = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4;
    ADC_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Analog;
    GPIO_InitPeripheral(GPIOC, &ADC_GPIO_InitStructure);
	
		ADC_GPIO_InitStructure.Pin       = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    ADC_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Analog;
    GPIO_InitPeripheral(GPIOA, &ADC_GPIO_InitStructure);
}
uint16_t ADC_GetData(uint8_t ADC_Channel)
{
    uint16_t dat;

    ADC_ConfigRegularChannel(ADC, ADC_Channel, 1, ADC_SAMP_TIME_55CYCLES5);
    /* Start ADC Software Conversion */
    ADC_EnableSoftwareStartConv(ADC,ENABLE);
    while(ADC_GetFlagStatus(ADC,ADC_FLAG_ENDC)==0){
    }
    ADC_ClearFlag(ADC,ADC_FLAG_ENDC);
    ADC_ClearFlag(ADC,ADC_FLAG_STR);
    dat=ADC_GetDat(ADC);
    return dat;
}

void ADC_Initial(void)
{
    /* ADC configuration ------------------------------------------------------*/
    ADC_InitStructure.MultiChEn      = DISABLE;
    ADC_InitStructure.ContinueConvEn = DISABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIGCONV_NONE;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = 1;
    ADC_Init(ADC, &ADC_InitStructure);
		
		ADC_SetConvResultBitNum(ADC,ADC_RST_BIT_10);
		
    /* Enable ADC */
    ADC_Enable(ADC, ENABLE);
    /* Check ADC Ready */

    while(ADC_GetFlagStatusNew(ADC,ADC_FLAG_RDY) == RESET)
        ;
    /* Start ADC1 calibration */
	
    ADC_StartCalibration(ADC);
    /* Check the end of ADC1 calibration */
    while (ADC_GetCalibrationStatus(ADC))
        ;
	
}