#ifndef _I2C_MASTER_H_
#define _I2C_MASTER_H_

#include <string.h>
#include <stdint.h>
#include "n32g43x_start_pins.h"
#include "main.h"
typedef unsigned char   BYTE1;
typedef unsigned short  WORD1;

#define _I2C_WRITE_SIZE_1                 	16
#define _I2C_TIMEOUT_LIMIT_1                  255

#define _I2C_BUSY_1                       	0
#define _I2C_OK_1                         	1

#define _I2C_WR_1                        	0
#define _I2C_RD_1                         	1

#define _FAIL_1      0
#define _SUCCESS_1   1
//----------------------------------------------------------------------------------------------------
#define  SCL_PORT 1  GPIOC   //PC0
#define  SDA_PORT1   GPIOC   //PC1

#define  SCL_PIN1  GPIO_PIN_0        //PC0
#define  SDA_PIN1   GPIO_PIN_1       //PC1

#define NACK_1 0
#define ACK1  1

#define INPUTI2CSDA_1()				LedInit_in(SDA_PORT,SDA_PIN)
#define OUTPUTI2CSDA_1()				LedInit(SDA_PORT,SDA_PIN)

#define SETI2CSDA1()                 LedOn(SDA_PORT,SDA_PIN)
#define CLRI2CSDA1()                 LedOff(SDA_PORT,SDA_PIN)
            
#define INPUTI2CSCL1()				LedInit_in(SCL_PORT,SCL_PIN)
#define OUTPUTI2SCL1()               LedInit(SCL_PORT,SCL_PIN)

#define SETI2CSCL1()                 LedOn(SCL_PORT,SCL_PIN)
#define CLRI2CSCL1()                 LedOff(SCL_PORT,SCL_PIN)

#define GETI2CSDA1()					GPIO_ReadInputDataBit(SDA_PORT,SDA_PIN)
#define GETI2CSCL1()					GPIO_ReadInputDataBit(SCL_PORT,SCL_PIN)
  
#define PULLUPSCL1()		            io_set_pull_off_mode(SCL_PORT,SCL_PIN)
#define PULLUPSDA1()		            io_set_pull_off_mode(SDA_PORT,SDA_PIN)

#define SDA_11()                     {LedInit(SDA_PORT,SDA_PIN); LedOn(SDA_PORT,SDA_PIN);}
#define SDA_01()                     {LedInit(SDA_PORT,SDA_PIN);LedOff(SDA_PORT,SDA_PIN);}
	
#define SCL_11()                     {LedInit(SCL_PORT,SCL_PIN);LedOn(SCL_PORT,SCL_PIN);} 
#define SCL_01()                     {LedInit(SCL_PORT,SCL_PIN);LedOff(SCL_PORT,SCL_PIN);}    

#define IIC_SCL1 
extern void __delay_cycles(volatile uint16_t cnt);

extern void Delay5us(void);
extern void i2c_init(void);
extern void __delay_ms(volatile uint16_t cnt);
int8_t i2c_write_block(uint8_t ucSlaveDeviceAddr,uint8_t numBytes,unsigned char multi, void* TxData);
int8_t i2c_read_block(uint8_t ucSlaveDeviceAddr,uint8_t numBytes,void* RxData);
int8_t safe_write(uint8_t sub_addr, volatile uint8_t *value, uint8_t len);

//extern uint8_t read_vol_IIC(uint8_t ucSlaveDeviceAddr,uint8_t rx_numBytes,void* RxData,uint8_t tx_numBytes,void* TxData);
extern int8_t CI2cRead_Block_TEST(uint8_t ucSlaveDeviceAddr,uint8_t cmd, uint8_t numBytes,void* RxData);
#endif

