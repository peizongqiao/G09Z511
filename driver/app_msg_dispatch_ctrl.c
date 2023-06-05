/*
 * xxxx.c
 *
 * Created: 2018/8/4 星期六 20:25:11
 *  Author:
 */
#include "app_msg_dispatch_ctrl.h"
#include "app_msg_dispatch_prj_api.h"
#include "app_log.h"
#include "app_softtimer.h"
#include "config.h"
#include "utils.h"
#include "GMtypes.h"
#include "bsp_i2c_host.h"
//#include "app_errno.h"


extern uint8_t data_buf[100];

extern uint8_t focal_dir;
extern uint32_t focal_step,focal_pps,focus_step_number;

extern uint16_t TIMx_pwm;
extern uint16_t TIM4_change,TIM2_change;
extern uint8_t led_mode;
extern uint8_t door_mode;
extern uint8_t iris_falg,iris_step,iris_step_number;
extern int sleep_mode;
extern uint8_t read_add;
extern uint8_t focal_end,zoom_end,focal_pi_flag,zoom_pi_flag;
extern int8_t temp_duf[8];
extern uint16_t ksl_speed,fan_5516_speed,fan_6025_P1_speed,fan_6025_P2_speed,fan_13038_speed;
typedef struct
{
    queue_t queue;                              // 消息队列
}msg_dispatch_ctrl_t;

// ======================== declare ========================
void msg_dispatch_poll(void);
static void msg_dispatch_msg_dispatch(msg_t *pmsg, msg_dispatch_ctrl_t *pdata);

static msg_dispatch_ctrl_t msg_dispatch;

/*
* @功能说明:消息分发初始化
* @注    意:无
* @形    参:无
* @返    回:无
*/
void msg_dispatch_init(void)
{
    #define MSG_DISPATCH_QUEUE_SIZES            20u
    msg_dispatch_ctrl_t *p = &msg_dispatch;
    // 创建消息队列
    static uint8_t queue_buff_array[MSG_DISPATCH_QUEUE_SIZES*sizeof(queue_buff_t)];
    queue_buff_t* queue_buff = (queue_buff_t*)queue_buff_array;

    queue_create(&p->queue, queue_buff, MSG_DISPATCH_QUEUE_SIZES);

    // pin控制
    bsp_soc_power_api_init();
    bsp_projector_on_api_init();
    bsp_wakeup_soc_api_init();
    bsp_check_soc_standby_api_init();
    // 创建周期回调任务：负责消息分发
    //TASK_PERIOD_CB_CREATE(2, msg_dispatch_poll);
}



/*
* @功能说明:向消息分发模块发送消息
* @注    意:无
* @形    参:[in]pmsg:要发送的消息的指针
* @返    回:无
*/
void msg_dispatch_send_msg(const msg_t* pmsg)
{
    msg_dispatch_ctrl_t *p = &msg_dispatch;
    queue_push(&p->queue, (const queue_buff_t *)pmsg);
}

/*
* @功能说明:直接分发消息，适合需要及时响应的模块（注意：一般用于iic中断，不可阻塞过久）
* @注    意:无
* @形    参:[in]pmsg:要发送的消息的指针
* @返    回:无
*/
void msg_dispatch_send_msg_block(const msg_t* pmsg)
{
    msg_dispatch_ctrl_t *p = &msg_dispatch;
    //queue_push(&p->queue, (const queue_buff_t *)pmsg);
    msg_dispatch_msg_dispatch((msg_t *)pmsg, p);
}

/*
* @功能说明:消息分发
* @注    意:无
* @形    参:[in]pmsg:要发送的消息的指针
* @返    回:无
*/
static void msg_dispatch_msg_dispatch(msg_t *pmsg, msg_dispatch_ctrl_t *pdata)
{
    UNUSED_PARAM(pdata);

    msg_handle_t *p_handle = (msg_handle_t *)msg_dispatch_api_get_handle_array();
    if(p_handle[(msg_type_t)pmsg->msgid]){
        (p_handle[(msg_type_t)pmsg->msgid])(pmsg);
    }else{
        //LOG_ERROR("callback NULL!",((msg_type_t)pmsg->msgid));
    }
}

void msg_dispatch_poll(void)
{
		if(0 != data_buf[0])
		{	
			//调焦 变焦
			if(0x21 == data_buf[0])
			{
				focal_dir = data_buf[1];
				focal_pps = data_buf[2] + (data_buf[3] << 8);
				focal_step = data_buf[4] + (data_buf[5] << 8);
				focal_end = 0;
				focus_step_number = 0;
				
			}
			
			if(0x03 == data_buf[0])
			{
				if(100 > data_buf[1])
					TIMx_pwm = data_buf[1];
				else
					TIMx_pwm = 99;
				TIM4_change = 0x01;
			}
			else if(0x04 == data_buf[0])
			{
				if(100 > data_buf[1])
					TIMx_pwm = data_buf[1];
				else
					TIMx_pwm = 99;
				TIM4_change = 0x02;
			}
			else if(0x05 == data_buf[0])
			{
				if(100 > data_buf[1])
					TIMx_pwm = data_buf[1];
				else
					TIMx_pwm = 99;
				TIM4_change = 0x04;
			}
			else if(0x06 == data_buf[0])
			{
				if(100 > data_buf[1])
					TIMx_pwm = data_buf[1];
				else
					TIMx_pwm = 99;
				TIM4_change = 0x08;
			}
			else if(0x07 == data_buf[0])
			{
				if(100 < data_buf[1])
					TIMx_pwm = 99;
				else if(100 > data_buf[1] && 60 < data_buf[1])
					TIMx_pwm = data_buf[1];
				else
					TIMx_pwm = 60;
				TIM2_change = 0x80;
			}
			else
			{
				TIM2_change = 0x00;
				TIM4_change = 0x00;
				TIMx_pwm = 0;
			}
			
			if(0x08 == data_buf[0])
			{
				if(1 == data_buf[1])
				{
					led_mode = 1;
				}
				else if(2 == data_buf[1])
				{
					led_mode = 2;
				}
				else if(3 == data_buf[1])
				{
					led_mode = 3;
				}
				else if(4 == data_buf[1])
				{
					led_mode = 4;
				}
				else
				{
					led_mode = 0;
				}
			}
			else
			{;}
			
			if(0x09 == data_buf[0])
			{
				if(1 == data_buf[1])
				{
					led_mode = 4;
					door_mode = 1;
				}
				else if(2 == data_buf[1])
				{
					led_mode = 4;
					door_mode = 2;
				}
				else if(3 == data_buf[1])
				{
					door_mode = 3;
				}
				else
				{
					door_mode = 0;
					led_mode = 0;
				}
			}

			if(0x25 == data_buf[0])
			{
					iris_falg = data_buf[1] >> 7;
					iris_step = data_buf[1] & 0x7f;
					iris_step_number = 0;
//				if(1 == (data_buf[1] >> 7))
//				{
//          iris_falg = 1;
//					iris_step = data_buf[1] & 0x7f;
//				}
//				else if(0 == (data_buf[1] >> 7))
//				{
//					iris_falg = 2;
//					iris_step = data_buf[1] & 0x7f;
//				}
//				else
//				{
//					iris_falg = 0;
//					iris_step = 0;
//				}
//        //iris_step_number = 0;
			}
			
			if(0x0b == data_buf[0])
			{
				if(1 == data_buf[1])
				{
          sleep_mode = 1;
				}
				else
				{
					sleep_mode = 0;
				}
			}
      
		}
		for(int a = 0;a<20;a++)
				data_buf[a] = 0;
}

void read_data_check(void)
{
	int32_t step_number_las;
		if(read_add == 0x23)
		{
			data_buf[0] = focal_end << 6 | focal_pi_flag << 4 | zoom_end << 2 |zoom_pi_flag << 0;
			data_buf[1] = focus_step_number%256;
			data_buf[2] = focus_step_number/256;
			data_buf[3] = 0;
			data_buf[4] = 0;
			data_buf[5] = 0;
			data_buf[6] = 0;
		}
		else if(read_add == 0x1e)
		{
			data_buf[0] = temp_duf[0];
			data_buf[1] = temp_duf[1];
			data_buf[2] = temp_duf[2];
			data_buf[3] = temp_duf[3];
			data_buf[4] = temp_duf[4];
			data_buf[5] = temp_duf[5];
			data_buf[6] = temp_duf[6];
			data_buf[7] = temp_duf[7];
			data_buf[8] = 0x1e;
			data_buf[9] = I2C_RD;
		}
		else if(read_add == 0x20)
		{
			data_buf[0] = ksl_speed;
			data_buf[1] = ksl_speed >> 8;
			data_buf[2] = fan_5516_speed;
			data_buf[3] = fan_5516_speed >> 8;
			data_buf[4] = fan_6025_P1_speed;
			data_buf[5] = fan_6025_P1_speed >> 8;
			data_buf[6] = fan_6025_P2_speed;
			data_buf[7] = fan_6025_P2_speed >> 8;
			data_buf[8] = fan_13038_speed;
			data_buf[9] = fan_13038_speed >> 8;
		}
}
