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
// ע�⣺1���ӿ�ʹ�ú�����װ�������ú궨���װ����Ϊ���ڱ���ʱ�ɽ��в������
//      2���˴������Ľӿں�������static��Ϊ����ʵ�ֽӿ�ʱ����.h�У������Ϳ���������ʡROM�ռ䡣
//
static const msg_handle_array_t *msg_dispatch_api_get_handle_array(void);

/*
* @����˵��:��ȡ�豸���ػ�״̬
* @ע    ��:��
* @��    ��:��
* @��    ��:TRUE-����;FALSE-�ػ�
*/
static BOOL msg_dispatch_api_get_on_off_status(void);

/*
* @����˵��:��ȡ�豸��ǰ����
* @ע    ��:��
* @��    ��:��
* @��    ��:TRUE-����;FALSE-�ػ�
*/
static uint8_t msg_dispatch_api_get_now_vol(void);


// =================== ������ͬ��Ŀ�ӿڵ�ʵ�� ==================
//


#include "app_msg_dispatch_prj_dabai.h"





#endif