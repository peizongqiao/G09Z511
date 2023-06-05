#include "../driver/app_fan_ctrl.h"
#include <driver_init.h>
#include "../driver/app_log.h"
#include "../driver/app_softtimer.h"
#include "../driver/app_mcu_bus_cfg.h"

motor_fan_state_t motor_fan_state;
fan_measure_t fan_measure;

uint16_t ksl_speed,fan_5516_speed,fan_6025_P1_speed,fan_6025_P2_speed,fan_13038_speed;

void app_fan_init(void);
void app_fan_tack(void);
void app_fan_poll(void);

void app_fan_init(void)
{
		GPIO_InitType GPIO_InitStructure;
		
		RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
		RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
	
		GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin        = GPIO_PIN_8 | GPIO_PIN_11;
    GPIO_InitStructure.GPIO_Pull  = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Input;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
		
		GPIO_InitStructure.Pin        = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStructure.GPIO_Pull  = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Input;
    GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
		
    TASK_PERIOD_CB_CREATE(5, app_fan_tack);
		TASK_PERIOD_CB_CREATE(FAN_CFG_TASK_POLL_CYC_MS*5, app_fan_poll);
	
		motor_fan_state.ksl.fan_now = 1;
		motor_fan_state.fan_5516.fan_now = 1;
		motor_fan_state.fan_6025_P1.fan_now = 1;
		motor_fan_state.fan_6025_P2.fan_now = 1;
		motor_fan_state.fan_13038.fan_now = 1;
}



void app_fan_tack(void)
{
		motor_fan_state.ksl.fan_now = GPIO_ReadInputDataBit(GPIOC,GPIO_PIN_13);
		motor_fan_state.fan_5516.fan_now = GPIO_ReadInputDataBit(GPIOC,GPIO_PIN_14);
		motor_fan_state.fan_6025_P1.fan_now = GPIO_ReadInputDataBit(GPIOC,GPIO_PIN_15);
		motor_fan_state.fan_6025_P2.fan_now = GPIO_ReadInputDataBit(GPIOA,GPIO_PIN_8);
		motor_fan_state.fan_13038.fan_now = GPIO_ReadInputDataBit(GPIOA,GPIO_PIN_11);
	
		//if(0 == motor_fan_state.ksl.fan_now && 1 == motor_fan_state.ksl.fan_last)
		if(motor_fan_state.ksl.fan_now != motor_fan_state.ksl.fan_last)
		{
			fan_measure.ksl.exit_trigger_times++;
		}
		//if(0 == motor_fan_state.fan_5516.fan_now && 1 == motor_fan_state.fan_5516.fan_last)
		if(motor_fan_state.fan_5516.fan_now != motor_fan_state.fan_5516.fan_last)
		{
			fan_measure.fan_5516.exit_trigger_times++;
		}
		//if(0 == motor_fan_state.fan_6025_P1.fan_now && 1 == motor_fan_state.fan_6025_P1.fan_last)
		if(motor_fan_state.fan_6025_P1.fan_now != motor_fan_state.fan_6025_P1.fan_last)
		{
			fan_measure.fan_6025_P1.exit_trigger_times++;
		}
		//if(0 == motor_fan_state.fan_6025_P2.fan_now && 1 == motor_fan_state.fan_6025_P2.fan_last)
		if(motor_fan_state.fan_6025_P2.fan_now != motor_fan_state.fan_6025_P2.fan_last)
		{
			fan_measure.fan_6025_P2.exit_trigger_times++;
		}
		//if(0 == motor_fan_state.fan_13038.fan_now && 1 == motor_fan_state.fan_13038.fan_last)
		if(motor_fan_state.fan_13038.fan_now != motor_fan_state.fan_13038.fan_last)
		{
			fan_measure.fan_13038.exit_trigger_times++;
		}
		
		motor_fan_state.ksl.fan_last =  motor_fan_state.ksl.fan_now;
		motor_fan_state.fan_5516.fan_last =  motor_fan_state.fan_5516.fan_now;
		motor_fan_state.fan_6025_P1.fan_last =  motor_fan_state.fan_6025_P1.fan_now;
		motor_fan_state.fan_6025_P2.fan_last =  motor_fan_state.fan_6025_P2.fan_now;
		motor_fan_state.fan_13038.fan_last =  motor_fan_state.fan_13038.fan_now;
}

void app_fan_poll(void)
{
//		log_info("ksl = %d\n\r",fan_measure.ksl.exit_trigger_times);
//		log_info("fan_5516 = %d\n\r",fan_measure.fan_5516.exit_trigger_times);
//		log_info("fan_6025_P1 = %d\n\r",fan_measure.fan_6025_P1.exit_trigger_times);
//		log_info("fan_6025_P2 = %d\n\r",fan_measure.fan_6025_P2.exit_trigger_times);
//		log_info("fan_13038 = %d\n\r",fan_measure.fan_13038.exit_trigger_times);
	
		fan_measure.ksl.calculate_speed =  FAN_CFG_MEASURE_FACTOR_PERIOD_MINUTE * fan_measure.ksl.exit_trigger_times;
		fan_measure.fan_5516.calculate_speed =  FAN_CFG_MEASURE_FACTOR_PERIOD_MINUTE * fan_measure.fan_5516.exit_trigger_times;
		fan_measure.fan_6025_P1.calculate_speed =  FAN_CFG_MEASURE_FACTOR_PERIOD_MINUTE * fan_measure.fan_6025_P1.exit_trigger_times;
		fan_measure.fan_6025_P2.calculate_speed =  FAN_CFG_MEASURE_FACTOR_PERIOD_MINUTE * fan_measure.fan_6025_P2.exit_trigger_times;
		fan_measure.fan_13038.calculate_speed =  FAN_CFG_MEASURE_FACTOR_PERIOD_MINUTE * fan_measure.fan_13038.exit_trigger_times;
	
		fan_measure.ksl.exit_trigger_times = 0;
		fan_measure.fan_5516.exit_trigger_times = 0;
		fan_measure.fan_6025_P1.exit_trigger_times = 0;
		fan_measure.fan_6025_P2.exit_trigger_times = 0;
		fan_measure.fan_13038.exit_trigger_times = 0;
	
		ksl_speed = fan_measure.ksl.calculate_speed;
		fan_5516_speed = fan_measure.fan_5516.calculate_speed; 
		fan_6025_P1_speed = fan_measure.fan_6025_P1.calculate_speed;
		fan_6025_P2_speed  = fan_measure.fan_6025_P2.calculate_speed;
		fan_13038_speed = fan_measure.fan_13038.calculate_speed;
	
//		log_info("ksl_speed = %d\n\r",ksl_speed);
//		log_info("fan_5516_speed = %d\n\r",fan_5516_speed);
//		log_info("fan_6025_P1_speed = %d\n\r",fan_6025_P1_speed);
//		log_info("fan_6025_P2_speed = %d\n\r",fan_6025_P2_speed);
//		log_info("fan_13038_speed = %d\n\r",fan_13038_speed);
}
