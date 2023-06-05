/*
 * xxxxx.h
 *
 * Created: 2018/8/4 ÐÇÆÚÁù 20:25:58
 *  Author:
 */
#ifndef _APP_MSG_DISPATCH_H_
#define _APP_MSG_DISPATCH_H_

#include "app_queue.h"
#include "app_msg_dispatch_prj_api.h"


// =================== external function ===================
void msg_dispatch_init(void);
void msg_dispatch_send_msg(const msg_t* pmsg);
void msg_dispatch_send_msg_block(const msg_t* pmsg);


#endif
