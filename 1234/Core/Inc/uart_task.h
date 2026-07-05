#ifndef __UART_TASK_H
#define __UART_TASK_H

#include "cmsis_os.h"

void USART1_IDLE_Callback(void);
void UART_TaskInit(void);
void UART_TaskLoop(void);

#endif
