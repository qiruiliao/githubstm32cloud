#include "key.h"
#include "SysTick.h"



  void Key_GPIO_Config(void)
{        //PE3
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*开启按键端口的时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3; 
	// 设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
}


 u8 Key_Scan(GPIO_TypeDef* GPIOX,u16 GPIO_Pin)
  {
	     /*检测是否有按键按下 */  
             
         
                  if(GPIO_ReadInputDataBit(GPIOX,GPIO_Pin) == KEY_ON )     
                       
					   Delay_10us(200000);
			        if(GPIO_ReadInputDataBit(GPIOX,GPIO_Pin) == KEY_ON )
					{						
                       /*等待按键释放 */      
					   return  KEY_ON;
                    }
				   		   
                   else  
			      {  
					return KEY_OFF;
                    	
			      }				  
}

