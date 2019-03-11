#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"
// ����Դ��ʹ�ܽţ�����ģ��Ŀ��ػ��͸�λ
#define PEN_ON     GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define PEN_OFF    GPIO_ResetBits(GPIOB,GPIO_Pin_7)

#define LED_OFF    GPIO_SetBits(GPIOB,GPIO_Pin_5)             // Ϩ��LED      
#define LED_ON     GPIO_ResetBits(GPIOB,GPIO_Pin_5)           // ����LED 

void gpio_config(void);

#endif


