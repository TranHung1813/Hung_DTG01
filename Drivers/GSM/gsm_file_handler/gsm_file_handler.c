#include "gsm_file_handler.h"

// #define FTP_Username "ezyro_32948978"
// #define FTP_Password "h4wxgr0btmru"
// #define FTP_Hostname "ftpupload.net"
// #define FTP_Port     21

static char Account_Info_AT_Command[MAX_SIZE_AT_COMMAND];
static char FTP_Server_Login_Info_AT_Command[MAX_SIZE_AT_COMMAND];
static char Upload_File_AT_Command[MAX_SIZE_AT_COMMAND];
static char Get_File_Size_AT_Command[MAX_SIZE_AT_COMMAND];
static char Set_Directory_AT_Command[MAX_SIZE_AT_COMMAND];
static char Upload_File_Data[MAX_FILE_SEND_SIZE];
static FTP_Config_TypDef File_Handler_Config;
static GSM_FileHandler_Manager_TypDef File_Handler_Manager;
static GSM_Multi_FileSend_Info_TypDef FileSend_Info;

void GSM_FileSend_Handler(GSM_Response_Event_TypDef event, void *Resp_Buffer);

const GSM_ATCommand_Table_TypDef ATC_Table_Login_Server[] =
{
     // Set APN
    {"AT+QICSGP=1,1,\"v-internet\",\"\",\"\",1\r\n", "OK\r\n", "", "ERROR", "", 6000, 5, GSM_Login_Server_Seq},
    // Activate PDP context 1
    {"AT+QIACT?\r\n","OK\r\n","","", "", 6000, 3, GSM_Login_Server_Seq},
    // Set the PDP context ID as 1
    {"AT+QFTPCFG=\"contextid\",1\r\n", "OK\r\n", "", "ERROR", "", 6000, 3, GSM_Login_Server_Seq},
    // Set username, password
    {Account_Info_AT_Command, "OK\r\n", "", "ERROR", "", 6000, 3, GSM_Login_Server_Seq},
    // Set file type as ASCII.
    {"AT+QFTPCFG=\"filetype\",1\r\n", "OK\r\n", "", "ERROR", "", 6000, 3, GSM_Login_Server_Seq},
    // Set transfer mode as passive mode
    {"AT+QFTPCFG=\"transmode\",1\r\n", "OK\r\n", "", "ERROR", "", 6000, 3, GSM_Login_Server_Seq},
    // Set the maximum response time as default 90 second
    {"AT+QFTPCFG=\"rsptimeout\",90\r\n", "OK\r\n", "", "ERROR", "", 6000, 3, GSM_Login_Server_Seq},
    // Login to FTP Server
    {FTP_Server_Login_Info_AT_Command, "OK\r\n", "+QFTPOPEN: 0,0\r\n", "", "", 15000, 3, GSM_Login_Server_Seq},
};
const GSM_ATCommand_Table_TypDef ATC_Table_File_Tranfer[] =
{
    // Set current directory
    {Set_Directory_AT_Command, "OK\r\n", "+QFTPCWD: 0,0\r\n", "ERROR", "", 10000, 3, GSM_File_Transfer_Seq},
    // Get the status of FTP Server
    {"AT+QFTPSTAT\r\n", "OK\r\n", "", "ERROR", "", 6000, 3, GSM_File_Transfer_Seq},
    /// Get the file name of current directory
    {"AT+QFTPNLST=\".\"\r\n", "OK\r\n", "", "ERROR", "", 6000, 3, GSM_FileSend_Handler},
    // Upload file via COM Port
    {Upload_File_AT_Command, "CONNECT\r\n", "", "", "", 7000, 3, GSM_File_Transfer_Seq},
    // Upload File's data
    {Upload_File_Data, "+QFTPPUT: 0,", "", "ERROR", "", 6000, 3, GSM_File_Transfer_Seq},
    // Get the Length of Transferred Data 
    {"AT+QFTPLEN\r\n", "+QFTPLEN: 0", "", "ERROR", "", 6000, 3, GSM_File_Transfer_Seq},
    // Query the size of file on FTP server.
    {Get_File_Size_AT_Command, "+QFTPSIZE:", "", "ERROR", "", 6000, 3, GSM_File_Transfer_Seq},
};

void GSM_File_Handler_Init(FTP_Config_TypDef* cfg)
{
    memcpy(&File_Handler_Config, cfg, sizeof(FTP_Config_TypDef));
    snprintf(Account_Info_AT_Command, sizeof(Account_Info_AT_Command), "%s%s%s%s%s",
                                                                    "AT+QFTPCFG=\"account\",\"",
                                                                    File_Handler_Config.Username,
                                                                    "\",\"",
                                                                    File_Handler_Config.Password,
                                                                    "\"\r\n");
    snprintf(FTP_Server_Login_Info_AT_Command, sizeof(FTP_Server_Login_Info_AT_Command), "%s%s%s%lu%s",
                                                                    "AT+QFTPOPEN=\"",
                                                                    File_Handler_Config.Hostname,
                                                                    "\",",
                                                                    File_Handler_Config.Port,
                                                                    "\r\n");
}
// Xu ly File Send ( Neu File chua ton tai tren server-> tao moi, neu da ton tai -> append)
void GSM_FileSend_Handler(GSM_Response_Event_TypDef event, void *Resp_Buffer)
{
    static uint8_t step = 0;
    switch (step)
    {
    case 0:
        if(event != GSM_EVENT_OK)
        {
            GSM_File_Transfer_Seq(event, &Resp_Buffer);
        }
        else
        {
            DEBUG_RAW("%s\r\n", (char*)Resp_Buffer);
            if(gsm_utilities_is_file_exist(FileSend_Info.File[FileSend_Info.FileID].Name, (char*)Resp_Buffer))
            {
                // Get size of exist file
                GSM_ATCommand_Table_TypDef AT_Command = 
                {
                    Get_File_Size_AT_Command,
                    "+QFTPSIZE: ", "",
                    "ERROR", "",
                    6000, 3,
                    GSM_FileSend_Handler,
                };
                GSM_SendCommand_AT(AT_Command);
                step++;
            }
            else
            {
                FileSend_Info.File[FileSend_Info.FileID].Index = 0;
                DEBUG_INFO("File does not exist -> Create new file!\r\n");
                GSM_File_Transfer_Seq(event, &Resp_Buffer);
            }
        }
        break;
    case 1:
        if(event == GSM_EVENT_OK)
        {
            step = 0;
            // Lay file size cua file da ton tai de Write Append 
            FileSend_Info.File[FileSend_Info.FileID].Index = gsm_utilities_get_number_from_string(21, (char*)Resp_Buffer);
            DEBUG_INFO("File exist, size %d bytes.\r\n", FileSend_Info.File[FileSend_Info.FileID].Index);
            // Set File Index
            snprintf(Upload_File_AT_Command, sizeof(Upload_File_AT_Command), "%s%s%s%d%s%d%s",
                                                        "AT+QFTPPUT=\"",
                                                        FileSend_Info.File[FileSend_Info.FileID].Name,
                                                        "\",\"COM:\",",
                                                        FileSend_Info.File[FileSend_Info.FileID].Index,
                                                        ",",
                                                        FileSend_Info.File[FileSend_Info.FileID].DataLength,
                                                        ",1\r\n");
            GSM_File_Transfer_Seq(event, NULL);
        }
        else
        {
            GSM_Manager_ChangeState(GSM_STATE_RESET);
        }
        break;
    default:
        break;
    } 
}
void GSM_Login_Server_Seq(GSM_Response_Event_TypDef event, void *Resp_Buffer)
{
    uint8_t TableIndex = File_Handler_Manager.step;
    const static uint8_t TableSize = sizeof(ATC_Table_Login_Server)/sizeof(ATC_Table_Login_Server[0]);
    if(TableIndex > TableSize)
    {
        return;
    }
    DEBUG_PrintResult_ATC(ATC_Table_Login_Server[TableIndex-1].cmd, (event == GSM_EVENT_OK)?"[OK]":"[FAIL]");
    DEBUG_RAW("%s\r\n", (char*)Resp_Buffer);
    if(event == GSM_EVENT_OK)
    {
        if(TableIndex < TableSize)
        {
            GSM_SendCommand_AT(ATC_Table_Login_Server[TableIndex]);
        }
        else
        {
            // Da Login Server xong
            File_Handler_Manager.step = 0;
            DEBUG_INFO("Log in server DONE.\r\n");
            if(File_Handler_Manager.mode == GSM_FILE_MODE_UPLOAD)
            {
                // Chuyen sang Mode Download
                FileSend_Info.FileID = 0;
                GSM_Add_FileInfo_to_AT_Command(&FileSend_Info.File[FileSend_Info.FileID]);
                GSM_SendCommand_AT(ATC_Table_File_Tranfer[0]);
            }
        }
        File_Handler_Manager.step++;
    }
    else //if(event == GSM_EVENT_TIMEOUT)
    {
        //GSM_Manager_ChangeState(GSM_STATE_RESET);
    }
}
void GSM_File_Transfer_Seq(GSM_Response_Event_TypDef event, void *Resp_Buffer)
{
    uint8_t TableIndex = File_Handler_Manager.step;
    const static uint8_t TableSize = sizeof(ATC_Table_File_Tranfer)/sizeof(ATC_Table_File_Tranfer[0]);
    if(TableIndex > TableSize)
    {
        return;
    }
    DEBUG_PrintResult_ATC(ATC_Table_File_Tranfer[TableIndex-1].cmd, (event == GSM_EVENT_OK)?"[OK]":"[FAIL]");
    DEBUG_RAW("%s\r\n", (char*)Resp_Buffer);
    if(event == GSM_EVENT_OK)
    {
        if(TableIndex < TableSize)
        {
            GSM_SendCommand_AT(ATC_Table_File_Tranfer[TableIndex]);
        }
        else
        {
            // Da Transfer File xong
            File_Handler_Manager.step = 0;
            DEBUG_INFO("File %d: %s Transfer DONE.\r\n", FileSend_Info.FileID + 1,
                                                         FileSend_Info.File[FileSend_Info.FileID].Name);
            // Bat dau chuyen file tiep theo
            if(++FileSend_Info.FileID >= FileSend_Info.NumberFile)
            {
                DEBUG_INFO("All File Transfer DONE.\r\n");
            }
            else
            {
                GSM_Add_FileInfo_to_AT_Command(&FileSend_Info.File[FileSend_Info.FileID]);
                GSM_SendCommand_AT(ATC_Table_File_Tranfer[0]);
            }
        }
        File_Handler_Manager.step++;
    }
    else //if(event == GSM_EVENT_TIMEOUT)
    {
        //GSM_Manager_ChangeState(GSM_STATE_RESET);
    }
}
void GSM_Add_FileInfo_to_AT_Command(GSM_FileSend_Info_TypDef *File_Info)
{
    // Set File Name
    snprintf(Upload_File_AT_Command, sizeof(Upload_File_AT_Command), "%s%s%s%d%s%d%s",
                                                                "AT+QFTPPUT=\"",
                                                                File_Info->Name,
                                                                "\",\"COM:\",",
                                                                File_Info->Index,
                                                                ",",
                                                                File_Info->DataLength,
                                                                ",1\r\n");
    // snprintf(Upload_File_AT_Command, sizeof(Upload_File_AT_Command), "%s%s%s%s",
    //                                                         "AT+QFTPPUT=\"",
    //                                                         FileSend_Info.Name,
    //                                                         "\",\"COM:\",",
    //                                                         "0,20,1\r\n");                                                     
    // Set File Data
    snprintf(Upload_File_Data, sizeof(Upload_File_Data), "%s%s", File_Info->Data, "\r\n");
    // Set Commamd Get File Size
    snprintf(Get_File_Size_AT_Command, sizeof(Get_File_Size_AT_Command), "%s%s%s",
                                                                "AT+QFTPSIZE=\"",
                                                                File_Info->Name,
                                                                "\"\r\n");
    // Set File Directory
    snprintf(Set_Directory_AT_Command, sizeof(Set_Directory_AT_Command), "%s%s%s",
                                                                "AT+QFTPCWD=\"",
                                                                File_Info->Directory,
                                                                "\"\r\n");
}
void GSM_Send_File(GSM_Multi_FileSend_Info_TypDef *File_Info)
{
    memcpy(&FileSend_Info, File_Info, sizeof(GSM_Multi_FileSend_Info_TypDef));
    if(File_Handler_Manager.step == 0)
    {
        File_Handler_Manager.step = 1;
        GSM_SendCommand_AT(ATC_Table_Login_Server[0]);
        File_Handler_Manager.mode = GSM_FILE_MODE_UPLOAD;
    }
}

