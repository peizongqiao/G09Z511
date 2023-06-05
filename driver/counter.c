#include <driver_init.h>
#include "counter.h"
#include "app_log.h"
#include "n32g43x.h"

OCInitType COUN_TIM_OCInitStructure;

// 用于系统ticks计数
static volatile counter_time_t counter_uptime = 0;
unsigned int time_nmb = 0; 

void counter_init()
{
	TIM_TimeBaseInitType  TIM_TimeBaseStructure;
    NVIC_InitType NVIC_InitStructure;

    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM6, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    //设置优先级
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;

    NVIC_Init(&NVIC_InitStructure);

    //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.Prescaler = 100 - 1;
    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.Period    = 10 - 1;
    //TIM向上计数模式
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    //设置时钟分割
    TIM_TimeBaseStructure.ClkDiv    = 0;
		
	TIM_TimeBaseStructure.RepetCnt  = 0;
		
    TIM_InitTimeBase(TIM6, &TIM_TimeBaseStructure);

    /* 定时器TIM1向上计时 */
    TIM_ConfigInt(TIM6, TIM_INT_UPDATE, ENABLE);
    /* 使能定时器TIM1 */
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
	if(TIM_GetFlagStatus(TIM6,TIM_INT_UPDATE))//溢出中断
	{
		/***************在此处添加中断执行内容******************///进入一次100us  
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
    TIM_ClearFlag(TIM6,TIM_INT_UPDATE);//清除中断标志位 
} 

/*
* @功能说明:返回系统
* @注    意:无
* @形    参:无
* @返    回:系统启动后运行时间,类似linux的uptime。 units:1ms
*/


counter_time_t counter_get_uptime(void)
{
    return counter_uptime;
}



/**
  * 得到时间差
  * @return    当前时间
  * @param     前面的时间  新的时间
  * @exception
  **/
counter_time_t get_tim_delta(counter_time_t old, counter_time_t now)
{
    return (counter_time_t)(now - old);
}
