/*
* 模块名称 : 步进电机对外API的数据类型
* 文件名称 : xxxxx.h
* 说    明 :
*
* 修改记录 :
*       版本号  日期        作者     说明
*
*/
#ifndef _BSP_FILTERMOTOR_API_TYPES_H_
#define _BSP_FILTERMOTOR_API_TYPES_H_


#include "GMtypes.h"


// 电机运动方向
typedef enum
{
    E_DIRECT_OPEN  = 0,
    E_DIRECT_CLOSE = 1,
}filtermotor_run_direct_t;

// 马达结构件方向
typedef enum
{
    E_DIRECT_LEFT  = 0, //马达丝印方向在左
    E_DIRECT_RIGHT = 1, //马达丝印方向在右
}filtermotor_structure_direct_t;


#endif
