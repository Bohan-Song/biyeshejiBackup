#include "water.h"
/******
*函数名称；WATER_Config
*函数功能；WATER初始化
*函数参数：无
*函数的返回值；无
*附加；
        
******/
void WATER_Config(void)
{
	/*开时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	/*定义核心结构体*/
	GPIO_InitTypeDef  	GPIO_InitStructure = {0};
	/* 填充核心结构体*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	/* 填充核心结构体*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	/* 填充核心结构体*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

void water_Config(void)
	
{
	/*配置IO口的初始状态*/
	GPIO_ResetBits(GPIOC,GPIO_Pin_0);
	Delay_nop_nms(250);
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	Delay_nop_nms(250);
	GPIO_SetBits(GPIOC,GPIO_Pin_1);
	GPIO_ResetBits(GPIOC,GPIO_Pin_2);
  Delay_nop_nms(250);
	GPIO_SetBits(GPIOC,GPIO_Pin_2);


}
