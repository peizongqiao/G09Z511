#include <string.h>
#include "app_log.h"
#include "../driver/bsp_uart.h"

/*
* @功能说明:日志打印初始化
* @注    意:无
* @形    参:无
* @返    回:无
*/
void log_init(void)
{
    // TODO：mutex锁初始化
    // 串口底层初始化
    bsp_uart_api_init();
}

static int is_lr_sent = 0;

//int fputc(int ch, FILE* f)
//{
//    if (ch == '\r')
//    {
//        is_lr_sent = 1;
//    }
//    else if (ch == '\n')
//    {
//        if (!is_lr_sent)
//        {
//            USART_SendData(LOG_USARTx, (uint8_t)'\r');
//            /* Loop until the end of transmission */
//            while (USART_GetFlagStatus(LOG_USARTx, USART_FLAG_TXC) == RESET)
//            {
//            }
//        }
//        is_lr_sent = 0;
//    }
//    else
//    {
//        is_lr_sent = 0;
//    }
//    USART_SendData(LOG_USARTx, (uint8_t)ch);
//    /* Loop until the end of transmission */
//    while (USART_GetFlagStatus(LOG_USARTx, USART_FLAG_TXC) == RESET)
//    {
//    }
//    return ch;
//}

#ifdef USE_FULL_ASSERT

__WEAK void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    log_error("assertion failed: `%s` at %s:%d", expr, file, line);
    while (1)
    {
    }
}
#endif // USE_FULL_ASSERT
