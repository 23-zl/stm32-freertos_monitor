#ifndef __ADC_TASK_H
#define __ADC_TASK_H

#include "cmsis_os.h"
extern float g_temperature;
void ADC_TaskInit(void);
void ADC_TaskLoop(void);

#endif
