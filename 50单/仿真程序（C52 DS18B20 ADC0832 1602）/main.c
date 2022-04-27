#include<head.h>

uint ph=0,zhuodu=0;

void Port_Init(void)
//四个端口初始化，0xff转化为2进制就是1111 1111
//分别对应I/O的8个口线 端口8个引脚均输出高电平
{
	P0 = 0xff;
    P1 = 0xff;
	P2 = 0xff;
	P3 = 0xff;
}

void main()	
{
	u16 times=0;
	
	Port_Init();				//端口初始化
	LCD_Init();					//LCD初始化
	DQ_init();					//DS18B20初始化
	
	while(1)
	{
		ph = ADconv(CH1)/2;		//获得双通道ch0=“+”计算返回值
		zhuodu = ADconv(CH2)*4; //获得双通道ch0=“-”计算返回值
		if(zhuodu<1024)
		{
			zhuodu=1024-zhuodu; //计算浊度值
		}
		else
		{
			zhuodu=0;			//首次未采集数据错误异常处理
		}
		
		times++;				//times自加 相当于times = times + 1;
		if(times>=100)
		{
			times=0;			//当times循环超过100置为0 用于下次循环 同时每100次循环计算下面的温度值和LCD刷新
			Tempt();			//循环获取温度值
			LCD_Scan();			//LCD数据刷新
		}
	}
}





