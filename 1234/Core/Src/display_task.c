#include "display_task.h"
#include "oled.h"
#include "main.h"
#include "adc_task.h"
#include <stdio.h>

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;

static void Display_Update(void)
{
    
}

/* 初始化函数 */
void Display_TaskInit(void)
{
	
    OLED_Init(&hi2c1);
}

/* 循环刷新函数 */
void Display_TaskLoop(void)
{
	
	Display_Update();
	osDelay(100);
	
    char line1[20], line2[20];
	  
	  OLED_Refresh();
	  

    // 第一行：温度
    sprintf(line1, "Temp: %.1f C", g_temperature);
    OLED_ShowString(0, 0, line1, 16);

    // 第二行：ADC原始值
    sprintf(line2, "ADC: %d", adc_value);
    OLED_ShowString(0, 16, line2, 16);   // y=2 即第16像素行

    OLED_Refresh();
}


