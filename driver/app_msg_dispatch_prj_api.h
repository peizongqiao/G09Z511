/*
 * xxxxx.h
 *
 * Created:
 *  Author:
 */
#ifndef _APP_MSG_DISPATCH_PRJ_API_H_
#define _APP_MSG_DISPATCH_PRJ_API_H_


#include "config.h"
#include "app_msg_dispatch_prj_api_types.h"




#define MSG_DISPATCH_CFG_TASK_POLL_CYC_MS (10)
// =================== external function ===================
// 注意：1、接口使用函数封装而不是用宏定义封装，是为了在编译时可进行参数检查
//      2、此处声明的接口函数且是static，为了在实现接口时是在.h中，这样就可内联，节省ROM空间。
//
static const msg_handle_array_t *msg_dispatch_api_get_handle_array(void);

/*
* @功能说明:获取设备开关机状态
* @注    意:无
* @形    参:无
* @返    回:TRUE-开机;FALSE-关机
*/
static BOOL msg_dispatch_api_get_on_off_status(void);

/*
* @功能说明:获取设备当前音量
* @注    意:无
* @形    参:无
* @返    回:TRUE-开机;FALSE-关机
*/
static uint8_t msg_dispatch_api_get_now_vol(void);


// =================== 包含不同项目接口的实现 ==================
//


#include "app_msg_dispatch_prj_dabai.h"





#endif