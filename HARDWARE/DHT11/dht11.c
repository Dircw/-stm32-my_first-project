/********************************************************************************************** 
* 本程序只供学习使用，未经作者许可，不得用于其它任何用途
* 介绍：办公室智能浇花
* 开发者：Dircw
* 时间：2022.12
**********************************************************************************************/

#include "dht11.h"
#include "delay.h"
#include "oled.h"
#include "stdio.h"  //fputc

struct DHT11_VALUE DHT11Data;// 定义结构体变量储存温湿度数值
u8 buffer[5];				 // 读取温湿度的临时数组变量

// dht11初始化
void dht11_init(void)
{
	//初始化，开时钟。后面分输入输出配置引脚
	RCC_APB2PeriphClockCmd(DHT11_RCC, ENABLE);
	DHT11Data.humi_int  = 0;
	DHT11Data.humi_deci = 0;
	DHT11Data.temp_int  = 0;
	DHT11Data.temp_deci = 0;
	DHT11Data.check_sum = 0;
	
    //dht11_gpio_input();   // 默认温湿度配置成输入模式
}

// 输入配置引脚
void dht11_gpio_input()
{ 
    GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(DHT11_RCC, ENABLE);
	
    GPIO_InitStruct.GPIO_Pin = DHT11_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
    GPIO_Init(DHT11_GPIO_TYPE, &GPIO_InitStruct);
}
// 输出配置引脚
void dht11_gpio_output()
{
    GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(DHT11_RCC, ENABLE);
    
    GPIO_InitStruct.GPIO_Pin = DHT11_GPIO_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
	GPIO_Init(DHT11_GPIO_TYPE, &GPIO_InitStruct);
}

void dht11_reset()
{
    // 按照DHT11手册步骤
    dht11_gpio_output();
    DHT11_DATA_L;
    delay_ms(19);
    DHT11_DATA_H;
    delay_us(30);
    dht11_gpio_input();
}

u16 dht11_scan(void)
{
    return DHT11_IN;
}

u16 dht11_read_bit()
{
    while (DHT11_IN == RESET);//0,没有信号输入
    delay_us(40);
    if (DHT11_IN == SET)
    {
        while (DHT11_IN == SET);
        return 1;
    }
    else
    {
        return 0;
    }
}

u16 dht11_read_byte()
{
    u16 i;
    u16 data = 0;
    for (i = 0; i < 8; i++)
    {
        data <<= 1;
        data |= dht11_read_bit();
    }
    return data;
}

// 读取温湿度到数组
u16 dht11_read_data(u8 buffer[5])
{
    u16 i = 0;
    u8 checksum;
    dht11_reset();
    if (dht11_scan() == RESET)
    {
        //检测到DHT11响应
        while (dht11_scan() == RESET);
        while (dht11_scan() == SET);
        for (i = 0; i < 5; i++)
        {
            buffer[i] = dht11_read_byte();
        }
        
        while (dht11_scan() == RESET);
        dht11_gpio_output();
        DHT11_DATA_H;
        
        checksum = buffer[0] + buffer[1] + buffer[2] + buffer[3];
        if (checksum != buffer[4])
        {
            // check error
            return DHT11_ERR;
        }
    }
    
    return DHT11_OK;
}
// 读取温湿度数值到结构体变量中
u8 dht11_get_val(void)
{
	if(dht11_read_data(buffer)==DHT11_OK)// dht11读取温湿度成功
	{
		DHT11Data.humi_int  = buffer[0];
		DHT11Data.humi_deci = buffer[1];
		DHT11Data.temp_int  = buffer[2];
		DHT11Data.temp_deci = buffer[3];
		// hum = buffer[0] + buffer[1] / 10.0;
        //temp = buffer[2] + buffer[3] / 10.0;
		printf("湿度：%3.2f %% 温度：%3.2f ℃\r\n",(float)buffer[0]+(float)buffer[1]/10,(float)buffer[2]+(float)buffer[3]/10);
		delay_ms(1000);
		 return DHT11_OK;
	}
	else
	{
		printf("读取温湿度错误\r\n");
		return DHT11_ERR;
	}
}

void  DTH11_display(void)
{
        if (dht11_get_val() == DHT11_OK)
        {
			if(DHT11Data.temp_int == 0 || DHT11Data.humi_int ==0 )
			{
				DHT11Data.temp_int = 21;
				DHT11Data.humi_int = 91;
			}
			OLED_ShowString(15,48,"t",16,1);
			OLED_ShowString(8+15,48,"=",16,1);
			OLED_ShowNum(16+15,48,DHT11Data.temp_int,2,16,1);
			OLED_ShowString(8*4+15,48,"C",16,1);
			
			OLED_ShowString(61,48," h",16,1);
			OLED_ShowString(78,48,"=",16,1);
			OLED_ShowNum(86,48,DHT11Data.humi_int,2,16,1);
			OLED_ShowString(102,48,"%",16,1);
			OLED_Refresh();
			//OLED_ShowString(110,6,"r",16);
			//OLED_ShowString(119,6,"h",16);  
        }
}


