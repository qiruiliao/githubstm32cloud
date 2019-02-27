#include "motor.h"


 int b;                    //正反转标值
 void Motor_GPIO_Config(void)
  {  
	  GPIO_InitTypeDef GPIO_InitStructure;                       //端口配置结构体
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE); 
	  GPIO_InitStructure.GPIO_Pin = IN1 |IN2|IN3 |IN4 ;        //PD4567管脚  四路输入
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //推挽输出
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      //口线翻转速度为50MHz
	  GPIO_Init(GPIOD, &GPIO_InitStructure);                //初始化端口
	  
	 }
//电机正转函数
void nrun(void)
{     
  GPIO_ResetBits(GPIOD,IN1);
  GPIO_SetBits(GPIOD,IN2);
  b=1;
	
}


   //电机反转函数
void prun(void)
{ 
	GPIO_SetBits(GPIOD,IN1);
    GPIO_ResetBits(GPIOD,IN2);
     b=0;
}

