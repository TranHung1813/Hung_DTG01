#ifndef GSM_H
#define GSM_H

#include "main.h"
#include "ringbuffer.h"
#include "stdbool.h"
#include "string.h"
#include "app_debug.h"
#include "gsm_utilities.h"
#include "sio.h"
#include "timeouts.h"
#include "ppp.h"
#include "pppos.h"
#include "dns.h"
#include "lwip/init.h"
#include "stdint.h"
#include "sntp.h"


#define E_OK     1
#define E_NOT_OK 0
#define MAX_ATC_TABLE_ROW  25

#define GSM_ATC_BUFFER_SIZE                   1024   // AT command buffer size
#define GSM_PPP_MODEM_BUFFER_SIZE             1024  // PPP buffer size

extern UART_HandleTypeDef huart1;
#define GSM_UART_TX( DataSend, length, Timeout)    HAL_UART_Transmit(&huart1, DataSend, length, Timeout)

typedef enum
{
    GSM_STATE_POWER_ON = 0,
    GSM_STATE_RESET = 1,
    GSM_STATE_OK,
    GSM_STATE_REOPEN_PPP,

}Gsm_State_TypDef;

typedef enum
{
    GSM_INTERNET_MODE_AT_STACK,
    GSM_INTERNET_MODE_PPP_STACK,
} gsm_internet_mode_t;

typedef struct 
{
    Gsm_State_TypDef state;
    uint8_t step;
    gsm_internet_mode_t mode;
    uint8_t ppp_phase; // @ref lwip ppp.h

}Gsm_Manager_TypDef;
typedef enum
{
    GSM_EVENT_OK = 0,  // GSM response ok
    GSM_EVENT_TIMEOUT, // Timeout is over
    GSM_EVENT_ERROR,   // GSM response wrong value
} GSM_Response_Event_TypDef;

typedef void (*GSM_Send_at_CallBack_TypDef)(GSM_Response_Event_TypDef event, void *response_buffer);

typedef struct
{
    uint8_t u8Buffer[GSM_ATC_BUFFER_SIZE];
    uint16_t index;
} GSM_ATC_Buffer_TypDef;

typedef struct
{
    uint16_t idx_in;
    uint16_t idx_out;
    uint8_t u8Buffer[GSM_PPP_MODEM_BUFFER_SIZE];
} GSM_Modem_Buffer_TypDef;

typedef struct
{
    char *cmd;
    char *expect_resp;
    char *expected_response_at_the_end;
    char *expect_error;
    char *expect_error_at_the_end;
    uint32_t Timeout_atc_ms;
    uint32_t Last_time_send_atc_ms;
    uint8_t Retry_Count_atc;
    GSM_ATC_Buffer_TypDef Recv_Buffer;
    GSM_Send_at_CallBack_TypDef Send_at_Callback;
} GSM_AT_Command_TypDef;

typedef struct
{
    char *cmd;
    char *expect_resp;
    char *expected_response_at_the_end;
    char *expect_error;
    char *expect_error_at_the_end;
    uint32_t Timeout_atc_ms;
    uint8_t Retry_Count_atc;
    GSM_Send_at_CallBack_TypDef Send_at_Callback;
} GSM_ATCommand_Table_TypDef;

typedef struct
{
    GSM_AT_Command_TypDef atc;
} GSM_Hardware_atc_TypDef;

/* The PPP control block */

void GMS_Hardware_Init(void);
void GSM_Turn_on_Power(void);
void GSM_SendCommand_AT (GSM_ATCommand_Table_TypDef AT_Cmd);
void GSM_GET_IMEI_Buffer(GSM_Response_Event_TypDef event, void *Resp_Buffer);
void GSM_GET_Signal_Strength(GSM_Response_Event_TypDef event, void *Resp_Buffer);

void GSM_mnr_task(void);
void Polling_GSM_StateMachine (void);
void GSM_Hardware_pppos_Polling(void);
void GSM_Manager_ChangeState(Gsm_State_TypDef state);
void GSM_Manager_ChangeInternetMode(gsm_internet_mode_t mode);
void GSM_Hardware_Layer_Run(void);

void GSM_Config_Module (GSM_Response_Event_TypDef event, void *Resp_Buffer);
void GSM_HwLayer_Reset_Rx_Buffer(void);
void GSM_HwLayer_Fill_Rx_Buffer(uint8_t* data, uint32_t length);

uint32_t GSM_Hardware_layer_Copy_ppp_Buffer(uint8_t* data, uint32_t length);
uint32_t sio_read(sio_fd_t fd, u8_t *data, u32_t len);
void *gsm_data_layer_get_ppp_control_block(void);

bool gsm_is_in_ppp_mode(void);
bool gsm_data_layer_is_ppp_connected(void);


#endif // GSM_H
