# include "gsm.h"

Gsm_Manager_TypDef GSM_Manager;

void GSM_Config_Module (GSM_Response_Event_TypDef event, void *Resp_Buffer)
{
    switch (GSM_Manager.step)
    {
        case 1:
            if(event != GSM_EVENT_OK)
            {
                SEGGER_RTT_printf(0,"Connect Module ERROR.\r\n");
                //GSM_Manager_ChangeState(GSM_STATE_RESET);
            }
            else
            {
                GSM_SendCommand_AT("ATE0\r\n", "OK\r\n","","","",3000,3,GSM_Config_Module);
            }
            break;
        case 2:
            SEGGER_RTT_printf(0,"Disable ECHO %s.\r\n",(event == GSM_EVENT_OK)?"OK":"FAIL");
            GSM_SendCommand_AT("AT+CMEE=2\r\n", "OK\r\n","","","",6000,5,GSM_Config_Module);
            break;
        case 3:
            SEGGER_RTT_printf(0,"Set up ERROR Message Format %s.\r\n",(event == GSM_EVENT_OK)?"OK":"FAIL");
            GSM_SendCommand_AT("ATI\r\n", "OK\r\n","","","",6000,5,GSM_Config_Module);
            break;
        case 4:
            SEGGER_RTT_printf(0,"Get Info Module %s.\r\n",(event == GSM_EVENT_OK)?"OK":"FAIL");
            GSM_SendCommand_AT("AT\r\n", "OK\r\n","","","",6000,5,GSM_Config_Module);
            break;
        case 5:
            SEGGER_RTT_printf(0,"AT Test 1 %s.\r\n",(event == GSM_EVENT_OK)?"OK":"FAIL");
            GSM_SendCommand_AT("AT\r\n", "OK\r\n","","","",3000,5,GSM_Config_Module);
            break;
        case 6:
            SEGGER_RTT_printf(0,"AT Test 2 %s.\r\n",(event == GSM_EVENT_OK)?"OK":"FAIL");
            GSM_SendCommand_AT("AT+QCFG=\"urc/ri/smsincoming\",\"pulse\",2000\r\n", "OK\r\n","","","",10000,2,GSM_Config_Module);
            break;
        case 7:
            SEGGER_RTT_printf(0,"Set URC Ringtype %s.\r\n",(event == GSM_EVENT_OK)?"OK":"FAIL");
            GSM_SendCommand_AT("AT+CNMI=2,1,0,0,0\r\n", "OK\r\n","","","",10000,3,GSM_Config_Module);
            break;
        case 8:
            SEGGER_RTT_printf(0,"Config SMS event report %s.\r\n",(event == GSM_EVENT_OK)?"OK":"FAIL");
            GSM_SendCommand_AT("AT+CMGF=1\r\n", "OK\r\n","","","",5000,5,GSM_Config_Module);
            break;
        case 9:
            SEGGER_RTT_printf(0,"Set SMS Format to Text mode %s.\r\n",(event == GSM_EVENT_OK)?"OK":"FAIL");
            GSM_SendCommand_AT("AT\r\n", "OK\r\n","","","",3000,5,GSM_Config_Module);
            break;
        case 10:
            SEGGER_RTT_printf(0,"AT Test %s.\r\n",(event == GSM_EVENT_OK)?"OK":"FAIL");
            GSM_SendCommand_AT("AT+CGSN\r\n", "OK\r\n","","","",8000,5,GSM_Config_Module);
            break;
        case 11:
            SEGGER_RTT_printf(0,"Get IMEI %s.\r\n",(event == GSM_EVENT_OK)?"OK":"FAIL");
            break;
    default:

        break;
    }
    GSM_Manager.step++;
}
void GSM_mnr_task(void)
{
    GSM_Hardware_Layer_Run();
    Polling_GSM_StateMachine();
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
                    GSM_SendCommand_AT("ATV1\r\n", "OK\r\n","","","",3000,5,GSM_Config_Module);
                }
                break;

            default:
                SEGGER_RTT_printf(0,"Unhandled state %d.\r\n", GSM_Manager.state);
                break;
        }
    }
}
void GSM_Manager_ChangeState(uint8_t state)
{
    GSM_Manager.state = state;
    GSM_Manager.step = 0;
}
