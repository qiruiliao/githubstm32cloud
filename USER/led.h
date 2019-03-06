#ifndef __LED_H   
#define __LED_H   
   
 #include "stm32f10x.h"   
    
  
   /*���ݵ�·ͼ�˿ڵ�ƽΪ��led��*/
  #define ON  0          //��LED
  #define OFF 1          //�ر�LED
 //���κ꣬��������������һ��ʹ��   
  #define LED2(a) if (a) \
                      GPIO_SetBits(GPIOE,GPIO_Pin_5); \
                  else   \
                     GPIO_ResetBits(GPIOE,GPIO_Pin_5); 
  #define LED3(a) if (a) \
	                 GPIO_SetBits(GPIOB,GPIO_Pin_5); \
                  else   \
                     GPIO_ResetBits(GPIOB,GPIO_Pin_5); 
				  
				  
				  
				  /* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //���Ϊ�ߵ�ƽ		
#define digitalLo(p,i)		 {p->BRR=i;}	 //����͵�ƽ
#define digitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬
  

#define LED2_TOGGLE		 digitalToggle(GPIOE,GPIO_Pin_5)
#define LED2_OFF		   digitalHi(GPIOE,GPIO_Pin_5)
#define LED2_ON			   digitalLo(GPIOE,GPIO_Pin_5)

  void LED_GPIO_Config(void);   
    
 #endif /* __LED_H */   
