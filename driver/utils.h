#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>

//#define P23_540p
//#define P23_720p
//#define P23_1080p
#define P33     
//#define P33_MS
//#define P33_MP
//#define P47
//#define P2NHD
//#define P3EM
//#define G10N000
//#define G10N120
//#define G05X200
//#define G05X203
//#define G05N010
//#define G07N100
//#define G07N120
//#define G08X100
//#define G08X200

#if defined(G07N100) || defined(G07N120)
	#define P23_540p
#endif

#if defined(G10N120) || defined(G10N000)
	#define P23_1080p
#endif

#if defined(P23_1080p)
	#define  P23_720p
#endif

#if defined(G08X100) || defined(G08X200) || defined(P33_MS) ||  defined(P33_MP)
	#define P33
#endif

#if defined(G05X200) || defined(G05X203) || defined(G05X205) ||defined(G05N010)
	#define P47
#endif

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80

/**
 * \brief Retrieve array size
 */
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

/** @} */

#define container_of(ptr, type, member) ({      \
 const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
  (type *)( (char *)__mptr - offsetof(type,member) );})      //获取某结构体某成员的入口地址

struct list_head { 
	struct list_head *next, *prev; 
};
typedef unsigned char           BOOL;
static inline void init_list_head(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

static inline void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}

#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

#define list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)
	
#define list_next_entry(pos, member) \
	list_entry((pos)->member.next, typeof(*(pos)), member)
	
#define list_prev_entry(pos, member) \
	list_entry((pos)->member.prev, typeof(*(pos)), member)

#define list_for_each_entry(pos, head, member)				\
	for (pos = list_first_entry(head, typeof(*pos), member);	\
	     &pos->member != (head);					\
	     pos = list_next_entry(pos, member))

#define true                              1
#define false                             0

typedef struct
{
    uint16_t node_x;    // x坐标
    int8_t node_y;      // y坐标
}coordinateXY_node_t;

void add_key_event(void);

typedef struct
{
    uint16_t *p_buff;
    uint8_t sizes;
    BOOL is_full;
    uint8_t w_postion;
    uint16_t max;
    uint16_t min;
    uint32_t total_value;
}filter_ctrl_t;

uint16_t filter_avg(filter_ctrl_t *p_ctrl, uint16_t data);
void delay_us_block(uint16_t cnt);

/********驱动*********/
#include "i2c_master.h"//i2c
#include "utils.h"
#include "dlp_manager.h"




#ifdef __cplusplus
}
#endif
#endif /* UTILS_H_INCLUDED */
