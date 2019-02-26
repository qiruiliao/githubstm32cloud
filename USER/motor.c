#include "motor.h"
#include "SysTick.h"

unsigned char F_Rotation[8]={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09} ;  //��

unsigned char B_Rotation[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08} ;  //��
//�����ת����
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


   //�����ת����
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
	GPIO_InitTypeDef GPIO_InitStructure; //�˿����ýṹ��
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //PD3�ܽ�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //���߷�ת�ٶ�Ϊ50MHz
  GPIO_Init(GPIOD, &GPIO_InitStructure); //��ʼ���˿�
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //PD6�ܽ�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //���߷�ת�ٶ�Ϊ50MHz
  GPIO_Init(GPIOD, &GPIO_InitStructure); //��ʼ���˿�
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //PD12�ܽ�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //���߷�ת�ٶ�Ϊ50MHz
  GPIO_Init(GPIOD, &GPIO_InitStructure); //��ʼ���˿�
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PD4�ܽ�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //���߷�ת�ٶ�Ϊ50MHz
  GPIO_Init(GPIOD, &GPIO_InitStructure); //��ʼ���˿�
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

//�������SetMotor���������ݴ������ݲ�ͬ�����Ƶ�4��IO pin�����ͬ��
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
