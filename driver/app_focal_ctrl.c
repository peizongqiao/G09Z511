#include "app_focal_ctrl.h"
#include "bsp_focal_dz24.h"
#include "app_softtimer.h"
#include "app_log.h"
#include "bsp_pi_api.h"
#include "app_iris.h"
#include "bsp_filtermotor_soft_subdivision.h"
#include "i2c_master_1.h"
#include "i2c2_slave_N32G43X.h"

uint16_t focal_step,focal_step_1;
uint16_t zoom_step,zoom_step_1;
uint16_t focus_step_number;
uint16_t zoom_step_number;
uint8_t focal_end = 0,zoom_end = 0,focal_pi_flag = 0,zoom_pi_flag = 0;
bool RecycleFlag = false;
bool RecycleFlag_1 = false;
extern bool df_status;
extern bool status;
uint8_t aut_iris;
uint8_t aut_df[4];
extern uint8_t flag_count;
extern uint16_t iris_number;
extern uint16_t filter_step_number;
extern uint32_t iris_step;
extern uint32_t iris_step_go;
uint16_t iris_number_1;
uint16_t RcycleCnt_focus;
uint16_t RcycleCnt_zoom;

void focal_init(void)
{
    focal_ctrl_t *pctrl = &focal_ctrl;

    pctrl->focus_run_number = 0;
	pctrl->zoom_run_number = 0;
    pctrl->focus_direction = E_DIRECTION_STOP;
    pctrl->zoom_direction = E_DIRECTION_STOP;
    bsp_focal_api_init();
}


uint8_t reture_date[10];
uint16_t log_step,log_pps; 
uint16_t absolutely_step,focal_mode = 0;
extern uint8_t log_number,log_flag;
extern uint8_t RxBuffer[15];
bool flag_pps = 0;
void foacl()
{
	focal_ctrl_t *pctrl = &focal_ctrl;
	uint8_t check_sum = 0,data_sum = 0,back_check_sum = 0;
    if(log_flag == 1)
    {
         check_sum = 0;
        for(int x = 1;x<12;x++)
        {
            check_sum = check_sum + RxBuffer[x];
        }
        data_sum = (RxBuffer[12] - '0')*10 + (RxBuffer[13] - '0');
        check_sum = check_sum%100;       
        if(check_sum == data_sum)
        {
            reture_date[5] = 0; 
            log_step = (RxBuffer[4] - '0')*1000 + (RxBuffer[5] - '0')*100 + (RxBuffer[6] - '0')*10 + (RxBuffer[7] - '0');
			if((RxBuffer[2] == 'A' && RxBuffer[3] == 'T')==0&&(RxBuffer[2] == 'S' && RxBuffer[3] == 'T')==0)
			{
				log_pps = (RxBuffer[8] - '0')*1000 + (RxBuffer[9] - '0')*100 + (RxBuffer[10] - '0')*10 + (RxBuffer[11] - '0');
			}
            reture_date[6] = 1;
            if(RxBuffer[1] == 0X31 && RxBuffer[2] == 'P' && RxBuffer[3] == 'I')
            {	
                pctrl -> focus_direction = E_DIRECTION_RUN;
                focal_step=4000;
				focus_step_number = focus_step_number-1;
				if(focus_step_number>6000)
					focus_step_number = 0;
            }
            else if(RxBuffer[1] == 0X31 &&RxBuffer[2] == 'G' && RxBuffer[3] == 'O')
            {
                pctrl -> focus_direction = E_DIRECTION_RET;
                focal_step=log_step;
            }
            else if(RxBuffer[1] == 0X31 &&RxBuffer[2] == 'B' && RxBuffer[3] == 'K')
            {
                pctrl -> focus_direction = E_DIRECTION_RUN;
                focal_step=log_step;
            }
            else if(RxBuffer[1] == 0X31 &&RxBuffer[2] == 'S' && RxBuffer[3] == 'T')
            {
                pctrl -> focus_direction = E_DIRECTION_STOP;
            }
            else if(RxBuffer[1] == 0X31 &&RxBuffer[2] == 'A' && RxBuffer[3] == 'T')
            {
                if(pctrl -> focus_direction == E_DIRECTION_STOP)
                {
                   reture_date[5] = 1; 
                }
                else
                   reture_date[5] = 2; 
            }  
			else if(RxBuffer[1] == 0X32 && RxBuffer[2] == 'P' && RxBuffer[3] == 'I')
            {	
				pctrl -> zoom_direction = E_DIRECTION_RUN;
				zoom_step=4000;
				zoom_step_number = zoom_step_number-1;
				if(zoom_step_number>6000)
					zoom_step_number = 0;	
            }
            else if(RxBuffer[1] == 0X32 &&RxBuffer[2] == 'G' && RxBuffer[3] == 'O')
            {
                pctrl -> zoom_direction = E_DIRECTION_RET;
                zoom_step=log_step;
            }
            else if(RxBuffer[1] == 0X32 &&RxBuffer[2] == 'B' && RxBuffer[3] == 'K')
            {
                pctrl -> zoom_direction = E_DIRECTION_RUN;
                zoom_step=log_step;
            }
            else if(RxBuffer[1] == 0X32 &&RxBuffer[2] == 'S' && RxBuffer[3] == 'T')
            {
                pctrl -> zoom_direction = E_DIRECTION_STOP;
            }
			else if(RxBuffer[1] == 0X32 &&RxBuffer[2] == 'B' && RxBuffer[3] == 'G')
            {
                pctrl -> zoom_direction = E_DIRECTION_RET;
				zoom_step = 3050;
            }
            else if(RxBuffer[1] == 0X32 &&RxBuffer[2] == 'A' && RxBuffer[3] == 'T')
            {
                if(pctrl -> zoom_direction == E_DIRECTION_STOP)
                {
                   reture_date[5] = 1; 
                }
                else
                   reture_date[5] = 2; 
            } 

			else if(RxBuffer[1] == 0X33 && RxBuffer[2] == 'P' && RxBuffer[3] == 'I')
            {	
				aut_iris = 1;
            }
            else if(RxBuffer[1] == 0X33 &&RxBuffer[2] == 'G' && RxBuffer[3] == 'O')
            {
				aut_iris = 2;
            }
            else if(RxBuffer[1] == 0X33 &&RxBuffer[2] == 'B' && RxBuffer[3] == 'K')
            {
				aut_iris = 3;
            }
            else if(RxBuffer[1] == 0X33 &&RxBuffer[2] == 'S' && RxBuffer[3] == 'T')
            {
                aut_iris = 4;
            }
			else if(RxBuffer[1] == 0X33 &&RxBuffer[2] == 'S' && RxBuffer[3] == 'E')
            {
                aut_iris = 5;
            }
            else if(RxBuffer[1] == 0X33 &&RxBuffer[2] == 'A' && RxBuffer[3] == 'T')
            {
                if(iris_step==0&&iris_step_go==0)
                {
                   reture_date[5] = 1; 
                }
                else
                   reture_date[5] = 2; 
            }  	
			else if(RxBuffer[1] == 0X34 && RxBuffer[2] == 'P' && RxBuffer[3] == 'I')
            {	
				aut_df[0] = 0x03;
				i2c_write_block_1(0x80, 1, 0, aut_df);

            }
            else if(RxBuffer[1] == 0X34 &&RxBuffer[2] == 'G' && RxBuffer[3] == 'O')
            {
				aut_df[0] = 0x04;
				aut_df[1] = log_step;
				aut_df[2] = log_step>>8;
				i2c_write_block_1(0x80, 3, 0, aut_df);
				I2C2_GPIO_init_1();
            }
            else if(RxBuffer[1] == 0X34 &&RxBuffer[2] == 'B' && RxBuffer[3] == 'K')
            {
				aut_df[0] = 0x05;
				aut_df[1] = log_step;
				aut_df[2] = log_step>>8;
				i2c_write_block_1(0x80, 3, 0, aut_df);

            }
            else if(RxBuffer[1] == 0X34 &&RxBuffer[2] == 'S' && RxBuffer[3] == 'T')
            {
                aut_df[0] = 0x06;
				i2c_write_block_1(0x80, 1, 0, aut_df);

            }
			else if(RxBuffer[1] == 0X34 &&RxBuffer[2] == 'C' && RxBuffer[3] == 'L')
            {
                aut_df[0] = 0x07;
				i2c_write_block_1(0x80, 1, 0, aut_df);

            }
			else if(RxBuffer[1] == 0X34 &&RxBuffer[2] == 'H' && RxBuffer[3] == 'A')
            {
                aut_df[0] = 0x08;
				i2c_write_block_1(0x80, 1, 0, aut_df);

            }
            else if(RxBuffer[1] == 0X34 &&RxBuffer[2] == 'A' && RxBuffer[3] == 'T')
            {
                if(df_status==1)
                {
                   reture_date[5] = 1; //IDLE
                }
                else 
                   reture_date[5] = 2; //BUSY
            } 
        }
        else
        {
            reture_date[6] = 0;
        }
		if(RxBuffer[1] == 0x31)
		{
			reture_date[1] = focus_step_number/1000;
			reture_date[2] = (focus_step_number%1000)/100;
			reture_date[3] = ((focus_step_number%1000)%100)/10;
			reture_date[4] = ((focus_step_number%1000)%100)%10;
		}
		if(RxBuffer[1] == 0x32)
		{
			reture_date[1] = zoom_step_number/1000;
			reture_date[2] = (zoom_step_number%1000)/100;
			reture_date[3] = ((zoom_step_number%1000)%100)/10;
			reture_date[4] = ((zoom_step_number%1000)%100)%10;
		}
		if(RxBuffer[1] == 0x33)
		{
			iris_number_1 = iris_number/17;
			reture_date[1] = iris_number_1/1000;
			reture_date[2] = (iris_number_1%1000)/100;
			reture_date[3] = ((iris_number_1%1000)%100)/10;
			reture_date[4] = ((iris_number_1%1000)%100)%10;
		}
		if(RxBuffer[1] == 0x34)
		{
			reture_date[1] = filter_step_number/1000;
			reture_date[2] = (filter_step_number%1000)/100;
			reture_date[3] = ((filter_step_number%1000)%100)/10;
			reture_date[4] = ((filter_step_number%1000)%100)%10;
		}
		
        back_check_sum = 0;
        for(int x = 1;x<7;x++)
        {
            back_check_sum = back_check_sum + reture_date[x];
        } 
        reture_date[7] = back_check_sum/10;
        reture_date[8] = back_check_sum%10;
        log_info("<%d%d%d%d%d%d%d%d>",reture_date[1],reture_date[2],reture_date[3],reture_date[4],reture_date[5],reture_date[6],reture_date[7],reture_date[8]);
        log_flag = 0;
        USART_ConfigInt(UART4, USART_INT_RXDNE, ENABLE);
    } 
}

extern uint8_t MOTOR_count;
uint8_t focal_test_flag;
uint16_t focal_motor_step,zoom_motor_step;
uint16_t focal_step_go,zoom_step_go;
uint8_t focaltest,zoomtest;
uint8_t zoom_test_flag;

void old(void)
{
	focal_ctrl_t *pctrl = &focal_ctrl;
	if(flag_count==43){// OLD
		flag_count = 0;
		focal_test_flag = 0;
	    RecycleFlag = true;
	}
	if(flag_count==45)
	{
		flag_count = 0;
		zoom_test_flag = 0;
		RecycleFlag_1 = true;
	}
	if (flag_count==44) // Manual
	{
		flag_count = 0;
		focal_test_flag = 0;
		pctrl -> focus_direction = E_DIRECTION_STOP;
		RecycleFlag = false;
	}
	if (flag_count==46) // Manual
	{
		flag_count = 0;
		zoom_test_flag = 0;
		pctrl -> zoom_direction = E_DIRECTION_STOP;
		RecycleFlag_1 = false;
	}
}

void focal_ctrl_poll(void)
{
	focal_ctrl_t *pctrl = &focal_ctrl;
	if(flag_count==28)
	{
		if(focus_step_number==3050)
			focus_step_number = 3049;
		pctrl -> focus_direction = E_DIRECTION_RET;
		focal_step=20;
	}
	else if(flag_count==29)
	{
		pctrl -> focus_direction = E_DIRECTION_RUN;
		focal_step=20;
	}
	else if(MOTOR_count==1)
	{
		MOTOR_count = 0;
		focal_test_flag = 0;
		pctrl -> focus_direction = E_DIRECTION_RET;
		focal_step=24;
	}
	else if(MOTOR_count==2)
	{
		MOTOR_count = 0;
		focal_test_flag = 0;
		pctrl -> focus_direction = E_DIRECTION_RUN;
		focal_step=24;
	}
	else if(flag_count==55)
	{
		flag_count = 0;
		focal_test_flag = 1;
		focal_motor_step = 0;
		focaltest = 0;
		pctrl -> focus_direction = E_DIRECTION_RET;
		focal_step_go = 3200;
	}
}	


void focal_diver_poll(void)
{
	focal_ctrl_t *pctrl = &focal_ctrl;
	focal_pi_flag = FocusMotorWait();
	if(RecycleFlag==false)
	{
		if(E_DIRECTION_RUN == pctrl -> focus_direction && true == focal_pi_flag)
		{
			focus_step_number = 0;
			focal_step = 0;
			pctrl -> focus_direction = E_DIRECTION_STOP;
		}
		else if(focal_step != 0)
		{
			pctrl -> focus_run_number++;
			if(pctrl -> focus_run_number >= 8)
				pctrl -> focus_run_number = 0;
			bsp_focus_api_run(pctrl ->focus_run_number,pctrl ->focus_direction);
				if(E_DIRECTION_RUN == pctrl ->focus_direction)
					focus_step_number--;
				if(focus_step_number>=6000)
					focus_step_number = 0;
				else if(E_DIRECTION_RET == pctrl ->focus_direction)
					focus_step_number++;
				if(focus_step_number >= 3050)
				focus_step_number = 3050;
				focal_step --;
			if(focal_step == 0)
			{
				pctrl -> focus_direction = E_DIRECTION_STOP;
			}
		}
	}
	else 
	{
		if(RcycleCnt_focus < 3050)
		{
			RcycleCnt_focus++;
		}
		else
		{				
			RcycleCnt_focus = 0;
			if(pctrl ->focus_direction==E_DIRECTION_RUN)
				pctrl ->focus_direction = E_DIRECTION_RET;
			else
				pctrl ->focus_direction = E_DIRECTION_RUN;
		}
		pctrl -> focus_run_number++;
		if(pctrl -> focus_run_number >= 8)
			pctrl -> focus_run_number = 0;
		bsp_focus_api_run(pctrl ->focus_run_number,pctrl ->focus_direction);
	}
}

 void zoom_ctrl_poll(void)
{
	focal_ctrl_t *pctrl = &focal_ctrl;
	if(flag_count==30)
	{
		if(zoom_step_number==3050)
			zoom_step_number = 3049;
		pctrl -> zoom_direction = E_DIRECTION_RET;
		zoom_step=20;
	}
	else if(flag_count==31)
	{
		pctrl -> zoom_direction = E_DIRECTION_RUN;
		zoom_step=20;
	}
	else if(MOTOR_count==3)
	{
		pctrl -> zoom_direction = E_DIRECTION_RUN;
		zoom_test_flag = 0;
		MOTOR_count = 0;
		zoom_step=24;
	}
	else if(MOTOR_count==4)
	{
		pctrl -> zoom_direction = E_DIRECTION_RET;
		zoom_test_flag = 0;
		MOTOR_count = 0;
		zoom_step=24;
	}
	else if(flag_count==56)
	{
		flag_count = 0;
		zoom_test_flag = 1;
		pctrl -> zoom_direction = E_DIRECTION_RET;
		zoom_motor_step = 0;
		zoomtest = 0;
		zoom_step_go=4000;
	}
}

void zoom_diver_poll(void)
{
	focal_ctrl_t *pctrl = &focal_ctrl;
	zoom_pi_flag = DoorMotorWait();
	if(RecycleFlag_1==false)
	{
		if(E_DIRECTION_RUN == pctrl -> zoom_direction && true == zoom_pi_flag)
		{
			zoom_step_number = 0;
			zoom_step = 0;
			pctrl -> zoom_direction = E_DIRECTION_STOP;
		}
		else if(zoom_step != 0)
		{
			pctrl -> zoom_run_number++;
			if(pctrl -> zoom_run_number >= 8)
				pctrl -> zoom_run_number = 0;
			bsp_zoom_api_run(pctrl ->zoom_run_number,pctrl ->zoom_direction);
			if(E_DIRECTION_RUN == pctrl ->zoom_direction)
				zoom_step_number--;
			if(zoom_step_number>=6000)
					zoom_step_number = 0;
			else if(E_DIRECTION_RET == pctrl ->zoom_direction)
				zoom_step_number++;
			if(zoom_step_number >= 3050)
				zoom_step_number = 3050;
			zoom_step --;
			if(zoom_step == 0)
			{
				pctrl -> zoom_direction = E_DIRECTION_STOP;	
			}
		}
	}
	else
	{
		if(RcycleCnt_zoom < 3050)
		{
			RcycleCnt_zoom++;
		}
		else
		{				
			RcycleCnt_zoom = 0;
			if(pctrl ->zoom_direction==E_DIRECTION_RUN)
				pctrl ->zoom_direction = E_DIRECTION_RET;
			else
				pctrl ->zoom_direction = E_DIRECTION_RUN;
		}
		pctrl -> zoom_run_number++;
		if(pctrl -> zoom_run_number >= 8)
			pctrl -> zoom_run_number = 0;
		bsp_zoom_api_run(pctrl ->zoom_run_number,pctrl ->zoom_direction);
	}
}
//************************************************************ 马达自测功能 ******************************************************************
void focal_back_go()
{
	focal_ctrl_t *pctrl = &focal_ctrl;
	if(focal_test_flag==1)
	{
		if(focal_step_go != 0)
		{
			focaltest = 1;
			pctrl -> focus_run_number++;
			if(pctrl -> focus_run_number >= 8)
				pctrl -> focus_run_number = 0;
			bsp_focus_api_run(pctrl ->focus_run_number,pctrl ->focus_direction);
			focal_step_go--;
		}
		else
			focal_test_flag = 2;
	}
	else if(focal_test_flag==2)
	{
		if(focal_pi_flag==0)
		{
			focaltest = 1;
			pctrl -> focus_direction = E_DIRECTION_RUN;
			pctrl -> focus_run_number++;
			if(pctrl -> focus_run_number >= 8)
				pctrl -> focus_run_number = 0;
			bsp_focus_api_run(pctrl ->focus_run_number,pctrl ->focus_direction);
			focal_motor_step++;
		}
		else if(focal_motor_step<3350&&focal_motor_step>2850)
			focaltest = 2;
		else 
			focaltest = 3;
	}
}

void zoom_back_go()
{
	focal_ctrl_t *pctrl = &focal_ctrl;
	if(zoom_test_flag==1)
	{
		if(zoom_step_go != 0)
		{
			zoomtest = 1;
			pctrl -> zoom_run_number++;
			if(pctrl -> zoom_run_number >= 8)
				pctrl -> zoom_run_number = 0;
			bsp_zoom_api_run(pctrl ->zoom_run_number,pctrl ->zoom_direction);
			zoom_step_go--;
		}
		else
			zoom_test_flag = 2;
	}
	else if(zoom_test_flag == 2)
	{
		if(zoom_pi_flag == 0)
		{
			zoomtest = 1;
			pctrl -> zoom_direction = E_DIRECTION_RUN;
			pctrl -> zoom_run_number++;
			if(pctrl -> zoom_run_number >= 8)
				pctrl -> zoom_run_number = 0;
			bsp_zoom_api_run(pctrl ->zoom_run_number,pctrl ->zoom_direction);
			zoom_motor_step++;
		}
		else if(zoom_motor_step<3200&&zoom_motor_step>2800)
		{
			zoomtest = 2;
		}
		else
			zoomtest = 3;
	}
}



