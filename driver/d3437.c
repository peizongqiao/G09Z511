/*
 * d3434.c
 *
 * Created: 2021.01.22
 * Author: mingjie.gu
 */
#include "dlp_manager.h"
#include "utils.h"
#include "stdlib.h"
uint16_t R_current;
uint16_t G_current;
uint16_t B_current;

volatile bool K8_flag = false;

#if defined(P33)

int8_t safe_read(uint8_t sub_addr, uint8_t *param,
				uint8_t para_len,volatile uint8_t *data,
				uint8_t data_len)
{
	int8_t ret;
	volatile uint8_t status=0;
	volatile int try_cnt = 5;
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
	volatile uint8_t status=0;
	volatile uint8_t try_cnt = 5;
	read_dlp(0xd0, 0, 0, &status, 1);
	while (status != 0x81 && try_cnt-->0) {
		__delay_ms(100);
		read_dlp(0xd0, 0, 0, &status, 1);
	}
	ret = write_dlp(sub_addr, value, len);
	return ret;
}

void tsp_power(bool onoff)
{
	//读状态
	volatile uint8_t status=0;
	volatile uint8_t try_cnt=5;
	io_set_dir_out(GPIOB,GPIO_PIN_0);
	read_dlp(0xd0, 0, 0, &status, 1);
	while(try_cnt){
		if (status == 0x81) {
			if(onoff==true)
			io_set_high(GPIOB,GPIO_PIN_0);
			else if(onoff==true)
			io_set_low(GPIOB,GPIO_PIN_0);
			break;
			}else{
			__delay_ms(100);
			read_dlp(0xd0, 0, 0, &status, 1);
			try_cnt--;
		}
	}
}

void pattern_white()
{
	set_current(1);
	__delay_ms(100);
	uint8_t d[3];
	uint8_t a[3];
	a[0] = 0x05;
	a[1] = 0x02;
	i2c_write_block(0x36, 2, 0, a);
	__delay_ms(100);
	d[0] = 0x16;
	d[1] = 0x0f;
	i2c_write_block(0x36, 2, 0, d);
}

void pattern_white_low()
{
	set_current(0);
	__delay_ms(100);
	uint8_t d[3];
	uint8_t a[3];
	a[0] = 0x05;
	a[1] = 0x02;
	i2c_write_block(0x36, 2, 0, a);
	__delay_ms(100);
	d[0] = 0x16;
	d[1] = 0x0f;
	i2c_write_block(0x36, 2, 0, d);
}

void pattern_red()
{
	uint8_t d[2];
	set_current(1);
	__delay_ms(100);
//	source_pattern();
	d[0] = 0x16;
	d[1] = 0x03;
	i2c_write_block(0x36, 2, 0, d);
}

void pattern_green()
{
	uint8_t d[3];
	set_current(1);
	__delay_ms(100);
//	source_pattern();
	d[0] = 0x16;
	d[1] = 0x05;
	i2c_write_block(0x36, 2, 0, d);
}

void pattern_blue()
{
	uint8_t d[3];
	set_current(1);
	__delay_ms(100);
//	source_pattern();
	d[0] = 0x16;
	d[1] = 0x07;
	i2c_write_block(0x36, 2, 0, d);
}

void pattern_black()
{
	uint8_t d[3];
	set_current(1);
	__delay_ms(100);
//	source_pattern();
	d[0] = 0x16;
	d[1] = 0x01;
	i2c_write_block(0x36, 2, 0, d);
}

void pattern_magenta()
{
	uint8_t d[3];
	set_current(1);
	__delay_ms(100);
//	source_pattern();
	d[0] = 0x16;
	d[1] = 0x0b;
	i2c_write_block(0x36, 2, 0, d);
}

void pattern_yellow()
{
	uint8_t d[3];
	set_current(1);
	__delay_ms(100);
//	source_pattern();
	d[0] = 0x16;
	d[1] = 0x0d;
	i2c_write_block(0x36, 2, 0, d);
}

void after_splash()
{
	uint8_t d[10] = {0x02};
	safe_write(0x62, d, 1);
	d[0] = 0x56;
	d[1] = 0x05;
	d[2] = 0x00;
	d[3] = 0x03;
	safe_write(0x60, d, 4);

}

void splash_0()
{
	uint8_t a[2];
	uint8_t b[2];
	uint8_t c[2];
	uint8_t d[2];
	a[0] = 0x16;
	a[1] = 0x00;
	i2c_write_block(0x36, 2, 0, a);
	__delay_ms(100);
	b[0] = 0x05;
	b[1] = 0x02;
	i2c_write_block(0x36, 2, 0, b);
	__delay_ms(100);
	c[0] = 0x0d;
	c[1] = 0x00;
	i2c_write_block(0x36, 2, 0, c);
	__delay_ms(100);
	d[0] = 0x35;
	i2c_write_block(0x36, 1, 0, d);
}

void splash_1()
{
	uint8_t a[2];
	uint8_t b[2];
	uint8_t c[2];
	uint8_t d[2];
//	a[0] = 0x16;
//	a[1] = 0x00;
//	i2c_write_block(0x36, 2, 0, a);
//	__delay_ms(100);
//	b[0] = 0x05;
//	b[1] = 0x02;
//	i2c_write_block(0x36, 2, 0, b);
	c[0] = 0x0d;
	c[1] = 0x01;
	i2c_write_block(0x36, 2, 0, c);
	__delay_ms(100);
	d[0] = 0x35;
	i2c_write_block(0x36, 1, 0, d);
}

void splash_2()
{
	uint8_t a[2];
	uint8_t b[2];
	uint8_t c[2];
	uint8_t d[2];
//	a[0] = 0x16;
//	a[1] = 0x00;
//	i2c_write_block(0x36, 2, 0, a);
//	__delay_ms(100);
//	b[0] = 0x05;
//	b[1] = 0x02;
//	i2c_write_block(0x36, 2, 0, b);
	c[0] = 0x0d;
	c[1] = 0x02;
	i2c_write_block(0x36, 2, 0, c);
	__delay_ms(100);
	d[0] = 0x35;
	i2c_write_block(0x36, 1, 0, d);
}

void splash_3()
{
	uint8_t a[2];
	uint8_t b[2];
	uint8_t c[2];
	uint8_t d[2];
	a[0] = 0x16;
	a[1] = 0x00;
//	i2c_write_block(0x36, 2, 0, a);
//	__delay_ms(100);
//	b[0] = 0x05;
//	b[1] = 0x02;
//	i2c_write_block(0x36, 2, 0, b);
	c[0] = 0x0d;
	c[1] = 0x03;
	i2c_write_block(0x36, 2, 0, c);
	__delay_ms(100);
	d[0] = 0x35;
	i2c_write_block(0x36, 1, 0, d);
}

void splash_4()
{
	uint8_t a[2];
	uint8_t b[2];
	uint8_t c[3];
	uint8_t d[3];
	a[0] = 0x16;
	a[1] = 0x0E;
	i2c_write_block(0x36, 2, 0, a);
	__delay_ms(100);
	b[0] = 0x05;
	b[1] = 0x00;
	i2c_write_block(0x36, 2, 0, b);
	__delay_ms(100);
//	c[0] = 0x62;
//	c[1] = 0x00;
	d[0] = 0x67;
	d[1] = 0x08;
	d[2] = 0x00;
	i2c_write_block(0x36, 3, 0, d);
	__delay_ms(100);
//	d[0] = 0x67;
//	d[1] = 0x08;
//	d[2] = 0x00;
		c[0] = 0x62;
	c[1] = 0x00;
	__delay_ms(100);
	i2c_write_block(0x36, 2, 0, c);
}

void pattern_grids()
{
	uint8_t d[3] = {0};
	source_pattern();
	d[0] = 0x81;
	d[1] = 0x00;
	safe_write(0x67, d, 2);
}

volatile static uint8_t act_gain;
void pic_init()
{
	#if defined(G08X100)
	pic_add(pattern_white);
	pic_add(pattern_black);
	pic_add(splash_0);
	pic_add(splash_1);
	pic_add(splash_2);
	pic_add(splash_3);
	pic_add(pattern_red);
	pic_add(pattern_green);
	pic_add(pattern_blue);
	pic_add(source_external);
	#else 
	pic_add(pattern_white);
	pic_add(splash_2);
	pic_add(splash_0);
	pic_add(splash_1);
	pic_add(splash_3);
	pic_add(pattern_red);
	pic_add(pattern_green);
	pic_add(pattern_blue);
	pic_add(pattern_black);
	pic_add(source_external);
	#endif

	act_gain = actuator_read_gain();
}

void set_look(uint8_t index)
{
	uint8_t d[2];
	d[0] = index;
	safe_write(0x22,d,1);
}

//??????
void set_aprerture(bool onoff)
{

}

//????????,pattern
void set_actuator(bool onoff)
{
	if (onoff) {
		uint8_t d[1] = {0x00};
		safe_write(0x7a, d, 1);
		d[0] = 0x01;
		safe_write(0x7e, d, 1);
	} else {
		uint8_t d[1] = {0x01};
		safe_write(0x7a, d, 1);
		d[0] = 0x00;
		safe_write(0x7e, d, 1);
	}
}

void actuator_pattern(bool onoff)
{
	if (onoff) {
		uint8_t d[2] = {0x00};
		source_pattern();
		__delay_ms(100);
		d[0] = 0x08;
		write_dlp(0x67, d, 2);
	} else {
		source_external();
	}
}

uint8_t actuator_read_gain()
{
	volatile static uint8_t gain;
	safe_read(0x73, 0, 0, &gain, 1);
	return gain;
}

void set_actuator_gain(bool onoff)
{
	if (onoff) {
		safe_write(0x72, &act_gain, 1);
	} else {
		uint8_t d[2] = {0};
		safe_write(0x72, &d, 1);
	}
}

bool power_off()
{	
//	tsp_power(false);
	set_actuator(false);
	set_current(false);
	io_set_dir_out(GPIOC,GPIO_PIN_14);
	io_set_low(GPIOC,GPIO_PIN_14);
	
	return true;
}

bool power_on()
{	
	__delay_ms(70);
	io_set_dir_out(GPIOC,GPIO_PIN_14);
	io_set_high(GPIOC,GPIO_PIN_14);
	__delay_ms(1000);	
	set_current(false);	
	set_led(true);
	uint8_t p[] = {0x01};
	uint8_t d[13];
	if(safe_read(0x0f, p, sizeof(p), d, 13)){
		set_actuator(true);
		tsp_power(true);
		return true;
	}
	return false;
}

void proj_reset()
{
	K8_flag = false;
	volatile uint8_t status=0;
	volatile uint8_t try_cnt=5;
	while(try_cnt--){
		__delay_ms(100);
		read_dlp(0xd0, 0, 0, &status, 1);
		if(status == 0x81){
			power_off();
			break;
		}
	}
	if(status!=0x81){
		if (power_on()) {
			pattern_white();
		}
	}
}
void set_led(bool onoff)
{
	uint8_t d[2];
	if (onoff) {
		d[0] = 0x07;
		safe_write(0x52, d, 1);
	} else {
		d[0] = 0x00;
		safe_write(0x52, d, 1);
	}
}
uint16_t R_current;
uint16_t G_current;
uint16_t B_current;

void set_current(bool level)
{
	R_current = Flash_Read(0x080175FF);
	G_current = Flash_Read(0x080176FF);
	B_current = Flash_Read(0x080177FF);
	if(level==1)
	set_rgbcurrent(R_current, G_current, B_current);			//10.4A，15.6A，15.6A
	else if(level==0)
	set_rgbcurrent(250, 100, 250);			//10.4A，15.6A，15.6A
}

void source_external()
{
	uint8_t d[2];
	uint8_t c[2];
//	d[0] = 0x16;
//	d[1] = 0x00;
//	i2c_write_block(0x36, 2, 0, d);
//	__delay_ms(100);
	c[0] = 0x14;
	c[1] = 0x04;
	i2c_write_block(0x36, 2, 0, c);
	__delay_ms(100);
	d[0] = 0x62;
	d[1] = 0x02;
	i2c_write_block(0x36, 2, 0, d);
}


void source_splash()
{
	tsp_power(false);
	set_actuator_gain(false);
	uint8_t d[] = {0x02};
	safe_write(0x05, d, sizeof(d));
}

void source_pattern()
{
	tsp_power(true);
	set_actuator_gain(true);
	uint8_t d[] = {0x00};
	d[0] = 0x00;
	safe_write(0x62, d, sizeof(d));
	safe_write(0x05, d, sizeof(d));
	
}

#endif
