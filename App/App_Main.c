#include "App_Main.h"
#include "main.h"

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

void UART_SendData(USART_TypeDef * uart, uint8_t *pTxBuffer, uint32_t length)
{
	for(uint32_t CountByte = 0; CountByte < length; CountByte++)
	{
		while((uart-> ISR & USART_ISR_TXE_Msk) == 0); // doi thanh ghi Data Empty
		uart ->TDR = (uint8_t)(*pTxBuffer & 0xFF);
		pTxBuffer++;
	}
	while (!(uart ->ISR & USART_ISR_TC_Msk)); // doi TC set
}
void UART_ReceiveData(USART_TypeDef * uart, uint8_t *pRxBuffer, uint32_t length)
{
	for(uint32_t CountByte = 0; CountByte < length; CountByte++)
	{
		while((uart->ISR & USART_ISR_RXNE_Msk) == 0); // doi RXNE set
		*pRxBuffer = (uint8_t)(uart->RDR & 0xFF);
		pRxBuffer++;
		//m_rx_buff.index++;
	}
}
void App_Main ()
{
	//Init SEGGER RTT Debug
	SEGGER_RTT_Init();
	// Cap phat bo nho cho RxRingBuffer
	RingBuffer_Init(&Rx_Buffer, 100);
	//Turn on power EC200
	EC200_Turn_on_Power();
	//EC200_Turn_off_Power();

	HAL_UART_Receive_IT(&huart1, &data, 1);

	EC200_Config_Module();
	//UART_SendData(USART1, bf_send, sizeof(bf_send));
	while(1)
	{
		HAL_Delay(2000);
		//HAL_UART_Transmit(&huart1, bf_send, sizeof(bf_send), 1000);
		//UART_ReceiveData(USART1, Rxbuffer, sizeof (Rxbuffer));
		//SEGGER_RTT_printf(0,"%d,\r\n",result);
		//uint8_t result = EC200_SendCommand_AT(bf_send,(uint8_t *)"OK\r\n");
	}

}
