#include "keyboard.h"
#include "led.h"
#define val_GPIO GPIO_ReadInputData(GPIOC)
//GPIO初始化函数
void GPIO_keyboard_4_4_init(void)
{
 GPIO_InitTypeDef GPIO_InitStructuress;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);           //打开时钟               
 GPIO_InitStructuress.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;  //初始化PD0-PD3
 GPIO_InitStructuress.GPIO_Mode = GPIO_Mode_Out_PP ;     // 重要
                                            
 GPIO_InitStructuress.GPIO_Speed = GPIO_Speed_50MHz;

 GPIO_Init(GPIOC, &GPIO_InitStructuress); 
 GPIO_InitStructuress.GPIO_Pin =GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;    //初始化PD4-PD7
 GPIO_InitStructuress.GPIO_Mode =GPIO_Mode_IPD ;//重要
 GPIO_InitStructuress.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOC, &GPIO_InitStructuress); 
 GPIO_SetBits( GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
 GPIO_ResetBits( GPIOC,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
}
//按键函数
void Keyspress()
{
	int KeyValue=0;//保存值
	int f=5;
	while(1)
	{
		OLED_ShowString(40,0,"wellcome!");
		
		 if((val_GPIO&0xff)!=0x0f){
			 
				delay_ms(20);
			 
			 if((val_GPIO&0xff)!=0x0f){ 
				 
				 GPIO_SetBits(GPIO_4_4,GPIO_Pin_0); 
				 //GPIO_Write(GPIOA, 0xf7);
				 GPIO_ResetBits(GPIO_4_4,GPIO_Pin_3|GPIO_Pin_1|GPIO_Pin_2);
				 
				 switch(val_GPIO&0xff){
					 
											case 0x11:KeyValue=13;break; 
			 
											case 0x21:KeyValue=14;break; 
			 
											case 0x41:KeyValue=15;break; 
			 
											case 0x81:KeyValue=16;break;
											//default:KeyValue=23;
										 } 
				 
											GPIO_SetBits(GPIO_4_4,GPIO_Pin_1);
			 
											GPIO_ResetBits(GPIO_4_4,GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3);
			 
											 switch(val_GPIO&0xff){ 
												 
											 case 0x12:KeyValue=9;break;
			 
											 case 0x22:KeyValue=10;break; 
			 
											 case 0x42:KeyValue=11;break;
			 
											 case 0x82:KeyValue=12;break; 
			 
											} 
											 GPIO_SetBits(GPIO_4_4,GPIO_Pin_2); 
			 
											 GPIO_ResetBits(GPIO_4_4,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3);
			 
												switch(val_GPIO&0xff){
													
													case 0x14:KeyValue=5;break;
			 
													case 0x24:KeyValue=6;break;
			 
													case 0x44:KeyValue=7;break;
			 
													case 0x84:KeyValue=8;break;
												 } 
													GPIO_SetBits(GPIO_4_4,GPIO_Pin_3); 
			 
													GPIO_ResetBits(GPIO_4_4,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);
																										
												 switch(val_GPIO&0xff){
													 
													 case 0x18:KeyValue=1;break;
			 
													 case 0x28:KeyValue=2;break; 
			 
													 case 0x48:KeyValue=3;break;
			 
													 case 0x88:KeyValue=4;break;
													 } 
												 GPIO_SetBits(GPIO_4_4,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2 |GPIO_Pin_3);
													 
												 GPIO_ResetBits(GPIO_4_4, GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 |GPIO_Pin_7);
													 
												 while((GPIO_ReadInputData(GPIOC)&0xff)!=0x0f);//等待按键释放
													 
												 switch(KeyValue){ 
													 
															case 1:		f=1;	break;
															case 2:		f=2;	break;
															case 3:		f=3;	break;
															case 4: 	f=4;	break;
															case 5: 	f=5;	break;
															case 6: 	f=6;	break;
															case 7:		f=7;	break;
															case 8:		f=8;	break;
															case 9: 	f=9;	break;
															case 10: 	f=10;	break;
															case 11:  f=11;	break;
															case 12:  f=12;	break;
															case 13: 	f=13;	break;
															case 14: 	f=14;	break;
															case 15: 	f=15;	break;
															case 16: 	f=16;	break;
													}
												 
												OLED_ShowNum(32,2,f,2,16);
									}  
									//OLED_ShowNum(32,2,8,2,16);
				}
		 
			if(f==1) pinSetlow(GPIOE, GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_5, RCC_APB2Periph_GPIOE);
			if(f==2) pinSetHigh(GPIOE, GPIO_Mode_Out_PP, GPIO_Speed_50MHz, GPIO_Pin_5, RCC_APB2Periph_GPIOE);
		} 
}
