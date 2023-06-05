/*
 * d3434.c
 *
 * Created: 2021.01.22
 * Author: mingjie.gu
 */
#include "dlp_manager.h"
#include "utils.h"
#include "stdio.h"

struct pic_def *pic_pos;


#include "stdint.h"


static const unsigned char  g_sCRCHI[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40
};
static const  unsigned char g_sCRCLO[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
    0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
    0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
    0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
    0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
    0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
    0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
    0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
    0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
    0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
    0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
    0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
    0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
    0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
    0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
    0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
    0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
    0x41, 0x81, 0x80, 0x40
};
/**
  * IchipsDataStorage CRCУ�����
  *
  * ע������:
  *
  *
  * �޶���|����|�޶�˵��
  * -----|----|-------
  * ������ | 2018-8-8 | ����
  **/


void LedInit_out1(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    /* Enable the GPIO Clock */
    if (GPIOx == GPIOA)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
    }
    else
    {
        if (GPIOx == GPIOD)
        {
            RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
        }
    }

    /* Configure the GPIO pin */
    if (Pin <= GPIO_PIN_ALL)
    {
        GPIO_InitStruct(&GPIO_InitStructure);
        GPIO_InitStructure.Pin          = Pin;
        GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
        GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
        GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_PP;
        GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
    }
}

uint16_t crcChecksum(uint8_t *data, uint16_t len)
{
    unsigned char ucCRCHi = 0xFF;
    unsigned char ucCRCLo = 0xFF;
    unsigned int iIndex;
    while (len--) {

        iIndex = ucCRCLo ^ *(data++);
        ucCRCLo = (unsigned char)(ucCRCHi ^ g_sCRCHI[iIndex]);
        ucCRCHi = g_sCRCLO[iIndex];
    }
    return (uint16_t)(ucCRCHi << 8 | ucCRCLo);
}

void pic_add(pic_handle handle)
{
 	struct pic_def *pic = malloc(sizeof(struct pic_def));
	pic->handle = handle;
	if (pic_pos) {
 		list_add_tail(&(pic->qset), &(pic_pos->qset));
	} else {
		pic_pos = pic;
		init_list_head(&(pic_pos->qset));
	}
}

//void pic_next()
//{
//	pic_pos = list_next_entry(pic_pos, qset);
//	pic_pos->handle();
//}

//void pic_prev()
//{
//	pic_pos = list_prev_entry(pic_pos, qset);
//	pic_pos->handle();
//}

//static uint32_t htonl(uint32_t value)
//{
	//return ((value & 0x000000FF) << 24) |  ((value & 0x0000FF00) << 8) |  ((value & 0x00FF0000) >> 8) | ((value & 0xFF000000) >> 24);
//}

struct trans_data {
	uint8_t sub_addr;
	uint32_t value;
};

#if defined(P3EM) || defined(P2NHD)
int8_t write_dlp(uint8_t sub_addr, uint32_t value)
{
	io_set_dir_out(SDA_PORT,SDA_PIN);
	io_set_dir_out(SCL_PORT,SCL_PIN);
	struct trans_data d;
	d.sub_addr = sub_addr;
	d.value = htonl(value);
	bool ret = i2c_write_block(0x36, sizeof(d), 0, &d);
	return ret;
}
#endif

#if defined(P23_720p) || defined(P23_540p) || defined(P33) || defined(P47)
int8_t write_dlp(uint8_t sub_addr,volatile uint8_t *value, uint8_t len)
{
	io_set_dir_out(SDA_PORT,SDA_PIN);
	io_set_dir_out(SCL_PORT,SCL_PIN);
	uint8_t d[13];
	d[0] = sub_addr;
	memcpy(&d[1], value, len);
	bool ret = i2c_write_block(0x36, len+1, 0, d);
	return ret;
}
#endif

#if defined (P3EM) ||  defined(P2NHD)
int8_t read_dlp(uint8_t sub_addr,uint8_t *data)
{
	int8_t ret = _SUCCESS;
	uint8_t d[2];
	d[0] = 0x15;
	d[1] = sub_addr;
	ret = i2c_write_block(0x36, sizeof(d), 0, d);
	if (ret != _SUCCESS) {
		return ret;
	}
	ret = i2c_read_block(0x37, 4, data);
	if (ret != _SUCCESS) {
		return ret;
	}
	*(uint32_t*)data = htonl(*(uint32_t*)data);
	return ret;
}

#endif

#if defined(P33) || defined(P47) || defined(P23_720p) || defined(P23_540p)
int8_t read_dlp(uint8_t sub_addr, uint8_t *param,
				uint8_t para_len,volatile uint8_t *data,
				uint8_t data_len)
{
	uint8_t ret;
	uint8_t d_len = sizeof(sub_addr) + para_len;
	uint8_t *d = malloc(d_len);
	d[0] = sub_addr;
	memcpy(d+sizeof(sub_addr), param, para_len);
	i2c_write_block(0x36, d_len, 0, d);
	__delay_ms(10);
	 //i2c_read_block(0x37, data_len, data);
    ret = i2c_read_block(0x37, data_len, data);
	free(d);
	return ret;
}
#endif

void set_rgbcurrent(uint16_t r, uint16_t g, uint16_t b)
{
	uint8_t d[6];
	
	memcpy(&d[0], &r, 2);
	memcpy(&d[2], &g, 2);
	memcpy(&d[4], &b, 2);
	safe_write(0x5c, d, 6); //max current
	safe_write(0x54, d, 6); //led current
}

#if defined(P47) || defined(P33) || defined(P23_720p) || defined(P23_540p)
static void dmd_training_check()
{
	uint8_t param[1];
	uint8_t data[11];
	bool err = false;

	for (uint8_t i=0; i<8; i++) {
		param[0] = i;
		read_dlp(0xdc, param, sizeof(param), data, sizeof(data));
		if (data[0] & BIT5) {
			err = true;
			break;
			} else {
			if ((data[3]&0x3f)-(data[2]&0x3f) <= 12) {
				err = true;
				break;
			}
		}
	}
	if (err) {
		pattern_magenta();
		} else {
		pattern_white();
	}
	return ;
}
#endif

void dlp_init(void)
{
}