/*
 * xxxxx.c
 *
 * Created: 2018/10/10 14:53:06
 *  Author:
 * 温度采集，使用NTC传感器。ADC采样，均值滤波，通过查表得出温度值。
 *
 */
#include "GMtypes.h"
#include "adc_basic.h"
#include "bsp_adc.h"
#include "app_temperature_NTC.h"
#include "utils.h"
#include "app_log.h"


typedef struct
{
    filter_ctrl_t filter[8];
}temper_NTC_ctrl_t;

temper_NTC_ctrl_t temper_NTC_ctrl = {0};




void app_temperature_NTC_init(void)
{
    #define NTC_FILTER_AVG_SIZES    15u
    static uint16_t filter_buff[8][NTC_FILTER_AVG_SIZES] = {0};

    for(uint8_t i=0; i<ARRAY_SIZE(temper_NTC_ctrl.filter); i++)
    {
        temper_NTC_ctrl.filter[i].sizes = NTC_FILTER_AVG_SIZES;
        temper_NTC_ctrl.filter[i].p_buff = &filter_buff[i][0];
    }
}



// ntc电压计算。uints:mv
uint16_t adc_get_NTC_voltage(uint8_t ntc_adc_channel)
{
    uint32_t adc_measurement = 0;

		adc_measurement = bsp_adc_get_value_block(ntc_adc_channel);
    adc_measurement *= NTC_CFG_ADC2VOL_FACTOR;
    adc_measurement = adc_measurement/1000;
    return adc_measurement;
}

// 读取激光系统温度
int8_t app_temperature_get_laser_tempture(void)
{
    // 读取电压值
    uint16_t laser_voltage = adc_get_NTC_voltage(NTC_CFG_LASER_ADC_CHANNEL);
    laser_voltage = filter_avg(&temper_NTC_ctrl.filter[0], laser_voltage);
    return find_sequential_2dimension(NTC_CFG_LASER_VOL2TEMP_TABLE, \
            ARRAY_SIZE(NTC_CFG_LASER_VOL2TEMP_TABLE), laser_voltage);
}

// 读取环境温度
int8_t app_temperature_get_env_tempture(void)
{
    // 读取电压值
    uint16_t env_voltage = adc_get_NTC_voltage(NTC_CFG_ENV_ADC_CHANNEL);
    env_voltage = filter_avg(&temper_NTC_ctrl.filter[1], env_voltage);
    return find_sequential_2dimension(NTC_CFG_ENV_VOL2TEMP_TABLE, \
            ARRAY_SIZE(NTC_CFG_ENV_VOL2TEMP_TABLE), env_voltage);
}

// 读取DMD温度
int8_t app_temperature_get_dmd_tempture(void)
{
    // 读取电压值
    uint16_t dmd_voltage = adc_get_NTC_voltage(NTC_CFG_DMD_ADC_CHANNEL);
    dmd_voltage = filter_avg(&temper_NTC_ctrl.filter[2], dmd_voltage);
    return find_sequential_2dimension(NTC_CFG_DMD_VOL2TEMP_TABLE, \
            ARRAY_SIZE(NTC_CFG_DMD_VOL2TEMP_TABLE), dmd_voltage);
}

// 读取色轮温度
int8_t app_temperature_get_cw_tempture(void)
{
    // 读取电压值
    uint16_t cw_voltage = adc_get_NTC_voltage(NTC_CFG_CW_ADC_CHANNEL);
    cw_voltage = filter_avg(&temper_NTC_ctrl.filter[3], cw_voltage);
    return find_sequential_2dimension(NTC_CFG_CW_VOL2TEMP_TABLE, \
            ARRAY_SIZE(NTC_CFG_CW_VOL2TEMP_TABLE), cw_voltage);
}

// 读取G灯温度
int8_t app_temperature_get_G_led_tempture(void)
{
    // 读取电压值
    uint16_t G_led_voltage = adc_get_NTC_voltage(NTC_CFG_G_LED_ADC_CHANNEL);
    G_led_voltage = filter_avg(&temper_NTC_ctrl.filter[4], G_led_voltage);
    return find_sequential_2dimension(NTC_CFG_G_LED_VOL2TEMP_TABLE, \
            ARRAY_SIZE(NTC_CFG_G_LED_VOL2TEMP_TABLE), G_led_voltage);
}

// 读取R灯温度
int8_t app_temperature_get_R_led_tempture(void)
{
    // 读取电压值
    uint16_t R_led_voltage = adc_get_NTC_voltage(NTC_CFG_R_LED_ADC_CHANNEL);
    R_led_voltage = filter_avg(&temper_NTC_ctrl.filter[5], R_led_voltage);
    return find_sequential_2dimension(NTC_CFG_R_LED_VOL2TEMP_TABLE, \
            ARRAY_SIZE(NTC_CFG_R_LED_VOL2TEMP_TABLE), R_led_voltage);
}

// 读取BP灯温度
int8_t app_temperature_get_BP_led_tempture(void)
{
    // 读取电压值
    uint16_t BP_led_voltage = adc_get_NTC_voltage(NTC_CFG_BP_LED_ADC_CHANNEL);
    BP_led_voltage = filter_avg(&temper_NTC_ctrl.filter[6], BP_led_voltage);
    return find_sequential_2dimension(NTC_CFG_BP_LED_VOL2TEMP_TABLE, \
            ARRAY_SIZE(NTC_CFG_BP_LED_VOL2TEMP_TABLE), BP_led_voltage);
}

// 读取BP灯温度
int8_t app_temperature_get_board_tempture(void)
{
    // 读取电压值
    uint16_t board_voltage = adc_get_NTC_voltage(NTC_CFG_BOARD_ADC_CHANNEL);
    board_voltage = filter_avg(&temper_NTC_ctrl.filter[7], board_voltage);
    return find_sequential_2dimension(NTC_CFG_BOARD_VOL2TEMP_TABLE, \
            ARRAY_SIZE(NTC_CFG_BOARD_VOL2TEMP_TABLE), board_voltage);
}

