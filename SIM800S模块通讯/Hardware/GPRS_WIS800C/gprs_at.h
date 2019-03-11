#ifndef _GPRS_AT_H_
#define _GPRS_AT_H_

#include "stm32f10x.h"

extern uint8_t gprs_init_flag,gprs_net_flag,gprs_connect_flag;

uint8_t gprs_init(void);
uint8_t gprs_phone(void);
uint8_t gprs_getbor_inf(void);
uint8_t gprs_send_message(void);
#endif



