/*
 * xxxx.h
 *
 * Created: 2019/12/17 16:48:10
 *  Author:
 */
#ifndef BSP_FOCAL_API_H_
#define BSP_FOCAL_API_H_

#include "bsp_focal_api_types.h"
#include "n32g43x.h"

static void bsp_focal_api_init(void);

static int bsp_focus_api_run(u8 run_number,focal_direction_t direction);

static int bsp_zoom_api_run(u8 run_number,focal_direction_t direction);

static int bsp_filter_api_run(u8 run_number,focal_direction_t direction);

static void bsp_focus_api_stop(void);

static void bsp_zoom_api_stop(void);

static void bsp_filter_api_stop(void);

static void bsp_time(void);

#include "bsp_focal_dz24.h"


#endif /* BSP_FOCAL_API_H_ */