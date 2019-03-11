/********************************************************************************
* @file    			gpio.c
* @function     GPIO配置 				  				
* @brief 				用3.5.0版本库建的工程模板             
* @attention		该例程仅作为参考，如需实际开发，请根据实际需求更改	
* @version 			V1.0		
* @company  		深圳市飞思创电子科技有限公司
* @website  		https://freestrong.taobao.com
* @Author       WisBarry
* @date    			2018-11-10	
********************************************************************************/

#include "gpio.h"

/**
  * @brief  gpio_config
  * @param  配置 GPIO 引脚
  * @retval 无
	* @note   PEN为GPRS核心板使能引脚，LED为单片机上的LED灯
  */
void gpio_config(void)
{		
	GPIO_InitTypeDef  GPIO_InitStructure;		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);	       // 使能GPIO
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8|GPIO_Pin_5;	          // 选择要初始化的GPIOB引脚PB5，PB8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	         // 设置引脚工作模式为通用推挽输出 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	        // 设置引脚输出最大速率为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);		
	PEN_OFF;                                                    
	LED_OFF;
}
