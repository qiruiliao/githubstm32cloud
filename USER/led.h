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
				  
				  
				  
				  /* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //输出为高电平		
#define digitalLo(p,i)		 {p->BRR=i;}	 //输出低电平
#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态
  

#define LED2_TOGGLE		 digitalToggle(GPIOE,GPIO_Pin_5)
#define LED2_OFF		   digitalHi(GPIOE,GPIO_Pin_5)
#define LED2_ON			   digitalLo(GPIOE,GPIO_Pin_5)

  void LED_GPIO_Config(void);   
    
 #endif /* __LED_H */   
