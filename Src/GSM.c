//******************************************************************************
//  Biblioteka obsługująca alarm - buzzer i czujnik otwarcia drzwi
//******************************************************************************


#include "GSM.h"
#include "string.h"
//#include "stm32f4xx_hal.h"



void GSM_Init(UART_HandleTypeDef* h){
	enter = 10;
	ctrlz= 26;
	huart = h;
	GSM_buffer_index = 0;
	GSM_Listen();

}

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

void GSM_SendCommandAndWaitForResponse(unsigned char* command, unsigned char* response){
	GSM_Send(command);

	if(GSM_CheckResponse(response)){
		int test = 0;
		test= 1;
	}else{

	};
	/* ewentualna obsluga jak nie znajdzie odp.*/

}

void GSM_SendSMS(unsigned char* number, unsigned char* message){

	GSM_SendCommandAndWaitForResponse((unsigned char*)"at+cmgf=1", (unsigned char*)"OK");
	sprintf((char*)buffer, "at+cmgs=\"%s\"\n", number);
	GSM_SendCommandAndWaitForResponse(buffer, (unsigned char*)">");

	memset(buffer, 0, sizeof(buffer));
	sprintf((char*)buffer, "%s%c", message, 0x1A);


	GSM_SendCommandAndWaitForResponse(buffer, (unsigned char*)"OK");
	memset(buffer, 0, sizeof(buffer));


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

