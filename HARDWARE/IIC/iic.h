#ifndef __IIC_H
#define __IIC_H
#include "stm32f10x.h"

#define IIC_PORT  GPIOC
#define IIC_SCL		GPIO_Pin_12
#define IIC_SDA   GPIO_Pin_11

void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
uint8_t IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_SendByte(uint8_t txd);			//IIC发送一个字节
uint8_t IIC_ReadByte(unsigned char ack) ;
void Write_Add(uint8_t address,uint8_t date);
uint8_t Read_Add(uint8_t address);

#endif
















