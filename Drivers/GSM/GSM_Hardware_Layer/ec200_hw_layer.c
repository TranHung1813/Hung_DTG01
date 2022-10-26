#include "ec200_hw_layer.h"
#include "string.h"

#define EC200_SEND(huart,DataSend,length)  HAL_UART_Transmit(huart,DataSend,length,200)

extern UART_HandleTypeDef huart1;
SuperBuffer_t m_rx_buff;
RingBuffer_Types Rx_Buffer;
void EC200_Turn_on_Power(void)
{
	SEGGER_RTT_WriteString(0,"Turning on Power ...\r\n");
	// Enable nguon 4.2V
	HAL_GPIO_WritePin(GSM_EN_GPIO_Port,GSM_EN_Pin,1);
	// Enable nguon GSM
	HAL_GPIO_WritePin(EN_GSM_GPIO_Port,EN_GSM_Pin,0);
	HAL_GPIO_WritePin(GSM_RESET_GPIO_Port,GSM_RESET_Pin,1);
	HAL_Delay(1000);
	HAL_GPIO_WritePin(EN_GSM_GPIO_Port,EN_GSM_Pin,1);
	HAL_Delay(1000);
	HAL_GPIO_WritePin(GSM_PWKEY_GPIO_Port,GSM_PWKEY_Pin,0);
	HAL_Delay(1000);
	HAL_GPIO_WritePin(GSM_PWKEY_GPIO_Port,GSM_PWKEY_Pin,1);
	HAL_Delay(200);
	HAL_GPIO_WritePin(GSM_RESET_GPIO_Port,GSM_RESET_Pin,0);
	HAL_Delay(1000);
	HAL_GPIO_WritePin(GSM_PWKEY_GPIO_Port,GSM_PWKEY_Pin,0);
	HAL_Delay(4000);

	SEGGER_RTT_WriteString(0,"Turn Module's Power on DONE.\r\n");

}
void EC200_Turn_off_Power(void)
{
	HAL_GPIO_WritePin(GSM_PWKEY_GPIO_Port,GSM_PWKEY_Pin,0);
	HAL_Delay(1000);
	HAL_GPIO_WritePin(GSM_PWKEY_GPIO_Port,GSM_PWKEY_Pin,1);
	HAL_Delay(1000);
	HAL_GPIO_WritePin(GSM_PWKEY_GPIO_Port,GSM_PWKEY_Pin,0);
	HAL_Delay(1000);
	HAL_GPIO_WritePin(EN_GSM_GPIO_Port,EN_GSM_Pin,0);
	HAL_GPIO_WritePin(GSM_RESET_GPIO_Port,GSM_RESET_Pin,1);
	HAL_Delay(1000);

	SEGGER_RTT_WriteString(0,"Turn off Power done.\r\n");
}
uint8_t EC200_CompareByteData(const uint8_t * src, uint16_t len_src, const uint8_t * des, uint16_t len_des)
{
	uint8_t result = E_NOT_OK;
	uint16_t CountPos = 0;
	uint16_t CountByte = 0;

	if(len_src < len_des)
	{
		return E_NOT_OK;
	}

	for(CountPos = 0; CountPos <= (len_src - len_des); CountPos++)
	{
		for(CountByte = 0; CountByte < len_des; CountByte++)
		{
			if(src[CountPos + CountByte] != des[CountByte])
			{
				break;
			}
		}

		if(CountByte == len_des)
		{
			result = E_OK;
			break;
		}
	}

	return result;
}
uint8_t EC200_SendCommand_AT(uint8_t* cmd, uint8_t* Keyword )
{
    uint8_t result = E_NOT_OK;
	uint8_t CountTimeRetry = EC200_COUNT_TIME_RETRY_SEND;
	while(CountTimeRetry > 0)
	{
		HAL_UART_Transmit(&huart1,cmd,strlen((char*)cmd),200);
		if(EC200_WaitResponse(Keyword, EC200_MAX_TIMEOUT_WAIT_REPS) == E_OK)
		{
			result = E_OK;
			break;
		}
		else
		{
			CountTimeRetry--;
		}
	}
    return result;
}

uint8_t EC200_WaitResponse(uint8_t* Keyword, uint16_t Timeout)
{
    uint8_t result = E_NOT_OK;
    uint16_t CountTime = 0;
    while(++CountTime < Timeout)
    {
        if((CountTime > 0) && (CountTime % EC200_TIME_TO_CHECK_REPS == 0))
        {
        	RingBuffer_GetBuffer(&m_rx_buff,&Rx_Buffer);
            if(EC200_CompareByteData(m_rx_buff.data, m_rx_buff.index, Keyword, strlen((char*)Keyword)) == E_OK)
            {
                result = E_OK;
                break;
            }
        }
        HAL_Delay(1);
    }
    SEGGER_RTT_printf(0,"%d,%d\r\n",m_rx_buff.index, result);
	for(int Count=1; Count < m_rx_buff.index; Count++)
	{
		SEGGER_RTT_printf(0,"%c",(char)m_rx_buff.data[Count]);
	}
	SEGGER_RTT_printf(0,"\r\n");
	memset(&m_rx_buff, 0, sizeof(m_rx_buff));
    return result;
}
