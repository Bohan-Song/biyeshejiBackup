/***********************************************************************************
	* __  ____    __ ______
	* \ \/ /\ \  / /|  __  \	�ٷ���վ�� www.edu118.com
	*  \  /  \_\/_/ | |  \ |					
	*  /  \   |  |  | |__/ |					
	* /_/\_\  |__|  |______/					
	*
	*��Ȩ��������ӯ��Ƽ����޹�˾��֣�ݷֲ�����������Ȩ
	*�ļ�����SYSTICK.h
	*���ߣ�XYD_WYC
	*�汾�ţ�v1.0
	*���ڣ�2020.08.18
	*������STM32F103R8��Сϵͳ ϵͳ��ʱ������
	*��ע����Сϵͳ
	*��ʷ��¼��			
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
