#ifndef __keyboad_h__
#define __keyboad_h__
#include "stm32f10x.h"
#include "stdint.h"
#include "delay.h"
#include "oled1.h"
//#define val_GPIO GPIO_ReadInputData(GPIOA);
#define GPIO_4_4 GPIOC
/**zzzzzzxxxxxx
 *  >A7
 *	>A6
 *  >A5
 *  >A4
 *  >A3
 *  >A2
 *  >A1
 *  >A0
 *
 */
void Keyspress(void);
void GPIO_keyboard_4_4_init(void);
#endif

