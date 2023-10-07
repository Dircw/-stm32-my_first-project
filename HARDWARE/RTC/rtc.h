/********************************************************************************************** 
* ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
* ���ܣ��칫�����ܽ���
* �����ߣ�������
* ʱ�䣺2022.12
**********************************************************************************************/


#ifndef __RTC_H
#define __RTC_H	    
//Mini STM32������
//RTCʵʱʱ�� ��������			 
//����ԭ��@ALIENTEK
//2010/6/6

// ��ȡNTP����ʱ����
#define GET_NTP_TIME  10

//��ˮʱ��ṹ��
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


//ʱ��ṹ��
typedef struct 
{
	vu8 hour;
	vu8 min;
	vu8 sec;			
	//������������
	vu16 w_year;
	vu8  w_month;
	vu8  w_date;
	vu8  week;		 
}_calendar_obj;					 
extern _calendar_obj calendar;	//�����ṹ��

extern u8 const mon_table[12];	//�·��������ݱ�
void Disp_Time(u8 x,u8 y,u8 size);//���ƶ�λ�ÿ�ʼ��ʾʱ��
void Disp_Week(u8 x,u8 y,u8 size,u8 lang);//��ָ��λ����ʾ����
u8 RTC_Init(void);        //��ʼ��RTC,����0,ʧ��;1,�ɹ�;
u8 Is_Leap_Year(u16 year);//ƽ��,�����ж�
u8 RTC_Alarm_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);
u8 RTC_Get(void);         //����ʱ��   
u8 RTC_Get_Week(u16 year,u8 month,u8 day);
u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);//����ʱ��	

/********************************************************************************/ 
extern _jiaoshui_time watre_time;
extern u8 watre_flag; // ��ˮ��
/**************************************************************************************/
/**************************************************************************************/
//����ʱ�䣬mode DISABLE �ر����жϣ��Ѽ���ֵ���ɽṹ��ֵ��ֹͣ���½ṹ��ֵ���ṹ��ֵ����ʾʱ���õģ�
//                ENABLE �������жϣ��ѽṹ��ֵ���ɼ���ֵ���ָ����½ṹ��ֵ������ֵ�Ƕ�ʱ������������
void seting_rtc(u8 mode);
#endif


