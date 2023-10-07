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
	//打开PA硬件时钟//打开串口1硬件时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
	
	//配置PA9，PA10为复用功能
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			//串口PA9 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	 //多功能模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO口速度为50MHz 
  GPIO_Init(GPIOA, &GPIO_InitStructure);			     //初始化GPIOA9
	
	//USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10 

	
	//将PA9和PA10引脚连接到串口1的硬件
	
	//配置串口1相关参数：波特率、无校验位、8位数据位、1个停止位...
	USART_InitStructure.USART_BaudRate = baud;								//配置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;				//8位数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;					//1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;						//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;			//接收与发送都使能
	USART_Init(USART1, &USART_InitStructure);//初始化USART1
	
	//配置串口1的中断触发方法：接受中断Receive Data register not empty interrupt
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	//配置串口中断优先级
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		//组优先级设置
	
   //Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	

	//使能串口1工作
	USART_Cmd(USART1, ENABLE);
	
}

void usart2_init(uint32_t baud)
{
	//打开PA硬件时钟//打开串口1硬件时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;			//串口PA10 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	 //多功能模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO口速度为50MHz 
  GPIO_Init(GPIOA, &GPIO_InitStructure);			     //初始化GPIOA9
	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PB11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOB11

	
	//将PA9和PA10引脚连接到串口1的硬件
	
	//配置串口1相关参数：波特率、无校验位、8位数据位、1个停止位...
	USART_InitStructure.USART_BaudRate = baud;								//配置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;				//8位数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;					//1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;						//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;			//接收与发送都使能
	USART_Init(USART2, &USART_InitStructure);//初始化USART1
	
	//配置串口1的中断触发方法：接受中断Receive Data register not empty interrupt
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	//配置串口中断优先级
	/* Configure the NVIC Preemption Priority Bits */  
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		//组优先级设置
	
   //Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	

	//使能串口1工作
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

		//指针偏移
		p++;
	}
}

//AT指令配置模块，蓝牙4.0模块不能跟手机进行连接
void ble_config_set(void)
{
	//发送AT的测试指令
	usart2_send_str("AT+NAMEDIRCW\r\n");
	delay_ms(500);


	
	//发送复位模块的指令
	usart2_send_str("AT+RST");
	delay_ms(3000);

}



void usart2_ctl(void)
{
	char buf[32]={0};
	char *p = NULL;
	uint8_t set=0;
	
	//蓝牙模块的配置
	//ble_config_set();
	
	if(g_usart_event)
	{
		printf("%d\r\n",g_usart_event);
	//判断字符串的有效性
			//g_usart_buf:"shidu=50#"
			if(strstr((const char *)g_usart_buf,"shidu"))
			{
				//分解字符串
				p=strtok((char *)g_usart_buf,"=");
				
				printf("%s\r\n",p);	//"shidu"
				
				p=strtok(NULL,"=");
				
				printf("%s\r\n",p);	//"50#"

				//字符串转换为整型
				set = atoi(p);			//"50#" -> 50
				
				water(set);
				
				water_set=set;
				
				printf("%d",set);
			
				//格式化字符串
				sprintf(buf,"shidu set %d ok\r\n",set);
				
				//告诉手机，已经配置成功
				usart2_send_str(buf);
				
				printf(buf);
			
		}
			
		if(strstr((const char *)g_usart_buf,"beep"))
			{	
				if(strstr((const char *)g_usart_buf,"on"))
				{
					//打开蜂鸣器
					beep_on1();
					
					printf("beep on ok\r\n");
				}
				if(strstr((const char *)g_usart_buf,"off"))
				{
					//关闭蜂鸣器
					PBout(5)=0;
					
					printf("beep off ok\r\n");					
					
				}
			}
			
			g_usart_event=0;
			
			//将buf清零
			memset((void *)g_usart_buf,0,sizeof g_usart_buf);
		
		}

		
	}

		



void USART1_IRQHandler(void)
{
	static uint32_t i=0;
	uint8_t d;
	
	
	//检测标志位
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		//接收数据
		d=USART_ReceiveData(USART1);
		
		g_usart_buf[i]=d;
		
		i++;
		
		//判断是否有结束符‘#’，同时检测有没有超过缓冲区的大小
		if(d == '#' || i >=sizeof (g_usart_buf))
		{
			i=0;
			g_usart_event=1;
		}
		
		
			//发送到串口1->PC
		USART_SendData(USART1,d);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
				
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);//清空标志位
		

	}

}

void USART2_IRQHandler(void)
{
	uint8_t d;
	static	uint32_t j=0;
	
	//检测标志位
	if(USART_GetITStatus(USART2,USART_IT_RXNE) == SET)
	{
		//接收数据
		d=USART_ReceiveData(USART2);
		g_usart_buf[j]=d;
		
		j++;
		
		//判断是否有结束符‘#’，同时检测有没有超过缓冲区的大小
		if(d == '#' || j >=sizeof (g_usart_buf))
		{
			j=0;
			g_usart_event=1;
		}
		
		//通过串口1发送给PC
		USART_SendData(USART1,d);
		
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
		USART_ClearFlag(USART1,USART_FLAG_TXE);
		

		//清空标志位
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}

}


