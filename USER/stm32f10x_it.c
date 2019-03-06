/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
//#include "exti.h"
#include "led.h"
#include "key.h"
#include "tim3.h"

#include "SysTick.h"
#include "motor.h"

#define  FALSE 	0
#define  TRUE  	1

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{     
	 
	TimingDelay_Decrement(); 
	   
}
//void TIM3_IRQHandler(void)                                         //TIM3 �ж�
//{
//   
//    static u16 keyupCnt = 0;                                     //������������ֵ
//	static u16 key_holdon_ms = 0;                               //���µ�ʱ��
//	u16 keyUpFlag = TRUE;                                      //���������־
//	
//    if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)      //��� TIM3 �����жϷ������
//    {
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);       //��� TIM3 �����жϱ�־
//        if(key_fall_flag == 1)                           //�������������¼�
//        {
//            if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 0)  //������������
//            {
//				
//                if(key_holdon_ms <= 2000)
//                {
//                    key_holdon_ms++;
//                }
//				     //����
//				else if(key_holdon_ms > 2000)   //�������µ�2000ms���жϳ���ʱ����������ɳ�����־
//                {
//                    key_holdon_ms = 0;	//���ʱ�䵥λ
//                    short_key_flag = 0; //��̰�����־
//                    key_long_down = 1;  //��������־��λ
//                    key_fall_flag = 0;  //�尴�����±�־
//					keyUpFlag = FALSE;  //��ǰ���
//					keyupCnt = 0;
//					Direction= !Direction;         //�����ı�����ת������
//					LED2(ON);
//                }
//				 //�����ϴε���ʱ����100~500ms֮�䣬����Ϊ���������¼�
//				if((keyupCnt > 300) && (keyupCnt < 500))
//				{
//					keyupCnt = 0;
//					doubleClick = 1;	//��Ƿ����������¼�
//					
//				}
//			
//            }
//            else //����̧��
//            {
//				
//				keyupCnt = 0;
//                if(key_holdon_ms > 50) //����ʱ�����50ms�����ɵ�����־
//                {
//                    key_holdon_ms = 0;
//                    short_key_flag = 1;	//��Ƕ̰���־
//                    key_long_down = 0;	//���������־
//                    key_fall_flag = 0;
//					keyupCnt = 0;
//                
//					//�����ϴε���ʱ����100~500ms֮�䣬����Ϊ���������¼�
//					if(keyupCnt>100 && keyupCnt<500)
//					{ 
//					   doubleClick = TRUE;
//					   short_key_flag=0;
//					} 
//					keyUpFlag = TRUE;//����̧�𰴼������ɰ���̧���־ 
//			  }
//                else  //��������ʱ��С��50ms������
//                {
//                    key_holdon_ms = 0;//��������ʱ���λ
//                    short_key_flag = 0;//�̰�
//                    key_long_down = 0;//������־
//                    key_fall_flag = 0;//�������±�־
//					keyupCnt = 0;
//                }
//				
//            }

//        }

//        if(keyUpFlag)                     //����̧�������������������500ms
//            keyupCnt++;

//        if(keyupCnt > 500)
//        {
//            keyupCnt = 0;
//            keyUpFlag = FALSE;//���Ϊ����
//        }

//    }
//}

void EXTI2_IRQHandler(void)
{     SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
	  Delay_10us(2000);
    if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 0)         //���� KEY2
    {
        key_fall_flag = 1; 
        key_long_down=1	;	
		//���ɰ������±�־
    }
	else
   {
      short_key_flag=1;
   
   }
		

    EXTI_ClearITPendingBit(EXTI_Line2);                    //��� LINE2 �ϵ��жϱ�־λ
}



/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
