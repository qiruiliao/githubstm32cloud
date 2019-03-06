#include "motor.h"
#include "SysTick.h"

u8 phasecw[8] ={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};// ��ʱ��
u8 phaseccw[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};// ˳ʱ��
                   
 void Motor_GPIO_Config(void)
  {  
	  GPIO_InitTypeDef GPIO_InitStructure;                       //�˿����ýṹ��
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE); 
	  GPIO_InitStructure.GPIO_Pin = IN1|IN2|IN3|IN4;          //PD4567�ܽ�  ��·����
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //�������
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      //���߷�ת�ٶ�Ϊ50MHz
	  GPIO_Init(GPIOD, &GPIO_InitStructure);                //��ʼ���˿�
	  
	 }
  
	//����ӳ��
void SetMotor(unsigned char InputData)
{
    if(InputData&0x01)                            //����1�ĵ�ƽ(PD4)
    {
        GPIO_SetBits(GPIOD,IN1);
    }
    else
    {
        GPIO_ResetBits(GPIOD,IN1);
    }
    if(InputData&0x02)                            //����2λ�ĵ�ƽ(PD5)
    {
        GPIO_SetBits(GPIOD,IN2);
    }
    else
    {
        GPIO_ResetBits(GPIOD,IN2);

    }
    if(InputData&0x04)                            //����3λ�ĵ�ƽ(PD6)
    {
        GPIO_SetBits(GPIOD,IN3);
    }
    else
    {
        GPIO_ResetBits(GPIOD,IN3);
    }
    if(InputData&0x08)                           //����2λ�ĵ�ƽ(PD7)
    {
        GPIO_SetBits(GPIOD,GPIO_Pin_7);
    }
    else
    {
        GPIO_ResetBits(GPIOD,GPIO_Pin_7);
    }
}


//�����5.625 360/5.625=64 ���ٱ�1/64 
//��64*64������תһȦ
//nȦ�� 
//position ����
//ʵ�ֵ����ת����Ȧ��������ת
/////////////////////////////////////////////////
void motorNcircle(int n,_Bool position,int speed)
{
    int i,j,k=0;
    for(j=0;j<n;j++)
    {
        //for(i=0;i<64*8;i++)
        for(i=0;i<8;i++)
        {
            for(k=0;k<8;k++)
            {
                if(position==1)
                {    
                     SetMotor(phaseccw[k]); 
					Delay_10us(speed);
                }
                else
                {    
                   SetMotor(phasecw[k]);
					Delay_10us(speed);    //100
                }
                Delay_10us(200);            //200   �Լ�������Ȼ�᲻ת�ͺܳ��Ϳ���
				
            }
        }
    }
}

	 
//�����ת����
void nrun(void)
{     
//0111        1
   GPIO_ResetBits(GPIOD,IN1);
   GPIO_SetBits(GPIOD,IN2);
   GPIO_SetBits(GPIOD,IN3);
   GPIO_SetBits(GPIOD,GPIO_Pin_7);
   Delay_10us(500);
	
	     //0011           2
   GPIO_ResetBits(GPIOD,IN1);
   GPIO_ResetBits(GPIOD,IN2);
   GPIO_SetBits(GPIOD,IN3);
   GPIO_SetBits(GPIOD,GPIO_Pin_7);
   Delay_10us(500);
	
      //1011              3
   GPIO_SetBits(GPIOD,IN1);
   GPIO_ResetBits(GPIOD,IN2);
   GPIO_SetBits(GPIOD,IN3);
   GPIO_SetBits(GPIOD,GPIO_Pin_7);
   Delay_10us(500);
	
	     //1001          4
   GPIO_SetBits(GPIOD,IN1);
   GPIO_ResetBits(GPIOD,IN2);
   GPIO_ResetBits(GPIOD,IN3);
   GPIO_SetBits(GPIOD,GPIO_Pin_7);
   Delay_10us(500);
         //1101           5
   GPIO_SetBits(GPIOD,IN1);
   GPIO_SetBits(GPIOD,IN2);
   GPIO_ResetBits(GPIOD,IN3);
   GPIO_SetBits(GPIOD,GPIO_Pin_7);
   Delay_10us(500);
   
        //1100            6
   GPIO_SetBits(GPIOD,IN1);
   GPIO_SetBits(GPIOD,IN2);
   GPIO_ResetBits(GPIOD,IN3);
   GPIO_ResetBits(GPIOD,GPIO_Pin_7);
   Delay_10us(500);
     //1110               7
   GPIO_SetBits(GPIOD,IN1);
   GPIO_SetBits(GPIOD,IN2);
   GPIO_SetBits(GPIOD,IN3);
   GPIO_ResetBits(GPIOD,GPIO_Pin_7);
   Delay_10us(500);
   
        //0110            8
   GPIO_ResetBits(GPIOD,IN1);
   GPIO_SetBits(GPIOD,IN2);
   GPIO_SetBits(GPIOD,IN3);
   GPIO_ResetBits(GPIOD,GPIO_Pin_7);
   Delay_10us(500);
	
}


   //�����ת����
void prun(void)
{ 
	       //0110            8
   GPIO_ResetBits(GPIOD,IN1);
   GPIO_SetBits(GPIOD,IN2);
   GPIO_SetBits(GPIOD,IN3);
   GPIO_ResetBits(GPIOD,GPIO_Pin_7);
   Delay_10us(500);
	
	    //1110               7
   GPIO_SetBits(GPIOD,IN1);
   GPIO_SetBits(GPIOD,IN2);
   GPIO_SetBits(GPIOD,IN3);
   GPIO_ResetBits(GPIOD,GPIO_Pin_7);
   Delay_10us(500);
	
	        //1100            6
   GPIO_SetBits(GPIOD,IN1);
   GPIO_SetBits(GPIOD,IN2);
   GPIO_ResetBits(GPIOD,IN3);
   GPIO_ResetBits(GPIOD,GPIO_Pin_7);
   Delay_10us(500);
	
	      //1101           5
   GPIO_SetBits(GPIOD,IN1);
   GPIO_SetBits(GPIOD,IN2);
   GPIO_ResetBits(GPIOD,IN3);
   GPIO_SetBits(GPIOD,GPIO_Pin_7);
   Delay_10us(500);
	
		     //1001          4
   GPIO_SetBits(GPIOD,IN1);
   GPIO_ResetBits(GPIOD,IN2);
   GPIO_ResetBits(GPIOD,IN3);
   GPIO_SetBits(GPIOD,GPIO_Pin_7);
   Delay_10us(500);
	
	   //1011              3
   GPIO_SetBits(GPIOD,IN1);
   GPIO_ResetBits(GPIOD,IN2);
   GPIO_SetBits(GPIOD,IN3);
   GPIO_SetBits(GPIOD,GPIO_Pin_7);
   Delay_10us(500);
	
	     //0011           2
   GPIO_ResetBits(GPIOD,IN1);
   GPIO_ResetBits(GPIOD,IN2);
   GPIO_SetBits(GPIOD,IN3);
   GPIO_SetBits(GPIOD,GPIO_Pin_7);
   Delay_10us(500);
	
	   //0111        1
   GPIO_ResetBits(GPIOD,IN1);
   GPIO_SetBits(GPIOD,IN2);
   GPIO_SetBits(GPIOD,IN3);
   GPIO_SetBits(GPIOD,GPIO_Pin_7);
   Delay_10us(500);
	
	
}

//���ֹͣ
void srun(void)
{
  
   GPIO_ResetBits(GPIOD,IN1);
   GPIO_ResetBits(GPIOD,IN2);
   GPIO_ResetBits(GPIOD,IN3);
   GPIO_ResetBits(GPIOD,GPIO_Pin_7);

}
