/**
  ******************************************************************************
  * File Name          : date_time.h
  * Description        : This file contains all the functions prototypes for
  *                      the date_time library
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
#ifndef __DATE_TIME_H
#define __DATE_TIME_H

#include "main.h"
#include "stm32f4xx_hal.h"

/**
 * Array to store time from RTC to be displayed on LCD
 */
unsigned char time[17];
/**
 * Array to store date from RTC to be displayed on LCD
 */
unsigned char date[17];
/**
 * RTC Handler
 */
RTC_HandleTypeDef* hhrtc;
/**
 * RTC date structure
 */
RTC_DateTypeDef sdatestructureget;
/**
 * RTC time structure
 */
RTC_TimeTypeDef stimestructureget;

/**
 * Initialization of library - appropriate RTC Handler
 * @param RTC Handler
 */
void date_time_init(RTC_HandleTypeDef*);
/**
 * Updating date structure with current date value from RTC
 */
void date_get();
/**
 * Updating time structure with current date value from RTC
 */
void time_get();

//void date_time_to_display(unsigned char*, unsigned char*);
//void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *);
/**
 * Displaying date and time on LCD
 */
void display_date();

#endif /* __DATE_TIME_H */
