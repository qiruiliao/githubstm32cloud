#ifndef __KEY_H  
#define __KEY_H  

#include "stm32f10x.h"
#define KEY_ON   0
#define KEY_OFF  1
void Key_GPIO_Config(void);
u8 Key_Scan(GPIO_TypeDef *GPIOX,u16 GPIO_Pin);
#endif