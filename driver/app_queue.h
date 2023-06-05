/*
* ģ������ : ����-���ݽṹ
* �ļ����� : app_queue.h
* ˵    �� : ����-ѭ�����С�
*
* �޸ļ�¼ :
*       �汾��  ����        ����     ˵��
*
*/
#ifndef _APP_QUEUE_H_
#define _APP_QUEUE_H_

#include "GMtypes.h"


// ���У�������������(һ��ֻ����Ϊ�޷�������)
typedef uint8_t  queue_capacity_t;
// ���У������������ͣ����Զ���Ϊ��void *
typedef uint16_t  queue_buff_t;

typedef struct
{
    queue_buff_t *buff;                         // ������̬���仺����к�queue_buff_t buf[x];
    volatile queue_capacity_t wpos;             // д
    volatile queue_capacity_t rpos;             // ��
    volatile queue_capacity_t readable_nums;    // �ɶ�����
    queue_capacity_t capacity;                  // ����
    //void *mutex;                              // �ٽ�������
}queue_t;



// =============================== external function =======================
void queue_create(queue_t *queue, queue_buff_t *buff, queue_capacity_t capacity);
int8_t queue_push(queue_t *queue, const queue_buff_t *msg);
int8_t queue_pop(queue_t *queue, queue_buff_t *const msg);
queue_capacity_t queue_readable_nums(const queue_t *queue);
queue_capacity_t queue_capacity(const queue_t *queue);


#endif