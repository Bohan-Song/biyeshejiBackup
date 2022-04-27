/* 防止递归包含该头文件 ------------------------------------------------------*/
#ifndef __LCD_H
#define __LCD_H
	 
#include "stm32f10x.h"
#include "lcd.h"
//画笔颜色
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
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色

void Lcd_Gpio_Init(void);
void LCD_Writ_Bus(u16 bus_data);
void LCD_Write_COM(u16 bus_data);
void LCD_Write_DATA(u16 bus_data);
//void Image();//载入图片1
void LCD_Fast_clear(u16 color);
void LCD_Init(void);
void Pant(int dcolor);
u16 LCD_ReadPoint(u16 x,u16 y);
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);
void LCD_Fill(unsigned short color);
void LCD_DrawPoint(u16 x,u16 y,u16 color);//在指定位置写入一个像素点数据
void LCD_ShowChar(u16 x,u16 y, u8 num,u8 mode);
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len);
void LCD_ShowNumPoint(u16 x,u16 y,u16 num);//显示4位数+2位小数点
#ifdef __cplusplus
}
#endif


#endif /* __LTK_GPIO_H */



