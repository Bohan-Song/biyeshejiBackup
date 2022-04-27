#include "led.h"


/******
*函数名称；LED_Config
*函数功能；LED初始化
*函数参数：无
*函数的返回值；无
*附加；
     LED1   GPIOC_Pin_0
*/
void LED_Config(void)
{
	/*编程流程
	
	      1、开时钟---开谁的时钟
				2、配置IO口的模式
				3、配置IO口的初始状态
				4、配置我们需要的工作状态
  */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	/*定义核心结构体*/
	GPIO_InitTypeDef  	GPIO_InitStructure = {0};
	
	/* 填充核心结构体*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	/*配置IO口的初始状态*/
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
	
	
	
	/* 填充核心结构体*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	/*配置IO口的初始状态*/
	GPIO_SetBits(GPIOC,GPIO_Pin_1);
		
		
		/* 填充核心结构体*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	/*配置IO口的初始状态*/
	GPIO_SetBits(GPIOC,GPIO_Pin_2 );	
		
	
	
	
	
}
