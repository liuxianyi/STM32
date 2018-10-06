#include "iic.h"
#include "delay.h"

void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );	  //����ʱ��ʹ��
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_SetBits(IIC_PORT,IIC_SCL);
	GPIO_SetBits(IIC_PORT,IIC_SDA);
	
}

void SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = IIC_SDA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
}

void SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = IIC_SDA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;   //��������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void IIC_Start(void)  //����IIC��ʼ�ź�
{
	SDA_OUT();     //sda�����
	GPIO_SetBits(IIC_PORT,IIC_SDA);	  	  
	GPIO_SetBits(IIC_PORT,IIC_SCL);
	delayus(4);
 	GPIO_ResetBits(IIC_PORT,IIC_SDA);//START:when CLK is high,DATA change form high to low 
	delayus(4);
	GPIO_ResetBits(IIC_PORT,IIC_SCL);//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  

void IIC_Stop(void)  //����IICֹͣ�ź�
{
	SDA_OUT();//sda�����
	GPIO_ResetBits(IIC_PORT,IIC_SCL);
	GPIO_ResetBits(IIC_PORT,IIC_SDA);//STOP:when CLK is high DATA change form low to high
 	delayus(4);
	GPIO_SetBits(IIC_PORT,IIC_SCL); 
	GPIO_SetBits(IIC_PORT,IIC_SDA);//����I2C���߽����ź�
	delayus(4);							   	
}

uint8_t IIC_Wait_Ack(void)//�ȴ�Ӧ���źŵ��� ����ֵ��1������Ӧ��ʧ��  0������Ӧ��ɹ�
{
	uint8_t ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
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
	GPIO_ResetBits(IIC_PORT,IIC_SCL);//ʱ�����0 	   
	return 0;  
} 

void IIC_Ack(void)  //����ACKӦ��
{
	GPIO_ResetBits(IIC_PORT,IIC_SCL);
	SDA_OUT();
	GPIO_ResetBits(IIC_PORT,IIC_SDA);
	delayus(2);
	GPIO_SetBits(IIC_PORT,IIC_SCL);
	delayus(2);
	GPIO_ResetBits(IIC_PORT,IIC_SCL);
}
    
void IIC_NAck(void)  //������ACKӦ��		
{
	GPIO_ResetBits(IIC_PORT,IIC_SCL);
	SDA_OUT();
	GPIO_SetBits(IIC_PORT,IIC_SDA);
	delayus(2);
	GPIO_SetBits(IIC_PORT,IIC_SCL);
	delayus(2);
	GPIO_ResetBits(IIC_PORT,IIC_SCL);
}					 				     
	  
void IIC_SendByte(uint8_t txd)//IIC����һ���ֽ� ���شӻ�����Ӧ�� 1����Ӧ�� 0����Ӧ��		
{
	uint8_t t;   
	SDA_OUT(); 	    
	GPIO_ResetBits(IIC_PORT,IIC_SCL);//����ʱ�ӿ�ʼ���ݴ���
	for(t=0;t<8;t++)
	{
		if((txd&0x80)>>7)
			GPIO_SetBits(IIC_PORT,IIC_SDA);
		else
			GPIO_ResetBits(IIC_PORT,IIC_SDA);  //  IIC_SDA = (txd&0x80)>>7;
		txd<<=1; 	  
		delayus(2);   //��TEA5767��������ʱ���Ǳ����
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

uint8_t IIC_ReadByte(unsigned char ack) //��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
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
        IIC_NAck();//����nACK
  else
        IIC_Ack(); //����ACK
	
 	return receive;
}
//�����������������������������������������������������������������������������������������������������й����� 24C02 �Ĵ���
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

























