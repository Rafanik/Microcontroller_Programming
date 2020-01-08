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
/**
 * Buffer used to construct messages and commands
 */
char buffer[100];
/**
 * Special sign - /n
 */
char enter;
/**
 * Special sign - ctrl+Z
 */
char ctrlz;
/**
 * Buffer to collect received data from GSM
 */
char GSM_buffer[300];
/**
 * GSM_buffer index used to indicate where new data from GSM should be written
 */
uint8_t GSM_buffer_index;
/**
 * Single sign received from GSM is stored there
 */
unsigned char GSM_Listener;
/**
 * UART Handler
 */
UART_HandleTypeDef* huart;

/**
 * Initialization of library - checking connection via UART
 * @param UART Handler
 */
void GSM_Init(UART_HandleTypeDef*);
/**
 * Enable collecting data from GSM in buffer (UART Transmition)
 */
void GSM_Listen(void);
/**
 * Sending data to GSM (UART Transmition)
 * @param data
 */
void GSM_Send(char*);
/**
 * Checking if response from GSM is present in GSM_buffer
 * @param response
 * @return boolean: 1 - response found; 0 - response not found
 */
uint8_t GSM_CheckResponse(char*);
/**
 * Sending command and checking response from GSM
 * @param command
 * @param response
 * @return boolean: 1 - response found; 0 - response not found
 */
uint8_t GSM_SendCommandAndWaitForResponse(char*, char*);
/**
 * Sending command checking response from GSM, copying array between begin and end
 * @param command
 * @param begin
 * @param end
 * @param response
 * @return boolean: 1 - response found and copied; 0 - response not found/ not copied
 */
uint8_t GSM_SendCommandAndCopyResponse(char*, char*, char*, char*);
/**
 * Receive Day, Month, Year from GSM
 * @param Day
 * @param Month
 * @param Year
 */
void GSM_GetDate(char*, char*, char*);
/**
 * Receive Hours, Minutes, Seconds from GSM
 * @param Hours
 * @param Minutes
 * @param Seconds
 */
void GSM_GetTime(char*, char*, char*);
/**
 * Sending SMS (text) to a given number
 * @param number
 * @param text
 */
void GSM_SendSMS(char*, char*);
/**
 * Reading SMS (text) and reading number
 * @param number
 * @param text
 * @return boolean: 1 - succefully read; 0 - not read
 */
uint8_t GSM_ReadSMS(char*, char*);

/**
 * UART Received data interrupt callback
 * @param UART Handler
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef*);
/**
 * UART Send data interrupt callback
 * @param UART Handler
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef*);



#endif /* __GSM_H */
