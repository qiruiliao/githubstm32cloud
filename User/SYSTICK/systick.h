#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

void systick_init(void);                      // ϵͳ�δ�ʱ�ӳ�ʼ��
void SysTickDelayTime_Counter(void);          // ��ȡ����

void delay_us(uint32_t us);                   // ΢����ʱ
void delay_ms(uint32_t ms);                   // ������ʱ
void delay_s(uint32_t s);                     // ����ʱ

#endif 


