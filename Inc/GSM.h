//******************************************************************************
//    THE SOFTWARE INCLUDED IN THIS FILE IS FOR GUIDANCE ONLY.
//    AUTHOR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
//    OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
//    FROM USE OF THIS SOFTWARE.
//
//    PROGRAM ZAWARTY W TYM PLIKU PRZEZNACZONY JEST WYLACZNIE
//    DO CELOW SZKOLENIOWYCH. AUTOR NIE PONOSI ODPOWIEDZIALNOSCI
//    ZA ZADNE EWENTUALNE, BEZPOSREDNIE I POSREDNIE SZKODY
//    WYNIKLE Z JEGO WYKORZYSTANIA.
//******************************************************************************
#ifndef __GSM_H
#define __GSM_H

//#include "main.h"
#include "stm32f4xx_hal.h"

unsigned char buffer[100];
unsigned char enter;
unsigned char ctrlz;
unsigned char GSM_buffer[300];
uint8_t GSM_buffer_index;
unsigned char GSM_Listener;
UART_HandleTypeDef* huart;

void GSM_Init(UART_HandleTypeDef*);
void GSM_Listen(void);
void GSM_Send(unsigned char*);
uint8_t GSM_CheckResponse(unsigned char*);
uint8_t GSM_SendCommandAndWaitForResponse(unsigned char*, unsigned char*);
uint8_t GSM_SendCommandAndCopyResponse(unsigned char*, unsigned char*, unsigned char*, unsigned char*);
void GSM_GetDate(char*, char*, char*);
void GSM_GetTime(char*, char*, char*);
void GSM_SendSMS(unsigned char*, unsigned char*);
uint8_t GSM_ReadSMS(char*, char*);


void HAL_UART_RxCpltCallback(UART_HandleTypeDef*);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef*);



#endif /* __GSM_H */
