#ifndef _I2C_MASTER_H_
#define _I2C_MASTER_H_

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
#define  SCL_PORT   GPIOC   //PC0
#define  SDA_PORT   GPIOC   //PC1

#define  SCL_PIN   GPIO_PIN_0        //PC0
#define  SDA_PIN   GPIO_PIN_1       //PC1

#define NACK 0
#define ACK  1

#define INPUTI2CSDA()				LedInit_in(SDA_PORT,SDA_PIN)
#define OUTPUTI2CSDA()				LedInit(SDA_PORT,SDA_PIN)

#define SETI2CSDA()                 LedOn(SDA_PORT,SDA_PIN)
#define CLRI2CSDA()                 LedOff(SDA_PORT,SDA_PIN)
            
#define INPUTI2CSCL()				LedInit_in(SCL_PORT,SCL_PIN)
#define OUTPUTI2SCL()               LedInit(SCL_PORT,SCL_PIN)

#define SETI2CSCL()                 LedOn(SCL_PORT,SCL_PIN)
#define CLRI2CSCL()                 LedOff(SCL_PORT,SCL_PIN)

#define GETI2CSDA()					GPIO_ReadInputDataBit(SDA_PORT,SDA_PIN)
#define GETI2CSCL()					GPIO_ReadInputDataBit(SCL_PORT,SCL_PIN)
  
#define PULLUPSCL()		            io_set_pull_off_mode(SCL_PORT,SCL_PIN)
#define PULLUPSDA()		            io_set_pull_off_mode(SDA_PORT,SDA_PIN)

#define SDA_1()                     {LedInit(SDA_PORT,SDA_PIN); LedOn(SDA_PORT,SDA_PIN);}
#define SDA_0()                     {LedInit(SDA_PORT,SDA_PIN);LedOff(SDA_PORT,SDA_PIN);}
	
#define SCL_1()                     {LedInit(SCL_PORT,SCL_PIN);LedOn(SCL_PORT,SCL_PIN);} 
#define SCL_0()                     {LedInit(SCL_PORT,SCL_PIN);LedOff(SCL_PORT,SCL_PIN);}    

#define IIC_SCL 
extern void __delay_cycles(volatile uint16_t cnt);

extern void Delay5us(void);
extern void i2c_init(void);
extern void __delay_ms(volatile uint16_t cnt);
int8_t i2c_write_block(uint8_t ucSlaveDeviceAddr,uint8_t numBytes,unsigned char multi, void* TxData);
int8_t i2c_read_block(uint8_t ucSlaveDeviceAddr,uint8_t numBytes,void* RxData);
int8_t safe_write(uint8_t sub_addr, volatile uint8_t *value, uint8_t len);
void IIC_Send_Byte(uint8_t txd);
//extern uint8_t read_vol_IIC(uint8_t ucSlaveDeviceAddr,uint8_t rx_numBytes,void* RxData,uint8_t tx_numBytes,void* TxData);
extern int8_t CI2cRead_Block_TEST(uint8_t ucSlaveDeviceAddr,uint8_t cmd, uint8_t numBytes,void* RxData);
#endif

