#include "motor.h"


 int b;                    //����ת��ֵ
 void Motor_GPIO_Config(void)
  {  
	  GPIO_InitTypeDef GPIO_InitStructure;                       //�˿����ýṹ��
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE); 
	  GPIO_InitStructure.GPIO_Pin = IN1 |IN2|IN3 |IN4 ;        //PD4567�ܽ�  ��·����
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //�������
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      //���߷�ת�ٶ�Ϊ50MHz
	  GPIO_Init(GPIOD, &GPIO_InitStructure);                //��ʼ���˿�
	  
	 }
//�����ת����
void nrun(void)
{     
  GPIO_ResetBits(GPIOD,IN1);
  GPIO_SetBits(GPIOD,IN2);
  b=1;
	
}


   //�����ת����
void prun(void)
{ 
	GPIO_SetBits(GPIOD,IN1);
    GPIO_ResetBits(GPIOD,IN2);
     b=0;
}

