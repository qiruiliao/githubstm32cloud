#include "Step_motor.h"
#include "SysTick.h"

int direction;            //  ת������
int step_delay;          //  ��֮�����ʱ
int number_of_steps;      // �ܲ���
int step_number;          // ���������һ��
uint32_t last_step_time; // ���һ��֮���ȡ��ʱ���
void Stepper(int number_of_steps )   //
{
	GPIO_InitTypeDef GPIO_InitStructure;
    step_number=0;
	last_step_time=0;
	number_of_steps=number_of_steps;
		
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE); 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_5|GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //���߷�ת�ٶ�Ϊ50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure); //��ʼ���˿�
}

void SetSpeed(long speed)
{
	  //һ������60*1000*1000����
     step_delay=60L*1000L*1000L/number_of_steps/speed;

}

void step(int steps_to_move,int dir)
{
    int steps_left;
	direction =dir;
	if(steps_to_move>0)
	    steps_left=steps_to_move;
	else
		steps_left=-steps_to_move;
	
	while(steps_left>0)
	{
	 uint32_t now =time;
	  if(now-last_step_time>=step_delay)	
	  {   
		  last_step_time=now;
		  if(direction==1)              //��ת
		  {
			  step_number++;               
			  if(step_number==number_of_steps)
				  step_number=0;
		  }
		  else                         //��ת
		  {
		   if(step_number==0)
		   {
		   step_number=number_of_steps;
		   }
		   step_number--;
		  }
		  steps_left--;
		  stepMotor(step_number%8);    
	  }
	}
}
void stepMotor(int thisStep)
{
  switch (thisStep){
  case 0:                              //0001
	 GPIO_ResetBits(GPIOD,GPIO_Pin_4);    
     GPIO_ResetBits(GPIOD,GPIO_Pin_5);
     GPIO_ResetBits(GPIOD,GPIO_Pin_6);
     GPIO_SetBits(GPIOD,GPIO_Pin_7); 
    break;
  case 1:                             //0011
     GPIO_ResetBits(GPIOD,GPIO_Pin_4);
     GPIO_ResetBits(GPIOD,GPIO_Pin_5);
     GPIO_SetBits(GPIOD,GPIO_Pin_6);
     GPIO_SetBits(GPIOD,GPIO_Pin_7);
   break;
  case 2:                            //0010
     GPIO_ResetBits(GPIOD,GPIO_Pin_4);
     GPIO_ResetBits(GPIOD,GPIO_Pin_5);
     GPIO_SetBits(GPIOD,GPIO_Pin_6);
     GPIO_ResetBits(GPIOD,GPIO_Pin_7); 
    break;
  case 3:                               //0110
     GPIO_ResetBits(GPIOD,GPIO_Pin_4);
     GPIO_SetBits(GPIOD,GPIO_Pin_5);
     GPIO_SetBits(GPIOD,GPIO_Pin_6);
     GPIO_ResetBits(GPIOD,GPIO_Pin_7);
    break;
  case 4:          //0100
    GPIO_ResetBits(GPIOD,GPIO_Pin_4);
    GPIO_SetBits(GPIOD,GPIO_Pin_5);
    GPIO_ResetBits(GPIOD,GPIO_Pin_6);
    GPIO_ResetBits(GPIOD,GPIO_Pin_7);
    break;
  case 5:         //1100
     GPIO_SetBits(GPIOD,GPIO_Pin_4);
     GPIO_SetBits(GPIOD,GPIO_Pin_5);
     GPIO_ResetBits(GPIOD,GPIO_Pin_6);
     GPIO_ResetBits(GPIOD,GPIO_Pin_7);
    break;
  case 6:       //1000
     GPIO_SetBits(GPIOD,GPIO_Pin_4);
     GPIO_ResetBits(GPIOD,GPIO_Pin_5);
     GPIO_ResetBits(GPIOD,GPIO_Pin_6);
     GPIO_ResetBits(GPIOD,GPIO_Pin_7); 
    break;
  case 7:                              //1001
     GPIO_SetBits(GPIOD,GPIO_Pin_4);
     GPIO_ResetBits(GPIOD,GPIO_Pin_5);
     GPIO_ResetBits(GPIOD,GPIO_Pin_6);
     GPIO_SetBits(GPIOD,GPIO_Pin_7);
    break;
  default:
     GPIO_ResetBits(GPIOD,GPIO_Pin_4);
     GPIO_ResetBits(GPIOD,GPIO_Pin_5);
     GPIO_ResetBits(GPIOD,GPIO_Pin_6);
     GPIO_ResetBits(GPIOD,GPIO_Pin_7);
    break;
  } 

//    switch(thisStep)
//	{
//		case 0:  // 1010
//		GPIO_SetBits(GPIOD,GPIO_Pin_4);      
//		GPIO_ResetBits(GPIOD,GPIO_Pin_5);
//		GPIO_SetBits(GPIOD,GPIO_Pin_6);
//        GPIO_ResetBits(GPIOD,GPIO_Pin_7);       
//      break;
//      case 1:  // 0110
//       GPIO_ResetBits(GPIOD,GPIO_Pin_4);
//	   GPIO_SetBits(GPIOD,GPIO_Pin_5);
//		GPIO_SetBits(GPIOD,GPIO_Pin_6);
//        GPIO_ResetBits(GPIOD,GPIO_Pin_7);     
//      break;
//      case 2:  //0101
//        GPIO_ResetBits(GPIOD,GPIO_Pin_4);
//		GPIO_SetBits(GPIOD,GPIO_Pin_5);
//		GPIO_ResetBits(GPIOD,GPIO_Pin_6);
//        GPIO_SetBits(GPIOD,GPIO_Pin_7);     
//      break;
//      case 3:  //1001
//        GPIO_SetBits(GPIOD,GPIO_Pin_4);
//		GPIO_ResetBits(GPIOD,GPIO_Pin_5);
//		GPIO_ResetBits(GPIOD,GPIO_Pin_6);
//        GPIO_SetBits(GPIOD,GPIO_Pin_7);     
//      break;
//    }
}



