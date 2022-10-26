#include "ringbuffer.h"


void RingBuffer_Init(RingBuffer_Types* ringbuffer, int BufferSize)
{
    ringbuffer->BufferSize = BufferSize;
    ringbuffer->Head = 0;
    ringbuffer->Tail = 0;
    ringbuffer->u8Buffer = (uint8_t*)malloc(BufferSize*sizeof(uint8_t));
}

// Day 1 Byte vào RingBuffer
uint8_t RingBuffer_Push(RingBuffer_Types* ringbuffer, uint8_t BytePush)
{
    if((ringbuffer->Head - ringbuffer->Tail == (ringbuffer->BufferSize - 1))
       || (ringbuffer->Tail - ringbuffer->Head == (ringbuffer->BufferSize - 1)))
       {
        return E_NOT_OK; // return E_NOT_OK khi bo nho Full
       }
    ringbuffer->u8Buffer[ringbuffer->Head] = BytePush;
    if(ringbuffer->Head == (ringbuffer->BufferSize - 1))
    {
        ringbuffer->Head = 0;
    }
    else
    {
        ringbuffer->Head += 1;
    }
    return E_OK;
}

// Doc 1 byte tư RingBuffer
uint8_t RingBuffer_Pop(RingBuffer_Types* ringbuffer)
{
    uint8_t BytePush = 0;
    if(ringbuffer->Head == ringbuffer->Tail)
    {
        return BytePush; // Return Null khi bo nho Empty
    }
    BytePush = ringbuffer->u8Buffer[ringbuffer->Tail];
    if(ringbuffer->Tail == (ringbuffer->BufferSize - 1))
    {
        ringbuffer->Tail = 0;
    }
    else
    {
        ringbuffer->Tail += 1;
    }
    return BytePush;
}
// Doc toan bo du lieu trong RingBuffer gán vào return Buffer
void RingBuffer_GetBuffer(GSM_atc_Buffer_TypDef* retBuffer, RingBuffer_Types* ringbuffer)
{
    int Num_Elements = RingBuffer_GetNumberElements(ringbuffer);
    if(Num_Elements == 0)
    {
    	return;
    }
    for(int CountByte = retBuffer->index; CountByte < retBuffer->index + Num_Elements; CountByte ++)
    {
        retBuffer->u8Buffer[CountByte] = RingBuffer_Pop(ringbuffer);
    }
    retBuffer->index += Num_Elements;
}

// Lay tong so byte du lieu trong RingBuffer
int RingBuffer_GetNumberElements(RingBuffer_Types* ringbuffer)
{
    int Num_Element = 0;
    if (ringbuffer->Head >= ringbuffer->Tail)
    {
        Num_Element = ringbuffer->Head - ringbuffer->Tail;
    }
    else
    {
        Num_Element = ringbuffer->BufferSize - ringbuffer->Tail + ringbuffer->Head;
    }
    return Num_Element;
}
// Xoa toan bo RingBuffer
void Erase_RingBuffer(RingBuffer_Types* ringbuffer)
{
    ringbuffer->Head = ringbuffer->Tail;
}
