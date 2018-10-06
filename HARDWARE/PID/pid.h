#ifndef _PID_H
#define _PID_H
#include "stm32f10x.h"
/*
float  	Kp =     					0.32  ; //比例常数

float  	Ti =              0.09 ; //积分时间常数

float 	Td =              0.0028 ;  //微分时间常数

#define T                 0.02 //采样周期

#define Ki     						Kp*(T/Ti)        // Kp Ki Kd 三个主要参数

#define Kd                Kp*(Td/T)
*/
/*——————————————PID结构体————————————————*/
typedef struct
{
	float  SetSpeed; 	//  定义设定值
	float 	ActualSpeed;		//	实际值
		
	float  err;      //  定义偏差值 
	float  err_last;        //  定义上一个偏差值
	float  Kp,Ki,Kd;      //  定义比例，积分，微分系数

	float voltage;     //  定义电压值==控制执行器的变量
	float integral;     //  定义积分值

}PID_P;

typedef struct
{
	float  SetSpeed; 	//  定义设定值
	float 	ActualSpeed;		//	实际值
		
	float  err;      //  定义偏差值 
	float  err_last;        //  定义上一个偏差值
	float  Kp,Ki,Kd;      //  定义比例，积分，微分系数

	float err_next;     //  定义最上前的偏差值

}PID_I;
void M1Init_PID_Paramete(float p,float I,float D) ;
float M1PID_IncCalu(float SetSpeed); 			//关于被控量M1的位置式PID调节

void M2Init_PID_Paramete(float p,float I,float D) ;
float M2PID_IncCalu(float SetSpeed); 			//关于被控量M2的增量式PID调节 

void M3Init_PID_Paramete(float p,float I,float D) ;
float M3PID_IncCalu(float SetSpeed); 			//关于被控量M3的积分分离的PID调节 

#endif
