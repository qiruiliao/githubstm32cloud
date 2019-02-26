#ifndef __STEP_MOTOR_H
#define __STEP_MOTOR_H
#include "stm32f10x.h"

void Stepper(int number_of_steps);
void SetSpeed(long speed);
void step(int steps_to_move,int dir);
void stepMotor(int thisStep);
extern volatile uint32_t time;

extern int direction;            //  转动方向
extern int step_delay;          //  步之间的延时
extern int number_of_steps;      // 总步数
extern int step_number;          // 电机正在哪一步
extern uint32_t last_step_time; // 最后一步之后采取的时间戳



#endif //__STEP_MOTOR_H


