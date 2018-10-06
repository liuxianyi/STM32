#include "led.h"
#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	
/***********************************
 * 描述：io口置高 实现B口的操作
 * 参数：GPIO_TypeDef* GPIOx 端口
 *          value:[GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG]            
 *			 GPIOMode_TypeDef GPIO_Mode_X 模式
 *   				value：[GPIO_Mode_AIN ,GPIO_Mode_IN_FLOATING = 0x04, GPIO_Mode_IPD = 0x28,  GPIO_Mode_IPU = 0x48,
 *          				GPIO_Mode_Out_OD = 0x14, GPIO_Mode_Out_PP = 0x10, GPIO_Mode_AF_OD = 0x1C, GPIO_Mode_AF_PP]
 *       GPIOSpeed_TypeDef GPIO_Speed_XMHZ IO口速率 
 *   				value: [GPIO_Speed_10MHz ,GPIO_Speed_2MHz, GPIO_Speed_50MHz]
 *       uint16_t GPIO_Pin口号 
 *   				value:[GPIO_Pin_0-15，GPIO_Pin_ALL]
 *       uint16_t RCC_APB2Periph时钟
 *  				value:[RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB, RCC_APB2Periph_GPIOC, RCC_APB2Periph_GPIOD,
 *  							RCC_APB2Periph_GPIOE, RCC_APB2Periph_GPIOF, RCC_APB2Periph_GPIOG]
 * 返回值：void
 ***********************************/
 void LED_INIT_ALL(GPIO_TypeDef* GPIOx, GPIOMode_TypeDef GPIO_Mode_X, GPIOSpeed_TypeDef GPIO_Speed_XMHZ, uint16_t GPIO_Pin, uint16_t RCC_APB2Periph){
	GPIO_InitTypeDef  GPIO_InitStructure;//
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);	 //使能PB端口时钟
	//开启时钟，使用或来同时开启
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin;				 //LED0-->PB.5 端口配置
	 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_X; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_XMHZ;		 //IO口速度为50MHz
	 
  GPIO_Init(GPIOx, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
  //GPIO_SetBits(GPIOx,GPIO_Pin);						 //PB.5 输出高

  //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;		 //LED1-->PE.5 端口配置, 推挽输出
}	
 
void pinSetHigh(GPIO_TypeDef* GPIOx, GPIOMode_TypeDef GPIO_Mode_X, GPIOSpeed_TypeDef GPIO_Speed_XMHZ, uint16_t GPIO_Pin, uint16_t RCC_APB2Periph){
	GPIO_InitTypeDef  GPIO_InitStructure;//
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);	 //使能PB端口时钟
	//开启时钟，使用或来同时开启
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin;				 //LED0-->PB.5 端口配置
	 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_X; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_XMHZ;		 //IO口速度为50MHz
	 
  GPIO_Init(GPIOx, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
  GPIO_SetBits(GPIOx,GPIO_Pin);						 //PB.5 输出高

  //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;		 //LED1-->PE.5 端口配置, 推挽输出
	 

}	
/***********************************
 * 描述：io口置低 实现B口的操作
 * 参数：GPIO_TypeDef* GPIOx  端口
 *          value:[GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG]            
 *			 GPIOMode_TypeDef GPIO_Mode_X  模式
 *   				value：[GPIO_Mode_AIN ,GPIO_Mode_IN_FLOATING, GPIO_Mode_IPD,  GPIO_Mode_IPU,
 *          				GPIO_Mode_Out_OD, GPIO_Mode_Out_PP, GPIO_Mode_AF_OD, GPIO_Mode_AF_PP]
 *       GPIOSpeed_TypeDef GPIO_Speed_XMHZ IO口速率 
 *   				value: [GPIO_Speed_10MHz ,GPIO_Speed_2MHz, GPIO_Speed_50MHz]
 *       uint16_t GPIO_Pin 口号 
 *   				value:[GPIO_Pin_0-15，GPIO_Pin_ALL]
 *       uint16_t RCC_APB2Periph 时钟
 *  				value:[RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB, RCC_APB2Periph_GPIOC, RCC_APB2Periph_GPIOD,
 *  							RCC_APB2Periph_GPIOE, RCC_APB2Periph_GPIOF, RCC_APB2Periph_GPIOG]
 * 返回值：void
 ***********************************/
void pinSetlow(GPIO_TypeDef* GPIOx, GPIOMode_TypeDef GPIO_Mode_X, GPIOSpeed_TypeDef GPIO_Speed_XMHZ, uint16_t GPIO_Pin, uint16_t RCC_APB2Periph){
	GPIO_InitTypeDef  GPIO_InitStructure;//
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);	 //使能PB端口时钟
	//开启时钟，使用或来同时开启
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin;				 //LED0-->PB.5 端口配置
	 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_X; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_XMHZ;		 //IO口速度为50MHz
	 
  GPIO_Init(GPIOx, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
  GPIO_ResetBits(GPIOx,GPIO_Pin);
	
}


/**
 *描述：io口初始化  推挽输出 IO口速度为50MHz
 *参数：GPIO_TypeDef* GPIOx  端口
 *          value:[GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG]
 *      uint16_t GPIO_Pin 口号 
 *   				value:[GPIO_Pin_0-15，GPIO_Pin_ALL]
 *      uint16_t RCC_APB2Periph 时钟
 *  				value:[RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB, RCC_APB2Periph_GPIOC, RCC_APB2Periph_GPIOD,
 *  							RCC_APB2Periph_GPIOE, RCC_APB2Periph_GPIOF, RCC_APB2Periph_GPIOG]
 *返回值：无
 */
void ledInit(uint16_t RCC_APB2Periph, uint16_t GPIO_Pin, GPIO_TypeDef* GPIOx){
	GPIO_InitTypeDef  GPIO_InitStructure;//
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);	 //使能PB,PE端口时钟
	//开启时钟，使用或来同时开启
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin;				 
	 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 
  GPIO_Init(GPIOx, &GPIO_InitStructure);					 
  
}

/**
 *参数：GPIO_TypeDef* GPIOx  端口
 *          value:[GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG]
 *      uint16_t GPIO_Pin 口号 
 *   				value:[GPIO_Pin_0-15，GPIO_Pin_ALL]
 * 
 */
void pinSetHigh_ONE(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	GPIO_SetBits(GPIOx,GPIO_Pin);
}
/**
 *参数：GPIO_TypeDef* GPIOx  端口
 *          value:[GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG]
 *      uint16_t GPIO_Pin 口号 
 *   				value:[GPIO_Pin_0-15，GPIO_Pin_ALL]
 * 
 */
void pinSetlow_ONE(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	
	GPIO_ResetBits(GPIOx,GPIO_Pin);
}

void LED_Init_PD_2(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); //使能PD 端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				     //LED-->PD.2 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);					       //根据设定参数初始化GPIOD.2
 GPIO_SetBits(GPIOD,GPIO_Pin_2);						           //PD.2 输出高，不亮灯
	
}

void IO_path(void){//红外循迹
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE); //使能PG 端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				     //LED-->PG.1 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //浮空输入
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOG, &GPIO_InitStructure);					       //根据设定参数初始化
	
}
uint8_t readIOPath(void){
	
	return GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_1);
	
}

void setPBout(u8 sta)
{
	//LED0=sta;
}
void setPEout(u8 sta)
{
	//LED1=sta;
}