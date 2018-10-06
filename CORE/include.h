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
#include "UltrasonicWave.h"//������
#include "timer_s.h"//��������ʱ���ж�
#include "IIC_color.h"//IIC�����ɫʶ��
u8 RTC_Init_flag=1;//0����
void init_all(){
		NVIC_Configuration();//�����ж����ȷ���
		delay_init();  //һֱҪ����
		OLED_Init();
		//TIM3_PWM_Init(199,7199);	//����Ƶ��899 PWMƵ��=72000/900=8Khz
		//GPIO_keyboard_4_4_init();//������̹ܽſ�
		//LCD_Init();//LCD��ʼ��
		//WKUP_Init();//��������
		//RTC_Init_flag = RTC_Init();//RTC����ʱ��
		//Dac1_Init();//��ģת��
		Adc_Init();//ģ��ת��
		//BEEP_Init();//��ʼ��������
		//TIM4_Int_Init(4999,7199);//��ʱ��5ms
		//TIM3_Int_Init(1999,719);//3ms
		
		//uart_init(9600);//�жϳ�ʼ��
		//uart3_init(9600);//����ģ��
		//ledInit(RCC_APB2Periph_GPIOE, GPIO_Pin_5, GPIOE);//==PE5--PB5
		//LED_INIT_ALL(GPIOB, GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_5, RCC_APB2Periph_GPIOB);
		
		//Keyspress();//�������	
		//usmart_dev.init(SystemCoreClock/1000000);//SystemCoreClock--72MHZ===���ڵ��Թ��߳�ʼ��
		//TIM5_Ctrl_Init(2999,719);
		//FDC2214_Init();//��ʼ��IIC I/O��
}
void Delay(u32 count);
#endif
