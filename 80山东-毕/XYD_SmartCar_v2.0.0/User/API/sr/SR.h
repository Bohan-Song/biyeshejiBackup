#ifndef _SR_04_H_
#define _SR_04_H_

#include "stm32f10x.h"
#include "delay.h"
#include "motor.h"

#define ECHO_PORT    GPIOC
#define ECHO_CLK     RCC_APB2Periph_GPIOC
#define ECHO_PIN     GPIO_Pin_6
#define TRIG_PORT    GPIOB
#define TRIG_CLK     RCC_APB2Periph_GPIOB
#define TRIG_PIN     GPIO_Pin_14


#define TRIG_Send(x)  (x)?(GPIO_SetBits(TRIG_PORT,TRIG_PIN)):(GPIO_ResetBits(TRIG_PORT,TRIG_PIN)) 
#define ECHO_Reci  (GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN))


void HCSR04_Config(void);
void Open_SR04Timer(void);

float Get_Length(void);


#endif
