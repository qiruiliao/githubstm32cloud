#ifndef __motor_H
#define __motor_H
#include "stm32f10x.h"

void nrun(u16 tt);                  //֤ת
void prun(u16 tt);                  //��ת
 
void SetMotor(unsigned char InputData);
void motorNCircle(int n,_Bool position);
void Motor_GPIO_Config(void);


#endif // __motor_H


