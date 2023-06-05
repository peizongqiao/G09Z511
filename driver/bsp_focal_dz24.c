#include "bsp_focal_dz24.h"
#include "counter.h"
#include "app_log.h"
#include "n32g43x_start_pins.h"
#include "bsp_focal_api.h"
#include "bsp_pi_api.h"
#include "app_focal_ctrl.h"

void bsp_focal_step_init(GPIO_Module* GPIOx, uint16_t Pin)
{
  GPIO_InitType GPIO_InitStructure;
  EXTI_InitType EXTI_InitStructure;
  NVIC_InitType NVIC_InitStructure;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  /* Enable the GPIO Clock */
  if (GPIOx == GPIOA)
  {
      RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_AFIO, ENABLE);
  }
  else if (GPIOx == GPIOB)
  {
      RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);
  }
  else if (GPIOx == GPIOC)
  {
      RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_AFIO, ENABLE);
  }
  else
  {
      if (GPIOx == GPIOD)
      {
          RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD | RCC_APB2_PERIPH_AFIO, ENABLE);
      }
  }

  /*Configure the GPIO pin as input floating*/
  if (Pin <= GPIO_PIN_ALL)
  {
      GPIO_InitStruct(&GPIO_InitStructure);
      GPIO_InitStructure.Pin        = Pin;
      GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
      GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Input;
      GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
  }
	
	/*Configure key EXTI Line to key input Pin*/
  GPIO_ConfigEXTILine(GPIOC_PORT_SOURCE, GPIO_PIN_SOURCE2);

  /*Configure key EXTI line*/
  EXTI_InitStructure.EXTI_Line    = EXTI_LINE2;
  EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; // EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_InitPeripheral(&EXTI_InitStructure);

  /*Set key input interrupt priority*/
  NVIC_InitStructure.NVIC_IRQChannel                   = EXTI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	
}

void bsp_focal_init_dz24(void)
{
	GPIO_InitType GPIO_InitStructure;

	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_GPIOD, ENABLE);

	GPIO_InitStruct(&GPIO_InitStructure);
  GPIO_InitStructure.Pin        = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_10 | GPIO_PIN_12;
  GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
  GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.Pin        = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
	GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
  GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
	
//	GPIO_InitStructure.Pin        = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8|GPIO_PIN_9;
//	GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
//  GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
//  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
//  GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.Pin        = GPIO_PIN_2;
	GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
  GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitPeripheral(GPIOD, &GPIO_InitStructure);
}


int bsp_focus_run_dz24(u8 run_number,focal_direction_t direction)
{
    focal_run_direct_t direct;
    
    if(direction == E_DIRECTION_STOP)
    {
        bsp_focus_stop_dz24();
        return 0;
    }
    if(direction == 2)
    {
        direct = run_number;
    }
    else if(direction == 1)
    {
        direct = 8 - run_number;
    }
    else
    {
        //bsp_focus_stop_dz24();
        return 0;		
    }
    switch(direct){	
		case 7:
		FOCUS_A_L;
		FOCUS_B_H;
		FOCUS_C_H;
		FOCUS_D_H;
		break;  
		case 6: 
		FOCUS_A_L;
		FOCUS_B_H;
		FOCUS_C_H;
		FOCUS_D_L;
		break;  
		case 5: 
		FOCUS_A_H;
		FOCUS_B_H;
		FOCUS_C_H;
		FOCUS_D_L;
		break;  
		case 4: 
		FOCUS_A_H;
		FOCUS_B_L;
		FOCUS_C_H;
		FOCUS_D_L;
		break;  
		case 3: 
		FOCUS_A_H;
		FOCUS_B_L;
		FOCUS_C_H;
		FOCUS_D_H;
		break;		
		case 2: 
		FOCUS_A_H;
		FOCUS_B_L;
		FOCUS_C_L;
		FOCUS_D_H;
		break;  
		case 1: 
		FOCUS_A_H;
		FOCUS_B_H;
		FOCUS_C_L;
		FOCUS_D_H;
		break;  
		case 0: 
		FOCUS_A_L;
		FOCUS_B_H;
		FOCUS_C_L;
		FOCUS_D_H;
		break;		
		default:
		FOCUS_A_H;
		FOCUS_B_H;
		FOCUS_C_H;
		FOCUS_D_H;
		break;		
	}
		return 1;
}

int bsp_zoom_run_dz24(u8 run_number,focal_direction_t direction)
{
    focal_run_direct_t direct;
    
    if(direction == E_DIRECTION_STOP)
    {
        bsp_zoom_stop_dz24();
        return 0;
    }
    
    if(direction == E_DIRECTION_RUN)//
    {
        direct = run_number;
    }
    else if(direction == E_DIRECTION_RET)
    {
        direct = 8 - run_number;
    }
    else
    {
//        bsp_zoom_stop_dz24();
        return 0;		
    }
switch(direct){	
		case 7:
		ZOOM_A_L;
		ZOOM_B_L;
		ZOOM_C_H;
		ZOOM_D_L;
		break;  
		case 6: 
		ZOOM_A_L;
		ZOOM_B_H;
		ZOOM_C_H;
		ZOOM_D_L;
		break;  
		case 5: 
		ZOOM_A_L;
		ZOOM_B_H;
		ZOOM_C_L;
		ZOOM_D_L;
		break;  
		case 4: 
		ZOOM_A_L;
		ZOOM_B_H;
		ZOOM_C_L;
		ZOOM_D_H;
		break;  
		case 3: 
		ZOOM_A_L;
		ZOOM_B_L;
		ZOOM_C_L;
		ZOOM_D_H;
		break;		
		case 2: 
		ZOOM_A_H;
		ZOOM_B_L;
		ZOOM_C_L;
		ZOOM_D_H;
		break;  
		case 1: 
		ZOOM_A_H;
		ZOOM_B_L;
		ZOOM_C_L;
		ZOOM_D_L;
		break;  
		case 0: 
		ZOOM_A_H;
		ZOOM_B_L;
		ZOOM_C_H;
		ZOOM_D_L;
		break;		
		default:
		ZOOM_A_H;
		ZOOM_B_H;
		ZOOM_C_H;
		ZOOM_D_H;
		break;
	}
		return 1;
}

int bsp_filter_run_dz24(u8 run_number,focal_direction_t direction)
{
    focal_run_direct_t direct;
    
    if(direction == E_DIRECTION_STOP)
    {
        bsp_filter_stop_dz24();
        return 0;
    }
    
    if(direction == E_DIRECTION_RUN)
    {
        direct = run_number;
    }
    else if(direction == E_DIRECTION_RET)
    {
        direct = 8 - run_number;
    }
    else
    {
//        bsp_filter_stop_dz24();
        return 0;			
    }
switch(direct){	
		case 7:
		filter_A_L;
		filter_B_H;
		filter_C_H;
		filter_D_H;
		break;  
		case 6: 
		filter_A_L;
		filter_B_H;
		filter_C_H;
		filter_D_L;
		break;  
		case 5: 
		filter_A_H;
		filter_B_H;
		filter_C_H;
		filter_D_L;
		break;  
		case 4: 
		filter_A_H;
		filter_B_L;
		filter_C_H;
		filter_D_L;
		break;  
		case 3: 
		filter_A_H;
		filter_B_L;
		filter_C_H;
		filter_D_H;
		break;		
		case 2: 
		filter_A_H;
		filter_B_L;
		filter_C_L;
		filter_D_H;
		break;  
		case 1: 
		filter_A_H;
		filter_B_H;
		filter_C_L;
		filter_D_H;
		break;  
		case 0: 
		filter_A_L;
		filter_B_H;
		filter_C_L;
		filter_D_H;
		break;		
		default:
		filter_A_H;
		filter_B_H;
		filter_C_H;
		filter_D_H;
		break;
	}
		return 1;
}

void bsp_focus_stop_dz24(void)
{
	FOCUS_A_L;
	FOCUS_B_L;
	FOCUS_C_L;
	FOCUS_D_L;
}

void bsp_zoom_stop_dz24(void)
{
	ZOOM_A_L;
	ZOOM_B_L;
	ZOOM_C_L;
	ZOOM_D_L;
}

void bsp_filter_stop_dz24(void)
{
	filter_A_L;
	filter_B_L;
	filter_C_L;
	filter_D_L;
}
