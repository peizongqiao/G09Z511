/*
 * xxxxxx.h
 *
 * Created: 2019/12/17 16:48:10
 *  Author:
 */
#ifndef _BSP_FILTERMOTOR_SOFT_SUBDIVISION_H_
#define _BSP_FILTERMOTOR_SOFT_SUBDIVISION_H_

#include "driver_init.h"
#include "config.h"
#include "bsp_filtermotor_api_types.h"
#include "bsp_filtermotor_soft_subdivision_cfg.h"






// ======================== declare ========================
void bsp_filtermotor_init_soft_subdivision(void);
void bsp_filtermotor_run_soft_subdivision(uint32_t pps, uint32_t step,filtermotor_run_direct_t direct);
void bsp_filtermotor_stop_soft_subdivision(void);







// ===================== external function =================
static void bsp_filtermotor_api_device_init(void)
{
    bsp_filtermotor_init_soft_subdivision();
}

static void bsp_filtermotor_api_run(uint32_t pps, uint32_t step, filtermotor_run_direct_t direct)
{
    bsp_filtermotor_run_soft_subdivision(pps, step, direct);
}

static void bsp_filtermotor_api_stop(void)
{
    bsp_filtermotor_stop_soft_subdivision();
}






#endif
