# include "ec200_data_layer.h"

void EC200_Config_Module (void)
{
    uint8_t Result = E_NOT_OK;
    SEGGER_RTT_WriteString(0,"Start config for Module...\r\n");
    Result = EC200_SendCommand_AT((uint8_t *)"ATE0\r\n", (uint8_t *)"OK\r\n");
    SEGGER_RTT_printf(0,"Disable ECHO %s.\r\n",(Result == E_OK)?"OK":"FAIL");
    HAL_Delay(100);
    Result = EC200_SendCommand_AT((uint8_t *)"AT+CMEE=2\r\n", (uint8_t *)"OK\r\n");
    SEGGER_RTT_printf(0,"Set up ERROR Message Format %s.\r\n",(Result == E_OK)?"OK":"FAIL");
    HAL_Delay(100);
    Result = EC200_SendCommand_AT((uint8_t *)"ATI\r\n", (uint8_t *)"OK\r\n");
    SEGGER_RTT_printf(0,"Get Info Module %s.\r\n",(Result == E_OK)?"OK":"FAIL");
    HAL_Delay(100);
    Result = EC200_SendCommand_AT((uint8_t *)"AT\r\n", (uint8_t *)"OK\r\n");
    SEGGER_RTT_printf(0,"AT Test 1 %s.\r\n",(Result == E_OK)?"OK":"FAIL");
    HAL_Delay(100);
    Result = EC200_SendCommand_AT((uint8_t *)"AT\r\n", (uint8_t *)"OK\r\n");
    SEGGER_RTT_printf(0,"AT Test 2 %s.\r\n",(Result == E_OK)?"OK":"FAIL");
    HAL_Delay(100);
    Result = EC200_SendCommand_AT((uint8_t *)"AT+QCFG=\"urc/ri/smsincoming\",\"pulse\",2000\r\n", (uint8_t *)"OK\r\n");
    SEGGER_RTT_printf(0,"Set URC Ringtype %s.\r\n",(Result == E_OK)?"OK":"FAIL");
    HAL_Delay(100);
    Result = EC200_SendCommand_AT((uint8_t *)"AT+CNMI=2,1,0,0,0\r\n", (uint8_t *)"OK\r\n");
    SEGGER_RTT_printf(0,"Config SMS event report %s.\r\n",(Result == E_OK)?"OK":"FAIL");
    HAL_Delay(100);
    Result = EC200_SendCommand_AT((uint8_t *)"AT+CMGF=1\r\n", (uint8_t *)"OK\r\n");
    SEGGER_RTT_printf(0,"Set SMS Format to Text mode %s.\r\n",(Result == E_OK)?"OK":"FAIL");
    HAL_Delay(100);
    Result = EC200_SendCommand_AT((uint8_t *)"AT\r\n", (uint8_t *)"OK\r\n");
    SEGGER_RTT_printf(0,"AT Test %s.\r\n",(Result == E_OK)?"OK":"FAIL");
    HAL_Delay(100);
    Result = EC200_SendCommand_AT((uint8_t *)"AT+CGSN\r\n", (uint8_t *)"OK\r\n");
    SEGGER_RTT_printf(0,"Get IMEI %s.\r\n",(Result == E_OK)?"OK":"FAIL");
    HAL_Delay(100);
}
