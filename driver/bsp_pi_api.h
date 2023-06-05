#ifndef __BSP_PI_API_H__
#define __BSP_PI_API_H__

#include "n32g43x.h" 
#include "bsp_pi_cfg.h"
#include "app_log.h"
#include "bsp_adc.h"

static void bsp_pi_api_init(void);

static bool PI_check(uint8_t channal, float value);
static bool DF_PI_check(uint8_t channal, float value);

static bool FocusMotorWait(void);
static bool ZoomMotorWait(void);
static bool DoorMotorWait(void);
static bool IrisMotorWait(void);

static void bsp_pi_api_init(void)
{
    //
}

static bool PI_check(uint8_t channal, float value)
{
    float v;
	
    v = (float)ADC_GetData(channal)*3.3/1023;
    if(v > value)
		return false;   //PI未遮挡大于1.1V

	else
		return true;
}

static bool DF_PI_check(uint8_t channal, float value)
{
    float v;
	
    v = (float)ADC_GetData(channal)*3.3/1023;
    if(v > value)
		return false;   //PI未遮挡大于1.1V

	else
		return true;
}

static bool FocusMotorWait()
{
    if( PI_check(FOCUS_PI, 1))
    {
		return true;
	}else{
		return false;
	}
}

static bool ZoomMotorWait()
{
    if( PI_check(ZOOM_PI, 2.8))
    {
		return true;
	}else{
		return false;
	}
}

static bool DoorMotorWait()
{
    if( PI_check(VALVE_PI, 1))
    {
		return true;
	}else{
		return false;
	}
}

static bool IrisMotorWait()
{
    if( PI_check(IRIS_PI, 0.2))
    {
		return true;
	}else{
		return false;
	}
}

static bool FilterMotorWait()
{
    if( DF_PI_check(FILTER_PI, 1.5))
    {
		return true;//没有遮挡PI
	}else{
		return false;// 遮挡PI
	}
}

#endif /* __BSP_PI_API_H__ */
