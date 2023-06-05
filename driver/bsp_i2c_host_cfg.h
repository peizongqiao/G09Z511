/*
* ģ������ : i2c host��������(Ĭ��)
* �ļ����� : xxxxx.h
* ˵    �� :
*
*/
#ifndef _BSP_I2C_HOST_CFG_H_
#define _BSP_I2C_HOST_CFG_H_

//#include <port.h>
#include "config.h"
#include "n32g43x_start_pins.h"



//============== configure(���ļ��ڽ�ֹ�޸�) ===============
// I2C host���߲���IOģ�⣬IO����

//Ӳ���Ƿ�����(0-��������1-����)
#define I2C_HOST_SDA_IS_HARDWARE_PULLUP                   (1u)
#define I2C_HOST_SCL_IS_HARDWARE_PULLUP                   (0u)


// SDA
#define I2C_HOST_SDA_OUT()          io_set_dir_out(GPIOB, 1)
#define I2C_HOST_SDA_INPUT()        io_set_dir_in(GPIOB, 1)
#define I2C_HOST_SDA_GET()          io_get_level(GPIOB, 1)

// ע�⣺
// 1.����MCU IO����������ԣ���������������H��ƽʱ�������豸���ܰ��������͡�
// 2.����I2C SDA����Ӳ����·�����ⲿ�������裬�ʣ�����MCU����Ϊ���룬SDAΪ��ͨ���ⲿ�����������ߡ�
#define I2C_HOST_SDA_1()            io_set_dir_in(GPIOB, 1)
#define I2C_HOST_SDA_0()            do{io_set_dir_out(GPIOB, 1); io_set_low(GPIOB, GPIO_PIN_1);}while(0)

#define I2C_HOST_SDA_PULLUP_OFF() io_set_pull_off_mode(GPIOB, 1)

// SCL
#define I2C_HOST_SCL_OUT()          io_set_dir_out(GPIOB, 0)
#define I2C_HOST_SCL_INPUT()        io_set_dir_in(GPIOB, 0)
#define I2C_HOST_SCL_1()            io_set_high(GPIOB, GPIO_PIN_0)
#define I2C_HOST_SCL_0()            io_set_low(GPIOB, GPIO_PIN_0)
#define I2C_HOST_SCL_PULLUP_OFF() io_set_pull_off_mode(GPIOB, 0)






#endif
