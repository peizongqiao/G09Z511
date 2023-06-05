#include "app_softtimer.h"
#include "../driver/GMtypes.h"
#include "../driver/utils.h"
#include "driver_init.h"
#include "app_log.h"
#include "app_iris.h"
#include "app_focal_ctrl.h"
#include "main.h"
#include "i2c_slave_N32G43X.h"
#include "i2c2_slave_N32G43X.h"
#include "i2c_master_1.h"
#include "bsp_pi_api.h"

extern bool flag_500pps;
extern bool flag_1ms;
extern bool flag_5ms;
extern bool flag_10ms;
extern bool flag_20ms;
extern bool flag_2ms;
extern bool flag_900us;
extern bool flag_500us;
extern bool flag_1;
extern uint8_t R_flag;
extern uint16_t log_pps;
uint8_t pps_flag;


// ������ʱ�����ݽṹ
typedef struct
{
    uint16_t period;                                // ��������
    counter_time_t last_time;                       // �ϴ�ʱ���
    softtimer_cb_t cb;                              // �ص�����
    run_mode_t run_mode;                            // ����ģʽ
}softtimer_t;

static softtimer_t softtimer_table[SOFTTIMER_CFG_ITEMS_NUMS] = {0};

/*
* @����˵��:������ʱ����ʼ��
* @ע    ��:��
* @��    ��:��
* @��    ��:��
*/
void softtimer_init(void)
{
    // ��ʵ��
}

/*
* @����˵��: ������ʱ����ע��ص��������ṩ���κ�����������ģʽ
* @ע    ��: 1.�����̰߳�ȫ�ģ��������ڶ��̡߳��ж��С�
*           2.�ص�ʱ����Ƚϵͣ�����Ҫ�߾��ȵĽ���ʹ��Ӳ����
* @��    ��: [in]period_ms:ʵ��ms������Χ1~65530ms�����ԣ�COUNTER_TICK_PERIOD_MS��
*                         Ϊ������������ΪCOUNTER_TICK_PERIOD_MS���������������Ͻ�10ms��ʽ
*           [in]run_mode:����ģʽ����������/��������
* @��    ��: ��
*/
void softtimer_register(uint16_t period_ms, softtimer_cb_t pfunc, run_mode_t run_mode)
{
    U16 i;

    for(i=0; i<SOFTTIMER_CFG_ITEMS_NUMS; i++)
    {
        // Ѱ��δʹ�õ�
        if(E_RUNMODE_NOT_USE == softtimer_table[i].run_mode){
            break;
        }
    }

    softtimer_table[i].run_mode = run_mode;
    // ��ʼ��Ϊע��ʱ�̵�ʱ�䡣
    softtimer_table[i].last_time = GET_TICK_STAMP();
    // ����COUNTER_TICK_MS���������㡣
    softtimer_table[i].period = (0 != (period_ms%COUNTER_TICK_PERIOD_MS)) ? \
        period_ms-(period_ms%COUNTER_TICK_PERIOD_MS)+(COUNTER_TICK_PERIOD_MS) : period_ms;
    softtimer_table[i].cb = pfunc;
}

/*
* @����˵��:ͨ�����������Ƴ��Ѿ�ע�����
* @ע    ��:����MCU��Դ���˴����ú�������ΪΨһ��׼�жϣ���ע����2�������ϵ���ͬ��������ʱ�����ܴ�����
* @��    ��:[in]function
* @��    ��:��
*/
void softtimer_remove_by_function(softtimer_cb_t function)
{
    for(uint8_t i=0; i<SOFTTIMER_CFG_ITEMS_NUMS; i++)
    {
        if(E_RUNMODE_NOT_USE != softtimer_table[i].run_mode){
            if(function == softtimer_table[i].cb){
                softtimer_table[i].run_mode = E_RUNMODE_NOT_USE;
                return;
            }
        }
    }
}

/*
* @����˵��:������ʱ����ѯ
* @ע    ��:��
* @��    ��:��
* @��    ��:��
*/
void softtimer_poll(void)
{
    for (uint8_t i = 0; i < SOFTTIMER_CFG_ITEMS_NUMS; i++)//SOFTTIMER_CFG_ITEMS_NUMS = 15
    {
        softtimer_t *p_timer = &softtimer_table[i];

        if (E_RUNMODE_NOT_USE == p_timer->run_mode) {
            continue;
        }
        if (get_tim_delta(p_timer->last_time, GET_TICK_STAMP()) >= p_timer->period){
            p_timer->cb();
            if (E_RUNMODE_SINGLE == p_timer->run_mode){
                p_timer->run_mode = E_RUNMODE_NOT_USE;
                continue;
            }
            p_timer->last_time = GET_TICK_STAMP();
        }
    }
}



void task(void)
{
	if(flag_1ms)
	{
		focal_diver_poll();
		zoom_diver_poll();
		focal_back_go();
		zoom_back_go();
		flag_1ms = 0;
	}
	if(flag_500us)
	{
		iris_flag_poll();
		flag_500us=0;
	}
	if(flag_500pps)
	{
		IRIS_19_PI();
		reset_iris();
		iris_poll();
		iris_poll_bk();
		iris_old_1();
		iris_poll_go();
		flag_500pps = 0;
	}
	if(flag_1)
	{
		old();
		iris_old();
		app_iris_poll();
		focal_ctrl_poll();
		zoom_ctrl_poll();
		screen_poll();
		app_iris_poll_1();
		flag_1 = 0;
	}
}