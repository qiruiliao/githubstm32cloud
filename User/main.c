#include "stm32f10x.h"
#include "bsp_usart.h"
#include "systick.h"
#include "LCDFront.h"
#include "LCD1602.h"
#include "motor_pwm.h"
#include "NearWay.h"

//�������·��û�С�T�����͡���7�����ͺ͡�ʮ�����͵�·��,��ֻ��Ҫ��S2��S3��S4��Near���ĸ�̽ͷ.
int main(void)
{	 

	uint8_t i;
	uint8_t temp[8];
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	systick_init();
	//USART_Config();
	ADVANCE_TIM_Init();       //TIM1���������ʼ��
	Near_way_GPIO_Config();
	LCD_RCC_Config();           //ʱ�ӳ�ʼ��
	LCD_GPIO_Config();          //LCD��������
	LCD1602_Init();             //LCDҺ����ʼ��
 while(1)
	{	
		//ȡ���Ƿ��ں��߹���ϵ�ֵ�Լ��Ƿ������ϰ���
		temp[0]=GPIO_ReadInputDataBit(GPIOA,S2_Port);  
		temp[1]=GPIO_ReadInputDataBit(GPIOA,S3_Port);   //�м�ĵ�
		temp[2]=GPIO_ReadInputDataBit(GPIOA,S4_Port);
		temp[3]=GPIO_ReadInputDataBit(GPIOA,Near_Port);
		
		  //temp[3]=1;
		//�����ϰ���
		if(temp[3])                    
		  { 
			  LCD_Write_Cmd(0x01);  
			  LCD_Write_String(0x80,"!!!!,Back ");
			  lcd1602_write_pic(i,pic[1]);  
			  Back();	
		  }
		
		//����̽ͷ����⵽���ߣ�ֱ�� 
		if(!(temp[1]|temp[0]|temp[2]))                    
		  { 
			  LCD_Write_Cmd(0x01);  
			  LCD_Write_String(0x80,"Direction: ");
			  lcd1602_write_pic(i,pic[0]);  
			  Forward();	
		  }
		 //����ⲻ�����ߣ��Ҳ���м��⵽����ת
		if(!temp[1]&temp[0]&!temp[2])               
		  { 
			  LCD_Write_Cmd(0x01);  
			  LCD_Write_String(0x80,"Direction: "); 
			  lcd1602_write_pic(i,pic[3]);  
			  Turn_Right();	
		   }
		//�Ҳ��ⲻ�����ߣ������м��⵽����ת
	   if(!temp[1]&!temp[0]&temp[2])                
		 { 
			  LCD_Write_Cmd(0x01);  
			  LCD_Write_String(0x80,"Direction: "); 
			  lcd1602_write_pic(i,pic[2]);  
			  Turn_Left();
		 }
		 
		 //�����յ㣬ǰ��û�к�����,����
		   if(temp[1]&!temp[0]&!temp[2])                
		 { 
			  LCD_Write_Cmd(0x01);  
			  LCD_Write_String(0x80,"Direction: "); 
			  lcd1602_write_pic(i,pic[1]);  
			  Back();
		 }

	}
}
/*********************************************END OF FILE**********************/
