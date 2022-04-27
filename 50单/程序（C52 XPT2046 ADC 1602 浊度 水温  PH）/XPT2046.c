#include <head.h>

u16 AD_value[4]={0};

//void delay_ms(uint ms)	   //��ʱ1ms * ms
//{
//	uint x,y;
//	for(x=ms;x>0;x--)
//		for(y=113;y>0;y--);
//}

/****************************************************************************
*��������SPI_Write
*��  �룺dat��д������
*��  ������
*��  �ܣ�ʹ��SPIд������
****************************************************************************/

void XPT_SPI_Write(uchar dat)
{
	uchar i;
	CLK = 0;
	for(i=0; i<8; i++)
	{
		DIN = dat >> 7;  	//�������λ
		dat <<= 1;
		CLK = 0;			//�����ط�������

		CLK = 1;

	}
}
/****************************************************************************
*��������SPI_Read
*��  �룺��
*��  ����dat����ȡ ��������
*��  �ܣ�ʹ��SPI��ȡ����
****************************************************************************/

uint XPT_SPI_Read(void)
{
	uint i, dat=0;
	CLK = 0;
	for(i=0; i<12; i++)		//����12λ����
	{
		dat <<= 1;

		CLK = 1;
		CLK = 0;

		dat |= DOUT;

	}
	return dat;	
}

/****************************************************************************
*��������Read_AD_Data
*��  �룺cmd����ȡ��X����Y
*��  ����endValue�������źŴ���󷵻ص�ֵ
*��  �ܣ���ȡ��������
****************************************************************************/
uint Read_AD_Data(uchar cmd)
{
	uchar i;
	uint AD_Value;
	CLK = 0;
	CS  = 0;
	XPT_SPI_Write(cmd);
	for(i=6; i>0; i--); 	//��ʱ�ȴ�ת�����
	CLK = 1;	  //����һ��ʱ�����ڣ����BUSY
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
	for(i=0;i<100;i++)				//��100��ѭ��������ƽ��ֵ���Ӷ����ٲ��������
	{
		AD_num+=Read_AD_Data(ch);	//��ÿ��ѭ����ֵ�ۼӵ�AD_num����ͬ��AD_num = AD_num + Read_AD_Data(ch);
	}
	AD_num=AD_num/100;				//ƽ��ֵ
	AD_val=(uint)AD_num;			//float����ǿ��ת�����޷�������

	return AD_val;					//�����յ�ֵ��Ϊ����ֵ����
}


//XPT2046 4��ͨ����ͨ��ѡ����ѡ�񣬲��ܲ��в��������Էֿ�����
//4��ͨ��ͬʱ�����ĳ���
void AD_WorkAll(void)
{
	static tt=0;  						//������̬����tt��ʼ��Ϊ0
	
	tt++;		  						//�Լ� tt=tt+1
	if(tt==5)							//��tt����5ʱ
	{
		AD_value[0] = AD_Work(CH0);		//����AD_value[0]Ϊ��1��ͨ�������ֵ
	}
	
	if(tt==10)							//��tt����10ʱ
	{
		AD_value[1] = AD_Work(CH1);		//����AD_value[1]Ϊ��2��ͨ�������ֵ
	}
	
	if(tt==15)							//��tt����15ʱ
	{
		AD_value[2] = AD_Work(CH2);		//����AD_value[2]Ϊ��3��ͨ�������ֵ
	}
	
	if(tt==20)							//��tt����20ʱ
	{
		AD_value[3] = AD_Work(CH3);		//����AD_value[3]Ϊ��4��ͨ�������ֵ
	}
	
	if(tt>=20)							//��tt����20ʱ
	{
		tt=0;							//��tt��Ϊ��ʼ��0���´�ѭ�����¼���
	}
}