#ifndef __gprs_uart2_H
#define __gprs_uart2_H

#include "stm32f10x.h"

extern char gprs_buf[1024];
extern uint8_t usart2_rev_flag,usart2_rev_cnt,usart2_rev_finish;     


void usart2_init(uint32_t baud);                                                //����2��ʼ��
uint8_t gprs_send_cmd(char *cmd,char *res,uint32_t timeOut,uint8_t retime);     //��ģ�鷢�������
void usart2_send_string(unsigned char *str, unsigned short len);               //����2�����ַ�����
void gprs_clear(void);                                                         // ���ģ��Ļ�������
void usart2_interrupt_process(void);                                           //����2���жϽ���


#endif


