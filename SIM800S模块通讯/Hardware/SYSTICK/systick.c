#include "systick.h"
uint32_t SysTickDelayTime;

/**
  * @brief  初始化系统滴答时钟SysTick      
  * @param  无
  * @retval 无
	* @note   1)、SystemFrequency / 1000		1ms中断一次
  *			    2)、SystemFrequency / 100000	10us中断一次
  *			    3)、SystemFrequency / 1000000	1us中断一次
  *         (SystemFrequency / Value)个系统时钟节拍中断一次
  */
void systick_init(void)
{
	while(SysTick_Config(SystemCoreClock/1000));	    // 初始化并使能系统滴答时钟,返回1表示计数设置太大			 
	
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;		   // 使能滴答定时器 
	
}

/**
  * @brief  微秒延时      
  * @param  需要延时的时间 us
  * @retval 无
  */
void delay_us(uint32_t us)
{ 
	SysTickDelayTime = us/1000;		 
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;   	         // 使能滴答定时器 
	while(SysTickDelayTime != 0);					        // 等待延时时间到
}

/**
  * @brief  毫秒延时      
  * @param  需要延时的时间 ms
  * @retval 无
  */
void delay_ms(uint32_t ms)
{ 
	SysTickDelayTime = ms;		 
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;	              // 使能滴答定时器 
	while(SysTickDelayTime != 0);					         // 等待延时时间到
}

/**
  * @brief  秒延时      
  * @param  需要延时的时间 s
  * @retval 无
  */
void delay_s(uint32_t s)
{ 
	SysTickDelayTime = s*1000;		 
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;	          // 使能滴答定时器 
	while(SysTickDelayTime != 0);					     // 等待延时时间到
}

/**
  * @brief  获取节拍函数      
  * @param  无
  * @retval 无
  * @note   在SysTick中断程序SysTick_Handler()调用(stm32f10x_it.c)
  */
void SysTickDelayTime_Counter(void)                //systick的中断调用函数
{
	if(SysTickDelayTime > 0)
	{ 
		SysTickDelayTime--;
	}
}

