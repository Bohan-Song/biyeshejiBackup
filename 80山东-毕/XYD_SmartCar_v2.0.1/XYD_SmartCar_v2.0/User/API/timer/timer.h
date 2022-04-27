#ifndef TIMER_H
#define TIMER_H
#include "stm32f10x.h"

#define car_front (u8)0
#define car_last (u8)1
#define car_left (u8)2
#define car_right (u8)3
#define car_stop   (u8)4
#define zheng  (u8)0
#define fan    (u8)1
static u16 current_speed =0 ;
void Control_V(char n_code);
void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr,u16 psc);
void SetSpeed(int car_mode,u16 speed);
void Set_speed(u16 value);
#endif
