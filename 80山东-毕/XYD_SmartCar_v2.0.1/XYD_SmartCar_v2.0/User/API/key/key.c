#include "key.h"


/******
*�������ƣ�KEY_Config
*�������ܣ�KEY��ʼ��
*������������
*�����ķ���ֵ����
*���ӣ�
     KEY1   GPIOA_Pin_0
******/
void KEY_Config(void)
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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	
}

/******
*�������ƣ�KEY_GetValue
*�������ܣ�KEY������ȡ
*������������
*�����ķ���ֵ����
*���ӣ�
    
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
