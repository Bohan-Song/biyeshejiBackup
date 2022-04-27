#include "main.h"
#include "bee.h"
#include "motor.h"
#include "timer.h"
#include "usart.h"
#include "SR.h"
#include "ir.h"
#include "tcrt.h"
extern u16 current_speed;
void delay_ms(int k)
{
			while(k--);
}
int main(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
  Systick_Config(SYSTICK_MS);
	
	
	USART_Config(112500);
	
	
	WATER_Config();
	BEE_Config();
	TIM3_PWM_Init(1000-1,72-1);  //这里频率给1.5k吧 72000000/72/1000=1k
	
	TIM4_PWM_Init(1000-1,72-1);
	//MOTOR_Config();
	u16 zyy=0;
	int lxy=0;
	int flag=1;
	int ppx=0;
	HCSR04_Config();
	float current_value=0.0;
	Tim2_Config(72,10000);
	TCRT5000I_Config();
	//Set_speed(500);
	char code;
	u8 number=0;
LED_Config();
	//两个按键  
	while(1)
	{	

//		current_value=Get_Length();
//		number=Ir_RecvAnalysis();
//		printf("\r\ncurrent value %f cm\r\n",current_value);
//		printf("\r\ncurrent number %d cm\r\n",number);
		
		if(IR_code== '*')
		{
			number=1;
			GPIO_ResetBits(GPIOC,GPIO_Pin_0);
			GPIO_SetBits(GPIOC,GPIO_Pin_2);
			GPIO_SetBits(GPIOC,GPIO_Pin_1);
			//Set_speed(500);
			//遥控模式
			
		}
		else if(IR_code=='0')
		{
			number=2;
			GPIO_SetBits(GPIOC,GPIO_Pin_0);
			GPIO_SetBits(GPIOC,GPIO_Pin_2);
			GPIO_ResetBits(GPIOC,GPIO_Pin_1);
			Set_speed(500);//循迹
		}
		else if(IR_code=='#')
		{
			number=3;
			GPIO_SetBits(GPIOC,GPIO_Pin_0);
			GPIO_ResetBits(GPIOC,GPIO_Pin_2);
			GPIO_SetBits(GPIOC,GPIO_Pin_1);
		}
		if(number==1)
		{
			Control_V(IR_code);
			printf("IR_Code is %c\r\n",IR_code);
			printf("current_speed is %d\r\n",current_speed);
					
		}
		else if(number==2)
		{
			TCRT5000I_Ctrl();
		}
		Delay_nop_nms(500);	
		
		
		
		
		

		
	}
}
