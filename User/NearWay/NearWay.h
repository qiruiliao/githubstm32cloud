#ifndef  __NEARWAY__H_
#define   __NEARWAY__H_
#include "stm32f10x.h"


//�õ�S1��S2��S3
#define   S1_Port     GPIO_Pin_1         //0����
#define   S2_Port     GPIO_Pin_2         //0����
#define   S3_Port     GPIO_Pin_3         //0����
#define   S4_Port     GPIO_Pin_4          //0����
#define   S5_Port     GPIO_Pin_5          //0����
#define   CLP_Port    GPIO_Pin_6           //����Ϊ�ߵ�ƽ��û��Ϊ�͵�ƽ
#define   Near_Port   GPIO_Pin_7           //�ӽ�Ϊ�ߵ�ƽ  

void Near_way_GPIO_Config(void);


#endif  //  __NEARWAY__H_


