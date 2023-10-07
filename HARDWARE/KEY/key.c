/********************************************************************************************** 
* 本程序只供学习使用，未经作者许可，不得用于其它任何用途
* 介绍：办公室智能浇花
* 开发者：Dircw
* 时间：2022.12
**********************************************************************************************/


#include "stm32f10x.h"
#include "key.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "motor.h"

EXTI_InitTypeDef   EXTI_InitStructure;
GPIO_InitTypeDef   GPIO_InitStructure;
NVIC_InitTypeDef   NVIC_InitStructure;

//外部中断0服务程序
	
void KEY_EXTIX_Init(void)						//中断线0定义
	 {	 									
	 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	    //使能PA端口时钟
		//配置PA0引脚
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//PA0 端口配置
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	 		//上拉输入
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 
		GPIO_Init(GPIOA, &GPIO_InitStructure);			     //初始化GPIOA0	 
		 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 		//使能AFIO端口
		
		 //将PA0与EXIT0连接在一起
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	
	
		EXTI_InitStructure.EXTI_Line = EXTI_Line0;				//外部中断0
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//中断
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //下降沿触发
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//使能
		EXTI_Init(&EXTI_InitStructure);							//初始化
		 
		 
        NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;		//外部中断0的请求通道
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//将占优先级
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;	//响应优先级
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//使能该通道
        NVIC_Init(&NVIC_InitStructure);							//初始化
	 }

 void EXTI0_IRQHandler(void)  		//中断服务函数
	{		
		if(EXTI_GetITStatus(EXTI_Line0) == SET)	//判断中断控制线0的中断状态是否有中断请求
		{
		motor_on();
			
		delay_ms(1800);
			
		motor_off();
			
		EXTI_ClearITPendingBit(EXTI_Line0);		/* 清空标志位，告诉CPU，已经完成当前中断处理，可以响应新的中断请求 */
		}
	}

