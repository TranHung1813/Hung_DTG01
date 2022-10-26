
#include "main.h"
#include <stdlib.h>

typedef struct
{
    uint8_t data[100];
    uint16_t index;
}SuperBuffer_t;

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
void RingBuffer_GetBuffer(SuperBuffer_t* retBuffer, RingBuffer_Types* ringbuffer);
int RingBuffer_GetNumberElements(RingBuffer_Types* ringbuffer);
void Erase_RingBuffer(RingBuffer_Types* ringbuffer);
