#ifndef __DATA_UNIT_H_
#define __DATA_UNIT_H_

#include "stm32f10x.h"

extern uint8_t err_cnt,err_num; 

void err_process(uint8_t err);
void gprs_reset(void);
uint8_t find_string(char* p);




#endif


