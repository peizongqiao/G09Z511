#include "app_iris.h"
#include "app_softtimer.h"
#include "bsp_pi_api.h"
#include "dlp_manager.h"

uint8_t iris_falg = 0,iris_step_number = 0;
uint32_t iris_step = 0;
uint32_t iris_step_go = 0;
uint32_t step = 0;
volatile uint16_t motor_pps = 500;
volatile float torque = 1.000;
uint32_t Cnt_1 = 0;
bool iris_direction = true;

uint32_t ShakeCnt0 = 0;
uint32_t ShakeCnt1 = 0;
uint8_t PicSwtichCnt = 0;
bool old_mode = false;
bool flag_pi;
bool flag_pi_1;
bool irisreset;
extern uint8_t aut_iris;
extern uint8_t flag_count;
extern uint16_t log_step;
uint16_t iris_number;
uint16_t iris_step_g;
uint32_t Cnt = 0;

void LedInit_1(GPIO_Module* GPIOx, uint16_t Pin)
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

void app_iris_init(void)
{
    app_iris_gpio_init();
}

void app_iris_gpio_init(void)
{
    GPIO_InitType GPIO_InitStructure;
    
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    
    GPIO_InitStructure.Pin        = GPIO_PIN_12|GPIO_PIN_15;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.Pin        = GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin        = GPIO_PIN_5;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
 
	IRIS_I1_0;
	IRIS_I0_0;
	
	IRIS_power_on;
}

int step_mode,step_number;



uint8_t iris_pi_flag;
uint16_t ii;
void screen_poll()
{
	if(flag_count==1)
	{
		flag_count=0;
		pattern_black();
	}
	if(flag_count==2)
	{
		flag_count=0;
		pattern_red();
	}
	if(flag_count==3)
	{
		flag_count=0;
		pattern_green();
	}
	if(flag_count==4)
	{
		flag_count=0;
		pattern_blue();
	}
	if(flag_count==5)
	{
		flag_count=0;
		pattern_white();
	}
	if(flag_count==6)
	{
		flag_count=0;
		splash_0();
	}
	if(flag_count==7)
	{
		flag_count=0;
		splash_1();
	}
	if(flag_count==8)
	{
		flag_count=0;
		splash_2();
	}
	if(flag_count==9)
	{
		flag_count=0;
		splash_3();
	}
	if(flag_count==10)
	{
		flag_count=0;
		splash_4();
	}
	if(flag_count==42)
	{
		flag_count=0;
		source_external();
	}
}
void app_iris_poll() 
{
	if(aut_iris==1||flag_count==34) 
	{
		flag_count=0;
		aut_iris = 0;
		iris_step_g = 0;
        flag_pi = 1;
		iris_step = 540;
		LedInit_1(GPIOC, GPIO_PIN_5);
		LedOff(GPIOC, GPIO_PIN_5);
		IRIS_I1_0;
		IRIS_I0_0;
	}
	if(aut_iris==2) 
	{
		aut_iris = 0;
	    flag_pi = 0;
		irisreset=1;
		iris_step_go = log_step*17+7;
		LedInit_1(GPIOC, GPIO_PIN_5);
		LedOn(GPIOC, GPIO_PIN_5);
		IRIS_I1_0;
		IRIS_I0_0;
	}
	if(aut_iris==3) 
	{
		aut_iris = 0;
	    flag_pi = 1;
		iris_step = log_step*17;
		LedInit_1(GPIOC, GPIO_PIN_5);
		LedOff(GPIOC, GPIO_PIN_5);
		IRIS_I1_0;
		IRIS_I0_0;
	}
	if(aut_iris==4) //STOP
	{
		aut_iris = 0;
		iris_step_go = 0;
		iris_step = 0;
	}
	if(aut_iris==5)
	{
		aut_iris = 0;
		if(log_step==17)
		{
			iris_step_go = 7*17+7;
		}
		else if(log_step==20)
		{
			iris_step_go = 14*17+7;
		}
		else if(log_step==25)
		{
			iris_step_go = 24*17+7;
		}
		else if(log_step == 30)
		{
			iris_step_go = 30*17+7;
		}
		flag_pi = 0;
		irisreset = 0;
	}
}

uint8_t iristest;

bool Recycle,Recycle_1;
bool iris_reset;


void app_iris_poll_1() // 7ms get in
{
	if(flag_count==37) // Farward 28 Step
	{
		flag_count=0;
		flag_pi = 0;
		irisreset=1;
		iris_step_g = 0;
		iris_step = 493;//476
		LedInit_1(GPIOC, GPIO_PIN_5);
		LedOn(GPIOC, GPIO_PIN_5);
		IRIS_I1_0;
		IRIS_I0_0;
	}
	if(flag_count==35) // Farward 7 Step
	{
		flag_count=0;
		iris_step_g = 0;
		irisreset=1;
		flag_pi = 0;		
		iris_step = 189;
		LedInit_1(GPIOC, GPIO_PIN_5);
		LedOn(GPIOC, GPIO_PIN_5);
		IRIS_I1_0;
		IRIS_I0_0;
	}
	if(flag_count==36) // Farward 22 Step
	{
		flag_count=0;
		iris_step_g = 0;
		irisreset=1;
		flag_pi = 0;		
		iris_step = 408;
		LedInit_1(GPIOC, GPIO_PIN_5);
		LedOn(GPIOC, GPIO_PIN_5);
		IRIS_I1_0;
		IRIS_I0_0;
	}
	if(flag_count==52) // Farward 22 Step
	{
		flag_count=0;	
		iris_step_g = 0;		
		iris_step = 17;
		irisreset=1;
		flag_pi = 0;
		LedInit_1(GPIOC, GPIO_PIN_5);
		LedOn(GPIOC, GPIO_PIN_5);
		IRIS_I1_0;
		IRIS_I0_0;
	}
	if(flag_count==53) // Farward 22 Step
	{
		flag_count=0;	
		iris_step_g = 0;		
		iris_step = 17;
		LedInit_1(GPIOC, GPIO_PIN_5);
		LedOff(GPIOC, GPIO_PIN_5);
		IRIS_I1_0;
		IRIS_I0_0;
	}
	if(flag_count==58) // Farward 22 Step
	{
		flag_count=0;
		iristest = 0;
		iris_number = 0;		
		iris_step_g = 520;
		LedInit_1(GPIOC, GPIO_PIN_5);
		LedOn(GPIOC, GPIO_PIN_5);
		IRIS_I1_0;
		IRIS_I0_0;
	}
}

void iris_res()
{
	iris_reset = IrisMotorWait();
	if(iris_reset==0)
	{
		iris_step = 540;
		LedInit_1(GPIOC, GPIO_PIN_5);
		LedOff(GPIOC, GPIO_PIN_5);
		IRIS_I1_0;
		IRIS_I0_0;
	}
}

void iris_poll_go()
{
	if(iris_step_g>1)
	{
		if(0 == iris_step_number)
		{
			iris_step_number=1;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step_g--;
		}
	}
	if(iris_step_g==1&&iris_reset==0)
	{
		iris_step_go = 1;
		irisreset=1;
		Recycle = false;
		LedInit_1(GPIOC, GPIO_PIN_5);
		LedOff(GPIOC, GPIO_PIN_5);
		IRIS_I1_0;
		IRIS_I0_0;
	}
}

void iris_old()
{
	if(flag_count==49){// OLD
		flag_count=0;
		Recycle = true;
		}
	if(flag_count==38){// Manual
			flag_count=0;
			iris_step = 0;
			Recycle_1 = false;
			Recycle = false;
		}
	if(flag_count == 54)
	{
		flag_count = 0;
		iris_step = 0;
		Recycle_1 = true;
	}
}

void iris_poll()
{
	if(0 != iris_step_go&&irisreset==1&&Recycle == false)
	{
		if(0 == iris_step_number)
		{
			iris_step_number=1;
			iristest = 1;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iristest = 1;
			iris_step_go--;
			iris_number++;
			if(iris_number>480&&iris_number<540)
			{
				iristest = 2;
			}
			else if(iris_number>540)
			{
				iristest = 3;
			}
		}
	}
	if(Recycle== true)                                      //老化IRIS一（两种老化）
	{
		if(Cnt < 1000)
		{
			Cnt++;
		}
		else
		{				
			Cnt = 0;
			if(iris_direction == 1)
			{
				io_set_dir_out(GPIOC, GPIO_PIN_5);
				io_set_low(GPIOC, GPIO_PIN_5);
				IRIS_I1_0;
				IRIS_I0_0;
				iris_direction = 0;
			}
			else
			{
				io_set_dir_out(GPIOC, GPIO_PIN_5);
				io_set_high(GPIOC, GPIO_PIN_5);
				IRIS_I1_0;
				IRIS_I0_0;
				iris_direction = 1;
			}
		}
		if(0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
		}
	}	
}
void iris_poll_bk()
{
	if(0 != iris_step)
	{
		if(0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_number--;
			if(iris_number>2000)
				iris_number = 0;
			iris_step--;
		}
	}
}
void IRIS_19_PI()
{
	iris_reset = IrisMotorWait();
	if(iris_reset==1&&flag_pi==1)
	{
		iris_step = 0;
		iris_number=0;
	}
}

void reset_iris()
{
	if(iris_reset==0&&irisreset==0)
	{
	    iris_step = 1;
		LedInit_1(GPIOC, GPIO_PIN_5);
		LedOff(GPIOC, GPIO_PIN_5);
		IRIS_I1_0;
		IRIS_I0_0;
	}
	if(iris_reset==1)
	{
		LedInit_1(GPIOC, GPIO_PIN_5);
		LedOn(GPIOC, GPIO_PIN_5);
		irisreset = 1;
	}
}


uint8_t iris_flag = 0;
uint16_t count_1=0;
uint16_t time_flag = 0;
void iris_flag_poll()
{
	if(Recycle_1&&time_flag!=30000)
	{
		count_1++;
		if(count_1==130)
		{
			iris_flag = 2;
			iris_step=51;
			LedInit_1(GPIOC, GPIO_PIN_5);
			LedOn(GPIOC, GPIO_PIN_5);
		}
		else if(count_1==260)
		{
			iris_flag = 3;
			iris_step=51;
			LedInit_1(GPIOC, GPIO_PIN_5);
			LedOn(GPIOC, GPIO_PIN_5);
		}
		else if(count_1==390)
		{
			iris_flag = 4;
			iris_step=51;
			LedInit_1(GPIOC, GPIO_PIN_5);
			LedOn(GPIOC, GPIO_PIN_5);
		}
		else if(count_1==520)
		{
			iris_flag = 5;
			iris_step=51;
			LedInit_1(GPIOC, GPIO_PIN_5);
			LedOn(GPIOC, GPIO_PIN_5);
		}
		else if(count_1==650)
		{
			iris_flag = 6;
			iris_step=51;
			LedInit_1(GPIOC, GPIO_PIN_5);
			LedOn(GPIOC, GPIO_PIN_5);
		}
		else if(count_1==780)
		{

			iris_flag = 7;
			iris_step=51;
			LedInit_1(GPIOC, GPIO_PIN_5);
			LedOn(GPIOC, GPIO_PIN_5);
		}
		else if(count_1==810)
		{

			iris_flag = 8;
			iris_step=51;
			LedInit_1(GPIOC, GPIO_PIN_5);
			LedOn(GPIOC, GPIO_PIN_5);
		}
		else if(count_1==940)
		{

			iris_flag = 9;
			iris_step=51;
			LedInit_1(GPIOC, GPIO_PIN_5);
			LedOn(GPIOC, GPIO_PIN_5);
		}
		else if(count_1==1070)
		{

			iris_flag = 10;
			iris_step=51;
			LedInit_1(GPIOC, GPIO_PIN_5);
			LedOn(GPIOC, GPIO_PIN_5);
		}
		else if(count_1==1300)
		{

			iris_flag = 11;
			iris_step=34;
			LedInit_1(GPIOC, GPIO_PIN_5);
			LedOn(GPIOC, GPIO_PIN_5);
		}
		else if(count_1==1430)
		{
			iris_flag = 12;
			iris_step=34;
			LedInit_1(GPIOC, GPIO_PIN_5);
			LedOff(GPIOC, GPIO_PIN_5);
		}
		else if(count_1==1560)
		{
			iris_flag = 13;
			iris_step=51;
			LedInit_1(GPIOC, GPIO_PIN_5);
			LedOff(GPIOC, GPIO_PIN_5);
		}
		else if(count_1==1690)
		{
			iris_flag = 14;
			iris_step=51;
			LedInit_1(GPIOC, GPIO_PIN_5);
			LedOff(GPIOC, GPIO_PIN_5);
		}
		else if(count_1==1820)
		{
			iris_flag = 15;
			iris_step=51;
			LedInit_1(GPIOC, GPIO_PIN_5);
			LedOff(GPIOC, GPIO_PIN_5);
		}
		else if(count_1==1950)
		{
			iris_flag = 16;
			iris_step=51;
			LedInit_1(GPIOC, GPIO_PIN_5);
			LedOff(GPIOC, GPIO_PIN_5);
		}
		else if(count_1==2080)
		{
			iris_flag = 17;
			iris_step=51;
			LedInit_1(GPIOC, GPIO_PIN_5);
			LedOff(GPIOC, GPIO_PIN_5);
		}
		else if(count_1==2210)
		{
			iris_flag = 18;
			iris_step=51;
			LedInit_1(GPIOC, GPIO_PIN_5);
			LedOff(GPIOC, GPIO_PIN_5);
		}
		else if(count_1==2340)
		{
			iris_flag = 19;
			iris_step=51;
			LedInit_1(GPIOC, GPIO_PIN_5);
			LedOff(GPIOC, GPIO_PIN_5);
		}
		else if(count_1==2470)
		{
			iris_flag = 20;
			iris_step=51;
			LedInit_1(GPIOC, GPIO_PIN_5);
			LedOff(GPIOC, GPIO_PIN_5);
		}
		else if(count_1==2600)
		{
			iris_flag = 21;
			iris_step=51;
			LedInit_1(GPIOC, GPIO_PIN_5);
			LedOff(GPIOC, GPIO_PIN_5);
		}
		else if(count_1>2600)
		{
			count_1=0;
			iris_flag = 0;
			time_flag++;
		}
	}
}
void iris_old_1()//细分的老化要注释上面老化
{
	if(iris_flag==2)
	{
		if(iris_step!=0&&0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(iris_step!=0&&1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step--;
		}
	}
	if(iris_flag==3)
	{
		if(iris_step!=0&&0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(iris_step!=0&&1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step--;
		}
	}
	if(iris_flag==4)
	{
		if(iris_step!=0&&0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(iris_step!=0&&1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step--;
		}
	}
	if(iris_flag==5)
	{
		if(iris_step!=0&&0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(iris_step!=0&&1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step--;
		}
	}
	if(iris_flag==6)
	{
		if(iris_step!=0&&0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(iris_step!=0&&1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step--;
		}
	}
	if(iris_flag==7)
	{
		if(iris_step!=0&&0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(iris_step!=0&&1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step--;
		}
	}
	if(iris_flag==8)
	{
		if(iris_step!=0&&0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(iris_step!=0&&1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step--;
		}
	}
	if(iris_flag==9)
	{
		if(iris_step!=0&&0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(iris_step!=0&&1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step--;
		}
	}
	if(iris_flag==10)
	{
		if(iris_step!=0&&0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(iris_step!=0&&1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step--;
		}
	}
	if(iris_flag==11)
	{
		if(iris_step!=0&&0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(iris_step!=0&&1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step--;
		}
	}
	if(iris_flag==12)
	{
		if(iris_step!=0&&0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(iris_step!=0&&1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step--;
		}
	}
	if(iris_flag==13)
	{
		if(iris_step!=0&&0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(iris_step!=0&&1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step--;
		}
	}
	if(iris_flag==14)
	{
		if(iris_step!=0&&0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(iris_step!=0&&1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step--;
		}
	}
	if(iris_flag==15)
	{
		if(iris_step!=0&&0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(iris_step!=0&&1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step--;
		}
	}
	if(iris_flag==16)
	{
		if(iris_step!=0&&0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(iris_step!=0&&1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step--;
		}
	}
	if(iris_flag==17)
	{
		if(iris_step!=0&&0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(iris_step!=0&&1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step--;
		}
	}
	if(iris_flag==18)
	{
		if(iris_step!=0&&0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(iris_step!=0&&1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step--;
		}
	}
	if(iris_flag==19)
	{
		if(iris_step!=0&&0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(iris_step!=0&&1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step--;
		}
	}
	if(iris_flag==20)
	{
		if(iris_step!=0&&0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(iris_step!=0&&1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step--;
		}
	}
	if(iris_flag==21)
	{
		if(iris_step!=0&&0 == iris_step_number)
		{
			iris_step_number++;
			GPIOB->PBSC = GPIO_PIN_5;
		}
		else if(iris_step!=0&&1 == iris_step_number)
		{
			iris_step_number = 0;
			GPIOB->PBC = GPIO_PIN_5;
			iris_step--;
		}
	}
}

