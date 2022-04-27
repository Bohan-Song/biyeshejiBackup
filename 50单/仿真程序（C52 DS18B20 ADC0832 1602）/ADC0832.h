#ifndef ADC0832_H
#define ADC0832_H

sbit AD0832_CS=P1^0; //使能。
sbit AD0832_CLK=P1^1;//时钟
sbit AD0832_DO=P1^3; // 数据输出
sbit AD0832_DI=P1^2;//数据输入

extern unsigned char CH1,CH2;

unsigned char ADconv(unsigned char CH);

#endif
