/********************************************************************************************** 
* ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
* ���ܣ��칫�����ܽ���
* �����ߣ�Dircw
* ʱ�䣺2022.12
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

//�ⲿ�ж�0�������
	
void KEY_EXTIX_Init(void)						//�ж���0����
	 {	 									
	 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	    //ʹ��PA�˿�ʱ��
		//����PA0����
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//PA0 �˿�����
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	 		//��������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 
		GPIO_Init(GPIOA, &GPIO_InitStructure);			     //��ʼ��GPIOA0	 
		 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 		//ʹ��AFIO�˿�
		
		 //��PA0��EXIT0������һ��
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	
	
		EXTI_InitStructure.EXTI_Line = EXTI_Line0;				//�ⲿ�ж�0
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//�ж�
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  //�½��ش���
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//ʹ��
		EXTI_Init(&EXTI_InitStructure);							//��ʼ��
		 
		 
        NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;		//�ⲿ�ж�0������ͨ��
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//��ռ���ȼ�
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;	//��Ӧ���ȼ�
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//ʹ�ܸ�ͨ��
        NVIC_Init(&NVIC_InitStructure);							//��ʼ��
	 }

 void EXTI0_IRQHandler(void)  		//�жϷ�����
	{		
		if(EXTI_GetITStatus(EXTI_Line0) == SET)	//�ж��жϿ�����0���ж�״̬�Ƿ����ж�����
		{
		motor_on();
			
		delay_ms(1800);
			
		motor_off();
			
		EXTI_ClearITPendingBit(EXTI_Line0);		/* ��ձ�־λ������CPU���Ѿ���ɵ�ǰ�жϴ���������Ӧ�µ��ж����� */
		}
	}

