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

void SEGGER_RTT_PrintBuffer(uint8_t* Buffer, int Buffer_len)
{
    for(int Count = 0; Count < Buffer_len; Count++)
    {
        SEGGER_RTT_printf(0,"%c",(char)Buffer[Count]);
    }
    SEGGER_RTT_printf(0,"\r\n");
}
void SEGGER_RTT_PrintResult_ATC(char* cmd, char* result)
{
    // In ket qua: "AT cmd: OK/FAIL " trong debug
    char sub_cmd[64] = "";
    strncpy(sub_cmd, cmd + 0, strlen(cmd) - 2);
    SEGGER_RTT_printf(0,"%s : %s\r\n", sub_cmd, result);
}
