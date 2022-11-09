#ifndef GSM_UTILITIES_H
#define GSM_UTILITIES_H

#include "stdint.h"
#include "string.h"
#include "app_debug.h"
#include "stdbool.h"

/*!
 * @brief               Get gsm imei from buffer
 * @param[in]           recv_Buffer raw receive buffer from gsm module
 * @param[out]          IMEI_Buffer gen IMEI to output
 * @param[in]           Max_IMEI_Length Max result length
 * @note                Maximum imei length is 15
 */ 

void GSM_Utilities_Get_IMEI(uint8_t *recv_Buffer, uint8_t* IMEI_Buffer, uint8_t Max_IMEI_Length);
bool gsm_utilities_get_signal_strength_from_buffer(uint8_t *buffer, uint16_t *csq);
uint16_t gsm_utilities_get_number_from_string(uint16_t begin_index, char *buffer);
bool gsm_utilities_is_file_exist(char* FileName, char *buffer);

void DEBUG_PrintResult_ATC(char* cmd, char* result);

#endif // GSM_UTILITIES_H
