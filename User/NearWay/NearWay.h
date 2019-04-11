#ifndef  __NEARWAY__H_
#define   __NEARWAY__H_
#include "stm32f10x.h"


//用到S1、S2、S3
#define   S1_Port     GPIO_Pin_1         //0黑线
#define   S2_Port     GPIO_Pin_2         //0黑线
#define   S3_Port     GPIO_Pin_3         //0黑线
#define   S4_Port     GPIO_Pin_4          //0黑线
#define   S5_Port     GPIO_Pin_5          //0黑线
#define   CLP_Port    GPIO_Pin_6           //触碰为高电平，没有为低电平
#define   Near_Port   GPIO_Pin_7           //接近为高电平  

void Near_way_GPIO_Config(void);


#endif  //  __NEARWAY__H_


