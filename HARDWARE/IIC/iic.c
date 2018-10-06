#include "iic.h"
#include "delay.h"

void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );	  //外设时钟使能
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_SetBits(IIC_PORT,IIC_SCL);
	GPIO_SetBits(IIC_PORT,IIC_SDA);
	
}

void SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = IIC_SDA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
}

void SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = IIC_SDA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;   //浮空输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void IIC_Start(void)  //产生IIC起始信号
{
	SDA_OUT();     //sda线输出
	GPIO_SetBits(IIC_PORT,IIC_SDA);	  	  
	GPIO_SetBits(IIC_PORT,IIC_SCL);
	delayus(4);
 	GPIO_ResetBits(IIC_PORT,IIC_SDA);//START:when CLK is high,DATA change form high to low 
	delayus(4);
	GPIO_ResetBits(IIC_PORT,IIC_SCL);//钳住I2C总线，准备发送或接收数据 
}	  

void IIC_Stop(void)  //产生IIC停止信号
{
	SDA_OUT();//sda线输出
	GPIO_ResetBits(IIC_PORT,IIC_SCL);
	GPIO_ResetBits(IIC_PORT,IIC_SDA);//STOP:when CLK is high DATA change form low to high
 	delayus(4);
	GPIO_SetBits(IIC_PORT,IIC_SCL); 
	GPIO_SetBits(IIC_PORT,IIC_SDA);//发送I2C总线结束信号
	delayus(4);							   	
}

uint8_t IIC_Wait_Ack(void)//等待应答信号到来 返回值：1，接收应答失败  0，接收应答成功
{
	uint8_t ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	GPIO_SetBits(IIC_PORT,IIC_SDA);delayus(1);	   
	GPIO_SetBits(IIC_PORT,IIC_SCL);delayus(1);	 
	while(GPIO_ReadInputDataBit(IIC_PORT,IIC_SDA))
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	GPIO_ResetBits(IIC_PORT,IIC_SCL);//时钟输出0 	   
	return 0;  
} 

void IIC_Ack(void)  //产生ACK应答
{
	GPIO_ResetBits(IIC_PORT,IIC_SCL);
	SDA_OUT();
	GPIO_ResetBits(IIC_PORT,IIC_SDA);
	delayus(2);
	GPIO_SetBits(IIC_PORT,IIC_SCL);
	delayus(2);
	GPIO_ResetBits(IIC_PORT,IIC_SCL);
}
    
void IIC_NAck(void)  //不产生ACK应答		
{
	GPIO_ResetBits(IIC_PORT,IIC_SCL);
	SDA_OUT();
	GPIO_SetBits(IIC_PORT,IIC_SDA);
	delayus(2);
	GPIO_SetBits(IIC_PORT,IIC_SCL);
	delayus(2);
	GPIO_ResetBits(IIC_PORT,IIC_SCL);
}					 				     
	  
void IIC_SendByte(uint8_t txd)//IIC发送一个字节 返回从机有无应答 1，有应答 0，无应答		
{
	uint8_t t;   
	SDA_OUT(); 	    
	GPIO_ResetBits(IIC_PORT,IIC_SCL);//拉低时钟开始数据传输
	for(t=0;t<8;t++)
	{
		if((txd&0x80)>>7)
			GPIO_SetBits(IIC_PORT,IIC_SDA);
		else
			GPIO_ResetBits(IIC_PORT,IIC_SDA);  //  IIC_SDA = (txd&0x80)>>7;
		txd<<=1; 	  
		delayus(2);   //对TEA5767这三个延时都是必须的
		GPIO_SetBits(IIC_PORT,IIC_SCL);
		delayus(2); 
		GPIO_ResetBits(IIC_PORT,IIC_SCL);	
		delayus(2);	
	}	 
//	GPIO_ResetBits(IIC_PORT,IIC_SCL);	
//	delayus(2);
//	GPIO_SetBits(IIC_PORT,IIC_SDA);
//	delayus(2); 
} 	    

uint8_t IIC_ReadByte(unsigned char ack) //读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
//	GPIO_ResetBits(IIC_PORT,IIC_SCL);	
//	delayus(2);
//	GPIO_SetBits(IIC_PORT,IIC_SDA);
//	delayus(2); 
  for(i=0;i<8;i++ )
	{
		GPIO_ResetBits(IIC_PORT,IIC_SCL);	
		delayus(2);
    GPIO_SetBits(IIC_PORT,IIC_SCL);
		delayus(2);
    receive<<=1;
    if(GPIO_ReadInputDataBit(IIC_PORT,IIC_SDA)) receive++;   
		delayus(1); 
//		GPIO_ResetBits(IIC_PORT,IIC_SCL); 
//    delayus(2);
  }
	if (!ack)
        IIC_NAck();//发送nACK
  else
        IIC_Ack(); //发送ACK
	
 	return receive;
}
//——————————————————————————————————————————————————有关器件 24C02 的代码
void Write_Add(uint8_t address,uint8_t date)
{
	IIC_Start();
	IIC_SendByte(0xa0);
	IIC_Wait_Ack();
	IIC_SendByte(address);
	IIC_Wait_Ack();
	IIC_SendByte(date);
	IIC_Wait_Ack();
	IIC_Stop();
	delayms(10);	 
}
uint8_t Read_Add(uint8_t address)
{
	uint8_t date;
	IIC_Start();
	IIC_SendByte(0xa0);
	IIC_Wait_Ack();
	IIC_SendByte(address);
	IIC_Wait_Ack();
	IIC_Start();
	IIC_SendByte(0xa1);
	IIC_Wait_Ack();
	date = IIC_ReadByte(0);
	IIC_Stop();
	return date;
}

























