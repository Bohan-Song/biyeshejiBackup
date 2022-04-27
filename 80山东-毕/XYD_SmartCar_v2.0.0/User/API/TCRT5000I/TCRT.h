/***********************************************************************************
	* __  ____    __ ______
	* \ \/ /\ \  / /|  __  \	官方网站： www.edu118.com
	*  \  /  \_\/_/ | |  \ |					
	*  /  \   |  |  | |__/ |					
	* /_/\_\  |__|  |______/					
	*
	*版权◎深圳信盈达科技有限公司（郑州分部）保留所有权
	*文件名：TCRT.h
	*作者：XYD_WYC
	*版本号：v1.0
	*日期：2020.11.16
	*描述：STM32智能楼宇节点板v1.1版 5路循迹头文件
	*备注：上课代码
	*历史记录：
	*				
***********************************************************************************/ 
#ifndef _TCRT_H_
#define _TCRT_H_

#include "stm32f10x.h"
#include "stdio.h"
#include "timer.h"
#include "delay.h"
#include "systick.h"

#define TCRT_OUT1 (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7))
#define TCRT_OUT2 (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8))
#define TCRT_OUT3 (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9))
#define TCRT_OUT4 (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10))
#define TCRT_OUT5 (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11))

void TCRT5000I_Config(void);
uint8_t TCRT5000I_GetState(void);
void TCRT5000I_Ctrl(void);

#endif
