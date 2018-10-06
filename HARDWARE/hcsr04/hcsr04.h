#ifndef __HCSR04_H
#define __HCSR04_H
#include "stm32f10x.h"

#define HCSR04_PORT     GPIOB
#define HCSR04_CLK      RCC_APB2Periph_GPIOB
#define HCSR04_TRIG     GPIO_Pin_5
#define HCSR04_ECHO     GPIO_Pin_6
#define TRIG_Send  PBout(5) 
#define ECHO_Reci  PBin(6)


void Hcsr04Init();
static void OpenTimerForHc();
static void CloseTimerForHc();
void hcsr04_NVIC();
u32 GetEchoTimer();
float Hcsr04GetLength(void );
void Delay_Ms(u16 time);
void Delay_Us(u16 time);
#endif