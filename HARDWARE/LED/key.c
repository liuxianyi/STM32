#include "key.h"
/*��������ʼ��ս���Ķ�������
 *��������
 *����ֵ����
 *ע�⣺����ģʽӦ��Ϊ�����������������
 *
 */
void keyInit(){
	GPIO_InitTypeDef  GPIO_InitStructure;//
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PB�˿�ʱ��
	//����ʱ�ӣ�ʹ�û���ͬʱ����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_5;				 
	 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 
  GPIO_Init(GPIOE, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOE
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/*��������ʱ����
 *������u16 count
 *����ֵ����
 */
void delay(u16 count){
	u16 i=0;
  for(;i<count;i++);
}
/*����������ɨ��(֧��������)
 *��������
 *����ֵ����
 */
u8 KEY_Scan(){
	if(  KEY0==0||KEY1==0||KEY2==0||KEY4==0 )
	{
		delay_ms(10);//ȥ���� 
		 
		if(KEY0==0)return KEY_RIGHT;
		else if(KEY1==0)return KEY_DOWN;
		else if(KEY2==0)return KEY_LEFT;
		else if(KEY4==0)return KEY_UP;
	}     
 	return 0;// �ް�������
}

u8 KEY_scan_no_onclick(){
	static u8 key_up=1;
	if( key_up&&( KEY0==0||KEY1==0||KEY2==0||KEY3==1) )
	{
		delay_ms(10);//ȥ���� 
		 key_up=0;
		if(KEY0==0)return KEY_RIGHT;
		else if(KEY1==0)return KEY_DOWN;
		else if(KEY2==0)return KEY_LEFT;
		else if(KEY3==1)return KEY_UP;
	} else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==0)key_up=1;     
 	return 0;// �ް�������,key_up�Ż��ʼ��
	
}


