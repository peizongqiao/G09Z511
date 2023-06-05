/*
 * xxxxx.c
 *
 * Created: 2019/8/15 10:32:21
 *  Author:
 */
#include "app_temperature_ctrl.h"
#include "app_temperature_api.h"
#include "config.h"
#include <string.h>
#include "app_mcu_bus.h"
#include "app_softtimer.h"
#include "utils.h"
#include "app_mcu_bus_cfg.h"
#include "../driver/app_log.h"



// ======================== declare ========================
static void app_temperature_poll(void);

int8_t temp_duf[8];

typedef struct
{
    int8_t laser;       // 系统温度(B灯)
    int8_t env;         // 环境温度
    int8_t dmd;         // DMD温度
    int8_t cw;          // 色轮温度
    int8_t G_led;       // G灯
    int8_t R_led;       // R灯
    int8_t BP_led;      // BP灯
    int8_t board;       // 驱动板温度
} temperature_t;

static temperature_t temperature = {0};

/*
* @功能说明:温度功能控制初始化
* @注    意:无
* @形    参:无
* @返    回:无
*/
void app_temperature_init(void)
{
    temp_prj_api_init();
    // 创建周期回调任务
    TASK_PERIOD_CB_CREATE(TEMP_CFG_TASK_POLL_MS*5, app_temperature_poll);
}



static void app_temperature_poll(void)
{
    temperature_t *p_data = &temperature;

    // 1.laser_temperature
    if (TRUE == temp_prj_api_block_get_laser(&p_data->laser)) {
        temp_prj_api_laser_filter((void *)&p_data->laser);
    }

    // 2.env_temperature
    if (TRUE == temp_prj_api_block_get_env(&p_data->env)) {
        temp_prj_api_env_filter((void *)&p_data->env);
    }

    // 3.dmd_temperature
    if (TRUE == temp_prj_api_block_get_dmd(&p_data->dmd)) {
        temp_prj_api_dmd_filter((void *)&p_data->dmd);
    }

    // 4.cw_temperature
    if (TRUE == temp_prj_api_block_get_cw(&p_data->cw)) {
        temp_prj_api_cw_filter((void *)&p_data->cw);
    }

    // 5.G_led_temperature
    if (TRUE == temp_prj_api_block_get_G_led(&p_data->G_led)) {
        temp_prj_api_G_led_filter((void *)&p_data->G_led);
    }

    // 6.R_led_temperature
    if (TRUE == temp_prj_api_block_get_R_led(&p_data->R_led)) {
        temp_prj_api_R_led_filter((void *)&p_data->R_led);
    }

    // 7.BP_led_temperature
    if (TRUE == temp_prj_api_block_get_BP_led(&p_data->BP_led)) {
        temp_prj_api_BP_led_filter((void *)&p_data->BP_led);
    }

    // 8.board_temperature
    if (TRUE == temp_prj_api_block_get_board(&p_data->board)) {
        temp_prj_api_board_filter((void *)&p_data->board);
    }

    // 写温度寄存器
    //mcubus_update_regarea_temperature((uint8_t *)p_data);
		
		
		
		temp_duf[0] = p_data->laser;
		temp_duf[1] = p_data->env;
		temp_duf[2] = p_data->dmd;
		temp_duf[3] = p_data->cw;
		temp_duf[4] = p_data->G_led;
		temp_duf[5] = p_data->R_led;
		temp_duf[6] = p_data->BP_led;
		temp_duf[7] = p_data->board;
//	    log_info("%d\n",temp_duf[0]);
//		log_info("%d\n",temp_duf[1]);
//		log_info("%d\n",temp_duf[2]);
//		log_info("%d\n",temp_duf[3]);
//		log_info("%d\n",temp_duf[4]);
//		log_info("%d\n",temp_duf[5]);
//		log_info("%d\n",temp_duf[6]);
//		log_info("%d\n",temp_duf[7]);

}



// 获取MCU端获取到的环境温度。uints:1℃
int8_t app_temperature_get_env_temp(void)
{
    return temperature.env;
}

// 获取MCU端获取到的系统温度。uints:1℃
int8_t app_temperature_get_laser_temp(void)
{
    return temperature.laser;
}

// 获取MCU端获取到的DMD温度。uints:1℃
int8_t app_temperature_get_dmd_temp(void)
{
    return temperature.dmd;
}

// 获取MCU端获取到的色轮温度。uints:1℃
int8_t app_temperature_get_cw_temp(void)
{
    return temperature.cw;
}

// 获取MCU端获取到的G灯温度。uints:1℃
int8_t app_temperature_get_G_led_temp(void)
{
    return temperature.G_led;
}

// 获取MCU端获取到的R灯温度。uints:1℃
int8_t app_temperature_get_R_led_temp(void)
{
    return temperature.R_led;
}

// 获取MCU端获取到的BP灯温度。uints:1℃
int8_t app_temperature_get_BP_led_temp(void)
{
    return temperature.BP_led;
}

// 获取MCU端获取到的驱动板温度。uints:1℃
int8_t app_temperature_get_board_temp(void)
{
    return temperature.board;
}
