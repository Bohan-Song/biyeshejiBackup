#include <head.h>

uchar data temp_DQ_data[2];   	  //�¶�ֵ��16λ �߰�λ �Ͱ�λ
uchar data temp_work_data[5];	  	//�¶�ת�����ݣ�ǰ��λ�ֱ�Ϊ�١�ʮ ������С����һλ
uchar code dis_dec[17]={0,1,1,2,2,3,3,4,4,5,5,6,7,8,8,9,9};	 //��ʾС��
uchar temp_value_int,temp_value_point;
uchar temp_warn=30;
						    
void delay1us(uchar t) 
{
	for(;t>0;t--); 
}

void DQ_reset(void)
{
  DQ = 1;               //DQ��λ,��ҪҲ����
	delay1us(1);        //������ʱ
	DQ = 0;             //��Ƭ����������
	delay1us(50);       //��ȷ��ʱ��ά������480us
	DQ = 1;             //�ͷ����ߣ�������������
	while(DQ);
	delay1us(45);       //�˴���ʱ���㹻,ȷ������DS18B20������������       
}

void DQ_write(uchar a)
{ 
   uchar i;
   for(i=8;i>0;i--)
   {
     DQ=1;		//DQ��1	
	  _nop_();//����2����������
	  _nop_();
      DQ=0;	//DQ��0
	  _nop_();//����5����������
	  _nop_();
	  _nop_();
	  _nop_();
	  _nop_();
		DQ=a&0x01;//ȡa�����λֵ������ �����������϶�Ӧλ��ֵ�����Ϊ1��������Ӧλ��ֵΪ1����������Ӧλ��ֵΪ0��
		delay1us(6); //�ӳ�6us
		a=a/2;
   }
   DQ=1;//dq��1
   delay1us(1);//�ӳ�1us   
}


uchar DQ_read(void)
{  
   uchar i;
   uchar value=0;
   for(i=8;i>0;i--)
   {
    DQ=1;
	  _nop_();//����2����������
	  _nop_();
    value>>=1; //����1λ
	  DQ=0;    
	  _nop_();//����4����������
	  _nop_();
	  _nop_();
	  _nop_();
    DQ=1;
	  _nop_();//����4����������
	  _nop_();
	  _nop_();
	  _nop_();
    if(DQ)
	  {
	  	value|=0x80;//���λ��1������λ���ֲ���
    }
    delay1us(6);	  //�ӳ�6us
   }
   DQ = 1;
   return(value);//����value
} 

void read_temp(void)
{  
   DQ_reset(); 	//�ȸ�λ
   delay1us(2);	//�ӳ�2us
   DQ_write(0xcc);   //������ȡ���кŲ���
   DQ_write(0xbe);   //�¶�ת��ָ��
   temp_DQ_data[0]=DQ_read();//��ȡ�¶�ֵ��16λ���ȶ����ֽ�
   temp_DQ_data[1]=DQ_read();//�ٶ����ֽ�
}

void Temp_Work(void)
{
	uchar fuhao=0;       
	if(temp_DQ_data[1]>127)
	{
  	temp_DQ_data[1]=(256-temp_DQ_data[1]);
		temp_DQ_data[0]=(256-temp_DQ_data[0]);
		fuhao=1;	 														//�������ű�־
	}
  temp_work_data[4]=temp_DQ_data[0]&0x0f;//�¶�ת����С����һλ����ͨ��temp_DQ_data�ĵڰ�λ����
	temp_value_point = dis_dec[temp_work_data[4]];//ͨ��С����һλ���ݼ�����ʾС�����浽temp_value_point��ʱ������
	temp_work_data[0]=temp_value_point;//�����λ��ֵ
  temp_work_data[4]=((temp_DQ_data[0]&0xf0)>>4)|((temp_DQ_data[1]&0x0f)<<4);//ͨ���߰�λ�͵ڰ�λ��0xf0��λ��������λ�����С��ֵ
	temp_value_int = temp_work_data[4];	//temp_work_data[4]ֵ����temp_value_int��ʱ���������ͣ�
	temp_work_data[3]=temp_work_data[4]/100;//ͨ��/100�����С��ֵ
	temp_work_data[1]=temp_work_data[4]%100;//ͨ��%100ȡ���� /10 %100 �ֱ����ø�λʮλ��λ
	temp_work_data[2]=temp_work_data[1]/10;//����10
	temp_work_data[1]=temp_work_data[1]%10;//����10ȡ����
	if(!temp_work_data[3])
	{
		temp_work_data[3] = 10;//��λ��ֵ����
		if(!temp_work_data[2])
		{
			temp_work_data[2] = 10;//ʮλ��ֵ
		}
	}

	if(fuhao)	 		//LCD1602Һ����ʾ��-��
	{
//		write_com(0x89);
//		write_data('-');
	}
}


void DQ_init(void)
{
   DQ_reset();		 //��reset��λ
   delay1us(1);		 //�ӳ�1us
   DQ_write(0xcc);   //д������ROMָ��
   DQ_write(0x44);	 //д�¶�ת��ָ��
}

void Tempt(void)
{
	DQ_init();		//��ʼ��
  read_temp();
  Temp_Work();
}
