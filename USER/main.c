/********************************************************************************************** 
* ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
* ���ܣ��칫�����ܽ���
* �����ߣ�Dircw
* ʱ�䣺2022.12
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




// չʾ���log
void ShowLog(void)
{
    OLED_Clear();         // OLED����
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
	delay_ms(1800);       // �ȴ�ϵͳ�ȶ�
	OLED_Clear();

	
}

// Ӳ���豸��ʼ��
void HARDWARE_Init()
{
    
    usart1_init(115200);      // ����1��ʼ��
	usart2_init(115200);		 
	Adc_Init();				//adc��ʼ��
    dht11_init();           // dht11��ʼ��
    KEY_EXTIX_Init();
	LED_GPIO_Config();
	MOTOR_Init();
	motor_off();
    OLED_Init();            // OLED��ʼ��
    OLED_Clear();           // OLED����
    ShowLog();
	motor_off();
	BEEP_Init();

	
}


int main(void)
{	
	delay_init();	    	 //��ʱ������ʼ��	  
	HARDWARE_Init();
	printf("water_set=%d\r\n",water_set);
	water(0);
	while(1) 
	{	

		// ��ʾ��ʪ��
			adc_display();
			DTH11_display();
			usart2_ctl();
		printf("%d\r\n",water_set);
			adc_display();
			water(water_set);
}
	  


}
