#ifndef __DHT11_H__
#define __DHT11_H__

#include "stm32f10x.h"

/*
#define DHT_DATA_H GPIO_SetBits(GPIOC, GPIO_Pin_10);
#define DHT_DATA_L GPIO_ResetBits(GPIOC, GPIO_Pin_10);

void DHT11_Init(void);
void DHT11_input(void);
void DHT11_output(void);
u32 DHT11_read(void);
*/

#include "stm32f10x_gpio.h"

// DHT11引脚 PB5
// 引脚定义，修改引脚记得下列相关的宏
#define DHT11_GPIO_TYPE  GPIOB
#define DHT11_GPIO_PIN   GPIO_Pin_8
#define DHT11_RCC        RCC_APB2Periph_GPIOB

// 嵌套宏定义
#define DHT11_DATA_H GPIO_SetBits(DHT11_GPIO_TYPE, DHT11_GPIO_PIN)
#define DHT11_DATA_L GPIO_ResetBits(DHT11_GPIO_TYPE, DHT11_GPIO_PIN)
#define DHT11_IN    GPIO_ReadInputDataBit(DHT11_GPIO_TYPE, DHT11_GPIO_PIN)

#define DHT11_OK    1
#define DHT11_ERR   0
struct DHT11_VALUE
{
	u8  humi_int ;// 湿度整数部分
	u8  humi_deci;// 湿度小数部分
	u8  temp_int; // 温度整数部分
	u8  temp_deci;// 温度小数部分
	u8  check_sum;// 校验
};//创建DHT11_VALUE结构体方便存储温湿度数据

extern struct DHT11_VALUE   DHT11Data;//全局变量
void dht11_init(void);// 初始化
void dht11_gpio_input(void);// 输入配置引脚
void dht11_gpio_output(void);// 输出配置引脚
u16 dht11_scan(void);
int32_t dht11_wait(void);
int32_t dht11_waitbit(void);
u16 dht11_read_bit(void);
u16 dht11_read_byte(void);
u16 dht11_read_data(u8 buffer[5]);// 读取温湿度到数组


// 读取温湿度数值到结构体变量中
u8 dht11_get_val(void);
// 读取温湿度到结构体后并显示
void DTH11_display(void);

// 读取温湿度数值到结构体变量中
u8 dht11_get_val(void);

#endif
