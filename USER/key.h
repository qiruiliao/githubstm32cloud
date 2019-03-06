#ifndef __KEY_H  
#define __KEY_H  

#include "stm32f10x.h"
#define KEY4		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4
#define KEY2 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)	//PE3 
#define KEY3 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) //PE2
#define KEY1 	    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)	//PA0



//������ť���µ�ֵ
#define KEY0_PRES 	1           
#define KEY1_PRES	2
#define KEY2_PRES	3
#define KEY4_PRES   4

extern u8 key_fall_flag ;//�������±�־



void KEY_Init(void);	//IO��ʼ��
u8 KEY_Scan(u8);  		//����ɨ�躯��	
void EXTIX_Init(void);
void TIM3_Int_Init(u16 arr, u16 psc);
#endif
