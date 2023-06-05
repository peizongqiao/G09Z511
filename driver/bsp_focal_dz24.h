/*
 * xxxxxx.h
 *
 * Created: 2019/12/17 16:48:10
 *  Author:
 */
#ifndef BSP_FOCAL_DZ24_H_
#define BSP_FOCAL_DZ24_H_

#include "driver_init.h"
#include "config.h"
#include "bsp_focal_api_types.h"
#include "bsp_focal_dz24_cfg.h"
#include "bsp_focal_api.h"

// ======================== declare ========================
void bsp_focal_init_dz24(void);
//void bsp_focal_step_init(GPIO_Module* GPIOx, uint16_t Pin);

int bsp_focus_run_dz24(u8 run_number,focal_direction_t direction);
int bsp_zoom_run_dz24(u8 run_number,focal_direction_t direction);
int bsp_filter_run_dz24(u8 run_number,focal_direction_t direction);
void bsp_focus_stop_dz24(void);
void bsp_zoom_stop_dz24(void);
void bsp_filter_stop_dz24(void);

// ===================== external function =================
static void bsp_focal_api_init(void)
{
    bsp_focal_init_dz24();
		
}

static int bsp_focus_api_run(u8 run_number,focal_direction_t direction)
{
    return bsp_focus_run_dz24(run_number,direction);
}

static int bsp_zoom_api_run(u8 run_number,focal_direction_t direction)
{
    return bsp_zoom_run_dz24(run_number,direction);
}

static int bsp_filter_api_run(u8 run_number,focal_direction_t direction)
{
    return bsp_filter_run_dz24(run_number,direction);
}

static void bsp_focus_api_stop(void)
{
    bsp_focus_stop_dz24();
}

static void bsp_zoom_api_stop(void)
{
    bsp_zoom_stop_dz24();
}

static void bsp_filter_api_stop(void)
{
    bsp_filter_stop_dz24();
}

static void bsp_time(void)
{
    
}

#endif/* BSP_FOCAL_DZ24_H_ */
