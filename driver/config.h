#ifndef _CONFIG_H_
#define _CONFIG_H_

//----------------------------------------------------------
//  CFG_PROJECT_ITEMS 取值
//  1--dabai项目
//  2--年糕2项目
//----------------------------------------------------------
// 根据上表!!修改!!
#define CFG_PROJECT_ITEMS                    (1)

// ============ 默认configure(本文件内禁止修改) ============

// 系统位数(8/16/32)
#define CFG_MCU_BIT_SYS                      (8)

// MCU多字节数据大小端（big-endin/little-endin）
// （0-小端；1-大端）
#define CFG_MCU_BIG_LITTLE_ENDIN             (0)

// 系统主频时钟频率(units: xxMHz)，更改时：需要结合硬件进行(AVR MCU)评估
#define CFG_MCU_CLK_MHZ                      (108u)

// ASSERT使用是否使用（0-不使用；1-使用）
#define CFG_ASSERT_IS_USE                    (0)

// 日志调试(printf)是否启用（0-不使用；1-使用）
#define CFG_LOG_IS_USE                       (0)

// 看门狗是否开启（0-不使用；1-使用）
#define CFG_WATCHDOG_IS_USE                  (1)

// 软件定时器数量值(1u~xxu)
#define CFG_SOFTTIMER_NUMS                   (15u)


// RTC硬件是否使用（0-不使用；1-使用）
#define CFG_RTC_IS_USE                       (0)

// qtouch是否使用（0-不使用；1-使用）
#define CFG_QTOUCH_IS_USE                    (0)

// 按键是否使用（0-不使用；1-使用）
#define CFG_KEY_IS_USE                       (0)

// 电池（0-电池不支持；1-bq2570x采集；2-ADC采集；3-电量计bq4050）
#define CFG_BAT_VOLTAGE_WAY                  (1)

// 适配器 （0-不支持；1-typeC；2-普通pin）
#define CFG_ADAPTER_WAY                      (1)

// TYPE-C器件地址长度 （0-8位；1-16位）
#define CFG_TYPE_C_ADDS                      (1)

// 低功耗睡眠功能是否使用（0-不使用；1-使用）
#define CFG_LOW_PWR_SLEEP_IS_USE             (1)

// TCA0硬件定时器PWM功能使用（0-不使用；1-使用）
// 注：一般不做修改
#define CFG_TCA0_PWM_IS_USE                  (1)

// TCB0硬件定时器功能使用（0-不使用；1-使用）
// 定时器默认是作为：软件定时器、系统调度、系统运行时间、延迟任务等
// 注：一般不做修改
#define CFG_TCB0_TIMER_USE                   (1)

// i2c slave设备使用
// 0-不使用
// 1-MCU 硬件i2c
// 注：一般不做修改
#define CFG_BSP_I2C_SLAVE_DEVICE             (1)

// 灯光(led)是否使用
// 0-不使用；
// 1-使用单色灯；
// 2-使用三色灯(单GPIO，使用私有单线协议)；
// 3-三色灯(三GPIO)；
#define CFG_LAMP_CTRL_IS_USE                 (0)

// 舱门功能是否使用
// 0-不使用
// 1-使用异步控制
// 2-使用阻塞控制（注意：阻塞控制限制很大，只有在对舱门控制时序要求极高时才选择此项）
#define CFG_DOOR_CTRL_IS_USE                 (0)

// 风扇功能是否使用（0-不使用；1-使能）
#define CFG_FAN_IS_USE                       (0)

// ADC类型（0-不使用；1-ADC0；2-ADC1；3-both）
#define CFG_ADC_IS_USE                       (0)

// 温度传感器是否使用（0-不使用；1-使用）
#define CFG_TEMPERATURE_SENSOR_IS_USE        (0)

// 单PIN总线协议是否使用（0-不使用；1-使用）
#define CFG_PRIVATE_PROTOCOL_IS_USE          (0)

// TCD0硬件定时器PWM功能使用（0-不使用；1-使用）
// 注：一般不做修改
#define CFG_TCD0_PWM_IS_USE                  (0)

// 霍尔传感器开关功能使用（0-不使用；1-使用）
// 注：一般不做修改
#define CFG_HALL_SWITCH_IS_USE               (0)

// =============== 包含不同项目的修改(可修改) ==============
#ifndef CFG_PROJECT_ITEMS
    #error "CFG_PROJECT_ITEMS" undefined!
#endif

//#if (CFG_PROJECT_ITEMS == 1)
//    #include "config_dabai.h"
//    #pragma message("global configure use dabai")
//#elif (CFG_PROJECT_ITEMS == 2)
//    #include "config_niangao2.h"
//    #pragma message("global configure use niangao2")
//#else
//    #pragma message("global configure use default")
//#endif

// ====================== 宏配置参数检查 ======================
// 检查宏配置参数：
#if (CFG_MCU_BIT_SYS != 8) && (CFG_MCU_BIT_SYS != 16) && (CFG_MCU_BIT_SYS != 32)
    #error configure macro "CFG_MCU_BIT_SYS"!
#endif

// MCU主时钟频率(units:Hz)
#define MCU_CLK_HZ                            ((CFG_MCU_CLK_MHZ)*1000000ul)     // xxMHz






#endif // CONFIG_H
