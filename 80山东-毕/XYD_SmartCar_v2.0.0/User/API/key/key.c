#include "key.h"


/******
*函数名称；KEY_Config
*函数功能；KEY初始化
*函数参数：无
*函数的返回值；无
*附加；
     KEY1   GPIOA_Pin_0
******/
void KEY_Config(void)
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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	
}

/******
*函数名称；KEY_GetValue
*函数功能；KEY按键获取
*函数参数：无
*函数的返回值；无
*附加；
    
*/
void KEY_GetValue(void)
{
	if(!(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)))
	{
		if(!(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)))
		{
		
			while(!(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)));
			GPIOC->ODR ^= (1 << 0);
		}
		
		
	}
}
