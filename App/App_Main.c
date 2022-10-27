#include "App_Main.h"
#include "main.h"
#include "SEGGER_RTT.h"
#include  <string.h>
extern UART_HandleTypeDef huart1;
uint8_t data = 0;
extern RingBuffer_Types Rx_Buffer;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//	m_rx_buff.data[m_rx_buff.index] = data ;
//	m_rx_buff.index++;

	RingBuffer_Push(&Rx_Buffer, data);
	HAL_UART_Receive_IT(&huart1, &data, 1);
}


void App_Main ()
{
	// Note: Sửa NOPULL -> PULLUP:  GPIO_InitStruct.Pull = GPIO_PULLUP; de tranh loi nhan NULL truoc khi Power on EC200
	HAL_UART_Receive_IT(&huart1, &data, 1);

	GMS_Hardware_Init();
	//UART_SendData(USART1, bf_send, sizeof(bf_send));
	while(1)
	{
		GSM_mnr_task();
	}

}
