#include "key.h"
#include "SysTick.h"



  void Key_GPIO_Config(void)
{        //PE3
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*���������˿ڵ�ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3; 
	// ���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//ʹ�ýṹ���ʼ������
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
}


 u8 Key_Scan(GPIO_TypeDef* GPIOX,u16 GPIO_Pin)
  {
	     /*����Ƿ��а������� */  
             
         
                  if(GPIO_ReadInputDataBit(GPIOX,GPIO_Pin) == KEY_ON )     
                       
					   Delay_10us(200000);
			        if(GPIO_ReadInputDataBit(GPIOX,GPIO_Pin) == KEY_ON )
					{						
                       /*�ȴ������ͷ� */      
					   return  KEY_ON;
                    }
				   		   
                   else  
			      {  
					return KEY_OFF;
                    	
			      }				  
}

