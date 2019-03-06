#include "key.h"
#include "SysTick.h"



u8 key_fall_flag = 0;//�������±�־

//������ʼ������
void KEY_Init(void)
{

    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE, ENABLE); //ʹ��GPIOA,GPIOEʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;          //KEY2 KEY3KEY3��Ӧ����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                               //��������ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOE, &GPIO_InitStructure);                                     //��ʼ��GPIOE2,3,4


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;            //KEY4��Ӧ����PA0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);               //��ʼ��GPIOA0

}






u8 KEY_Scan(u8 mode)
{
    static u8 key_up = 1;         //�������ɿ���־

    if(mode)key_up = 1;          //֧������

    if(key_up && ( KEY2 == 0 ))      //����һ������ȥ
    {
          Delay_10us(1000);//ȥ����
          key_up = 0;

        if(KEY2 == 0)
			return 1;
       
    }
    else if( KEY2 == 1)           //û��һ������ȥ
	     key_up = 1;           
         return 0;// �ް�������
	
}




void EXTIX_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    KEY_Init();                                 //�����˿ڳ�ʼ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  
    //GPIOE.2 �ж����Լ��жϳ�ʼ������,�½��ش���
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2); //
    EXTI_InitStructure.EXTI_Line = EXTI_Line2;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;     //�½��ش���
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);            //��ʼ���ж��߲���

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;                  //ʹ�ܰ����ⲿ�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;     //��ռ���ȼ� 2��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;            //�����ȼ� 2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);//��ʼ�� NVIC
}





















