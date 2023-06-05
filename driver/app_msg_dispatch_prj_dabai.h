#ifndef __APP_MSG_DISPATCH_PRJ_DABAI_H__
#define __APP_MSG_DISPATCH_PRJ_DABAI_H__

#include "app_msg_dispatch_prj_api_types.h"
#include "bsp_pin_ctrl_api.h"

#undef MSG_DISPATCH_CFG_TASK_POLL_CYC_MS
#define MSG_DISPATCH_CFG_TASK_POLL_CYC_MS 10
// ========================= declare =======================
extern const msg_handle_array_t msg_handle_table_dabai;
BOOL get_on_off_status_dabai(void);

// ====================== external =========================
static const msg_handle_array_t *msg_dispatch_api_get_handle_array(void)
{
    return &msg_handle_table_dabai;
}

/*
* @功能说明:获取设备开关机状态
* @注    意:无
* @形    参:无
* @返    回:TRUE-开机;FALSE-关机
*/
static BOOL msg_dispatch_api_get_on_off_status(void)
{
    return get_on_off_status_dabai();
}

#endif /* __APP_MSG_DISPATCH_PRJ_DABAI_H__ */