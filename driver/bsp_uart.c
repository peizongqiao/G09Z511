#include "bsp_uart.h"
#include "app_log.h"
#include <string.h>

uint8_t RxBuffer[15];
uint8_t log_number = 0,log_flag = 0;

void UART_NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;
    
     /* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    /* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel            = LOG_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd         = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void bsp_uart_api_init()
{
    GPIO_InitType GPIO_InitStructure;
    USART_InitType USART_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    RCC_EnableAPB2PeriphClk(LOG_PERIPH_GPIO, ENABLE);

    LOG_APBxClkCmd(LOG_PERIPH, ENABLE);

    UART_NVIC_Configuration();
    
    GPIO_InitStructure.Pin        = LOG_TX_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Alternate = LOG_Tx_GPIO_AF;
    GPIO_InitPeripheral(LOG_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.Pin       = LOG_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = LOG_Rx_GPIO_AF;
    GPIO_InitPeripheral(LOG_GPIO, &GPIO_InitStructure);

    USART_InitStructure.BaudRate            = 115200;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;

    // init uart
    USART_Init(LOG_USARTx, &USART_InitStructure);

    // enable uart
    USART_Enable(LOG_USARTx, ENABLE);
    
    USART_ConfigInt(LOG_USARTx, USART_INT_RXDNE, ENABLE);
}
static int is_lr_sent = 0;

int fputc(int ch, FILE* f)
{
    if (ch == '\r')
    {
        is_lr_sent = 1;
    }
    else if (ch == '\n')
    {
        if (!is_lr_sent)
        {
            USART_SendData(LOG_USARTx, (uint8_t)'\r');
            /* Loop until the end of transmission */
            while (USART_GetFlagStatus(LOG_USARTx, USART_FLAG_TXC) == RESET)
            {
            }
        }
        is_lr_sent = 0;
    }
    else
    {
        is_lr_sent = 0;
    }
    USART_SendData(LOG_USARTx, (uint8_t)ch);
    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(LOG_USARTx, USART_FLAG_TXC) == RESET)
    {
    }
    return ch;
}

/**
 * @brief  This function handles USARTz global interrupt request.
 */
void LOG_IRQHandler(void)
{
    if (USART_GetIntStatus(LOG_USARTx, USART_INT_RXDNE) != RESET && (0 == log_flag))
    {
        RxBuffer[log_number++] = USART_ReceiveData(LOG_USARTx);
        if('[' == RxBuffer[log_number-1])
        {
            RxBuffer[0] = RxBuffer[log_number - 1];
            log_number = 1;
        }
        else if(']' == RxBuffer[log_number-1])
        {
            USART_ConfigInt(LOG_USARTx, USART_INT_RXDNE, DISABLE);
            log_number = 0;
            log_flag = 1;
        }
        else if(log_number > 15)
        {
            log_number = 0;
            log_flag = 0;
        }
            
    }
}

#ifdef USE_FULL_ASSERT

__WEAK void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    log_error("assertion failed: `%s` at %s:%d", expr, file, line);
    while (1)
    {
    }
}
#endif // USE_FULL_ASSERT
