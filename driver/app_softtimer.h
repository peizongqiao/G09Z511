/*
* 模块名称 :软件定时器功能。
* 文件名称 : xxxx.h
* 说    明 :1.封装了任务注册接口;
*          2.封装了延时队列接口。
*
*/
#ifndef _APP_SOFTTIMER_H_
#define _APP_SOFTTIMER_H_

#include "../driver/GMtypes.h"
#include "counter.h"
#include "../driver/config.h"



// 软件定时器支持数量(1~255)
#define SOFTTIMER_CFG_ITEMS_NUMS                    CFG_SOFTTIMER_NUMS

// 获取系统时间戳(units:1ms)
#define GET_TICK_STAMP()                            counter_get_uptime()


// 软件定时器运行模式
typedef enum
{
    E_RUNMODE_NOT_USE = 0,                          // 软件定时器，未使用
    E_RUNMODE_SINGLE,                               // 软件定时器，单次模式
    E_RUNMODE_CONTINUE ,                            // 软件定时器，连续模式
}run_mode_t;


typedef void (*softtimer_cb_t)(void);





// =================== external function ===================
void softtimer_init(void);
void softtimer_register(uint16_t period_ms, softtimer_cb_t pfunc, run_mode_t run_mode);
void softtimer_remove_by_function(softtimer_cb_t function);
void softtimer_poll(void);


/*
* 封装接口：周期任务
*/
// 任务调度初始化
#define TASK_INIT()                                 softtimer_init()
// 任务创建：(period_ms-建议为素数*10)
// 素数表：2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71...
#define TASK_PERIOD_CB_CREATE(period_ms, func)      softtimer_register(period_ms, func, E_RUNMODE_CONTINUE)
// 任务销毁：通过函数名
#define TASK_PERIOD_CB_DESTROY(func)                softtimer_remove_by_function(func)
// 任务调度：开始
#define TASK_START()                                counter_init()
// 任务调度：运行
#define TASK_SCHEDULE()                             softtimer_poll()



/*
* 封装接口：延时队列
* 说明：1.一般用于延时执行某个事情(function)。
*      2.延时队列只支持单次任务处理。
*/
// 延时队列：压入队列中
#define DELAY_QUEUE_PUSH(delay_ms, func)            softtimer_register(delay_ms, func, E_RUNMODE_SINGLE)
// 延时队列：从队列中弹出
// 如果延时队列中压入了相同处理函数的，则弹出只弹出较早压入的处理函数。
#define DELAY_QUEUE_POP_BY_FUNCTION(func)           softtimer_remove_by_function(func)






#endif /* _APP_SOFTTIMER_H_ */
