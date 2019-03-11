/********************************************************************************
* @file    			gpio.c
* @function     GPIO���� 				  				
* @brief 				��3.5.0�汾�⽨�Ĺ���ģ��             
* @attention		�����̽���Ϊ�ο�������ʵ�ʿ����������ʵ���������	
* @version 			V1.0		
* @company  		�����з�˼�����ӿƼ����޹�˾
* @website  		https://freestrong.taobao.com
* @Author       WisBarry
* @date    			2018-11-10	
********************************************************************************/

#include "gpio.h"

/**
  * @brief  gpio_config
  * @param  ���� GPIO ����
  * @retval ��
	* @note   PENΪGPRS���İ�ʹ�����ţ�LEDΪ��Ƭ���ϵ�LED��
  */
void gpio_config(void)
{		
	GPIO_InitTypeDef  GPIO_InitStructure;		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);	       // ʹ��GPIO
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8|GPIO_Pin_5;	          // ѡ��Ҫ��ʼ����GPIOB����PB5��PB8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	         // �������Ź���ģʽΪͨ��������� 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	        // ������������������Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);		
	PEN_OFF;                                                    
	LED_OFF;
}
