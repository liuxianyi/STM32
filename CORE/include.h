#ifndef __include_h__
#define __include_h__
#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "beep.h"
#include "usart.h"
#include "timer.h"
#include "oled1.h"
#include "adc.h"
#include "bmp1.h"
#include "keyboard.h"
#include "dac.h"
#include "dma.h"
#include "pid.h"
#include "lcd.h"
#include "rtc.h"
#include "wkup.h"
#include "usmart.h"
#include "FDC2214.H"
#include "usart1.h"
#include "UltrasonicWave.h"//超声波
#include "timer_s.h"//超声波定时器中断
#include "IIC_color.h"//IIC配合颜色识别
u8 RTC_Init_flag=1;//0正常
void init_all(){
		NVIC_Configuration();//设置中断优先分组
		delay_init();  //一直要开启
		OLED_Init();
		//TIM3_PWM_Init(199,7199);	//不分频。899 PWM频率=72000/900=8Khz
		//GPIO_keyboard_4_4_init();//矩阵键盘管脚口
		//LCD_Init();//LCD初始化
		//WKUP_Init();//待机唤醒
		//RTC_Init_flag = RTC_Init();//RTC日期时间
		//Dac1_Init();//数模转换
		Adc_Init();//模数转换
		//BEEP_Init();//初始化蜂鸣器
		//TIM4_Int_Init(4999,7199);//定时器5ms
		//TIM3_Int_Init(1999,719);//3ms
		
		//uart_init(9600);//中断初始化
		//uart3_init(9600);//蓝牙模块
		//ledInit(RCC_APB2Periph_GPIOE, GPIO_Pin_5, GPIOE);//==PE5--PB5
		//LED_INIT_ALL(GPIOB, GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_5, RCC_APB2Periph_GPIOB);
		
		//Keyspress();//矩阵键盘	
		//usmart_dev.init(SystemCoreClock/1000000);//SystemCoreClock--72MHZ===串口调试工具初始化
		//TIM5_Ctrl_Init(2999,719);
		//FDC2214_Init();//初始化IIC I/O口
}
void Delay(u32 count);
#endif
