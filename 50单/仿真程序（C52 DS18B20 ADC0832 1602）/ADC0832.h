#ifndef ADC0832_H
#define ADC0832_H

sbit AD0832_CS=P1^0; //ʹ�ܡ�
sbit AD0832_CLK=P1^1;//ʱ��
sbit AD0832_DO=P1^3; // �������
sbit AD0832_DI=P1^2;//��������

extern unsigned char CH1,CH2;

unsigned char ADconv(unsigned char CH);

#endif
