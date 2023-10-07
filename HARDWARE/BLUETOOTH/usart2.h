#ifndef __USART2_H
#define __USART2_H	 
#include "sys.h"  




void usart2_init(u32 bound);				//´®¿Ú2³õÊ¼»¯ 
void usart2_ctl(void);
void ble_config_set(void);
void usart2_send_str(char *pstr);
extern  uint32_t water_set;

#endif













