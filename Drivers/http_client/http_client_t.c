#include "http_client_t.h"

static HTTP_Client_Config_TypDef HTTP_Client_Config;
static httpc_connection_t HTTP_Connect_Settings;
// static uint32_t Total_Bytes_Recv = 0;
// static uint32_t Content_Length = 0;

static httpc_state_t* HTTP_Connection_State;
static HTTP_Manager_TypDef HTTP_Manager;

void HTTP_Client_Init(HTTP_Client_Config_TypDef *cfg)
{
    HTTP_Cleanup();
    memcpy(&HTTP_Client_Config, cfg, sizeof(HTTP_Client_Config_TypDef));
    HTTP_Manager.Step = HTTP_STEP_DISCONNECT;
    DEBUG_INFO("HTTP_STEP_DISCONNECT.\r\n");
}
void HTTP_Cleanup(void)
{
    //Total_Bytes_Recv = 0;
    //Content_Length = 0;
    memset(&HTTP_Client_Config, 0, sizeof(HTTP_Client_Config));
}
/**
 * @brief Header received done callback
 */
err_t HTTP_Headers_Done_Callback(httpc_state_t *connection, void *arg, struct pbuf *hdr, u16_t hdr_len, u32_t content_len)
{
    DEBUG_INFO("httpc_headers_callback, content length %d\r\n", content_len);
    //DEBUG_INFO("HTTP header %.*s\r\n", hdr->len, hdr->payload);

    if (content_len == 0xFFFFFFFF)
    {
        /*
            Content length không hợp lệ, có thể có những lí do sau
            	- Trong header server trả về không có trường "Content-Length"
            	- Server trả về dạng stream data, dữ liệu kết thúc khi server đóng kết nối
            	- Các lí do khác
        */
        DEBUG_INFO("Invalid content length\r\n");
    }
    else
    {
        DEBUG_INFO("HTTP content length %u bytes\r\n", content_len);
    }

    return ERR_OK;
}
/**
 * @brief Result transfer done callback
 */
static void HTTP_Result_Callback(void *arg, httpc_result_t httpc_result, u32_t rx_content_len, u32_t srv_res, err_t err)
{
    DEBUG_INFO("result: %d, content len: %d, status code: %d\r\n", httpc_result, rx_content_len, srv_res);
    switch (err)
    {
        case HTTPC_RESULT_OK: /** File successfully received */
        {
            DEBUG_INFO("HTTPC_RESULT_OK\r\n");
        }
            break;

        case HTTPC_RESULT_ERR_UNKNOWN:     /** Unknown error */
                                           //break;
        case HTTPC_RESULT_ERR_CONNECT:     /** Connection to server failed */
                                           //break;
        case HTTPC_RESULT_ERR_HOSTNAME:    /** Failed to resolve server hostname */
                                           //break;
        case HTTPC_RESULT_ERR_CLOSED:      /** Connection unexpectedly closed by remote server */
                                           //break;
        case HTTPC_RESULT_ERR_TIMEOUT:     /** Connection timed out (server didn't respond in time) */
                                           //break;
        case HTTPC_RESULT_ERR_SVR_RESP:    /** Server responded with an error code */
                                           //break;
        case HTTPC_RESULT_ERR_MEM:         /** Local memory error */
                                           //break;
        case HTTPC_RESULT_LOCAL_ABORT:     /** Local abort */
                                           //break;
        case HTTPC_RESULT_ERR_CONTENT_LEN: /** Content length mismatch */
            DEBUG_ERROR("Error content length\r\n");
            break;

        default:
            DEBUG_INFO("httpc_result_callback error %d\r\n", err);
            break;
    }
}
/** 
 * @brief Handle data connection incoming data
 * @param pointer to lwftp session data
 * @param pointer to PCB
 * @param pointer to incoming pbuf
 * @param state of incoming process
 */
static err_t HTTP_File_Receive_Callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *data_recv, err_t err)
{
    // Nếu có dữ liệu đến, kiểm tra buffer
    // Nếu buffer không hợp lệ (NULL) thì đóng kết nối TCP
    if (data_recv)
    {
        struct pbuf *q;
        for (q = data_recv; q; q = q->next)
        {
            // Đây là dữ liệu nhận về, có độ dài bằng q->len, và data là q->payload
            DEBUG_INFO("HTTP data length %u\r\n", q->len);
            DEBUG_INFO("HTTP data %.*s\r\n", q->len, q->payload);
        }
        tcp_recved(tpcb, data_recv->tot_len);
        pbuf_free(data_recv);
    }
    else
    {
        DEBUG_WARN("tcp_close\r\n");
        tcp_close(tpcb);
        return ERR_ABRT;
    }

    return ERR_OK;
}

void HTTP_Config(void)
{
    /* Init Http connection params */
    HTTP_Connect_Settings.use_proxy = 0;
    HTTP_Connect_Settings.headers_done_fn = HTTP_Headers_Done_Callback;
    HTTP_Connect_Settings.result_fn = HTTP_Result_Callback;

    DEBUG_INFO("HTTP url %s%s, port %d\r\n", HTTP_Client_Config.Url,
                                             HTTP_Client_Config.File,
                                             HTTP_Client_Config.Port);
}
void HTTP_Get_Data(void)
{
    // Kết nối HTTP
    err_t err = httpc_get_file_dns((const char*)HTTP_Client_Config.Url,
                                   HTTP_Client_Config.Port,
                                   HTTP_Client_Config.File,
                                   &HTTP_Connect_Settings,
                                   HTTP_File_Receive_Callback,
                                   NULL,
                                   &HTTP_Connection_State);
    HTTP_Connect_Settings.headers_done_fn = HTTP_Headers_Done_Callback;
    HTTP_Connect_Settings.result_fn = HTTP_Result_Callback;
    if(err != ERR_OK)
    {
        DEBUG_INFO("HTTP Get File DNS return %d\r\n", err);
    }
    else
    {
        DEBUG_INFO("HTTP Get File DNS successfully\r\n");
        //HTTP_Manager.Step = HTTP_STEP_CONNECTED;
        //DEBUG_INFO("HTTP_STEP_CONNECTED.\r\n");
    }
}
void HTTP_Client_Polling_Task(void *arg)
{
    //static uint32_t Last_time_get_data = 0, tick = 0;
    static uint32_t Last_Tick = 0;
    uint32_t Current_Tick = sys_get_tick_ms();

    if((Current_Tick - Last_Tick) >= (uint32_t)1000)
    {
        Last_Tick = Current_Tick;
    }
    else
    {
        return;
    }
    static bool HTTP_Allow = false;
    if(gsm_data_layer_is_ppp_connected())
    {
        if(HTTP_Allow == false)
        {
            HTTP_Allow = true;
            DEBUG_INFO("HTTP Thread started.\r\n");
        }
    }
    else
    {
        if(HTTP_Allow == true)
        {
            HTTP_Allow = false;
            DEBUG_INFO("HTTP Thread stopped.\r\n");
        }
    }
    if(HTTP_Allow)
    {
        switch (HTTP_Manager.Step)
        {
        case HTTP_STEP_DISCONNECT:
            HTTP_Manager.Step = HTTP_STEP_CONFIG;
            DEBUG_INFO("HTTP_STEP_CONFIG.\r\n");
            break;

        case HTTP_STEP_CONFIG:
            HTTP_Config();
            HTTP_Manager.Step = HTTP_STEP_CONNECTING;
            DEBUG_INFO("HTTP_STEP_CONNECTING.\r\n");
            break;

        case HTTP_STEP_CONNECTING:
            //tick = Current_Tick;

            HTTP_Get_Data();
            HTTP_Manager.Step = HTTP_STEP_CONNECTED;
//            if((tick - Last_time_get_data) >= (uint32_t)5000)
//            {
//                Last_time_get_data = tick;
//            }
            break;

        case HTTP_STEP_CONNECTED:

            break;

        default:
            break;
        }
    }
}
