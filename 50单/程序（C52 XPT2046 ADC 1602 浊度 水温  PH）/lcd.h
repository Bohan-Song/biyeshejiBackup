#ifndef LCD_H
#define LCD_H

sbit  lcdrs = P2^6;
sbit  lcden = P2^7;

void delay_ms(uint ms);
void write_com(uchar com);
void write_data(uchar dat);
void LCD_ShowChar(uchar x,uchar dat);
void LCD_ShowNum(uchar x,uint num,uchar len);
void LCD_ShowString(uchar x,uchar *chr);
void LCD_Init(void);
void LCD_Scan(void);

extern uint ph,zhuodu;

#endif
