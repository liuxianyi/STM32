#include "led.h"
#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	
/***********************************
 * ������io���ø� ʵ��B�ڵĲ���
 * ������GPIO_TypeDef* GPIOx �˿�
 *          value:[GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG]            
 *			 GPIOMode_TypeDef GPIO_Mode_X ģʽ
 *   				value��[GPIO_Mode_AIN ,GPIO_Mode_IN_FLOATING = 0x04, GPIO_Mode_IPD = 0x28,  GPIO_Mode_IPU = 0x48,
 *          				GPIO_Mode_Out_OD = 0x14, GPIO_Mode_Out_PP = 0x10, GPIO_Mode_AF_OD = 0x1C, GPIO_Mode_AF_PP]
 *       GPIOSpeed_TypeDef GPIO_Speed_XMHZ IO������ 
 *   				value: [GPIO_Speed_10MHz ,GPIO_Speed_2MHz, GPIO_Speed_50MHz]
 *       uint16_t GPIO_Pin�ں� 
 *   				value:[GPIO_Pin_0-15��GPIO_Pin_ALL]
 *       uint16_t RCC_APB2Periphʱ��
 *  				value:[RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB, RCC_APB2Periph_GPIOC, RCC_APB2Periph_GPIOD,
 *  							RCC_APB2Periph_GPIOE, RCC_APB2Periph_GPIOF, RCC_APB2Periph_GPIOG]
 * ����ֵ��void
 ***********************************/
 void LED_INIT_ALL(GPIO_TypeDef* GPIOx, GPIOMode_TypeDef GPIO_Mode_X, GPIOSpeed_TypeDef GPIO_Speed_XMHZ, uint16_t GPIO_Pin, uint16_t RCC_APB2Periph){
	GPIO_InitTypeDef  GPIO_InitStructure;//
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);	 //ʹ��PB�˿�ʱ��
	//����ʱ�ӣ�ʹ�û���ͬʱ����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin;				 //LED0-->PB.5 �˿�����
	 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_X; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_XMHZ;		 //IO���ٶ�Ϊ50MHz
	 
  GPIO_Init(GPIOx, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
  //GPIO_SetBits(GPIOx,GPIO_Pin);						 //PB.5 �����

  //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;		 //LED1-->PE.5 �˿�����, �������
}	
 
void pinSetHigh(GPIO_TypeDef* GPIOx, GPIOMode_TypeDef GPIO_Mode_X, GPIOSpeed_TypeDef GPIO_Speed_XMHZ, uint16_t GPIO_Pin, uint16_t RCC_APB2Periph){
	GPIO_InitTypeDef  GPIO_InitStructure;//
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);	 //ʹ��PB�˿�ʱ��
	//����ʱ�ӣ�ʹ�û���ͬʱ����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin;				 //LED0-->PB.5 �˿�����
	 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_X; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_XMHZ;		 //IO���ٶ�Ϊ50MHz
	 
  GPIO_Init(GPIOx, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
  GPIO_SetBits(GPIOx,GPIO_Pin);						 //PB.5 �����

  //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;		 //LED1-->PE.5 �˿�����, �������
	 

}	
/***********************************
 * ������io���õ� ʵ��B�ڵĲ���
 * ������GPIO_TypeDef* GPIOx  �˿�
 *          value:[GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG]            
 *			 GPIOMode_TypeDef GPIO_Mode_X  ģʽ
 *   				value��[GPIO_Mode_AIN ,GPIO_Mode_IN_FLOATING, GPIO_Mode_IPD,  GPIO_Mode_IPU,
 *          				GPIO_Mode_Out_OD, GPIO_Mode_Out_PP, GPIO_Mode_AF_OD, GPIO_Mode_AF_PP]
 *       GPIOSpeed_TypeDef GPIO_Speed_XMHZ IO������ 
 *   				value: [GPIO_Speed_10MHz ,GPIO_Speed_2MHz, GPIO_Speed_50MHz]
 *       uint16_t GPIO_Pin �ں� 
 *   				value:[GPIO_Pin_0-15��GPIO_Pin_ALL]
 *       uint16_t RCC_APB2Periph ʱ��
 *  				value:[RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB, RCC_APB2Periph_GPIOC, RCC_APB2Periph_GPIOD,
 *  							RCC_APB2Periph_GPIOE, RCC_APB2Periph_GPIOF, RCC_APB2Periph_GPIOG]
 * ����ֵ��void
 ***********************************/
void pinSetlow(GPIO_TypeDef* GPIOx, GPIOMode_TypeDef GPIO_Mode_X, GPIOSpeed_TypeDef GPIO_Speed_XMHZ, uint16_t GPIO_Pin, uint16_t RCC_APB2Periph){
	GPIO_InitTypeDef  GPIO_InitStructure;//
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);	 //ʹ��PB�˿�ʱ��
	//����ʱ�ӣ�ʹ�û���ͬʱ����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin;				 //LED0-->PB.5 �˿�����
	 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_X; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_XMHZ;		 //IO���ٶ�Ϊ50MHz
	 
  GPIO_Init(GPIOx, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
  GPIO_ResetBits(GPIOx,GPIO_Pin);
	
}


/**
 *������io�ڳ�ʼ��  ������� IO���ٶ�Ϊ50MHz
 *������GPIO_TypeDef* GPIOx  �˿�
 *          value:[GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG]
 *      uint16_t GPIO_Pin �ں� 
 *   				value:[GPIO_Pin_0-15��GPIO_Pin_ALL]
 *      uint16_t RCC_APB2Periph ʱ��
 *  				value:[RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB, RCC_APB2Periph_GPIOC, RCC_APB2Periph_GPIOD,
 *  							RCC_APB2Periph_GPIOE, RCC_APB2Periph_GPIOF, RCC_APB2Periph_GPIOG]
 *����ֵ����
 */
void ledInit(uint16_t RCC_APB2Periph, uint16_t GPIO_Pin, GPIO_TypeDef* GPIOx){
	GPIO_InitTypeDef  GPIO_InitStructure;//
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	//����ʱ�ӣ�ʹ�û���ͬʱ����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin;				 
	 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 
  GPIO_Init(GPIOx, &GPIO_InitStructure);					 
  
}

/**
 *������GPIO_TypeDef* GPIOx  �˿�
 *          value:[GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG]
 *      uint16_t GPIO_Pin �ں� 
 *   				value:[GPIO_Pin_0-15��GPIO_Pin_ALL]
 * 
 */
void pinSetHigh_ONE(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	GPIO_SetBits(GPIOx,GPIO_Pin);
}
/**
 *������GPIO_TypeDef* GPIOx  �˿�
 *          value:[GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG]
 *      uint16_t GPIO_Pin �ں� 
 *   				value:[GPIO_Pin_0-15��GPIO_Pin_ALL]
 * 
 */
void pinSetlow_ONE(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	
	GPIO_ResetBits(GPIOx,GPIO_Pin);
}

void LED_Init_PD_2(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); //ʹ��PD �˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				     //LED-->PD.2 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);					       //�����趨������ʼ��GPIOD.2
 GPIO_SetBits(GPIOD,GPIO_Pin_2);						           //PD.2 ����ߣ�������
	
}

void IO_path(void){//����ѭ��
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE); //ʹ��PG �˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				     //LED-->PG.1 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //��������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOG, &GPIO_InitStructure);					       //�����趨������ʼ��
	
}
uint8_t readIOPath(void){
	
	return GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_1);
	
}

void setPBout(u8 sta)
{
	//LED0=sta;
}
void setPEout(u8 sta)
{
	//LED1=sta;
}