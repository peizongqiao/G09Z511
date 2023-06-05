#ifndef DRIVER_INIT_H_INCLUDED
#define DRIVER_INIT_H_INCLUDED


#ifdef __cplusplus
extern "C" {
#endif

//#include "bsp_i2c_host.h"
//#include "version.h"
#include "n32g43x.h"
#include <n32g43x_start_pins.h>

void system_init(void);

#ifdef __cplusplus
}
#endif

#endif /* DRIVER_INIT_H_INCLUDED */