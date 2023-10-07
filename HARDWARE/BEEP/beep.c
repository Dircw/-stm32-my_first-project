#include "beep.h"
int melody[] = {50, 50, 50, 50, 200, 200, 200, 400, 400, 500, 500, 500};
void BEEP_Init(void)//PB5
{   
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能b端口时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOB.5
    GPIO_SetBits(GPIOB,GPIO_Pin_5);	
}

void Sound(u16 frq)
{
	u32 time;
	if(frq != 1000)
	{
		time = 500000/((u32)frq);
		PBeep = 1;
		delay_us(time);
		PBeep = 0;
		delay_us(time);
	}else
		delay_us(1000);
}

void beep_off(void)
{
	
	PBeep = 0;
	
}

void beep_on(void)
{
	//             低7  1   2   3   4   5   6   7  高1 高2  高3 高4 高5 不发音
	uc16 tone[] = {247,262,294,330,349,392,440,494,523,587,659,698,784,1000};//音频数据表
	//红尘情歌
/*	u8 music[]={5,5,6,8,7,6,5,6,13,13,//音调
                5,5,6,8,7,6,5,3,13,13,
                2,2,3,5,3,5,6,3,2,1,
                6,6,5,6,5,3,6,5,13,13,

                5,5,6,8,7,6,5,6,13,13,
                5,5,6,8,7,6,5,3,13,13,
                2,2,3,5,3,5,6,3,2,1,
                6,6,5,6,5,3,6,1,	

                13,8,9,10,10,9,8,10,9,8,6,
                13,6,8,9,9,8,6,9,8,6,5,
                13,2,3,5,5,3,5,5,6,8,7,6,
                6,10,9,9,8,6,5,6,8};	
	u8 time[] = {2,4,2,2,2,2,2,8,4, 4, //时间
                2,4,2,2,2,2,2,8,4, 4, 
                2,4,2,4,2,2,4,2,2,8,
                2,4,2,2,2,2,2,8,4 ,4, 

                2,4,2,2,2,2,2,8,4, 4, 
                2,4,2,2,2,2,2,8,4, 4, 
                2,4,2,4,2,2,4,2,2,8,
                2,4,2,2,2,2,2,8,

                4, 2,2,2, 4, 2,2,2, 2,2,8,
                4, 2,2,2,4,2,2,2,2,2,8,
                4, 2,2,2,4,2,2,5,2,6,2,4,
                2,2 ,2,4,2,4,2,2,12};	*/
	
	//小燕子
		u8 music[]={3,5,8,6,5,13,//音调
	                3,5,6,8,5,13,
	                8,10,9,8,9,8,6,8,5,13,
					3,5,6,5,6,8,9,5,6,13,
					3,2,1,2,13,
					2,2,3,5,5,8,2,3,5,13};
		u8 time[] ={2,2,2,2,6,3,//时间  
				2,2,2,2,6,3,
                6,2,4,4,2,2,2,2,6,3,
				6,2,4,2,2,4,2,2,6,3,
				2,2,4,6,3,
				4,2,2,4,4,4,2,2,6,3};
//	u8 music[]={13,1,2,3,4,5,6,7,8};//测试基础音
//	u8 time[] ={4, 4,4,4,4,4,4,4,4};

	u32 yanshi;
	u16 i,e;
	yanshi = 8;
	for(i=0;i<sizeof(music)/sizeof(music[0]);i++)
		{
		for(e=0;e<((u16)time[i])*tone[music[i]]/yanshi;e++)
			{
			Sound((u32)tone[music[i]]);
			}	
	}
}


void beep_on1(void)
{
	//             低7  1   2   3   4   5   6   7  高1 高2  高3 高4 高5 不发音
	uc16 tone[] = {247,262,294,330,349,392,440,494,523,587,659,698,784,1000};//音频数据表

	u8 music[]={13,1,2,3,4,5,6,7,8};//测试基础音
	u8 time[] ={2,2,2,2,2,2,2,2,2};

	u32 yanshi;
	u16 i,e;
	yanshi = 8;
	for(i=0;i<sizeof(music)/sizeof(music[0]);i++)
		{
		for(e=0;e<((u16)time[i])*tone[music[i]]/yanshi;e++)
			{
			Sound((u32)tone[music[i]]);
			}	
	}
}


void beep_on2(void)
{
	//             低7  1   2   3   4   5   6   7  高1 高2  高3 高4 高5 不发音
	uc16 tone[] = {247,262,294,330,349,392,440,494,523,587,659,698,784,1000};//音频数据表

	u8 music[]={8,7,6,5,4,3,2,1,13};//测试基础音
	u8 time[] ={2,2,2,2,2,2,2,2,2};

	u32 yanshi;
	u16 i,e;
	yanshi = 8;
	for(i=0;i<sizeof(music)/sizeof(music[0]);i++)
		{
		for(e=0;e<((u16)time[i])*tone[music[i]]/yanshi;e++)
			{
			Sound((u32)tone[music[i]]);
			}	
	}
}