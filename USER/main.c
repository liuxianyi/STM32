#include "include.h"
#include "sys.h"

/***全局变量***/
int Motor_A,Motor_B,Servo,Target_A,Target_B;  //电机，舵机控制相关
float Velocity,Velocity_Set,Angle,Angle_Set;  // 电量,角度相关
int flag_chaosheng, flag_hongwai, dis_cao_int;  // 超声波，红外测距
float UltrasonicWave_Distance;      // 操声波计算出的距离
unsigned int val;  // 红外测距直接值
/*****全局变量***/

/***** 局部变量***/
int UltrasonicWave_Distance_temp;  // 操声波数据处理间接转换量，用来分离整数和小数部分
u16 adc_value,adc_value_point;  // 红外测距数据处理间接转换量，用来分离整数和小数部分
float temp;  // 红外测距数据处理间接转换量，用来分离整数和小数部分
int re_straight_flag=0;
int flag_change =0;
/***** 局部变量***/

int main(void){	
	
	
	/*** 颜色识别***/
		u8  raw_data[9]={0},data=0;
		u16 datas[4]={0};
		RGBC rgbc={0,0,0,0};
		RGB rgb={0,0,0};
		uint16_t CT=0,Lux=0;
		u8 color=0;
	/*** 颜色识别***/
	
		
	/*****初始化配置*****/
		init_all();
		Motor_PWM_Init(7199,0);  // 车轮PWM
		Servo_PWM_Init(9999,144);  // 舵机PWM
	//车头对准我 8400=>最右 8850中间 9350=>最左
		TIM5_Ctrl_Init(7199,719);  // 定时器5处理红外测距
		Timerx_Init_s(7199,0);   // 10Khz的计数频率，计数到5000为500ms 
		UltrasonicWave_Configuration();  // 超声波配置
		keyInit();  // 按键初始化
		IO_path();  // 红外io初始化
		I2C_GPIO_Config();  // IIC_颜色识配置
		delay_ms(1);//等待颜色识别模块初始化完成
	/*****初始化配置****/
		
		
	/****重要初始参数设置*****/
		SERVO=8847;
		Motor_A =800;
		Motor_B =800;
	/****重要初始参数设置*****/
	
	
		while(1){			
			UltrasonicWave_StartMeasure();  //超声波初始化			
			if(flag_chaosheng==1){  // 超声波显示
				OLED_ShowString(1,1,"dist:");
				UltrasonicWave_Distance_temp = UltrasonicWave_Distance;
				dis_cao_int = UltrasonicWave_Distance; 
				OLED_ShowNum(40,1,UltrasonicWave_Distance_temp,3,16);
				UltrasonicWave_Distance -= UltrasonicWave_Distance_temp;
				UltrasonicWave_Distance *=100;
				UltrasonicWave_Distance_temp = UltrasonicWave_Distance;
				OLED_ShowChar(65,1,'.');
				OLED_ShowNum(70,1,UltrasonicWave_Distance_temp,2,16);
			}
			//SERVO=8850;
			/*if(dis_cao_int<9){

				SERVO=8750;
				
			}else{
				SERVO=8847;
			}*/
			
			if(flag_hongwai ==1){  // 红外测距显示
				
				/*temp = (1/(val*0.0000228324+0.00140335))-4.0;
				adc_value = temp;
				
				delay_ms(100);*/

				//OLED_ShowString(0,2,"value:");
				//OLED_ShowNum(45,2,adc_value,5,16);
			}

			
	//车头对准我 8400=>最右 8850中间 9350=>最左
	/****按键区域*****/
			if(KEY_Scan()==KEY_LEFT){//k1
				
				if(SERVO==10000)
					SERVO=10000;
				else
					SERVO +=50;
			}
			if(KEY_Scan()==KEY_DOWN){//k2
				
				if(SERVO ==7000)
					SERVO=700;
				else
				SERVO -=50;
			}
			
			
			/****显示舵机参数***/
			//OLED_ShowString(4,0,"SERVO");
			//OLED_ShowNum(60,0,SERVO,5,16);	
			/****显示舵机参数***/
			
			
			if(KEY_Scan()==KEY_RIGHT){//k3
				Motor_A +=200;
				Motor_B +=200;
				if(Motor_A==7200){
					Motor_A =200;
					Motor_B =200;
				}
					
			}
			if(KEY_Scan()==KEY_UP){//k4
				
				OLED_Clear();
				if(flag_change==0)
				flag_change = 1;
				else
					flag_change=0;								
			}
			
			/****按键区域*****/
			
			
			/*****显示速度***/
			//OLED_ShowString(6,6,"speed");
			//OLED_ShowNum(60,6,Motor_A,5,16);
			/*****显示速度***/
		


			
			/*val=Get_Adc_Average(1,10);
			
			
			
			temp = (1/(val*0.0000228324+0.00140335))-4.0;
			adc_value = temp;
			
			delay_ms(100);
			OLED_ShowString(40,1,"welcome!");
			OLED_ShowString(0,3,"value:");
			OLED_ShowNum(45,3,adc_value,5,16);*/
//			Kinematic_Analysis(Velocity,90);
//			Motor_A =2000;
//			Motor_B =2000;
			//Xianfu_Pwm();                                                      //===PWM限幅
			//Set_Pwm(Motor_A,Motor_B,Servo);
			//Motor_A =-1000;
			//Motor_B =1000;
			
					
			/***轮子PWM处理***/
			if(Motor_A<0)			PWMA1=7200,PWMA2=7200+Motor_A;
			else 							PWMA2=7200,PWMA1=7200-Motor_A;
			if(Motor_B<0)			PWMB1=7200,PWMB2=7200+Motor_B;
			else 	            PWMB2=7200,PWMB1=7200-Motor_B;
			/***轮子PWM处理***/
	
	
			//显示红外循迹模块值
			//OLED_ShowNum(105,3,readIOPath(),1,16);
			//显示红外循迹模块值
			
			//OLED_Clear();
			if(flag_change==0){
					
				if(Single_ReadI2C(0xb4,0x0f,raw_data,1))//读取颜色
					datas[2]=color=raw_data[0];
				OLED_ShowNum(30,3,color,3,16);
			
				if(color<=4&&color>=0){  // 红灯
					
						Motor_A =0;
						Motor_B =0;
				}
				if(color>6&&color<=32){  // 绿灯
						Motor_A =800;
						Motor_B =800;
					
				}
				
				if(Single_ReadI2C(0xb4,0x0c,raw_data,3))//读取处理后的rgb
				{
					rgb.Red=raw_data[0];
					rgb.Green=raw_data[1];
					rgb.Blue=raw_data[2];
				}
				if(dis_cao_int<9){

					SERVO=8750;
					
				}else{
					SERVO=8847;
				}
				OLED_ShowNum(10,5,rgb.Red,3,16);
				OLED_ShowNum(40,5,rgb.Green,3,16);
				OLED_ShowNum(70,5,rgb.Blue,3,16);
				
			}else{
				/****显示舵机参数***/
				OLED_ShowString(4,3,"SERVO");
				OLED_ShowNum(60,3,SERVO,5,16);	
				/****显示舵机参数***/
				
				/*****显示速度***/
				OLED_ShowString(6,6,"speed");
				OLED_ShowNum(60,6,Motor_A,5,16);
				/*****显示速度***/
				
				
			}
		
			
			
			
		}
		
}

