#include "motor.h"
#include "SysTick.h"

unsigned char F_Rotation[8]={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09} ;  //反

unsigned char B_Rotation[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08} ;  //正
//电机正转函数
void nrun(u16 tt)
{     
     //1000
  GPIO_SetBits(GPIOC, GPIO_Pin_6);   
  GPIO_ResetBits(GPIOC, GPIO_Pin_7);
  GPIO_ResetBits(GPIOC, GPIO_Pin_8);
  GPIO_ResetBits(GPIOC, GPIO_Pin_9);
   Delay_10us(tt);
	
   //1100 
  GPIO_SetBits(GPIOC, GPIO_Pin_6);
  GPIO_SetBits(GPIOC, GPIO_Pin_7);
  GPIO_ResetBits(GPIOC, GPIO_Pin_8);
  GPIO_ResetBits(GPIOC, GPIO_Pin_9);
   Delay_10us(tt);
	
  //0100
  GPIO_SetBits(GPIOC, GPIO_Pin_6);   
  GPIO_SetBits(GPIOC, GPIO_Pin_7);
  GPIO_ResetBits(GPIOC, GPIO_Pin_8);
  GPIO_ResetBits(GPIOC, GPIO_Pin_9);
   Delay_10us(tt);
	
  //0110  
  GPIO_ResetBits(GPIOC, GPIO_Pin_6);
  GPIO_SetBits(GPIOC, GPIO_Pin_7);
  GPIO_SetBits(GPIOC, GPIO_Pin_8);
  GPIO_ResetBits(GPIOC, GPIO_Pin_9);
   Delay_10us(tt);
  
  //0010
  GPIO_ResetBits(GPIOC, GPIO_Pin_6);    
  GPIO_ResetBits(GPIOC, GPIO_Pin_7);
  GPIO_SetBits(GPIOC, GPIO_Pin_8);
  GPIO_ResetBits(GPIOC, GPIO_Pin_9);
   Delay_10us(tt);
  
  //0011
  GPIO_ResetBits(GPIOD, GPIO_Pin_6);
  GPIO_ResetBits(GPIOD, GPIO_Pin_7);
  GPIO_SetBits(GPIOD, GPIO_Pin_8);
  GPIO_SetBits(GPIOD, GPIO_Pin_9);
   Delay_10us(tt);
  
  //0001
  GPIO_ResetBits(GPIOD, GPIO_Pin_6);    
  GPIO_ResetBits(GPIOD, GPIO_Pin_7);
  GPIO_ResetBits(GPIOD, GPIO_Pin_8);
  GPIO_SetBits(GPIOD, GPIO_Pin_9);
   Delay_10us(tt);
  
  //1001   
  GPIO_SetBits(GPIOD, GPIO_Pin_6);
  GPIO_ResetBits(GPIOD, GPIO_Pin_7);
  GPIO_ResetBits(GPIOD, GPIO_Pin_8);
  GPIO_SetBits(GPIOD, GPIO_Pin_9);
   Delay_10us(tt);
}


   //电机反转函数
void prun(u16 tt)
{
//  //1001   
//  GPIO_SetBits(GPIOD, GPIO_Pin_3);
//  GPIO_ResetBits(GPIOD, GPIO_Pin_6);
//  GPIO_ResetBits(GPIOD, GPIO_Pin_12);
//  GPIO_SetBits(GPIOD, GPIO_Pin_4);
//   Delay_10us(tt);
//  //0011
//  GPIO_ResetBits(GPIOD, GPIO_Pin_3);
//  GPIO_ResetBits(GPIOD, GPIO_Pin_6);
//  GPIO_SetBits(GPIOD, GPIO_Pin_12);
//  GPIO_SetBits(GPIOD, GPIO_Pin_4);
//   Delay_10us(tt);  
//  //0110
//  GPIO_ResetBits(GPIOD, GPIO_Pin_3);
//  GPIO_SetBits(GPIOD, GPIO_Pin_6);
//  GPIO_SetBits(GPIOD, GPIO_Pin_12);
//  GPIO_ResetBits(GPIOD, GPIO_Pin_4);
//   Delay_10us(tt);
//  //1100
//  GPIO_SetBits(GPIOD, GPIO_Pin_3);
//  GPIO_SetBits(GPIOD, GPIO_Pin_6);
//  GPIO_ResetBits(GPIOD, GPIO_Pin_12);
//  GPIO_ResetBits(GPIOD, GPIO_Pin_4);
//   Delay_10us(tt);  
}
 void Motor_GPIO_Config(void)
  {  
	GPIO_InitTypeDef GPIO_InitStructure; //端口配置结构体
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //PD3管脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //口线翻转速度为50MHz
  GPIO_Init(GPIOD, &GPIO_InitStructure); //初始化端口
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //PD6管脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //口线翻转速度为50MHz
  GPIO_Init(GPIOD, &GPIO_InitStructure); //初始化端口
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //PD12管脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //口线翻转速度为50MHz
  GPIO_Init(GPIOD, &GPIO_InitStructure); //初始化端口
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PD4管脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //口线翻转速度为50MHz
  GPIO_Init(GPIOD, &GPIO_InitStructure); //初始化端口
 }
void motorNCircle(int n,_Bool position)

{

   int i=0;
   int  j=0;
   int k=0;
   for(j=0;j<n;j++)
   {
      for(i=0;i<64*8;i++)     
      {
          for(k=0;k<8;k++)
          {
            if(1== position)
                 SetMotor(F_Rotation[k]);  
             else
                 SetMotor(B_Rotation[k]);  
            Delay_10us(500);     
          }
      }
    }
}

//下面就是SetMotor函数，根据传的数据不同，控制的4个IO pin输出不同。
void SetMotor(unsigned char InputData)
{
    if(InputData & 0x08)
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_6 );   
    }
    else
   {
        GPIO_SetBits(GPIOC, GPIO_Pin_6);
    }
    if(InputData & 0x04)
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_7 );   
    }
   else
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_7);
    }
    if(InputData & 0x02)
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_8 );   
    }
    else
   {
        GPIO_SetBits(GPIOC, GPIO_Pin_8);
    }
   if(InputData & 0x01)
   {
       GPIO_ResetBits(GPIOC, GPIO_Pin_9 );   
   }
   else
  {
       GPIO_SetBits(GPIOC, GPIO_Pin_9);
  }
}
