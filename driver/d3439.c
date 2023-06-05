/*
 * d3434.c
 *
 * Created: 2021.01.22
 * Author: mingjie.gu
 */
#include "dlp_manager.h"
#include "utils.h"
#include "stdlib.h"
uint32_t R_current;
uint32_t G_current;
uint32_t B_current;
#if defined(P47)

int8_t safe_read(uint8_t sub_addr, uint8_t *param,
uint8_t para_len,volatile uint8_t *data,
uint8_t data_len)
{
	int8_t ret;
	volatile uint8_t status=0;
	int try_cnt = 5;
	read_dlp(0xd0, 0, 0, &status, 1);
	while (status != 0x81 && try_cnt-->0) {
		__delay_ms(100);
		read_dlp(0xd0, 0, 0, &status, 1);
	}
	ret = read_dlp(sub_addr, param, para_len, data, data_len);
	return ret;
}

int8_t safe_write(uint8_t sub_addr, volatile uint8_t *value, uint8_t len)
{
	int8_t ret;
	uint8_t status=0;
	int try_cnt = 5;
//	read_dlp(0xd0, 0, 0, &status, 1);
//	while (status != 0x81 && try_cnt-->0) {
//		__delay_ms(100);
//		read_dlp(0xd0, 0, 0, &status, 1);
//	}
	ret = write_dlp(sub_addr, value, len);
	return ret;
}

void pattern_white()
{
	uint8_t d[2];
	set_current(1);
	source_pattern();
	d[0] = 0x00;
	d[1] = 0x70;
	safe_write(0x0b, d, 2);
}

void pattern_red()
{
	uint8_t d[3];
	set_current(1);
	source_pattern();
	d[0] = 0x00;
	d[1] = 0x10;
	safe_write(0x0b, d, 2);
}

void pattern_green()
{
	uint8_t d[3];
	set_current(1);
	source_pattern();
	d[0] = 0x00;
	d[1] = 0x20;
	safe_write(0x0b, d, 2);
}

void pattern_blue()
{
	uint8_t d[3];
	set_current(1);
	source_pattern();
	d[0] = 0x00;
	d[1] = 0x30;
	safe_write(0x0b, d, 2);
}

void pattern_black()
{
	uint8_t d[3];
	set_current(1);
	source_pattern();
	d[0] = 0x01;
	safe_write(0x16, d, 1);
}

void pattern_magenta()
{
	uint8_t d[2];
	set_current(1);
	source_pattern();
	d[0] = 0x00;
	d[1] = 0x50;
	safe_write(0x0b, d, 2);
}

void pattern_yellow()
{
	uint8_t d[3];
	set_current(1);
	source_pattern();
	d[0] = 0x00;
	d[1] = 0x60;
	safe_write(0x0b, d, 2);
}

void pattern_grids()
{
	
}

void splash_0()
{
	uint8_t d[3];
	set_current(1);
	source_splash();
	d[0] = 0x00;
	safe_write(0x0d, d,1);
	safe_write(0x35, d,0);
}

void splash_1()
{
	uint8_t d[3];
	set_current(1);
	source_splash();
	d[0] = 0x01;
	safe_write(0x0d, d,1);
	safe_write(0x35, d,0);
}

void splash_2()
{
	uint8_t d[3];
	set_current(1);
	source_splash();
	d[0] = 0x02;
	safe_write(0x0d, d,1);
	safe_write(0x35, d,0);
}

void splash_3()
{
	uint8_t d[3];
	set_current(1);
	source_splash();
	d[0] = 0x03;
	safe_write(0x0d, d,1);
	safe_write(0x35, d,0);
}

void splash_4()
{
	uint8_t d[3];
	set_current(1);
	source_splash();
	d[0] = 0x04;
	safe_write(0x0d, d,1);
	safe_write(0x35, d,0);
}

void pic_init()
{
	pic_add(pattern_white);
	pic_add(splash_4);
	pic_add(splash_0);
	pic_add(splash_2);
	pic_add(splash_1);
	pic_add(splash_3);
	pic_add(pattern_red);
	pic_add(pattern_green);
	pic_add(pattern_blue);
	pic_add(pattern_black);
	pic_add(source_external);
}

void set_look(uint8_t index)
{
	uint8_t d[2];
	d[0] = index;
	safe_write(0x22,d,1);
}

//���ع�Ȧ
void set_aprerture(bool onoff)
{
	if (onoff) {
		//PORTB_set_pin_level(0, 1);
		//PORTB_set_pin_level(1, 0);
	} else {
		//PORTB_set_pin_level(0, 0);
		//PORTB_set_pin_level(1, 1);
	}
}

//��������,pattern
void set_actuator(bool onoff)
{

}

void actuator_pattern(bool onoff)
{

}

uint8_t actuator_read_gain()
{

}

void set_actuator_gain(bool onoff)
{

}


bool power_off()
{

}

bool power_on()
{
	return true;
}

void proj_reset()
{
	static bool flag = false;
	flag = !flag;
	if (flag) {
		//PORTB_set_pin_dir(3, PORT_DIR_OUT);
		//PORTB_set_pin_level(3, 0);	//proj on

        io_set_high(GPIOC,11);
		__delay_ms(200);
	} else {
		//PORTB_set_pin_level(3, 1);	//proj on
		__delay_ms(350);
		io_set_low(GPIOC,11);	//bp en

		__delay_ms(200);
		set_current(0);
		
		__delay_ms(200);
		pattern_white();
		__delay_ms(200);
		set_led(true);
	}
}

void set_led(bool onoff)
{
	uint8_t d[1];
	if (onoff) {
		d[0] = 0x07;
		safe_write(0x52, d, 1);
	} else {
		d[0] = 0x00;
		safe_write(0x52, d, 1);
	}
}

void set_current(bool level)
{
	if(level==1){
	R_current = Flash_Read(0x080175FF);
	G_current = Flash_Read(0x080176FF);
	B_current = Flash_Read(0x080177FF);
	set_rgbcurrent(R_current, G_current, B_current);			//4xx 630 900 900   40x 630 940 940 
	}
}

void source_external()
{
	uint8_t d[10];
	d[0] = 0x00;
	safe_write(0x05,d,1);
}

void source_splash()
{
	uint8_t d[10];
	d[0] = 0x02;
	safe_write(0x05, d, 1);
}

void source_pattern()
{
	uint8_t d[1];
	d[0] = 0x01;
	safe_write(0x05, d, 1);
}

void source_pattern_1()
{
	uint8_t d[1];
	d[0] = 0x01;
	safe_write(0x05, d, 1);
}
#endif
