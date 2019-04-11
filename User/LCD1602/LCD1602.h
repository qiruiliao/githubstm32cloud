#ifndef                _LCD1602_H
#define                _LCD1602_H
#include "stm32f10x.h"
//PD15-PD8 ��Ӧ LCD1602��D7-D0  
//PC0			 RS
//PC1			 WR
//PC2			 E										
//LCD1602 ������ ״̬  

#define Set_RS()    GPIO_SetBits(GPIOC,GPIO_Pin_0);    // ����
#define Reset_RS()  GPIO_ResetBits(GPIOC,GPIO_Pin_0);  // ���� ״̬

#define Set_RW()    GPIO_SetBits(GPIOC,GPIO_Pin_1);	    // ��
#define Reset_RW()  GPIO_ResetBits(GPIOC,GPIO_Pin_1);   // д

#define Set_E()     GPIO_SetBits(GPIOC,GPIO_Pin_2);	    //ʹ��
#define Reset_E()   GPIO_ResetBits(GPIOC,GPIO_Pin_2);   //ʧ��

void LCD_RCC_Config(void);
void LCD_GPIO_Config(void);
void  Busy_Wait(void);
void LCD_Write_Cmd(uint8_t Cmd);
void LCD_Write_Data(uint8_t Data);
void LCD_Write_String(uint8_t cmd,uint8_t* p);  
void LCD1602_Init(void);
void Delay(uint32_t t);
void lcd1602_write_pic(uint8_t add,uint8_t *pic_num);     //��ʾ�������Ҽ�ͷ��

#endif


