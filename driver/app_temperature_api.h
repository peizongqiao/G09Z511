/*
 * xxxxx.h
 *
 * 温度模块，抽象出的API，不同项目实现接口
 *
 * Created:
 *  Author:
 */
#ifndef __APP_TEMPERATURE_API_H__
#define __APP_TEMPERATURE_API_H__

#include "GMtypes.h"
#include "utils.h"





// ======================== 接口 ============================
// 注意：1、接口使用函数封装而不是用宏定义封装，是为了在编译时可进行参数检查
//      2、此处声明的接口函数且是static，为了在实现接口时是在.h中，这样就可内联，节省ROM空间。
//

/*
* API:初始化
*/
static void temp_prj_api_init(void);

/*
* API:激光系统温度值滤波
*/
static void temp_prj_api_laser_filter(void *p);

/*
* API:环境温度值滤波
*/
static void temp_prj_api_env_filter(void *p);

/*
* API:DMD温度值滤波
*/
static void temp_prj_api_dmd_filter(void *p);

/*
* API:色轮温度值滤波
*/
static void temp_prj_api_cw_filter(void *p);

/*
* API:色轮温度值滤波
*/
static void temp_prj_api_G_led_filter(void *p);

/*
* API:色轮温度值滤波
*/
static void temp_prj_api_R_led_filter(void *p);

/*
* API:色轮温度值滤波
*/
static void temp_prj_api_BP_led_filter(void *p);

/*
* API:驱动板温度值滤波
*/
static void temp_prj_api_board_filter(void *p);

/*
* @功能说明:阻塞的方式，获取环境温度。
* @注    意:
* @形    参:[out]p_ret_value:返回的温度值，units:1℃
* @返    回:<0-错误;>=0正确；
*/
static BOOL temp_prj_api_block_get_env(int8_t *p_ret_value);


/*
* @功能说明:阻塞的方式，获取系统温度
* @注    意:
* @形    参:[out]p_ret_value:返回的温度值，units:1℃
* @返    回:<0-错误;>=0正确；
*/
static BOOL temp_prj_api_block_get_laser(int8_t *p_ret_value);


/*
* @功能说明:阻塞的方式，获取DMD温度值
* @注    意:
* @形    参:[out]p_ret_value:返回的温度值，units:1℃
* @返    回:<0-错误;>=0正确；
*/
static BOOL temp_prj_api_block_get_dmd(int8_t *p_ret_value);

/*
* @功能说明:阻塞的方式，获取色轮温度值
* @注    意:
* @形    参:[out]p_ret_value:返回的温度值，units:1℃
* @返    回:<0-错误;>=0正确；
*/
static BOOL temp_prj_api_block_get_cw(int8_t *p_ret_value);

/*
* @功能说明:阻塞的方式，获取G灯温度值
* @注    意:
* @形    参:[out]p_ret_value:返回的温度值，units:1℃
* @返    回:<0-错误;>=0正确；
*/
static BOOL temp_prj_api_block_get_G_led(int8_t *p_ret_value);

/*
* @功能说明:阻塞的方式，获取R灯温度值
* @注    意:
* @形    参:[out]p_ret_value:返回的温度值，units:1℃
* @返    回:<0-错误;>=0正确；
*/
static BOOL temp_prj_api_block_get_R_led(int8_t *p_ret_value);

/*
* @功能说明:阻塞的方式，获取BP灯温度值
* @注    意:
* @形    参:[out]p_ret_value:返回的温度值，units:1℃
* @返    回:<0-错误;>=0正确；
*/
static BOOL temp_prj_api_block_get_BP_led(int8_t *p_ret_value);

/*
* @功能说明:阻塞的方式，获取驱动板温度值
* @注    意:
* @形    参:[out]p_ret_value:返回的温度值，units:1℃
* @返    回:<0-错误;>=0正确；
*/
static BOOL temp_prj_api_block_get_board(int8_t *p_ret_value);


#include "app_temperature_NTC.h"

#endif

