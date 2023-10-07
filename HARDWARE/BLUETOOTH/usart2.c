#include "sys.h"
#include "led.h"
#include "beep.h"
#include "motor.h"
#include "usart2.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static GPIO_InitTypeDef 		GPIO_InitStructure;
static NVIC_InitTypeDef 		NVIC_InitStructure;
static USART_InitTypeDef 		USART_InitStructure;


static volatile uint8_t g_usart_buf[32]={0};
static volatile uint32_t g_usart_event=0;
uint32_t water_set;

#pragma import(__use_no_semihosting_swi)
struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
	
	USART_SendData(USART1,ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	USART_ClearFlag(USART1,USART_FLAG_TXE);
	
	
	return ch;
}
void _sys_exit(int return_code) {

}



void usart1_init(uint32_t baud)
{
	//��PAӲ��ʱ��//�򿪴���1Ӳ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
	
	//����PA9��PA10Ϊ���ù���
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			//����PA9 �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	 //�๦��ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO���ٶ�Ϊ50MHz 
  GPIO_Init(GPIOA, &GPIO_InitStructure);			     //��ʼ��GPIOA9
	
	//USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10 

	
	//��PA9��PA10�������ӵ�����1��Ӳ��
	
	//���ô���1��ز����������ʡ���У��λ��8λ����λ��1��ֹͣλ...
	USART_InitStructure.USART_BaudRate = baud;								//���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;				//8λ����λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;					//1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;						//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;			//�����뷢�Ͷ�ʹ��
	USART_Init(USART1, &USART_InitStructure);//��ʼ��USART1
	
	//���ô���1���жϴ��������������ж�Receive Data register not empty interrupt
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	//���ô����ж����ȼ�
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		//�����ȼ�����
	
   //Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	

	//ʹ�ܴ���1����
	USART_Cmd(USART1, ENABLE);
	
}

void usart2_init(uint32_t baud)
{
	//��PAӲ��ʱ��//�򿪴���1Ӳ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;			//����PA10 �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	 //�๦��ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO���ٶ�Ϊ50MHz 
  GPIO_Init(GPIOA, &GPIO_InitStructure);			     //��ʼ��GPIOA9
	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PB11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOB11

	
	//��PA9��PA10�������ӵ�����1��Ӳ��
	
	//���ô���1��ز����������ʡ���У��λ��8λ����λ��1��ֹͣλ...
	USART_InitStructure.USART_BaudRate = baud;								//���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;				//8λ����λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;					//1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;						//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;			//�����뷢�Ͷ�ʹ��
	USART_Init(USART2, &USART_InitStructure);//��ʼ��USART1
	
	//���ô���1���жϴ��������������ж�Receive Data register not empty interrupt
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	//���ô����ж����ȼ�
	/* Configure the NVIC Preemption Priority Bits */  
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		//�����ȼ�����
	
   //Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	

	//ʹ�ܴ���1����
	USART_Cmd(USART2, ENABLE);
	
}

void usart2_send_str(char *pstr)
{
	char *p = pstr;
	
	while(*p!='\0')
	{
	
		USART_SendData(USART2,*p);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
		USART_ClearFlag(USART2,USART_FLAG_TXE);

		//ָ��ƫ��
		p++;
	}
}

//ATָ������ģ�飬����4.0ģ�鲻�ܸ��ֻ���������
void ble_config_set(void)
{
	//����AT�Ĳ���ָ��
	usart2_send_str("AT+NAMEDIRCW\r\n");
	delay_ms(500);


	
	//���͸�λģ���ָ��
	usart2_send_str("AT+RST");
	delay_ms(3000);

}



void usart2_ctl(void)
{
	char buf[32]={0};
	char *p = NULL;
	uint8_t set=0;
	
	//����ģ�������
	//ble_config_set();
	
	if(g_usart_event)
	{
		printf("%d\r\n",g_usart_event);
	//�ж��ַ�������Ч��
			//g_usart_buf:"shidu=50#"
			if(strstr((const char *)g_usart_buf,"shidu"))
			{
				//�ֽ��ַ���
				p=strtok((char *)g_usart_buf,"=");
				
				printf("%s\r\n",p);	//"shidu"
				
				p=strtok(NULL,"=");
				
				printf("%s\r\n",p);	//"50#"

				//�ַ���ת��Ϊ����
				set = atoi(p);			//"50#" -> 50
				
				water(set);
				
				water_set=set;
				
				printf("%d",set);
			
				//��ʽ���ַ���
				sprintf(buf,"shidu set %d ok\r\n",set);
				
				//�����ֻ����Ѿ����óɹ�
				usart2_send_str(buf);
				
				printf(buf);
			
		}
			
		if(strstr((const char *)g_usart_buf,"beep"))
			{	
				if(strstr((const char *)g_usart_buf,"on"))
				{
					//�򿪷�����
					beep_on1();
					
					printf("beep on ok\r\n");
				}
				if(strstr((const char *)g_usart_buf,"off"))
				{
					//�رշ�����
					PBout(5)=0;
					
					printf("beep off ok\r\n");					
					
				}
			}
			
			g_usart_event=0;
			
			//��buf����
			memset((void *)g_usart_buf,0,sizeof g_usart_buf);
		
		}

		
	}

		



void USART1_IRQHandler(void)
{
	static uint32_t i=0;
	uint8_t d;
	
	
	//����־λ
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		//��������
		d=USART_ReceiveData(USART1);
		
		g_usart_buf[i]=d;
		
		i++;
		
		//�ж��Ƿ��н�������#����ͬʱ�����û�г����������Ĵ�С
		if(d == '#' || i >=sizeof (g_usart_buf))
		{
			i=0;
			g_usart_event=1;
		}
		
		
			//���͵�����1->PC
		USART_SendData(USART1,d);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
				
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);//��ձ�־λ
		

	}

}

void USART2_IRQHandler(void)
{
	uint8_t d;
	static	uint32_t j=0;
	
	//����־λ
	if(USART_GetITStatus(USART2,USART_IT_RXNE) == SET)
	{
		//��������
		d=USART_ReceiveData(USART2);
		g_usart_buf[j]=d;
		
		j++;
		
		//�ж��Ƿ��н�������#����ͬʱ�����û�г����������Ĵ�С
		if(d == '#' || j >=sizeof (g_usart_buf))
		{
			j=0;
			g_usart_event=1;
		}
		
		//ͨ������1���͸�PC
		USART_SendData(USART1,d);
		
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
		USART_ClearFlag(USART1,USART_FLAG_TXE);
		

		//��ձ�־λ
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}

}


