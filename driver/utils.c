/*
 * utils.c
 *
 * Created: 2020/8/18 11:49:13
 *  Author:
 */

#include "utils.h"
#include "config.h"
#include "GMtypes.h"

/*
* @功能说明: us延时
* @注    意: 会阻塞CPU运行
* @形    参: [in]cnt：us
* @返    回: 无
*/
void delay_us_block(uint16_t cnt)
{
    uint16_t count = cnt * 10;
    while (count--)
    {
        __asm__ __volatile__("nop"); //空指令
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
        __asm__ __volatile__("nop");
    }
}

/*
* @功能说明: 检测：MCU是在多字节存储上，是大端还是小端
* @注    意: 无
* @形    参: 无
* @返    回: 0-小端； 1-大端
*/
uint8_t mcu_big_small_endin_check(void)
{
    uint16_t test_endin = 0x1122;
    uint8_t *ptest_endin = (uint8_t *)&test_endin;

    if(0x22 == ptest_endin[0]){
        // 内存中低地址处保存低字节数据
        return 0;
    }else{
        return 1;
    }
}



/*
* @功能说明:查找二维有序表,通过x查找y
* @注    意:1、二维数据结构(x,y)，①x按照下标数据是从小到大有序的。②y是有序的。
*          2、相邻坐标，采用等比斜率的方式计算。并采用四舍五入。
*          3、不适用于数据量较大的场景，否则效率较低，O(N)。
*          4、(y[i]-y[i-1])/(x[i]-x[i-1]) = (b-y[i-1])/(a-x[i-1])。输入a求b
* @形    参:[in]p_table:只想二维数据结构；
*          [in]table_nums:数据结构数据个数；
*          [in]input_x:通过此值查对应的y值
* @返    回:无
*/
int8_t find_sequential_2dimension(const coordinateXY_node_t *p_table, uint8_t table_nums, uint16_t input_x)
{
    int32_t calculate_value = 0;

    // 采集数值区间校验
    if (input_x <= p_table[0].node_x) {
        return p_table[0].node_y;
    } else if (input_x >= p_table[table_nums-1].node_x) {
        return p_table[table_nums-1].node_y;
    }

    for (uint8_t i = 0; i < table_nums; i++)
    {
        // 寻找临近区间
        if (input_x <= p_table[i].node_x) {
            calculate_value = (int32_t)((int32_t)input_x - p_table[i-1].node_x)*((int32_t)p_table[i].node_y - p_table[i-1].node_y);
            int32_t temp = (int32_t)p_table[i].node_x - p_table[i-1].node_x;
            // 此处扩大10倍提高计算精度
            calculate_value = calculate_value*((int32_t)10)/temp + p_table[i-1].node_y*((int32_t)10);
            // 四舍五入
            temp = 0;
            if (labs(calculate_value)%10 > 5) {
                temp = calculate_value >= 0 ? 1 : -1;
            }
            calculate_value = calculate_value/((int32_t)10) + temp;
            break;
        }
    }
    return (int8_t)calculate_value;
}



// 均值滤波
// 目前支持的数据类型：1byte数据、2byte数据类型
uint16_t filter_avg(filter_ctrl_t *p_ctrl, uint16_t data)
{
    uint16_t filter_value = 0;
    uint16_t pop_data = p_ctrl->p_buff[p_ctrl->w_postion]; //保存即将被丢弃的值

    p_ctrl->p_buff[p_ctrl->w_postion++] = data;
    p_ctrl->total_value += data;

    if (!p_ctrl->is_full && (1 == p_ctrl->w_postion)) {
        // 第1次进入
        p_ctrl->max = data;
        p_ctrl->min = data;
    } else if (data > p_ctrl->max) {
        p_ctrl->max = data;
    } else if (data < p_ctrl->min) {
        p_ctrl->min = data;
    }

    // 当最大/小值被移除之后，需要重新找队列中最大/小值
    if (pop_data == p_ctrl->max) {
        p_ctrl->max = p_ctrl->min;
        for (uint8_t i=0; i < p_ctrl->sizes; i++)
        {
            if (p_ctrl->p_buff[i] > p_ctrl->max) {
                p_ctrl->max = p_ctrl->p_buff[i];
            }
        }
    }
    if (pop_data == p_ctrl->min) {
        p_ctrl->min = p_ctrl->max;
        for (uint8_t i=0; i < p_ctrl->sizes; i++)
        {
            if (p_ctrl->p_buff[i] < p_ctrl->min) {
                p_ctrl->min = p_ctrl->p_buff[i];
            }
        }
    }

    if (p_ctrl->is_full) {
        p_ctrl->total_value -= pop_data;
        filter_value = p_ctrl->total_value - (p_ctrl->min + p_ctrl->max); //减去最大最小值
        filter_value = (filter_value/(p_ctrl->sizes - 2));
    } else {
        filter_value = (p_ctrl->total_value/p_ctrl->w_postion);
    }

    // 缓冲区满了
    if (p_ctrl->w_postion >= p_ctrl->sizes) {
        p_ctrl->is_full = TRUE;
        p_ctrl->w_postion = 0;
    }

    return filter_value;
}




