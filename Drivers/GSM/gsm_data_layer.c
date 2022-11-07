# include "gsm.h"

Gsm_Manager_TypDef GSM_Manager;
static uint8_t GSM_IMEI_Buffer[20] = {0};
static uint16_t GSM_Signal_Strength = 0;

// PPP
/* The PPP IP interface */
static struct netif m_ppp_netif;
/* The PPP control block */
static ppp_pcb *m_ppp_control_block;
static uint32_t ppp_output_callback(ppp_pcb *pcb, u8_t *data, u32_t len, void *ctx);
static void ppp_link_status_cb(ppp_pcb *pcb, int err_code, void *ctx);
static void ppp_notify_phase_cb(ppp_pcb *pcb, u8_t phase, void *ctx);
static void open_ppp_stack(GSM_Response_Event_TypDef event, void *Resp_Buffer);
static bool m_ppp_connected = false;

const GSM_ATCommand_Table_TypDef atc_table_config_module[] =
{
    {"ATV1\r\n", "OK\r\n", "OK\r\n", "ERROR", "", 3000, 5, GSM_Config_Module}, // Set TA Response Format (OK/'0')
    {"ATE0\r\n", "OK\r\n", "OK\r\n", "ERROR", "", 3000, 3, GSM_Config_Module}, //Disable ECHO
    {"AT+CMEE=2\r\n", "OK\r\n", "OK\r\n", "ERROR", "", 6000, 5, GSM_Config_Module}, //Setup ERROR Message Format
    {"ATI\r\n", "OK\r\n", "OK\r\n", "ERROR", "", 6000, 5, GSM_Config_Module}, //Get Info Module
    {"AT\r\n", "OK\r\n", "OK\r\n", "ERROR", "", 6000, 5, GSM_Config_Module}, //AT Test 1
    {"AT\r\n", "OK\r\n", "OK\r\n", "ERROR", "", 3000, 5, GSM_Config_Module}, //AT Test 2
    {"AT+QCFG=\"urc/ri/smsincoming\",\"pulse\",2000\r\n", "OK\r\n", "OK\r\n", "ERROR", "", 10000, 2, GSM_Config_Module}, //Set URC Ringtype
    {"AT+CNMI=2,1,0,0,0\r\n", "OK\r\n", "OK\r\n", "ERROR", "", 10000, 3, GSM_Config_Module}, // Config SMS event report
    {"AT+CMGF=1\r\n", "OK\r\n", "OK\r\n", "ERROR", "", 5000, 5, GSM_Config_Module}, //Set SMS to Text Mode
    {"AT\r\n", "OK\r\n", "OK\r\n", "ERROR", "", 3000, 5, GSM_Config_Module}, // AT Test
    {"AT+CGSN\r\n", "OK\r\n", "OK\r\n", "ERROR", "", 8000, 5, GSM_GET_IMEI_Buffer}, // Get IMEI
    {"AT+CIMI\r\n", "OK\r\n", "OK\r\n", "", "", 1000, 5, GSM_Config_Module}, // GET IMSI
    {"AT+QCCID\r\n", "QCCID", "OK\r\n", "ERROR", "", 3000, 7, GSM_Config_Module}, // Get ICCID
    {"AT+CPIN?\r\n", "+CPIN: READY\r\n", "OK\r\n", "", "", 3000, 3, GSM_Config_Module}, // Get state CPIN
    {"AT+QIDEACT=1\r\n", "OK\r\n", "OK\r\n", "ERROR", "", 3000, 3, GSM_Config_Module},// De-activate PDP
    {"AT\r\n", "OK\r\n", "OK\r\n", "ERROR", "", 5000, 2, GSM_Config_Module}, // AT Test
    {"AT+CGDCONT=1,\"IP\",\"v-internet\"\r\n", "OK\r\n", "", "ERROR", "", 3000, 5, GSM_Config_Module}, // Define PDP context
    {"AT+QIACT=1\r\n", "OK", "OK\r\n", "ERROR", "", 15000, 2, GSM_Config_Module}, //CSCS=GSM?
    {"AT+CGREG=2\r\n", "OK\r\n", "OK\r\n", "ERROR", "", 3000, 5, GSM_Config_Module}, //Network registration status
    {"AT+CGREG?\r\n", "OK\r\n", "OK\r\n", "ERROR", "", 5000, 5, GSM_Config_Module}, //Query network status
    {"AT+COPS?\r\n", "OK\r\n", "OK\r\n", "ERROR", "", 3000, 5, GSM_Config_Module}, //Query network operator
    {"AT\r\n", "OK\r\n", "OK\r\n", "ERROR", "", 3000, 5, GSM_Config_Module}, //AT Test
    {"AT+CSQ\r\n", "OK\r\n", "OK\r\n", "ERROR", "", 3000, 5, GSM_GET_Signal_Strength}, //Get CSQ
    {"AT\r\n", "OK\r\n", "OK\r\n", "ERROR", "", 3000, 5, GSM_Config_Module}, // AT Test

};
const GSM_ATCommand_Table_TypDef atc_table_open_ppp_stack[] =
{
    {"ATV1\r\n", "OK\r\n", "", "ERROR", "", 1000, 5, open_ppp_stack},
    {"AT+CSQ\r\n", "OK\r\n", "", "ERROR", "", 1000, 2, open_ppp_stack}, //Get CSQ
    {"AT+CPIN?\r\n", "OK\r\n", "", "ERROR", "", 1000, 5, open_ppp_stack}, // Check SIM has inserted or not
    {"ATD*99***1#\r\n", "CONNECT", "", "", "", 1000, 10, open_ppp_stack}, // Open ppp stack
    
};

void GSM_Config_Module (GSM_Response_Event_TypDef event, void *Resp_Buffer)
{
    uint8_t TableIndex = GSM_Manager.step;
    uint8_t TableSize = sizeof(atc_table_config_module)/sizeof(atc_table_config_module[0]);
    if(TableIndex > TableSize)
    {
        return;
    }
    DEBUG_PrintResult_ATC(atc_table_config_module[TableIndex-1].cmd, (event == GSM_EVENT_OK)?"[OK]":"[FAIL]");
    if(event == GSM_EVENT_OK)
    {
        if(TableIndex < TableSize)
        {
        	//HAL_Delay(2000);
            GSM_SendCommand_AT(atc_table_config_module[TableIndex]);
        }
        else
        {
            // Da Config Module xong
            GSM_Manager.step = 0;
            DEBUG_INFO("Config module DONE.\r\n");
            GSM_SendCommand_AT(atc_table_open_ppp_stack[0]);
        }
        GSM_Manager.step++;
    }
    else //if(event == GSM_EVENT_TIMEOUT)
    {
        GSM_Manager_ChangeState(GSM_STATE_RESET);
    }
}
void open_ppp_stack(GSM_Response_Event_TypDef event, void *Resp_Buffer)
{
    DEBUG_INFO("Open PPP stack step %d\r\n", GSM_Manager.step);
    uint8_t TableIndex = GSM_Manager.step;
    uint8_t TableSize = sizeof(atc_table_open_ppp_stack)/sizeof(atc_table_open_ppp_stack[0]);
    if(TableIndex > TableSize)
    {
        return;
    }
    DEBUG_PrintResult_ATC(atc_table_open_ppp_stack[TableIndex-1].cmd, (event == GSM_EVENT_OK)?"[OK]":"[FAIL]");
    if(event == GSM_EVENT_OK)
    {
        if(TableIndex < TableSize)
        {
            GSM_SendCommand_AT(atc_table_open_ppp_stack[TableIndex]);
        }
        else
        {
            GSM_Manager.mode = GSM_INTERNET_MODE_PPP_STACK;
            // Da CONNECT PPP thanh cong
            GSM_Manager_ChangeState(GSM_STATE_OK);

            //Create PPP connection
            m_ppp_control_block = pppos_create(&m_ppp_netif, ppp_output_callback, ppp_link_status_cb, NULL);
            if (m_ppp_control_block == NULL)
            {
                DEBUG_ERROR("Create PPP interface ERR!\r\n");
                //assert(0);
                // TODO handle memory error
                NVIC_SystemReset();
            }

            /* Set this interface as default route */
            ppp_set_default(m_ppp_control_block);
            //ppp_set_auth(m_ppp_control_block, PPPAUTHTYPE_CHAP, "", "");
            ppp_set_notify_phase_callback(m_ppp_control_block, ppp_notify_phase_cb);
            ppp_connect(m_ppp_control_block, 0);
        }
        GSM_Manager.step++;
    }
    else //if(event == GSM_EVENT_TIMEOUT)
    {
        // Handle ERROR
        GSM_Manager_ChangeState(GSM_STATE_RESET);
    }
}
void GSM_GET_IMEI_Buffer(GSM_Response_Event_TypDef event, void *Resp_Buffer)
{
    if(event != GSM_EVENT_OK)
    {
        GSM_Config_Module(event, &Resp_Buffer);
    }
    else
    {
        if(strlen((char*)GSM_IMEI_Buffer) < 14)
        {
            GSM_Utilities_Get_IMEI(Resp_Buffer, GSM_IMEI_Buffer, 16);
            if(strlen((char*)GSM_IMEI_Buffer) < 15)
            {
                DEBUG_WARN("IMEI's invalid!\r\n");
                GSM_Manager_ChangeState(GSM_STATE_RESET); // Cant get GSM imei, maybe gsm module error =>> Restart module
                return;
            }
            else
            {
                DEBUG_INFO("GSM IMEI: %s\r\n", GSM_IMEI_Buffer);
            }
        }
        GSM_Config_Module(event, &Resp_Buffer);
    }
}
void GSM_GET_Signal_Strength(GSM_Response_Event_TypDef event, void *Resp_Buffer)
{
    
    if(event != GSM_EVENT_OK)
    {
        GSM_Config_Module(event, &Resp_Buffer);
    }
    else
    {
        if(GSM_Signal_Strength == 0)
        {
            gsm_utilities_get_signal_strength_from_buffer(Resp_Buffer, &GSM_Signal_Strength);
            DEBUG_INFO("GSM Signal strength: %d\r\n", GSM_Signal_Strength);
        }
        GSM_Config_Module(event, &Resp_Buffer);
    }
}
static void ppp_notify_phase_cb(ppp_pcb *pcb, u8_t phase, void *ctx)
{
    switch (phase)
    {
    /* Session is down (either permanently or briefly) */
    case PPP_PHASE_DEAD:
        DEBUG_INFO("PPP_PHASE_DEAD\r\n");
        GSM_Manager.ppp_phase = PPP_PHASE_DEAD;
        break;

    /* We are between two sessions */
    case PPP_PHASE_HOLDOFF:
        DEBUG_INFO("PPP_PHASE_HOLDOFF\r\n");
        GSM_Manager.ppp_phase = PPP_PHASE_HOLDOFF;
        break;

    /* Session just started */
    case PPP_PHASE_INITIALIZE:
        DEBUG_INFO("PPP_PHASE_INITIALIZE\r\n");
        GSM_Manager.ppp_phase = PPP_PHASE_INITIALIZE;
        break;

    case PPP_PHASE_NETWORK:
        DEBUG_INFO("PPP_PHASE_NETWORK\r\n");
        break;

    case PPP_PHASE_ESTABLISH:
        DEBUG_INFO("PPP_PHASE_ESTABLISH\r\n");
        break;

    /* Session is running */
    case PPP_PHASE_RUNNING:
        DEBUG_INFO("PPP_PHASE_RUNNING\r\n");
        GSM_Manager.ppp_phase = PPP_PHASE_RUNNING;
        m_ppp_connected = true;
        break;

    case PPP_PHASE_TERMINATE:
        DEBUG_INFO("PPP_PHASE_TERMINATE\r\n");
        break;

    case PPP_PHASE_DISCONNECT:
        DEBUG_INFO("PPP_PHASE_DISCONNECT\r\n");
        break;

    default:
        DEBUG_INFO("Unknown PPP phase %d\r\n", phase);
        break;
    }
}
static uint32_t ppp_output_callback(ppp_pcb *pcb, u8_t *data, u32_t len, void *ctx)
{
    GSM_UART_TX( data, len, 1000);
    return len;
}
void *gsm_data_layer_get_ppp_control_block(void)
{
    return m_ppp_control_block;
}
static void initialize_stnp(void)
{
    static bool sntp_start = false;
    if (sntp_start == false)
    {
        sntp_start = true;
        DEBUG_INFO("Initialize stnp\r\n");
        sntp_setoperatingmode(SNTP_OPMODE_POLL);
        sntp_setservername(0, "pool.ntp.org");
        sntp_init();
    }
}

void lwip_sntp_recv_callback(uint32_t time)
{
    if (time == 0)
    {
        DEBUG_WARN("NTP: Error, server not responding or bad response\r\n");
    }
    else
    {
        DEBUG_INFO("NTP: %u seconds elapsed since 1.1.1970\r\n", time);
    }
}


/**
 * PPP status callback
 * ===================
 *
 * PPP status callback is called on PPP status change (up, down, ...) from lwIP core thread
 */
static void ppp_link_status_cb(ppp_pcb *pcb, int err_code, void *ctx)
{
    struct netif *pppif = ppp_netif(pcb);
    LWIP_UNUSED_ARG(ctx);

    switch (err_code)
    {
    case PPPERR_NONE:
    {
#if LWIP_DNS
        const ip_addr_t *ns;
#endif /* LWIP_DNS */

        DEBUG_INFO("PPP Connected\r\n");

#if PPP_IPV4_SUPPORT

        DEBUG_INFO("\tour_ipaddr    = %s\r\n", ipaddr_ntoa(&pppif->ip_addr));
        DEBUG_INFO("\this_ipaddr    = %s\r\n", ipaddr_ntoa(&pppif->gw));
        DEBUG_INFO("\tnetmask       = %s\r\n", ipaddr_ntoa(&pppif->netmask));
        HAL_Delay(1);

#if LWIP_DNS
        ns = dns_getserver(0);
        DEBUG_INFO("\tdns1          = %s\r\n", ipaddr_ntoa(ns));
        ns = dns_getserver(1);
        DEBUG_INFO("\tdns2          = %s\r\n", ipaddr_ntoa(ns));
        HAL_Delay(1);
#endif /* LWIP_DNS */

#endif /* PPP_IPV4_SUPPORT */

#if PPP_IPV6_SUPPORT
        DEBUG_INFO("\r   our6_ipaddr = %s\n", ip6addr_ntoa(netif_ip6_addr(pppif, 0)));
#endif /* PPP_IPV6_SUPPORT */
        break;
    }

    case PPPERR_PARAM:
    {
        DEBUG_INFO("status_cb: Invalid parameter\r\n");
        break;
    }
    case PPPERR_OPEN:
    {
        DEBUG_INFO("status_cb: Unable to open PPP session\r\n");
        break;
    }
    case PPPERR_DEVICE:
    {
        DEBUG_INFO("status_cb: Invalid I/O device for PPP\r\n");
        break;
    }
    case PPPERR_ALLOC:
    {
        DEBUG_INFO("status_cb: Unable to allocate resources\r\n");
        break;
    }
    case PPPERR_USER: /* 5 */
    {
        /* ppp_close() was previously called, reconnect */
        DEBUG_INFO("status_cb: ppp is closed by user OK! Try to re-open...\r\n");
        /* ppp_free(); -- can be called here */
        ppp_free(m_ppp_control_block);
        GSM_Manager_ChangeState(GSM_STATE_REOPEN_PPP);
        break;
    }
    case PPPERR_CONNECT: /* 6 */
    {
        DEBUG_INFO("status_cb: Connection lost\r\n");
        m_ppp_connected = false;
        ppp_close(m_ppp_control_block, 1);
        break;
    }
    case PPPERR_AUTHFAIL:
    {
        DEBUG_INFO("status_cb: Failed authentication challenge\r\n");
        break;
    }
    case PPPERR_PROTOCOL:
    {
        DEBUG_INFO("status_cb: Failed to meet protocol\n");
        break;
    }
    case PPPERR_PEERDEAD:
    {
        DEBUG_INFO("status_cb: Connection timeout\r\n");
        break;
    }
    case PPPERR_IDLETIMEOUT:
    {
        DEBUG_INFO("status_cb: Idle Timeout\r\n");
        break;
    }
    case PPPERR_CONNECTTIME:
    {
        DEBUG_INFO("status_cb: Max connect time reached\r\n");
        break;
    }
    case PPPERR_LOOPBACK:
    {
        DEBUG_INFO("status_cb: Loopback detected\r\n");
        break;
    }
    default:
    {
        DEBUG_INFO("status_cb: Unknown error code %d\r\n", err_code);
        break;
    }
    }

    /*
	* This should be in the switch case, this is put outside of the switch
	* case for example readability.
	*/

    if (err_code == PPPERR_NONE)
    {
        DEBUG_INFO("PPP is opened OK\r\n");
        initialize_stnp();
        return;
    }

    //  /* ppp_close() was previously called, don't reconnect */
    //  if (err_code == PPPERR_USER) {
    //    /* ppp_free(); -- can be called here */
    //	 m_ppp_connected = false;
    //	 ppp_free(m_ppp_control_block);
    //	 DEBUG_INFO("\r\nPPP opened ERR!\r\n");
    //    return;
    //  }

    /*
   * Try to reconnect in 30 seconds, if you need a modem chatscript you have
   * to do a much better signaling here ;-)
   */
    //  ppp_connect(pcb, 30);
    /* OR ppp_listen(pcb); */
}
void Polling_GSM_StateMachine (void)
{
    static uint32_t last_tick = 0;
    uint32_t current_tick = sys_get_tick_ms();
    if(current_tick - last_tick >= (uint32_t)1000)
    {
        last_tick = current_tick;
        switch (GSM_Manager.state)
        {
            case GSM_STATE_RESET:
                GSM_Turn_on_Power();
                break;
            case GSM_STATE_POWER_ON:
                if(GSM_Manager.step == 0)
                {
                    GSM_Manager.step = 1;
                    GSM_SendCommand_AT(atc_table_config_module[0]);
                }
                break;
            case GSM_STATE_OK:

                break;
            case GSM_STATE_REOPEN_PPP:

            	break;
            default:
                DEBUG_WARN("Unhandled state %d.\r\n", GSM_Manager.state);
                break;
        }
    }
}
bool gsm_is_in_ppp_mode(void)
{
    return GSM_Manager.mode == GSM_INTERNET_MODE_PPP_STACK? true : false;
}
bool gsm_data_layer_is_ppp_connected(void)
{
    return m_ppp_connected;
}


void GSM_Manager_ChangeState(Gsm_State_TypDef state)
{
    GSM_Manager.state = state;
    GSM_Manager.step = 0;
    DEBUG_INFO("Change GSM State to: ");
    switch (state)
    {
    case GSM_STATE_OK:
        DEBUG_RAW("OK\r\n");

        break;
    case GSM_STATE_RESET:
    	DEBUG_RAW("RESET\r\n");
        GSM_HwLayer_Reset_Rx_Buffer(); // Reset USART RX buffer
        GSM_Manager_ChangeInternetMode(GSM_INTERNET_MODE_AT_STACK);
        HAL_GPIO_WritePin(EN_GSM_GPIO_Port,EN_GSM_Pin,0);    // Set GSM power en level to 0 = power off device
		HAL_GPIO_WritePin(GSM_RESET_GPIO_Port,GSM_RESET_Pin,1);  // Set GSM Reset pin to high
		HAL_GPIO_WritePin(GSM_PWKEY_GPIO_Port,GSM_PWKEY_Pin,0);  // Reset GSM power key pin
        break;
    case GSM_STATE_POWER_ON:
    	DEBUG_RAW("POWER ON\r\n");
        GSM_HwLayer_Reset_Rx_Buffer(); // Reset USART RX buffer
        break;

    case GSM_STATE_REOPEN_PPP:
    	DEBUG_RAW("REOPEN PPP\r\n");
        if (GSM_Manager.step == 0)
        {
            GSM_Manager.step = 1;
            m_ppp_connected = false;
            GSM_Manager_ChangeInternetMode(GSM_INTERNET_MODE_AT_STACK);
            GSM_HwLayer_Reset_Rx_Buffer(); // Reset USART RX buffer
            GSM_SendCommand_AT(atc_table_open_ppp_stack[0]);
        }
        break;
    default:
        break;
    }
}
void GSM_Manager_ChangeInternetMode(gsm_internet_mode_t mode)
{
    GSM_Manager.mode = mode;
}
void GSM_mnr_task(void)
{
    GSM_Hardware_Layer_Run();
    Polling_GSM_StateMachine();
    GSM_Hardware_pppos_Polling();
}
