 #include "exti.h"
  static void NVIC_Configuration(void) 
 {   
    NVIC_InitTypeDef NVIC_InitStructure;   
      
     //组别设置为第一组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    

   /* 配置 P[A|B|C|D|E]2 为中断源 */  
    NVIC_InitStructure.NVIC_IRQChannel =EXTI2_IRQn;   
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
    NVIC_Init(&NVIC_InitStructure);   
  }
 void EXTI_PE2_Config(void)   
  {   
     GPIO_InitTypeDef GPIO_InitStructure;    
     EXTI_InitTypeDef EXTI_InitStructure;   
        //启用外部PE2时钟和复用时钟  
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO,ENABLE);   
           /* config the NVIC(PE2) */  
     NVIC_Configuration();   
          /* EXTI line gpio config(PE2) */       
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;          
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_Init(GPIOE, &GPIO_InitStructure);   
    
	     /* EXTI line(PE2) mode config */  
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);    
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;   
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;   
	EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Falling; //下降沿中断

	EXTI_InitStructure.EXTI_LineCmd = ENABLE;   
	EXTI_Init(&EXTI_InitStructure);    
  }  
  