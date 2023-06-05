#ifndef _BSP_PIN_CTRL_API_H_
#define _BSP_PIN_CTRL_API_H_

#include "GMtypes.h"
#include "config.h"

// ========================= �ӿ� ==========================
// ע�⣺1���ӿ�ʹ�ú�����װ�������ú궨���װ����Ϊ���ڱ���ʱ�ɽ��в������
//      2���˴������Ľӿں�������static��Ϊ����ʵ�ֽӿ�ʱ����.h�У������Ϳ���������ʡROM�ռ䡣
//

// ------------------ ������Դ���� ---------------------------
static void bsp_soc_power_api_init(void);
static void bsp_soc_power_api_set_close(void);
static void bsp_soc_power_api_set_open(void);


// -------------------- ����pin���� -------------------------
static void bsp_wakeup_soc_api_init(void);
static void bsp_wakeup_soc_api_open(void);
static void bsp_wakeup_soc_api_close(void);


// ---------------- ��ȡ�����˴���״̬��Ϣ ---------------------
// ���ڼ������������һ���ڽ���standby״̬֮��
//

static void bsp_check_soc_standby_api_init(void);
// FALSE-Ϊ������TRUE-����
static BOOL bsp_check_soc_standby_api_get_status(void);
// ���������жϻ��Ѻ���ע��
static void bsp_check_soc_standby_api_ISR_register(void *handle);



// -------------------- ͶӰ�豸Ӳ������ ----------------------
static void bsp_projector_on_api_init(void);
static void bsp_projector_on_api_high(void);
static void bsp_projector_on_api_low(void);

// ----------------------- GPIO ----------------------------
// δʹ��GPIO��ʼ������main���еĵ�һ�����
// һ��������Ϊ��Ϊ�˵͹��ģ�AVR FAE��������Ϊ����������ʽ
static void bsp_pin_ctrl_api_unused_gpio_init(void);




#include "bsp_pin_ctrl_dabai.h"




#endif
