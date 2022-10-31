#ifndef GSM_UTILITIES_H
#define GSM_UTILITIES_H

#include "stdint.h"
#include "string.h"
#include "app_debug.h"

/*!
 * @brief               Get gsm imei from buffer
 * @param[in]           recv_Buffer raw receive buffer from gsm module
 * @param[out]          IMEI_Buffer gen IMEI to output
 * @param[in]           Max_IMEI_Length Max result length
 * @note                Maximum imei length is 15
 */ 

void GSM_Utilities_Get_IMEI(uint8_t *recv_Buffer, uint8_t* IMEI_Buffer, uint8_t Max_IMEI_Length);

void DEBUG_PrintBuffer(uint8_t* Buffer, int Buffer_len);
void DEBUG_PrintResult_ATC(char* cmd, char* result);

#endif // GSM_UTILITIES_H
