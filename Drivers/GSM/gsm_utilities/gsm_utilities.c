#include "gsm_utilities.h"

void GSM_Utilities_Get_IMEI(uint8_t *recv_Buffer, uint8_t* IMEI_Buffer, uint8_t Max_IMEI_Length)
{
    int IMEI_Index = 0;
    for(int CountByte = 0; CountByte < strlen((char*)recv_Buffer); CountByte++)
    {
        if((recv_Buffer[CountByte] >= '0') && (recv_Buffer[CountByte] <= '9'))
        {
            if(IMEI_Index < Max_IMEI_Length)
            {
                IMEI_Buffer[IMEI_Index++] = recv_Buffer[CountByte];
            }
            else
            {
                IMEI_Buffer[IMEI_Index] = 0;
                break;
            }
        }
    }
    IMEI_Buffer[IMEI_Index] = 0;
}
bool gsm_utilities_get_signal_strength_from_buffer(uint8_t *buffer, uint16_t *csq)
{
    char *tmp_buff = strstr((char *)buffer, "+CSQ:");

    if (tmp_buff == NULL)
    {
        return false;
    }

    *csq = gsm_utilities_get_number_from_string((uint16_t)6, tmp_buff);
    return true;
}
/*
 * 	Ham doc mot so trong chuoi bat dau tu dia chi nao do.
 *	Buffer = abc124mff thi gsm_utilities_get_number_from_string(3,Buffer) = 123
 *
 */
uint16_t gsm_utilities_get_number_from_string(uint16_t begin_index, char *buffer)
{
    // assert(buffer);

	uint16_t value = 0;
    uint16_t tmp = begin_index;
    uint32_t len = strlen(buffer);
    while (buffer[tmp] && tmp < len)
    {
        if (buffer[tmp] >= '0' && buffer[tmp] <= '9')
        {
            value *= 10;
            value += buffer[tmp] - 48;
        }
        else
        {
            break;
        }
        tmp++;
    }

    return value;
}
void DEBUG_PrintResult_ATC(char* cmd, char* result)
{
    // In ket qua: "AT cmd: OK/FAIL " trong debug
    char sub_cmd[64] = "";
    strncpy(sub_cmd, cmd + 0, strlen(cmd) - 2);
    DEBUG_INFO("%s : %s\r\n", sub_cmd, result);
}
