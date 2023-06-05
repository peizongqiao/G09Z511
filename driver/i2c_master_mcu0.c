#include "i2c_master_mcu0.h"


BYTE1 CI2cSendByte(BYTE1 ucValue);
uint8_t errorflag = 0;

//----------------------------------------------------------------------------------------------------
// I2C communication basic function
//----------------------------------------------------------------------------------------------------
void __delay_cycles_mcu0(volatile uint16_t cnt)
{
	while(cnt--)
	{
		__asm__ __volatile__("nop");
		//__asm__ __volatile__("nop");
	}
}

void __delay_ms_mcu0(volatile uint16_t cnt)
{
	volatile uint16_t i,j;
	
//	for(i=cnt;i>0;i--)
//	for(j=1100;j>0;j--);
	for(i=0;i<cnt;i++)
	{
		for(j=0;j<1100;j++);
	}
}
void Delay4us_mcu0(void)
{
	__asm__ __volatile__("nop");
	__asm__ __volatile__("nop");
	__asm__ __volatile__("nop");
	__asm__ __volatile__("nop");
	__asm__ __volatile__("nop");
	__asm__ __volatile__("nop");
	__asm__ __volatile__("nop");
	__asm__ __volatile__("nop");
	
  
}

BYTE1 CHECKI2CSDA_mcu0(void)  
{
	 return  GETI2CSDA1();
}

//У��IIC-SCL��״̬
BYTE1 CHECKI2CSCL_mcu0(void)
{
	BYTE1 level = 0;
	INPUTI2CSCL1();
	level = GETI2CSCL1();
	
	return level;
}

//��ʼ��IIC
void i2c_init_mcu0(void)
{			
  OUTPUTI2CSDA_1();
  OUTPUTI2SCL1();
  
  PULLUPSCL1();
  PULLUPSDA1();
  
  SETI2CSCL1();
  SETI2CSDA1();

}
//����IIC��ʼ�ź�
void IIC_Start_mcu0(void)
{
	OUTPUTI2CSDA_1();     //sda�����
	__delay_cycles(1);	
	SETI2CSDA1();	 	 	  
	SETI2CSCL1();
	__delay_cycles(5);	
 	CLRI2CSDA1();//START:when CLK is high,DATA change form high to low 
	__delay_cycles(20);	
	LedOff(GPIOC,GPIO_PIN_0);//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop_mcu0(void)
{
	OUTPUTI2CSDA_1();//sda�����
	__delay_cycles(1);
	LedOff(GPIOC,GPIO_PIN_0);
	CLRI2CSDA1();//STOP:when CLK is high DATA change form low to high
 	__delay_cycles(5);
	SETI2CSCL1();
	__delay_cycles(12);	
	SETI2CSDA1();//����I2C���߽����ź�
	__delay_cycles(5);						   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t IIC_Wait_Ack_mcu0(void)
{
	volatile uint8_t ucErrTime=0;
	 
	LedOff(GPIOC,GPIO_PIN_0);
	__delay_cycles(5);
	INPUTI2CSDA_1();
	//__delay_cycles(5);
	__delay_cycles(12);	
	SETI2CSCL1();//ʱ�����1 			 
	while(CHECKI2CSDA1())
	{
		ucErrTime++;
		if(ucErrTime> 10)
		{
			IIC_Stop();
			return 1;
		}
		//__delay_cycles(10);
	}   
	
	__delay_cycles(10);
	return 0;  
} 
//����ACKӦ��
void IIC_Ack_mcu0(void)
{
	LedOff(GPIOC,GPIO_PIN_0);
	OUTPUTI2CSDA_1();
	CLRI2CSDA1();
	__delay_cycles(10);
	SETI2CSCL1();
	__delay_cycles(10);
	
	//INPUTI2CSDA();
}
//������ACKӦ��		    
void IIC_NAck_mcu0(void)
{
	LedOff(GPIOC,GPIO_PIN_0);
	OUTPUTI2CSDA_1();
	__delay_cycles(10);
	SETI2CSDA1();
	__delay_cycles(10);
	SETI2CSCL1();
	__delay_cycles(10);
	LedOff(GPIOC,GPIO_PIN_0);
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte_mcu0(uint8_t txd)
{                         
    volatile uint8_t t;   
	OUTPUTI2CSDA_1(); 
	__delay_cycles(6);   
    for(t=0;t<8;t++)
    {              
		
		 LedOff(GPIOC,GPIO_PIN_0);//����ʱ�ӿ�ʼ���ݴ���
		 __delay_cycles(1);
        if((txd&0x80))
		{
			SETI2CSDA1();
		}
		else
		{
			CLRI2CSDA1();
		}
        txd<<=1; 	  
		__delay_cycles(15);   //��TEA5767��������ʱ���Ǳ����
		SETI2CSCL1();
		__delay_cycles(15); 
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t IIC_Read_Byte_mcu0(uint8_t ack)
{
	volatile uint8_t i,dat = 0;
	LedOff(GPIOC,GPIO_PIN_0);
	__delay_cycles(5);//import�л�������ע����ʱһ����ʱ��
	INPUTI2CSDA_1();//SDA����Ϊ����
    for(i = 0;i < 8;i++ )
	{
        LedOff(GPIOC,GPIO_PIN_0);
        __delay_cycles(20);
		SETI2CSCL1();
        dat <<= 1;
        if(CHECKI2CSDA1()) dat++;   
		__delay_cycles(20); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return dat;
}



int8_t i2c_write_block_mcu0(uint8_t ucSlaveDeviceAddr,uint8_t numBytes,unsigned char multi, void* TxData)
{
	volatile uint8_t  i;
    uint8_t *temp;
	BYTE1 control;
	
	LedInit(SDA_PORT1,SDA_PIN1);
	LedInit(SCL_PORT1,SCL_PIN1);

	temp = (uint8_t *)TxData;           // Initialize array pointer
	control = ucSlaveDeviceAddr & (~0x01);
	IIC_Start_mcu0();
	IIC_Send_Byte_mcu0(control);
	if(IIC_Wait_Ack_mcu0())
	{
		LedInit_in(SDA_PORT1,SDA_PIN1);
		LedInit_in(SCL_PORT1,SCL_PIN1);
		return _FAIL;
	}
	LedOff(GPIOC,GPIO_PIN_0);
	__delay_cycles(30);
	
	for (i = 0; i < numBytes ; i++)
	{
		IIC_Send_Byte_mcu0(*(temp));      // Send data and ack
		
		if(IIC_Wait_Ack_mcu0())//���û���յ�Ӧ��
		{
			LedInit_in(SDA_PORT1,SDA_PIN1);
			LedInit_in(SCL_PORT1,SCL_PIN1);
			return _FAIL;
		}
		LedOff(GPIOC,GPIO_PIN_0);
		__delay_cycles(30);
		temp ++;                                 // Increment pointer to next element
	}
	
	if (multi == 0)
	{	
		IIC_Stop();                              // Quick delay
	}
	
	LedInit_in(SDA_PORT1,SDA_PIN1);
	LedInit_in(SCL_PORT1,SCL_PIN1);
	return _SUCCESS;
}

int8_t i2c_read_block_mcu0(uint8_t ucSlaveDeviceAddr,volatile uint8_t numBytes,void* RxData)
{
    volatile uint8_t  i;
	uint8_t* temp;
	BYTE1 control;
	
	LedInit(SDA_PORT1,SDA_PIN1);
	LedInit(SCL_PORT1,SCL_PIN1);

	temp = (uint8_t *)RxData;           // Initialize array pointer
	control = ucSlaveDeviceAddr | 0x01;
	IIC_Start_mcu0();
	IIC_Send_Byte_mcu0(control);
	if(IIC_Wait_Ack())
	{
		LedInit_in(SDA_PORT1,SDA_PIN1);
		LedInit_in(SCL_PORT1,SCL_PIN1);
		return _FAIL;
	}
	
	
	for (i = 0; i < numBytes ; i++)
	{
		Delay4us();
		if(i == numBytes -1)
		{
			*(temp) = IIC_Read_Byte_mcu0(NACK);// Read last 8-bit data with no ACK
		}
		else
		{
			*(temp) = IIC_Read_Byte_mcu0(ACK);// Read last 8-bit data with no ACK
		}
		

		temp++;                                 // Increment pointer to next element
	}
	
	IIC_Stop();                   // Send Stop condition
	
	LedInit_in(SDA_PORT1,SDA_PIN1);
	LedInit_in(SCL_PORT1,SCL_PIN1);
	return _SUCCESS;
}

int8_t CI2cRead_Block_TEST_mcu0(uint8_t ucSlaveDeviceAddr,uint8_t cmd, uint8_t numBytes,void* RxData)
{
	 volatile uint8_t  i;
	uint8_t* temp;
	BYTE1 control;
	IIC_Start();
	IIC_Send_Byte_mcu0(ucSlaveDeviceAddr);
	if(IIC_Wait_Ack_mcu0())
	{
		return _FAIL;_I2C_WR_1  
	}
	IIC_Send_Byte(cmd);
	if(IIC_Wait_Ack_mcu0())
	{
		return _FAIL;
	}
	
	LedOff(GPIOC,GPIO_PIN_0);
	OUTPUTI2CSDA_1();
	SETI2CSDA1();
	__delay_cycles(50);
	SETI2CSCL1();
	temp = (uint8_t *)RxData;           // Initialize array pointer
	control = ucSlaveDeviceAddr | 0x01;
	IIC_Start();
	IIC_Send_Byte_mcu0(control);
	if(IIC_Wait_Ack_mcu0())
	{
		return _FAIL;
	}
	
	
	for (i = 0; i < numBytes ; i++)
	{
		Delay4us();
		if(i == numBytes -1)
		{
			*(temp) = IIC_Read_Byte_mcu0(NACK);// Read last 8-bit data with no ACK
		}
		else
		{
			*(temp) = IIC_Read_Byte_mcu0(ACK);// Read last 8-bit data with no ACK
		}
		

		temp++;                                 // Increment pointer to next element
	}
	
	IIC_Stop_mcu0();                   // Send Stop condition
	
	return _SUCCESS;
}

uint8_t read_vol_IIC_mcu0(uint8_t ucSlaveDeviceAddr,uint8_t rx_numBytes,void* RxData,uint8_t tx_numBytes,void* TxData)
{
	volatile uint8_t  i;
	//uint8_t *temp;
	BYTE1 control;

	//temp = (uint8_t *)TxData;           // Initialize array pointer
	control = ucSlaveDeviceAddr & (~0x01);
	IIC_Start_mcu0();
	IIC_Send_Byte_mcu0(control);
	if(IIC_Wait_Ack_mcu0())
	{
		errorflag = 1;
		return 0;
	}
	for (i = 0; i < tx_numBytes ; i++)
	{
		IIC_Send_Byte_mcu0(0x0d);      // Send data and ack
		if(IIC_Wait_Ack_mcu0())
		{
			errorflag = 1;
			return 0;
		}
		TxData ++;                                 // Increment pointer to next element
	}
	
	control = ucSlaveDeviceAddr | 0x01;
	IIC_Start_mcu0();
	IIC_Send_Byte_mcu0(control);
	if(IIC_Wait_Ack_mcu0())
	{
		errorflag = 1;
		return 0;
	}
	
	
	for (i = 0; i < rx_numBytes ; i++)
	{
		Delay4us();
		if(i == rx_numBytes -1)
		{
			*((uint8_t *)RxData) = IIC_Read_Byte_mcu0(0);// Read last 8-bit data with no ACK
			//CI2cSendNoAck();
		}
		else
		{
			*((uint8_t *)RxData) = IIC_Read_Byte_mcu0(1);// Read last 8-bit data with no ACK
			//CI2cSendAck();
		}
		

		RxData++;                                 // Increment pointer to next element
	}
	
	IIC_Stop_mcu0();                   // Send Stop condition
	return true;
	
}






















//==============================================================================
/*

void SWI2CMST_writeBlock_mcu0(uint8_t ucSlaveDeviceAddr, uint8_t numBytes, unsigned char multi, void* TxData)
{

	uint8_t  i;
	uint8_t *temp;
	BYTE1 control;

	temp = (uint8_t *)TxData;           // Initialize array pointer
	control = ucSlaveDeviceAddr | _I2C_WR;
	if(CI2cStart(control) != _I2C_OK)  // Send Start condition
	return _FAIL;

	for (i = 0; i < numBytes ; i++)
	{
		CI2cSendByte(*(temp));      // Send data and ack
		temp ++;                                 // Increment pointer to next element
	}
	
	if (multi == 0)
	{
		CI2cStop();                              // Quick delay
	}
	

	return _SUCCESS;
}


int8_t SWI2CMST_readBlock_mcu0(uint8_t ucSlaveDeviceAddr,uint8_t numBytes,void* RxData)
{
	uint8_t  i;
	uint8_t* temp;
	BYTE1 control;

	temp = (uint8_t *)RxData;           // Initialize array pointer
	control = ucSlaveDeviceAddr | _I2C_RD;
	if(CI2cStart(control) != _I2C_OK)  // Send Start condition
	return _FAIL;
	
	for (i = 0; i < numBytes - 1; i++)
	{
		*(temp) = CI2cGetByte();// Read last 8-bit data with no ACK
		CI2cSendAck();
		temp++;                                 // Increment pointer to next element
	}
	*(temp) = CI2cGetByte();// Read last 8-bit data with no ACK
	CI2cSendNoAck();
	CI2cStop();                   // Send Stop condition
	
	return _SUCCESS;
}

*/