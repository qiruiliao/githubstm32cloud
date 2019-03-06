
#include "pwm_output.h"

 void TIM3_GPIO_Config(void )
 {
       //PA6 PA7 PB0 PB1
	  GPIO_InitTypeDef GPIO_InitStructure;                       //�˿����ýṹ��
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_0|GPIO_Pin_1 ;        
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //�������
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      //���߷�ת�ٶ�Ϊ50MHz
	  GPIO_Init(GPIOD, &GPIO_InitStructure);   
      GPIO_Init(GPIOB, &GPIO_InitStructure);	                  //��ʼ���� 
 }
  void TIM3_Mode_Config(void)   
  {   
      TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   
      TIM_OCInitTypeDef  TIM_OCInitStructure;   
    
      /* PWM �źŵ�ƽ����ֵ */  
      u16 CCR1_Val = 500;           
      u16 CCR2_Val = 375;   
      u16 CCR3_Val = 250;   
      u16 CCR4_Val = 125;   
    
  /* -----------------------------------------------------------------------  
      TIM3 Configuration: generate 4 PWM signals with 4 different duty cycles:  
      TIM3CLK = 36 MHz, Prescaler = 0x0, TIM3 counter clock = 36 MHz  
      TIM3 ARR Register = 999 => TIM3 Frequency = TIM3 counter clock/(ARR + 1)  
      TIM3 Frequency = 36 KHz.  
      TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 = 50%  
      TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 = 37.5%  
      TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%  
      TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR)* 100 = 12.5%  
   ----------------------------------------------------------------------- */  
   
   /* Time base configuration */
   //����ʱ���� 0 ������ 999����Ϊ 1000 �Σ�Ϊһ����ʱ����           
    TIM_TimeBaseStructure.TIM_Period = 999;
 
     //����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ 36MHz      
   TIM_TimeBaseStructure.TIM_Prescaler = 0;
       
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;  //����ʱ�ӷ�Ƶϵ��������Ƶ   
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ   
    
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);   
   
    /* PWM1 Mode configuration: Channel1 */  
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;   //����Ϊ PWM ģʽ 1   
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 

    //��������ֵ�������������������ֵʱ����ƽ��������   
    TIM_OCInitStructure.TIM_Pulse = CCR1_Val; 
 
   //����ʱ������ֵС�� CCR1_Val ʱΪ�ߵ�ƽ    
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   
  
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);   //ʹ��ͨ�� 1   
   TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);   
    
    /* PWM1 Mode configuration: Channel2 */  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
 
   //����ͨ�� 2 �ĵ�ƽ����ֵ���������һ��ռ�ձȵ� PWM
    TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
       
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);    //ʹ��ͨ�� 2   
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);   
    
  /* PWM1 Mode configuration: Channel3 */  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
 
  //����ͨ�� 3 �ĵ�ƽ����ֵ���������һ��ռ�ձȵ� PWM 
    TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
     
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);   //ʹ��ͨ�� 3   
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);   
    
   /* PWM1 Mode configuration: Channel4 */  
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
 
  //����ͨ�� 4 �ĵ�ƽ����ֵ���������һ��ռ�ձȵ� PWM   
    TIM_OCInitStructure.TIM_Pulse = CCR4_Val;   
   TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //ʹ��ͨ�� 4    
   TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);   
    
   TIM_ARRPreloadConfig(TIM3, ENABLE);   
   
   /* TIM3 enable counter */  
    TIM_Cmd(TIM3, ENABLE);   //ʹ�ܶ�ʱ�� 3    
}


void TIM3_PWM_Init(void)   
 {   
     TIM3_GPIO_Config();   
     TIM3_Mode_Config();    
 }  
