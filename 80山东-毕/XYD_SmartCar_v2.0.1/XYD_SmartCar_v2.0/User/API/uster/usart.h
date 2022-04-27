/***********************************************************************************
	* __  ____    __ ______
	* \ \/ /\ \  / /|  __  \	�ٷ���վ�� www.edu118.com
	*  \  /  \_\/_/ | |  \ |					
	*  /  \   |  |  | |__/ |					
	* /_/\_\  |__|  |______/					
	*
	*��Ȩ��������ӯ��Ƽ����޹�˾��֣�ݷֲ�����������Ȩ
	*�ļ�����USART.c
	*���ߣ�XYD_WYC
	*�汾�ţ�v1.0
	*���ڣ�2020.08.14
	*������STM32����¥��ڵ��v1.1�� ����ģ��ͷ�ļ�
	*��ע���Ͽδ���
	*��ʷ��¼��
	*				v1.0 USART1�Ĵ�����&�⺯����
	*							���Ժ���
***********************************************************************************/ 
#ifndef _USART_H_
#define _USART_H_

#include "stm32f10x.h"
#include "stdio.h"
#include "LED.h"

extern double a_,b_,c_;

extern uint8_t Usart1_Rdata;
extern u8  USART_RX_BUF[100]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
void USART_Config(uint32_t brr);
void USART_Echo(void);
void USART3_Config(uint32_t brr);
#endif
