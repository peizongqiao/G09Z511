/*
 * xxxxx.h
 *
 * Created: 2019/8/15 10:31:56
 *  Author:
 */
#ifndef __APP_TEMPERATURE_CTRL_H__
#define __APP_TEMPERATURE_CTRL_H__

#include "GMtypes.h"



// ==================== external function ==================
void app_temperature_init(void);
int8_t app_temperature_get_env_temp(void);
int8_t app_temperature_get_laser_temp(void);
int8_t app_temperature_get_dmd_temp(void);
int8_t app_temperature_get_cw_temp(void);
int8_t app_temperature_get_G_led_temp(void);
int8_t app_temperature_get_R_led_temp(void);
int8_t app_temperature_get_BP_led_temp(void);
int8_t app_temperature_get_board_temp(void);

#endif

