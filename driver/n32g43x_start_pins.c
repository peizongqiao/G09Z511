
#include "n32g43x.h"
#include "n32g43x_start_pins.h"


//设置输出高
void io_set_high(GPIO_Module* GPIOx,uint16_t GPIO_PIN_X)
{
    GPIOx->PBSC = GPIO_PIN_X;
}
//设置输出低
void io_set_low(GPIO_Module* GPIOx,uint16_t GPIO_PIN_X)
{
    GPIOx->PBC = GPIO_PIN_X;
}
//设置为输出模式
void io_set_dir_out(GPIO_Module* GPIOx,uint16_t Pin)
{
    GPIOx->PMODE |= (1 << (Pin*2));
}
//设置为输入模式
void io_set_dir_in(GPIO_Module* GPIOx,uint16_t Pin)
{
    GPIOx->PMODE &= ~(1 << (Pin*2));
}
//设置为下拉输入模式
void io_set_pull_off_mode(GPIO_Module* GPIOx,uint16_t Pin)
{
    GPIOx->PUPD |= (1 << (Pin*2));
}
//设置为上拉输入模式
void io_set_pull_up_mode(GPIO_Module* GPIOx,uint16_t Pin)
{
    GPIOx->PUPD |= (2 << (Pin*2));
}
//读取端口电平
int io_get_level(GPIO_Module* GPIOx,uint16_t Pin)
{
	if(0 != (GPIOx->PID&(1 << Pin)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}