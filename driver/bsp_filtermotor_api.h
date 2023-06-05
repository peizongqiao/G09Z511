/*
* 模块名称 : filter马达对外API
* 文件名称 : xxxxx.h
* 说    明 :
*
* 修改记录 :
*       版本号  日期        作者     说明
*
*/

#ifndef _BSP_FILTERMOTOR_API_H_
#define _BSP_FILTERMOTOR_API_H_


#include "GMtypes.h"
#include "bsp_filtermotor_api_types.h"
#include "config.h"





// ========================= 接口 ==========================
// 注意：1、接口使用函数封装而不是用宏定义封装，是为了在编译时可进行参数检查
//      2、此处声明的接口函数且是static，为了在实现接口时是在.h中，这样就可内联，节省ROM空间。
//

// 设备初始化
static void bsp_filtermotor_api_device_init(void);
// 电机转动控制
static void bsp_filtermotor_api_run(uint32_t pps, uint32_t step, filtermotor_run_direct_t direct);
// 电机制动控制
static void bsp_filtermotor_api_stop(void);



#include "bsp_filtermotor_soft_subdivision.h"





#endif
