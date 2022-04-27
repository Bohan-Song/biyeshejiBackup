#ifndef __IR_H
#define __IR_H

#include "main.h"

#define IR_TIM						TIM2
#define IR_TIM_CLK				RCC_APB1Periph_TIM2
#define IR_TIM_CLK_INIT		RCC_APB1PeriphClockCmd

#define IR_Channel				TIM_Channel_2


#define IR_CLK     		RCC_APB2Periph_GPIOA
#define IR_CLK_INIT		RCC_APB2PeriphClockCmd
#define IR_PORT				GPIOA
#define	IR_PIN				GPIO_Pin_1


#define MAX_DATALEN 5
typedef struct{
	u8 mode;
	u8 Ir_Data[MAX_DATALEN];
	u16 Ir_Length;
}IR_DATA_TypeDef;

extern uint8_t IR_code;

void Tim2_Config(u16 psc, u16 arr);
u8 Ir_RecvAnalysis(void);
#endif
