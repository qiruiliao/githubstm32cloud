#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

void systick_init(void);                      // 系统滴答时钟初始化
void SysTickDelayTime_Counter(void);          // 获取节拍

void delay_us(uint32_t us);                   // 微秒延时
void delay_ms(uint32_t ms);                   // 毫秒延时
void delay_s(uint32_t s);                     // 秒延时

#endif 


