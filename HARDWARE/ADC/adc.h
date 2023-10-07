#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"

//正点原子的adc采集代码
void Adc_Init(void);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times);
void adc_display(void);
extern int shidu;
int get_shidu(void);
 
#endif 
