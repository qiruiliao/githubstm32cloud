#ifndef __motor_H
#define __motor_H
#include "stm32f10x.h"
//因nrun()和prun()实现方法较SetMotor()方法代码多，推荐用SetMotor()
void nrun(void);                  //证转
void prun(void);                  //反转
void srun(void);
void Motor_GPIO_Config(void);

void SetMotor(unsigned char InputData);
void motorNcircle(int n,_Bool position,int speed);

#define   IN1        GPIO_Pin_4         //橙
#define   IN2        GPIO_Pin_5         //黄
#define   IN3        GPIO_Pin_6         //粉
#define   IN4        GPIO_Pin_7;        //蓝

#endif // __motor_H


