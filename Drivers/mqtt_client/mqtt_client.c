# include "mqtt_client.h"

static char MQTT_Publish_Topic_Name[MQTT_TOPIC_MAX_NAME_LENGTH];
static char MQTT_Subscribe_Topic_Name[MQTT_TOPIC_MAX_NAME_LENGTH];
static char MQTT_Tx_Buffer[256];

static mqtt_client_t MQTT_Static_Client;
static MQTT_Client_State_TypDef MQTT_Client_State = MQTT_CLIENT_STATE_DISCONNECTED;
static MQTT_Client_Config_TypDef MQTT_Client_Config;
static ip_addr_t MQTT_Server_Address;

#define	TOPIC_PUB_HEADER	"lwip_porting/pub/"
#define	TOPIC_SUB_HEADER	"lwip_porting/sub/"

static bool MQTT_Process_Now = false;
static bool m_is_dns_resolved = false;
static uint8_t Retry_Send_Subcribe = 0;
static bool m_is_valid_sub_topic = false;

void MQTT_Client_Init (MQTT_Client_Config_TypDef* cfg)
{
    memcpy(&MQTT_Client_Config, cfg, sizeof(MQTT_Client_Config_TypDef));
    snprintf(MQTT_Publish_Topic_Name, sizeof(MQTT_Publish_Topic_Name), "%s%s",
                                             TOPIC_PUB_HEADER, "Test_Publish");
    snprintf(MQTT_Subscribe_Topic_Name, sizeof(MQTT_Subscribe_Topic_Name), "%s%s",
                                             TOPIC_SUB_HEADER, "Test_Subcribe");
}
static void MQTT_Subcribe_Request_Callback(void *arg, err_t result)
{
    if(result != ERR_OK)
    {
        DEBUG_INFO("Retry send subscribe %d\r\n", Retry_Send_Subcribe);
        if(++Retry_Send_Subcribe >= MAXTIME_RETRY_SEND_SUBCRIBE)
        {
            Retry_Send_Subcribe = 0;
            /* close mqtt connection */
            mqtt_disconnect(&MQTT_Static_Client);
            MQTT_Client_State = MQTT_CLIENT_STATE_DISCONNECTED;
            DEBUG_RAW("MQTT_CLIENT_STATE_DISCONNECTED\r\n");
        }
        else
        {
            err_t err = mqtt_subscribe(&MQTT_Static_Client,
                                        MQTT_Subscribe_Topic_Name,
                                        SUB_QoS,
                                        MQTT_Subcribe_Request_Callback,
                                        arg);
            if(err == ERR_OK)
            {
                DEBUG_INFO("mqtt_subscribe return: %d\r\n", err);
            }
            else
            {
                DEBUG_INFO("mqtt_subscribe error: %d\r\n", err);
            }
        }
    }
    else
    {
        MQTT_Process_Now = true;
        DEBUG_INFO("Subscribed\r\n");
    }
}
/* 3. Implementing callbacks for incoming publish and data */
/* The idea is to demultiplex topic and create some reference to be used in data callbacks
   Example here uses a global variable, better would be to use a member in arg
   If RAM and CPU budget allows it, the easiest implementation might be to just take a copy of
   the topic string and use it in mqtt_incoming_data_cb
*/
static void MQTT_Incoming_Publish_Callback (void *arg, const char *topic, u32_t topic_len)
{
    DEBUG_INFO("MQTT publish topic %s, length %u\r\n", topic, (unsigned int) topic_len);
    /* Decode topic string into a user defined reference */
    if(strcmp(topic, MQTT_Subscribe_Topic_Name) == 0)
    {
        m_is_valid_sub_topic = true;
    }
    else
    {
        m_is_valid_sub_topic = false;
    }
}
static void MQTT_Incoming_Data_Callback(void *arg, const u8_t *data, u16_t len, u8_t flags)
{
    DEBUG_INFO("MQTT data cb, length %d, flags %u\r\n", len, (unsigned int)flags);
    if(flags & MQTT_DATA_FLAG_LAST)
    {
        DEBUG_INFO("Payload data: %s\r\n", (const char *)data);
        if(m_is_valid_sub_topic)
        {
            m_is_valid_sub_topic = false;
            /* Update firmware message  */
            if (strstr((char *)data, "UDFW,"))
            {
                DEBUG_INFO("Update firmware\r\n");
            }
            else if (strstr((char *)data, "PLEASE RESET"))
            {
                NVIC_SystemReset();
            }
        }
        // Clear received buffer of client -> du lieu nhan lan sau khong bi thua cua lan truoc,
        // neu lan truoc gui length > MQTT_VAR_HEADER_BUFFER_LEN
        memset(MQTT_Static_Client.rx_buffer, 0, MQTT_VAR_HEADER_BUFFER_LEN);
    }
    else
    {
        /* Handle fragmented payload, store in buffer, write to file or whatever */
    }
}
void MQTT_Client_Connection_Callback(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
    DEBUG_INFO("mqtt_client_connection_callback reason: %d\r\n", status);
    if(status == MQTT_CONNECT_ACCEPTED)
    {
        DEBUG_INFO("mqtt_connection_cb: Successfully connected.\r\n");
        MQTT_Process_Now = true;
        MQTT_Client_State = MQTT_CLIENT_STATE_CONNECTED;
        DEBUG_RAW("MQTT_CLIENT_STATE_CONNECTED\r\n");

        /* Setup callback for incoming publish requests */
        mqtt_set_inpub_callback(client, MQTT_Incoming_Publish_Callback, MQTT_Incoming_Data_Callback, arg);

        /* Subscribe to a topic named "fire/sub/IMEI" with QoS level 1,
        call mqtt_sub_request_cb with result */
        DEBUG_INFO("Subcribe %s\r\n", MQTT_Subscribe_Topic_Name);
        err_t err = mqtt_subscribe( &MQTT_Static_Client,
                                    MQTT_Subscribe_Topic_Name,
                                    SUB_QoS,
                                    MQTT_Subcribe_Request_Callback, arg);
        if(err == ERR_OK)
        {
            DEBUG_INFO("mqtt_subscribe ok: %d\r\n", err);
        }
        else
        {
            DEBUG_INFO("mqtt_subscribe error: %d\r\n", err);
        }
    }
    else
    {
        DEBUG_INFO("[%s] mqtt connection status %d\r\n", __FUNCTION__);
        mqtt_disconnect(&MQTT_Static_Client);
        MQTT_Client_State = MQTT_CLIENT_STATE_DISCONNECTED;
        DEBUG_RAW("MQTT_CLIENT_STATE_DISCONNECTED\r\n");
    }
}
static int8_t MQTT_Connect_Broker(mqtt_client_t* client)
{
   struct mqtt_connect_client_info_t client_info =
   {
       MQTT_Client_Config.ClientID,
       NULL, NULL,               //User, pass
       MQTT_KEEP_ALIVE_INTERVAL, //Keep alive in seconds, 0 - disable
       NULL, NULL, 0, 0          //Will topic, will msg, will QoS, will retain
   };

   /* Minimal amount of information required is client identifier, so set it here */
   client_info.client_user = MQTT_Client_Config.UserName;
   client_info.client_pass = MQTT_Client_Config.Password;
   /* 
    * Initiate client and connect to server, if this fails immediately an error code is returned
    * otherwise mqtt_connection_cb will be called with connection result after attempting 
    * to establish a connection with the server. 
    * For now MQTT version 3.1.1 is always used 
    */
    err_t err = mqtt_client_connect(client,
                                    &MQTT_Server_Address,
                                    MQTT_Client_Config.Port,
									MQTT_Client_Connection_Callback,
                                    0,
                                    &client_info);
    /* For now just print the result code if something goes wrong */
    if (err != ERR_OK)
    {
        DEBUG_INFO("mqtt_connect error %d \r\n", err);
        if( err == ERR_ISCONN)
        {
            DEBUG_INFO("MQTT already connected. \r\n");
        } 
    }
    else
    {
        DEBUG_INFO("Host %s:%d %s, client id %s\r\n",
                   MQTT_Client_Config.Broker_Address,
                   MQTT_Client_Config.Port,
                   ipaddr_ntoa(&MQTT_Server_Address),
                   MQTT_Client_Config.ClientID);
        DEBUG_INFO("mqtt_client_connect: OK\r\n");
    }
    return err;
}
/**
 * @brief DNS found callback when using DNS names as server address.
 */
static void mqtt_dns_found(const char *hostname, const ip_addr_t *ipaddr, void *arg)
{
    DEBUG_INFO("mqtt_dns_found: %s\r\n", hostname);

    LWIP_UNUSED_ARG(hostname);
    LWIP_UNUSED_ARG(arg);

    if (ipaddr != NULL)
    {
        /* Address resolved, send request */
        MQTT_Server_Address.addr = ipaddr->addr;
        DEBUG_INFO("Server address resolved = %s\r\n", ipaddr_ntoa(&MQTT_Server_Address));
        m_is_dns_resolved = true;
        MQTT_Process_Now = true;
    }
    else
    {
        /* DNS resolving failed -> try another server */
        DEBUG_INFO("mqtt_dns_found: Failed to resolve server address resolved, trying next server.\r\n");
        m_is_dns_resolved = false;
    }
}

/* -----------------------------------------------------------------
4. Using outgoing publish
*/
/* Called when publish is complete either with sucess or failure */
static void MQTT_Publish_Request_Callback(void *arg, err_t result)
{
    if (result != ERR_OK)
    {
        DEBUG_INFO("Publish result: %d\r\n", result);
    }
    else
    {
        DEBUG_INFO("Publish: OK\r\n");
    }
}
static void MQTT_Client_Send_Heartbeat(void)
{
    snprintf(MQTT_Tx_Buffer, sizeof(MQTT_Tx_Buffer), "%s", "Hello world!");
    err_t err = mqtt_publish(&MQTT_Static_Client,
                             MQTT_Publish_Topic_Name,
                             MQTT_Tx_Buffer,
                             strlen(MQTT_Tx_Buffer),
                             PUB_QoS,
                             PUB_RETAIN,
                             MQTT_Publish_Request_Callback,
                             NULL);
    DEBUG_INFO("Publish data \"%s\" to topic %s\r\n", MQTT_Tx_Buffer, MQTT_Publish_Topic_Name);  
    DEBUG_INFO("Publish return: %d\r\n", err);
}

void MQTT_Client_Polling_Task(void *arg)
{
    static uint8_t MQTT_Tick = 0;
    static uint32_t tick = 0, last_time_send_sub_request = 0, last_time_send_hearbeat = 0;
    static uint32_t last_tick = 0;
    uint32_t current_tick = sys_get_tick_ms();
    if(current_tick - last_tick >= (uint32_t)1000 || MQTT_Process_Now)
    {
        MQTT_Process_Now = false;
        last_tick = current_tick;
    }
    else
    {
        return;
    }

    static bool MQTT_Allow = false;

    if(gsm_data_layer_is_ppp_connected())
    {
        if(MQTT_Allow == false)
        {
            MQTT_Allow = true;
            if(mqtt_client_is_connected(&MQTT_Static_Client))
            {
                mqtt_disconnect(&MQTT_Static_Client);
                MQTT_Client_State = MQTT_CLIENT_STATE_DISCONNECTED;
                DEBUG_RAW("MQTT_CLIENT_STATE_DISCONNECTED\r\n");
            }
            DEBUG_INFO("MQTT Thread Started.\r\n");
        }
    }
    else
    {
        if(MQTT_Allow)
        {
            MQTT_Allow = false;
            DEBUG_INFO("MQTT Thread Stopped.\r\n");
        }
    }
    if(MQTT_Allow)
    {
        MQTT_Tick++;
        switch (MQTT_Client_State)
        {
            case MQTT_CLIENT_STATE_DISCONNECTED:
                m_is_dns_resolved = false;
                MQTT_Client_State = MQTT_CLIENT_STATE_RESOLVE_HOSTNAME;
                DEBUG_RAW("MQTT_CLIENT_STATE_RESOLVE_HOSTNAME\r\n");
                MQTT_Tick = 4;
                break;
            case MQTT_CLIENT_STATE_RESOLVE_HOSTNAME:
                if(!m_is_dns_resolved)
                {
                    if(MQTT_Tick >= 5)
                    {
                        MQTT_Tick = 0;
                        err_t err = dns_gethostbyname(MQTT_Client_Config.Broker_Address,
                                                        &MQTT_Server_Address,
                                                        mqtt_dns_found,
                                                        NULL);
                        if(err == ERR_INPROGRESS)
                        {
                            /* DNS request sent, wait for sntp_dns_found being called */
                            DEBUG_INFO("sntp_request: %d - Waiting for server %s address to be resolved.\r\n", 
                                        err, MQTT_Client_Config.Broker_Address);
                        }
                        else if(err == ERR_OK)
                        {
                            DEBUG_INFO("DNS resolved aready, host %s, mqtt_ipaddr = %s\r\n",
                                        MQTT_Client_Config.Broker_Address,
                                        ipaddr_ntoa(&MQTT_Server_Address));
                            m_is_dns_resolved = true;
                        }
                        else
                        {
                            DEBUG_INFO("dns_gethostbyname error: %d\r\n", err);
                        }
                    }
                }
                else
                {
                    MQTT_Tick = 9;
                    MQTT_Client_State = MQTT_CLIENT_STATE_CONNECTING;
                    DEBUG_RAW("MQTT_CLIENT_STATE_CONNECTING\r\n");
                }
                break;

            case MQTT_CLIENT_STATE_CONNECTING:
                if(MQTT_Tick >= 10)
                {
                    if(MQTT_Connect_Broker(&MQTT_Static_Client) == ERR_OK)
                    {
                        MQTT_Tick = 5;  /* Gui login sau 5s */
                    }
                    else
                    {
                        MQTT_Tick = 0;
                    }
                }
                break;
            case MQTT_CLIENT_STATE_CONNECTED:
                tick = current_tick;

                if(last_time_send_sub_request == 0)
                {
                    last_time_send_sub_request = tick;
                }

                if(mqtt_client_is_connected(&MQTT_Static_Client))
                {
                    if((tick - last_time_send_sub_request) >= MQTT_Client_Config.Period_sub_req_s * 1000)
                    {
                        last_time_send_sub_request = tick;
                        err_t err = mqtt_subscribe(&MQTT_Static_Client,
                                                    MQTT_Subscribe_Topic_Name,
                                                    SUB_QoS,
                                                    MQTT_Subcribe_Request_Callback, arg);
                        DEBUG_INFO("Subcribe to: topic %s return: %d.\r\n", MQTT_Subscribe_Topic_Name, err);
                    }
                    if((tick - last_time_send_hearbeat) >= (uint32_t)30000)
                    {
                        last_time_send_hearbeat = tick;
                        MQTT_Client_Send_Heartbeat();
                    }
                }
                else
                {
                    MQTT_Client_State = MQTT_CLIENT_STATE_DISCONNECTED;
                    DEBUG_RAW("MQTT_CLIENT_STATE_DISCONNECTED\r\n");
                }

                break;

            default:
                break;
        }
    }

}
