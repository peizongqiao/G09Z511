/*
 * bsp_filtermotor_soft_subdivision.c
 *
 * Created: 2022/12/1
 *  Author:
 * 说    明: 控制直流电机相关API
 *
 */
#include "bsp_filtermotor_soft_subdivision.h"
#include "counter.h"
#include "pwm_basic.h"
#include "bsp_mult_pwm.h"
#include "app_log.h"
#include "bsp_focal_dz24.h"
#include "utils.h"
#include "bsp_filtermotor_soft_subdivision_cfg.h"

#if (FILTERMOTOR_SOFT_SUBDIVISION_LEVEL == 4)
//=====================4细分==============================
static const uint8_t Filtermotor_phase_cos_1_duty[16] = {
    50, 50, 50, 50, 50, 31, 15, 4, 0, 4, 15, 31, 50, 50, 50, 50
};

static const uint8_t Filtermotor_phase_cos_2_duty[16] = {
    0, 4, 15, 31, 50, 50, 50, 50, 50, 50, 50, 50, 50, 31, 15, 4
};

static const uint8_t Filtermotor_phase_sin_1_duty[16] = {
    50, 50, 50, 50, 50, 50, 50, 50, 50, 31, 15, 4, 0, 4, 15, 31
};

static const uint8_t Filtermotor_phase_sin_2_duty[16] = {
    50, 31, 15, 4, 0, 4, 15, 31, 50, 50, 50, 50, 50, 50, 50, 50
};
#elif (FILTERMOTOR_SOFT_SUBDIVISION_LEVEL == 8)
//=====================8细分==============================
static const uint8_t Filtermotor_phase_cos_1_duty[32] = {
    50, 50, 50, 50, 50, 50, 50, 50, 50, 40, 31, 22, 15, 9, 4, 1, 0, 1, 4, 9, 15, 22, 31, 40, 50, 50, 50, 50, 50, 50, 50, 50
};

static const uint8_t Filtermotor_phase_cos_2_duty[32] = {
    0, 1, 4, 9, 15, 22, 31, 40, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 40, 31, 22, 15, 9, 4, 1
};

static const uint8_t Filtermotor_phase_sin_1_duty[32] = {
    50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 40, 31, 22, 15, 9, 4, 1, 0, 1, 4, 9, 15, 22, 31, 40
};

static const uint8_t Filtermotor_phase_sin_2_duty[32] = {
    50, 40, 31, 22, 15, 9, 4, 1, 0, 1, 4, 9, 15, 22, 31, 40, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50
};
#elif (FILTERMOTOR_SOFT_SUBDIVISION_LEVEL == 16)
//=====================16细分==============================
static const uint8_t Filtermotor_phase_cos_1_duty[64] = {
    50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,45 ,40 ,36 ,31 ,27 ,22 ,19 ,15 ,12 ,9 ,6 ,4 ,2 ,1 ,0 ,0 ,0 ,1 ,2 ,4 ,6 ,9 ,12 ,15 ,19 ,22 ,27 ,31 ,36 ,40 ,45 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50
};

static const uint8_t Filtermotor_phase_cos_2_duty[64] = {
    0 ,0 ,1 ,2 ,4 ,6 ,9 ,12 ,15 ,19 ,22 ,27 ,31 ,36 ,40 ,45 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,45 ,40 ,36 ,31 ,27 ,22 ,19 ,15 ,12 ,9 ,6 ,4 ,2 ,1 ,0
};

static const uint8_t Filtermotor_phase_sin_1_duty[64] = {
    50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,45 ,40 ,36 ,31 ,27 ,22 ,19 ,15 ,12 ,9 ,6 ,4 ,2 ,1 ,0 ,0 ,0 ,1 ,2 ,4 ,6 ,9 ,12 ,15 ,19 ,22 ,27 ,31 ,36 ,40 ,45
};

static const uint8_t Filtermotor_phase_sin_2_duty[64] = {
    50 ,45 ,40 ,36 ,31 ,27 ,22 ,19 ,15 ,12 ,9 ,6 ,4 ,2 ,1 ,0 ,0 ,0 ,1 ,2 ,4 ,6 ,9 ,12 ,15 ,19 ,22 ,27 ,31 ,36 ,40 ,45 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50 ,50
};
#endif

typedef struct filtermotor_soft_subdivision_t {
    uint8_t     subdivision_phase;              //当前时序位置
    uint32_t    subdivision_delay;              //每两步中间的时间间隔
    uint8_t     subdivision_duty_A1;            //细分占空比A控制脚
    uint8_t     subdivision_duty_A2;            //细分占空比A控制脚
    uint8_t     subdivision_duty_B1;            //细分占空比B控制脚
    uint8_t     subdivision_duty_B2;            //细分占空比B控制脚
} filtermotor_ctl_t;

static filtermotor_ctl_t filtermotor_ctl;

void filtermotor_delay_us(uint16_t us)  //0.917us
{
    delay_us_block(us);
}

static void filtermortor_run_PWM_A1(uint8_t duty)
{
    bsp_pwm_set_dutycycle_TIM1_8(7, duty);
}

static void filtermortor_run_PWM_A2(uint8_t duty)
{
    bsp_pwm_set_dutycycle_TIM1_8(8, duty);
}

static void filtermortor_run_PWM_B1(uint8_t duty)
{
    bsp_pwm_set_dutycycle_TIM1_8(9, duty);
}

static void filtermortor_run_PWM_B2(uint8_t duty)
{
    bsp_pwm_set_dutycycle_TIM1_8(10, duty);
}

/*
* @功能说明:电机初始化
* @注    意:无
* @形    参:无
* @返    回:无
*/
void bsp_filtermotor_init_soft_subdivision(void)
{
    memset(&filtermotor_ctl, 0, sizeof(filtermotor_ctl_t));
    filtermortor_run_PWM_A1(0);
    filtermortor_run_PWM_A2(0);
    filtermortor_run_PWM_B1(0);
    filtermortor_run_PWM_B2(0);
}

/*
* @功能说明:设置电机运行
* @注    意:无
* @形    参:[in]step：设置运行的步数
           [in]pps：电机运行的速度
*          [in]direct:方向，stepmotor_run_direct_t取值。
* @返    回:无
*/
void bsp_filtermotor_run_soft_subdivision(uint32_t pps, uint32_t step, filtermotor_run_direct_t direct)
{
    uint32_t i = 0;
    filtermotor_ctl_t *m_p_motor_obj = &filtermotor_ctl;

    m_p_motor_obj->subdivision_delay = (uint16_t)((1000000/pps));
    if(direct == E_DIRECT_OPEN) {
        for(i = 0; i < step; i++) {
            if (E_DIRECT_LEFT == FILTERMOTOR_STRUCTURE_DIRECT){
                m_p_motor_obj->subdivision_duty_A1 = Filtermotor_phase_cos_1_duty[m_p_motor_obj->subdivision_phase];
                m_p_motor_obj->subdivision_duty_A2 = Filtermotor_phase_cos_2_duty[m_p_motor_obj->subdivision_phase];
                m_p_motor_obj->subdivision_duty_B1 = Filtermotor_phase_sin_1_duty[m_p_motor_obj->subdivision_phase];
                m_p_motor_obj->subdivision_duty_B2 = Filtermotor_phase_sin_2_duty[m_p_motor_obj->subdivision_phase];
            }else if (E_DIRECT_RIGHT == FILTERMOTOR_STRUCTURE_DIRECT){
                m_p_motor_obj->subdivision_duty_A1 = Filtermotor_phase_sin_1_duty[m_p_motor_obj->subdivision_phase];
                m_p_motor_obj->subdivision_duty_A2 = Filtermotor_phase_sin_2_duty[m_p_motor_obj->subdivision_phase];
                m_p_motor_obj->subdivision_duty_B1 = Filtermotor_phase_cos_1_duty[m_p_motor_obj->subdivision_phase];
                m_p_motor_obj->subdivision_duty_B2 = Filtermotor_phase_cos_2_duty[m_p_motor_obj->subdivision_phase];
            }
            filtermortor_run_PWM_A1(m_p_motor_obj->subdivision_duty_A1);
            filtermortor_run_PWM_A2(m_p_motor_obj->subdivision_duty_A2);
            filtermortor_run_PWM_B1(m_p_motor_obj->subdivision_duty_B1);
            filtermortor_run_PWM_B2(m_p_motor_obj->subdivision_duty_B2);
            m_p_motor_obj->subdivision_phase++;
            if(m_p_motor_obj->subdivision_phase == sizeof(Filtermotor_phase_sin_1_duty)) {
                m_p_motor_obj->subdivision_phase = 0;
            }
            filtermotor_delay_us(m_p_motor_obj->subdivision_delay);
        }
    } else if(direct == E_DIRECT_CLOSE) {
        for(i = 0; i < step; i++) {
            if (E_DIRECT_LEFT == FILTERMOTOR_STRUCTURE_DIRECT){
                m_p_motor_obj->subdivision_duty_A1 = Filtermotor_phase_sin_1_duty[m_p_motor_obj->subdivision_phase];
                m_p_motor_obj->subdivision_duty_A2 = Filtermotor_phase_sin_2_duty[m_p_motor_obj->subdivision_phase];
                m_p_motor_obj->subdivision_duty_B1 = Filtermotor_phase_cos_1_duty[m_p_motor_obj->subdivision_phase];
                m_p_motor_obj->subdivision_duty_B2 = Filtermotor_phase_cos_2_duty[m_p_motor_obj->subdivision_phase];
            }else if (E_DIRECT_RIGHT == FILTERMOTOR_STRUCTURE_DIRECT) {
                m_p_motor_obj->subdivision_duty_A1 = Filtermotor_phase_cos_1_duty[m_p_motor_obj->subdivision_phase];
                m_p_motor_obj->subdivision_duty_A2 = Filtermotor_phase_cos_2_duty[m_p_motor_obj->subdivision_phase];
                m_p_motor_obj->subdivision_duty_B1 = Filtermotor_phase_sin_1_duty[m_p_motor_obj->subdivision_phase];
                m_p_motor_obj->subdivision_duty_B2 = Filtermotor_phase_sin_2_duty[m_p_motor_obj->subdivision_phase];
            }
            filtermortor_run_PWM_A1(m_p_motor_obj->subdivision_duty_A1);
            filtermortor_run_PWM_A2(m_p_motor_obj->subdivision_duty_A2);
            filtermortor_run_PWM_B1(m_p_motor_obj->subdivision_duty_B1);
            filtermortor_run_PWM_B2(m_p_motor_obj->subdivision_duty_B2);
            m_p_motor_obj->subdivision_phase++;
            if(m_p_motor_obj->subdivision_phase == sizeof(Filtermotor_phase_sin_1_duty)) {
                m_p_motor_obj->subdivision_phase = 0;
            }
            filtermotor_delay_us(m_p_motor_obj->subdivision_delay);
        }
    }
}



/*
* @功能说明:电机停止
* @注    意:无
* @形    参:无
* @返    回:无
*/
void bsp_filtermotor_stop_soft_subdivision(void)
{
    filtermortor_run_PWM_A1(0);
    filtermortor_run_PWM_A2(0);
    filtermortor_run_PWM_B1(0);
    filtermortor_run_PWM_B2(0);
}




