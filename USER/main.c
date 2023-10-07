/********************************************************************************************** 
* 本程序只供学习使用，未经作者许可，不得用于其它任何用途
* 介绍：办公室智能浇花
* 开发者：Dircw
* 时间：2022.12
**********************************************************************************************/
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "usart2.h"
#include "oled.h"
#include "adc.h"
#include "dht11.h"
#include "beep.h"
#include "motor.h"




// 展示设计log
void ShowLog(void)
{
    OLED_Clear();         // OLED清屏
    OLED_ShowString(28,14,"Design by",16,1);
	OLED_ShowChinese(0,32,0,16,1);
	OLED_ShowChinese(16*1,32,1,16,1);
	OLED_ShowChinese(16*2,32,2,16,1);
	OLED_ShowChinese(16*3,32,3,16,1);
	OLED_ShowChinese(16*4,32,4,16,1);
	OLED_ShowChinese(16*5,32,5,16,1);
	OLED_ShowChinese(16*6,32,6,16,1);
	OLED_ShowChinese(16*7,32,7,16,1);
	OLED_Refresh();
	delay_ms(1800);       // 等待系统稳定
	OLED_Clear();

	
}

// 硬件设备初始化
void HARDWARE_Init()
{
    
    usart1_init(115200);      // 串口1初始化
	usart2_init(115200);		 
	Adc_Init();				//adc初始化
    dht11_init();           // dht11初始化
    KEY_EXTIX_Init();
	LED_GPIO_Config();
	MOTOR_Init();
	motor_off();
    OLED_Init();            // OLED初始化
    OLED_Clear();           // OLED清屏
    ShowLog();
	motor_off();
	BEEP_Init();

	
}


int main(void)
{	
	delay_init();	    	 //延时函数初始化	  
	HARDWARE_Init();
	printf("water_set=%d\r\n",water_set);
	water(0);
	while(1) 
	{	

		// 显示温湿度
			adc_display();
			DTH11_display();
			usart2_ctl();
		printf("%d\r\n",water_set);
			adc_display();
			water(water_set);
}
	  


}
