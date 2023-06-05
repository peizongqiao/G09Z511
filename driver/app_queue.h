/*
* 模块名称 : 队列-数据结构
* 文件名称 : app_queue.h
* 说    明 : 队列-循环队列。
*
* 修改记录 :
*       版本号  日期        作者     说明
*
*/
#ifndef _APP_QUEUE_H_
#define _APP_QUEUE_H_

#include "GMtypes.h"


// 队列：容量数据类型(一般只设置为无符号类型)
typedef uint8_t  queue_capacity_t;
// 队列：缓存数据类型，可以定义为：void *
typedef uint16_t  queue_buff_t;

typedef struct
{
    queue_buff_t *buff;                         // 经过动态分配缓冲队列后，queue_buff_t buf[x];
    volatile queue_capacity_t wpos;             // 写
    volatile queue_capacity_t rpos;             // 读
    volatile queue_capacity_t readable_nums;    // 可读数量
    queue_capacity_t capacity;                  // 容量
    //void *mutex;                              // 临界区互斥
}queue_t;



// =============================== external function =======================
void queue_create(queue_t *queue, queue_buff_t *buff, queue_capacity_t capacity);
int8_t queue_push(queue_t *queue, const queue_buff_t *msg);
int8_t queue_pop(queue_t *queue, queue_buff_t *const msg);
queue_capacity_t queue_readable_nums(const queue_t *queue);
queue_capacity_t queue_capacity(const queue_t *queue);


#endif