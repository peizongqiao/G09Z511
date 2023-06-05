//#include  "pwm_basic.h"
#include "bsp_mult_pwm.h"
//#include "N32G43x_Start.h"


GPIO_InitType PWM_GPIO_InitStructure;
TIM_TimeBaseInitType TIM_TimeBaseStructure;
OCInitType TIM_OCInitStructure;
uint16_t Channel1Pulse = 0,Channel2Pulse = 0,Channel3Pulse = 0,Channel4Pulse = 0;
void PWM_TIME(void)
{
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);
	
	GPIO_InitStruct(&PWM_GPIO_InitStructure);
    /* GPIOA Configuration: Channel 1, 2 and 3 as alternate function push-pull */
    PWM_GPIO_InitStructure.Pin        = GPIO_PIN_2;
    PWM_GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    PWM_GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM2;
    PWM_GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitPeripheral(GPIOA, &PWM_GPIO_InitStructure);
	
	
	TIM_TimeBaseStructure.Prescaler = 9 - 1;
    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.Period    = 200 - 1;
    //TIM向上计数模式
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
   //设置时钟分割
   TIM_TimeBaseStructure.ClkDiv    = 0;
   
   TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.ClkDiv    = 0;
	
	TIM_InitTimeBase(TIM2, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.OcMode       = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse        = 200;
    TIM_OCInitStructure.OcPolarity   = TIM_OC_POLARITY_LOW;
 
    TIM_InitOc3(TIM2, &TIM_OCInitStructure);

    TIM_ConfigArPreload(TIM2, ENABLE);

    TIM_Enable(TIM2, ENABLE);
	
}

void PWM_BLED(void)
{
 //PC6 TIM8_CH1 PC7 TIM8_CH2 PC8 TIM8_CH3 PC9 TIM8_CH4
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_AFIO | RCC_APB2_PERIPH_TIM1, ENABLE);  
//    DBG_ConfigPeriph(DBG_TIM1_STOP , ENABLE);
		
		GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    /* GPIOA Configuration: Channel 1, 2 and 3 as alternate function push-pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_8;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM1;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

     //触发时间：(Prescaler + 1) * (Period + 1)/108M
    //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.Prescaler = 10 - 1;
     //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
     TIM_TimeBaseStructure.Period    = 256 - 1;
     //TIM向上计数模式
     TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    //设置时钟分割
    TIM_TimeBaseStructure.ClkDiv    = 0; 
//    TIM_TimeBaseStructure.RepetCnt  = 0;   
    TIM_InitTimeBase(TIM1, &TIM_TimeBaseStructure); 
    /* PWM1 Mode configuration: Channel1 */
    TIM_OCInitStructure.OcMode       = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse        = 172;
    TIM_OCInitStructure.OcPolarity   = TIM_OC_POLARITY_LOW;    
    TIM_InitOc1(TIM1, &TIM_OCInitStructure);    
    TIM_InitOc2(TIM1, &TIM_OCInitStructure);
    TIM_InitOc3(TIM1, &TIM_OCInitStructure);
    TIM_InitOc4(TIM1, &TIM_OCInitStructure);

    //TIM_ConfigArPreload(TIM8, ENABLE);  
    TIM_Enable(TIM1, ENABLE);
    TIM_EnableCtrlPwmOutputs(TIM1, ENABLE);
	
}

void PWM_FAN1_4(void)
{
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM4, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);
	
	GPIO_InitStruct(&PWM_GPIO_InitStructure);
    /* GPIOA Configuration: Channel 1, 2 and 3 as alternate function push-pull */
    PWM_GPIO_InitStructure.Pin        = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
    PWM_GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    PWM_GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM4;
    PWM_GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitPeripheral(GPIOB, &PWM_GPIO_InitStructure);
	 
	TIM_TimeBaseStructure.Prescaler = 18 - 1;
    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.Period    = 100 - 1;
    //TIM向上计数模式
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
   //设置时钟分割
   TIM_TimeBaseStructure.ClkDiv    = 0;
   
   TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.ClkDiv    = 0;
	
	TIM_InitTimeBase(TIM4, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.OcMode       = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse        = 50;
    TIM_OCInitStructure.OcPolarity   = TIM_OC_POLARITY_LOW;
 
    TIM_InitOc1(TIM4, &TIM_OCInitStructure);
	TIM_InitOc2(TIM4, &TIM_OCInitStructure);
	TIM_InitOc3(TIM4, &TIM_OCInitStructure);
    TIM_InitOc4(TIM4, &TIM_OCInitStructure);
    TIM_ConfigArPreload(TIM4, ENABLE);
    TIM_Enable(TIM4, ENABLE);	
}

//void PWM_FAN_5(void)
//{
//	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM9, ENABLE);
//    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);
//	
//	GPIO_InitStruct(&PWM_GPIO_InitStructure);
//    /* GPIOA Configuration: Channel 1, 2 and 3 as alternate function push-pull */
//    PWM_GPIO_InitStructure.Pin        = GPIO_PIN_14;
//    PWM_GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
//    PWM_GPIO_InitStructure.GPIO_Alternate = GPIO_AF1_TIM9;
//    PWM_GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
//    GPIO_InitPeripheral(GPIOB, &PWM_GPIO_InitStructure);

//	TIM_TimeBaseStructure.Prescaler = 18 - 1;
//    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
//    TIM_TimeBaseStructure.Period    = 100 - 1;
//    //TIM向上计数模式
//    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
//   //设置时钟分割
//   TIM_TimeBaseStructure.ClkDiv    = 0;
//   
//   TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
//    TIM_TimeBaseStructure.ClkDiv    = 0;
//	
//	TIM_InitTimeBase(TIM9, &TIM_TimeBaseStructure);
//	
//	TIM_OCInitStructure.OcMode       = TIM_OCMODE_PWM2;
//    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
//    TIM_OCInitStructure.Pulse        = 50;
//    TIM_OCInitStructure.OcPolarity   = TIM_OC_POLARITY_LOW;
// 
//    TIM_InitOc3(TIM9, &TIM_OCInitStructure);

//    TIM_ConfigArPreload(TIM9, ENABLE);

//    TIM_Enable(TIM9, ENABLE);
//	
//}

void PWM_FAN_1(void)
{
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM4, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);  
	
	GPIO_InitStruct(&PWM_GPIO_InitStructure);
    /* GPIOA Configuration: Channel 1, 2 and 3 as alternate function push-pull */
    PWM_GPIO_InitStructure.Pin        = GPIO_PIN_6;
    PWM_GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    PWM_GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM4;
    PWM_GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitPeripheral(GPIOB, &PWM_GPIO_InitStructure);
	
	
	TIM_TimeBaseStructure.Prescaler = 18 - 1;
    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.Period    = 100 - 1;
    //TIM向上计数模式
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
   //设置时钟分割
   TIM_TimeBaseStructure.ClkDiv    = 0;
   
   TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.ClkDiv    = 0;
	
	TIM_InitTimeBase(TIM1, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.OcMode       = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse        = 100;
    TIM_OCInitStructure.OcPolarity   = TIM_OC_POLARITY_LOW;
 
    TIM_InitOc1(TIM4, &TIM_OCInitStructure);    
    TIM_OCInitStructure.Pulse = 20;
    TIM_InitOc2(TIM4, &TIM_OCInitStructure);
    TIM_OCInitStructure.Pulse = 20;
    TIM_InitOc3(TIM4, &TIM_OCInitStructure);
    TIM_OCInitStructure.Pulse = 20;
    TIM_InitOc4(TIM4, &TIM_OCInitStructure);

    TIM_ConfigArPreload(TIM4, ENABLE);  
    TIM_Enable(TIM4, ENABLE);
}

void PWM_FAN_5(void)
{
  	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);
	
	GPIO_InitStruct(&PWM_GPIO_InitStructure);
    /* GPIOA Configuration: Channel 1, 2 and 3 as alternate function push-pull */
    PWM_GPIO_InitStructure.Pin        = GPIO_PIN_0;
    PWM_GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    PWM_GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM3;
    PWM_GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitPeripheral(GPIOB, &PWM_GPIO_InitStructure);
	
	TIM_TimeBaseStructure.Prescaler = 18 - 1;
    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.Period    = 100 - 1;
    //TIM向上计数模式
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
   //设置时钟分割
   TIM_TimeBaseStructure.ClkDiv    = 0;
   
   TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.ClkDiv    = 0;
	
	TIM_InitTimeBase(TIM3, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.OcMode       = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse        = 50;
    TIM_OCInitStructure.OcPolarity   = TIM_OC_POLARITY_LOW;
 
    TIM_InitOc3(TIM3, &TIM_OCInitStructure);

    TIM_ConfigArPreload(TIM3, ENABLE);

    TIM_Enable(TIM3, ENABLE);
}

void pwm_filter()
{
    //PC6 TIM8_CH1 PC7 TIM8_CH2 PC8 TIM8_CH3 PC9 TIM8_CH4
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_AFIO | RCC_APB2_PERIPH_TIM8, ENABLE);  
    DBG_ConfigPeriph(DBG_TIM8_STOP , ENABLE);
		
		GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    /* GPIOA Configuration: Channel 1, 2 and 3 as alternate function push-pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF6_TIM8;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
	
    Channel1Pulse = (uint16_t)(((uint32_t)99 * (200 - 1)) / 100);
    Channel2Pulse = (uint16_t)(((uint32_t)99 * (200 - 1)) / 100);
    Channel3Pulse = (uint16_t)(((uint32_t)99 * (200 - 1)) / 100);
    Channel4Pulse = (uint16_t)(((uint32_t)99 * (200 - 1)) / 100);

     //触发时间：(Prescaler + 1) * (Period + 1)/108M
    //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.Prescaler = 10 - 1;
     //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
     TIM_TimeBaseStructure.Period    = 108 - 1;
     //TIM向上计数模式
     TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    //设置时钟分割
    TIM_TimeBaseStructure.ClkDiv    = 0; 
    TIM_TimeBaseStructure.RepetCnt  = 0;   
    TIM_InitTimeBase(TIM8, &TIM_TimeBaseStructure); 
    /* PWM1 Mode configuration: Channel1 */
    TIM_OCInitStructure.OcMode       = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse        = 50;
    TIM_OCInitStructure.OcPolarity   = TIM_OC_POLARITY_LOW;    
    TIM_InitOc1(TIM8, &TIM_OCInitStructure);    
    TIM_OCInitStructure.Pulse = 50;
    TIM_InitOc2(TIM8, &TIM_OCInitStructure);
    TIM_OCInitStructure.Pulse = 50;
    TIM_InitOc3(TIM8, &TIM_OCInitStructure);
    TIM_OCInitStructure.Pulse = 50;
    TIM_InitOc4(TIM8, &TIM_OCInitStructure);

    //TIM_ConfigArPreload(TIM8, ENABLE);  
    TIM_Enable(TIM8, ENABLE);
    TIM_EnableCtrlPwmOutputs(TIM8, ENABLE);
}

//void bsp_pwm_TIM3_init()
//{
//		TIM_TimeBaseInitType  TIM_TimeBaseStructure;
//    NVIC_InitType NVIC_InitStructure;
//		GPIO_InitType GPIO_InitStructure;

//    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);
//		RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);

//		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

//		//设置优先级
//		NVIC_InitStructure.NVIC_IRQChannel                   = TIM3_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
//		NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;

//		NVIC_Init(&NVIC_InitStructure);

//    //设置用来作为TIMx时钟频率除数的预分频值
//    TIM_TimeBaseStructure.Prescaler = 54 - 1;
//    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
//    TIM_TimeBaseStructure.Period    = 1000 - 1;
//    //TIM向上计数模式
//    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
//    //设置时钟分割
//    TIM_TimeBaseStructure.ClkDiv    = 0;
//		
//		TIM_TimeBaseStructure.RepetCnt  = 0;
//		
//    TIM_InitTimeBase(TIM3, &TIM_TimeBaseStructure);

//    /* 定时器TIM1向上计时 */
//    TIM_ConfigInt(TIM3, TIM_INT_UPDATE, ENABLE);
//    /* 使能定时器TIM1 */
//    TIM_Enable(TIM3, ENABLE);
//	
//		GPIO_InitStruct(&GPIO_InitStructure);
//		GPIO_InitStructure.Pin        = GPIO_PIN_5;
//		GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
//		GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
//		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
//		GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
//		
////	 //PB5 使用TIM3_CH2
////   RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);
////   RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);

////   /* Compute the value to be set in AR regiter to generate signal frequency at 17.57 Khz */
////   //TimerPeriod = (uint16_t)(SystemCoreClock / 1000000 ) - 1;
////   /* Compute CCDAT4 value to generate a duty cycle at 12.5%  for channel 4 */
////   Channel2Pulse = (uint16_t)(((uint32_t)0 * (TimerPeriod - 1)) / 100); 


////    //触发时间：(Prescaler + 1) * (Period + 1)/54M 简化为2*Prescaler/
////   //设置用来作为TIMx时钟频率除数的预分频值
////   TIM_TimeBaseStructure.Prescaler = 54 - 1;
////    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
////    TIM_TimeBaseStructure.Period    = TimerPeriod;
////    //TIM向上计数模式
////    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
////   //设置时钟分割
////   TIM_TimeBaseStructure.ClkDiv    = 0;


////   TIM_InitTimeBase(TIM3, &TIM_TimeBaseStructure);

////   /* PWM1 Mode configuration: Channel1 */
////   TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
////   TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
////   TIM_OCInitStructure.Pulse       = Channel2Pulse;
////   TIM_OCInitStructure.OcPolarity  = TIM_OC_POLARITY_LOW;

////   TIM_InitOc2(TIM3, &TIM_OCInitStructure);

////   TIM_ConfigArPreload(TIM3, ENABLE);

////   TIM_Enable(TIM3, ENABLE);
//}

