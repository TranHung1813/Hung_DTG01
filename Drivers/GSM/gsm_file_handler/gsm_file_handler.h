#ifndef GSM_FILE_HANDLER_H
#define GSM_FILE_HANDLER_H

#include "gsm.h"

#define MAX_SIZE_AT_COMMAND  70
#define MAX_FILE_SEND_SIZE   50
#define MAX_NUMBER_MULTI_FILE_SEND 10 
typedef enum
{
    GSM_FILE_MODE_UPLOAD = 0,
    GSM_FILE_MODE_DOWNLOAD,

}GSM_FileHandler_Mode_TypDef;

typedef struct
{
    char* Hostname;
    char* Username;
    char* Password;
    uint32_t Port;
} FTP_Config_TypDef;
typedef struct
{
    char* Data;
    uint16_t DataLength;
    char* Name;
    char* Directory;
    uint16_t Index;
} GSM_FileSend_Info_TypDef;
typedef struct
{
    GSM_FileSend_Info_TypDef File[MAX_NUMBER_MULTI_FILE_SEND];
    uint8_t NumberFile;
    uint8_t FileID;  // Vi tri File gui di
}GSM_Multi_FileSend_Info_TypDef;
typedef struct
{
    GSM_FileHandler_Mode_TypDef mode;
    uint8_t step;
}GSM_FileHandler_Manager_TypDef;

void GSM_File_Handler_Init(FTP_Config_TypDef* cfg);
void GSM_Login_Server_Seq(GSM_Response_Event_TypDef event, void *Resp_Buffer);
void GSM_File_Transfer_Seq(GSM_Response_Event_TypDef event, void *Resp_Buffer);
void GSM_Send_File(GSM_Multi_FileSend_Info_TypDef *File_Info);
void GSM_Add_FileInfo_to_AT_Command(GSM_FileSend_Info_TypDef *File_Info);








#endif    /*GSM_FILE_HANDLER_H*/
