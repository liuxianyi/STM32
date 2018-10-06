#include "include.h"
#include "sys.h"

/***ȫ�ֱ���***/
int Motor_A,Motor_B,Servo,Target_A,Target_B;  //���������������
float Velocity,Velocity_Set,Angle,Angle_Set;  // ����,�Ƕ����
int flag_chaosheng, flag_hongwai, dis_cao_int;  // ��������������
float UltrasonicWave_Distance;      // ������������ľ���
unsigned int val;  // ������ֱ��ֵ
/*****ȫ�ֱ���***/

/***** �ֲ�����***/
int UltrasonicWave_Distance_temp;  // ���������ݴ�����ת��������������������С������
u16 adc_value,adc_value_point;  // ���������ݴ�����ת��������������������С������
float temp;  // ���������ݴ�����ת��������������������С������
int re_straight_flag=0;
int flag_change =0;
/***** �ֲ�����***/

int main(void){	
	
	
	/*** ��ɫʶ��***/
		u8  raw_data[9]={0},data=0;
		u16 datas[4]={0};
		RGBC rgbc={0,0,0,0};
		RGB rgb={0,0,0};
		uint16_t CT=0,Lux=0;
		u8 color=0;
	/*** ��ɫʶ��***/
	
		
	/*****��ʼ������*****/
		init_all();
		Motor_PWM_Init(7199,0);  // ����PWM
		Servo_PWM_Init(9999,144);  // ���PWM
	//��ͷ��׼�� 8400=>���� 8850�м� 9350=>����
		TIM5_Ctrl_Init(7199,719);  // ��ʱ��5���������
		Timerx_Init_s(7199,0);   // 10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms 
		UltrasonicWave_Configuration();  // ����������
		keyInit();  // ������ʼ��
		IO_path();  // ����io��ʼ��
		I2C_GPIO_Config();  // IIC_��ɫʶ����
		delay_ms(1);//�ȴ���ɫʶ��ģ���ʼ�����
	/*****��ʼ������****/
		
		
	/****��Ҫ��ʼ��������*****/
		SERVO=8847;
		Motor_A =800;
		Motor_B =800;
	/****��Ҫ��ʼ��������*****/
	
	
		while(1){			
			UltrasonicWave_StartMeasure();  //��������ʼ��			
			if(flag_chaosheng==1){  // ��������ʾ
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
			
			if(flag_hongwai ==1){  // ��������ʾ
				
				/*temp = (1/(val*0.0000228324+0.00140335))-4.0;
				adc_value = temp;
				
				delay_ms(100);*/

				//OLED_ShowString(0,2,"value:");
				//OLED_ShowNum(45,2,adc_value,5,16);
			}

			
	//��ͷ��׼�� 8400=>���� 8850�м� 9350=>����
	/****��������*****/
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
			
			
			/****��ʾ�������***/
			//OLED_ShowString(4,0,"SERVO");
			//OLED_ShowNum(60,0,SERVO,5,16);	
			/****��ʾ�������***/
			
			
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
			
			/****��������*****/
			
			
			/*****��ʾ�ٶ�***/
			//OLED_ShowString(6,6,"speed");
			//OLED_ShowNum(60,6,Motor_A,5,16);
			/*****��ʾ�ٶ�***/
		


			
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
			//Xianfu_Pwm();                                                      //===PWM�޷�
			//Set_Pwm(Motor_A,Motor_B,Servo);
			//Motor_A =-1000;
			//Motor_B =1000;
			
					
			/***����PWM����***/
			if(Motor_A<0)			PWMA1=7200,PWMA2=7200+Motor_A;
			else 							PWMA2=7200,PWMA1=7200-Motor_A;
			if(Motor_B<0)			PWMB1=7200,PWMB2=7200+Motor_B;
			else 	            PWMB2=7200,PWMB1=7200-Motor_B;
			/***����PWM����***/
	
	
			//��ʾ����ѭ��ģ��ֵ
			//OLED_ShowNum(105,3,readIOPath(),1,16);
			//��ʾ����ѭ��ģ��ֵ
			
			//OLED_Clear();
			if(flag_change==0){
					
				if(Single_ReadI2C(0xb4,0x0f,raw_data,1))//��ȡ��ɫ
					datas[2]=color=raw_data[0];
				OLED_ShowNum(30,3,color,3,16);
			
				if(color<=4&&color>=0){  // ���
					
						Motor_A =0;
						Motor_B =0;
				}
				if(color>6&&color<=32){  // �̵�
						Motor_A =800;
						Motor_B =800;
					
				}
				
				if(Single_ReadI2C(0xb4,0x0c,raw_data,3))//��ȡ������rgb
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
				/****��ʾ�������***/
				OLED_ShowString(4,3,"SERVO");
				OLED_ShowNum(60,3,SERVO,5,16);	
				/****��ʾ�������***/
				
				/*****��ʾ�ٶ�***/
				OLED_ShowString(6,6,"speed");
				OLED_ShowNum(60,6,Motor_A,5,16);
				/*****��ʾ�ٶ�***/
				
				
			}
		
			
			
			
		}
		
}

