#ifndef __IIC_H
#define __IIC_H
#include "stm32f10x.h"

#define IIC_PORT  GPIOC
#define IIC_SCL		GPIO_Pin_12
#define IIC_SDA   GPIO_Pin_11

void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
uint8_t IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_SendByte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t IIC_ReadByte(unsigned char ack) ;
void Write_Add(uint8_t address,uint8_t date);
uint8_t Read_Add(uint8_t address);

#endif
















