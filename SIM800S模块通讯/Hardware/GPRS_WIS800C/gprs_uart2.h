#ifndef __gprs_uart2_H
#define __gprs_uart2_H

#include "stm32f10x.h"

extern char gprs_buf[1024];
extern uint8_t usart2_rev_flag,usart2_rev_cnt,usart2_rev_finish;     


void usart2_init(uint32_t baud);                                                //串口2初始化
uint8_t gprs_send_cmd(char *cmd,char *res,uint32_t timeOut,uint8_t retime);     //给模块发送命令函数
void usart2_send_string(unsigned char *str, unsigned short len);               //串口2发送字符串的
void gprs_clear(void);                                                         // 清楚模块的缓存数组
void usart2_interrupt_process(void);                                           //串口2中中断进程


#endif


