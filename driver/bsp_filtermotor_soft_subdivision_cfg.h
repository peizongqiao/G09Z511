/*
* 模块名称 : 步进电机驱动参数配置（默认）
* 文件名称 : xxxxx.c
* 说     明 :
*
*/
#ifndef BSP_FILTERMOTOR_SOFT_SUBDIVISION_CFG_H_
#define BSP_FILTERMOTOR_SOFT_SUBDIVISION_CFG_H_

//#include "port.h"
#include "n32g43x_start_pins.h"
#include "config.h"
#include "adc_basic.h"


//============= configure(本文件内禁止修改) ================
//软仿细分必须配置PWM输出控制，注意同步配置PWM模块
#define FILTERMOTOR_INT_A_CHANNEL                     (PWM_CHANNEL_TIM2_CH2)
#define FILTERMOTOR_INT_B_CHANNEL                     (PWM_CHANNEL_TIM2_CH1)
#define FILTERMOTOR_INT_C_CHANNEL                     (PWM_CHANNEL_TIM2_CH3)
#define FILTERMOTOR_INT_D_CHANNEL                     (PWM_CHANNEL_TIM2_CH4)

//软仿细分等级（目前仅实现4、8、16）
#define FILTERMOTOR_SOFT_SUBDIVISION_LEVEL            (4)

//马达结构件方向
#define FILTERMOTOR_STRUCTURE_DIRECT                  (E_DIRECT_RIGHT)

#include "bsp_filtermotor_soft_subdivision_cfg_dabai.h"



// ==================== 配置参数依赖检查 ===================




#endif
