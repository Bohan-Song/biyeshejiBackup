#include "water.h"
/******
*�������ƣ�WATER_Config
*�������ܣ�WATER��ʼ��
*������������
*�����ķ���ֵ����
*���ӣ�
        
******/
void WATER_Config(void)
{
	/*��ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	/*������Ľṹ��*/
	GPIO_InitTypeDef  	GPIO_InitStructure = {0};
	/* �����Ľṹ��*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	/* �����Ľṹ��*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	/* �����Ľṹ��*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

void water_Config(void)
	
{
	/*����IO�ڵĳ�ʼ״̬*/
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
