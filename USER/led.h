#ifndef __LED_H   
#define __LED_H   
   
 #include "stm32f10x.h"   
    
  
   /*根据电路图端口电平为低led亮*/
  #define ON  0          //打开LED
  #define OFF 1          //关闭LED
 //带参宏，可以像内联函数一样使用   
  #define LED2(a) if (a) \
                      GPIO_SetBits(GPIOE,GPIO_Pin_5); \
                  else   \
                     GPIO_ResetBits(GPIOE,GPIO_Pin_5); 
  #define LED3(a) if (a) \
	                 GPIO_SetBits(GPIOB,GPIO_Pin_5); \
                  else   \
                     GPIO_ResetBits(GPIOB,GPIO_Pin_5); 
  
  void LED_GPIO_Config(void);   
    
 #endif /* __LED_H */   
