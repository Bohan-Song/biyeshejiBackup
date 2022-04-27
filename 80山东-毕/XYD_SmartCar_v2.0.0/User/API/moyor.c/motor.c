#include "motor.h"


void MOTOR_Config()
{

/******
*函数名称；MOTOR_Config
*函数功能；MOTOR初始化
*函数参数：无
*函数的返回值；无
*附加；
	    右前轮
      IA1 GPIOA_Pin_8
	    IB1 GPIOA_Pin_9
******/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
	/*定义核心结构体*/
	GPIO_InitTypeDef  	GPIO_InitStructure = {0};
	/*填充核心结构体*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	
}
void qianjin(int a,int b) //这里用a来确定轮子正转，b确定轮子反转
{
	if(a>0)
	{
		//正转
		if(a%6==1)  //右前轮
		{
			IA1_1;
			IB1_0;
		}
		else if(a%6==2) //右后轮
		{
			IA2_1;
			IB2_0;		
		}
		else if(a%6==3)//左后
		{
			IA3_1;
			IB3_0;
		}
		else if(a%6==4)//左前
		{
			IA4_1;
			IB4_0;
		}
		else if(a%6==5) //左转
		{
			IA1_1;
			IB1_0;
			IA2_1;
			IB2_0;
			IA3_0;
			IB3_0;
			IA4_0;
			IB4_0;			
		}
		else if(a%6==0)//右转
		{
			IA1_0;
			IB1_0;
			IA2_0;
			IB2_0;
			IA3_1;
			IB3_0;
			IA4_1;
			IB4_0;			
		}
	}

	//反转
	if(b>0)
	{
		if(b%4==1)
		{
			IA1_0;
			IB1_1;
		}
		else if(b%4==2)
		{
			IA2_0;
			IB2_1;		
		}
		else if(b%4==3)
		{
			IA3_0;
			IB3_1;
		}
		else if(b%4==0)
		{
			IA4_0;
			IB4_1;
		}
	}
}
//void KEY_Config(void)
//{
//	
//		
//		
//		
//		
//		/*编程流程
//	
//	      1、开时钟---开谁的时钟
//				2、配置IO口的模式
//				3、配置IO口的初始状态
//				4、配置我们需要的工作状态
//  */
//	/*开时钟*/
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//		
//	/*定义核心结构体*/
//	GPIO_InitTypeDef  	GPIO_InitStructure = {0};
//	/*填充核心结构体*/
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ; 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	
//	
//	
//}
