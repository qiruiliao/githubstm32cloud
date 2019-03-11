#ifndef __pc_usart1_H
#define __pc_usart1_H

#include "stm32f10x.h"
#include <stdio.h>


void usart1_init(uint32_t baud);                                // 串口1初始化 MCU与PC通信
void usart1_interrupt_process(void);

#endif   
