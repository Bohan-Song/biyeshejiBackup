#ifndef  DS18B20_H
#define  DS18B20_H

sbit DQ=P2^0;

extern uchar data temp_DQ_data[2];
extern uchar data temp_work_data[5];
extern uchar code dis_dec[17];
extern uchar temp_value_int,temp_value_point,temp_warn;

extern void delay1us(uchar t);
extern void DQ_reset(void);
extern void DQ_write(uchar a);
extern uchar DQ_read(void);
extern void read_temp(void);
extern void Temp_Work(void);
extern void DQ_init(void);
extern void Tempt(void);

#endif