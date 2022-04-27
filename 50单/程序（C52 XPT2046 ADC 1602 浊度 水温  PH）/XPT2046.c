#include <head.h>

u16 AD_value[4]={0};

//void delay_ms(uint ms)	   //延时1ms * ms
//{
//	uint x,y;
//	for(x=ms;x>0;x--)
//		for(y=113;y>0;y--);
//}

/****************************************************************************
*函数名：SPI_Write
*输  入：dat：写入数据
*输  出：无
*功  能：使用SPI写入数据
****************************************************************************/

void XPT_SPI_Write(uchar dat)
{
	uchar i;
	CLK = 0;
	for(i=0; i<8; i++)
	{
		DIN = dat >> 7;  	//放置最高位
		dat <<= 1;
		CLK = 0;			//上升沿放置数据

		CLK = 1;

	}
}
/****************************************************************************
*函数名：SPI_Read
*输  入：无
*输  出：dat：读取 到的数据
*功  能：使用SPI读取数据
****************************************************************************/

uint XPT_SPI_Read(void)
{
	uint i, dat=0;
	CLK = 0;
	for(i=0; i<12; i++)		//接收12位数据
	{
		dat <<= 1;

		CLK = 1;
		CLK = 0;

		dat |= DOUT;

	}
	return dat;	
}

/****************************************************************************
*函数名：Read_AD_Data
*输  入：cmd：读取的X或者Y
*输  出：endValue：最终信号处理后返回的值
*功  能：读取触摸数据
****************************************************************************/
uint Read_AD_Data(uchar cmd)
{
	uchar i;
	uint AD_Value;
	CLK = 0;
	CS  = 0;
	XPT_SPI_Write(cmd);
	for(i=6; i>0; i--); 	//延时等待转换结果
	CLK = 1;	  //发送一个时钟周期，清除BUSY
	_nop_();
	_nop_();
	CLK = 0;
	_nop_();
	_nop_();
	AD_Value = XPT_SPI_Read();
	CS = 1;
	
	if(cmd==CH2)
	{
		AD_Value = AD_Value*4;
	}
	
	return AD_Value;	
}

uint AD_Work(unsigned char ch)  
{
	uint AD_val;
	float AD_num;
	
	unsigned int i;
	for(i=0;i<100;i++)				//用100次循环来计算平均值，从而减少采样的误差
	{
		AD_num+=Read_AD_Data(ch);	//将每次循环的值累加到AD_num，等同于AD_num = AD_num + Read_AD_Data(ch);
	}
	AD_num=AD_num/100;				//平均值
	AD_val=(uint)AD_num;			//float类型强制转换成无符号整型

	return AD_val;					//将最终的值作为返回值返回
}


//XPT2046 4个通道是通过选择器选择，不能并行测量，可以分开测量
//4个通道同时测量的程序
void AD_WorkAll(void)
{
	static tt=0;  						//声明静态变量tt初始化为0
	
	tt++;		  						//自加 tt=tt+1
	if(tt==5)							//当tt等于5时
	{
		AD_value[0] = AD_Work(CH0);		//数组AD_value[0]为第1个通道计算的值
	}
	
	if(tt==10)							//当tt等于10时
	{
		AD_value[1] = AD_Work(CH1);		//数组AD_value[1]为第2个通道计算的值
	}
	
	if(tt==15)							//当tt等于15时
	{
		AD_value[2] = AD_Work(CH2);		//数组AD_value[2]为第3个通道计算的值
	}
	
	if(tt==20)							//当tt等于20时
	{
		AD_value[3] = AD_Work(CH3);		//数组AD_value[3]为第4个通道计算的值
	}
	
	if(tt>=20)							//当tt等于20时
	{
		tt=0;							//将tt置为初始化0，下次循环重新计算
	}
}