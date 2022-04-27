#include "motor.h"


void MOTOR_Config()
{

/******
*�������ƣ�MOTOR_Config
*�������ܣ�MOTOR��ʼ��
*������������
*�����ķ���ֵ����
*���ӣ�
	    ��ǰ��
      IA1 GPIOA_Pin_8
	    IB1 GPIOA_Pin_9
******/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
	/*������Ľṹ��*/
	GPIO_InitTypeDef  	GPIO_InitStructure = {0};
	/*�����Ľṹ��*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	
}
void qianjin(int a,int b) //������a��ȷ��������ת��bȷ�����ӷ�ת
{
	if(a>0)
	{
		//��ת
		if(a%6==1)  //��ǰ��
		{
			IA1_1;
			IB1_0;
		}
		else if(a%6==2) //�Һ���
		{
			IA2_1;
			IB2_0;		
		}
		else if(a%6==3)//���
		{
			IA3_1;
			IB3_0;
		}
		else if(a%6==4)//��ǰ
		{
			IA4_1;
			IB4_0;
		}
		else if(a%6==5) //��ת
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
		else if(a%6==0)//��ת
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

	//��ת
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
//		/*�������
//	
//	      1����ʱ��---��˭��ʱ��
//				2������IO�ڵ�ģʽ
//				3������IO�ڵĳ�ʼ״̬
//				4������������Ҫ�Ĺ���״̬
//  */
//	/*��ʱ��*/
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//		
//	/*������Ľṹ��*/
//	GPIO_InitTypeDef  	GPIO_InitStructure = {0};
//	/*�����Ľṹ��*/
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ; 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	
//	
//	
//}
