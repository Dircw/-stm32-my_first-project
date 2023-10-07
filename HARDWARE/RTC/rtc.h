/********************************************************************************************** 
* 本程序只供学习使用，未经作者许可，不得用于其它任何用途
* 介绍：办公室智能浇花
* 开发者：温幸鑫
* 时间：2022.12
**********************************************************************************************/


#ifndef __RTC_H
#define __RTC_H	    
//Mini STM32开发板
//RTC实时时钟 驱动代码			 
//正点原子@ALIENTEK
//2010/6/6

// 获取NTP网络时间间隔
#define GET_NTP_TIME  10

//浇水时间结构体
typedef struct 
{
	u8 hour1;
	u8 min1;
    u8 hour2;
	u8 min2;
    u8 hour3;
	u8 min3;
    
//	vu8 hour;
//	vu8 min;
	 
}_jiaoshui_time;	   


//时间结构体
typedef struct 
{
	vu8 hour;
	vu8 min;
	vu8 sec;			
	//公历日月年周
	vu16 w_year;
	vu8  w_month;
	vu8  w_date;
	vu8  week;		 
}_calendar_obj;					 
extern _calendar_obj calendar;	//日历结构体

extern u8 const mon_table[12];	//月份日期数据表
void Disp_Time(u8 x,u8 y,u8 size);//在制定位置开始显示时间
void Disp_Week(u8 x,u8 y,u8 size,u8 lang);//在指定位置显示星期
u8 RTC_Init(void);        //初始化RTC,返回0,失败;1,成功;
u8 Is_Leap_Year(u16 year);//平年,闰年判断
u8 RTC_Alarm_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);
u8 RTC_Get(void);         //更新时间   
u8 RTC_Get_Week(u16 year,u8 month,u8 day);
u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);//设置时间	

/********************************************************************************/ 
extern _jiaoshui_time watre_time;
extern u8 watre_flag; // 浇水。
/**************************************************************************************/
/**************************************************************************************/
//设置时间，mode DISABLE 关闭秒中断，把计数值换成结构体值，停止更新结构体值（结构体值是显示时间用的）
//                ENABLE 开启秒中断，把结构体值换成计数值，恢复更新结构体值（计数值是定时器计量的数）
void seting_rtc(u8 mode);
#endif


