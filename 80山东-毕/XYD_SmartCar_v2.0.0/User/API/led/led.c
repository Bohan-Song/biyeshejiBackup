#include "led.h"


/******
*�������ƣ�LED_Config
*�������ܣ�LED��ʼ��
*������������
*�����ķ���ֵ����
*���ӣ�
     LED1   GPIOC_Pin_0
*/
void LED_Config(void)
{
	/*�������
	
	      1����ʱ��---��˭��ʱ��
				2������IO�ڵ�ģʽ
				3������IO�ڵĳ�ʼ״̬
				4������������Ҫ�Ĺ���״̬
  */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	/*������Ľṹ��*/
	GPIO_InitTypeDef  	GPIO_InitStructure = {0};
	
	/* �����Ľṹ��*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	/*����IO�ڵĳ�ʼ״̬*/
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
	
	
	
	/* �����Ľṹ��*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	/*����IO�ڵĳ�ʼ״̬*/
	GPIO_SetBits(GPIOC,GPIO_Pin_1);
		
		
		/* �����Ľṹ��*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	/*����IO�ڵĳ�ʼ״̬*/
	GPIO_SetBits(GPIOC,GPIO_Pin_2 );	
		
	
	
	
	
}
