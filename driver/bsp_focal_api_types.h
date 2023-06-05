#ifndef BSP_FOCAL_API_TYPES_H_
#define BSP_FOCAL_API_TYPES_H_

#include "GMtypes.h"

typedef enum
{
    E_DIRECT_A  = 0,
    E_DIRECT_AB = 1,
    E_DIRECT_B  = 2,
    E_DIRECT_BC = 3,
    E_DIRECT_C  = 4,
    E_DIRECT_CD = 5,
    E_DIRECT_D  = 6,
    E_DIRECT_DA = 7,
}focal_run_direct_t;

typedef enum
{
    E_DIRECTION_STOP  = 0,
    E_DIRECTION_RUN 	= 1,
    E_DIRECTION_RET  	= 2,
}focal_direction_t;

#endif /* BSP_FOCAL_API_TYPES_H_ */