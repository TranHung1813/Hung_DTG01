#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include "gsm.h"
#include "mqtt.h"
#include "mqtt_priv.h"

/* QoS value, 0 - at most once, 1 - at least once or 2 - exactly once */
#define SUB_QoS	    1
#define PUB_QoS	    1
#define PUB_RETAIN	0
#define MQTT_KEEP_ALIVE_INTERVAL 600
#define MQTT_TOPIC_MAX_NAME_LENGTH 48

#define MAXTIME_RETRY_SEND_SUBCRIBE  5
typedef enum 
{
    MQTT_CLIENT_STATE_DISCONNECTED = 0,
    MQTT_CLIENT_STATE_RESOLVE_HOSTNAME,
    MQTT_CLIENT_STATE_CONNECTING,
    MQTT_CLIENT_STATE_CONNECTED,
} MQTT_Client_State_TypDef;

typedef struct
{
    uint32_t Period_sub_req_s; //second
    const char* Broker_Address;
    uint16_t Port;
    const char* ClientID;
    const char* UserName;
    const char* Password;
} MQTT_Client_Config_TypDef;

/**
 * @brief           MQTT client initialize
 * @param[in]       MQTT config parameter
 */
void MQTT_Client_Init (MQTT_Client_Config_TypDef* cfg);

/**
 * @brief Polling MQTT service
 */
void MQTT_Client_Polling_Task(void *arg);




















#endif  // MQTT_CLIENT_H
