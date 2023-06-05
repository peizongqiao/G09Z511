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


// ϵͳ����ģʽ
typedef enum
{
    E_SYS_MODE_NOTHING = 0,
    E_SYS_MODE_STANDBY,             // ����ģʽ��һ��Ҫ���͹��ģ�
    E_SYS_MODE_WORKING,             // ����ģʽ
    E_SYS_MODE_POWER_DOWN,          // SOC�ػ�ģʽ
    E_SYS_MODE_SLEEP,               // SOC sleepģʽ
    E_SYS_MODE_MCU_CHECKED_BOOT,    // MCU��⵽�����������ڿ��ٿ������磺���������Ŀ��


    E_SYS_MODE_BOOT,
}sys_mode_t;


// ��Ϣ�ṹ��
typedef union
{
    uint16_t all_data;
    struct
    {
        uint8_t msgid:4;            // ��Ϣid
        uint8_t dataid:4;           // ����id
        uint8_t data;               // ��Ϣ�������ݣ�ָ��
    }__attribute__((aligned(1)));
}msg_t;


typedef enum
{
    E_MSG_TIME_PERIOD = 0,         // ��ʱ����
    E_MSG_FROM_SOC_LAMP,           // SOCͬ���ĵƹ�״̬��Ϣ
    E_MSG_FROM_SOC_STATUS,         // ��SOCͬ����״̬��Ϣ
    E_MSG_KEY_EVENT,               // �����¼�
    E_MSG_DOOR_STATE_EVENT,        // ����״̬�¼���Ϣ
    E_MSG_FROM_SOC_CTRL_DOOR,      // ��SOC�����Ŀ��Ʋ���
    E_MSG_FROM_SOC_CTRL_FAN,       // ��SOC�����Ŀ��Ʒ���
    E_MSG_FROM_PRIVATE_PROTOCOL,   // �ӵ�PIN���߷����Ŀ�������
    E_MSG_FROM_SOC_VOL,            // ��SOC������������С
    // ����ʵ���������...

    E_MSG_MAX_NUMS,
}msg_type_t;




typedef void (*msg_handle_t)(const msg_t*);
typedef msg_handle_t msg_handle_array_t[E_MSG_MAX_NUMS];



#endif
