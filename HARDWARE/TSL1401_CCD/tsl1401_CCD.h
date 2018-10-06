#ifndef _TSL1401_CCD_H_
#define _TSL1401_CCD_H_

#include "stm32f10x_gpio.h"
#include "stm32f10x_adc.h"

//可以根据自己的需要修改响应的引脚

#define SI_Pin GPIO_Pin_0
#define SI_Port GPIOC

#define CLK_Pin GPIO_Pin_1
#define CLK_Port GPIOC

#define AO_Pin GPIO_Pin_2
#define AO_Port    GPIOC
#define A0_ADCChannel ADC_Channel_12
#define SI_SetVal   GPIO_SetBits(SI_Port,SI_Pin)
#define SI_ClrVal   GPIO_ResetBits(SI_Port,SI_Pin)
#define CLK_SetVal  GPIO_SetBits(CLK_Port,CLK_Pin)
#define CLK_ClrVal  GPIO_ResetBits(CLK_Port,CLK_Pin)


void CCDInitConfiguration(void);
void StartIntergration(void);
void ADC_Configuration(void);
void ImageCapture(unsigned char * ImageData) ;
void SendImageData(unsigned char * ImageData);
void SamplingDelay(void);
#endif
