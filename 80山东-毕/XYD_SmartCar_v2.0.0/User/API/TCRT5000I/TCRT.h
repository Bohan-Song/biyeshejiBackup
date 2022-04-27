/***********************************************************************************
	* __  ____    __ ______
	* \ \/ /\ \  / /|  __  \	�ٷ���վ�� www.edu118.com
	*  \  /  \_\/_/ | |  \ |					
	*  /  \   |  |  | |__/ |					
	* /_/\_\  |__|  |______/					
	*
	*��Ȩ��������ӯ��Ƽ����޹�˾��֣�ݷֲ�����������Ȩ
	*�ļ�����TCRT.h
	*���ߣ�XYD_WYC
	*�汾�ţ�v1.0
	*���ڣ�2020.11.16
	*������STM32����¥��ڵ��v1.1�� 5·ѭ��ͷ�ļ�
	*��ע���Ͽδ���
	*��ʷ��¼��
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
