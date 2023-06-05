/**
 * \file
 *
 * \brief i2c host driver.
 *
 * (c) 2018 xxxx Technology Inc. and its subsidiaries.
 *
 */

#ifndef BSP_I2C_HOST_H_
#define BSP_I2C_HOST_H_


//#include <port.h>
#include "GMtypes.h"
#include "bsp_i2c_host_cfg.h"



// I2C¶¯×÷
typedef enum
{
    I2C_WR=0,
    I2C_RD=1,
}I2C_action_t;



// ================== external function ====================
void bsp_i2c_init(void);
void bsp_i2c_start(void);
void bsp_i2c_stop(void);
uint8_t bsp_i2c_wait_ack(void);
void bsp_i2c_ack(void);
void bsp_i2c_nack(void);
void bsp_i2c_send_byte(uint8_t txd);
uint8_t bsp_i2c_read_byte(uint8_t ack);


#endif
