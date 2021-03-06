#include "stm32f10x.h"
#include "key.h"

void Key_init(void)	//初始化 KEY1
{	
	GPIO_InitTypeDef gpio_init_struct;//结构体

	RCC_APB2PeriphClockCmd(KEY1_RCC, ENABLE);//初始化时钟 

	gpio_init_struct.GPIO_Mode = GPIO_Mode_IPU;//输入上拉
	gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init_struct.GPIO_Pin = KEY1_PIN|KEY2_PIN;

	GPIO_Init(KEY1_PORT, &gpio_init_struct);
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//初始化时钟 
	gpio_init_struct.GPIO_Mode = GPIO_Mode_IPU;//输入上拉
	gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init_struct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
	GPIO_Init(GPIOA, &gpio_init_struct);
	
	
	
	
}







