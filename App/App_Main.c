#include "App_Main.h"
#include "main.h"
#include "SEGGER_RTT.h"
#include <stdio.h>

extern UART_HandleTypeDef huart1;
uint8_t data = 0;
extern RingBuffer_Types Rx_Buffer;

MQTT_Client_Config_TypDef MQTT_Cfg =
{
	30,
	"test-mqtt-stm32-ec200.cloud.shiftr.io",
	1883,
	"Hung_DTG01",
	"test-mqtt-stm32-ec200",
	"inQSolHhWx8lX0xj",
};
HTTP_Client_Config_TypDef HTTP_Cfg = 
{
	"httpbin.org",
	80,
	"/get",
};
FTP_Config_TypDef GSM_File_Handler_Cfg = 
{
	"171.244.40.51",
	"firmware",
	"abcd@1234",
	(uint32_t)21,
};
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//	m_rx_buff.data[m_rx_buff.index] = data ;
//	m_rx_buff.index++;

	RingBuffer_Push(&Rx_Buffer, data);
	HAL_UART_Receive_IT(&huart1, &data, 1);
}
static void dns_initialize(void);

void App_Main ()
{
	// Note: Sửa NOPULL -> PULLUP:  GPIO_InitStruct.Pull = GPIO_PULLUP; de tranh loi nhan NULL truoc khi Power on EC200
	HAL_UART_Receive_IT(&huart1, &data, 1);

 	dns_initialize();
	//lwip_init();
	//MQTT_Client_Init(&MQTT_Cfg);
	//HTTP_Client_Init(&HTTP_Cfg);
	GSM_File_Handler_Init(&GSM_File_Handler_Cfg);
	DEBUG_INFO("Application started\r\n");
	GMS_Hardware_Init();
	//UART_SendData(USART1, bf_send, sizeof(bf_send));
	while(1)
	{
		GSM_mnr_task();
		//MQTT_Client_Polling_Task(NULL);
		HTTP_Client_Polling_Task(NULL);
	}
}

static void dns_initialize(void)
{
    ip_addr_t dns_server_0 = IPADDR4_INIT_BYTES(8, 8, 8, 8);
    ip_addr_t dns_server_1 = IPADDR4_INIT_BYTES(1, 1, 1, 1);
    dns_setserver(0, &dns_server_0);
    dns_setserver(1, &dns_server_1);
    dns_init();
}
#ifdef __GNUC__

 /* With GCC, small printf (option LD Linker->Libraries->Small printf

   set to 'Yes') calls __io_putchar() */

 #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)

#else

 #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

#endif /* __GNUC__ */
int __io_putchar(int ch)

{

 /* Place your implementation of fputc here */

 /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */

	DEBUG_INFO("%c", &ch, 1);



 return ch;

}

