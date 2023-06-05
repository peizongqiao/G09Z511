/*
 * @Author: your name
 * @Date: 2022-03-09 16:37:03
 * @LastEditTime: 2022-03-09 16:51:23
 * @LastEditors: Please set LastEditors
 * @Description: ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \Attiny1616_3217_APP\Attiny1616_3217_APP\Drivers\BSP\pin_ctrl\bsp_pin_ctrl_sprite.h
 */
/*
* ģ������ :xxxxx
* �ļ����� : xxxx.h
* ˵    �� :
*/
#ifndef __BSP_SOC_POWER_DABAI_H__
#define __BSP_SOC_POWER_DABAI_H__

#include "GMtypes.h"
#include "n32g43x_start_pins.h"
#include "utils.h"

// ================ external fucntion ======================
// �ӿڷ�װ
// �˴���.h�ļ��ж���static�ĺ�����ʽ�ķ�װ��Ϊ������(inline)���Դﵽ��ʡROM�ռ�
//


// ----------------------- ��Դ  ---------------------------
static void bsp_soc_power_api_init(void)
{
    //�����ϵ��
    io_set_high(GPIOC, GPIO_PIN_3);
    io_set_dir_out(GPIOC, 3);
}
static void bsp_soc_power_api_set_close(void)
{
    io_set_low(GPIOC, GPIO_PIN_3);
    io_set_dir_out(GPIOC, 3);
}
static void bsp_soc_power_api_set_open(void)
{
    io_set_high(GPIOC, GPIO_PIN_3);
    io_set_dir_out(GPIOC, 3);
}


// ---------------------- ����pin���� -----------------------
static void bsp_wakeup_soc_api_init(void)
{
    io_set_dir_out(GPIOA, 4);
    io_set_high(GPIOA, GPIO_PIN_4);
}

static void bsp_wakeup_soc_api_open(void)
{
    io_set_low(GPIOA, GPIO_PIN_4);
}

static void bsp_wakeup_soc_api_close(void)
{
    io_set_high(GPIOA, GPIO_PIN_4);
}

// ------------------ �����������״̬ -----------------------
static void bsp_check_soc_standby_api_init(void)
{
    io_set_dir_in(GPIOA, 3);
    io_set_pull_off_mode(GPIOA, 3);
}

static BOOL bsp_check_soc_standby_api_get_status(void)
{
    BOOL ret = (0 != (io_get_level(GPIOA, 3)) ? TRUE : FALSE);
    return ret;
}

static void bsp_check_soc_standby_api_ISR_register(void *handle){}

// -------------------- ͶӰ�豸Ӳ������ ----------------------
static void bsp_projector_on_api_init(void){}
static void bsp_projector_on_api_high(void){}
static void bsp_projector_on_api_low(void){}
// ----------------------- δʹ��GPIO��ʼ�� ------------------
// ��ʼ��Ϊ����ģʽ���Ա���͹���
static void bsp_pin_ctrl_api_unused_gpio_init(void)
{

}



#endif
/***************************** (END OF FILE) *********************************/
