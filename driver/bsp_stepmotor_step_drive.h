/*
 * xxxxxx.h
 *
 * Created: 2019/12/17 16:48:10
 *  Author:
 */
#ifndef _BSP_STEPMOTER_STEP_DRIVE_H_
#define _BSP_STEPMOTER_STEP_DRIVE_H_

#include "driver_init.h"
#include "config.h"
#include "bsp_stepmotor_api_types.h"
#include "bsp_stepmotor_step_drive_cfg.h"


#define PHASE_TAB_LEN                                      4

#define BIT_F_A1                                        0X08
#define BIT_F_A2                                        0X04
#define BIT_F_B1                                        0X02
#define BIT_F_B2                                        0X01

#define MOTER_STOP_PHASE                                0X00


// ======================== declare ========================
void bsp_motor_init_step(void);
void bsp_motor_run_step(uint32_t pps, uint32_t step, stepmotor_run_direct_t direct);
void bsp_motor_stop_step(void);







// ===================== external function =================
static void bsp_stepmotor_api_device_init(void)
{
    bsp_motor_init_step();
}

static void bsp_stepmotor_api_run(uint32_t pps, uint32_t step, stepmotor_run_direct_t direct)
{
    bsp_motor_run_step(pps, step, direct);
}

static void bsp_stepmotor_api_stop(void)
{
    bsp_motor_stop_step();
}






#endif
