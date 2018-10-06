#ifndef __led_H__
#define __led_H__
#include "stm32f10x.h"
#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5
//#define led PDout(2)// PD.2
void pinSetHigh(GPIO_TypeDef* GPIOx, GPIOMode_TypeDef GPIO_Mode_X, GPIOSpeed_TypeDef GPIO_Speed_XMHZ, uint16_t GPIO_Pin, uint16_t RCC_APB2Periph);
void pinSetlow(GPIO_TypeDef* GPIOx, GPIOMode_TypeDef GPIO_Mode_X, GPIOSpeed_TypeDef GPIO_Speed_XMHZ, uint16_t GPIO_Pin, uint16_t RCC_APB2Periph);
void ledInit(uint16_t RCC_APB2Periph, uint16_t GPIO_Pin, GPIO_TypeDef* GPIOx);
void LED_INIT_ALL(GPIO_TypeDef* GPIOx, GPIOMode_TypeDef GPIO_Mode_X, GPIOSpeed_TypeDef GPIO_Speed_XMHZ, uint16_t GPIO_Pin, uint16_t RCC_APB2Periph);
void pinSetHigh_ONE(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void pinSetlow_ONE(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
//void LED_Init_PD_2(void);//初始化PD.2
void IO_path(void);//红外循迹初始化
uint8_t readIOPath(void);
#endif
