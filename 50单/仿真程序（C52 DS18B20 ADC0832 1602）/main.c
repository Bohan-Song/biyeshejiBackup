#include<head.h>

uint ph=0,zhuodu=0;

void Port_Init(void)
//�ĸ��˿ڳ�ʼ����0xffת��Ϊ2���ƾ���1111 1111
//�ֱ��ӦI/O��8������ �˿�8�����ž�����ߵ�ƽ
{
	P0 = 0xff;
    P1 = 0xff;
	P2 = 0xff;
	P3 = 0xff;
}

void main()	
{
	u16 times=0;
	
	Port_Init();				//�˿ڳ�ʼ��
	LCD_Init();					//LCD��ʼ��
	DQ_init();					//DS18B20��ʼ��
	
	while(1)
	{
		ph = ADconv(CH1)/2;		//���˫ͨ��ch0=��+�����㷵��ֵ
		zhuodu = ADconv(CH2)*4; //���˫ͨ��ch0=��-�����㷵��ֵ
		if(zhuodu<1024)
		{
			zhuodu=1024-zhuodu; //�����Ƕ�ֵ
		}
		else
		{
			zhuodu=0;			//�״�δ�ɼ����ݴ����쳣����
		}
		
		times++;				//times�Լ� �൱��times = times + 1;
		if(times>=100)
		{
			times=0;			//��timesѭ������100��Ϊ0 �����´�ѭ�� ͬʱÿ100��ѭ������������¶�ֵ��LCDˢ��
			Tempt();			//ѭ����ȡ�¶�ֵ
			LCD_Scan();			//LCD����ˢ��
		}
	}
}





