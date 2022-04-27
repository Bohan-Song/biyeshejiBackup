#ifndef	__XPT2046_H_
#define __XPT2046_H_

//---����ʹ�õ�IO��---//
sbit CLK  = P1^0;	  //ʱ��
sbit CS   = P1^1;	  //Ƭѡ
sbit DIN  = P1^2;	  //����
sbit DOUT = P1^3;	  //���

extern u16 AD_value[4];

void delay_ms(uint ms);
uint Read_AD_Data(uchar cmd);
uint XPT_SPI_Read(void);
void XPT_SPI_Write(uchar dat);
uint AD_Work(unsigned char ch);
void AD_WorkAll(void);

#define CH0 0x94  //������ͨ��ʱ��CH1ͨ������Ϊ0V
#define CH1 0xD4  //������ͨ��ʱ��CH0ͨ������Ϊ0V
#define CH2 0xA4  //��ͨ���ڲ��з�ѹ����2.5K 7.5K������Ϊ1/4�������ϳ���4��Ϊʵ��ֵ,��ͨ��������Ҫ�ӵ�ѹ�����·
#define CH3 0xE4

#endif





