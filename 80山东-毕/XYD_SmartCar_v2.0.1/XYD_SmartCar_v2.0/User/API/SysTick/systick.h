/***********************************************************************************
	* __  ____    __ ______
	* \ \/ /\ \  / /|  __  \	官方网站： www.edu118.com
	*  \  /  \_\/_/ | |  \ |					
	*  /  \   |  |  | |__/ |					
	* /_/\_\  |__|  |______/					
	*
	*版权◎深圳信盈达科技有限公司（郑州分部）保留所有权
	*文件名：SYSTICK.h
	*作者：XYD_WYC
	*版本号：v1.0
	*日期：2020.08.18
	*描述：STM32F103R8最小系统 系统定时器函数
	*备注：最小系统
	*历史记录：			
	*			
***********************************************************************************/ 
#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "stm32f10x.h"

#define SYSTICK_MS 72000
#define SYSTICK_US 72

extern uint32_t Sys_DelayTime;
extern uint32_t Error_TimerRun;
extern uint32_t UI_Run[2];

uint8_t Systick_Config(uint32_t tick);
void Delay_sys_nms(uint32_t time);

#endif
