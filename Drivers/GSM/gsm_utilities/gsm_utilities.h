#ifndef GSM_UTILITIES_H
#define GSM_UTILITIES_H

#include "stdint.h"
#include "string.h"
#include "SEGGER_RTT.h"

/*!
 * @brief               Get gsm imei from buffer
 * @param[in]           recv_Buffer raw receive buffer from gsm module
 * @param[out]          IMEI_Buffer gen IMEI to output
 * @param[in]           Max_IMEI_Length Max result length
 * @note                Maximum imei length is 15
 */ 

void GSM_Utilities_Get_IMEI(uint8_t *recv_Buffer, uint8_t* IMEI_Buffer, uint8_t Max_IMEI_Length);

void SEGGER_RTT_PrintBuffer(uint8_t* Buffer, int Buffer_len);

#endif // GSM_UTILITIES_H
