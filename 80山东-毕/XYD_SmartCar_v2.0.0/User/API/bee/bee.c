#include "bee.h"

//GPIOA_pin_15
void BEE_Config()
{
	
		
		
		
		
		/*编程流程
	
	      1、开时钟---开谁的时钟
				2、配置IO口的模式
				3、配置IO口的初始状态
				4、配置我们需要的工作状态
  */
	/*开时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		
	/*定义核心结构体*/
	GPIO_InitTypeDef  	GPIO_InitStructure = {0};
	/*填充核心结构体*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_15);	//引脚要对应

}


	
	