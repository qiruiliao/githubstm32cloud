#include "led.h"
void LED_GPIO_Config(void)   
{          
     /*定义一个 GPIO_InitTypeDef 类型的结构体*/  
     GPIO_InitTypeDef GPIO_InitStructure;   
  
     /*开启 GPIOB 的外设时钟*/  
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);    
                                                                   
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
;    
    
     /*设置引脚模式为通用推挽输出*/  
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      
    
      /*设置引脚速率为 50MHz */      
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
    
      /*调用库函数，初始化 GPIOC*/  
	 GPIO_Init(GPIOE, &GPIO_InitStructure); 
	 
    /* 关闭所有 led 灯 */  
	 GPIO_SetBits(GPIOE, GPIO_Pin_5);
}
