#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include "main.h"

#define FRAME_HEADER    0xA5
#define FRAME_TAIL      0x5A
#define CMD_SET_MODE    0x01
#define CMD_SET_PARAM   0x02
#define CMD_QUERY_DATA  0x03
#define CMD_RESPONSE    0x81

#pragma pack(1)
typedef struct {
    uint8_t  header;
    uint8_t  command;
    uint8_t  data_len;
    uint8_t  data[32];
    uint16_t crc;
    uint8_t  tail;
} Frame_TypeDef;
#pragma pack()

int8_t Protocol_Parse(uint8_t *buf, uint16_t len);
void Protocol_SendResponse(uint8_t cmd, uint8_t *data, uint8_t len);

#endif
