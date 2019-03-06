#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "misc.h"
#include "SysTick.h"
#include "key.h"
#include "tim3.h"
#include "motor.h"
#include "led.h"
//#include "pwm_output.h"

extern u16 short_key_flag;//短按标志位
extern u16 key_long_down;//长按标志位
//extern u16 doubleClick;//连击标志
extern u8 key_fall_flag;
extern _Bool Direction;
int8_t Key_value;
int Speed_value=1000;      //初始速度
int i;
int main(void)
{ 
   SysTick_Init();
   Motor_GPIO_Config();
    KEY_Init();
	LED_GPIO_Config();
    EXTIX_Init();
    LED_GPIO_Config(); 
	LED2(ON);
	LED3(OFF);
	//TIM3_Int_Init(10-1,1000-1);
    //TIM3_PWM_Init();
	
	
   
  while (1)  
  {     
////	    Key_value=KEY_Scan(1);
//	    if(short_key_flag==1)
//		{
//		   LED2(ON);
//			LED3(OFF);
//		  Speed_value=Speed_value-100;
//			if(Speed_value<200)
//			{
//			    
//				Speed_value=1000;
//				 
//			}  
//		}
//		if(key_long_down==1)
//		{
//		  Direction=!Direction;
//			LED3(ON);
//		}
		for(i=0;i<50;i++)
		   {
		    Speed_value=Speed_value-100;
			   
		if(Speed_value<200)
		   {  
			  Speed_value=1000;
		      Direction=!Direction;
			}  
		}
	    motorNcircle(8,Direction,Speed_value);
  
	   }

} 
