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

// DHT11���� PB5
// ���Ŷ��壬�޸����żǵ�������صĺ�
#define DHT11_GPIO_TYPE  GPIOB
#define DHT11_GPIO_PIN   GPIO_Pin_8
#define DHT11_RCC        RCC_APB2Periph_GPIOB

// Ƕ�׺궨��
#define DHT11_DATA_H GPIO_SetBits(DHT11_GPIO_TYPE, DHT11_GPIO_PIN)
#define DHT11_DATA_L GPIO_ResetBits(DHT11_GPIO_TYPE, DHT11_GPIO_PIN)
#define DHT11_IN    GPIO_ReadInputDataBit(DHT11_GPIO_TYPE, DHT11_GPIO_PIN)

#define DHT11_OK    1
#define DHT11_ERR   0
struct DHT11_VALUE
{
	u8  humi_int ;// ʪ����������
	u8  humi_deci;// ʪ��С������
	u8  temp_int; // �¶���������
	u8  temp_deci;// �¶�С������
	u8  check_sum;// У��
};//����DHT11_VALUE�ṹ�巽��洢��ʪ������

extern struct DHT11_VALUE   DHT11Data;//ȫ�ֱ���
void dht11_init(void);// ��ʼ��
void dht11_gpio_input(void);// ������������
void dht11_gpio_output(void);// �����������
u16 dht11_scan(void);
int32_t dht11_wait(void);
int32_t dht11_waitbit(void);
u16 dht11_read_bit(void);
u16 dht11_read_byte(void);
u16 dht11_read_data(u8 buffer[5]);// ��ȡ��ʪ�ȵ�����


// ��ȡ��ʪ����ֵ���ṹ�������
u8 dht11_get_val(void);
// ��ȡ��ʪ�ȵ��ṹ�����ʾ
void DTH11_display(void);

// ��ȡ��ʪ����ֵ���ṹ�������
u8 dht11_get_val(void);

#endif
