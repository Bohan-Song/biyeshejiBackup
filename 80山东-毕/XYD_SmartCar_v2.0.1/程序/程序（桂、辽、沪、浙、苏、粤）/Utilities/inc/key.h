/**
  ******************************************************************************
  * 文件: ltk_key.h
  * 作者: LeiTek (leitek.taobao.com)
  * 版本: V1.0.0
  * 描述: 按键外部中断中间件头文件
  ******************************************************************************
  *
  *                  版权所有 (C): LeiTek (leitek.taobao.com)
  *                                www.leitek.com
  *
  ******************************************************************************
  */
  
/* 防止递归包含该头文件 ------------------------------------------------------*/
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

void Key_init(void);	//初始化 KEY\




#ifdef __cplusplus
}
#endif


#endif /* __LTK_KEY_H */

/****************************** leitek.taobao.com *****************************/
