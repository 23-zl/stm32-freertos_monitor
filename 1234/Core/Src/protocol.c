#include "protocol.h"
#include "crc16.h"
#include "main.h"
extern UART_HandleTypeDef huart1;

int8_t Protocol_Parse(uint8_t *buf, uint16_t len)
{
    Frame_TypeDef *frame = (Frame_TypeDef *)buf;
    uint16_t crc_calc;
    
    if(frame->header != FRAME_HEADER || frame->tail != FRAME_TAIL)
        return -1;
    
    if(frame->data_len > 32)
        return -2;
    
    crc_calc = CRC16_Calculate((uint8_t *)frame, sizeof(Frame_TypeDef) - 3);
    if(crc_calc != frame->crc)
        return -3;
    
    return 0;
}

void Protocol_SendResponse(uint8_t cmd, uint8_t *data, uint8_t len)
{
    Frame_TypeDef tx_frame;
    
    tx_frame.header = FRAME_HEADER;
    tx_frame.command = cmd;
    tx_frame.data_len = len;
    
    if(len <= 32)
    {
        for(uint8_t i = 0; i < len; i++)
            tx_frame.data[i] = data[i];
    }
    
    tx_frame.crc = CRC16_Calculate((uint8_t *)&tx_frame, sizeof(Frame_TypeDef) - 3);
    tx_frame.tail = FRAME_TAIL;
    
    HAL_UART_Transmit(&huart1, (uint8_t *)&tx_frame, sizeof(Frame_TypeDef), 100);
}
