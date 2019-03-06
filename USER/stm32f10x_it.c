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
//void TIM3_IRQHandler(void)                                         //TIM3 中断
//{
//   
//    static u16 keyupCnt = 0;                                     //按键弹起后计数值
//	static u16 key_holdon_ms = 0;                               //按下的时长
//	u16 keyUpFlag = TRUE;                                      //按键弹起标志
//	
//    if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)      //检查 TIM3 更新中断发生与否
//    {
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);       //清除 TIM3 更新中断标志
//        if(key_fall_flag == 1)                           //发生按键按下事件
//        {
//            if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 0)  //按键持续按下
//            {
//				
//                if(key_holdon_ms <= 2000)
//                {
//                    key_holdon_ms++;
//                }
//				     //长按
//				else if(key_holdon_ms > 2000)   //按键按下到2000ms就判断长按时间成立，生成长按标志
//                {
//                    key_holdon_ms = 0;	//清除时间单位
//                    short_key_flag = 0; //清短按键标志
//                    key_long_down = 1;  //长按键标志置位
//                    key_fall_flag = 0;  //清按键按下标志
//					keyUpFlag = FALSE;  //标记按下
//					keyupCnt = 0;
//					Direction= !Direction;         //长按改变电机的转动方向
//					LED2(ON);
//                }
//				 //距离上次单击时间在100~500ms之间，则认为发生连击事件
//				if((keyupCnt > 300) && (keyupCnt < 500))
//				{
//					keyupCnt = 0;
//					doubleClick = 1;	//标记发生了连击事件
//					
//				}
//			
//            }
//            else //按键抬起
//            {
//				
//				keyupCnt = 0;
//                if(key_holdon_ms > 50) //按下时间大于50ms，生成单击标志
//                {
//                    key_holdon_ms = 0;
//                    short_key_flag = 1;	//标记短按标志
//                    key_long_down = 0;	//清除长按标志
//                    key_fall_flag = 0;
//					keyupCnt = 0;
//                
//					//距离上次单击时间在100~500ms之间，则认为发生连击事件
//					if(keyupCnt>100 && keyupCnt<500)
//					{ 
//					   doubleClick = TRUE;
//					   short_key_flag=0;
//					} 
//					keyUpFlag = TRUE;//单击抬起按键后，生成按键抬起标志 
//			  }
//                else  //按键持续时间小于50ms，忽略
//                {
//                    key_holdon_ms = 0;//按键按下时间的位
//                    short_key_flag = 0;//短按
//                    key_long_down = 0;//长按标志
//                    key_fall_flag = 0;//按键按下标志
//					keyupCnt = 0;
//                }
//				
//            }

//        }

//        if(keyUpFlag)                     //单击抬起后，启动计数，计数到500ms
//            keyupCnt++;

//        if(keyupCnt > 500)
//        {
//            keyupCnt = 0;
//            keyUpFlag = FALSE;//标记为弹起
//        }

//    }
//}

void EXTI2_IRQHandler(void)
{     SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
	  Delay_10us(2000);
    if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2) == 0)         //按键 KEY2
    {
        key_fall_flag = 1; 
        key_long_down=1	;	
		//生成按键按下标志
    }
	else
   {
      short_key_flag=1;
   
   }
		

    EXTI_ClearITPendingBit(EXTI_Line2);                    //清除 LINE2 上的中断标志位
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
