#include "systick.h"
uint32_t SysTickDelayTime;

/**
  * @brief  ��ʼ��ϵͳ�δ�ʱ��SysTick      
  * @param  ��
  * @retval ��
	* @note   1)��SystemFrequency / 1000		1ms�ж�һ��
  *			    2)��SystemFrequency / 100000	10us�ж�һ��
  *			    3)��SystemFrequency / 1000000	1us�ж�һ��
  *         (SystemFrequency / Value)��ϵͳʱ�ӽ����ж�һ��
  */
void systick_init(void)
{
	while(SysTick_Config(SystemCoreClock/1000));	    // ��ʼ����ʹ��ϵͳ�δ�ʱ��,����1��ʾ��������̫��			 
	
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;		   // ʹ�ܵδ�ʱ�� 
	
}

/**
  * @brief  ΢����ʱ      
  * @param  ��Ҫ��ʱ��ʱ�� us
  * @retval ��
  */
void delay_us(uint32_t us)
{ 
	SysTickDelayTime = us/1000;		 
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;   	         // ʹ�ܵδ�ʱ�� 
	while(SysTickDelayTime != 0);					        // �ȴ���ʱʱ�䵽
}

/**
  * @brief  ������ʱ      
  * @param  ��Ҫ��ʱ��ʱ�� ms
  * @retval ��
  */
void delay_ms(uint32_t ms)
{ 
	SysTickDelayTime = ms;		 
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;	              // ʹ�ܵδ�ʱ�� 
	while(SysTickDelayTime != 0);					         // �ȴ���ʱʱ�䵽
}

/**
  * @brief  ����ʱ      
  * @param  ��Ҫ��ʱ��ʱ�� s
  * @retval ��
  */
void delay_s(uint32_t s)
{ 
	SysTickDelayTime = s*1000;		 
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;	          // ʹ�ܵδ�ʱ�� 
	while(SysTickDelayTime != 0);					     // �ȴ���ʱʱ�䵽
}

/**
  * @brief  ��ȡ���ĺ���      
  * @param  ��
  * @retval ��
  * @note   ��SysTick�жϳ���SysTick_Handler()����(stm32f10x_it.c)
  */
void SysTickDelayTime_Counter(void)                //systick���жϵ��ú���
{
	if(SysTickDelayTime > 0)
	{ 
		SysTickDelayTime--;
	}
}

