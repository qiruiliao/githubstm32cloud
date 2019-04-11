#include "stm32f10x.h"
#include "bsp_usart.h"
#include "systick.h"
#include "LCDFront.h"
#include "LCD1602.h"
#include "motor_pwm.h"
#include "NearWay.h"

//假设黑线路径没有“T”字型、“7”字型和“十“字型的路线,即只需要用S2、S3、S4和Near这四个探头.
int main(void)
{	 

	uint8_t i;
	uint8_t temp[8];
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	systick_init();
	//USART_Config();
	ADVANCE_TIM_Init();       //TIM1互补输出初始化
	Near_way_GPIO_Config();
	LCD_RCC_Config();           //时钟初始化
	LCD_GPIO_Config();          //LCD引脚配置
	LCD1602_Init();             //LCD液晶初始化
 while(1)
	{	
		//取得是否在黑线轨道上的值以及是否遇到障碍物
		temp[0]=GPIO_ReadInputDataBit(GPIOA,S2_Port);  
		temp[1]=GPIO_ReadInputDataBit(GPIOA,S3_Port);   //中间的点
		temp[2]=GPIO_ReadInputDataBit(GPIOA,S4_Port);
		temp[3]=GPIO_ReadInputDataBit(GPIOA,Near_Port);
		
		  //temp[3]=1;
		//遇到障碍物
		if(temp[3])                    
		  { 
			  LCD_Write_Cmd(0x01);  
			  LCD_Write_String(0x80,"!!!!,Back ");
			  lcd1602_write_pic(i,pic[1]);  
			  Back();	
		  }
		
		//三个探头都检测到黑线，直走 
		if(!(temp[1]|temp[0]|temp[2]))                    
		  { 
			  LCD_Write_Cmd(0x01);  
			  LCD_Write_String(0x80,"Direction: ");
			  lcd1602_write_pic(i,pic[0]);  
			  Forward();	
		  }
		 //左侧检测不到黑线，右侧和中间检测到，右转
		if(!temp[1]&temp[0]&!temp[2])               
		  { 
			  LCD_Write_Cmd(0x01);  
			  LCD_Write_String(0x80,"Direction: "); 
			  lcd1602_write_pic(i,pic[3]);  
			  Turn_Right();	
		   }
		//右侧检测不到黑线，左侧和中间检测到，左转
	   if(!temp[1]&!temp[0]&temp[2])                
		 { 
			  LCD_Write_Cmd(0x01);  
			  LCD_Write_String(0x80,"Direction: "); 
			  lcd1602_write_pic(i,pic[2]);  
			  Turn_Left();
		 }
		 
		 //到达终点，前面没有黑线了,后退
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
