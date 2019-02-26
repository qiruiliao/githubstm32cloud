#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "SysTick.h"
#include "led.h"
#include "key.h"
#include "Step_motor.h"
#include "tim6.h"

volatile uint32_t  time = 0; // ms 计时变量 
int main(void)
{
	
    Stepper(512);
    SysTick_Init(); 
	BASIC_TIM_Init();
	//Key_GPIO_Config();
	SetSpeed(20);
	LED_GPIO_Config(); 
   
  while (1)
  {
    
	 step(20,1);
//	  if ( time == 1000 ) /* 1000 * 1 ms = 1s 时间到 */
//    {
//      time = 0;    
//			 LED2(ON); 
//    }        
  }
}
 
