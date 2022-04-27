#include "hcsr04.h"


uint16_t SR04_TimeCount = 0;
/***************************************
函数名称：HCSR04_Config
函数功能：超声波初始化
函数传参：无
函数返回值：无
***************************************/
void HCSR04_Config(void)
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;     
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(ECHO_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(TRIG_CLK, ENABLE);
	//IO初始化
	GPIO_InitStructure.GPIO_Pin =TRIG_PIN;       //发送电平引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_Init(TRIG_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =   TRIG_PIN;     //返回电平引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(ECHO_PORT, &GPIO_InitStructure);  

	//定时器初始化 使用基本定时器TIM1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);   //使能对应RCC时钟
	//配置定时器基础结构体
	TIM_TimeBaseStructure.TIM_Period = (1000-1); //设置在下一个更新事件装入活动的自动重装载寄存器周期的值         计数到1000为1ms
	TIM_TimeBaseStructure.TIM_Prescaler =(72-1); //设置用来作为TIMx时钟频率除数的预分频值  1M的计数频率 1US计数
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位         

	TIM_ClearFlag(TIM1, TIM_FLAG_Update);   //清除更新中断，免得一打开中断立即产生中断
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);    //打开定时器更新中断
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;             //选择串口1中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //抢占式中断优先级设置为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;         //响应式中断优先级设置为1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;        //使能中断
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM1,DISABLE);     
}

/***************************************
函数名称：TIM4_IRQHandler
函数功能：定时器4中断服务程序
函数传参：无
函数返回值：无

***************************************/
void TIM1_UP_IRQHandler(void)   
{
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)  //检查TIM4更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);  //清除TIM4更新中断标志 
		SR04_TimeCount++;
	}
}

/***************************************
函数名称：Open_SR04Timer
函数功能：打开超声波定时器
函数传参：无
函数返回值：无

***************************************/
void Open_SR04Timer(void)        
{
	TIM_SetCounter(TIM1,0);	//清除计数
	SR04_TimeCount = 0;
	TIM_Cmd(TIM1,ENABLE);  //使能TIMx外设
}
 
/***************************************
函数名称：Close_SR04Timer
函数功能：关闭超声波定时器
函数传参：无
函数返回值：无

***************************************/
void Close_SR04Timer(void)
{
	TIM_Cmd(TIM1, DISABLE);  //使能TIMx外设
}

/***************************************
函数名称：Close_SR04Timer
函数功能：获取ECHO定时器时间
函数传参：无
函数返回值：无

***************************************/
uint32_t Get_EchoTimer(void)
{
	uint32_t Timer_Count = 0;
	Timer_Count = SR04_TimeCount*1000;		//得到MS
	Timer_Count += TIM_GetCounter(TIM1);	//得到US
	TIM_SetCounter(TIM1,0);
	delay_ms(50);
	return Timer_Count;
}

/***************************************
函数名称：Get_Length
函数功能：获取距离
函数传参：无
函数返回值：无

***************************************/
float Get_Length(void)
{
	uint32_t Time = 0;
	uint8_t i = 0;
	float Length_Temp = 0.0,Sum = 0.0;
	
	for(i=0;i<5;i++)
	{
		TRIG_Send(1);      //发送口高电平输出
		delay_us(20);
		TRIG_Send(0);
		
		while(ECHO_Reci == 0);   //等待接收口高电平输出
		Open_SR04Timer();        //打开定时器
		while(ECHO_Reci == 1);
		Close_SR04Timer();       //关闭定时器
		
		Time = Get_EchoTimer();  //获取时间,分辨率为1us
		Length_Temp = (Time/58.0);		 //cm
		Sum += Length_Temp;
	}
	Length_Temp = Sum/5.0;
	return Length_Temp;
}


