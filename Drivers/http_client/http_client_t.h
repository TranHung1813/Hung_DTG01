#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include "gsm.h"
#include "http_client.h"

#define APP_HTTP_MAX_URL_SIZE 256

typedef enum
{
    HTTP_STEP_DISCONNECT = 0,
    HTTP_STEP_CONFIG,
    HTTP_STEP_CONNECTING,
    HTTP_STEP_CONNECTED,
}Http_Step_TypDef;
typedef struct
{
    char Url[APP_HTTP_MAX_URL_SIZE];
    uint16_t Port;
    char File[APP_HTTP_MAX_URL_SIZE];
}HTTP_Client_Config_TypDef;

typedef struct
{
    Http_Step_TypDef Step;
    uint8_t State;
}HTTP_Manager_TypDef;

/**
 * @brief       Clean up current configuration
 */
void app_http_cleanup(void);
/**
 * @brief       Init HTTP_Client download
 * @param[in]   cfg : HTTP configuration
 * @retval      TRUE : Operation success
 *              FALSE : Operation failed
 */
void HTTP_Client_Init(HTTP_Client_Config_TypDef *cfg);
void HTTP_Cleanup(void);
void HTTP_Client_Polling_Task(void *arg);







#endif /* HTTP_CLIENT_H */
