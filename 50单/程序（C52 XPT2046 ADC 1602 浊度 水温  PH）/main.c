#include<head.h>

float ftmp;
uint times,ph=0,zhuodu=0;

void Port_Init(void)//�ĸ��˿ڳ�ʼ����0xffת��Ϊ2���ƾ���1111 1111,�ֱ��ӦI/O��8������ �˿�8�����ž�����ߵ�ƽ
{
	P0 = 0xff;
	P1 = 0xff;
	P2 = 0xff;
	P3 = 0xff; 	
}

void main()
{
	Port_Init(); 				//�˿ڳ�ʼ��
	DQ_init();					//DS18B20��ʼ��
	Tempt();					//DS18B20�����¶�
	while(temp_value_int==85)
	{
		Tempt();				//DS18B20�����¶�
	}
	
	LCD_Init();					//LCD��ʼ��
	
	while(1)
	{
		AD_WorkAll();			//XPT2046 ADת��
			
		ftmp = 23.977-((5.7887*5.0*AD_value[0])/4096); //���������ڵ���ʱ���軻��ɵ�ѹֵ
		ph = (uint)(ftmp*10);	//��������ֵ��10�� ��floatǿ��ת����int��
			
		ftmp = AD_value[1]/4;	//����ֵ����ftmp
		
		if(zhuodu<1024)			
		{
			zhuodu=1024-(uint)ftmp; //�����Ƕ�ֵ
		}
		else
		{
			zhuodu=0;				//�״�δ�ɼ����ݴ����쳣����
		}
		
		Tempt();					//ѭ����ȡ�¶�ֵ
		LCD_Scan();					//LCD����ˢ��
	}
}



	
