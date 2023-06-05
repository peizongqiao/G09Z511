/*
 * dlp_manager.h
 *
 * Created: 2019/6/12 19:00:28
 *  Author: macha
 */


#ifndef DLP_MANAGER_H_
#define DLP_MANAGER_H_

#include "stdbool.h"
#include "stdint.h"
#include "utils.h"


typedef void (*pic_handle)(void);
struct pic_def {
	pic_handle handle;
	struct list_head qset;
};

#pragma pack(1)  //1字节对齐  G10使用
volatile struct  WPC_data 
{
	uint16_t tag;
	uint16_t len;
	uint8_t type;
	float lx;
	float W[2];
	uint8_t SN[30];
	float CIE1931;
	uint8_t duty[3];
	float WH[2];
	float R[3];
	float G[3];
	float B[3];
	float Black[3];
	uint16_t index;
	uint8_t result;
	uint32_t time;
	uint8_t tsp[14];	
	uint16_t crc;		
};
#pragma pack()

uint16_t crcChecksum(uint8_t *data, uint16_t len);

extern struct pic_def *pic_pos;

void pattern_white();
void pattern_red();
void pattern_green();
void pattern_blue();
void pattern_black();
void pattern_magenta();
void pattern_yellow();
void splash_0();
void splash_1();
void splash_2();
void splash_3();
void splash_4();
void pattern_grids();
void source_external();

//.23 使用
void front_splash();
void front_external();
void set_tsp_para();
volatile static uint8_t p23_coilA_gain,p23_coilC_gain,p23_coilA_invert,p23_coilC_invert;
volatile static uint16_t p23_coilA_length,p23_coilC_length;


//�л�ͼƬ
void pic_init();
void pic_next();
void pic_prev();
void pic_add(pic_handle handle);

//�л�look
void set_look(uint8_t index);

//���ع�Ȧ
void set_aprerture(bool onoff);

//��������,pattern
void set_actuator(bool onoff);
void actuator_pattern(bool onoff);
#if defined(P23_1080p)
uint8_t actuator_read_gain(uint8_t coil);
#endif
#if defined(P33)
uint8_t actuator_read_gain();
#endif
void set_actuator_gain(bool onoff);

bool power_off();
bool power_on();
void proj_reset();

void set_led(bool onoff);
void set_current(bool level);
void set_rgbcurrent(uint16_t r, uint16_t g, uint16_t b);
void source_splash();
void source_pattern();
void pattern_white_low();

void tsp_power(bool onoff);

#if defined(P3EM) || defined(P2NHD)
int8_t write_dlp(uint8_t sub_addr, volatile uint32_t value);
int8_t read_dlp(uint8_t sub_addr,volatile uint8_t *data);
#endif
#if defined(P23_720p) || defined(P23_540p) || defined(P33)
int8_t write_dlp(uint8_t sub_addr, volatile uint8_t *value, uint8_t len);
#endif
#if defined(P33) || defined(P47) || defined(P23_720p) || defined(P23_540p)
int8_t read_dlp(uint8_t sub_addr, uint8_t *param,
				uint8_t para_len,volatile uint8_t *data,
				uint8_t data_len);
int8_t safe_read(uint8_t sub_addr, uint8_t *param,
				uint8_t para_len,volatile uint8_t *data,
				uint8_t data_len);
#endif

void dlp_init(void);

#endif /* DLP_MANAGER_H_ */
