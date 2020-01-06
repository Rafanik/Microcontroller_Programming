/**
  ******************************************************************************
  * File Name          : GSM.h
  * Description        : This file contains all the functions prototypes for
  *                      the GSM library
  * Authors			   : Rafał Szczepanik, Kacper Kaczmarek
  * Project            : University of Warsaw Project for subject
  * 					 "Programming Microcontrollers in C"
  * Github             : https://github.com/Rafanik/PMIK_microcontroller_programming
  ******************************************************************************
  *
  * No rights reserved
  *
  ******************************************************************************
  */
#ifndef __GSM_H
#define __GSM_H

//#include "main.h"
#include "stm32f4xx_hal.h"

char buffer[100]; // used to construct messages and commands
char enter;  // special sign - /n
char ctrlz;  // special sign - ctrl+Z
char GSM_buffer[300]; // buffer to collect received data from GSM
uint8_t GSM_buffer_index;
unsigned char GSM_Listener; // single sign received from GSM is stored there
UART_HandleTypeDef* huart;

void GSM_Init(UART_HandleTypeDef*);

void GSM_Listen(void); // Enable collecting data from GSM in buffer (UART Transmition)
void GSM_Send(char*); // Sending data to GSM (UART Transmition)
uint8_t GSM_CheckResponse(char*); // Checking response from GSM
uint8_t GSM_SendCommandAndWaitForResponse(char*, char*); // Sending command and checking response from GSM
uint8_t GSM_SendCommandAndCopyResponse(char*, char*, char*, char*); // Sending command and copying response from GSM, between begin and end
void GSM_GetDate(char*, char*, char*); // Receive Day, Month, Year from GSM
void GSM_GetTime(char*, char*, char*); // Receive Hours, Minutes, Seconds from GSM
void GSM_SendSMS(char*, char*); // Sending SMS (text) to a given number
uint8_t GSM_ReadSMS(char*, char*); // Reading SMS (text) and reading number


void HAL_UART_RxCpltCallback(UART_HandleTypeDef*);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef*);



#endif /* __GSM_H */
