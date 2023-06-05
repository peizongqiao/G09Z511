/*
 * control_task.c
 *
 * Created: 2018/5/2 9:39:19
 *  Author: TF
 */ 
#include "control_task.h"

static struct list_head task_head;	//任务链表头

void task_init(void)
{
	init_list_head(&task_head);
}

void task_add(void (*task_hook)(void), uint16_t itv_time)
{
	struct task_components *task;
	task = malloc(sizeof(struct task_components));
	task->run_flag = 0;
	task->itv_time = itv_time/3;
	task->timer = itv_time;
	task->task_hook = task_hook;
	list_add_tail(&task->qset, &task_head);
}

void task_remarks(void)
{
	struct task_components *task;
	
	list_for_each_entry(task, &task_head, qset) {
		if (task->timer) {
			task->timer--;
			if (task->timer == 0) {
				task->timer = task->itv_time;
				task->run_flag = true;
			}
		}
	}
}

void task_process(void)
{
	struct task_components *task;
	uint8_t tmp = 0;

	if(SREG & 0x80 ) {
		tmp = 1;
		SREG &= ~0x80;
	}
	list_for_each_entry(task, &task_head, qset) {
		if (task->run_flag == true) {
			task->run_flag = false;
			task->task_hook();
		}
	}
	if (tmp) {
		SREG |= 0X80;
	}
	
	//static uint16_t cnt = 0;
	////老化G10N120治具控制风扇 使用时解开注释   8  13   //
	//PORTB_set_pin_dir(1, PORT_DIR_OUT);
	//if((cnt%8) == 0){
		//PB1_set_level(true);
	//}
	//if((cnt%13) == 0){
		//PB1_set_level(false);
	//}
	//if(cnt < 40000){
		//cnt++;
		//}else{
			//cnt = 0;
		//}

	
}