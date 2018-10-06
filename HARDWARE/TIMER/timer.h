#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "delay.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/4
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//********************************************************************************


#define PWMA1   TIM4->CCR1  //���A
#define PWMA2   TIM4->CCR2 

#define PWMB1   TIM4->CCR3  //���B
#define PWMB2   TIM4->CCR4

#define SERVO   TIM1->CCR4  //�������

#define SERVO_INIT 750


void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc);
//void TIM4_Int_Init(u16 arr,u16 psc);
//���벶��
void TIM5_Cap_Init(u16 arr,u16 psc);
void TIM5_IRQHandler(void);
void TIM5_Ctrl_Init(u16 arr,u16 psc);

void Motor_PWM_Init(u16 arr,u16 psc);
void Xianfu_Pwm(void);
void Set_Pwm(int motor_a,int motor_b,int servo);
void Kinematic_Analysis(float velocity,float angle);

void Servo_PWM_Init(u16 arr,u16 psc);
#endif
