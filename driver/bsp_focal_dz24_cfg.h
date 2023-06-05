#ifndef BSP_FOCAL_DZ24_CFG_H_
#define BSP_FOCAL_DZ24_CFG_H_

#include "n32g43x.h"
#include "adc_basic.h"


/* 设置输出电平 */
#define FOCUS_A_H	              io_set_high(GPIOB, GPIO_PIN_1)
#define FOCUS_A_L	              io_set_low(GPIOB, GPIO_PIN_1)
#define FOCUS_B_H	              io_set_high(GPIOB, GPIO_PIN_2)
#define FOCUS_B_L	              io_set_low(GPIOB, GPIO_PIN_2)
#define FOCUS_C_H	              io_set_high(GPIOB, GPIO_PIN_10)
#define FOCUS_C_L	              io_set_low(GPIOB, GPIO_PIN_10)
#define FOCUS_D_H	              io_set_high(GPIOB, GPIO_PIN_12)
#define FOCUS_D_L	              io_set_low(GPIOB, GPIO_PIN_12)

#define ZOOM_A_H	              io_set_high(GPIOC, GPIO_PIN_10)
#define ZOOM_A_L	              io_set_low(GPIOC, GPIO_PIN_10)
#define ZOOM_B_H	              io_set_high(GPIOC, GPIO_PIN_11)
#define ZOOM_B_L	              io_set_low(GPIOC, GPIO_PIN_11)
#define ZOOM_C_H	              io_set_high(GPIOC, GPIO_PIN_12)
#define ZOOM_C_L	              io_set_low(GPIOC, GPIO_PIN_12)
#define ZOOM_D_H	              io_set_high(GPIOD, GPIO_PIN_2)
#define ZOOM_D_L	              io_set_low(GPIOD, GPIO_PIN_2)

#define filter_A_H	              io_set_high(GPIOC, GPIO_PIN_6)
#define filter_A_L	              io_set_low(GPIOC, GPIO_PIN_6)
#define filter_B_H	              io_set_high(GPIOC, GPIO_PIN_7)
#define filter_B_L	              io_set_low(GPIOC, GPIO_PIN_7)
#define filter_C_H	              io_set_high(GPIOC, GPIO_PIN_8)
#define filter_C_L	              io_set_low(GPIOC, GPIO_PIN_8)
#define filter_D_H	              io_set_high(GPIOC, GPIO_PIN_9)
#define filter_D_L	              io_set_low(GPIOC, GPIO_PIN_9)

/* PI到头检测 */
#define FOCIS_GEI_PI()            ADC_GetData(ADC_CH_2_PA1)
#define ZOOM_GEI_PI()             ADC_GetData(ADC_CH_3_PA2)
#define FILTER_GEI_PI()             ADC_GetData(ADC_CH_4_PA3)
#endif /* BSP_FOCAL_DZ24_CFG_H_ */
