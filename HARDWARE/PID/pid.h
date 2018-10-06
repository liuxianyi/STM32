#ifndef _PID_H
#define _PID_H
#include "stm32f10x.h"
/*
float  	Kp =     					0.32  ; //��������

float  	Ti =              0.09 ; //����ʱ�䳣��

float 	Td =              0.0028 ;  //΢��ʱ�䳣��

#define T                 0.02 //��������

#define Ki     						Kp*(T/Ti)        // Kp Ki Kd ������Ҫ����

#define Kd                Kp*(Td/T)
*/
/*����������������������������PID�ṹ�塪������������������������������*/
typedef struct
{
	float  SetSpeed; 	//  �����趨ֵ
	float 	ActualSpeed;		//	ʵ��ֵ
		
	float  err;      //  ����ƫ��ֵ 
	float  err_last;        //  ������һ��ƫ��ֵ
	float  Kp,Ki,Kd;      //  ������������֣�΢��ϵ��

	float voltage;     //  �����ѹֵ==����ִ�����ı���
	float integral;     //  �������ֵ

}PID_P;

typedef struct
{
	float  SetSpeed; 	//  �����趨ֵ
	float 	ActualSpeed;		//	ʵ��ֵ
		
	float  err;      //  ����ƫ��ֵ 
	float  err_last;        //  ������һ��ƫ��ֵ
	float  Kp,Ki,Kd;      //  ������������֣�΢��ϵ��

	float err_next;     //  ��������ǰ��ƫ��ֵ

}PID_I;
void M1Init_PID_Paramete(float p,float I,float D) ;
float M1PID_IncCalu(float SetSpeed); 			//���ڱ�����M1��λ��ʽPID����

void M2Init_PID_Paramete(float p,float I,float D) ;
float M2PID_IncCalu(float SetSpeed); 			//���ڱ�����M2������ʽPID���� 

void M3Init_PID_Paramete(float p,float I,float D) ;
float M3PID_IncCalu(float SetSpeed); 			//���ڱ�����M3�Ļ��ַ����PID���� 

#endif
