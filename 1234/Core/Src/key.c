#include "key.h"

static volatile uint8_t key_state = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_1 || 
       GPIO_Pin == GPIO_PIN_2 || 
       GPIO_Pin == GPIO_PIN_3)
    {
        key_state = GPIO_Pin;  /* 记录哪个按键被按下 */
    }
}

uint8_t Key_GetState(void)
{
    uint8_t temp = key_state;
    key_state = 0;
    return temp;
}
