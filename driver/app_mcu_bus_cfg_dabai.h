#ifndef _APP_MCU_BUS_CFG_DABAI_H_
#define _APP_MCU_BUS_CFG_DABAI_H_


#ifdef __cplusplus
extern "C" {
#endif


#include "GMtypes.h"
#include "n32g43x.h"
#include "n32g43x_start_pins.h"

// ====================== configure ========================
// 配置：硬件触发线(MCU_IRQ_Status) (PC2)
#undef MCUBUS_TRIGGER_io_set_pull_off
#define MCUBUS_TRIGGER_io_set_pull_off()        io_set_pull_off_mode(GPIOB, 13)

#undef MCUBUS_TRIGGER_GPIO_Out
#define MCUBUS_TRIGGER_GPIO_Out()         io_set_dir_out(GPIOB, 13)

#undef MCUBUS_TRIGGER_GPIO_IN
#define MCUBUS_TRIGGER_GPIO_IN()          io_set_dir_in(GPIOB, 13)

#undef MCUBUS_TRIGGER_io_set_level_high
#define MCUBUS_TRIGGER_io_set_level_high()      io_set_high(GPIOB, GPIO_PIN_13)

#undef MCUBUS_TRIGGER_io_set_level_low
#define MCUBUS_TRIGGER_io_set_level_low()       io_set_low(GPIOB, GPIO_PIN_13)


/* 用于MCU IIC总线与SOC之间通信的辅助：
*  1.MCU端有紧急数据变化时，通过拉电平（xxms）进行通知SOC端。
*  2.XIAOBAI常态xxx电平
*  3.由于此GPIO与其他功能进行了复用，故需要初始化
*/
#undef MCUBUS_TRIGGER_SOC_ENABLE
#define MCUBUS_TRIGGER_SOC_ENABLE()             do{io_set_dir_out(GPIOB, 13); io_set_low(GPIOB, GPIO_PIN_13);}while(0)


#undef MCUBUS_TRIGGER_SOC_DISABLE
#define MCUBUS_TRIGGER_SOC_DISABLE()            do{io_set_dir_out(GPIOB, 13); io_set_high(GPIOB, GPIO_PIN_13);}while(0)




// ============================= IIC总线与SOC通信：功能使能配置 ============================
//寄存器配置：使能寄存器(1)；  不配置寄存器(0)
#undef CONF_EN_REG_START_MODE
#define CONF_EN_REG_START_MODE                  (1)         //(r)寄存器命令：从mcu发过来的同步起始模式，投影，升级，音响

#undef CONF_EN_REG_SYNC_SOC_STATUS
#define CONF_EN_REG_SYNC_SOC_STATUS             (1)         //(w)寄存器命令：发往MCU的同步状态的

#undef CONF_EN_REG_MCU_STATUS
#define CONF_EN_REG_MCU_STATUS                  (1)         //(r)寄存器命令：mcu设备状态

#undef CONF_EN_REG_FROM_SOC_CTRL_FAN
#define CONF_EN_REG_FROM_SOC_CTRL_FAN           (1)         //(w)寄存器命令：mcu控制寄存器

#undef CONF_EN_REG_LAMP_MODE
#define CONF_EN_REG_LAMP_MODE                   (1)         //(w)寄存器命令：灯光模式设置

#undef CONF_EN_REG_MCU_EVENT
#define CONF_EN_REG_MCU_EVENT                   (1)         //(r)寄存器命令：发往SOC MCU产生的事件

#undef CONF_EN_REG_SOC_FAN_STATUS
#define CONF_EN_REG_SOC_FAN_STATUS              (1)         //(r)寄存器配置宏：MCU控制的风扇状态信息

#undef CONF_EN_REG_FASTPOWERON
#define CONF_EN_REG_FASTPOWERON                 (1)         //(r)寄存器：快速开机

#undef CONF_EN_REG_CTRL_UPDATE
#define CONF_EN_REG_CTRL_UPDATE                 (1)         //(w)升级MCU程序命令




// 寄存器通道数
#undef  MCUBUS_NUMS_MCU_FAN_SPEED_CHANNL
#define MCUBUS_NUMS_MCU_FAN_SPEED_CHANNL        (0)         //风扇通道数

#undef  MCUBUS_NUMS_SOC_FAN_SPEED_CHANNL
#define MCUBUS_NUMS_SOC_FAN_SPEED_CHANNL        (1)         //风扇通道数



#ifdef __cplusplus
}
#endif


#endif
