#ifndef _I2C_MASTER_1_H_
#define _I2C_MASTER_1_H_

#include <string.h>
#include <stdint.h>
#include "n32g43x_start_pins.h"
#include "main.h"
typedef unsigned char   BYTE;
typedef unsigned short  WORD;

#define _I2C_WRITE_SIZE                 	16
#define _I2C_TIMEOUT_LIMIT                  255

#define _I2C_BUSY                       	0
#define _I2C_OK                         	1

#define _I2C_WR                         	0
#define _I2C_RD                         	1

#define _FAIL      0
#define _SUCCESS   1
//----------------------------------------------------------------------------------------------------
#define  SCL_PORT_1   GPIOA   //PC0
#define  SDA_PORT_1   GPIOA   //PC1

#define  SCL_PIN_1   GPIO_PIN_9        //PC0
#define  SDA_PIN_1   GPIO_PIN_10       //PC1

#define NACK 0
#define ACK  1

#define INPUTI2CSDA_1()				LedInit_in(SDA_PORT_1,SDA_PIN_1)
#define OUTPUTI2CSDA_1()			LedInit(SDA_PORT_1,SDA_PIN_1)

#define SETI2CSDA_1()                 LedOn(SDA_PORT_1,SDA_PIN_1)
#define CLRI2CSDA_1()                 LedOff(SDA_PORT_1,SDA_PIN_1)
            
#define INPUTI2CSCL_1()				LedInit_in(SCL_PORT_1,SCL_PIN_1)
#define OUTPUTI2SCL_1()               LedInit(SCL_PORT_1,SCL_PIN_1)

#define SETI2CSCL_1()                 LedOn(SCL_PORT_1,SCL_PIN_1)
#define CLRI2CSCL_1()                 LedOff(SCL_PORT_1,SCL_PIN_1)

#define GETI2CSDA_1()					GPIO_ReadInputDataBit(SDA_PORT_1,SDA_PIN_1)
#define GETI2CSCL_1()					GPIO_ReadInputDataBit(SCL_PORT_1,SCL_PIN_1)
  
#define PULLUPSCL_1()		            io_set_pull_off_mode(SCL_PORT_1,SCL_PIN_1)
#define PULLUPSDA_1()		            io_set_pull_off_mode(SDA_PORT_1,SDA_PIN_1)

#define SDA_1_1()                     {LedInit(SDA_PORT_1,SDA_PIN_1); LedOn(SDA_PORT_1,SDA_PIN_1);}
#define SDA_0_1()                     {LedInit(SDA_PORT_1,SDA_PIN_1);LedOff(SDA_PORT_1,SDA_PIN_1);}
	
#define SCL_1_1()                     {LedInit(SCL_PORT_1,SCL_PIN_1);LedOn(SCL_PORT_1,SCL_PIN_1);} 
#define SCL_0_1()                     {LedInit(SCL_PORT_1,SCL_PIN_1);LedOff(SCL_PORT_1,SCL_PIN_1);}    

#define IIC_SCL 
extern void __delay_cycles_1(volatile uint16_t cnt);

extern void Delay5us_1(void);
extern void i2c_init_1(void);
extern void __delay_ms_1(volatile uint16_t cnt);
int8_t i2c_write_block_1(uint8_t ucSlaveDeviceAddr,uint8_t numBytes,unsigned char multi, void* TxData);
int8_t i2c_read_block_1(uint8_t ucSlaveDeviceAddr,uint8_t numBytes,void* RxData);
int8_t safe_write_1(uint8_t sub_addr, volatile uint8_t *value, uint8_t len);

//extern uint8_t read_vol_IIC(uint8_t ucSlaveDeviceAddr,uint8_t rx_numBytes,void* RxData,uint8_t tx_numBytes,void* TxData);
extern int8_t CI2cRead_Block_TEST_1(uint8_t ucSlaveDeviceAddr,uint8_t cmd, uint8_t numBytes,void* RxData);
#endif

