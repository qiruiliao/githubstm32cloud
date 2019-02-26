#include "SysTick.h"
#include "stm32f10x.h"
static __IO u32 TimingDelay;
 int a;
 /*����SysTick��ʱ��*/
 /*SysTick_Config������core_cm3.h�У���stm32f10x.h�а���core_cm3.h��SysTick����include "stm32f10x.h"*/
void SysTick_Init(void)   
  {   
     
     //���óɹ����ȹرռ�ʱ�������������ѭ���ȴ�
    if (SysTick_Config(SystemCoreClock / 100000))       
     {    
       /* Capture error */    
         while (1);   
      }   
                                   
      SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;   // �ȹرյδ�ʱ������ʹ��ʱ������ 
   }
  
  void Delay_10us(__IO u32 nTime)
  {   
	  TimingDelay=nTime;
	  SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;  //������ʱ��
	  while(TimingDelay!=0);                     //ֱ������0����ʱ����
   } 
   
  void TimingDelay_Decrement(void) 
  {
   if (TimingDelay != 0x00)   
   {    
      TimingDelay--;
	   a++;
  }
  }

  
  
  