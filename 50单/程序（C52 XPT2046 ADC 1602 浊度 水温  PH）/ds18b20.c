#include <head.h>

uchar data temp_DQ_data[2];   	  //温度值的16位 高八位 低八位
uchar data temp_work_data[5];	  	//温度转换数据，前四位分别为百、十 、个、小数后一位
uchar code dis_dec[17]={0,1,1,2,2,3,3,4,4,5,5,6,7,8,8,9,9};	 //显示小数
uchar temp_value_int,temp_value_point;
uchar temp_warn=30;
						    
void delay1us(uchar t) 
{
	for(;t>0;t--); 
}

void DQ_reset(void)
{
  DQ = 1;               //DQ复位,不要也可行
	delay1us(1);        //稍做延时
	DQ = 0;             //单片机拉低总线
	delay1us(50);       //精确延时，维持至少480us
	DQ = 1;             //释放总线，即拉高了总线
	while(DQ);
	delay1us(45);       //此处延时有足够,确保能让DS18B20发出存在脉冲       
}

void DQ_write(uchar a)
{ 
   uchar i;
   for(i=8;i>0;i--)
   {
     DQ=1;		//DQ给1	
	  _nop_();//运行2个机器周期
	  _nop_();
      DQ=0;	//DQ给0
	  _nop_();//运行5个机器周期
	  _nop_();
	  _nop_();
	  _nop_();
	  _nop_();
		DQ=a&0x01;//取a的最低位值的运算 两个操作数上对应位的值如果均为1，则结果对应位上值为1，否则结果对应位上值为0。
		delay1us(6); //延迟6us
		a=a/2;
   }
   DQ=1;//dq拉1
   delay1us(1);//延迟1us   
}


uchar DQ_read(void)
{  
   uchar i;
   uchar value=0;
   for(i=8;i>0;i--)
   {
    DQ=1;
	  _nop_();//运行2个机器周期
	  _nop_();
    value>>=1; //右移1位
	  DQ=0;    
	  _nop_();//运行4个机器周期
	  _nop_();
	  _nop_();
	  _nop_();
    DQ=1;
	  _nop_();//运行4个机器周期
	  _nop_();
	  _nop_();
	  _nop_();
    if(DQ)
	  {
	  	value|=0x80;//最高位置1，其它位保持不变
    }
    delay1us(6);	  //延迟6us
   }
   DQ = 1;
   return(value);//返回value
} 

void read_temp(void)
{  
   DQ_reset(); 	//先复位
   delay1us(2);	//延迟2us
   DQ_write(0xcc);   //跳过读取序列号操作
   DQ_write(0xbe);   //温度转换指令
   temp_DQ_data[0]=DQ_read();//读取温度值共16位，先读低字节
   temp_DQ_data[1]=DQ_read();//再读高字节
}

void Temp_Work(void)
{
	uchar fuhao=0;       
	if(temp_DQ_data[1]>127)
	{
  	temp_DQ_data[1]=(256-temp_DQ_data[1]);
		temp_DQ_data[0]=(256-temp_DQ_data[0]);
		fuhao=1;	 														//给出负号标志
	}
  temp_work_data[4]=temp_DQ_data[0]&0x0f;//温度转换的小数后一位数据通过temp_DQ_data的第八位计算
	temp_value_point = dis_dec[temp_work_data[4]];//通过小数后一位数据计算显示小数，存到temp_value_point临时变量中
	temp_work_data[0]=temp_value_point;//存入百位的值
  temp_work_data[4]=((temp_DQ_data[0]&0xf0)>>4)|((temp_DQ_data[1]&0x0f)<<4);//通过高八位和第八位和0xf0按位与左右移位后计算小数值
	temp_value_int = temp_work_data[4];	//temp_work_data[4]值存入temp_value_int临时变量（整型）
	temp_work_data[3]=temp_work_data[4]/100;//通过/100计算得小数值
	temp_work_data[1]=temp_work_data[4]%100;//通过%100取余数 /10 %100 分别计算得个位十位百位
	temp_work_data[2]=temp_work_data[1]/10;//除以10
	temp_work_data[1]=temp_work_data[1]%10;//除以10取余数
	if(!temp_work_data[3])
	{
		temp_work_data[3] = 10;//个位赋值运算
		if(!temp_work_data[2])
		{
			temp_work_data[2] = 10;//十位赋值
		}
	}

	if(fuhao)	 		//LCD1602液晶显示‘-’
	{
//		write_com(0x89);
//		write_data('-');
	}
}


void DQ_init(void)
{
   DQ_reset();		 //先reset复位
   delay1us(1);		 //延迟1us
   DQ_write(0xcc);   //写跳过读ROM指令
   DQ_write(0x44);	 //写温度转换指令
}

void Tempt(void)
{
	DQ_init();		//初始化
  read_temp();
  Temp_Work();
}
