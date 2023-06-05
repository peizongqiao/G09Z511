/**
 * \file
 *
 * \brief I2C slave driver.
 *
 (c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms,you may use this software and
    any derivatives exclusively with Microchip products.It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

/**
 * \defgroup doc_driver_i2c_slave I2C Slave Driver
 * \ingroup doc_driver_i2c
 *
 * \section doc_driver_i2c_slave_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */

#include "i2c_slave_N32G43X.h"
#include <stdbool.h>
#include "utils.h"
//#include "touch_GM.h"
#include "counter.h"
#include "app_log.h"
#include "app_mcu_bus.h"

uint8_t data_buf[100];
static __IO uint32_t I2CTimeout;
uint8_t flag_slave_send_finish         = 0;
uint8_t flag_slave_recv_finish         = 0;
static uint8_t rxDataNum = 0;
static uint8_t RCC_RESET_Flag = 0;
extern uint8_t dev_addr;
uint8_t Data_prt;
uint8_t read_add;
uint8_t R_flag = 0;
// Bus Error Event Interrupt Handlers
void (*I2C_0_bus_error_interrupt_handler)(void) = NULL;
// Bus Collision Event Interrupt Handlers
void (*I2C_0_collision_interrupt_handler)(void) = NULL;
// Stop Event Interrupt Handlers
void (*I2C_0_stop_interrupt_handler)(void)= NULL;
// Read Event Interrupt Handlers
void (*I2C_0_read_interrupt_handler)(void) = NULL;
// Write Event Interrupt Handlers
void (*I2C_0_write_interrupt_handler)(void) = NULL;
// Address Event Interrupt Handlersstatic
void (*I2C_0_address_interrupt_handler)(void) = NULL;

extern void read_data_check(void);
extern void msg_dispatch_poll_1(void);

void NVIC_Configuration_I2C(uint8_t ch)
{
    NVIC_InitType NVIC_InitStructure;
    if (ch == 1)
    {
        NVIC_InitStructure.NVIC_IRQChannel = I2C1_EV_IRQn;
    }
    if (ch == 2)
    {
        NVIC_InitStructure.NVIC_IRQChannel = I2C2_EV_IRQn;
    }
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    if (ch == 1)
    {
        NVIC_InitStructure.NVIC_IRQChannel = I2C1_ER_IRQn; // test err
    }
    if (ch == 2)
    {
        NVIC_InitStructure.NVIC_IRQChannel = I2C2_ER_IRQn; // test err
    }
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void I2C_ResetBusy(I2C_Module* I2Cx)
{
    I2Cx->CTRL1 |= 0x8000;  // CTRL1_SWRESET_SET
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    I2Cx->CTRL1 &= ~0x8000;  // CTRL1_SWRESET_RESET
}

void I2C2_GPIO_init(void)
{
		GPIO_InitType i2c2_gpio;
		
		//RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
		RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
	
		/*PC0 -- SCL; PC1 -- SDA*/
    GPIO_InitStruct(&i2c2_gpio);
    i2c2_gpio.Pin               = GPIO_PIN_0 | GPIO_PIN_1;
    i2c2_gpio.GPIO_Slew_Rate    = GPIO_Slew_Rate_High;
    i2c2_gpio.GPIO_Mode         = GPIO_Mode_AF_OD;
    i2c2_gpio.GPIO_Alternate    = GPIO_AF7_I2C1;
    i2c2_gpio.GPIO_Pull         = GPIO_Pull_Up;	  
    GPIO_InitPeripheral(GPIOC, &i2c2_gpio);
	
}

/**
 * \brief Initialize I2C interface
 * If module is configured to disabled state, the clock to the I2C is disabled
 * if this is supported by the device's clock system.
 *
 * \return Nothing
 */
void I2C2_init(uint8_t address)
{
    I2C_InitType i2c2_SlaveInit;
	
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C1, ENABLE);
	
    I2C_DeInit(I2C1);     //复位I2C寄存器
    I2C_ResetBusy(I2C1);  //复位BUSY信号

		I2C_DeInit(I2C1);
    i2c2_SlaveInit.BusMode     = I2C_BUSMODE_I2C;
		i2c2_SlaveInit.OwnAddr1    = address;
    i2c2_SlaveInit.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    i2c2_SlaveInit.AckEnable   = I2C_ACKEN;
    i2c2_SlaveInit.AddrMode    = I2C_ADDR_MODE_7BIT;
    i2c2_SlaveInit.ClkSpeed    = 100000; //400K	
    I2C_Init(I2C1, &i2c2_SlaveInit);
//    I2C_ConfigOwnAddr2(I2C1,0x24);
    // int enable
	NVIC_Configuration_I2C((uint8_t)1);
    I2C_ConfigInt(I2C1, I2C_INT_EVENT | I2C_INT_BUF | I2C_INT_ERR, ENABLE);
    
    I2C_Enable(I2C1, ENABLE);
}

/* ################iic 异常侦测 patch############### */
uint32_t iic_time_cnt = 0; //iic起始时间戳
uint8_t iic_start_flag = 0;    //iic开始通信的标志
/* ############################################# */

void I2C1_EV_IRQHandler(void)
{
    uint8_t timeout_flag = 0;
    uint32_t last_event = I2C_GetLastEvent(I2C1);
		
    if ((last_event & I2C_ROLE_MASTER) != I2C_ROLE_MASTER) // MSMODE = 0:I2C slave mode
    {
        switch (last_event)
        {
					/*  */
					case I2C_EVT_SLAVE_SEND_ADDR_MATCHED:  // 0x00060082.EV1.EV3_1 (ADDRF TXDATE)
						rxDataNum=0;	
						read_add = data_buf[0];
						//read_data_check();
						I2C_SendData(I2C1, data_buf[rxDataNum++]);
					break;
					case I2C_EVT_SLAVE_DATA_SENDING:       // 0x00060080.EV3 (TXDATE)
						I2C_SendData(I2C1, data_buf[rxDataNum++]);
					break;
					
					case I2C_EVT_SLAVE_DATA_SENDED:        // 0x00060084.EV3_2 (TXDATE BSF)
						I2C_SendData(I2C1, data_buf[rxDataNum++]);
						//GPIOB->PBC = GPIO_PIN_13;
					break;

					case I2C_EVT_SLAVE_RECV_ADDR_MATCHED:  // 0x00020002.EV1 (ADDRF)
						rxDataNum = 0;
						GPIOB->PBSC = GPIO_PIN_13;
					break;
					
					case I2C_EVT_SLAVE_DATA_RECVD:  // 0x00020040.EV2 (RXDATNE)
							data_buf[rxDataNum++] = I2C_RecvData(I2C1);
					break;
					
					case I2C_EVT_SLAVE_STOP_RECVD:  // 0x00000010.EV4 (STOPF)
						//I2C_0_stop_callback();
					I2C_Enable(I2C1, ENABLE);
						msg_dispatch_poll_1();
						rxDataNum = 0;
//						I2C_Enable(I2C1, ENABLE);
					break;
					
					default:
            I2C2_init(MCUBUS_I2C_SLAVE_CFG_HARD_ADDR);
						I2C_Enable(I2C1, ENABLE);
           break;
        }
    }
		
}
 
void LedInit_out(GPIO_Module* GPIOx, uint16_t Pin)
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
void I2C1_ER_IRQHandler(void)
{
		
	uint32_t last_event;
    last_event = I2C_GetLastEvent(I2C1);
	
		if ((last_event & I2C_EVT_SLAVE_ACK_MISS) == I2C_EVT_SLAVE_ACK_MISS) {
        I2C_ClrFlag(I2C1, I2C_FLAG_ACKFAIL);  //作为从机缺失主机ACK，清除错误标志，不复位
    } else {
        I2C2_init(MCUBUS_I2C_SLAVE_CFG_HARD_ADDR);
    }
}
void msg_dispatch_poll_1(void)
{
	uint8_t ee[10];
	uint8_t d[10];
	uint8_t b[2];
	uint8_t cc[2];
	if(data_buf[0] == 0x01 && data_buf[1] == 0xfe)
	{
		LedInit_out(GPIOB, GPIO_PIN_13);//PB13 SPI_CTRL
		LedInit_out(GPIOA, GPIO_PIN_14);//PA8 E_SPI_CTRL
		LedOff(GPIOB,GPIO_PIN_13);
		LedOn(GPIOA,GPIO_PIN_14);
	}
	else if(data_buf[0] == 0x01 && data_buf[1] == 0xf6)
	{
		LedInit_out(GPIOB, GPIO_PIN_13);
		LedInit_out(GPIOA, GPIO_PIN_14);//PA8 E_SPI_CTRL
		LedOff(GPIOB,GPIO_PIN_13);
		LedOff(GPIOA,GPIO_PIN_14);
	}
	else if(data_buf[0] == 0x01 && data_buf[1] == 0xff)
	{
		
		LedInit_out(GPIOB, GPIO_PIN_13);//PB13 SPI_CTRL
		LedOn(GPIOB,GPIO_PIN_13);
	}
	else if(data_buf[0] == 0x01 && data_buf[1] == 0xfb)
	{
		
		LedInit_out(GPIOC, GPIO_PIN_14);//PA10 projiect_on
		LedOff(GPIOC,GPIO_PIN_14);
		__delay_ms(700);
		LedOn(GPIOC,GPIO_PIN_14);
		__delay_ms(8000);
		b[0] = 0x05;
		b[1] = 0x02;

		i2c_write_block(0x36, 2, 0, b);
		__delay_ms(100);

		cc[0] = 0x52;
		cc[1] = 0x07;
		i2c_write_block(0x36, 2, 0, cc);
		__delay_ms(100);

		uint8_t bb[2];
		bb[0] = 0x16;
		bb[1] = 0x0f;
		i2c_write_block(0x36, 2, 0, bb);
		I2C2_GPIO_init();
//            proj_reset();
	}
	else if(data_buf[0] == 0x00 && data_buf[1] == 0x52)
	{
		R_flag=1;
	}
	else if(data_buf[0] == 0x00 && data_buf[1] == 0x47)
	{
		R_flag=2;
	}
	else if(data_buf[0] == 0x00 && data_buf[1] == 0x42)
	{
		R_flag=3;
	}
	else if(data_buf[0] == 0x00 && data_buf[1] == 0x57)
	{
		R_flag=4;
	}
	else if(data_buf[0] == 0x00 && data_buf[1] == 0x48)
	{
		R_flag=5;
	}
	else
	{R_flag=0;}
}