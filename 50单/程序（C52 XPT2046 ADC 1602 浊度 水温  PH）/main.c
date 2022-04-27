#include<head.h>

float ftmp;
uint times,ph=0,zhuodu=0;

void Port_Init(void)//四个端口初始化，0xff转化为2进制就是1111 1111,分别对应I/O的8个口线 端口8个引脚均输出高电平
{
	P0 = 0xff;
	P1 = 0xff;
	P2 = 0xff;
	P3 = 0xff; 	
}

void main()
{
	Port_Init(); 				//端口初始化
	DQ_init();					//DS18B20初始化
	Tempt();					//DS18B20计算温度
	while(temp_value_int==85)
	{
		Tempt();				//DS18B20计算温度
	}
	
	LCD_Init();					//LCD初始化
	
	while(1)
	{
		AD_WorkAll();			//XPT2046 AD转换
			
		ftmp = 23.977-((5.7887*5.0*AD_value[0])/4096); //计算周期内的临时电阻换算成电压值
		ph = (uint)(ftmp*10);	//测量的数值乘10后 由float强制转换成int型
			
		ftmp = AD_value[1]/4;	//数组值返给ftmp
		
		if(zhuodu<1024)			
		{
			zhuodu=1024-(uint)ftmp; //计算浊度值
		}
		else
		{
			zhuodu=0;				//首次未采集数据错误异常处理
		}
		
		Tempt();					//循环获取温度值
		LCD_Scan();					//LCD数据刷新
	}
}



	
