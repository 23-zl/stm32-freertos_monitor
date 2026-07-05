#include "adc_task.h"
#include "main.h"
#include "string.h"
#include "stdio.h"

float g_temperature=25.0f;
	
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart1;
volatile uint16_t adc_value = 0;
static volatile uint8_t adc_ready = 0;

/* DMA传输完成回调 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if(hadc->Instance == ADC1)
    {
        adc_ready = 1;
    }
}

/* 初始化函数（在任务开始时调用一次） */
void ADC_TaskInit(void)
{
	// 1. 使能内部温度传感器和VREFINT（关键！）
    ADC1->CR2 |= ADC_CR2_TSVREFE;
	
	
	  ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;   // 通道16
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5; // 必须 ≥ 17.1μs
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&adc_value, 1);
}

/* 循环处理函数（在任务循环中反复调用） */
void ADC_TaskLoop(void)
{
    static uint32_t count = 0;
    if(adc_ready)
    {
			  
			
        adc_ready = 0;
        
        // 每100次打印一次原始ADC值
        if(++count >= 100)
        {
            count = 0;
            char buf[32];
            int len = sprintf(buf, "ADC raw: %d\r\n", adc_value);
            HAL_UART_Transmit(&huart1, (uint8_t*)buf, len, 100);
        }

        // 计算温度
        float voltage = (adc_value * 3.3f) / 4096.0f;
        g_temperature = ((1.43f - voltage) / 0.0043f) + 25.0f;
				
				
				
				// 每 100ms 发送一次 VOFA+ 数据帧
        static uint32_t cnt = 0;
        cnt++;
        if(cnt >= 100)  // 假设任务每 1ms 执行一次，100次=100ms
        {
            cnt = 0;
            uint8_t buf[8];
            float temp = g_temperature;
            memcpy(buf, &temp, 4);          // 浮点数转为4字节小端序
            buf[4] = 0x00; buf[5] = 0x00;   // firewater 帧尾
            buf[6] = 0x80; buf[7] = 0x7F;
            HAL_UART_Transmit_DMA(&huart1, buf, 8);
        }
    }
}
