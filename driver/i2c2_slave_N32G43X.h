
#ifndef I2C2_SLAVE_N32G43X_H
#define I2C2_SLAVE_N32G43X_H
#include <n32g43x_start_pins.h>
#include "utils.h"
#include "GMtypes.h"
#include "bsp_i2c_slave_api_types.h"
#include "app_mcu_bus.h"

#ifdef __cplusplus
extern "C" {
#endif


// ============================ Configure ========================

// 注意：由于是使用的硬件I2C Slave设备
// SDA(PA1)
#define I2C_SLAVE_CFG_SDA_PORT              GPIOC
#define I2C_SLAVE_CFG_SDA_PIN               GPIO_PIN_1
#define I2C_SLAVE_CFG_SDA_PIN_NUM           1
//#define I2C_SLAVE_CFG_SDA_PORTMUX()         do{PORTMUX.CTRLB |= PORTMUX_TWI0_bm;}while(0)

// SCL(PA2)
#define I2C_SLAVE_CFG_SCL_PORT              GPIOC
#define I2C_SLAVE_CFG_SCL_PIN               GPIO_PIN_0
#define I2C_SLAVE_CFG_SCL_PIN_NUM           0
//#define I2C_SLAVE_CFG_SCL_PORTMUX()         do{PORTMUX.CTRLB |= PORTMUX_TWI0_bm;}while(0)

extern void HC595SendData(uint16_t SendVal);

static inline void I2C_SDA_set_pull_off_1(void)
{
    io_set_pull_off_mode(I2C_SLAVE_CFG_SDA_PORT, I2C_SLAVE_CFG_SDA_PIN_NUM);
}

static inline void I2C_SDA_set_pull_up_1(void)
{
    io_set_pull_up_mode(I2C_SLAVE_CFG_SDA_PORT, I2C_SLAVE_CFG_SDA_PIN_NUM);
}

static inline void I2C_SDA_set_dir_in_1(void)
{
    io_set_dir_in(I2C_SLAVE_CFG_SDA_PORT, I2C_SLAVE_CFG_SDA_PIN_NUM);
}


static inline void I2C_SDA_set_dir_out_1_1(void)
{
    io_set_dir_out(I2C_SLAVE_CFG_SDA_PORT, I2C_SLAVE_CFG_SDA_PIN_NUM);
}
void I2C_ResetBusy(I2C_Module* I2Cx);

///*
// * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
// *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
// *                PORT_ISC_RISING_gc        = Sense Rising Edge
// *                PORT_ISC_FALLING_gc       = Sense Falling Edge
// *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
// *                PORT_ISC_LEVEL_gc         = Sense low Level
// */
//static inline void I2C_SDA_set_isc(const PORT_ISC_t isc)
//{
//    io_set_isc(I2C_SLAVE_CFG_SDA_PORT, I2C_SLAVE_CFG_SDA_PIN, isc);
//}


/*
 * is inverted
 */
//static inline void I2C_SDA_set_enable_inverted(void)
//{
//    io_set_enable_inverted(I2C_SLAVE_CFG_SDA_PORT, I2C_SLAVE_CFG_SDA_PIN);
//}
//
//
//// is not inverted
//static inline void I2C_SDA_set_disable_inverted(void)
//{
//    io_set_disable_inverted(I2C_SLAVE_CFG_SDA_PORT, I2C_SLAVE_CFG_SDA_PIN);
//}



/**
 * \brief Set I2C_SDA level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void I2C_SDA_set_level_high_1(void)
{
    io_set_high(I2C_SLAVE_CFG_SDA_PORT, I2C_SLAVE_CFG_SDA_PIN);
}

static inline void I2C_SDA_set_level_low_1(void)
{
    io_set_low(I2C_SLAVE_CFG_SDA_PORT, I2C_SLAVE_CFG_SDA_PIN);
}


static inline void I2C_SCL_set_pull_off_1(void)
{
    io_set_pull_off_mode(I2C_SLAVE_CFG_SCL_PORT, I2C_SLAVE_CFG_SCL_PIN);
}

static inline void I2C_SCL_set_pull_up_1(void)
{
    io_set_pull_up_mode(I2C_SLAVE_CFG_SCL_PORT, I2C_SLAVE_CFG_SCL_PIN_NUM);
}

static inline void I2C_SCL_set_dir_in_1(void)
{
    io_set_dir_in(I2C_SLAVE_CFG_SCL_PORT, I2C_SLAVE_CFG_SCL_PIN_NUM);
}


static inline void I2C_SCL_set_dir_out_1(void)
{
    io_set_dir_out(I2C_SLAVE_CFG_SCL_PORT, I2C_SLAVE_CFG_SCL_PIN_NUM);
}



/*
 * \param[in] isc PORT_ISC_INTDISABLE_gc    = Iterrupt disabled but input buffer enabled
 *                PORT_ISC_BOTHEDGES_gc     = Sense Both Edges
 *                PORT_ISC_RISING_gc        = Sense Rising Edge
 *                PORT_ISC_FALLING_gc       = Sense Falling Edge
 *                PORT_ISC_INPUT_DISABLE_gc = Digital Input Buffer disabled
 *                PORT_ISC_LEVEL_gc         = Sense low Level
 */
//static inline void I2C_SCL_set_isc(const PORT_ISC_t isc)
//{
//    io_set_isc(I2C_SLAVE_CFG_SCL_PORT, I2C_SLAVE_CFG_SCL_PIN, isc);
//}


/*
 * is inverted
 */
//static inline void I2C_SCL_set_enable_inverted(void)
//{
//    io_set_enable_inverted(I2C_SLAVE_CFG_SCL_PORT, I2C_SLAVE_CFG_SCL_PIN);
//}


//// is not inverted
//static inline void I2C_SCL_set_disable_inverted(void)
//{
//    io_set_disable_inverted(I2C_SLAVE_CFG_SCL_PORT, I2C_SLAVE_CFG_SCL_PIN);
//}


/**
 * \brief Set I2C_SCL level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void I2C_SCL_set_level_high_1(void)
{
    io_set_high(I2C_SLAVE_CFG_SCL_PORT, I2C_SLAVE_CFG_SCL_PIN);
}

static inline void I2C_SCL_set_level_low_1(void)
{
    io_set_low(I2C_SLAVE_CFG_SCL_PORT, I2C_SLAVE_CFG_SCL_PIN);
}




// ====================== declare ==========================

// Bus Error Event Interrupt Handlers
extern void (*I2C_0_bus_error_interrupt_handler)(void);
// Bus Collision Event Interrupt Handlers
extern void (*I2C_0_collision_interrupt_handler)(void);
// Stop Event Interrupt Handlers
extern void (*I2C_0_stop_interrupt_handler)(void);
// Read Event Interrupt Handlers
extern void (*I2C_0_read_1_1_interrupt_handler)(void);
// Write Event Interrupt Handlers
extern void (*I2C_0_write_1_interrupt_handler)(void);
// Address Event Interrupt Handlersstatic
extern void (*I2C_0_address_interrupt_handler)(void);

void I2C2_EV_IRQHandler(void);
void I2C2_ER_IRQHandler(void);

void I2C2_GPIO_init_1(void);
void I2C2_init_1(uint8_t address);

// 注意：
// 1、此处使用原在.C文件中定义的函数。
// 2、在.h中定义的static函数，为了编译器产生内联(inline)，以达到节省ROM空间的目的。
// 3、不使用#define宏定义，而使用函数的形式时为了：inline可以达到在编译时候进行参数检查的目的，增加安全性。
/**
 * \brief Open the I2C for communication. Enables the module if disabled.
 *
 * \return Nothing
 */
static void I2C_0_open_1(void)
{
    I2C_Enable(I2C2, ENABLE);
}

///**
// * \brief Close the I2C for communication. Disables the module if enabled.
// *
// * \return Nothing
// */
//static void I2C_0_close_1(void)
//{
//    I2C_Enable(I2C2, DISABLE);
//}

///**
// * \brief Read one byte from the data register of I2C_0
// *
// * Function will not block if a character is not available, so should
// * only be called when data is available.
// *
// * \return Data read from the I2C_0 module
// */
//static uint8_t I2C_0_read_1_1(void)
//{
//    return I2C_RecvData(I2C2);
//}

///**
// * \brief Write one byte to the data register of I2C_0
// *
// * Function will not block if data cannot be safely accepted, so should
// * only be called when safe, i.e. in the read callback handler.
// *
// * \param[in] data The character to write to the I2C
// *
// * \return Nothing
// */
//static void I2C_0_write_1(uint8_t data)
//{
//    I2C_SendData(I2C2, data);
//}

///**
// * \brief Send ACK to received address or data. Should
// * only be called when appropriate, i.e. in the callback handlers.
// *
// * \return Nothing
// */
//static void I2C_0_send_ack_1(void)
//{
//    I2C_ConfigAck(I2C2, ENABLE);
//}

///**
// * \brief Send NACK to received address or data. Should
// * only be called when appropriate, i.e. in the callback handlers.
// *
// * \return Nothing
// */
//static void I2C_0_send_nack_1(void)
//{
//    I2C_ConfigAck(I2C2, DISABLE);
//}

///**
// * \brief Goto unaddressed state. Used to reset I2C HW that are aware
// * of bus state to an unaddressed state.
// *
// * \return Nothing
// */
////static void I2C_0_goto_unaddressed(void)
////{
////    // Reset module
////    TWI0.SSTATUS |= (TWI_DIF_bm | TWI_APIF_bm);
////    TWI0.SCTRLB = TWI_SCMD_COMPTRANS_gc;
////}

///**
// * \brief Callback handler for event where master wishes to read a byte from slave.
// *
// * \return Nothing
// */
//static void I2C_0_set_read_callback_1(i2c_slave_callback_t handler)
//{
//    I2C_0_read_1_1_interrupt_handler = handler;
//}


///**
// * \brief Callback handler for event where master wishes to write a byte to slave.
// *
// * \return Nothing
// */
//static void I2C_0_set_write_callback_1(i2c_slave_callback_t handler)
//{
//    I2C_0_write_1_interrupt_handler = handler;
//}

///**
// * \brief Callback handler for event where slave has received its address.
// *
// * \return Nothing
// */
//static void I2C_0_set_address_callback_1(i2c_slave_callback_t handler)
//{
//    I2C_0_address_interrupt_handler = handler;
//}

///**
// * \brief Callback handler for event where slave has received a STOP condition after being addressed.
// *
// * \return Nothing
// */
//static void I2C_0_bus_error_callback_1(i2c_slave_callback_t handler)
//{
//    I2C_0_stop_interrupt_handler = handler;
//}

///**
// * \brief Callback handler for event where slave detects a bus collision.
// *
// * \return Nothing
// */
//static void I2C_0_set_collision_callback_1_1(i2c_slave_callback_t handler)
//{
//    I2C_0_collision_interrupt_handler = handler;
//}


///**
// * \brief Callback handler for event where slave detects a bus error.
// *
// * \return Nothing
// */
//static void I2C_0_set_bus_error_callback_1(i2c_slave_callback_t handler)
//{
//    I2C_0_bus_error_interrupt_handler = handler;
//}

//// Read Event Interrupt Handlers
//static void I2C_0_read_1_1_callback(void)
//{
//    if (I2C_0_read_1_1_interrupt_handler) {
//        I2C_0_read_1_1_interrupt_handler();
//    }
//}

//// Write Event Interrupt Handlers
//static void I2C_0_write_1_callback(void)
//{
//    if (I2C_0_write_1_interrupt_handler) {
//        I2C_0_write_1_interrupt_handler();
//    }
//}

//// Address Event Interrupt Handlers
//static void I2C_0_address_callback_1(void)
//{
//    if (I2C_0_address_interrupt_handler) {
//        I2C_0_address_interrupt_handler();
//    }
//}

//// Stop Event Interrupt Handlers
//static void I2C_0_stop_callback_1(void)
//{
//    if (I2C_0_stop_interrupt_handler) {
//        I2C_0_stop_interrupt_handler();
//    }
//}

//// Bus Collision Event Interrupt Handlers
//static void I2C_0_collision_callback_1(void)
//{
//    if (I2C_0_collision_interrupt_handler) {
//        I2C_0_collision_interrupt_handler();
//    }
//}

//// Bus Error Event Interrupt Handlers
//static void I2C_0_bus_error_callback_1(void)
//{
//    if (I2C_0_bus_error_interrupt_handler) {
//        I2C_0_bus_error_interrupt_handler();
//    }
//}



// ======================== 实现接口 =========================
// 接口封装
// 此处在.h文件中定义static的函数形式的封装是为了内联(inline)，以达到节省ROM空间
//

// i2c硬件初始化(如：io，中断等设置，硬件设置地址等)
static void bsp_i2c_slave_api_init_1(uint8_t address)
{
    I2C2_init_1(address);
}

//// 让i2c设备处于低功耗状态(如：关闭设备，pins IO处于低功耗模式等)
//static void bsp_i2c_slave_api_low_pwr_init_1(void)
//{
//    //__nop__();
//}
static void bsp_i2c2_slave_api_open(void)
{
    I2C_0_open_1();
}
//static void bsp_i2c_slave_api_close_1(void)
//{
//    I2C_0_close_1();
//}
//static uint8_t bsp_i2c_slave_api_read_1(void)
//{
//    return I2C_0_read_1_1();
//}
//static void bsp_i2c_slave_api_write_1(uint8_t data)
//{
//    I2C_0_write_1(data);
//}
//static void bsp_i2c_slave_api_send_ack_1(void)
//{
//    I2C_0_send_ack_1();
//}
//static void bsp_i2c_slave_api_send_nack_1(void)
//{
//    I2C_0_send_nack_1();
//}
//static void bsp_i2c_slave_api_goto_unaddressed_1(void)
//{
//    I2C_0_goto_unaddressed_1();
//}
//static void bsp_i2c_slave_api_set_read_callback_1(i2c_slave_callback_t handler)
//{
//    I2C_0_set_read_callback_1(handler);
//}
//static void bsp_i2c_slave_api_set_write_callback_1(i2c_slave_callback_t handler)
//{
//    I2C_0_set_write_callback_1(handler);
//}
//// i2c host传输了设备硬件地址
//static void bsp_i2c_slave_api_set_address_callback_1(i2c_slave_callback_t handler)
//{
//    I2C_0_set_address_callback_1(handler);
//}
//static void bsp_i2c_slave_api_set_stop_callback_1(i2c_slave_callback_t handler)
//{
//    I2C_0_bus_error_callback_1(handler);
//}
//static void bsp_i2c_slave_api_set_collision_callback_1(i2c_slave_callback_t handler)
//{
//    I2C_0_set_collision_callback_1(handler);
//}
//static void bsp_i2c_slave_api_set_bus_error_callback(i2c_slave_callback_t handler)
//{
//    I2C_0_set_bus_error_callback(handler);
//}
void msg_dispatch_poll_2(void);

#ifdef __cplusplus
}
#endif

#endif /* I2C_SLAVE_H */
