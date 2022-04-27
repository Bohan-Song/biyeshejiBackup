#ifndef __SG90_H
#define __SG90_H

#include "stm32f10x.h"
#include "lcd.h"
#include "stdio.h"
void TIM4_PWM_Init(u16 arr,u16 psc);
void closeLan();
void openLan();
void RecommendChewei(u8 chewei);
int check_C(char* cuurent,char* chewei);
char * stopC();
char * state(u8 flag);

#endif