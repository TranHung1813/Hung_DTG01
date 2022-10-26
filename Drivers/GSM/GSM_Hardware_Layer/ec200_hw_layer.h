
#include "main.h"
#include "ringbuffer.h"
#include "SEGGER_RTT.h"

#define EC200_MAX_TIMEOUT_WAIT_REPS  50
#define EC200_TIME_TO_CHECK_REPS     10
#define EC200_COUNT_TIME_RETRY_SEND  3
#define E_OK     1
#define E_NOT_OK 0

void EC200_Turn_on_Power(void);
void EC200_Turn_off_Power(void);
uint8_t EC200_CompareByteData( const uint8_t * src, uint16_t len_src, const uint8_t * des, uint16_t len_des);
uint8_t EC200_SendCommand_AT(uint8_t* cmd, uint8_t* Keyword);
uint8_t EC200_WaitResponse(uint8_t* Keyword, uint16_t Timeout);
