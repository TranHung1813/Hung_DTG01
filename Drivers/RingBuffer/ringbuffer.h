#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "main.h"
#include <stdlib.h>
//#include "gsm.h"

#define GSM_ATC_BUFFER_SIZE             256   // AT command buffer size


typedef struct
{
    uint8_t u8Buffer[GSM_ATC_BUFFER_SIZE];
    uint16_t index;
} GSM_atc_Buffer_TypDef;

typedef struct 
{
    int BufferSize;
    int Head;
    int Tail;
    uint8_t *u8Buffer;
}RingBuffer_Types;

#define E_OK     1
#define E_NOT_OK 0

void RingBuffer_Init(RingBuffer_Types* ringbuffer, int BufferSize);
uint8_t RingBuffer_Push(RingBuffer_Types* ringbuffer, uint8_t BytePush);
uint8_t RingBuffer_Pop(RingBuffer_Types* ringbuffer);
void RingBuffer_GetBuffer(GSM_atc_Buffer_TypDef* retBuffer, RingBuffer_Types* ringbuffer);
int RingBuffer_GetNumberElements(RingBuffer_Types* ringbuffer);
void Erase_RingBuffer(RingBuffer_Types* ringbuffer);


#endif // RINGBUFFER_H
