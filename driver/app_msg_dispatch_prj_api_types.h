/*
 * xxxx.h
 *
 * Created:
 *  Author:
 */
#ifndef _APP_MSG_DISPATCH_PRJ_API_TYPES_H_
#define _APP_MSG_DISPATCH_PRJ_API_TYPES_H_

#include "GMtypes.h"


typedef enum
{
    EN_STEP_0 = 0,
    EN_STEP_1,
    EN_STEP_2,
    EN_STEP_3,
    EN_STEP_4,
    EN_STEP_5,
    EN_STEP_6
}internal_step_t;


// 系统工作模式
typedef enum
{
    E_SYS_MODE_NOTHING = 0,
    E_SYS_MODE_STANDBY,             // 待机模式（一般要做低功耗）
    E_SYS_MODE_WORKING,             // 工作模式
    E_SYS_MODE_POWER_DOWN,          // SOC关机模式
    E_SYS_MODE_SLEEP,               // SOC sleep模式
    E_SYS_MODE_MCU_CHECKED_BOOT,    // MCU检测到开机（可用于快速开机，如：激光电视项目）


    E_SYS_MODE_BOOT,
}sys_mode_t;


// 消息结构体
typedef union
{
    uint16_t all_data;
    struct
    {
        uint8_t msgid:4;            // 消息id
        uint8_t dataid:4;           // 数据id
        uint8_t data;               // 消息数据内容，指针
    }__attribute__((aligned(1)));
}msg_t;


typedef enum
{
    E_MSG_TIME_PERIOD = 0,         // 定时周期
    E_MSG_FROM_SOC_LAMP,           // SOC同步的灯光状态信息
    E_MSG_FROM_SOC_STATUS,         // 从SOC同步了状态信息
    E_MSG_KEY_EVENT,               // 按键事件
    E_MSG_DOOR_STATE_EVENT,        // 舱门状态事件消息
    E_MSG_FROM_SOC_CTRL_DOOR,      // 从SOC发来的控制舱门
    E_MSG_FROM_SOC_CTRL_FAN,       // 从SOC发来的控制风扇
    E_MSG_FROM_PRIVATE_PROTOCOL,   // 从单PIN总线发来的控制命令
    E_MSG_FROM_SOC_VOL,            // 从SOC发来的音量大小
    // 根据实际需求添加...

    E_MSG_MAX_NUMS,
}msg_type_t;




typedef void (*msg_handle_t)(const msg_t*);
typedef msg_handle_t msg_handle_array_t[E_MSG_MAX_NUMS];



#endif
