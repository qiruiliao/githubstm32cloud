#ifndef __motor_H
#define __motor_H
#include "stm32f10x.h"
//��nrun()��prun()ʵ�ַ�����SetMotor()��������࣬�Ƽ���SetMotor()
void nrun(void);                  //֤ת
void prun(void);                  //��ת
void srun(void);
void Motor_GPIO_Config(void);

void SetMotor(unsigned char InputData);
void motorNcircle(int n,_Bool position,int speed);

#define   IN1        GPIO_Pin_4         //��
#define   IN2        GPIO_Pin_5         //��
#define   IN3        GPIO_Pin_6         //��
#define   IN4        GPIO_Pin_7;        //��

#endif // __motor_H


