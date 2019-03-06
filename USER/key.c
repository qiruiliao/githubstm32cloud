#include "key.h"
#include "SysTick.h"



u8 key_fall_flag = 0;//按键按下标志

//按键初始化函数
void KEY_Init(void)
{

    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE, ENABLE); //使能GPIOA,GPIOE时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;          //KEY2 KEY3KEY3对应引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;                               //上啦输入模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOE, &GPIO_InitStructure);                                     //初始化GPIOE2,3,4


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;            //KEY4对应引脚PA0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);               //初始化GPIOA0

}






u8 KEY_Scan(u8 mode)
{
    static u8 key_up = 1;         //按键按松开标志

    if(mode)key_up = 1;          //支持连按

    if(key_up && ( KEY2 == 0 ))      //随意一个按下去
    {
          Delay_10us(1000);//去抖动
          key_up = 0;

        if(KEY2 == 0)
			return 1;
       
    }
    else if( KEY2 == 1)           //没有一个按下去
	     key_up = 1;           
         return 0;// 无按键按下
	
}




void EXTIX_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    KEY_Init();                                 //按键端口初始化
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  
    //GPIOE.2 中断线以及中断初始化配置,下降沿触发
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2); //
    EXTI_InitStructure.EXTI_Line = EXTI_Line2;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;     //下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);            //初始化中断线参数

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;                  //使能按键外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;     //抢占优先级 2，
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;            //子优先级 2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);//初始化 NVIC
}





















