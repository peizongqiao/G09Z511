#include "main.h"
#include "i2c2_slave_N32G43X.h"
#include <stdbool.h>
#include "utils.h"
#include "counter.h"
#include "app_log.h"
#include "app_mcu_bus.h"

uint8_t data_buf_1[100];
static uint8_t rxDataNum_1 = 0;
uint8_t read_add_1;
uint8_t flag_count;
uint8_t MOTOR_count;
uint8_t pwn_count = 50;
extern float temp[7];
bool df_status;
bool status;
uint16_t filter_step_number;

extern void read_data_check_1(void);
extern void msg_dispatch_poll_2(void);

extern int8_t tepm_r;
extern int8_t tepm_g;
extern int8_t tepm_b;
extern int8_t tepm_bp;
extern int8_t tepm_dr;
extern uint16_t R_current;
extern uint16_t G_current;
extern uint16_t B_current;

uint16_t TEMP_DMD;
uint8_t c;
uint16_t 	user_buf1[128];
uint8_t 	user_buf2[256];
uint32_t	addr;

void NVIC_Configuration_I2C_1(uint8_t ch)
{
    NVIC_InitType NVIC_InitStructure;
    if (ch == 1)
    {
        NVIC_InitStructure.NVIC_IRQChannel = I2C2_EV_IRQn;
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
        NVIC_InitStructure.NVIC_IRQChannel = I2C2_ER_IRQn; // test err
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

void I2C_ResetBusy_1(I2C_Module* I2Cx)
{
    I2Cx->CTRL1 |= 0x8000;  // CTRL1_SWRESET_SET
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    I2Cx->CTRL1 &= ~0x8000;  // CTRL1_SWRESET_RESET
}

void I2C2_GPIO_init_1(void)
{
	GPIO_InitType i2c2_gpio;

	//RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);

	/*PC0 -- SCL; PC1 -- SDA*/
	GPIO_InitStruct(&i2c2_gpio);
	i2c2_gpio.Pin               = GPIO_PIN_10 | GPIO_PIN_9;
	i2c2_gpio.GPIO_Slew_Rate    = GPIO_Slew_Rate_High;
	i2c2_gpio.GPIO_Mode         = GPIO_Mode_AF_OD;
	i2c2_gpio.GPIO_Alternate    = GPIO_AF6_I2C2;
	i2c2_gpio.GPIO_Pull         = GPIO_Pull_Up;	  
	GPIO_InitPeripheral(GPIOA, &i2c2_gpio);

}

/**
 * \brief Initialize I2C interface
 * If module is configured to disabled state, the clock to the I2C is disabled
 * if this is supported by the device's clock system.
 *
 * \return Nothing
 */
void I2C2_init_1(uint8_t address)
{
    I2C_InitType i2c2_SlaveInit;
	
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C2, ENABLE);
	
    I2C_DeInit(I2C2);     //复位I2C寄存器
    I2C_ResetBusy_1(I2C2);  //复位BUSY信号

		I2C_DeInit(I2C2);
    i2c2_SlaveInit.BusMode     = I2C_BUSMODE_I2C;
		i2c2_SlaveInit.OwnAddr1    = address;
    i2c2_SlaveInit.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    i2c2_SlaveInit.AckEnable   = I2C_ACKEN;
    i2c2_SlaveInit.AddrMode    = I2C_ADDR_MODE_7BIT;
    i2c2_SlaveInit.ClkSpeed    = 100000; //400K	
    I2C_Init(I2C2, &i2c2_SlaveInit);
//    I2C_ConfigOwnAddr2(I2C2,0x24);
    // int enable
	NVIC_Configuration_I2C_1((uint8_t)1);
    I2C_ConfigInt(I2C2, I2C_INT_EVENT | I2C_INT_BUF | I2C_INT_ERR, ENABLE);
    
    I2C_Enable(I2C2, ENABLE);
}

/* ################iic 异常侦测 patch############### */
//uint32_t iic_time_cnt = 0; //iic起始时间戳
//uint8_t iic_start_flag = 0;    //iic开始通信的标志
/* ############################################# */

void I2C2_EV_IRQHandler(void)
{
    uint8_t timeout_flag = 0;
    uint32_t last_event = I2C_GetLastEvent(I2C2);
		
    if ((last_event & I2C_ROLE_MASTER) != I2C_ROLE_MASTER) // MSMODE = 0:I2C slave mode
    {
        switch (last_event)
        {
					/*  */
					case I2C_EVT_SLAVE_SEND_ADDR_MATCHED:  // 0x00060082.EV1.EV3_1 (ADDRF TXDATE)
						rxDataNum_1=0;	
						read_add_1 = data_buf_1[0];
						//read_data_check_1();
						I2C_SendData(I2C2, data_buf_1[rxDataNum_1++]);
					break;
					case I2C_EVT_SLAVE_DATA_SENDING:       // 0x00060080.EV3 (TXDATE)
						I2C_SendData(I2C2, data_buf_1[rxDataNum_1++]);
					break;
					
					case I2C_EVT_SLAVE_DATA_SENDED:        // 0x00060084.EV3_2 (TXDATE BSF)
						I2C_SendData(I2C2, data_buf_1[rxDataNum_1++]);
//					    log_info("a");
						//GPIOB->PBC = GPIO_PIN_13;
					break;

					case I2C_EVT_SLAVE_RECV_ADDR_MATCHED:  // 0x00020002.EV1 (ADDRF)
						rxDataNum_1 = 0;
//						GPIOB->PBSC = GPIO_PIN_13;
//						log_info("b");
					break;
					
					case I2C_EVT_SLAVE_DATA_RECVD:  // 0x00020040.EV2 (RXDATNE)
							data_buf_1[rxDataNum_1++] = I2C_RecvData(I2C2);
					break;
					
					case I2C_EVT_SLAVE_STOP_RECVD:  // 0x00000010.EV4 (STOPF)
						//I2C_0_stop_callback();
					I2C_Enable(I2C2, ENABLE);
						msg_dispatch_poll_2();
						rxDataNum_1 = 0;
//						I2C_Enable(I2C2, ENABLE);
					break;
					
					default:
            I2C2_init_1(MCUBUS_I2C_SLAVE);
						I2C_Enable(I2C2, ENABLE);
           break;
        }
    }
		
}
 
void LedInit_out_1(GPIO_Module* GPIOx, uint16_t Pin)
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
void I2C2_ER_IRQHandler(void)
{
		
	uint32_t last_event;
    last_event = I2C_GetLastEvent(I2C2);
	
		if ((last_event & I2C_EVT_SLAVE_ACK_MISS) == I2C_EVT_SLAVE_ACK_MISS) {
        I2C_ClrFlag(I2C2, I2C_FLAG_ACKFAIL);  //作为从机缺失主机ACK，清除错误标志，不复位
    } else {
        I2C2_init_1(MCUBUS_I2C_SLAVE);
    }
}
void msg_dispatch_poll_2(void)
{
	if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x00)
	{
		flag_count = 1;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x01)
	{
		flag_count = 2;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x02)
	{
		flag_count = 3;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x03)
	{
		flag_count = 4;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x04)
	{
		flag_count = 5;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x05)
	{
		flag_count = 6;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x06)
	{
		flag_count = 7;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x07)
	{
		flag_count = 8;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x08)
	{
		flag_count = 9;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x09)
	{
		flag_count = 10;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x2A)
	{
		flag_count = 42;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x0a)
	{
		R_current = Flash_Read(0x080175FF);
		R_current = R_current +5;
		addr = 0x080175FF;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = R_current;
		user_buf2[1] = R_current>>8;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节	
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x0b)
	{
		G_current = Flash_Read(0x080176FF);
		G_current = G_current +5;
		addr = 0x080176FF;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = G_current;
		user_buf2[1] = G_current>>8;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节	
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x0c)
	{
		B_current = Flash_Read(0x080177FF);
		B_current = B_current +5;
		addr = 0x080177FF;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = B_current;
		user_buf2[1] = B_current>>8;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节	
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x0d)
	{
		R_current = Flash_Read(0x080175FF);
		R_current = R_current -5;
		addr = 0x080175FF;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = R_current;
		user_buf2[1] = R_current>>8;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节	
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x0e)
	{
		G_current = Flash_Read(0x080176FF);
		G_current = G_current -5;
		addr = 0x080176FF;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = G_current;
		user_buf2[1] = G_current>>8;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节	
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x0f)
	{
		B_current = Flash_Read(0x080177FF);
		B_current = B_current -5;
		addr = 0x080177FF;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = B_current;
		user_buf2[1] = B_current>>8;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节	
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x10)
	{
		tepm_r = Flash_Read(R_TEMP);
		tepm_r = tepm_r +1;
		addr = R_TEMP;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = tepm_r;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x11)
	{
		tepm_g = Flash_Read(G_TEMP);
		tepm_g = tepm_g +1;
		addr = G_TEMP;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = tepm_g;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x12)
	{
		tepm_b = Flash_Read(B_TEMP);
		tepm_b = tepm_b +1;
		addr = B_TEMP;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = tepm_b;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x13)
	{
		tepm_bp = Flash_Read(BP_TEMP);
		tepm_bp = tepm_bp +1;
		addr = BP_TEMP;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = tepm_bp;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x14)
	{
		tepm_dr = Flash_Read(DR_TEMP);
		tepm_dr = tepm_dr +1;
		addr = DR_TEMP;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = tepm_dr;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x15)
	{
		tepm_r = Flash_Read(R_TEMP);
		tepm_r = tepm_r -1;
		addr = R_TEMP;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = tepm_r;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x16)
	{
		tepm_g = Flash_Read(G_TEMP);
		tepm_g = tepm_g -1;
		addr = G_TEMP;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = tepm_g;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x17)
	{
		tepm_b = Flash_Read(B_TEMP);
		tepm_b = tepm_b -1;
		addr = B_TEMP;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = tepm_b;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x18)
	{
		tepm_bp = Flash_Read(BP_TEMP);
		tepm_bp = tepm_bp -1;
		addr = BP_TEMP;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = tepm_bp;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x19)
	{
		tepm_dr = Flash_Read(DR_TEMP);
		tepm_dr = tepm_dr -1;
		addr = DR_TEMP;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = tepm_dr;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x1a)
	{
		pwn_count = Flash_Read(0x08017000);
		TIM1->CCDAT1=++pwn_count;
		addr = FLASH_WRITE_START_ADDR;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = pwn_count;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x1b)
	{
		pwn_count = Flash_Read(0x08017000);
		TIM1->CCDAT1=--pwn_count;
	    addr = FLASH_WRITE_START_ADDR;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = pwn_count;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x1c)
	{
		flag_count = 28;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x1d)
	{
		flag_count = 29;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x1e)
	{
		flag_count = 30;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x1f)
	{
		flag_count = 31;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x20)
	{
		flag_count = 32;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x21)
	{
		flag_count = 33;
	}
	else if(data_buf_1[0] == 0x03&&data_buf_1[1] == 0x22)
	{
		flag_count = 60;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x22)
	{
		flag_count = 34;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x23)
	{
		flag_count = 35;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x24)
	{
		flag_count = 36;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x25)
	{
		flag_count = 37;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x26)
	{
		flag_count = 38;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x27)
	{
		flag_count = 39;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x28)
	{
		flag_count = 40;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x29)
	{
		flag_count = 41;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x2B)
	{
		flag_count = 0;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x2C)
	{
		flag_count = 0;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x2D)
	{
		flag_count = 0;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x2E)
	{
		flag_count = 0;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x2F)
	{
		flag_count = 0;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x30)
	{
		flag_count = 0;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x31)
	{
		flag_count = 43;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x32)
	{
		flag_count = 44;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x33)
	{
		flag_count = 45;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x34)
	{
		flag_count = 46;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x35)
	{
		flag_count = 47;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x36)
	{
		flag_count = 48;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x37)
	{
		flag_count = 49;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x38)
	{
		flag_count = 50;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x39)
	{
		flag_count = 51;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x40)
	{
		flag_count = 52;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x41)
	{
		flag_count = 53;
	}
	else if(data_buf_1[0] == 0x01&&data_buf_1[1] == 0x60)
	{
		flag_count = 54;
	}
	else if(data_buf_1[0] == 0x0B&&data_buf_1[1] == 0x01)
	{
		flag_count = 55;
	}
	else if(data_buf_1[0] == 0x0B&&data_buf_1[1] == 0x02)
	{
		flag_count = 56;
	}
	else if(data_buf_1[0] == 0x0B&&data_buf_1[1] == 0x03)
	{
		flag_count = 57;
	}
	else if(data_buf_1[0] == 0x0B&&data_buf_1[1] == 0x04)
	{
		flag_count = 58;
	}
	else if(data_buf_1[0] == 0x0B&&data_buf_1[1] == 0x05)
	{
		flag_count = 59;
	}
	else if(data_buf_1[0] == 0x07&&data_buf_1[1] == 0x1C)
	{
		MOTOR_count = 1;
	}
	else if(data_buf_1[0] == 0x07&&data_buf_1[1] == 0x1D)
	{
		MOTOR_count = 2;
	}
	else if(data_buf_1[0] == 0x07&&data_buf_1[1] == 0x2C)
	{
		MOTOR_count = 3;
	}
	else if(data_buf_1[0] == 0x07&&data_buf_1[1] == 0x2D)
	{
		MOTOR_count = 4;
	}
	else if(data_buf_1[0] == 0x07&&data_buf_1[1] == 0x3C)
	{
		MOTOR_count = 5;
	}
	else if(data_buf_1[0] == 0x07&&data_buf_1[1] == 0x3D)
	{
		MOTOR_count = 6;
	}
	else if(data_buf_1[0] == 0x02&&data_buf_1[1] == 0x01)
	{
		addr = R_TEMP;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = 0;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节
	}
	else if(data_buf_1[0] == 0x02&&data_buf_1[1] == 0x02)
	{
		addr = G_TEMP;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = 0;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节
	}
	else if(data_buf_1[0] == 0x02&&data_buf_1[1] == 0x03)
	{
		addr = B_TEMP;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = 0;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节
	}
	else if(data_buf_1[0] == 0x02&&data_buf_1[1] == 0x04)
	{
		addr = BP_TEMP;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = 0;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节
	}
	else if(data_buf_1[0] == 0x02&&data_buf_1[1] == 0x05)
	{
		addr = DR_TEMP;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = 0;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节
	}
	else if(data_buf_1[0] == 0x02&&data_buf_1[1] == 0x10)
	{
		addr = 0x080175FF;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = 0xf4;
		user_buf2[1] = 0x01;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节	
		__delay_ms(10);
		addr = 0x080176FF;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = 0xf4;
		user_buf2[1] = 0x01;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节	
		__delay_ms(10);
		addr = 0x080177FF;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = 0xf4;
		user_buf2[1] = 0x01;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节	
	}
	else if(data_buf_1[0] == 0x02&&data_buf_1[1] == 0x11)
	{
		addr = 0x080175FF;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = 0x20;
		user_buf2[1] = 0x03;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节	
		__delay_ms(10);
		addr = 0x080176FF;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = 0x20;
		user_buf2[1] = 0x03;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节	
		__delay_ms(10);
		addr = 0x080177FF;
		memset(user_buf2, 0xa1, 256);
		user_buf2[0] = 0x20;
		user_buf2[1] = 0x03;
		FLASH_Program_User(addr, user_buf2, 256);	//在0x08010000起始地址写256字节
	}
	else if(data_buf_1[0] == 0x03)
	{
		filter_step_number = data_buf_1[1]+data_buf_1[2]*256;
		df_status = data_buf_1[3];
		TEMP_DMD = data_buf_1[4]+data_buf_1[5]*256;
		TEMP_DMD = TEMP_DMD/10;
	}
	else if(data_buf_1[0] == 0x04)
	{
		status = data_buf_1[1];
	}

}