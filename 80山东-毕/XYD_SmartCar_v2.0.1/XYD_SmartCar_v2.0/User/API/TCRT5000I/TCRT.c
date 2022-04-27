/***********************************************************************************
	* __  ____    __ ______
	* \ \/ /\ \  / /|  __  \	�ٷ���վ�� www.edu118.com
	*  \  /  \_\/_/ | |  \ |					
	*  /  \   |  |  | |__/ |					
	* /_/\_\  |__|  |______/					
	*
	*��Ȩ��������ӯ��Ƽ����޹�˾��֣�ݷֲ�����������Ȩ
	*�ļ�����TCRT.c
	*���ߣ�XYD_WYC
	*�汾�ţ�v1.0
	*���ڣ�2020.11.16
	*������STM32F103R8T6��Сϵͳ 5·ѭ��Դ�ļ�
	*��ע����Сϵͳ
	*��ʷ��¼��
	*				
***********************************************************************************/ 
#include "tcrt.h"

/****************************
�������ƣ�TCRT5000I_Config
�������ã�5·ѭ����ʼ��
������������
��������ֵ����
�������ߣ�XYD_WYC
����ʱ�䣺2020.11.16
�޸�ʱ�䣺2021.05.28
****************************/
void TCRT5000I_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};
	//ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	//ģʽ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

/****************************
�������ƣ�TCRT5000I_GetState
�������ã�5·ѭ����ȡ״̬
������������
��������ֵ����
�������ߣ�XYD_WYC
����ʱ�䣺2020.11.16
�޸�ʱ�䣺2020.11.16
11011
31 0011001
****************************/
uint8_t TCRT5000I_GetState(void)
{
	uint8_t State = 0X00;
	State |= (TCRT_OUT1 << 4);
	State |= (TCRT_OUT2 << 3);
	State |= (TCRT_OUT3 << 2);
	State |= (TCRT_OUT4 << 1);
	State |= (TCRT_OUT5 << 0);
	return State;
}

/****************************
�������ƣ�TCRT5000I_Ctrl
�������ã�5·ѭ������
������ڣ���
�������ڣ���
�������ߣ�XYD_WYC
����ʱ�䣺2020.11.16
�޸�ʱ�䣺2020.11.16
****************************/
uint8_t Car_OutStopFlag = 0;	//0δȫ����1ȫ��
void TCRT5000I_Ctrl(void)
{
	uint8_t Get_Black = 0;
	Get_Black = TCRT5000I_GetState();
	
	//û�к�ɫ�����ж�
	if(Get_Black == 0X1F)
	{
		if(Car_OutStopFlag == 0)//��һ��δȫ��
		{
			Car_OutStopFlag = 1;
			Error_TimerRun = 0;
		}
		else if(Car_OutStopFlag == 1)
		{
			if(Error_TimerRun >= 800)
			{
				SetSpeed(car_stop,500);
				Car_OutStopFlag = 0;
			}		
		}
	}
	else
	{
		Car_OutStopFlag = 0;
		//00111---01111---10111----10011
		//
//		if((Get_Black == 0X07)||(Get_Black == 0X0F)||(Get_Black == 0X17)||(Get_Black == 0X13))
//		{
//			Set_speed(500);//ѭ��
//			SetSpeed(car_front,500);
//		}
		//11011

		switch(Get_Black)
		{
			case 0x00: 
			case 0x11: 
			case 0x01: 
			case 0x10: SetSpeed(car_stop,500); break;

			case 0x13: SetSpeed(car_left,500);Set_speed(600-200); break;
			case 0x17: Set_speed(600-300); break;
			case 0x07: Set_speed(600-400); break;
			case 0x0f: SetSpeed(car_left,500); break;

			case 0x19: Set_speed(600-200); break;
			case 0x1c: Set_speed(600-300); break;
			case 0x1d: Set_speed(600-400); break;
			case 0x1e: SetSpeed(car_right,600); break;//??4?
			
			case 0x1b: Set_speed(600);SetSpeed(car_front,600); break;
			
			case 0xff: SetSpeed(car_stop,500); break;
			
			default:SetSpeed(car_stop,500); break;
		}
		
//		if(!(Get_Black & 0x40))
//		{
//			Set_speed(500);//ѭ��
//			SetSpeed(car_front,500);
//		}
//		//11100----11110-----11101------11001
//		else if((Get_Black == 0X1C)||(Get_Black == 0X1E)||(Get_Black == 0X1D)||(Get_Black == 0X19))
//		{
//			SetSpeed(car_right,500);
//		}
//		//11001
//		else if(Get_Black == 0X1B)
//		{
//			SetSpeed(car_left,500);
//		}
//		//00000
//		else if(Get_Black == 0X00)
//		{
//			Delay_nop_nms(100);
//			if(TCRT5000I_GetState() == 0X00)
//			{
//				SetSpeed(car_stop,500);
//			}
//		}
//	}
}
}
