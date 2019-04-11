#include "NearWay.h"
//Ñ­¼£Ä£¿é
void Near_way_GPIO_Config (void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	 GPIO_InitStructure.GPIO_Pin= S1_Port|S2_Port|S3_Port|S4_Port  
                                 |S5_Port|CLP_Port|Near_Port;
     GPIO_Init(GPIOA,&GPIO_InitStructure); 
}



