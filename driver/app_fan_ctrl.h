#ifndef __APP_FAN_CTRL_H__
#define __APP_FAN_CTRL_H__

#include "app_log.h"
#include "n32g43x.h" 

typedef struct
{
    // 中断触发计次数
    volatile uint16_t exit_trigger_times;
    // 计算出的风扇速度
    volatile uint16_t calculate_speed;
}measure_t;

typedef struct
{
		measure_t ksl;
		measure_t fan_5516;
		measure_t fan_6025_P1;
		measure_t fan_6025_P2;
		measure_t fan_13038;
}fan_measure_t;


typedef struct
{
    volatile bool fan_now;
    volatile bool fan_last;
}fan_state_t;

typedef struct
{
	fan_state_t ksl;
	fan_state_t fan_5516;
	fan_state_t fan_6025_P1;
	fan_state_t fan_6025_P2;
	fan_state_t fan_13038;
}motor_fan_state_t;

// 配置：周期调用的计数
#define FAN_CFG_TASK_POLL_CYC_MS                            (600u)


// ------------------------ 风扇测速功能 ---------------------
//
// 配置：风扇计算风速系数(转换为r/minutes)
#define FAN_CFG_MEASURE_FACTOR_PERIOD_MINUTE                ((60u*1000u)/FAN_CFG_TASK_POLL_CYC_MS)
#define FAN_CFG_MEASURE_THRESHOLD_SPEED                     (500)


// =================== external function ===================
void app_fan_init(void);
void app_fan_set_run_speed(uint8_t index, uint8_t fan_speed);



#endif


