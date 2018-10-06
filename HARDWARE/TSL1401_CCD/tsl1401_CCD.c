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
     
     ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;//ADC2/ADC2�����ڶ���ģʽ
     ADC_InitStructure.ADC_ScanConvMode=DISABLE;//�����ڵ�ͨ��ģʽ��
     ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;//����������ģʽ��
     ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//ת�����������
     ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;//�Ҷ���ģʽ
     ADC_InitStructure.ADC_NbrOfChannel=1;//˳����й���ת���� ADC ͨ������Ŀ
     ADC_Init(ADC2,&ADC_InitStructure);
     ADC_RegularChannelConfig(ADC2,A0_ADCChannel,1,ADC_SampleTime_239Cycles5);
     ADC_Cmd(ADC2,ENABLE);
     
     ADC_ResetCalibration(ADC2);//����ָ��ADC��У׼�Ĵ���
     while(ADC_GetResetCalibrationStatus(ADC2));//��ȡADC����У׼�Ĵ�����״̬

    ADC_StartCalibration(ADC2);//��ʼָ�� ADC ��У׼״̬ 
     while(ADC_GetCalibrationStatus(ADC2));//��ȡָ�� ADC ��У׼����

    ADC_SoftwareStartConvCmd(ADC2,ENABLE);//ʹ�ܻ���ʧ��ָ���� ADC �����ת���������� 
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
