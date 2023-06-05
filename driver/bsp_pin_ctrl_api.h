#ifndef _BSP_PIN_CTRL_API_H_
#define _BSP_PIN_CTRL_API_H_

#include "GMtypes.h"
#include "config.h"

// ========================= 接口 ==========================
// 注意：1、接口使用函数封装而不是用宏定义封装，是为了在编译时可进行参数检查
//      2、此处声明的接口函数且是static，为了在实现接口时是在.h中，这样就可内联，节省ROM空间。
//

// ------------------ 主机电源控制 ---------------------------
static void bsp_soc_power_api_init(void);
static void bsp_soc_power_api_set_close(void);
static void bsp_soc_power_api_set_open(void);


// -------------------- 唤醒pin控制 -------------------------
static void bsp_wakeup_soc_api_init(void);
static void bsp_wakeup_soc_api_open(void);
static void bsp_wakeup_soc_api_close(void);


// ---------------- 获取主机端待机状态信息 ---------------------
// 用于检测主机待机，一般在进入standby状态之后
//

static void bsp_check_soc_standby_api_init(void);
// FALSE-为待机；TRUE-工作
static BOOL bsp_check_soc_standby_api_get_status(void);
// 待机检测脚中断唤醒函数注册
static void bsp_check_soc_standby_api_ISR_register(void *handle);



// -------------------- 投影设备硬件控制 ----------------------
static void bsp_projector_on_api_init(void);
static void bsp_projector_on_api_high(void);
static void bsp_projector_on_api_low(void);

// ----------------------- GPIO ----------------------------
// 未使用GPIO初始化，在main运行的第一条语句
// 一般是设置为：为了低功耗，AVR FAE建议设置为输入上拉方式
static void bsp_pin_ctrl_api_unused_gpio_init(void);




#include "bsp_pin_ctrl_dabai.h"




#endif
