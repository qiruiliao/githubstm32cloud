#include "tim.h"
#include "gprs_uart2.h"
#include "gprs_at.h"

/**
  * @brief  ��ʱ��3��������    
  * @param  ��
  * @retval ��
	* @note   1ms�ж�һ��
  */
void tim3_parameter_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);                           // ʹ�ܶ�ʱ��3ʱ��
	
	/*��ʱ����������*/
	TIM_TimeBaseStructure.TIM_Period = 999;					                      // ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 71;					                  // ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ(72KHz�ļ���Ƶ��)
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		                 // ����ʱ�ӷָ�:���ָѡ��Ĭ��TDTS = TIM_CKD_DIV1
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	                 // TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE );                                 // ������ʱ��3�ж�
	TIM_Cmd(TIM3, ENABLE);  									                // ������ʱ��3	
}	

/**
  * @brief  ��ʱ��3�ж�������ʼ������   
  * @param  ��
  * @retval ��
  */
void tim3_nvic_config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;                        		        // ����NVIC��ʼ���ṹ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);            // �����ж����ȼ���Ϊ2����ռ���ȼ��ʹ����ȼ�����λ(����0��3)

	/*��ʱ��3�ж���������*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;				      		 // tim3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  	      	 	// ������ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			     	   // ������Ӧ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				      	  // ʹ��IRQͨ��
	NVIC_Init(&NVIC_InitStructure); 	
}

/**
  * @brief  ��ʱ��3��ʼ��  
  * @param  ��
  * @retval ��
  */
void tim3_init(void)
{
  tim3_parameter_init();
  tim3_nvic_config();
}

/**
  * @brief  ��ʱ���жϴ��� 
  * @param  ��
  * @retval ��
  */
void tim3_interrupt_process(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)       // ���tim3�����жϷ������
	{	
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );        // ���tim3�����жϱ�־
		/* ���ڽ��մ��� */
		if(usart2_rev_flag)                                 // ��� usart2 �������ݱ�־Ϊ1
	     {		 					      
		    usart2_rev_cnt++;                               // usart2 ���ռ���	
		  if(usart2_rev_cnt >= 5)                          // ������ 5ms δ���յ����ݣ�����Ϊ���ݽ�����ɡ�
		  {
			usart2_rev_finish = 1;
			usart2_rev_flag = 0;
			usart2_rev_cnt = 0;
		  }
	     }
	}
}
