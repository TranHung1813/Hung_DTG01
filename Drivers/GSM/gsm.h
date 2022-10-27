#ifndef GSM_H
#define GSM_H

#include "main.h"
#include "ringbuffer.h"
#include "stdbool.h"
#include "string.h"
#include "gsm_utilities.h"

#define EC200_MAX_TIMEOUT_WAIT_REPS  50
#define EC200_TIME_TO_CHECK_REPS     10
#define EC200_COUNT_TIME_RETRY_SEND  3
#define E_OK     1
#define E_NOT_OK 0

typedef enum
{
    GSM_STATE_POWER_ON = 0,
    GSM_STATE_RESET = 1,
    GSM_STATE_CONFIG_DONE,
}Gsm_State_TypDef;
typedef struct 
{
    Gsm_State_TypDef state;
    uint8_t step;

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
    char *cmd;
    char *expect_resp;
    char *expected_response_at_the_end;
    char *expect_error;
    char *expect_error_at_the_end;
    uint32_t Timeout_atc_ms;
    uint32_t Last_time_send_atc_ms;
    uint8_t Retry_Count_atc;
    GSM_atc_Buffer_TypDef Recv_Buffer;
    GSM_Send_at_CallBack_TypDef Send_at_Callback;
} GSM_AT_Command_TypDef;

typedef struct
{
	GSM_AT_Command_TypDef Table[25];
	uint8_t Table_index;
}GSM_ATCommand_Table_TypDef;
typedef struct
{
    GSM_AT_Command_TypDef atc;
} GSM_Hardware_atc_TypDef;

void GMS_Hardware_Init(void);
void GSM_Turn_on_Power(void);
void GSM_SendCommand_AT (char* cmd,
						 char* expect_resp,
						 char* expect_resp_at_the_end,
						 char* expect_error,
						 char* expect_error_at_the_end,
						 uint32_t Timeout, uint8_t RetryCount,
						 GSM_Send_at_CallBack_TypDef Callback);

void GSM_mnr_task(void);
void Polling_GSM_StateMachine (void);
void GSM_Manager_ChangeState(uint8_t state);
void GSM_Hardware_Layer_Run(void);

void GSM_Config_Module (GSM_Response_Event_TypDef event, void *Resp_Buffer);

uint32_t sys_get_tick_ms(void);

#endif // GSM_H
