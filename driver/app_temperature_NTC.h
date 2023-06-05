/*
 * xxxxxx.h
 *
 * Created:
 *  Author:
 */
#ifndef __APP_TEMPERATURE_NTC_H__
#define __APP_TEMPERATURE_NTC_H__

#include "GMtypes.h"
#include "bsp_pin_ctrl_api.h"
#include "app_temperature_NTC_cfg.h"




// ====================== external function =========================
void app_temperature_NTC_init(void);
int8_t app_temperature_get_laser_tempture(void);
int8_t app_temperature_get_env_tempture(void);
int8_t app_temperature_get_dmd_tempture(void);
int8_t app_temperature_get_cw_tempture(void);
int8_t app_temperature_get_G_led_tempture(void);
int8_t app_temperature_get_R_led_tempture(void);
int8_t app_temperature_get_BP_led_tempture(void);
int8_t app_temperature_get_board_tempture(void);
// ====================== external =========================
// 接口封装
// 此处在.h文件中定义static的函数形式的封装是为了内联(inline)，以达到节省ROM空间
//

static void temp_prj_api_init(void)
{
    app_temperature_NTC_init();
}

static BOOL temp_prj_api_block_get_laser(int8_t *p_ret_value)
{
#if (NTC_CFG_LASER_IS_USE != 0)
    *p_ret_value =  app_temperature_get_laser_tempture();
    return TRUE;
#else
    return FALSE;
#endif
}

static BOOL temp_prj_api_block_get_env(int8_t *p_ret_value)
{
#if (NTC_CFG_ENV_IS_USE != 0)
    *p_ret_value = app_temperature_get_env_tempture();
    return TRUE;
#else
    return FALSE;
#endif
}

static BOOL temp_prj_api_block_get_dmd(int8_t *p_ret_value)
{
#if (NTC_CFG_DMD_IS_USE != 0)
    *p_ret_value = app_temperature_get_dmd_tempture();
    return TRUE;
#else
    return FALSE;
#endif
}

static BOOL temp_prj_api_block_get_cw(int8_t *p_ret_value)
{
#if (NTC_CFG_CW_IS_USE != 0)
    *p_ret_value = app_temperature_get_cw_tempture();
    return TRUE;
#else
    return FALSE;
#endif
}

static BOOL temp_prj_api_block_get_G_led(int8_t *p_ret_value)
{
#if (NTC_CFG_G_LED_IS_USE != 0)
    *p_ret_value = app_temperature_get_G_led_tempture();
    return TRUE;
#else
    return FALSE;
#endif
}

static BOOL temp_prj_api_block_get_R_led(int8_t *p_ret_value)
{
#if (NTC_CFG_R_LED_IS_USE != 0)
    *p_ret_value = app_temperature_get_R_led_tempture();
    return TRUE;
#else
    return FALSE;
#endif
}

static BOOL temp_prj_api_block_get_BP_led(int8_t *p_ret_value)
{
#if (NTC_CFG_BP_LED_IS_USE != 0)
    *p_ret_value = app_temperature_get_BP_led_tempture();
    return TRUE;
#else
    return FALSE;
#endif
}

static BOOL temp_prj_api_block_get_board(int8_t *p_ret_value)
{
#if (NTC_CFG_BOARD_IS_USE != 0)
    *p_ret_value = app_temperature_get_board_tempture();
    return TRUE;
#else
    return FALSE;
#endif
}

// 目前温度传感器无需滤波算法提高精度
static void temp_prj_api_env_filter(void *p){UNUSED(p);}
static void temp_prj_api_laser_filter(void *p){UNUSED(p);}
static void temp_prj_api_dmd_filter(void *p){UNUSED(p);}
static void temp_prj_api_cw_filter(void *p){UNUSED(p);}
static void temp_prj_api_G_led_filter(void *p){UNUSED(p);}
static void temp_prj_api_R_led_filter(void *p){UNUSED(p);}
static void temp_prj_api_BP_led_filter(void *p){UNUSED(p);}
static void temp_prj_api_board_filter(void *p){UNUSED(p);}

#endif

