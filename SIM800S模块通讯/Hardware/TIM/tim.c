#include "tim.h"
#include "gprs_uart2.h"
#include "gprs_at.h"

/**
  * @brief  定时器3参数设置    
  * @param  无
  * @retval 无
	* @note   1ms中断一次
  */
void tim3_parameter_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);                           // 使能定时器3时钟
	
	/*定时器参数设置*/
	TIM_TimeBaseStructure.TIM_Period = 999;					                      // 设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 71;					                  // 设置用来作为TIMx时钟频率除数的预分频值(72KHz的计数频率)
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		                 // 设置时钟分割:不分割，选择默认TDTS = TIM_CKD_DIV1
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	                 // TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE );                                 // 开启定时器3中断
	TIM_Cmd(TIM3, ENABLE);  									                // 开启定时器3	
}	

/**
  * @brief  定时器3中断向量初始化配置   
  * @param  无
  * @retval 无
  */
void tim3_nvic_config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;                        		        // 定义NVIC初始化结构体
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);            // 设置中断优先级组为2，先占优先级和从优先级各两位(可设0～3)

	/*定时器3中断向量配置*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;				      		 // tim3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  	      	 	// 设置抢占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			     	   // 设置响应优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				      	  // 使能IRQ通道
	NVIC_Init(&NVIC_InitStructure); 	
}

/**
  * @brief  定时器3初始化  
  * @param  无
  * @retval 无
  */
void tim3_init(void)
{
  tim3_parameter_init();
  tim3_nvic_config();
}

/**
  * @brief  定时器中断处理 
  * @param  无
  * @retval 无
  */
void tim3_interrupt_process(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)       // 检查tim3更新中断发生与否
	{	
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );        // 清除tim3更新中断标志
		/* 串口接收处理 */
		if(usart2_rev_flag)                                 // 如果 usart2 接收数据标志为1
	     {		 					      
		    usart2_rev_cnt++;                               // usart2 接收计数	
		  if(usart2_rev_cnt >= 5)                          // 当超过 5ms 未接收到数据，则认为数据接收完成。
		  {
			usart2_rev_finish = 1;
			usart2_rev_flag = 0;
			usart2_rev_cnt = 0;
		  }
	     }
	}
}
