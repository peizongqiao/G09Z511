#include "i2c_master_1.h"


//BYTE CI2cSendByte(BYTE ucValue);
uint8_t errorflag_1 = 0;

//----------------------------------------------------------------------------------------------------
// I2C communication basic function
//----------------------------------------------------------------------------------------------------
void __delay_cycles_1(volatile uint16_t cnt)
{
	while(cnt--)
	{
		__asm__ __volatile__("nop");
		//__asm__ __volatile__("nop");
	}
}

void __delay_ms_1(volatile uint16_t cnt)
{
	volatile uint16_t i,j;
	
//	for(i=cnt;i>0;i--)
//	for(j=1100;j>0;j--);
	for(i=0;i<cnt;i++)
	{
		for(j=0;j<1100;j++);
	}
}
void Delay4us_1(void)
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

BYTE CHECKI2CSDA_1(void)  
{
	 return  GETI2CSDA_1();
}

//У��IIC-SCL��״̬
BYTE CHECKI2CSCL_1(void)
{
	BYTE level = 0;
	INPUTI2CSCL_1();
	level = GETI2CSCL_1();
	
	return level;
}

//��ʼ��IIC
void i2c_init_1(void)
{			
  OUTPUTI2CSDA_1();
  OUTPUTI2SCL_1();
  
  PULLUPSCL_1();
  PULLUPSDA_1();
  
  SETI2CSCL_1();
  SETI2CSDA_1();

}
//����IIC��ʼ�ź�
void IIC_Start_1(void)
{
	OUTPUTI2CSDA_1();     //sda�����
	__delay_cycles_1(1);	
	SETI2CSDA_1();	 	 	  
	SETI2CSCL_1();
	__delay_cycles_1(5);	
 	CLRI2CSDA_1();//START:when CLK is high,DATA change form high to low 
	__delay_cycles_1(20);	
	LedOff(GPIOA,GPIO_PIN_9);//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop_1(void)
{
	OUTPUTI2CSDA_1();//sda�����
	__delay_cycles_1(1);
	LedOff(GPIOA,GPIO_PIN_9);
	CLRI2CSDA_1();//STOP:when CLK is high DATA change form low to high
 	__delay_cycles_1(5);
	SETI2CSCL_1();
	__delay_cycles_1(12);	
	SETI2CSDA_1();//����I2C���߽����ź�
	__delay_cycles_1(5);						   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t IIC_Wait_Ack_1(void)
{
	volatile uint8_t ucErrTime=0;
	 
	LedOff(GPIOA,GPIO_PIN_9);
	__delay_cycles_1(5);
	INPUTI2CSDA_1();
	//__delay_cycles_1(5);
	__delay_cycles_1(12);	
	SETI2CSCL_1();//ʱ�����1 			 
	while(CHECKI2CSDA_1())
	{
		ucErrTime++;
		if(ucErrTime> 10)
		{
			IIC_Stop_1();
			return 1;
		}
		//__delay_cycles_1(10);
	}   
	
	__delay_cycles_1(10);
	return 0;  
} 
//����ACKӦ��
void IIC_Ack_1(void)
{
	LedOff(GPIOA,GPIO_PIN_9);
	OUTPUTI2CSDA_1();
	CLRI2CSDA_1();
	__delay_cycles_1(10);
	SETI2CSCL_1();
	__delay_cycles_1(10);
	
	//INPUTI2CSDA_1();
}
//������ACKӦ��		    
void IIC_NAck_1(void)
{
	LedOff(GPIOA,GPIO_PIN_9);
	OUTPUTI2CSDA_1();
	__delay_cycles_1(10);
	SETI2CSDA_1();
	__delay_cycles_1(10);
	SETI2CSCL_1();
	__delay_cycles_1(10);
	LedOff(GPIOA,GPIO_PIN_9);
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte_1(uint8_t txd)
{                         
    volatile uint8_t t;   
	OUTPUTI2CSDA_1(); 
	__delay_cycles_1(6);   
    for(t=0;t<8;t++)
    {              
		
		 LedOff(GPIOA,GPIO_PIN_9);//����ʱ�ӿ�ʼ���ݴ���
		 __delay_cycles_1(1);
        if((txd&0x80))
		{
			SETI2CSDA_1();
		}
		else
		{
			CLRI2CSDA_1();
		}
        txd<<=1; 	  
		__delay_cycles_1(15);   //��TEA5767��������ʱ���Ǳ����
		SETI2CSCL_1();
		__delay_cycles_1(15); 
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t IIC_Read_Byte_1(uint8_t ack)
{
	volatile uint8_t i,dat = 0;
	LedOff(GPIOA,GPIO_PIN_9);
	__delay_cycles_1(5);//import�л�������ע����ʱһ����ʱ��
	INPUTI2CSDA_1();//SDA����Ϊ����
    for(i = 0;i < 8;i++ )
	{
        LedOff(GPIOA,GPIO_PIN_9);
        __delay_cycles_1(20);
		SETI2CSCL_1();
        dat <<= 1;
        if(CHECKI2CSDA_1()) dat++;   
		__delay_cycles_1(20); 
    }					 
    if (!ack)
        IIC_NAck_1();//����nACK
    else
        IIC_Ack_1(); //����ACK   
    return dat;
}



int8_t i2c_write_block_1(uint8_t ucSlaveDeviceAddr,uint8_t numBytes,unsigned char multi, void* TxData)
{
	volatile uint8_t  i;
    uint8_t *temp;
	BYTE control;
	
	LedInit(SDA_PORT_1,SDA_PIN_1);
	LedInit(SCL_PORT_1,SCL_PIN_1);

	temp = (uint8_t *)TxData;           // Initialize array pointer
	control = ucSlaveDeviceAddr & (~0x01);
	IIC_Start_1();
	IIC_Send_Byte_1(control);
	if(IIC_Wait_Ack_1())
	{
		LedInit_in(SDA_PORT_1,SDA_PIN_1);
		LedInit_in(SCL_PORT_1,SCL_PIN_1);
		return _FAIL;
	}
	LedOff(GPIOA,GPIO_PIN_9);
	__delay_cycles_1(30);
	
	for (i = 0; i < numBytes ; i++)
	{
		IIC_Send_Byte_1(*(temp));      // Send data and ack
		
		if(IIC_Wait_Ack_1())//���û���յ�Ӧ��
		{
			LedInit_in(SDA_PORT_1,SDA_PIN_1);
			LedInit_in(SCL_PORT_1,SCL_PIN_1);
			return _FAIL;
		}
		LedOff(GPIOA,GPIO_PIN_9);
		__delay_cycles_1(30);
		temp ++;                                 // Increment pointer to next element
	}
	
	if (multi == 0)
	{	
		IIC_Stop_1();                              // Quick delay
	}
	
	LedInit_in(SDA_PORT_1,SDA_PIN_1);
	LedInit_in(SCL_PORT_1,SCL_PIN_1);
	return _SUCCESS;
}

int8_t i2c_read_block_1(uint8_t ucSlaveDeviceAddr,volatile uint8_t numBytes,void* RxData)
{
    volatile uint8_t  i;
	uint8_t* temp;
	BYTE control;
	
	LedInit(SDA_PORT_1,SDA_PIN_1);
	LedInit(SCL_PORT_1,SCL_PIN_1);

	temp = (uint8_t *)RxData;           // Initialize array pointer
	control = ucSlaveDeviceAddr | 0x01;
	IIC_Start_1();
	IIC_Send_Byte_1(control);
	if(IIC_Wait_Ack_1())
	{
		LedInit_in(SDA_PORT_1,SDA_PIN_1);
		LedInit_in(SCL_PORT_1,SCL_PIN_1);
		return _FAIL;
	}
	
	
	for (i = 0; i < numBytes ; i++)
	{
		Delay4us_1();
		if(i == numBytes -1)
		{
			*(temp) = IIC_Read_Byte_1(NACK);// Read last 8-bit data with no ACK
		}
		else
		{
			*(temp) = IIC_Read_Byte_1(ACK);// Read last 8-bit data with no ACK
		}
		

		temp++;                                 // Increment pointer to next element
	}
	
	IIC_Stop_1();                   // Send Stop condition
	
	LedInit_in(SDA_PORT_1,SDA_PIN_1);
	LedInit_in(SCL_PORT_1,SCL_PIN_1);
	return _SUCCESS;
}

int8_t CI2cRead_Block_TEST_1(uint8_t ucSlaveDeviceAddr,uint8_t cmd, uint8_t numBytes,void* RxData)
{
	 volatile uint8_t  i;
	uint8_t* temp;
	BYTE control;
	IIC_Start_1();
	IIC_Send_Byte_1(ucSlaveDeviceAddr);
	if(IIC_Wait_Ack_1())
	{
		return _FAIL;
	}
	IIC_Send_Byte_1(cmd);
	if(IIC_Wait_Ack_1())
	{
		return _FAIL;
	}
	
	LedOff(GPIOA,GPIO_PIN_9);
	OUTPUTI2CSDA_1();
	SETI2CSDA_1();
	__delay_cycles_1(50);
	SETI2CSCL_1();
	temp = (uint8_t *)RxData;           // Initialize array pointer
	control = ucSlaveDeviceAddr | 0x01;
	IIC_Start_1();
	IIC_Send_Byte_1(control);
	if(IIC_Wait_Ack_1())
	{
		return _FAIL;
	}
	
	
	for (i = 0; i < numBytes ; i++)
	{
		Delay4us_1();
		if(i == numBytes -1)
		{
			*(temp) = IIC_Read_Byte_1(NACK);// Read last 8-bit data with no ACK
		}
		else
		{
			*(temp) = IIC_Read_Byte_1(ACK);// Read last 8-bit data with no ACK
		}
		

		temp++;                                 // Increment pointer to next element
	}
	
	IIC_Stop_1();                   // Send Stop condition
	
	return _SUCCESS;
}

uint8_t read_vol_IIC_1(uint8_t ucSlaveDeviceAddr,uint8_t rx_numBytes,void* RxData,uint8_t tx_numBytes,void* TxData)
{
	volatile uint8_t  i;
	//uint8_t *temp;
	BYTE control;

	//temp = (uint8_t *)TxData;           // Initialize array pointer
	control = ucSlaveDeviceAddr & (~0x01);
	IIC_Start_1();
	IIC_Send_Byte_1(control);
	if(IIC_Wait_Ack_1())
	{
		errorflag_1 = 1;
		return 0;
	}
	for (i = 0; i < tx_numBytes ; i++)
	{
		IIC_Send_Byte_1(0x0d);      // Send data and ack
		if(IIC_Wait_Ack_1())
		{
			errorflag_1 = 1;
			return 0;
		}
		TxData ++;                                 // Increment pointer to next element
	}
	
	control = ucSlaveDeviceAddr | 0x01;
	IIC_Start_1();
	IIC_Send_Byte_1(control);
	if(IIC_Wait_Ack_1())
	{
		errorflag_1 = 1;
		return 0;
	}
	
	
	for (i = 0; i < rx_numBytes ; i++)
	{
		Delay4us_1();
		if(i == rx_numBytes -1)
		{
			*((uint8_t *)RxData) = IIC_Read_Byte_1(0);// Read last 8-bit data with no ACK
			//CI2cSendNoAck();
		}
		else
		{
			*((uint8_t *)RxData) = IIC_Read_Byte_1(1);// Read last 8-bit data with no ACK
			//CI2cSendAck();
		}
		

		RxData++;                                 // Increment pointer to next element
	}
	
	IIC_Stop_1();                   // Send Stop condition
	return true;
	
}
