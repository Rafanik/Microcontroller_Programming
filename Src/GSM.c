//******************************************************************************
//  Biblioteka obsługująca alarm - buzzer i czujnik otwarcia drzwi
//******************************************************************************


#include "GSM.h"
#include "string.h"
//#include "stm32f4xx_hal.h"





void GSM_Send(unsigned char* text){

	strcpy((char*)buffer, (char*)text);
	buffer[strlen((char*)buffer)]=enter;
	buffer[strlen((char*)buffer)+1] = '\0';
	uint8_t length = strlen((char*)buffer);
	HAL_UART_Transmit_IT(huart, buffer, length);


}

void GSM_Listen(){
	HAL_UART_Receive_IT(huart, &GSM_Listener, 1);
	//HAL_UART_Receive_IT(huart, GSM_buffer, 3);
}

uint8_t GSM_CheckResponse(unsigned char* response){
	int i =0;
	while(strstr((char*)GSM_buffer, (char*)response)==NULL){
		if(i++>32000){
		//memset(GSM_buffer, 0, sizeof(GSM_buffer));
		//GSM_buffer_index=0;
		return 0;
		}
	}
	memset(GSM_buffer, 0, sizeof(GSM_buffer));
	GSM_buffer_index = 0;
	return 1;
}

uint8_t GSM_SendCommandAndWaitForResponse(unsigned char* command, unsigned char* response){
	GSM_Send(command);

	return GSM_CheckResponse(response);

}
	/* ewentualna obsluga jak nie znajdzie odp.*/


uint8_t GSM_SendCommandAndCopyResponse(unsigned char* command, unsigned char* begin, unsigned char* end, unsigned char* response){
	GSM_Send(command);
	char* start;
	char* stop;
	char* xd;

	int i =0;
		while(strstr((char*)GSM_buffer, (char*)begin)==NULL ||  strstr((char*)GSM_buffer, (char*)end)==NULL){
			if(i++>32000){
			memset(GSM_buffer, 0, sizeof(GSM_buffer));
			GSM_buffer_index=0;
			//memset(GSM_buffer, 0, sizeof(GSM_buffer));
			return 0;
			}
		}
	start = strstr((char*)GSM_buffer, (char*)begin);
	stop = strstr((char*)GSM_buffer, (char*)end);
	*stop = '\0';
	int correction = strlen(begin)*sizeof(unsigned char);
	start = start + correction;
	strcpy(response, start);

	memset(GSM_buffer, 0, sizeof(GSM_buffer));
	GSM_buffer_index=0;
	int x = 0;
	return 1;
}

void GSM_Init(UART_HandleTypeDef* h){
	enter = 10;
	ctrlz= 26;
	huart = h;
	GSM_buffer_index = 0;
	GSM_Listen();
	int i = 0;
	while(	GSM_SendCommandAndWaitForResponse((unsigned char*)"at", (unsigned char*)"OK") && i<20){
		++i;
	};
	i=0;
	while(	GSM_SendCommandAndWaitForResponse((unsigned char*)"at+cmgf=1", (unsigned char*)"OK") && i<20){
		++i;
	};

}

void GSM_SendSMS(unsigned char* number, unsigned char* message){

	uint8_t x = GSM_SendCommandAndWaitForResponse((unsigned char*)"at+cmgf=1", (unsigned char*)"OK");
	sprintf((char*)buffer, "at+cmgs=\"%s\"", number);
	uint8_t y = GSM_SendCommandAndWaitForResponse(buffer, (unsigned char*)">");

	memset(buffer, 0, sizeof(buffer));
	sprintf((char*)buffer, "%s%c", message, 0x1A);


	GSM_SendCommandAndWaitForResponse(buffer, (unsigned char*)"OK");
	memset(buffer, 0, sizeof(buffer));


}

void GSM_GetDate(char* year, char* month, char* day){
	  unsigned char response[30];
	  GSM_SendCommandAndCopyResponse("at+cclk?", "+CCLK:", "\"\r\n", response);
	  year[0]=response[2];
	  year[1]=response[3];
	  month[0]=response[5];
	  month[1]=response[6];
	  day[0]=response[8];
	  day[1]=response[9];
}

void GSM_GetTime(char* hours, char* minutes, char* seconds){
	  unsigned char response[30];
	  GSM_SendCommandAndCopyResponse("at+cclk?", "+CCLK:", "\"\r\n", response);
	  hours[0]=response[11];
	  hours[1]=response[12];
	  minutes[0]=response[14];
	  minutes[1]=response[15];
	  seconds[0]=response[17];
	  seconds[1]=response[18];
}

uint8_t GSM_ReadSMS(char* number, char* text){
	  unsigned char response[30];
	  int i = 0;
	  int status = 0;
	  while(	!GSM_SendCommandAndWaitForResponse((unsigned char*)"at+cmgf=1", (unsigned char*)"OK") && i<20){
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
		 		  status = GSM_SendCommandAndWaitForResponse((unsigned char*)"at+cmgd=8", (unsigned char*)"OK");
		 		  ++i;
		 		};
		  return 0;
	  }
	  status = 0;
	  i = 0;
	  while(	!status && i<20){
	 		  status = GSM_SendCommandAndWaitForResponse((unsigned char*)"at+cmgd=8", (unsigned char*)"OK");
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

