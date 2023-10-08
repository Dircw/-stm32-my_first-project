# -stm32-my_first-project
stm32毕设自动浇花


2022.12
所使用单片机的硬件资源:
	STM32C8T6
	串口1：TX-->PA9,RX-->PA10
	串口2：波特率115200，蓝牙串口模块，RXD-->PA2(TX)  RXD-->PA3(RX) 通信协议：必须以回车换行结尾。
	OLED_IIC屏幕：电源5V，SDA PB7，SCL  PB6
	按键：WK_UP PA0
	蜂鸣器：PB5	5V
	继电器：IN接PA8，与水泵形成回路 5V
	温湿度模块：PB8 3.3V
	土壤湿度传感器：3.3V PA1

蓝牙APP：蓝牙调试器（注意在设置里替换换行符 \r\n 0D 0A；编码选GB2312）。
	     通信协议阅读usart2.c部分代码。

蓝牙串口微信小程序


