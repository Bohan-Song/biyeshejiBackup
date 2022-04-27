#include "hcsr04.h"


uint16_t SR04_TimeCount = 0;
/***************************************
�������ƣ�HCSR04_Config
�������ܣ���������ʼ��
�������Σ���
��������ֵ����
***************************************/
void HCSR04_Config(void)
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;     
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(ECHO_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(TRIG_CLK, ENABLE);
	//IO��ʼ��
	GPIO_InitStructure.GPIO_Pin =TRIG_PIN;       //���͵�ƽ����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_Init(TRIG_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =   TRIG_PIN;     //���ص�ƽ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(ECHO_PORT, &GPIO_InitStructure);  

	//��ʱ����ʼ�� ʹ�û�����ʱ��TIM1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);   //ʹ�ܶ�ӦRCCʱ��
	//���ö�ʱ�������ṹ��
	TIM_TimeBaseStructure.TIM_Period = (1000-1); //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ         ������1000Ϊ1ms
	TIM_TimeBaseStructure.TIM_Prescaler =(72-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  1M�ļ���Ƶ�� 1US����
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ         

	TIM_ClearFlag(TIM1, TIM_FLAG_Update);   //��������жϣ����һ���ж����������ж�
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);    //�򿪶�ʱ�������ж�
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;             //ѡ�񴮿�1�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռʽ�ж����ȼ�����Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;         //��Ӧʽ�ж����ȼ�����Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;        //ʹ���ж�
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM1,DISABLE);     
}

/***************************************
�������ƣ�TIM4_IRQHandler
�������ܣ���ʱ��4�жϷ������
�������Σ���
��������ֵ����

***************************************/
void TIM1_UP_IRQHandler(void)   
{
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)  //���TIM4�����жϷ������
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);  //���TIM4�����жϱ�־ 
		SR04_TimeCount++;
	}
}

/***************************************
�������ƣ�Open_SR04Timer
�������ܣ��򿪳�������ʱ��
�������Σ���
��������ֵ����

***************************************/
void Open_SR04Timer(void)        
{
	TIM_SetCounter(TIM1,0);	//�������
	SR04_TimeCount = 0;
	TIM_Cmd(TIM1,ENABLE);  //ʹ��TIMx����
}
 
/***************************************
�������ƣ�Close_SR04Timer
�������ܣ��رճ�������ʱ��
�������Σ���
��������ֵ����

***************************************/
void Close_SR04Timer(void)
{
	TIM_Cmd(TIM1, DISABLE);  //ʹ��TIMx����
}

/***************************************
�������ƣ�Close_SR04Timer
�������ܣ���ȡECHO��ʱ��ʱ��
�������Σ���
��������ֵ����

***************************************/
uint32_t Get_EchoTimer(void)
{
	uint32_t Timer_Count = 0;
	Timer_Count = SR04_TimeCount*1000;		//�õ�MS
	Timer_Count += TIM_GetCounter(TIM1);	//�õ�US
	TIM_SetCounter(TIM1,0);
	delay_ms(50);
	return Timer_Count;
}

/***************************************
�������ƣ�Get_Length
�������ܣ���ȡ����
�������Σ���
��������ֵ����

***************************************/
float Get_Length(void)
{
	uint32_t Time = 0;
	uint8_t i = 0;
	float Length_Temp = 0.0,Sum = 0.0;
	
	for(i=0;i<5;i++)
	{
		TRIG_Send(1);      //���Ϳڸߵ�ƽ���
		delay_us(20);
		TRIG_Send(0);
		
		while(ECHO_Reci == 0);   //�ȴ����տڸߵ�ƽ���
		Open_SR04Timer();        //�򿪶�ʱ��
		while(ECHO_Reci == 1);
		Close_SR04Timer();       //�رն�ʱ��
		
		Time = Get_EchoTimer();  //��ȡʱ��,�ֱ���Ϊ1us
		Length_Temp = (Time/58.0);		 //cm
		Sum += Length_Temp;
	}
	Length_Temp = Sum/5.0;
	return Length_Temp;
}


