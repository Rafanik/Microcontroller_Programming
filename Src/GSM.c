/**
  ******************************************************************************
  * File Name          : GSM.c
  * Description        : Library handling GSM Module communication functions
  * Authors			   : Rafał Szczepanik, Kacper Kaczmarek
  * Project            : University of Warsaw Project for subject "Programming Microcontrollers in C"
  * Github             : https://github.com/Rafanik/PMIK_microcontroller_programming
  ******************************************************************************
  *
  * No rights reserved
  *
  ******************************************************************************
  */

#include "GSM.h"
#include "string.h"
#include "stdio.h"

void GSM_Listen(){
	HAL_UART_Receive_IT(huart, &GSM_Listener, 1);
}

void GSM_Send(char* text){
	strcpy((char*)buffer, (char*)text);
	buffer[strlen((char*)buffer)]=enter;
	buffer[strlen((char*)buffer)+1] = '\0';
	uint8_t length = strlen((char*)buffer);
	HAL_UART_Transmit_IT(huart, (unsigned char*)buffer, length);
}

uint8_t GSM_CheckResponse(char* response){
	int i =0;
	while(strstr((char*)GSM_buffer, (char*)response)==NULL){
		// wait for correct response
		if(i++>32000){
		// timeout
		return 0;
		}
	}
	memset(GSM_buffer, 0, sizeof(GSM_buffer));
	GSM_buffer_index = 0;
	return 1;
}

uint8_t GSM_SendCommandAndWaitForResponse(char* command, char* response){
	GSM_Send(command);
	return GSM_CheckResponse(response);
}

uint8_t GSM_SendCommandAndCopyResponse(char* command, char* begin, char* end, char* response){
	GSM_Send(command);
	char* start;
	char* stop;
	int i =0;
		while(strstr((char*)GSM_buffer, (char*)begin)==NULL ||  strstr((char*)GSM_buffer, (char*)end)==NULL){
			if(i++>32000){
			// timeout
			memset(GSM_buffer, 0, sizeof(GSM_buffer));
			GSM_buffer_index=0;
			return 0;
			}
		}
	start = strstr((char*)GSM_buffer, (char*)begin);
	stop = strstr((char*)GSM_buffer, (char*)end);
	// setting correction - jump over chars in 'begin' string
	int correction = strlen((char*)begin)*sizeof(unsigned char);
	start = start + correction;
	// setting value of stop pointer to /0 in order to use strcpy (\0 - end of string)
	*stop = '\0';
	strcpy(response, start);
	memset(GSM_buffer, 0, sizeof(GSM_buffer));
	GSM_buffer_index=0;
	return 1;
}

void GSM_Init(UART_HandleTypeDef* h){
	enter = 10;
	ctrlz= 0x1A;
	huart = h;
	GSM_buffer_index = 0;
	GSM_Listen();
	int i = 0;
	while(	GSM_SendCommandAndWaitForResponse("at", "OK") && i<20){
		++i;
	};
	i=0;
	while(	GSM_SendCommandAndWaitForResponse("at+cmgf=1", "OK") && i<20){
		++i;
	};

}

void GSM_SendSMS(char* number, char* message){

	GSM_SendCommandAndWaitForResponse("at+cmgf=1", "OK");
	sprintf(buffer, "at+cmgs=\"%s\"", number);
	//HAL_Delay(500);
	uint8_t y = GSM_SendCommandAndWaitForResponse((char*)buffer, ">");
	// sometimes GSM simply doesn't response at first time
	if(y==0){
		y = GSM_SendCommandAndWaitForResponse(buffer, ">");
	}
	if(y==0){
		y = GSM_SendCommandAndWaitForResponse(buffer, ">");
	}
	if(y==0){
		y = GSM_SendCommandAndWaitForResponse(buffer, ">");
	}
	memset(buffer, 0, sizeof(buffer));
	sprintf((char*)buffer, "%s%c", message, 0x1A);
	GSM_SendCommandAndWaitForResponse(buffer,"OK");
	memset(buffer, 0, sizeof(buffer));
}

void GSM_GetDate(char* year, char* month, char* day){
	  char response[30];
	  GSM_SendCommandAndCopyResponse("at+cclk?", "+CCLK:", "\"\r\n", response);
	  year[0]=response[2];
	  year[1]=response[3];
	  month[0]=response[5];
	  month[1]=response[6];
	  day[0]=response[8];
	  day[1]=response[9];
}

void GSM_GetTime(char* hours, char* minutes, char* seconds){
	  char response[30];
	  GSM_SendCommandAndCopyResponse("at+cclk?", "+CCLK:", "\"\r\n", response);
	  hours[0]=response[11];
	  hours[1]=response[12];
	  minutes[0]=response[14];
	  minutes[1]=response[15];
	  seconds[0]=response[17];
	  seconds[1]=response[18];
}

uint8_t GSM_ReadSMS(char* number, char* text){
	  int i = 0;
	  int status = 0;
	  while(	!GSM_SendCommandAndWaitForResponse("at+cmgf=1", "OK") && i<20){
		  ++i;
		};
	  if(i==20) return 0;
	  status = 0;
	  i = 0;
	  while(!GSM_SendCommandAndCopyResponse("at+cmgr=8", "\"\r\n", "\r\n\r\nOK", text) && i<20){
		  ++i;
	  };
	  if(i==20) return 0;
	  i = 0;
	  status = 0;
	  while(!status && i<20){
		  status = GSM_SendCommandAndCopyResponse("at+cmgr=8", "READ\",\"", "\",\"\",\"", number);
		  ++i;
	  };
	  if(i==20) {
		  while(!status && i<20){
		 		  status = GSM_SendCommandAndWaitForResponse("at+cmgd=8", "OK");
		 		  ++i;
		 		};
		  return 0;
	  }
	  status = 0;
	  i = 0;
	  while(	!status && i<20){
	 		  status = GSM_SendCommandAndWaitForResponse("at+cmgd=8", "OK");
	 		  ++i;
	 		};
	  return 1;

}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *h) {

	if(h == huart){
			GSM_buffer[GSM_buffer_index] = GSM_Listener;
			++GSM_buffer_index;
			GSM_Listen();
		}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *h) {
	if(h == huart){

		}
}

