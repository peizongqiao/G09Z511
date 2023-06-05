#ifndef _APP_MCU_BUS_H_
#define _APP_MCU_BUS_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "GMtypes.h"
//#include "app_door_ctrl.h"
//#include "app_fan_ctrl.h"
#include "config.h"
#include "app_mcu_bus_cfg.h"
#include "n32g43x.h"


// IIC总线硬件读写地址
#define MCUBUS_DEV_WR_ADDR                  (MCUBUS_I2C_SLAVE_CFG_HARD_ADDR | I2C_WR)      //器件写地址
#define MCUBUS_DEV_RD_ADDR                  (MCUBUS_I2C_SLAVE_CFG_HARD_ADDR | I2C_RD)      //器件读地址



// ================== 通信协议：寄存器定义 =====================
//寄存器地址((读r/写w)以主机SOC端角度进行描述)
#define MCUBUS_REG_TOUCH_PARA               (0X10)      //(r)寄存器命令：qtouch参数
#define MCUBUS_REG_BATTERY_TEMP             (0X11)      //(r)寄存器命令：电池温度
#define MCUBUS_REG_BATTERY_STATUS           (0X12)      //(r)寄存器命令：电池设备故障状态
#define MCUBUS_REG_SOC_BATTERY_PERCENT      (0x13)      //(w)寄存器命令：发往MCU电量百分比值
#define MCUBUS_REG_START_MODE               (0x14)      //(r)寄存器命令：从mcu发过来的同步起始模式，投影，升级，音响
#define MCUBUS_REG_SYNC_SOC_STATUS          (0x15)      //(w)寄存器命令：发往MCU的同步状态的
#define MCUBUS_REG_CHKSUM                   (0x16)      //(r/w)寄存器命令：校验和
#define MCUBUS_REG_MCU_STATUS               (0x17)      //(r)寄存器命令：mcu设备状态
#define MCUBUS_REG_CTRL_MCU_OLD             (0x18)      //(w)寄存器命令：mcu旧控制寄存器(如：舱门/风扇，新MCU框架下此寄存器无作用，此寄存器用于控制老项目的风扇、舱门，SOC由于共代码，，故将此寄存器留空)
#define MCUBUS_REG_MCU_APP_SV               (0x19)      //(r)寄存器命令：mcu APP版本号
#define MCUBUS_REG_LAMP_MODE                (0x1A)      //(w)寄存器命令：灯光模式设置
#define MCUBUS_REG_MCU_EVENT                (0x1B)      //(r)寄存器命令：发往SOC MCU产生的事件
#define MCUBUS_REG_VOLTAMETER               (0x1D)      //(r)寄存器命令：电量信息
#define MCUBUS_REG_TEMP                     (0x1E)      //(r)寄存器命令：环温(单位:1℃)
#define MCUBUS_REG_SOC_FAN                  (0x1F)      //(r)寄存器命令：SOC控制转动的风扇状态信息
#define MCUBUS_REG_MCU_FAN                  (0x20)      //(r)寄存器命令：MCU控制转动的风扇状态信息

#define MCUBUS_DATE                         (0x21)      //(r)寄存器命令：MCU控制转动的风扇状态信息



#define MCUBUS_REG_VOLUME_CTL               (0x24)      //(w)寄存器命令：音量大小设置
#define MCUBUS_REG_TRAVEL_MODE              (0x26)      //(w)寄存器命令：旅行模式标志
#define MCUBUS_REG_CTRL_MCU_FAN             (0x27)      //(w)寄存器命令：mcu控制寄存器(控制风扇)
#define MCUBUS_REG_FASTPOWERON              (0x28)      //(r)mcu快速开机模式
#define MCUBUS_REG_CTRL_MCU_DOOR            (0X29)      //(w)寄存器命令：mcu控制寄存器(舱门动作)

#define MCUBUS_REG_MCU_BOOTLOADER_SV        (0x32)      //(r)寄存器命令：MCU bootloader版本
#define MCUBUS_REG_SOC_EEPROM_SAVE_ADDR_START (0x33)    //(r/w)寄存器命令：SOC存储EEPROM数据的开始地址。
#define MCUBUS_REG_SOC_EEPROM_SAVE_ADDR_END (MCUBUS_REG_SOC_EEPROM_SAVE_ADDR_START+(64-1)) //寄存器命令：SOC存储EEPROM数据的结束地址。


#define MCUBUS_REG_CTRL_UPDATE              (0xF1)      //(w)升级MCU程序命令

#define MCUBUS_REG_NULL                     (0xFF)      //(soc视角)寄存器命令：空命令




// ========================== 0x10 ==========================
//协议数据内容：qtouc参数
typedef struct
{
    uint16_t reference;
    uint16_t delta;
} protocol_touch_para_t;



// ========================= 0x14 ==========================
// 协议数据类型：mcu向SOC同步状态信息
typedef enum {
    E_FLAG_PROJECTION_MODE = 0,                 //投影模式
    E_FLAG_SOUND_MODE,                          //音响模式
    E_FLAG_UPDATE_MODE,                         //升级模式
    E_FLAG_NFC_MODE,                            //NFC开机模式
    E_FLAG_NULL,                                //NULL
    E_FLAG_TRAVEL_MODE                          //旅行模式
} protocol_soc_start_mode_t;



// ========================= 0x15 ==========================
// 协议数据类型：SOC状态信息
typedef enum
{
    E_SOC_STATE_NONE        = 0,                //soc不会发送该信号
    E_SOC_STATE_STANDBY     = 2,                //soc待机前发送待机信号
    E_SOC_STATE_BOOT        = 3,                //soc正在启动
    E_SOC_STATE_PROJECTOR   = 4,                //soc首次进入主界面时发送的信号
    E_SOC_STATE_SPEAKER     = 5,                //soc首次进音响模式后发送的信号
    E_SOC_STATE_SOC_UPDATE  = 6,                //soc检查到升级文件，进入SOC升级流程前发送的信号
    E_SOC_STATE_WORK        = 7,                //工作模式
#if 0
    E_SOC_STATE_BTCONNECT_SUCCESS,
    E_SOC_STATE_BTCONNECT_FAIL,
    E_SOC_STATE_MUSICPAUSE,
    E_SOC_STATE_MUSICPLAY,
#endif
}protocol_soc_status_t;



// ========================= 0x17 ==========================
// 协议数据类型:MCU端状态寄存器
typedef struct
{
    uint8_t eeprom_is_ready:1;                  // eeprom是否准备就绪可读写（1-就绪；0-未就绪）
    uint8_t reserve1:7;                         // 保留
}protocol_mcu_status_t;

// =========================== 0x18 ========================
// 舱门动作
typedef enum
{
    ENUM_MSTATE_FRONT = 0,
    ENUM_MSTATE_BACK,
    ENUM_MSTATE_STOP,
    ENUM_MSTATE_HWTEST,
    ENUM_MSTATE_ACK,
    ENUM_MSTATE_FRONT_TEST = 5,
    ENUM_MSTATE_BACK_TEST = 6,
    ENUM_MSTATE_NULL,
}protocol_door_action_t;

#pragma pack(1)
typedef struct
{
    uint8_t action;
    uint8_t speed;
}protocol_ctrl_mcu_door_t;
#pragma pack()
// ========================= 0x1E ==========================
// 协议数据类型:温度
#pragma pack(1)
typedef struct
{
    int8_t laser;       // 系统温度(B灯)
    int8_t env;         // 环境温度
    int8_t dmd;         // DMD温度
    int8_t cw;          // 色轮温度
    int8_t G_led;       // G灯
    int8_t R_led;       // R灯
    int8_t BP_led;      // BP灯
    int8_t board;       // 驱动板
}protocol_temperature_status_t;
#pragma pack()


// ========================= 0x1F ==========================
// 协议数据类型：风扇相关
// 转速单位：（转/分，r/min）s->m
// 注意：在协议上需要注明大小端
#pragma pack(1)
typedef struct
{
    uint16_t speed;                             // 风扇转速(units:r/min)
}protocol_fan_status_t;
#pragma pack()



// ========================== 0x1D =========================
// 协议数据类型：电池相关数据
// 注意：在协议上需要注明大小端
#pragma pack(1)
typedef struct
{
    struct
    {
        uint8_t standbyIsCharged:1;         // standby模式下，是否充过电（bool类型）
        uint8_t reserve1:7;                 // 保留
    };
    uint8_t reserve;                        // 保留
    uint16_t voltage_mv;                    // 电池电压，mv（按照little-endin传输）
    uint8_t percent;                        // 电池电量百分比
}protocol_voltameter_t;
#pragma pack()

// ========================== 0x12 =========================
// 电量计状态
typedef enum
{
    E_BAT_DEV_STATUS_NORMAL     = 0x55,
    E_BAT_DEV_STATUS_FAULT      = 0x50
}protocol_battery_status_t;




// ========================== 0x1B =========================
// 协议数据类型：舱门状态
typedef enum
{
    E_PROTO_DOOR_STATE_OPEN          = 0xF0, // 打开的
    E_PROTO_DOOR_STATE_CLOSE         = 0xE0, // 关闭的
    E_PROTO_DOOR_STATE_CHECK_OK      = 0xD0, // 自检成功
    E_PROTO_DOOR_STATE_CHECK_FAIL    = 0xC0  // 自检失败
}protocol_door_state_t;



// 协议数据类型：按键事件消息类型
typedef enum
{
    E_KEY_MSG_NULL       = 0x00,
    E_KEY_MSG_PLUS       = 0x01,         //SOC 信号：音量加
    E_KEY_MSG_MINUS      = 0x02,         //SOC 信号：音量减
    E_KEY_MSG_PLAY       = 0x04,         //SOC 信号：播放暂停
    E_KEY_MSG_NEXT       = 0x08,         //SOC 信号：媒体下一曲
    E_KEY_MSG_POWER      = 0x10,         //SOC 信号：mcu电源
    E_KEY_MSG_NEAR       = 0x0C,         //SOC 信号：接近感应按下
    E_KEY_MSG_LEAVE      = 0x0D,         //SOC 信号：接近感应释放
    E_KEY_MSG_PRESS      = 0X12,         //SOC 信号：pwr按下 ATV便携机用于关机
    E_KEY_MSG_RELASE     = 0X13,         //SOC 信号：pwr释放
    E_KEY_MSG_AUDIO      = 0x20,          //SOC 信号：音响模式
}protocol_key_msg_t;


// 协议数据类型：typeC的状态字
typedef enum
{
    E_PROTO_ADAPTER_INVALID  = 0x00,        //数据不可靠
    E_PROTO_ADAPTER_INSERT   = 0x01,        //插入一瞬间
    E_PROTO_ADAPTER_REMOVE   = 0x02,        //拔出一瞬间
    E_PROTO_ADAPTER_HIGH     = 0x04,        //高电平状态长时间持续
    E_PROTO_ADAPTER_LOW      = 0x08,        //低电平状态长时间持续
}protocol_adapter_status_t;



// 协议数据类型：按键事件，由从机soc实时更新，soc从mcu读取
// 注意：enum枚举类型，可能由于编译器不同占用字节数不用
#pragma pack(1)
typedef struct
{
    struct {
        protocol_key_msg_t key_event;                       // 按键事件
        protocol_door_state_t door_state;                   // 舱门事件
    }event;

    protocol_adapter_status_t adapter_plug_status;      // 适配器状态
}protocol_mcu_event_t;
#pragma pack()

// =========================== 0x27 ========================
// 协议数据类型：控制mcu寄存器
#pragma pack(1)
typedef struct
{
    protocol_door_action_t unused;           // 历史原因，之前由于舱门与风扇共用控制寄存器，导致首字节被舱门控制占用
    #pragma pack(1)
    struct
    {
        uint8_t mode;                             // 控制模式（1-主机曲线风控逻辑；0-MCU曲线风控逻辑）
        uint8_t speed[MCUBUS_NUMS_FAN_SET_CTRL_CHANNL];
    }fan;
    #pragma pack()
}protocol_ctrl_mcu_fan_t;
#pragma pack()



// ========================== 0xF1 =========================
// 协议数据类型：升级格式
#pragma pack(1)
typedef struct
{
    uint8_t start;
    uint8_t len;
    uint8_t reserve;
    uint8_t end;
}protocol_update_frame_format_t;
#pragma pack()






// ================== external function ====================
void mcubus_init(void);
void mcubus_i2c_low_pwr_init(void);
void mcubus_i2c_init(void);
void mcubus_i2c_addr_match_ISR_register(void *cb);
void mcubus_check_bus_timeout(void);
void mcubus_trigger_soc(void);
// 用于解除触发
static void mcubus_untrigger_soc(void)
{
    MCUBUS_TRIGGER_SOC_DISABLE();
}


void mcubus_update_regarea_start_mode(protocol_soc_start_mode_t start_mode);
void mcubus_update_regarea_sv(const char *version);
void mcubus_update_regarea_bootloader_sv(void);
//void mcubus_update_regarea_mcu_fan(measure_t *pdata);
//void mcubus_update_regarea_soc_fan(measure_t *pdata);
void mcubus_update_regarea_voltameter_mv(uint16_t mv);
void mcubus_update_regarea_keyevent_motor(void *pdata);
void mcubus_update_regarea_adapter_plug_status(protocol_adapter_status_t status);
//void mcubus_update_regarea_door(door_state_t state);
void mcubus_update_regarea_key_package(uint8_t idx, uint8_t event);
void mcubus_update_regarea_battery_temputer(uint8_t bat_temp);
void mcubus_update_regarea_battery_status(protocol_battery_status_t bat_status);
void mcubus_update_regarea_eeprom_status(BOOL status);
void mcubus_update_regarea_voltameter_percentage(uint8_t voltameter_percentage);
void mcubus_update_regarea_touch_para(void);
void mcubus_update_regarea_temperature(uint8_t *p_temperature);
void mcubus_update_regarea_fast_poweron(BOOL is_fast_poweron);


#ifdef __cplusplus
}
#endif


#endif
