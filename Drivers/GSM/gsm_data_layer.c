# include "gsm.h"

Gsm_Manager_TypDef GSM_Manager;
static uint8_t GSM_IMEI_Buffer[20] = {0};
const GSM_ATCommand_Table_TypDef atc_table_config_module[] =
{
    {"ATV1\r\n", "OK\r\n", "", "ERROR", "", 3000, 5, GSM_Config_Module}, // Set TA Response Format (OK/'0')
    {"ATE0\r\n", "OK\r\n", "", "ERROR", "", 3000, 3, GSM_Config_Module}, //Disable ECHO
    {"AT+CMEE=2\r\n", "OK\r\n", "", "ERROR", "", 6000, 5, GSM_Config_Module}, //Setup ERROR Message Format
    {"ATI\r\n", "OK\r\n", "", "ERROR", "", 6000, 5, GSM_Config_Module}, //Get Info Module
    {"AT\r\n", "OK\r\n", "", "ERROR", "", 6000, 5, GSM_Config_Module}, //AT Test 1
    {"AT\r\n", "OK\r\n", "", "ERROR", "", 3000, 5, GSM_Config_Module}, //AT Test 2
    {"AT+QCFG=\"urc/ri/smsincoming\",\"pulse\",2000\r\n", "OK\r\n", "", "ERROR", "", 10000, 2, GSM_Config_Module}, //Set URC Ringtype
    {"AT+CNMI=2,1,0,0,0\r\n", "OK\r\n", "", "ERROR", "", 10000, 3, GSM_Config_Module}, // Config SMS event report
    {"AT+CMGF=1\r\n", "OK\r\n", "", "ERROR", "", 5000, 5, GSM_Config_Module}, //Set SMS to Text Mode
    {"AT\r\n", "OK\r\n", "", "ERROR", "", 3000, 5, GSM_Config_Module}, // AT Test
    {"AT+CGSN\r\n", "OK\r\n", "", "ERROR", "", 8000, 5, GSM_GET_IMEI_Buffer}, // Get IMEI
    {"AT+CIMI\r\n", "OK\r\n", "", "ERROR", "", 1000, 5, GSM_Config_Module}, // GET IMSI
    {"AT+QCCID\r\n", "QCCID", "OK\r\n", "ERROR", "", 3000, 3, GSM_Config_Module}, // Get ICCID
    {"AT+CPIN?\r\n", "+CPIN: READY\r\n", "OK\r\n", "ERROR", "", 3000, 3, GSM_Config_Module}, // Get state CPIN
    {"AT+QIDEACT=1\r\n", "OK\r\n", "", "ERROR", "", 3000, 3, GSM_Config_Module},// De-activate PDP
    {"AT\r\n", "OK\r\n", "", "ERROR", "", 5000, 2, GSM_Config_Module}, // AT Test
    {"AT+CGDCONT=1,\"IP\",\"v-internet\"\r\n", "OK\r\n", "", "ERROR", "", 3000, 5, GSM_Config_Module}, // Define PDP context
    {"AT+QIACT=1\r\n", "OK", "", "ERROR", "", 15000, 2, GSM_Config_Module}, //CSCS=GSM?
    {"AT+CGREG=2\r\n", "OK\r\n", "", "ERROR", "", 3000, 5, GSM_Config_Module}, //Network registration status
    {"AT+CGREG?\r\n", "OK\r\n", "", "ERROR", "", 3000, 5, GSM_Config_Module}, //Query network status
    {"AT+COPS?\r\n", "OK\r\n", "", "ERROR", "", 3000, 5, GSM_Config_Module}, //Query network operator
    {"AT\r\n", "OK\r\n", "", "ERROR", "", 3000, 5, GSM_Config_Module}, //AT Test
    {"AT+CSQ\r\n", "OK\r\n", "", "ERROR", "", 3000, 5, GSM_Config_Module}, //Get CSQ
    {"AT\r\n", "OK\r\n", "", "ERROR", "", 3000, 5, GSM_Config_Module}, // AT Test

};

void GSM_Config_Module (GSM_Response_Event_TypDef event, void *Resp_Buffer)
{
    uint8_t TableIndex = GSM_Manager.step;
    uint8_t TableSize = sizeof(atc_table_config_module)/sizeof(atc_table_config_module[0]);
    if(TableIndex >= TableSize)
    {
        return;
    }
    DEBUG_PrintResult_ATC(atc_table_config_module[TableIndex-1].cmd, (event == GSM_EVENT_OK)?"[OK]":"[FAIL]");
    GSM_SendCommand_AT(atc_table_config_module[TableIndex]);
    GSM_Manager.step++;
}
void GSM_mnr_task(void)
{
    GSM_Hardware_Layer_Run();
    Polling_GSM_StateMachine();
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
            default:
                DEBUG_WARN("Unhandled state %d.\r\n", GSM_Manager.state);
                break;
        }
    }
}
void GSM_Manager_ChangeState(uint8_t state)
{
    GSM_Manager.state = state;
    GSM_Manager.step = 0;
}
