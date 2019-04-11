#ifndef                _LCD1602_H
#define                _LCD1602_H
#include "stm32f10x.h"
//PD15-PD8 对应 LCD1602的D7-D0  
//PC0			 RS
//PC1			 WR
//PC2			 E										
//LCD1602 的命令 状态  

#define Set_RS()    GPIO_SetBits(GPIOC,GPIO_Pin_0);    // 数据
#define Reset_RS()  GPIO_ResetBits(GPIOC,GPIO_Pin_0);  // 命令 状态

#define Set_RW()    GPIO_SetBits(GPIOC,GPIO_Pin_1);	    // 读
#define Reset_RW()  GPIO_ResetBits(GPIOC,GPIO_Pin_1);   // 写

#define Set_E()     GPIO_SetBits(GPIOC,GPIO_Pin_2);	    //使能
#define Reset_E()   GPIO_ResetBits(GPIOC,GPIO_Pin_2);   //失能

void LCD_RCC_Config(void);
void LCD_GPIO_Config(void);
void  Busy_Wait(void);
void LCD_Write_Cmd(uint8_t Cmd);
void LCD_Write_Data(uint8_t Data);
void LCD_Write_String(uint8_t cmd,uint8_t* p);  
void LCD1602_Init(void);
void Delay(uint32_t t);
void lcd1602_write_pic(uint8_t add,uint8_t *pic_num);     //显示上下左右箭头的

#endif


