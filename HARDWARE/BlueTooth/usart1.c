#include "usart1.h"
#include <stdio.h>
#include "delay.h"
#include "usart.h"

void uart2_init(u32 bound)
{
  	//GPIO�˿�����
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		 
		RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART3|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
     //USART1_TX   PA.9 Pb7
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART1_RX	  PA.10  Pb6
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

   //Usart1 NVIC ����

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

		USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART3, &USART_InitStructure); //��ʼ������
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�
    USART_Cmd(USART3, ENABLE);                     //ʹ�ܴ��� 

}
//�����жϳ�������ڽ��յڶ�������֮ǰ���жϣ�������Щ����û�н���

void USART3_IRQHandler(void)                	//����1�жϷ������
{
	
	u8 Res;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART3);//(USART1->DR);	//��ȡ���յ�������
		USART_SendData(USART3,'k'); 
			printf("%c",'f');
		//printf(" contray direction!");
		}
		/*switch(Res)
		{
			case 'l'://Change_PWM(2000,1000,2000,1000);
			printf(" turn left!");
			USART_SendData(USART1,'s');
			break;
			case 'r'://Change_PWM(1000,2000,1000,2000);
			printf(" turn right!");
			break;
			case 's'://Change_PWM(0,0,0,0);
			printf(" stop!");
			break;
			case 'f'://Direction(1);//��ת
			//Change_PWM(2000,2000,2000,2000);
			printf(" start!");
			printf(" right direction");
			break;
			case 'b'://Direction(0);//��ת
			//Change_PWM(2000,2000,2000,2000);
			printf(" contray direction!");
			break;
		}*/
}
/*
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB
#if 1
#pragma import(__use_no_semihosting)   
//��׼����Ҫ��֧�ֺ���   
struct __FILE 
{ 
	int handle; 
}; 
FILE __stdout;      
//����_sys_exit()�Ա���ʹ�ð�����ģʽ  
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{
  	USART_SendData(USART1, (u8) ch);
  	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
  	return ch;
}
#endif
*/
