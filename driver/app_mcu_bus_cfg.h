/*
* 模块名称 : mcu_bus IIC总线通信 参数配置（默认）
* 文件名称 : xxxx.h
* 说     明 :
*/
#ifndef _APP_MCU_BUS_CFG_H_
#define _APP_MCU_BUS_CFG_H_


#ifdef __cplusplus
extern "C" {
#endif


#include "GMtypes.h"
#include "config.h"



// ============== configure(本文件内禁止修改) ==============
// 配置：I2C slave设备硬件地址
#define MCUBUS_I2C_SLAVE_CFG_HARD_ADDR          0x82u
#define MCUBUS_I2C_SLAVE         0x02u


// 配置：硬件触发线(MCU_IRQ_Status)
#define MCUBUS_TRIGGER_io_set_pull_off()        io_set_pull_off_mode(GPIOB, 13)
#define MCUBUS_TRIGGER_GPIO_Out()         io_set_dir_out(GPIOB, 13)
#define MCUBUS_TRIGGER_GPIO_IN()          io_set_dir_in(GPIOB, 13)
#define MCUBUS_TRIGGER_io_set_level_high()      io_set_high(GPIOB, GPIO_PIN_13)
#define MCUBUS_TRIGGER_io_set_level_low()       io_set_low(GPIOB, GPIO_PIN_13)


// 用于MCU IIC总线与SOC之间通信的辅助：
// 2.MCU端有紧急数据变化时，通过拉电平（xxms）进行通知SOC端。
#define MCUBUS_TRIGGER_SOC_ENABLE()             io_set_high(GPIOB, GPIO_PIN_13)
#define MCUBUS_TRIGGER_SOC_DISABLE()            io_set_low(GPIOB, GPIO_PIN_13)



// ========== 寄存器功能使能(本文件内禁止修改) =============

//寄存器地址读r/写w以主机SOC端角度进行描述。
//寄存器配置：使能寄存器(1)；  不使能寄存器(0)
#define CONF_EN_REG_TOUCH_PARAM                 (1)         //(r)寄存器命令：qtouch参数
#define CONF_EN_REG_BATTERY_TEMP                (0)         //(r)寄存器命令：电池温度
#define CONF_EN_REG_BATTERY_STATUS              (0)         //(r)寄存器命令：电池设备故障状态
#define CONF_EN_REG_SOC_BATTERY_PERCENT         (0)         //(w)寄存器命令：发往MCU电量百分比值
#define CONF_EN_REG_START_MODE                  (0)         //(r)寄存器命令：从mcu发过来的同步起始模式，投影，升级，音响
#define CONF_EN_REG_SYNC_SOC_STATUS             (0)         //(w)寄存器命令：发往MCU的同步状态的
#define CONF_EN_REG_CHKSUM                      (1)         //(r/w)寄存器命令：校验和
#define CONF_EN_REG_MCU_STATUS                  (0)         //(r)寄存器命令：mcu设备状态
#define CONF_EN_REG_FROM_SOC_CTRL_DOOR          (0)         //(w)寄存器命令：mcu控制寄存器（共用同一寄存器）
#define CONF_EN_REG_FROM_SOC_CTRL_FAN           (0)         //(w)寄存器命令：mcu控制寄存器（共用同一寄存器）
#define CONF_EN_REG_MCU_APP_SV                  (1)         //(r)寄存器命令：mcu APP版本号
#define CONF_EN_REG_LAMP_MODE                   (0)         //(w)寄存器命令：灯光模式设置
#define CONF_EN_REG_MCU_EVENT                   (0)         //(r)寄存器命令：发往SOC MCU产生的事件
#define CONF_EN_REG_VOLTAMETER                  (0)         //(r)寄存器命令：电量信息
#define CONF_EN_REG_TEMP                        (1)         //(r)寄存器配置宏：温度信息
#define CONF_EN_REG_SOC_FAN_STATUS              (0)         //(r)寄存器配置宏：SOC控制的风扇信息
#define CONF_EN_REG_MCU_FAN_STATUS              (0)         //(r)寄存器配置宏：MCU控制的风扇信息

#define CONF_EN_REG_TRAVEL_MODE                 (0)         //(w)寄存器命令：旅行模式标志
#define CONF_EN_REG_FASTPOWERON                 (0)         //(r)寄存器：快速开机
#define CONF_EN_REG_MCU_BOOTLOADER_SV           (0)         //(r)寄存器命令：MCU bootloader版本

#define CONF_EN_REG_CTRL_UPDATE                 (1)         //(w)升级MCU程序命令
#define CONF_EN_REG_SOC_EEPROM_SAVE             (0)         //(r/w)寄存器命令：S是否是能，SOC发送EEPROM到MCU存储。

#define CONF_EN_REG_VOLUME_CTL                  (0)         //(w)寄存器命令：音量大小设置



// ========= 寄存器数据大小配置(本文件内禁止修改) ==========
#define MCUBUS_SIZES_MCU_APP_SV                 (8)         //MCU APP软件版本字节长度

#define MCUBUS_NUMS_TOUCH_CHANNEL               (3)         //qtouch参数表通道数

#define MCUBUS_NUMS_MCU_FAN_SPEED_CHANNL        (1)         //MCU控制的风扇状态通道数
#define MCUBUS_NUMS_SOC_FAN_SPEED_CHANNL        (1)         //SOC控制的风扇状态通道数

#define MCUBUS_NUMS_FAN_SET_CTRL_CHANNL         (5)         //风扇设置控制通道数

#define MCUBUS_SIZES_CHECKSUM                   (2)         //checksum字节数

#define MCUBUS_SIZES_SOC_EEPROM_CACHE           (16)        //SOC EEPROM存储cache字节大小




// ================== 包含不同项目的修改 ===================

#include "app_mcu_bus_cfg_dabai.h"

#ifdef __cplusplus
}
#endif


#endif