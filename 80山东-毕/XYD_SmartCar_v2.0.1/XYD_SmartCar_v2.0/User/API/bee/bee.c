#include "bee.h"

//GPIOA_pin_15
void BEE_Config()
{
	
		
		
		
		
		/*�������
	
	      1����ʱ��---��˭��ʱ��
				2������IO�ڵ�ģʽ
				3������IO�ڵĳ�ʼ״̬
				4������������Ҫ�Ĺ���״̬
  */
	/*��ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		
	/*������Ľṹ��*/
	GPIO_InitTypeDef  	GPIO_InitStructure = {0};
	/*�����Ľṹ��*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_15);	//����Ҫ��Ӧ

}


	
	