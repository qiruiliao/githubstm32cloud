#include "SysTick.h"
#include "stm32f10x.h"
static __IO u32 TimingDelay;
 int a;
 /*配置SysTick定时器*/
 /*SysTick_Config函数在core_cm3.h中，因stm32f10x.h中包含core_cm3.h和SysTick，因include "stm32f10x.h"*/
void SysTick_Init(void)   
  {   
     
     //配置成功，先关闭计时器，否则进入死循环等待
    if (SysTick_Config(SystemCoreClock / 100000))       
     {    
       /* Capture error */    
         while (1);   
      }   
                                   
      SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;   // 先关闭滴答定时器，待使用时再启动 
   }
  
  void Delay_10us(__IO u32 nTime)
  {   
	  TimingDelay=nTime;
	  SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;  //开启定时器
	  while(TimingDelay!=0);                     //直到等于0，延时结束
   } 
   
  void TimingDelay_Decrement(void) 
  {
   if (TimingDelay != 0x00)   
   {    
      TimingDelay--;
	   a++;
  }
  }

  
  
  