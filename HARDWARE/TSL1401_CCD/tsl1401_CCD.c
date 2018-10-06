#include "TSL1401_CCD.h"

void CCDInitConfiguration(void)
{
     GPIO_InitTypeDef GPIO_InitStructure;
     
     GPIO_InitStructure.GPIO_Pin=SI_Pin;
     GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
     GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
     
     GPIO_Init(SI_Port,&GPIO_InitStructure);
     
     GPIO_InitStructure.GPIO_Pin=CLK_Pin;
     
     GPIO_Init(CLK_Port,&GPIO_InitStructure);
     
     GPIO_InitStructure.GPIO_Pin=AO_Pin;
     GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
     GPIO_Init(AO_Port,&GPIO_InitStructure);
     ADC_Configuration();
}

void ADC_Configuration(void)
{
     ADC_InitTypeDef    ADC_InitStructure;
     
     ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;//ADC2/ADC2工作在独立模式
     ADC_InitStructure.ADC_ScanConvMode=DISABLE;//工作在单通道模式下
     ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;//工作在连续模式下
     ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//转换由软件触发
     ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;//右对齐模式
     ADC_InitStructure.ADC_NbrOfChannel=1;//顺序进行规则转换的 ADC 通道的数目
     ADC_Init(ADC2,&ADC_InitStructure);
     ADC_RegularChannelConfig(ADC2,A0_ADCChannel,1,ADC_SampleTime_239Cycles5);
     ADC_Cmd(ADC2,ENABLE);
     
     ADC_ResetCalibration(ADC2);//重新指定ADC的校准寄存器
     while(ADC_GetResetCalibrationStatus(ADC2));//获取ADC重置校准寄存器的状态

    ADC_StartCalibration(ADC2);//开始指定 ADC 的校准状态 
     while(ADC_GetCalibrationStatus(ADC2));//获取指定 ADC 的校准程序

    ADC_SoftwareStartConvCmd(ADC2,ENABLE);//使能或者失能指定的 ADC 的软件转换启动功能 
}
void StartIntergration(void)
{
     unsigned char i;
     SI_SetVal;
     SamplingDelay();
     CLK_SetVal;
     SamplingDelay();
     SI_ClrVal;
     SamplingDelay();
     CLK_ClrVal;
     for(i=0; i<127; i++)
     {
         SamplingDelay();
         SamplingDelay();
         CLK_SetVal;
         SamplingDelay();
         SamplingDelay();
         CLK_ClrVal;
     }
     SamplingDelay();
     SamplingDelay();
     
     CLK_SetVal;
     SamplingDelay();
     SamplingDelay();
     CLK_ClrVal;
}
void ImageCapture(unsigned char * ImageData) 
{
     unsigned char i;
   extern u8 AtemP ;
     SI_SetVal;
     SamplingDelay();
     CLK_SetVal;
     SamplingDelay();
     SI_ClrVal;
     SamplingDelay();
     for(i=0;i<255;i++)
     {
         SamplingDelay();
     }
     ADC_SoftwareStartConvCmd(ADC2,ENABLE);
     while(!ADC_GetFlagStatus(ADC2,ADC_FLAG_EOC));
     *ImageData=ADC_GetConversionValue(ADC2)>>4;
     ImageData++;
     CLK_ClrVal;
     for(i=0;i<127;i++)
     {
         SamplingDelay();
         SamplingDelay();
         
         CLK_SetVal;
         SamplingDelay();
         SamplingDelay();
         
         ADC_SoftwareStartConvCmd(ADC2,ENABLE);
         while(!ADC_GetFlagStatus(ADC2,ADC_FLAG_EOC));
         *ImageData=ADC_GetConversionValue(ADC2)>>4;
         ImageData++;
         CLK_ClrVal;
     }
     SamplingDelay();
     SamplingDelay();
     CLK_SetVal; 
     SamplingDelay();
     SamplingDelay();
     CLK_ClrVal;
}

void SamplingDelay(void)
{
    volatile uint8_t i ;
    for(i=0;i<1;i++) 
     {
     __NOP();
     __NOP();
     }
    
}
