#ifndef __WATCHDOG_TASK_H
#define __WATCHDOG_TASK_H

#include "cmsis_os.h"

void Watchdog_TaskInit(void);
void Watchdog_TaskLoop(void);

#endif

