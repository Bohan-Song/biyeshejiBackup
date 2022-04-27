/* ��ֹ�ݹ������ͷ�ļ� ------------------------------------------------------*/
#ifndef __LCD_H
#define __LCD_H
	 
#include "stm32f10x.h"
#include "lcd.h"
//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ

void Lcd_Gpio_Init(void);
void LCD_Writ_Bus(u16 bus_data);
void LCD_Write_COM(u16 bus_data);
void LCD_Write_DATA(u16 bus_data);
//void Image();//����ͼƬ1
void LCD_Fast_clear(u16 color);
void LCD_Init(void);
void Pant(int dcolor);
u16 LCD_ReadPoint(u16 x,u16 y);
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);
void LCD_Fill(unsigned short color);
void LCD_DrawPoint(u16 x,u16 y,u16 color);//��ָ��λ��д��һ�����ص�����
void LCD_ShowChar(u16 x,u16 y, u8 num,u8 mode);
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len);
void LCD_ShowNumPoint(u16 x,u16 y,u16 num);//��ʾ4λ��+2λС����
#ifdef __cplusplus
}
#endif


#endif /* __LTK_GPIO_H */



