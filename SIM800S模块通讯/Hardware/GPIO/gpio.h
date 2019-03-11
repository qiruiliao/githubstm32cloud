#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"
// 板块电源的使能脚，用于模块的开关机和复位
#define PEN_ON     GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define PEN_OFF    GPIO_ResetBits(GPIOB,GPIO_Pin_7)

#define LED_OFF    GPIO_SetBits(GPIOB,GPIO_Pin_5)             // 熄灭LED      
#define LED_ON     GPIO_ResetBits(GPIOB,GPIO_Pin_5)           // 点亮LED 

void gpio_config(void);

#endif


