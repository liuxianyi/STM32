#ifndef _IIC_H
#define _IIC_H
#include "stm32f10x.h"
#define SCL_H         GPIOE->BSRR = GPIO_Pin_2
#define SCL_L         GPIOE->BRR  = GPIO_Pin_2
   
#define SDA_H         GPIOE->BSRR = GPIO_Pin_3
#define SDA_L         GPIOE->BRR  = GPIO_Pin_3

#define SCL_read      GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)
#define SDA_read      GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)

typedef struct
{
    uint16_t Red;
    uint16_t Green;
    uint16_t Blue;
    uint16_t Clear;
} RGBC;
typedef struct
{
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
} RGB;

void I2C_GPIO_Config(void);
void I2C_Stop(void);
u8 Single_WriteI2C_byte(u8 Slave_Address,u8 REG_Address,u8 data);
u8 Single_ReadI2C(u8 Slave_Address,u8 REG_Address,u8 *REG_data,u8 length);
#endif
