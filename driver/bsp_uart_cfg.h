#ifndef _BSP_UART_CFG_H_
#define _BSP_UART_CFG_H_

#include "n32g43x.h"
#include "n32g43x_gpio.h"
#include "n32g43x_usart.h"
#include "n32g43x_rcc.h"

#define LOG_USARTx      UART4
#define LOG_PERIPH      RCC_APB2_PERIPH_UART4
#define LOG_GPIO        GPIOB
#define LOG_PERIPH_GPIO RCC_APB2_PERIPH_GPIOB
#define LOG_TX_PIN      GPIO_PIN_14
#define LOG_RX_PIN      GPIO_PIN_15
#define LOG_Rx_GPIO_AF  GPIO_AF6_UART4
#define LOG_Tx_GPIO_AF  GPIO_AF6_UART4
#define LOG_APBxClkCmd  RCC_EnableAPB2PeriphClk
#define LOG_IRQn        UART4_IRQn
#define LOG_IRQHandler  UART4_IRQHandler


#endif /* _BSP_UART_CFG_H_ */