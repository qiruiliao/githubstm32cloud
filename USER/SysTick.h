#ifndef __SysTick_
#define __SysTick_
#include "stm32f10x.h"
 
 void SysTick_Init(void); 
 extern void Delay_10us(__IO u32 nTime);
 void TimingDelay_Decrement(void);
 extern  int a;
 




#endif
