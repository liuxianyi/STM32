#include "pid.h"
#include <math.h>
/*！！！！！！！！！！！！！！！！！！！！了崔塀PID！！！！！！！！！！！！！！！！！！*/
PID_P M1;

void M1Init_PID_Paramete(float P,float I,float D){
	M1.SetSpeed=0.0;
	M1.ActualSpeed=0.0;
	M1.err=0.0;
	M1.err_last=0.0;
	M1.voltage=0.0;
	M1.integral=0.0;
	M1.Kp=P;
	M1.Ki=I;
	M1.Kd=D;
	
}
float M1PID_IncCalu(float SetSpeed)     
{
	M1.SetSpeed=SetSpeed;
	M1.err=M1.SetSpeed-M1.ActualSpeed;
	M1.integral+=M1.err;
	M1.voltage=M1.Kp*M1.err+M1.Ki*M1.integral+M1.Kd*(M1.err-M1.err_last);
	M1.err_last=M1.err;
	M1.ActualSpeed=M1.voltage*1.0;
	return M1.ActualSpeed;
}

/*！！！！！！！！！！！！！！！！！！！！奐楚塀PID！！！！！！！！！！！！！！！！！！*/
PID_I M2;
void M2Init_PID_Paramete(float P,float I,float D){
	M2.SetSpeed=0.0;
	M2.ActualSpeed=0.0;
	M2.err=0.0;
	M2.err_last=0.0;
	M2.err_next=0.0;
	M2.Kp=P;
	M2.Ki=I;
	M2.Kd=D;
}

float M2PID_IncCalu(float SetSpeed)     
{
	float incrementSpeed;
	M2.SetSpeed=SetSpeed;
	M2.err=M2.SetSpeed-M2.ActualSpeed;
	incrementSpeed=M2.Kp*(M2.err-M2.err_next)+M2.Ki*M2.err+M2.Kd*(M2.err-2*M2.err_next+M2.err_last);
	M2.ActualSpeed+=incrementSpeed;
	M2.err_last=M2.err_next;
	M2.err_next=M2.err;
	return M2.ActualSpeed;
}
PID_P M3;
/*！！！！！！！！！！！！！！！！單晒！！！！！！！！！！！！！！！！！！！！！！*/
void M3Init_PID_Paramete(float P,float I,float D){
	M3.SetSpeed=0.0;
	M3.ActualSpeed=0.0;
	M3.err=0.0;
	M3.err_last=0.0;
	M3.voltage=0.0;
	M3.integral=0.0;
	M3.Kp=P;
	M3.Ki=I;
	M3.Kd=D;
	
}

float M3PID_IncCalu(float SetSpeed)     
{
	float index;
	M3.SetSpeed=SetSpeed;
	M3.err=M3.SetSpeed-M3.ActualSpeed;
	if(fabs(M3.err)>888.0){
		index=0.0;
	}else if(fabs(M3.err)>860.0){
		index=1.0;
		M3.integral+=M3.err;
	}else{
		index=(200.0-fabs(M3.err))/20;
		M3.integral+=M3.err;
	}
	M3.voltage=M3.Kp*M3.err+index*M3.Ki*M3.integral+M3.Kd*(M3.err-M3.err_last);
	M3.err_last=M3.err;
	M3.ActualSpeed=M3.voltage*1.0;
	return M3.ActualSpeed;
}

