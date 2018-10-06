#include "key.h"
/*描述：初始化战舰的独立按键
 *参数：无
 *返回值：无
 *注意：设置模式应该为上拉输入或下拉输入
 *
 */
void keyInit(){
	GPIO_InitTypeDef  GPIO_InitStructure;//
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB端口时钟
	//开启时钟，使用或来同时开启
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_5;				 
	 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //上拉输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 
  GPIO_Init(GPIOE, &GPIO_InitStructure);					 //根据设定参数初始化GPIOE
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/*描述：延时函数
 *参数：u16 count
 *返回值：无
 */
void delay(u16 count){
	u16 i=0;
  for(;i<count;i++);
}
/*描述：按键扫描(支持连续按)
 *参数：无
 *返回值：无
 */
u8 KEY_Scan(){
	if(  KEY0==0||KEY1==0||KEY2==0||KEY4==0 )
	{
		delay_ms(10);//去抖动 
		 
		if(KEY0==0)return KEY_RIGHT;
		else if(KEY1==0)return KEY_DOWN;
		else if(KEY2==0)return KEY_LEFT;
		else if(KEY4==0)return KEY_UP;
	}     
 	return 0;// 无按键按下
}

u8 KEY_scan_no_onclick(){
	static u8 key_up=1;
	if( key_up&&( KEY0==0||KEY1==0||KEY2==0||KEY3==1) )
	{
		delay_ms(10);//去抖动 
		 key_up=0;
		if(KEY0==0)return KEY_RIGHT;
		else if(KEY1==0)return KEY_DOWN;
		else if(KEY2==0)return KEY_LEFT;
		else if(KEY3==1)return KEY_UP;
	} else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==0)key_up=1;     
 	return 0;// 无按键按下,key_up才会初始化
	
}


