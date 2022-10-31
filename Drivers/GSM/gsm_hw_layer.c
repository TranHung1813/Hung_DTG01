#include "gsm.h"

#define EC200_SEND(huart,DataSend,length)  HAL_UART_Transmit(huart,DataSend,length,200)

extern UART_HandleTypeDef huart1;
RingBuffer_Types Rx_Buffer;

uint32_t Current_Response_len;
uint32_t Current_Response_len_error_handle;
uint32_t Expect_len_compare;
uint32_t Expect_len_compare_error_handle;
uint8_t *p_compare_end_str;
uint8_t *p_compare_end_str_error_handle;

static GSM_Hardware_atc_TypDef m_gsm_atc;

void GMS_Hardware_Init(void)
{
	//Init SEGGER RTT Debug
	SEGGER_RTT_Init();
	// Cap phat bo nho cho RxRingBuffer
	RingBuffer_Init(&Rx_Buffer, 100);
	// Set default GMS State to GMS_STATE_RESET
	GSM_Manager_ChangeState(GSM_STATE_RESET);
}
void GSM_Hardware_Layer_Run(void)
{
	static uint32_t LastTick = 0;
	uint32_t Current_Tick = sys_get_tick_ms();

	if(Current_Tick - LastTick < (uint32_t)5)
	{
		return;
	}
	uint32_t diff = sys_get_tick_ms() - m_gsm_atc.atc.Last_time_send_atc_ms;
	if(m_gsm_atc.atc.Timeout_atc_ms && diff >= m_gsm_atc.atc.Timeout_atc_ms)
	{
		if(--m_gsm_atc.atc.Retry_Count_atc <= 0)
		{
			m_gsm_atc.atc.Timeout_atc_ms = 0;
			if(m_gsm_atc.atc.Send_at_Callback != NULL)
			{
				m_gsm_atc.atc.Send_at_Callback(GSM_EVENT_TIMEOUT,NULL);
			}
			memset(&m_gsm_atc.atc.Recv_Buffer, 0, sizeof(m_gsm_atc.atc.Recv_Buffer));
		}
		else
		{
			DEBUG_INFO("Retry send ATC %d.\r\n",m_gsm_atc.atc.Retry_Count_atc);
			m_gsm_atc.atc.Last_time_send_atc_ms = sys_get_tick_ms();
			memset(&m_gsm_atc.atc.Recv_Buffer, 0, sizeof(m_gsm_atc.atc.Recv_Buffer));
			HAL_UART_Transmit(&huart1, (uint8_t*) m_gsm_atc.atc.cmd, strlen(m_gsm_atc.atc.cmd), 200);
		}
	}
	RingBuffer_GetBuffer(&m_gsm_atc.atc.Recv_Buffer,&Rx_Buffer);
	if(strlen(m_gsm_atc.atc.expect_resp) && strstr((char*)m_gsm_atc.atc.Recv_Buffer.u8Buffer, m_gsm_atc.atc.expect_resp))
	{
		bool do_callback = true;
		if(m_gsm_atc.atc.expected_response_at_the_end && strlen(m_gsm_atc.atc.expected_response_at_the_end))
		{
			Expect_len_compare = strlen(m_gsm_atc.atc.expected_response_at_the_end);
			Current_Response_len = strlen((char*)m_gsm_atc.atc.Recv_Buffer.u8Buffer);
			if(Expect_len_compare < Current_Response_len)
			{
				p_compare_end_str = &m_gsm_atc.atc.Recv_Buffer.u8Buffer[Current_Response_len - Expect_len_compare];
				if(memcmp(p_compare_end_str,m_gsm_atc.atc.expected_response_at_the_end,Expect_len_compare) == 0)
				{
					// Compare thành công đuôi Response
					do_callback = true;
				}
				else
				{
					do_callback = false;
				}
			}
			else
			{
				do_callback = false;
			}
		}
		if(do_callback == true)
		{
			m_gsm_atc.atc.Timeout_atc_ms = 0;
			m_gsm_atc.atc.Retry_Count_atc = 0;
			m_gsm_atc.atc.Send_at_Callback(GSM_EVENT_OK,m_gsm_atc.atc.Recv_Buffer.u8Buffer);
			memset(&m_gsm_atc.atc.Recv_Buffer, 0, sizeof(m_gsm_atc.atc.Recv_Buffer));
		}

	}
	else if(strlen(m_gsm_atc.atc.expect_error) && strstr((char*)m_gsm_atc.atc.Recv_Buffer.u8Buffer, m_gsm_atc.atc.expect_error))
	{
		bool do_callback = true;
		if(m_gsm_atc.atc.expect_error_at_the_end && strlen(m_gsm_atc.atc.expect_error_at_the_end))
		{
			Expect_len_compare_error_handle = strlen(m_gsm_atc.atc.expect_error_at_the_end);
			Current_Response_len_error_handle = strlen((char*)m_gsm_atc.atc.Recv_Buffer.u8Buffer);
			if(Expect_len_compare_error_handle < Current_Response_len_error_handle)
			{
				p_compare_end_str_error_handle = &m_gsm_atc.atc.Recv_Buffer.u8Buffer[Current_Response_len_error_handle - Expect_len_compare_error_handle];
				if(memcmp(p_compare_end_str_error_handle,m_gsm_atc.atc.expect_error_at_the_end,Expect_len_compare_error_handle))
				{
					// Compare thành công đuôi Response (trường hợp Response Error)
					do_callback = true;
				}
				else
				{
					do_callback = false;
				}
			}
			else
			{
				do_callback = false;
			}
		}
		if(do_callback == true)
		{
			m_gsm_atc.atc.Last_time_send_atc_ms = 0;
			m_gsm_atc.atc.Timeout_atc_ms = 0;
			m_gsm_atc.atc.Retry_Count_atc = 0;
			m_gsm_atc.atc.Send_at_Callback(GSM_EVENT_ERROR,m_gsm_atc.atc.Recv_Buffer.u8Buffer);
			memset(&m_gsm_atc.atc.Recv_Buffer, 0, sizeof(m_gsm_atc.atc.Recv_Buffer));
		}
	}
	LastTick = sys_get_tick_ms();
}
void GSM_Turn_on_Power(void)
{
	static uint8_t step;
	DEBUG_INFO("GSM Hard reset step %d.\r\n", step);
	switch (step)
	{
		case 0:
			HAL_GPIO_WritePin(EN_GSM_GPIO_Port,EN_GSM_Pin,0);
			HAL_GPIO_WritePin(GSM_RESET_GPIO_Port,GSM_RESET_Pin,1);
			HAL_GPIO_WritePin(GSM_PWKEY_GPIO_Port,GSM_PWKEY_Pin,0);
			step++;
			break;
		case 1:
			HAL_GPIO_WritePin(GSM_RESET_GPIO_Port,GSM_RESET_Pin,0);
			DEBUG_INFO("GSM turn on Power!\r\n");
			HAL_GPIO_WritePin(EN_GSM_GPIO_Port,EN_GSM_Pin,1);
			// Enable nguon 4.2V
			HAL_GPIO_WritePin(GSM_EN_GPIO_Port,GSM_EN_Pin,1);
			step++;
			break;
		case 2:
			step++;
			break;
		case 3: 
			/* Generate pulse from (1-0-1) |_| to Power On module */
			DEBUG_INFO("Pulse power key.\r\n");
			HAL_GPIO_WritePin(GSM_PWKEY_GPIO_Port,GSM_PWKEY_Pin,1);
			step++;
			break;
		case 4:
			HAL_GPIO_WritePin(GSM_PWKEY_GPIO_Port,GSM_PWKEY_Pin,0);
			HAL_GPIO_WritePin(GSM_RESET_GPIO_Port,GSM_RESET_Pin,0);
			step++;
			break;
		case 5:
		case 6:
			step++;
			break;
		case 7:
			step = 0;
			DEBUG_INFO("GSM Hard reset DONE.\r\n");
			GSM_Manager_ChangeState(GSM_STATE_POWER_ON); // GSM turn on Power Finish-> active GSM by AT Cmd
			break;
		default:
		break;
	}
}
void GSM_SendCommand_AT (GSM_ATCommand_Table_TypDef AT_Cmd)
{
	if(AT_Cmd.Timeout_atc_ms == 0 || AT_Cmd.Send_at_Callback == NULL)
	{
		memset(&m_gsm_atc.atc.Recv_Buffer, 0, sizeof(m_gsm_atc.atc.Recv_Buffer));
		HAL_UART_Transmit(&huart1, (uint8_t *)AT_Cmd.cmd, strlen(AT_Cmd.cmd), 200);
		return;
	}
	if(strlen(AT_Cmd.cmd) < 64)
	{

	}
	m_gsm_atc.atc.cmd = AT_Cmd.cmd;
	m_gsm_atc.atc.expect_resp = AT_Cmd.expect_resp;
	m_gsm_atc.atc.expected_response_at_the_end = AT_Cmd.expected_response_at_the_end;
	m_gsm_atc.atc.expect_error = AT_Cmd.expect_error;
	m_gsm_atc.atc.expect_error_at_the_end = AT_Cmd.expect_error_at_the_end;
	m_gsm_atc.atc.Timeout_atc_ms = AT_Cmd.Timeout_atc_ms;
	m_gsm_atc.atc.Last_time_send_atc_ms = sys_get_tick_ms();
	m_gsm_atc.atc.Retry_Count_atc = AT_Cmd.Retry_Count_atc;
	m_gsm_atc.atc.Send_at_Callback = AT_Cmd.Send_at_Callback;

	memset(&m_gsm_atc.atc.Recv_Buffer, 0, sizeof(m_gsm_atc.atc.Recv_Buffer));
	HAL_UART_Transmit(&huart1, (uint8_t *)AT_Cmd.cmd, strlen(AT_Cmd.cmd), 200);

}
uint32_t sys_get_tick_ms(void)
{
    return HAL_GetTick();
}
