#ifndef __BEEP__H
#define __BEEP__H

#include "sys.h"
#include "stdlib.h"	  
#include "delay.h"

//����GPIOB��λ��ַ�����꣬λ����꣬�����
#define PBeep PBout(5)

void BEEP_Init(void);
void Sound(u16 frq);
void beep_off(void);
void beep_on(void);
void beep_on1(void);
void beep_on2(void);
#endif
