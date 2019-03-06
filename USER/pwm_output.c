
#include "pwm_output.h"

 void TIM3_GPIO_Config(void )
 {
       //PA6 PA7 PB0 PB1
	  GPIO_InitTypeDef GPIO_InitStructure;                       //端口配置结构体
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_0|GPIO_Pin_1 ;        
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //推挽输出
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      //口线翻转速度为50MHz
	  GPIO_Init(GPIOD, &GPIO_InitStructure);   
      GPIO_Init(GPIOB, &GPIO_InitStructure);	                  //初始化端 
 }
  void TIM3_Mode_Config(void)   
  {   
      TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   
      TIM_OCInitTypeDef  TIM_OCInitStructure;   
    
      /* PWM 信号电平跳变值 */  
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
   //当定时器从 0 计数到 999，即为 1000 次，为一个定时周期           
    TIM_TimeBaseStructure.TIM_Period = 999;
 
     //设置预分频：不预分频，即为 36MHz      
   TIM_TimeBaseStructure.TIM_Prescaler = 0;
       
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;  //设置时钟分频系数：不分频   
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式   
    
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);   
   
    /* PWM1 Mode configuration: Channel1 */  
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;   //配置为 PWM 模式 1   
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 

    //设置跳变值，当计数器计数到这个值时，电平发生跳变   
    TIM_OCInitStructure.TIM_Pulse = CCR1_Val; 
 
   //当定时器计数值小于 CCR1_Val 时为高电平    
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   
  
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);   //使能通道 1   
   TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);   
    
    /* PWM1 Mode configuration: Channel2 */  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
 
   //设置通道 2 的电平跳变值，输出另外一个占空比的 PWM
    TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
       
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);    //使能通道 2   
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);   
    
  /* PWM1 Mode configuration: Channel3 */  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
 
  //设置通道 3 的电平跳变值，输出另外一个占空比的 PWM 
    TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
     
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);   //使能通道 3   
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);   
    
   /* PWM1 Mode configuration: Channel4 */  
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
 
  //设置通道 4 的电平跳变值，输出另外一个占空比的 PWM   
    TIM_OCInitStructure.TIM_Pulse = CCR4_Val;   
   TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //使能通道 4    
   TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);   
    
   TIM_ARRPreloadConfig(TIM3, ENABLE);   
   
   /* TIM3 enable counter */  
    TIM_Cmd(TIM3, ENABLE);   //使能定时器 3    
}


void TIM3_PWM_Init(void)   
 {   
     TIM3_GPIO_Config();   
     TIM3_Mode_Config();    
 }  
