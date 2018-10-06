#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "delay.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//定时器 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/4
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//********************************************************************************


#define PWMA1   TIM4->CCR1  //电机A
#define PWMA2   TIM4->CCR2 

#define PWMB1   TIM4->CCR3  //电机B
#define PWMB2   TIM4->CCR4

#define SERVO   TIM1->CCR4  //舵机引脚

#define SERVO_INIT 750


void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc);
//void TIM4_Int_Init(u16 arr,u16 psc);
//输入捕获
void TIM5_Cap_Init(u16 arr,u16 psc);
void TIM5_IRQHandler(void);
void TIM5_Ctrl_Init(u16 arr,u16 psc);

void Motor_PWM_Init(u16 arr,u16 psc);
void Xianfu_Pwm(void);
void Set_Pwm(int motor_a,int motor_b,int servo);
void Kinematic_Analysis(float velocity,float angle);

void Servo_PWM_Init(u16 arr,u16 psc);
#endif
