/***********************************************************************************
	* __  ____    __ ______
	* \ \/ /\ \  / /|  __  \	官方网站： www.edu118.com
	*  \  /  \_\/_/ | |  \ |					
	*  /  \   |  |  | |__/ |					
	* /_/\_\  |__|  |______/					
	*
	*版权◎深圳信盈达科技有限公司（郑州分部）保留所有权
	*文件名：USART.c
	*作者：XYD_WYC
	*版本号：v1.0
	*日期：2020.08.14
	*描述：STM32智能楼宇节点板v1.1版 串口模块头文件
	*备注：上课代码
	*历史记录：
	*				v1.0 USART1寄存器版&库函数版
	*							回显函数
***********************************************************************************/ 
#ifndef _USART_H_
#define _USART_H_

#include "stm32f10x.h"
#include "stdio.h"
#include "LED.h"

extern double a_,b_,c_;

extern uint8_t Usart1_Rdata;
extern u8  USART_RX_BUF[100]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
void USART_Config(uint32_t brr);
void USART_Echo(void);
void USART3_Config(uint32_t brr);
#endif
