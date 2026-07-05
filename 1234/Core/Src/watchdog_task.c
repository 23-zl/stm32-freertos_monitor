#include "watchdog_task.h"
#include "main.h"

extern IWDG_HandleTypeDef hiwdg;

/* 初始化函数 */
void Watchdog_TaskInit(void)
{
    // 看门狗初始化已在 CubeMX 中完成，这里可直接喂狗
}

/* 循环喂狗函数 */
void Watchdog_TaskLoop(void)
{
    HAL_IWDG_Refresh(&hiwdg);
}

