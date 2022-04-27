#ifndef MOTOR_H
#define MOTOR_H
#include "stm32f10x.h"

#define IA1_0  GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define IA1_1  GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define IB1_0  GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define IB1_1  GPIO_SetBits(GPIOB,GPIO_Pin_9)

#define IA2_0  GPIO_ResetBits(GPIOB,GPIO_Pin_0)
#define IA2_1  GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define IB2_0  GPIO_ResetBits(GPIOB,GPIO_Pin_1)
#define IB2_1  GPIO_SetBits(GPIOB,GPIO_Pin_1)


#define IA3_0  GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define IA3_1  GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define IB3_0  GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define IB3_1  GPIO_SetBits(GPIOB,GPIO_Pin_7)

#define IA4_0  GPIO_ResetBits(GPIOA,GPIO_Pin_6)
#define IA4_1 GPIO_SetBits(GPIOA,GPIO_Pin_6)
#define IB4_0  GPIO_ResetBits(GPIOA,GPIO_Pin_7)
#define IB4_1  GPIO_SetBits(GPIOA,GPIO_Pin_7)
void qianjin(int a,int b);
void MOTOR_Config();

#endif
