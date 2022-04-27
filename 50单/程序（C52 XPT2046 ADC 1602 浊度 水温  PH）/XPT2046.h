#ifndef	__XPT2046_H_
#define __XPT2046_H_

//---定义使用的IO口---//
sbit CLK  = P1^0;	  //时钟
sbit CS   = P1^1;	  //片选
sbit DIN  = P1^2;	  //输入
sbit DOUT = P1^3;	  //输出

extern u16 AD_value[4];

void delay_ms(uint ms);
uint Read_AD_Data(uchar cmd);
uint XPT_SPI_Read(void);
void XPT_SPI_Write(uchar dat);
uint AD_Work(unsigned char ch);
void AD_WorkAll(void);

#define CH0 0x94  //测量该通道时，CH1通道不能为0V
#define CH1 0xD4  //测量该通道时，CH0通道不能为0V
#define CH2 0xA4  //该通道内部有分压电阻2.5K 7.5K，比例为1/4，程序上乘以4即为实际值,该通道输入需要加电压跟随电路
#define CH3 0xE4

#endif





