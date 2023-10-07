/********************************************************************************************** 
* 本程序只供学习使用，未经作者许可，不得用于其它任何用途
* 介绍：办公室智能浇花
* 开发者：Dircw
* 时间：2022.12
**********************************************************************************************/



#include "beep.h"
#include "motor.h"
#include "sys.h" 
#include "delay.h"
#include "oled.h"
#include "adc.h"
#include "bmp.h"


void MOTOR_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能ABCD时钟
	
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO口速度为50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始GPIOA
	motor_off();
}


void motor_on(void)
{
	PAout(8)=0;
}

void motor_off(void)
{
	PAout(8)=1;
}


void water(uint32_t h)
{
	if(shidu <h)
	{
	OLED_ShowPicture(0,0,128,64,BMP1,1);
	OLED_Refresh();
	beep_on1();
	motor_on();
	delay_ms(1800);
	motor_off();
	OLED_Clear();
	}
	
	
	

}

