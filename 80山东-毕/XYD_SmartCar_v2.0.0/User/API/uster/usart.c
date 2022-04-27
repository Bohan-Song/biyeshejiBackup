/***********************************************************************************
	* __  ____    __ ______
	* \ \/ /\ \  / /|  __  \	�ٷ���վ�� www.edu118.com
	*  \  /  \_\/_/ | |  \ |					
	*  /  \   |  |  | |__/ |					
	* /_/\_\  |__|  |______/					
	*
	*��Ȩ��������ӯ��Ƽ����޹�˾��֣�ݷֲ�����������Ȩ
	*�ļ�����USART.c
	*���ߣ�XYD_WYC
	*�汾�ţ�v1.0
	*���ڣ�2020.08.14
	*������STM32����¥��ڵ��v1.1�� ����ģ��Դ�ļ�
	*��ע���Ͽδ���
	*��ʷ��¼��
	*				v1.0 
	*							���Ժ���USART1�Ĵ�����&�⺯����
***********************************************************************************/ 
#include "usart.h"

/****************************
�������ƣ�USART_Config
�������ã����ڳ�ʼ��
������������
��������ֵ����
�������ߣ�XYD_WYC
����ʱ�䣺2020.08.13
�޸�ʱ�䣺2020.08.13
****************************/
void USART_Config(uint32_t brr)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	//ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
	//GPIO�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//USART����
	USART_InitStructure.USART_BaudRate = brr;		//������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ��������--��ʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//��������������
	USART_InitStructure.USART_Parity = USART_Parity_No;	//��У��
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//ֹͣλ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//����λ
	USART_Init(USART1,&USART_InitStructure);
	//USARTģ��ʹ��
	USART_Cmd(USART1,ENABLE);
}

/****************************
�������ƣ�fputc
�������ã�ƴ��Printf
������������
��������ֵ����
�������ߣ�XYD_WYC
����ʱ�䣺2020.08.14
�޸�ʱ�䣺2020.08.14
****************************/
int fputc(int c, FILE *stream)
{
	while((USART1->SR & (1 << 6)) == 0);//�ȴ���һ�����ݷ������
	USART1->DR = c;
	return c;
}

/****************************
�������ƣ�USART_Echo
�������ã����ڻ���
������������
��������ֵ����
�������ߣ�XYD_WYC
����ʱ�䣺2020.08.14
�޸�ʱ�䣺2020.08.14
****************************/
void USART_Echo(void)
{
	u8 data = 0X00;
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == 0);
	data = USART_ReceiveData(USART1);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == 0);
	USART_SendData(USART1,data);	

}
u16 USART_RX_BUF[1000];
int i,k,flag,p;
double longitude,latitude,speed,high;
void USART1_IRQHandler(void)                	//����1�жϷ������
	{
	    u8 res; 
		res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		if(res=='$'||USART_RX_BUF[0]=='$')
		{
			if(res=='$')
			i=0;
			USART_RX_BUF[i]=res;
			i++;
		}			
if(USART_RX_BUF[4]=='M'&&USART_RX_BUF[5]=='C')
			{	
			if(res==',')
    	k++;
		switch(k)
		{
			case 2:
				if(res=='A'&&res!=',')
					flag=1;
				else 
					flag=0;
			break;
			case 3:
				if(flag==1&&res!=','&&res!='.')
				{	longitude*=10;
				  longitude+=res-48;}
				break;
			case 5:
				if(flag==1&&res!=','&&res!='.')
				{latitude*=10;
				 latitude+=res-48;}
				break;
		  case 7:
				if(flag==1&&res!=','&&res!='.')
				{	speed*=10;
				  speed+=res-48;}
				  break;
		
		}
		}		
		if(USART_RX_BUF[4]=='G'&&USART_RX_BUF[5]=='A')
			{	
			if(res==',')
    	    p++;
		switch(p)
		{			
			case 9:
				if(res!=','&&res!='.')
				{
				 high*=10;
				 high+=res-48;
				 }
				 break;				
		}		
		
			
if(res==0x0A)
		{  
		  memset(USART_RX_BUF,0x00,200);
			i=0;
			k=0;			
			a=longitude/10000000;
			b=latitude/10000000;
			c=speed/10*0.5144;
	  	printf("longitude: %f\r\n",a);
		  printf("latitude: %f\r\n",b);
		  printf("speed: %f\r\n",c);
			 printf("high: %f\r\n",high/100);
			longitude=0;
			latitude=0;
			speed=0;
			
		}		
		}						
 
}


