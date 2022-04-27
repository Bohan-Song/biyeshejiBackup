#include "ir.h"

#define RCKeyNum 		17
#define RCIRLength 	4

uint8_t IR_key[17] ="123456789*0#+LOR-";

u8 RemoteControl_Table[RCKeyNum][RCIRLength] = {
	{0x00,0xFF,0x45,0xBA},
	{0x00,0xFF,0x46,0xB9},
	{0x00,0xFF,0x47,0xB8},	
	{0x00,0xFF,0x44,0xBB},	
	{0x00,0xFF,0x40,0xBF},	
	{0x00,0xFF,0x43,0xBC},	
	{0x00,0xFF,0x07,0xF8},	
	{0x00,0xFF,0x15,0xEA},	
	{0x00,0xFF,0x09,0xF6},	
	{0x00,0xFF,0x16,0xE9},	
	{0x00,0xFF,0x19,0xE6},	
	{0x00,0xFF,0x0D,0xF2},		
	{0x00,0xFF,0x18,0xE7},		
	{0x00,0xFF,0x08,0xF7},	
	{0x00,0xFF,0x1C,0xE3},	
	{0x00,0xFF,0x5A,0xA5},		
	{0x00,0xFF,0x52,0xAD},		
};

u16 ir_buf[1024] = {0};
u16 ir_count = 0;
u16 ir_flag = 0;
void TIM2_IRQHandler(void)
{
	//更新中断
	if(TIM_GetFlagStatus(IR_TIM, TIM_FLAG_Update) == SET)
	{
		TIM_ClearFlag(IR_TIM, TIM_FLAG_Update);
		ir_flag = 1;
		Ir_RecvAnalysis();	//接收红外信号
//		TIM_Cmd(TIM2,DISABLE);
	}
	//捕获中断
	if(TIM_GetFlagStatus(IR_TIM, TIM_FLAG_CC2) == SET)
	{
		TIM_ClearFlag(IR_TIM, TIM_FLAG_CC2);
		if(ir_flag == 0)
		{
			ir_buf[ir_count++] = IR_TIM->CCR2;
			TIM_SetCounter(IR_TIM, 0);
			IR_TIM->CCER ^= (1<<5);				
		}
	}
}

//TIM2 CH2	PA1
void Tim2_Config(u16 psc, u16 arr)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	
	//开时钟
	IR_TIM_CLK_INIT(IR_TIM_CLK, ENABLE);
	IR_CLK_INIT(IR_CLK, ENABLE);
	//配置PA1
//	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = IR_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(IR_PORT, &GPIO_InitStructure);
	//配置TIM2 捕获功能
	TIM_ICInitStructure.TIM_Channel = IR_Channel;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0;
	TIM_ICInit(IR_TIM,&TIM_ICInitStructure);
	//配置TIM2 基本定时
  TIM_TimeBaseStructure.TIM_Period = arr - 1;
  TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(IR_TIM, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(IR_TIM, ENABLE);
	
	TIM_ITConfig(IR_TIM, TIM_IT_Update|TIM_IT_CC2, ENABLE);
	
	NVIC_SetPriority(TIM2_IRQn, 1);
	NVIC_EnableIRQ(TIM2_IRQn);
  /* TIM2 enable counter */
  TIM_Cmd(IR_TIM, ENABLE);		
}

//判断数据范围函数
//数据在给定的范围之内：返回1
//数据在给定的范围之外：返回0
//time1:待判断时间
//time2:标准时间
u8 Time_Range(u16 time1, u16 time2, u16 range1, u16 range2)
{
	if((time1 > (time2-range1)) && (time1 < (time2+range2)))
		return 1;
	else 
		return 0;
}

//校验遥控器按键
//正确，返回遥控器按键所对应的数组行号
//错误 -1  按键地址错误 不是这个遥控器
//错误 -2  地址正确，但是当前版本遥控器没有这个按键值
int Check_RemoteControlKey(u8 *buff)
{
	u8 i=0;
	int retn;
//	if(buff[0] != RemoteControl_Table[0][0] || buff[1] != RemoteControl_Table[0][1])
	if((buff[0]!=0x00) || (buff[1]!=0xFF))
		retn = -1;//地址错误
	for(i=0; i<RCKeyNum; i++)
	{
		if((buff[2]==RemoteControl_Table[i][2]) && (buff[3]==RemoteControl_Table[i][3]))
		{
			retn = i;
			break;
		}
		
	}
	if(i>=RCKeyNum)	retn = -2;
	return retn;
}


//返回值 
//0 解析成功
//1 没有接收完成
//2 引导码错误
//3 前半段数据错误
//4 后半段数据错误
IR_DATA_TypeDef ir = {0};
uint8_t IR_code = 0XFF;
u8 Ir_RecvAnalysis(void)
{
	u16 i = 0;
	u8 err;
	if(ir_flag == 0) return 1;
//	for(i=0; i<ir_count; i++)
//		printf("%d\r\n",ir_buf[i]);
	
	if(Time_Range(ir_buf[1],9000,1000,1000) == 0){
		err = 2;
		goto error;
	}
	if(Time_Range(ir_buf[2],4500,500,500) == 0){
		err = 2;
		goto error;
	}
	for(i=3; i<ir_count-1; i++)
	{
		if(Time_Range(ir_buf[i],560,200,200))
		{
			i++;
			if(Time_Range(ir_buf[i],560,200,200))
			{
				//数据0  0-7  data[0]  8-15 data[1]
				//先收到低位保存到低位，也可以反着
				ir.Ir_Data[ir.Ir_Length/8] &= ~(1<<(ir.Ir_Length%8));
				ir.Ir_Length++;
			}
			else if(Time_Range(ir_buf[i],1690,200,200)==1)
			{
				//数据1
				ir.Ir_Data[ir.Ir_Length/8] |= (1<<(ir.Ir_Length%8));
				ir.Ir_Length++;
			}
			else{
				err = 4;
				goto error;
			}			
		}
		else{
			err = 3;
			goto error;
		}
	}
//	for(i=0; i<ir.Ir_Length/8; i++)
//		printf("%02X\t",ir.Ir_Data[i]);
//	printf("\r\n");
	if(Check_RemoteControlKey(ir.Ir_Data) < 17 && Check_RemoteControlKey(ir.Ir_Data) >=0)
	{
		IR_code = IR_key[Check_RemoteControlKey(ir.Ir_Data)];
		return 0;
	}
		
error:
	memset(ir_buf,0,sizeof(ir_buf));
	memset(ir.Ir_Data,0,sizeof(ir.Ir_Data));
	ir.Ir_Length = 0;
	ir_count = 0;
	ir_flag = 0;
	TIM_Cmd(TIM2,ENABLE);
	if(err)	return err;
	else	return 0;
}



