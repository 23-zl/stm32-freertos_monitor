#ifndef __OLED_H
#define __OLED_H

#include "main.h"

void OLED_Init(I2C_HandleTypeDef *hi2c);
void OLED_Clear(void);
void OLED_ShowString(uint8_t x, uint8_t y, char *str, uint8_t size);
void OLED_Refresh(void);

#endif
