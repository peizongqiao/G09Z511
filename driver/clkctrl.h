#ifndef CLKCTRL_H_INCLUDED
#define CLKCTRL_H_INCLUDED

#include "n32g43x.h"
#include "../driver/app_log.h"

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    SYSCLK_PLLSRC_HSI,
    SYSCLK_PLLSRC_HSIDIV2,
    SYSCLK_PLLSRC_HSI_PLLDIV2,
    SYSCLK_PLLSRC_HSIDIV2_PLLDIV2,
    SYSCLK_PLLSRC_HSE,
    SYSCLK_PLLSRC_HSEDIV2,
    SYSCLK_PLLSRC_HSE_PLLDIV2,
    SYSCLK_PLLSRC_HSEDIV2_PLLDIV2,
};

void DumpClock(const char* msg);
void SetSysClockToMSI(void);
void SetSysClockToHSI(void);
void SetSysClockToHSE(void);
void SetSysClockToPLL(uint32_t freq, uint8_t src);
void CLKCTRL_init();
//void RCC_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* CLKCTRL_H_INCLUDED */