/*
* 模块名称 : 步进电机驱动参数配置（默认）
* 文件名称 : xxxxx.c
* 说     明 :
*
*/
#ifndef _BSP_STEPMOTOR_STEP_DRIVE_CFG_H_
#define _BSP_STEPMOTOR_STEP_DRIVE_CFG_H_

#include "n32g43x_start_pins.h"
#include "config.h"


//============= configure(本文件内禁止修改) ================
//整步控制必须配置IO
#define STEP_A1_CFG_GPIO_PORT                  GPIOB
#define STEP_A1_CFG_GPIO_PIN                   GPIO_PIN_4

#define STEP_A2_CFG_GPIO_PORT                  GPIOB
#define STEP_A2_CFG_GPIO_PIN                   GPIO_PIN_4

#define STEP_B1_CFG_GPIO_PORT                  GPIOB
#define STEP_B1_CFG_GPIO_PIN                   GPIO_PIN_4

#define STEP_B2_CFG_GPIO_PORT                  GPIOB
#define STEP_B2_CFG_GPIO_PIN                   GPIO_PIN_4


//马达运行相位拍数(4拍：整步，8拍：半步)
#define STEPMOTOR_PHASE_LEN                         (4)

//马达结构件方向
#define STEPMOTOR_STRUCTURE_DIRECT                  (E_DIRECT_LEFT)


// =================== 不同项目的参数配置 ==================
#ifndef CFG_PROJECT_ITEMS
    #error "CFG_PROJECT_ITEMS" undefined!
#endif

#if (CFG_PROJECT_ITEMS == 2)
    //#pragma message("bsp_stepmotor_soft_subdivision configure use niangao2")
    #include "bsp_stepmotor_step_drive_cfg_niangao2.h"
#else
    //#pragma message("bsp_stepmotor_soft_subdivision configure use default")
#endif




// ==================== 配置参数依赖检查 ===================




#endif
