#ifndef __motor_H
#define __motor_H
#include "stm32f10x.h"

void nrun(void);                  //证转
void prun(void);                  //反转
void Motor_GPIO_Config(void);
extern int b;

#define   IN1        GPIO_Pin_4
#define   IN2        GPIO_Pin_5
#define   IN3        GPIO_Pin_6
#define   IN4        GPIO_Pin_7;


#endif // __motor_H


