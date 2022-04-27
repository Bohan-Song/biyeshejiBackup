/***********************************************************************************
	* __  ____    __ ______
	* \ \/ /\ \  / /|  __  \	官方网站： www.edu118.com
	*  \  /  \_\/_/ | |  \ |					
	*  /  \   |  |  | |__/ |					
	* /_/\_\  |__|  |______/					
	*
	*版权◎深圳信盈达科技有限公司（郑州分部）保留所有权
	*文件名：USART.c
	*作者：XYD_WYC
	*版本号：v1.0
	*日期：2020.08.14
	*描述：STM32智能楼宇节点板v1.1版 串口模块源文件
	*备注：上课代码
	*历史记录：
	*				v1.0 
	*							回显函数USART1寄存器版&库函数版
***********************************************************************************/ 
#include "usart.h"

/****************************
函数名称：USART_Config
函数作用：串口初始化
函数参数：无
函数返回值：无
函数作者：XYD_WYC
创建时间：2020.08.13
修改时间：2020.08.13
****************************/
void USART_Config(uint32_t brr)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	//时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
	//GPIO端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//USART配置
	USART_InitStructure.USART_BaudRate = brr;		//波特率
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//硬件控制流--不使用
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//接收器、发送器
	USART_InitStructure.USART_Parity = USART_Parity_No;	//不校验
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//停止位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//数据位
	USART_Init(USART1,&USART_InitStructure);
	//USART模块使能
	USART_Cmd(USART1,ENABLE);
}

/****************************
函数名称：fputc
函数作用：拼接Printf
函数参数：无
函数返回值：无
函数作者：XYD_WYC
创建时间：2020.08.14
修改时间：2020.08.14
****************************/
int fputc(int c, FILE *stream)
{
	while((USART1->SR & (1 << 6)) == 0);//等待上一次数据发送完成
	USART1->DR = c;
	return c;
}

/****************************
函数名称：USART_Echo
函数作用：串口回显
函数参数：无
函数返回值：无
函数作者：XYD_WYC
创建时间：2020.08.14
修改时间：2020.08.14
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
void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
	    u8 res; 
		res =USART_ReceiveData(USART1);	//读取接收到的数据
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


