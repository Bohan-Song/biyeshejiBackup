#include "sg90.h"
#include "key.h"
char chewei_buf[50];
void TIM4_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ�ܶ�ʱ��4ʱ��
 	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD , ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE); //Timer4������ӳ��  TIM4_CH3->PD14 TIM4_CH4-> PD15
 
   //���ø�����Ϊ�����������,���TIM4_CH3��PWM���岨��	GPIOD.14 GPIOD.15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15; //TIM4_CH3  TIM4_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIO

   //��ʼ��TIM4
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM3 Channel2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	  //����Tָ���Ĳ�����ʼ������TIM4 OC3  TIM4 OC4
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR3�ϵ�Ԥװ�ؼĴ���
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR4�ϵ�Ԥװ�ؼĴ���
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM4

}
void openLan()
{
	TIM_SetCompare3(TIM4,900);//����180������ת 7200-20ms   2.5ms --- 7200/20*2.5 =900
}
void closeLan()
{
	TIM_SetCompare3(TIM4,180);//����0������ת 7200-20ms   0.5ms --- 7200/20*0.5 =180
}
void isCar(float juli,char flag)  //�ſڳ�������� �ж��Ƿ��г�����
{
	if(juli<50)         //����50cm�����
	{
		//��⵽����
		//flag �����Ƿ���
		if(flag==1)
		{
			openLan();//��դ��
		}
		else
		{
			closeLan();
		}
		
	}
	else
	{
		//û�м�⵽
			closeLan();
	}
}
void RecommendChewei(u8 chewei)
{
	//��λ��0 �Ƽ�1��λ
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
