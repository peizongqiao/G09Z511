/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file main.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include "i2c_master.h"
#include "dlp_manager.h"
#include "bsp_uart.h"
#include "../driver/bsp_adc.h"
#include "../driver/adc_basic.h"
#include "../driver/driver_init.h"
#include "bsp_mult_pwm.h"
#include "../driver/app_log.h"
#include "../driver/app_softtimer.h"
#include "../driver/clkctrl.h"
//#include "app_focal_ctrl.h"
#include "i2c_slave_N32G43X.h"
#include <math.h>
#include "app_focal_ctrl.h"
#include "app_iris.h"
#include "app_temperature_ctrl.h"
#include "i2c2_slave_N32G43X.h"
#include "i2c_master_1.h"
#include "bsp_pi_api.h"

volatile int i = 0,TEMP_FLAG_cnt=0;
float v,vol;
static uint16_t c;
extern bool flag_1ms;
extern bool flag_900us;
extern bool flag_20ms;
extern uint8_t flag_count;
uint16_t printf_temp;
uint16_t close_temp;
bool flag_temp = false;
int8_t tepm_r;
int8_t tepm_g;
int8_t tepm_b;
int8_t tepm_bp;
int8_t tepm_dr;


//void print_temp();
void LedInit(GPIO_Module* GPIOx, uint16_t Pin);
void LedOff(GPIO_Module* GPIOx, uint16_t Pin);
void LedOn(GPIO_Module* GPIOx, uint16_t Pin);
//-----------------------------------------------------------------------
//register address(command)
#define REG_TEMP_SET	0x01
#define REG_TEMP_OFFS	0x02
#define REG_P			0x05
#define REG_I			0x06
#define REG_D			0x07

#define OLED_ONOFF			0x08


#define FAN_NUM 4

uint8_t FANPWM,FANPWM_1,FANPWM_2,FANPWM_3,FANPWM_4;
float temp[7] = {0};

#define  TOGLE_TESTPIN   VPORTA_IN =1<<6;   //测试PIN
#define  SPI0_CS_L  PORTA_set_pin_le\vel(4, false);
#define  SPI0_CS_H  PORTA_set_pin_level(4, true);

#define  PWR_ON_L  PORTC_set_pin_level(0, false);
#define  PWR_ON_H  PORTC_set_pin_level(0, true);

#define  PROJ_ON_L  PORTC_set_pin_level(1, false);
#define  PROJ_ON_H  PORTC_set_pin_level(1, true);


//long data buffer memory structure
typedef struct _MB_REG_COMM_BUF
{
	uint8_t len;
	uint8_t data[256];
}MB_REG_COMM_BUF_t;

//register topology structure
typedef struct _MCUBUS_REG_AREA
{
	uint8_t dev_status;
	float temp_set[5];	//设置温度
	float temp[5];			//实际温度
	float temp_offs[5];
	float fanspeed[5];	//风速
	uint16_t P;
	uint16_t I;
	uint16_t D;
	uint8_t oled_onoff;
	uint8_t ver;
	volatile int keep_alive;
}MCUBUS_REG_AREA_t;


MCUBUS_REG_AREA_t g_t_reg;

void mcubus_cmd_cb(uint8_t cmdval, MB_REG_COMM_BUF_t *cmd_buf)
{
	g_t_reg.keep_alive = 50;
	if (cmd_buf->len != 0) {
		switch (cmdval) {
		case REG_TEMP_SET:
			if (cmd_buf->len == sizeof(g_t_reg.temp_set)) {
				memcpy(g_t_reg.temp_set, cmd_buf->data, sizeof(g_t_reg.temp_set));
			}
			break;
		case REG_TEMP_OFFS:
			if (cmd_buf->len == sizeof(g_t_reg.temp_offs)) {
				memcpy(g_t_reg.temp_offs, cmd_buf->data, sizeof(g_t_reg.temp_offs));		
			}
			break;
		case REG_P:
			if (cmd_buf->len == sizeof(g_t_reg.P)) {
				memcpy(&g_t_reg.P, cmd_buf->data, sizeof(g_t_reg.P));
			}
			break;
		case REG_I:
			if (cmd_buf->len == sizeof(g_t_reg.I)) {
 				memcpy(&g_t_reg.I, cmd_buf->data, sizeof(g_t_reg.I));
			}
			break;
		case REG_D:
			if (cmd_buf->len == sizeof(g_t_reg.D)) {
				memcpy(&g_t_reg.D, cmd_buf->data, sizeof(g_t_reg.D));
			}
			break;
		case OLED_ONOFF:
			if (cmd_buf->len == sizeof(g_t_reg.oled_onoff)) {
				memcpy(&g_t_reg.oled_onoff, cmd_buf->data, sizeof(g_t_reg.oled_onoff));
			}
			break;
		}
		//config_write((uint8_t *)&g_t_reg, sizeof(g_t_reg));
	}
}


static uint8_t PIDCalc( float Sv, float Pv)  // Sv设定温度值  Pv当前温度值
{
  float DERR1 = 0;       //
  float DERR2 = 0;       //

  float Pout = 0;       //比例结果
  float Iout = 0;       //积分结果
  float Dout = 0;       //微分结果
  int16_t Out = 0; //总输出
  static uint8_t Out1;  //记录上次输出

  static float ERR;       //当前误差
  static float ERR1;      //上次误差
  static float ERR2;      //上上次误差

  /******************
  *以下四项是需要根据实际情况调试的
  ******************/
  static uint8_t pidt = 100;     //300MS计算一次 计算周期
  char Kp = g_t_reg.P;       //比例系数
  uint16_t Ti= g_t_reg.I; //积分时间
  uint16_t Td= g_t_reg.D; //微分时间

  static unsigned char Upper_Limit= 100; //PID输出上限
  static unsigned char Lower_Limit= 0; //PID输出下限

  ERR = Pv - Sv;   //算出当前误差
  DERR1 = ERR - ERR1;   //上次
  DERR2 = ERR - 2 * ERR1 + ERR2; //上上次

  Pout = Kp * DERR1;    //输出P
  Iout = (float)(ERR * ((float)(Kp * pidt) / Ti));  //输出I
  Dout = (float)(DERR2 * ((float)(Kp * Td) / pidt));   //输出D
//  Out = (unsigned int)(Out1 + Pout + Iout + Dout);
//  cout << "Pout: " << Pout << ", Iout: " << Iout << endl;
  Out = (Out1 + Pout + Iout);

  if(Out >= Upper_Limit)   //如果输出大于等于上限
  {
    Out = Upper_Limit;
  }
  else if(Out <= Lower_Limit)  //如果输出小于等于下线
  {
    Out = Lower_Limit;
  }
  
  if (Pv < -50) {
	  Out = 100;
  }
  Out1 = Out;      //记录这次输出的值

  ERR2 = ERR1;    //记录误差
  ERR1 = ERR;     //记录误差
  
  return Out1;
}

static uint8_t PIDCalc1( float Sv, float Pv)  // Sv设定温度值  Pv当前温度值
{
  float DERR1 = 0;       //
  float DERR2 = 0;       //

  float Pout = 0;       //比例结果
  float Iout = 0;       //积分结果
  float Dout = 0;       //微分结果
  int16_t Out = 0; //总输出
  static uint8_t Out1;  //记录上次输出

  static float ERR;       //当前误差
  static float ERR1;      //上次误差
  static float ERR2;      //上上次误差

  /******************
  *以下四项是需要根据实际情况调试的
  ******************/
  static uint8_t pidt = 100;     //300MS计算一次 计算周期
  char Kp = g_t_reg.P;       //比例系数
  uint16_t Ti= g_t_reg.I; //积分时间
  uint16_t Td= g_t_reg.D; //微分时间

  static unsigned char Upper_Limit= 100; //PID输出上限
  static unsigned char Lower_Limit= 0; //PID输出下限

  ERR = Pv - Sv;   //算出当前误差
  DERR1 = ERR - ERR1;   //上次
  DERR2 = ERR - 2 * ERR1 + ERR2; //上上次

  Pout = Kp * DERR1;    //输出P
  Iout = (float)(ERR * ((float)(Kp * pidt) / Ti));  //输出I
  Dout = (float)(DERR2 * ((float)(Kp * Td) / pidt));   //输出D
//  Out = (unsigned int)(Out1 + Pout + Iout + Dout);
//  cout << "Pout: " << Pout << ", Iout: " << Iout << endl;
  Out = (Out1 + Pout + Iout);

  if(Out >= Upper_Limit)   //如果输出大于等于上限
  {
    Out = Upper_Limit;
  }
  else if(Out <= Lower_Limit)  //如果输出小于等于下线
  {
    Out = Lower_Limit;
  }
  
  if (Pv < -50) {
	  Out = 100;
  }
  Out1 = Out;      //记录这次输出的值

  ERR2 = ERR1;    //记录误差
  ERR1 = ERR;     //记录误差
  

  return Out1;
}

static uint8_t PIDCalc2( float Sv, float Pv)  // Sv设定温度值  Pv当前温度值
{
  float DERR1 = 0;       //
  float DERR2 = 0;       //

  float Pout = 0;       //比例结果
  float Iout = 0;       //积分结果
  float Dout = 0;       //微分结果
  int16_t Out = 0; //总输出
  static uint8_t Out1;  //记录上次输出

  static float ERR;       //当前误差
  static float ERR1;      //上次误差
  static float ERR2;      //上上次误差

  /******************
  *以下四项是需要根据实际情况调试的
  ******************/
  static uint8_t pidt = 100;     //300MS计算一次 计算周期
  char Kp = g_t_reg.P;       //比例系数
  uint16_t Ti= g_t_reg.I; //积分时间
  uint16_t Td= g_t_reg.D; //微分时间

  static unsigned char Upper_Limit= 100; //PID输出上限
  static unsigned char Lower_Limit= 0; //PID输出下限

  ERR = Pv - Sv;   //算出当前误差
  DERR1 = ERR - ERR1;   //上次
  DERR2 = ERR - 2 * ERR1 + ERR2; //上上次

  Pout = Kp * DERR1;    //输出P
  Iout = (float)(ERR * ((float)(Kp * pidt) / Ti));  //输出I
  Dout = (float)(DERR2 * ((float)(Kp * Td) / pidt));   //输出D
//  Out = (unsigned int)(Out1 + Pout + Iout + Dout);
//  cout << "Pout: " << Pout << ", Iout: " << Iout << endl;
  Out = (Out1 + Pout + Iout);

  if(Out >= Upper_Limit)   //如果输出大于等于上限
  {
    Out = Upper_Limit;
  }
  else if(Out <= Lower_Limit)  //如果输出小于等于下线
  {
    Out = Lower_Limit;
  }
  
  if (Pv < -50) {
	  Out = 100;
  }
  Out1 = Out;      //记录这次输出的值

  ERR2 = ERR1;    //记录误差
  ERR1 = ERR;     //记录误差
  
//    log_info("%f\t",Sv);
//    log_info("%f\t",Pv);
//    log_info("%f\n",Out1);
  return Out1;
}

static uint8_t PIDCalc3( float Sv, float Pv)  // Sv设定温度值  Pv当前温度值
{
  float DERR1 = 0;       //
  float DERR2 = 0;       //

  float Pout = 0;       //比例结果
  float Iout = 0;       //积分结果
  float Dout = 0;       //微分结果
  int16_t Out = 0; //总输出
  static uint8_t Out1;  //记录上次输出

  static float ERR;       //当前误差
  static float ERR1;      //上次误差
  static float ERR2;      //上上次误差

  /******************
  *以下四项是需要根据实际情况调试的
  ******************/
  static uint8_t pidt = 100;     //300MS计算一次 计算周期
  char Kp = g_t_reg.P;       //比例系数
  uint16_t Ti= g_t_reg.I; //积分时间
  uint16_t Td= g_t_reg.D; //微分时间

  static unsigned char Upper_Limit= 100; //PID输出上限
  static unsigned char Lower_Limit= 0; //PID输出下限

  ERR = Pv - Sv;   //算出当前误差
  DERR1 = ERR - ERR1;   //上次
  DERR2 = ERR - 2 * ERR1 + ERR2; //上上次

  Pout = Kp * DERR1;    //输出P
  Iout = (float)(ERR * ((float)(Kp * pidt) / Ti));  //输出I
  Dout = (float)(DERR2 * ((float)(Kp * Td) / pidt));   //输出D
//  Out = (unsigned int)(Out1 + Pout + Iout + Dout);
//  cout << "Pout: " << Pout << ", Iout: " << Iout << endl;
  Out = (Out1 + Pout + Iout);

  if(Out >= Upper_Limit)   //如果输出大于等于上限
  {
    Out = Upper_Limit;
  }
  else if(Out <= Lower_Limit)  //如果输出小于等于下线
  {
    Out = Lower_Limit;
  }
  
  if (Pv < -50) {
	  Out = 100;
  }
  Out1 = Out;      //记录这次输出的值

  ERR2 = ERR1;    //记录误差
  ERR1 = ERR;     //记录误差
  

  return Out1;
}

static uint8_t PIDCalc4( float Sv, float Pv)  // Sv设定温度值  Pv当前温度值
{
  float DERR1 = 0;       //
  float DERR2 = 0;       //

  float Pout = 0;       //比例结果
  float Iout = 0;       //积分结果
  float Dout = 0;       //微分结果
  int16_t Out = 0; //总输出
  static uint8_t Out1;  //记录上次输出

  static float ERR;       //当前误差
  static float ERR1;      //上次误差
  static float ERR2;      //上上次误差

  /******************
  *以下四项是需要根据实际情况调试的
  ******************/
  static uint8_t pidt = 100;     //300MS计算一次 计算周期
  char Kp = g_t_reg.P;       //比例系数
  uint16_t Ti= g_t_reg.I; //积分时间
  uint16_t Td= g_t_reg.D; //微分时间

  static unsigned char Upper_Limit= 100; //PID输出上限
  static unsigned char Lower_Limit= 0; //PID输出下限

  ERR = Pv - Sv;   //算出当前误差
  DERR1 = ERR - ERR1;   //上次
  DERR2 = ERR - 2 * ERR1 + ERR2; //上上次

  Pout = Kp * DERR1;    //输出P
  Iout = (float)(ERR * ((float)(Kp * pidt) / Ti));  //输出I
  Dout = (float)(DERR2 * ((float)(Kp * Td) / pidt));   //输出D
//  Out = (unsigned int)(Out1 + Pout + Iout + Dout);
//  cout << "Pout: " << Pout << ", Iout: " << Iout << endl;
  Out = (Out1 + Pout + Iout);

  if(Out >= Upper_Limit)   //如果输出大于等于上限
  {
    Out = Upper_Limit;
  }
  else if(Out <= Lower_Limit)  //如果输出小于等于下线
  {
    Out = Lower_Limit;
  }
  
  if (Pv < -50) {
	  Out = 100;
  }
  Out1 = Out;      //记录这次输出的值

  ERR2 = ERR1;    //记录误差
  ERR1 = ERR;     //记录误差
  

  return Out1;
}


//-----------------------------------------------------

#define  R0                         100000   //100K
#define  B                          3975
#define  R2T(r)                     (B/(logf(r) - logf(R0) + B/(25+273.15)) - 273.15)

#define  R1                         10000   //10K
#define  B1                          3975
#define  R3T(r)                     (B1/(logf(r) - logf(R1) + B1/(25+273.15)) - 273.15)
//TMP235
struct tmp_row_s {
	int t_infl;
	float t_c;
	float v_offs;
};

struct tmp_row_s tmp_row[3] = {
	{ 125, 10.6, 1752.5 },
	{ 100, 10.1, 1500 },
	{ 0, 10, 500 },
};

float v2t(float v)
{
	struct tmp_row_s *t;
	
	for (int i=0; i<(sizeof(tmp_row)/sizeof(tmp_row[0])); i++) {
		if (v > tmp_row[i].v_offs) {
			t = &tmp_row[i];
			break;
		}
	}
	return ((v-t->v_offs)/t->t_c+t->t_infl);
}

//type: 0代表电阻，非0代表电压
float ad2temp(uint8_t channal, unsigned char type)
{
	float v;
	float r;
	v = (float)ADC_GetData(channal)*3.3/1024;//    ADC_CH_8_PA7
	r = v*30*1000/(3.3-v);
	if (type == 0) {
		return R2T(r);
		} else {
		return v2t(v*1000);
	}
}

float ad3temp(uint8_t channal, unsigned char type)
{
	float v;
	float r;
	v = (float)ADC_GetData(channal)*3.3/1024;//    ADC_CH_8_PA7
	r = v*30*1000/(3.3-v);
	if (type == 0) {
		return R3T(r);
		} else {
		return v2t(v*1000);
	}
}

float ad4temp()
{
	float v;
	float r;
	v = (float)ADC_GetData(ADC_CH_8_PA7)*3.3/1024;//    ADC_CH_8_PA7
	r = v*30*1000/(3.3-v);
	if (1) {
		return R2T(r);
		} else {
		return v2t(v*1000);
	}
}
uint16_t TEMP[6] = {0};
uint8_t  Fan_speed[6] = {0};
int8_t tepm_R;
int8_t tepm_G;
int8_t tepm_B;
int8_t tepm_BP;
int8_t tepm_DR;
extern uint16_t TEMP_DMD;

void FAN_CTRL(void)
{
	bool Tepm_R;
    uint8_t Tepm_G;
    uint8_t Tepm_B;
    uint8_t Tepm_BP;
    uint8_t Tepm_DR;
	tepm_R = Flash_Read(0x080178FF);
	tepm_G = Flash_Read(0x080171FF);
	tepm_B = Flash_Read(0x080172FF);
	tepm_BP = Flash_Read(0x080173FF);
 	tepm_DR = Flash_Read(0x080174FF);

	temp[1] = (ad4temp()+tepm_R);    //G

	temp[2] = (ad2temp(ADC_CH_6_PA5, 0)+tepm_G);    //G

	temp[3] = (ad2temp(ADC_CH_7_PA6, 0)+tepm_B);    //G

    temp[4] = (ad2temp(ADC_CH_15_PC4, 0)+tepm_BP);    //G

	temp[5] = (ad2temp(ADC_CH_13_PC2, 0)+tepm_DR);    //G
	
	if((temp[1]>100&&temp[1]<500)||(temp[2]>100&&temp[2]<500)||(temp[3]>100&&temp[3]<500)||(temp[4]>100&&temp[4]<500)||(temp[5]>100&&temp[5]<500)||TEMP_DMD>61)
	{
		LedInit(GPIOC, GPIO_PIN_14);//PA10 projiect_on
		LedOff(GPIOC,GPIO_PIN_14);
	}
	uint8_t speed_0 = PIDCalc(47,temp[1]);
	uint8_t speed_1 = PIDCalc1(62,temp[2]);
	uint8_t speed_2 = PIDCalc2(65,temp[3]);
	uint8_t speed_3 = PIDCalc3(63,temp[4]);
	uint8_t speed_4 = PIDCalc4(47,temp[5]);
	FANPWM=speed_0;
	FANPWM_1=speed_1;
	FANPWM_2=speed_2;
	FANPWM_3=speed_3;
	FANPWM_4=speed_4;
	
	TIM4->CCDAT1 = FANPWM;
	TIM4->CCDAT2 = FANPWM_1;
	TIM4->CCDAT3 = FANPWM_2;
	TIM4->CCDAT4 = FANPWM_3;
	TIM3->CCDAT3 = FANPWM_4;
	i++;
	if(i==15)
	{
		Fan_speed[0] = 0xBC;
		Fan_speed[1] = FANPWM;
		Fan_speed[2] = FANPWM_1;
		Fan_speed[3] = FANPWM_2;
		Fan_speed[4] = FANPWM_3;
		Fan_speed[5] = FANPWM_4;
		i2c_write_block_1(0x80, 6, 0, Fan_speed);
	}
	if(i == 25)
	{
		i = 0;
		TEMP[0] = 0XBB;
		TEMP[1] = temp[1]*10;
		TEMP[2] = temp[2]*10;
		TEMP[3] = temp[3]*10;
		TEMP[4] = temp[4]*10;
		TEMP[5] = temp[5]*10;
	
		i2c_write_block_1(0x80, 12, 0, TEMP);
	}
}	 	
/**
 * @brief  Inserts a delay time.
 * @param count specifies the delay time length.
 */
void Delay(uint32_t count)
{
    for (; count > 0; count--)
        ;
}

/**
 * @brief  Configures key GPIO.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void KeyInputInit(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    /* Enable the GPIO Clock */
    if (GPIOx == GPIOA)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
    }
    else
    {
        if (GPIOx == GPIOD)
        {
            RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
        }
    }

    /* Configure the GPIO pin as input floating*/
    if (Pin <= GPIO_PIN_ALL)
    {
        GPIO_InitStruct(&GPIO_InitStructure);
        GPIO_InitStructure.Pin        = Pin;
        GPIO_InitStructure.GPIO_Pull  = GPIO_No_Pull;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Input;
        GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
    }
}


void LedInit_in(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    /* Enable the GPIO Clock */
    if (GPIOx == GPIOA)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
    }
    else
    {
        if (GPIOx == GPIOD)
        {
            RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
        }
    }

    /* Configure the GPIO pin */
    if (Pin <= GPIO_PIN_ALL)
    {
        GPIO_InitStruct(&GPIO_InitStructure);
        GPIO_InitStructure.Pin          = Pin;
        GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
        GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
        GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Input;
        GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
    }
}
/**
 * @brief  Configures LED GPIO.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void LedInit(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    /* Enable the GPIO Clock */
    if (GPIOx == GPIOA)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
    }
    else
    {
        if (GPIOx == GPIOD)
        {
            RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
        }
    }

    /* Configure the GPIO pin */
    if (Pin <= GPIO_PIN_ALL)
    {
        GPIO_InitStruct(&GPIO_InitStructure);
        GPIO_InitStructure.Pin          = Pin;
        GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
        GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
        GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_PP;
        GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
    }
}


void LedIni(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    /* Enable the GPIO Clock */
    if (GPIOx == GPIOA)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
    }
    else
    {
        if (GPIOx == GPIOD)
        {
            RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
        }
    }

    /* Configure the GPIO pin */
    if (Pin <= GPIO_PIN_ALL)
    {
        GPIO_InitStruct(&GPIO_InitStructure);
        GPIO_InitStructure.Pin          = Pin;
        GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
        GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
        GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_PP;
        GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
    }
}


/**
 * @brief  Turns selected Led on as output low level.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void LedOn(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBSC = Pin;
}
/**
 * @brief  Turns selected Led Off as output high level.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void LedOff(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBC = Pin;
}

void LEDBlink(GPIO_Module* GPIOx,uint16_t Pin)
{
    GPIOx->POD ^= Pin;
}

void LEDB()
{
 LedInit(GPIOC, GPIO_PIN_5);
 LEDBlink(GPIOC, GPIO_PIN_5);
	
}



//=======================================================================
/** 		用户flash写入函数
	说明：	任意起始地址, 没有对齐限制
			任意数据长度, 支持flash跨页
*/

#define	FLASH_PAGE_SIZE		2048		// flash一页空间为2048字节
static FLASH_STS FLASH_ProgramPage(uint32_t* SrcAddr, uint32_t DstAddr, uint16_t Len)
{
    uint32_t i;

    for (i = 0; i < Len; i += 4)
    {
        FLASH_ProgramWord(DstAddr + i, *(uint32_t*)((uint32_t)SrcAddr + i));
		#if (0)		// 是否开启擦除校验
        if (*(uint32_t*)(DstAddr + i) != *(uint32_t*)((uint32_t)SrcAddr + i))
        {
            return FLASH_ERROR_PG;	
        }
		#endif
    }
    return FLASH_COMPL;
}



FLASH_STS FLASH_Program_User(uint32_t addr, 		// 起始地址
								uint8_t *src, 		// 写入的数据指针
								uint32_t len)		// 数据字节长度		
{
	uint8_t FLASH_PAGE_BUF[FLASH_PAGE_SIZE];
    uint32_t i, flag = 0;
    uint32_t pageAddr, pageCount;
    uint32_t tmpAddr, tmpLen;   
    uint32_t startAddr, endAddr;  

    FLASH_Unlock();
    startAddr = addr % FLASH_PAGE_SIZE;				
    endAddr   = (addr + len) % FLASH_PAGE_SIZE;		
	
    if (startAddr == 0)
    {
        pageAddr = addr;		
        pageCount = len / FLASH_PAGE_SIZE;
        for (i = 0; i < pageCount; i++)
        {
            if (FLASH_COMPL != FLASH_EraseOnePage(pageAddr) != 0)
			{FLASH_Lock();	return FLASH_ERROR_WRP;}
				
            if (FLASH_COMPL != FLASH_ProgramPage((uint32_t*)(src + (i * FLASH_PAGE_SIZE)), pageAddr, FLASH_PAGE_SIZE))
			{FLASH_Lock();	return FLASH_ERROR_WRP;}
            
			pageAddr += FLASH_PAGE_SIZE;
        }
		
        if (endAddr != 0)
        {
            for (i = 0; i < FLASH_PAGE_SIZE; i++)
			{FLASH_PAGE_BUF[i] = ((uint8_t*)pageAddr)[i];}
			
            tmpAddr = len % FLASH_PAGE_SIZE;
            for (i = 0; i < tmpAddr; i++)
            {FLASH_PAGE_BUF[i] = ((uint8_t*)(src + (pageCount * FLASH_PAGE_SIZE)))[i];}
			
            if (FLASH_COMPL != FLASH_EraseOnePage(pageAddr))
            {FLASH_Lock();	return FLASH_ERROR_WRP;}

            if (FLASH_COMPL != FLASH_ProgramPage((uint32_t*)FLASH_PAGE_BUF, pageAddr, FLASH_PAGE_SIZE))
            {FLASH_Lock();	return FLASH_ERROR_WRP;}
        }
    }
    else
    {
        pageAddr = (addr / FLASH_PAGE_SIZE) * FLASH_PAGE_SIZE;	
        tmpAddr = addr % FLASH_PAGE_SIZE;						
        tmpLen = FLASH_PAGE_SIZE - tmpAddr;						
        
		if (tmpLen > len)	{ tmpLen = len; flag = 0;	}
        else				{ flag = 1;					}

        for (i = 0; i < FLASH_PAGE_SIZE; i++)
        {FLASH_PAGE_BUF[i] = ((uint8_t*)pageAddr)[i]; }

        for (i = 0; i < tmpLen; i++)
        { FLASH_PAGE_BUF[tmpAddr + i] = ((uint8_t*)src)[i]; }
		
        if (FLASH_COMPL != FLASH_EraseOnePage(pageAddr))
        {FLASH_Lock();	return FLASH_ERROR_WRP; }
		
        if (FLASH_COMPL != FLASH_ProgramPage((uint32_t*)FLASH_PAGE_BUF, pageAddr, FLASH_PAGE_SIZE))
        {FLASH_Lock(); 	return FLASH_ERROR_WRP; }
		
        pageCount = (len - tmpLen) / FLASH_PAGE_SIZE;
        pageAddr += FLASH_PAGE_SIZE;
        for (i = 0; i < pageCount; i++)
        {
            if (FLASH_COMPL != FLASH_EraseOnePage(pageAddr))
            { FLASH_Lock();	return FLASH_ERROR_WRP; }

            if (FLASH_COMPL != FLASH_ProgramPage((uint32_t*)(src + tmpLen + (i * FLASH_PAGE_SIZE)), pageAddr, FLASH_PAGE_SIZE))
            {FLASH_Lock();	return FLASH_ERROR_WRP; }
			
            pageAddr += FLASH_PAGE_SIZE;
        }
		
        if ((endAddr != 0) && (flag == 1))
        {
            for (i = 0; i < FLASH_PAGE_SIZE; i++)
            {FLASH_PAGE_BUF[i] = ((uint8_t*)pageAddr)[i]; }
			
            tmpAddr = (len - tmpLen) % FLASH_PAGE_SIZE;
			
            for (i = 0; i < tmpAddr; i++)
            {FLASH_PAGE_BUF[i] = ((uint8_t*)(src + tmpLen + (pageCount * FLASH_PAGE_SIZE)))[i]; }

            if (FLASH_COMPL != FLASH_EraseOnePage(pageAddr))
            {FLASH_Lock();	return FLASH_ERROR_WRP; }

            if (FLASH_COMPL != FLASH_ProgramPage((uint32_t*)FLASH_PAGE_BUF, pageAddr, FLASH_PAGE_SIZE))
            {FLASH_Lock();	return FLASH_ERROR_WRP; }
        }
    }

    FLASH_Lock();
    return FLASH_COMPL;
}


uint32_t Flash_Read(uint32_t address)
{
    uint32_t retval;
    retval = *(uint16_t *)(address);
    return retval;
}

/**
 * @brief Assert failed function by user.
 * @param file The name of the call that failed.
 * @param line The source line number of the call that failed.
 */
#ifdef USE_FULL_ASSERT
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    while (1)
    {
    }
}
#endif // USE_FULL_ASSERT

/**
 * @brief  Main program.
 */
float df_value;
bool df_test;
extern uint8_t zoomtest;
extern uint8_t focaltest;
extern uint8_t iristest;
uint8_t data_temp = 50;
uint8_t filter_pi[5];
uint8_t pi_filter[2];
extern uint8_t flag_count;
int main(void)
{
	uint16_t bb[5];
	uint16_t dd[2];
	bool KeyFlagRight = false;
	g_t_reg.P = 16;
	g_t_reg.I = 1000;
	g_t_reg.D = 600;
	g_t_reg.oled_onoff = 1;
	g_t_reg.temp_set[0] = 56;
	g_t_reg.temp_set[1] = 56;
	g_t_reg.temp_set[2] = 56;
	g_t_reg.temp_set[3] = 56;
	LedInit(GPIOA, GPIO_PIN_2);
	bsp_uart_api_init();	
	CLKCTRL_init();
	bsp_adc_init();
	bsp_pwm_init();
	focal_init();
	app_iris_init();


	LedInit(GPIOC, GPIO_PIN_13);
	LedInit(GPIOA, GPIO_PIN_9);
	LedInit(GPIOB, GPIO_PIN_5);
	LedInit(GPIOC, GPIO_PIN_1);
	LedInit(GPIOC, GPIO_PIN_0);
	LedInit(GPIOC, GPIO_PIN_11);
	LedInit(GPIOC, GPIO_PIN_5);
	LedInit(GPIOA, GPIO_PIN_15);
	LedInit(GPIOD, GPIO_PIN_0);
	io_set_high(GPIOD, GPIO_PIN_0);
	LedInit_in(GPIOC, GPIO_PIN_14|GPIO_PIN_15);
	/* Initialize Led1~Led2 as output pushpull mode*/
	i2c_init();
	i2c_init_1();
	dlp_init();
	__delay_ms(700);
	I2C2_GPIO_init();
	dd[0] = 0x01; 
	bb[0] = 0x54;
	bb[1] = 0x80;
	bb[2] = 0x01;
	bb[3] = 0x00;
	bb[4] = 0x07;
	__delay_ms(10); 
    i2c_write_block(0x34, 1, 0, dd);
	__delay_ms(1); 
	i2c_write_block(0x34, 5, 0, bb);
	I2C2_GPIO_init_1();
	bsp_i2c_slave_api_init(MCUBUS_I2C_SLAVE_CFG_HARD_ADDR);
	bsp_i2c_slave_api_open();
	bsp_i2c_slave_api_init_1(MCUBUS_I2C_SLAVE);//0x02
	bsp_i2c2_slave_api_open();
	iris_res();
    TASK_START();
	PWM_BLED();
	
while (1)
	{
		task();
		if(flag_count==0)
		{
			if(flag_900us)
			{
				 FAN_CTRL();
				 filter_pi[0] = 0;
				 filter_pi[1] = Flash_Read(0x08017000);
				 filter_pi[2] = focaltest;
				 filter_pi[3] = zoomtest;
				 filter_pi[4] = iristest;
				 TIM1->CCDAT1 = filter_pi[1];
				 i2c_write_block_1(0x80, 5, 0, filter_pi);
				 I2C2_GPIO_init_1();
				 flag_900us = 0; 
			}
			if(flag_20ms)
			{
				foacl();
				pi_filter[0] = 0xBF;
				pi_filter[1] = FilterMotorWait();
				i2c_write_block_1(0x80, 2, 0, pi_filter);
				I2C2_GPIO_init_1();
				flag_20ms = 0;
			}
		}
	}
}
/**
 * @}
 */
