/*
 * @Author: raijin.long raijin.long@xgimi.com
 * @Date: 2022-08-09 13:52:09
 * @LastEditors: raijin.long raijin.long@xgimi.com
 * @LastEditTime: 2022-08-09 13:51:23
 * @FilePath: \Attiny1616_3217_APP\Attiny1616_3217_APP\Drivers\BSP\stepmotor\bsp_stepmotor_soft_subdivision_cfg_niangao.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*
* 模块名称 : 步进电机驱动参数配置（DABAI项目类型）
* 文件名称 : xxxxx.c
* 说     明 :
*
*/
#ifndef _BSP_STEPMOTOR_STEP_DRIVE_CFG_NIANGAO2_H_
#define _BSP_STEPMOTOR_STEP_DRIVE_CFG_NIANGAO2_H_

#include "n32g43x_start_pins.h"


//======================= configure ========================

//整步控制必须配置IO
#undef  STEP_A1_CFG_GPIO_PORT
#define STEP_A1_CFG_GPIO_PORT                  GPIOC

#undef  STEP_A1_CFG_GPIO_PIN
#define STEP_A1_CFG_GPIO_PIN                   GPIO_PIN_6

#undef  STEP_A2_CFG_GPIO_PORT
#define STEP_A2_CFG_GPIO_PORT                  GPIOC

#undef  STEP_A2_CFG_GPIO_PIN
#define STEP_A2_CFG_GPIO_PIN                   GPIO_PIN_7

#undef  STEP_B1_CFG_GPIO_PORT
#define STEP_B1_CFG_GPIO_PORT                  GPIOC

#undef  STEP_B1_CFG_GPIO_PIN
#define STEP_B1_CFG_GPIO_PIN                   GPIO_PIN_8

#undef  STEP_B2_CFG_GPIO_PORT
#define STEP_B2_CFG_GPIO_PORT                  GPIOC

#undef  STEP_B2_CFG_GPIO_PIN
#define STEP_B2_CFG_GPIO_PIN                   GPIO_PIN_9


//马达运行相位拍数(4拍：整步，8拍：半步)
#undef  STEPMOTOR_PHASE_LEN
#define STEPMOTOR_PHASE_LEN                         (4)

//马达结构件方向
#undef  STEPMOTOR_STRUCTURE_DIRECT
#define STEPMOTOR_STRUCTURE_DIRECT                  (E_DIRECT_LEFT)






#endif
