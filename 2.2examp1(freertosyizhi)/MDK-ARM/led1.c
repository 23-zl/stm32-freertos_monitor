#include "led1.h"
#include "main.h"



static uint32_t state=0;

void LED1_Init(void);
{
}

void LED1_On(void);
{
	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
	state = 1;
}

void LED1_OFF(void);
{
	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
	state = 0;
}

void LED1_Toggle(void)
{
	if(state == 0)
	{
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
		state=1;
	}
	else
	{
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
		state=0;
	}
}