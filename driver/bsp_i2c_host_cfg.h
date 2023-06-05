/*
* 模块名称 : i2c host参数配置(默认)
* 文件名称 : xxxxx.h
* 说    明 :
*
*/
#ifndef _BSP_I2C_HOST_CFG_H_
#define _BSP_I2C_HOST_CFG_H_

//#include <port.h>
#include "config.h"
#include "n32g43x_start_pins.h"



//============== configure(本文件内禁止修改) ===============
// I2C host总线采用IO模拟，IO配置

//硬件是否上拉(0-非上拉；1-上拉)
#define I2C_HOST_SDA_IS_HARDWARE_PULLUP                   (1u)
#define I2C_HOST_SCL_IS_HARDWARE_PULLUP                   (0u)


// SDA
#define I2C_HOST_SDA_OUT()          io_set_dir_out(GPIOB, 1)
#define I2C_HOST_SDA_INPUT()        io_set_dir_in(GPIOB, 1)
#define I2C_HOST_SDA_GET()          io_get_level(GPIOB, 1)

// 注意：
// 1.由于MCU IO输出的特殊性：是推完输出，输出H电平时，其他设备不能把总线拉低。
// 2.由于I2C SDA总线硬件电路加了外部上拉电阻，故：设置MCU设置为输入，SDA为高通过外部电阻上拉拉高。
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
