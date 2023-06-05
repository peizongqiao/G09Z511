#ifndef CPUINT_H_INCLUDED
#define CPUINT_H_INCLUDED

#include "n32g43x.h"

#ifdef __cplusplus
extern "C" {
#endif

// 系统时间变量类型
typedef uint32_t counter_time_t;

typedef void (*counter_cb_t)(void);

void CPUINT_init(void);

// COUNTER使用的硬件定时器中断频率
#define COUNTER_CFG_TICK_FREQ_HZ            (1000u)

// COUNTER中断间隔时间
#define COUNTER_TICK_PERIOD_MS              (1000u/COUNTER_CFG_TICK_FREQ_HZ)


// ========================= external =============================
void counter_init(void);
counter_time_t counter_get_uptime(void);
counter_time_t get_tim_delta(counter_time_t old, counter_time_t now);
void task(void);
void time_cnt(void);
#ifdef __cplusplus
}
#endif

#endif /* CPUINT_H_INCLUDED */