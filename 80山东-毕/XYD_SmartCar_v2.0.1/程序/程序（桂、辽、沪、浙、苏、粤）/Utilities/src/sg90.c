#include "sg90.h"
#include "key.h"
char chewei_buf[50];
void TIM4_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能定时器4时钟
 	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD , ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE); //Timer4部分重映射  TIM4_CH3->PD14 TIM4_CH4-> PD15
 
   //设置该引脚为复用输出功能,输出TIM4_CH3的PWM脉冲波形	GPIOD.14 GPIOD.15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15; //TIM4_CH3  TIM4_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIO

   //初始化TIM4
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	  //根据T指定的参数初始化外设TIM4 OC3  TIM4 OC4
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR3上的预装载寄存器
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR4上的预装载寄存器
	TIM_Cmd(TIM4, ENABLE);  //使能TIM4

}
void openLan()
{
	TIM_SetCompare3(TIM4,900);//设置180°舵机旋转 7200-20ms   2.5ms --- 7200/20*2.5 =900
}
void closeLan()
{
	TIM_SetCompare3(TIM4,180);//设置0°舵机旋转 7200-20ms   0.5ms --- 7200/20*0.5 =180
}
void isCar(float juli,char flag)  //门口超声波检测 判断是否有车到来
{
	if(juli<50)         //设置50cm距离差
	{
		//检测到车子
		//flag 车牌是否检测
		if(flag==1)
		{
			openLan();//打开栅栏
		}
		else
		{
			closeLan();
		}
		
	}
	else
	{
		//没有检测到
			closeLan();
	}
}
void RecommendChewei(u8 chewei)
{
	//车位是0 推荐1车位
 	if(chewei==0)
	{
	LCD_ShowChar(35+8*0,10,'G',0);
	LCD_ShowChar(35+8*1,10,'o',0);
	LCD_ShowChar(35+8*2,10,' ',0);
	LCD_ShowChar(35+8*3,10,'t',0);
	LCD_ShowChar(35+8*4,10,'o',0);
	LCD_ShowChar(35+8*5,10,' ',0);
	
	LCD_ShowChar(35+8*6,10,'A',0);
	LCD_ShowChar(35+8*7,10,'1',0);
	LCD_ShowChar(35+8*8,10,' ',0);
	LCD_ShowChar(35+8*9,10,'G',0);
	LCD_ShowChar(35+8*10,10,'1',0);	
  LCD_ShowChar(35+8*11,10,'0',0);
	LCD_ShowChar(35+8*12,10,'0',0);
	LCD_ShowChar(35+8*13,10,'L',0);

//	LCD_ShowChar(35+8*18,10,'r',0);
//	LCD_ShowChar(35+8*19,10,'i',0);
//	LCD_ShowChar(35+8*20,10,'c',0);
//	LCD_ShowChar(35+8*21,10,'e',0);
	}
	else if(chewei==1)
	{	
	LCD_ShowChar(35+8*0,10,'G',0);
	LCD_ShowChar(35+8*1,10,'o',0);
	LCD_ShowChar(35+8*2,10,' ',0);
	LCD_ShowChar(35+8*3,10,'t',0);
	LCD_ShowChar(35+8*4,10,'o',0);
	LCD_ShowChar(35+8*5,10,' ',0);
	
	LCD_ShowChar(35+8*6,10,'A',0);
	LCD_ShowChar(35+8*7,10,'2',0);
	LCD_ShowChar(35+8*8,10,' ',0);
	LCD_ShowChar(35+8*9,10,'G',0);
	LCD_ShowChar(35+8*10,10,'1',0);	
  LCD_ShowChar(35+8*11,10,'0',0);
	LCD_ShowChar(35+8*12,10,'0',0);
	LCD_ShowChar(35+8*13,10,'L',0);
	}
	else if(chewei==2)
	{
	LCD_ShowChar(35+8*0,10,'G',0);
	LCD_ShowChar(35+8*1,10,'o',0);
	LCD_ShowChar(35+8*2,10,' ',0);
	LCD_ShowChar(35+8*3,10,'t',0);
	LCD_ShowChar(35+8*4,10,'o',0);
	LCD_ShowChar(35+8*5,10,' ',0);
	
	LCD_ShowChar(35+8*6,10,'B',0);
	LCD_ShowChar(35+8*7,10,'1',0);
	LCD_ShowChar(35+8*8,10,' ',0);
	LCD_ShowChar(35+8*9,10,'G',0);
	LCD_ShowChar(35+8*10,10,' ',0);	
  LCD_ShowChar(35+8*11,10,'9',0);
	LCD_ShowChar(35+8*12,10,'0',0);
	LCD_ShowChar(35+8*13,10,'R',0);
	}
	else if(chewei==3)
	{
	LCD_ShowChar(35+8*0,10,'G',0);
	LCD_ShowChar(35+8*1,10,'o',0);
	LCD_ShowChar(35+8*2,10,' ',0);
	LCD_ShowChar(35+8*3,10,'t',0);
	LCD_ShowChar(35+8*4,10,'o',0);
	LCD_ShowChar(35+8*5,10,' ',0);
	
	LCD_ShowChar(35+8*6,10,'B',0);
	LCD_ShowChar(35+8*7,10,'2',0);
	LCD_ShowChar(35+8*8,10,' ',0);
	LCD_ShowChar(35+8*9,10,'G',0);
	LCD_ShowChar(35+8*10,10,'1',0);	
  LCD_ShowChar(35+8*11,10,'0',0);
	LCD_ShowChar(35+8*12,10,'0',0);
	LCD_ShowChar(35+8*13,10,'R',0);
	}
	else if(chewei==4)
	{
	LCD_ShowChar(35+8*0,10,'N',0);
	LCD_ShowChar(35+8*1,10,'o',0);
	LCD_ShowChar(35+8*2,10,' ',0);
	LCD_ShowChar(35+8*3,10,'C',0);
	LCD_ShowChar(35+8*4,10,'h',0);
	LCD_ShowChar(35+8*5,10,'e',0);
	
	LCD_ShowChar(35+8*6,10,' ',0);
	LCD_ShowChar(35+8*7,10,'W',0);
	LCD_ShowChar(35+8*8,10,'e',0);
	LCD_ShowChar(35+8*9,10,'i',0);
	LCD_ShowChar(35+8*10,10,' ',0);	
	}
	
}
char * state(u8 flag)
{
	if(flag==0)
	{
		return "0000";
	}
	else if(flag==1)
	{
		return "0001";
	}
	else if(flag==2)
	{
		return "0011";
	}
	else if(flag==3)
	{
		return "0111";
	}
	else
	{
		return "1111";
	}
}
char * stopC()
{
	sprintf(chewei_buf,"%d%d%d%d",HC1,HC2,HC3,HC4);
	return chewei_buf;
}
int check_C(char* cuurent,char* chewei)
{
	int num;
	while(*(cuurent++)==*(chewei++))
	{
		num++;
	}
	return num+1;
}
