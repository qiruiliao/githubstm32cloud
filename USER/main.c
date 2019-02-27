#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "misc.h"
#include "SysTick.h"
#include "key.h"
#include "exti.h"
#include "tim6.h"
#include "motor.h"
#include "led.h"
#include "pwm_output.h"

volatile uint32_t  time = 0; // ms 计时变量 
int main(void)
{
	
    
   SysTick_Init();
   Key_GPIO_Config();
   EXTI_PE2_Config();
	
   Motor_GPIO_Config();
   LED_GPIO_Config(); 
   TIM3_PWM_Init();
	
	
   
  while (1)
  {   
	  	  if(b==1)
				  nrun();
	           else 
			      prun();  			
		}	 
   
  }
 
