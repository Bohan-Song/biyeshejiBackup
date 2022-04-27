#include<head.h>

void delay_ms(uint ms)	   //延时1ms * ms
{
	//通过循环方式延迟
	uint x,y;
	for(x=ms;x>0;x--)
		for(y=113;y>0;y--);
}

void write_com(uchar com)    //写命令
{
	lcdrs=0;
	P0=com;
	delay_ms(2);//延迟2ms等待
	lcden=1;	//置为1
	delay_ms(2);//延迟2ms等待
	lcden=0;	//置为0
}

void write_data(uchar dat)	  //写数据
{
	lcdrs=1;
	P0=dat;
	delay_ms(2);//延迟2ms等待
	lcden=1;	//置为1
	delay_ms(2);//延迟2ms等待
	lcden=0;	//置为0
}
/******************************************************************************
函数说明：显示字符
入口数据：x,y    起点坐标
num    要显示的字符
mode   1叠加方式  0非叠加方式
返回值：  无
******************************************************************************/
void LCD_ShowChar(uchar x,uchar dat)
{
	write_com(x);//写命令
	write_data(dat);//写数据
}

//m^n函数
uint LCD_pow(uchar m,uchar n)
{
	uint result=1;	 
	while(n--)result*=m; //等同于result = result * m;
	return result;
}		

//显示N个数字
//x :坐标	 
//len :数字的位数
//num:数值(0~65536);	 		  
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

//显示一个字符号串
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

void LCD_Init(void)	           //1602液晶初始化
{
	lcden=0;
	write_com(0x38);/*显示模式设置*/ 
	write_com(0x0c);//设置开显示,不显示光标
	write_com(0x06);
	write_com(0x01);/*显示清屏*/ 
	write_com(0x80);//初始指针指向第一行

	LCD_ShowString(0x80,"T:00.0'C");//显示数据"T:00.0'C"
	LCD_ShowChar(0x86,0xdf);/*显示字符*/
	
	LCD_ShowString(0xc0,"PH:00.0 TDS:0000");//显示一个字符号串
}

void LCD_Scan(void)
{
	//显示温度 PH 和浊度
	LCD_ShowNum(0x82,temp_value_int,2);
	LCD_ShowNum(0x85,temp_value_point,1);
	
	LCD_ShowNum(0xc3,ph/10,2);
	LCD_ShowNum(0xc6,ph%10,1);
	
	LCD_ShowNum(0xcc,zhuodu,4);
}



