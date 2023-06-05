#ifndef N32G43X_START_PINS_H_INCLUDED
#define N32G43X_START_PINS_H_INCLUDED

//#include <port.h>
#include "n32g43x.h"

void io_set_high(GPIO_Module* GPIOx,uint16_t GPIO_PIN_X);
void io_set_low(GPIO_Module* GPIOx,uint16_t GPIO_PIN_X);
void io_set_dir_out(GPIO_Module* GPIOx,uint16_t Pin);
void io_set_dir_in(GPIO_Module* GPIOx,uint16_t Pin);
void io_set_pull_off_mode(GPIO_Module* GPIOx,uint16_t Pin);
void io_set_pull_up_mode(GPIO_Module* GPIOx,uint16_t Pin);
int io_get_level(GPIO_Module* GPIOx,uint16_t Pin);

#endif /* ATMEL_START_PINS_H_INCLUDED */
