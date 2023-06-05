#ifndef __APP_IRIS_H__
#define __APP_IRIS_H__

#include "n32g43x_start_pins.h"
#include "bsp_mult_pwm.h"
#include "n32g43x.h"

#define IRIS_I0_1           io_set_high(GPIOA, GPIO_PIN_12)
#define IRIS_I0_0           io_set_low(GPIOA, GPIO_PIN_12)
#define IRIS_I1_1           io_set_high(GPIOB, GPIO_PIN_3)
#define IRIS_I1_0           io_set_low(GPIOB, GPIO_PIN_3)

#define	IRIS_CW		        io_set_high(GPIOC, GPIO_PIN_5)
#define	IRIS_CCW		    io_set_low(GPIOC, GPIO_PIN_5)

#define	IRIS_power_on		io_set_high(GPIOA, GPIO_PIN_15)
#define	IRIS_power_off		io_set_low(GPIOA, GPIO_PIN_15)

#define	IRIS_CFG_DEV_PWM    PWM_CHANNEL_TIM3_CH2



static volatile uint8_t IrismotorSteps=0;


static void IRIS();
void app_iris_init(void);
void app_iris_gpio_init(void);
void app_iris_poll(void);
void app_iris_poll_run(void);
void IRIS();
void iris_poll();
void iris_poll_bk();
void screen_poll();
void IRIS_19_PI();
void iris_old();
void iris_old_1();
void reset_iris();
void app_iris_poll_1();
void iris_res();
void iris_flag_poll();
void iris_poll_go();
#endif /* __APP_IRIS_H__ */

