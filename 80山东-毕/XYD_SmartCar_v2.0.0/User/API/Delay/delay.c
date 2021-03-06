/***********************************************************************************
	* __  ____    __ ______
	* \ \/ /\ \  / /|  __  \	官方网站： www.edu118.com
	*  \  /  \_\/_/ | |  \ |					
	*  /  \   |  |  | |__/ |					
	* /_/\_\  |__|  |______/					
	*
	*版权◎深圳信盈达科技有限公司（郑州分部）保留所有权
	*文件名：delay.c
	*作者：XYD_WYC
	*版本号：v1.0
	*日期：2020.08.14
	*描述：STM32F103延时函数
	*备注：最小系统
	*历史记录：
	*
***********************************************************************************/  
#include "delay.h"


/****************************
函数名称：Delay_nop_1us
函数作用：延时1微妙
函数参数：无
函数返回值：无
函数作者：XYD_WYC
创建时间：2020.08.11
修改时间：2020.08.11
****************************/
void Delay_nop_1us(void)
{
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
}

/****************************
函数名称：Delay_nop_nus
函数作用：延时n微妙
函数参数：time 	延时时间
函数返回值：无
函数作者：XYD_WYC
创建时间：2020.08.11
修改时间：2020.08.11
****************************/
void Delay_nop_nus(uint32_t time)
{
	while(time--)
		Delay_nop_1us();
}

/*
void Delay_nop_nms(uint32_t time)
{
	while(time--)
		Delay_nop_nus(1000);
}
*/

