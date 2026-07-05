#ifndef __DISPLAY_TASK_H
#define __DISPLAY_TASK_H

#include "cmsis_os.h"
extern volatile uint16_t adc_value;
extern float g_temperature;
void Display_TaskInit(void);
void Display_TaskLoop(void);

#endif

