#include "led.h"
void LED_GPIO_Config(void)   
{          
     /*����һ�� GPIO_InitTypeDef ���͵Ľṹ��*/  
     GPIO_InitTypeDef GPIO_InitStructure;   
  
     /*���� GPIOB ������ʱ��*/  
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);    
                                                                   
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
;    
    
     /*��������ģʽΪͨ���������*/  
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      
    
      /*������������Ϊ 50MHz */      
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
    
      /*���ÿ⺯������ʼ�� GPIOC*/  
	 GPIO_Init(GPIOE, &GPIO_InitStructure); 
	 
    /* �ر����� led �� */  
	 GPIO_SetBits(GPIOE, GPIO_Pin_5);
}
