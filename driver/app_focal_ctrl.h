#ifndef _APP_FOCAL_CTRL_H
#define _APP_FOCAL_CTRL_H

#include "bsp_focal_api_types.h"
#include "n32g43x.h"

typedef struct
{
    u8 focus_run_number;
	u8 zoom_run_number;
	u8 filter_run_number;

    focal_direction_t focus_direction;
    focal_direction_t zoom_direction;
	focal_direction_t filter_direction;
}focal_ctrl_t;

static focal_ctrl_t focal_ctrl;

void focal_init(void);
void focal_diver_poll(void);
void zoom_diver_poll(void);
void focal_ctrl_poll(void);
void zoom_ctrl_poll(void);
void flag_filter();
void filter_poll();
void filter_ctrl_poll(void);
void old(void);
void filter_oold_poll();
void filter_res();
void foacl();
void focal_go();
void zoom_go();
void focal_back_go();
void zoom_back_go();
#endif /* _APP_FOCAL_CTRL_H */