#include<head.h>

void delay_ms(uint ms)	   //��ʱ1ms * ms
{
	//ͨ��ѭ����ʽ�ӳ�
	uint x,y;
	for(x=ms;x>0;x--)
		for(y=113;y>0;y--);
}

void write_com(uchar com)    //д����
{
	lcdrs=0;
	P0=com;
	delay_ms(2);//�ӳ�2ms�ȴ�
	lcden=1;	//��Ϊ1
	delay_ms(2);//�ӳ�2ms�ȴ�
	lcden=0;	//��Ϊ0
}

void write_data(uchar dat)	  //д����
{
	lcdrs=1;
	P0=dat;
	delay_ms(2);//�ӳ�2ms�ȴ�
	lcden=1;	//��Ϊ1
	delay_ms(2);//�ӳ�2ms�ȴ�
	lcden=0;	//��Ϊ0
}
/******************************************************************************
����˵������ʾ�ַ�
������ݣ�x,y    �������
num    Ҫ��ʾ���ַ�
mode   1���ӷ�ʽ  0�ǵ��ӷ�ʽ
����ֵ��  ��
******************************************************************************/
void LCD_ShowChar(uchar x,uchar dat)
{
	write_com(x);//д����
	write_data(dat);//д����
}

//m^n����
uint LCD_pow(uchar m,uchar n)
{
	uint result=1;	 
	while(n--)result*=m; //��ͬ��result = result * m;
	return result;
}		

//��ʾN������
//x :����	 
//len :���ֵ�λ��
//num:��ֵ(0~65536);	 		  
void LCD_ShowNum(uchar x,uint num,uchar len)
{         	
	uchar t,temp;
	uchar enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+t,'0');
				continue;
			}else enshow=1; 	 
		}
		LCD_ShowChar(x+t,temp+'0'); 
	}
} 

//��ʾһ���ַ��Ŵ�
void LCD_ShowString(uchar x,uchar *chr)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		
		LCD_ShowChar(x,chr[j]);
		x+=1;
		j++;
	}
}

void LCD_Init(void)	           //1602Һ����ʼ��
{
	lcden=0;
	write_com(0x38);/*��ʾģʽ����*/ 
	write_com(0x0c);//���ÿ���ʾ,����ʾ���
	write_com(0x06);
	write_com(0x01);/*��ʾ����*/ 
	write_com(0x80);//��ʼָ��ָ���һ��

	LCD_ShowString(0x80,"T:00.0'C");//��ʾ����"T:00.0'C"
	LCD_ShowChar(0x86,0xdf);/*��ʾ�ַ�*/
	
	LCD_ShowString(0xc0,"PH:00.0 TDS:0000");//��ʾһ���ַ��Ŵ�
}

void LCD_Scan(void)
{
	//��ʾ�¶� PH ���Ƕ�
	LCD_ShowNum(0x82,temp_value_int,2);
	LCD_ShowNum(0x85,temp_value_point,1);
	
	LCD_ShowNum(0xc3,ph/10,2);
	LCD_ShowNum(0xc6,ph%10,1);
	
	LCD_ShowNum(0xcc,zhuodu,4);
}



