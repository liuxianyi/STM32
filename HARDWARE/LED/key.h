#ifndef __KEY_H__
#define __KEY_H__
#include "stm32f10x.h"
#include "delay.h"
#define u8 unsigned char
#define u16 unsigned int
#define KEY_UP 4
#define KEY_DOWN 2
#define KEY_LEFT 3
#define KEY_RIGHT 1

#define KEY0 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)
#define KEY1 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)
#define KEY2 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)
#define KEY4 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5)
#define KEY3 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)

void keyInit(void);
u8 KEY_Scan(void);
u8 KEY_scan_no_onclick(void);
#endif
