#ifndef BEE_H
#define BEE_H

#include "stm32f10x.h"

#include "delay.h"
#define BEEP1 = GPIO_ResetBits(GPIOA,GPIO_Pin_15)
#define BEEP0 = GPIO_SetBits(GPIOA,GPIO_Pin_15)
void BEE_Config();


#endif  
