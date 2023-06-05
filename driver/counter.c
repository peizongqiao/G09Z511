#include <driver_init.h>
#include "counter.h"
#include "app_log.h"
#include "n32g43x.h"

OCInitType COUN_TIM_OCInitStructure;

// ����ϵͳticks����
static volatile counter_time_t counter_uptime = 0;
unsigned int time_nmb = 0; 

void counter_init()
{
	TIM_TimeBaseInitType  TIM_TimeBaseStructure;
    NVIC_InitType NVIC_InitStructure;

    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM6, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    //�������ȼ�
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;

    NVIC_Init(&NVIC_InitStructure);

    //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.Prescaler = 100 - 1;
    //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.Period    = 10 - 1;
    //TIM���ϼ���ģʽ
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    //����ʱ�ӷָ�
    TIM_TimeBaseStructure.ClkDiv    = 0;
		
	TIM_TimeBaseStructure.RepetCnt  = 0;
		
    TIM_InitTimeBase(TIM6, &TIM_TimeBaseStructure);

    /* ��ʱ��TIM1���ϼ�ʱ */
    TIM_ConfigInt(TIM6, TIM_INT_UPDATE, ENABLE);
    /* ʹ�ܶ�ʱ��TIM1 */
    TIM_Enable(TIM6, ENABLE);
}
uint16_t time1_counter1 = 0;
uint16_t time1_counter2 = 0;
uint16_t time1_counter3 = 0;
uint16_t time1_counter4 = 0;
uint16_t time1_counter5 = 0;
uint16_t time1_counter6 = 0;
bool flag_1ms = 0;
bool flag_20ms = 0;
bool flag_900us = 0;
bool flag_500us = 0;
bool flag_500pps = 0;
bool flag_1 = 0;
void TIM6_IRQHandler(void) 
{ 	    	  	     
	if(TIM_GetFlagStatus(TIM6,TIM_INT_UPDATE))//����ж�
	{
		/***************�ڴ˴�����ж�ִ������******************///����һ��100us  
		time1_counter1++;
		time1_counter2++;
		time1_counter3++;
		time1_counter4++;
		time1_counter5++;
		time1_counter6++;
		if(time1_counter1 == 2000)//1ms
		{
			time1_counter1 = 0;
			flag_900us = 1;	
		}
		if(time1_counter2 == 15)//1ms
		{
			time1_counter2 = 0;
			flag_1ms = 1;	
		}
		if(time1_counter4 == 1000)
		{
			time1_counter4 = 0;
			flag_500us = 1;
		}
		if(time1_counter3 == 400)//20ms
		{
			time1_counter3 = 0;
			flag_20ms = 1;	
		}
		if(time1_counter5 == 20)//20ms
		{
			time1_counter5 = 0;
			flag_500pps = 1;	
		}
		if(time1_counter6 == 200)//20ms
		{
			time1_counter6= 0;
			flag_1 = 1;	
		}
	}	
    TIM_ClearFlag(TIM6,TIM_INT_UPDATE);//����жϱ�־λ 
} 

/*
* @����˵��:����ϵͳ
* @ע    ��:��
* @��    ��:��
* @��    ��:ϵͳ����������ʱ��,����linux��uptime�� units:1ms
*/


counter_time_t counter_get_uptime(void)
{
    return counter_uptime;
}



/**
  * �õ�ʱ���
  * @return    ��ǰʱ��
  * @param     ǰ���ʱ��  �µ�ʱ��
  * @exception
  **/
counter_time_t get_tim_delta(counter_time_t old, counter_time_t now)
{
    return (counter_time_t)(now - old);
}
