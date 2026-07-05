#include "uart_task.h"
#include "main.h"
#include "protocol.h"

#define RX_BUF_SIZE  256

extern UART_HandleTypeDef huart1;

static uint8_t rx_buf[RX_BUF_SIZE];
static volatile uint16_t rx_len = 0;
static volatile uint8_t rx_done = 0;

/* 空闲中断回调（由 stm32f1xx_it.c 调用） */
void USART1_IDLE_Callback(void)
{
    HAL_UART_DMAStop(&huart1);
    rx_len = RX_BUF_SIZE - __HAL_DMA_GET_COUNTER(huart1.hdmarx);
    rx_done = 1;
    HAL_UART_Receive_DMA(&huart1, rx_buf, RX_BUF_SIZE);
}

/* 初始化函数 */
void UART_TaskInit(void)
{
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
    HAL_UART_Receive_DMA(&huart1, rx_buf, RX_BUF_SIZE);
}

/* 循环处理函数 */
void UART_TaskLoop(void)
{
    if(rx_done)
    {
        rx_done = 0;
        Protocol_Parse(rx_buf, rx_len);
    }
}
