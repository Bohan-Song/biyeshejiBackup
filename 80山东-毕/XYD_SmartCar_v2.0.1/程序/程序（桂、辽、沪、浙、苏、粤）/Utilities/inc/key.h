/**
  ******************************************************************************
  * �ļ�: ltk_key.h
  * ����: LeiTek (leitek.taobao.com)
  * �汾: V1.0.0
  * ����: �����ⲿ�ж��м��ͷ�ļ�
  ******************************************************************************
  *
  *                  ��Ȩ���� (C): LeiTek (leitek.taobao.com)
  *                                www.leitek.com
  *
  ******************************************************************************
  */
  
/* ��ֹ�ݹ������ͷ�ļ� ------------------------------------------------------*/
#ifndef __KEY_H
#define __KEY_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/


#define HC1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)
#define HC2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)
#define HC3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)
#define HC4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)

void Key_init(void);	//��ʼ�� KEY\




#ifdef __cplusplus
}
#endif


#endif /* __LTK_KEY_H */

/****************************** leitek.taobao.com *****************************/
