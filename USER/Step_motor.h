#ifndef __STEP_MOTOR_H
#define __STEP_MOTOR_H
#include "stm32f10x.h"

void Stepper(int number_of_steps);
void SetSpeed(long speed);
void step(int steps_to_move,int dir);
void stepMotor(int thisStep);
extern volatile uint32_t time;

extern int direction;            //  ת������
extern int step_delay;          //  ��֮�����ʱ
extern int number_of_steps;      // �ܲ���
extern int step_number;          // ���������һ��
extern uint32_t last_step_time; // ���һ��֮���ȡ��ʱ���



#endif //__STEP_MOTOR_H


