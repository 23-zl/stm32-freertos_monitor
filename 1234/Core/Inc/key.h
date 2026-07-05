#ifndef __KEY_H
#define __KEY_H

#include "main.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
uint8_t Key_GetState(void);

#endif
