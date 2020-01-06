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

unsigned char time[17];
unsigned char date[17];

RTC_HandleTypeDef* hhrtc;

RTC_DateTypeDef sdatestructureget;
RTC_TimeTypeDef stimestructureget;

void date_time_init(RTC_HandleTypeDef*);
void date_get();
void time_get();
void date_time_to_display(unsigned char*, unsigned char*);
//void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *);
void display_date();

#endif /* __DATE_TIME_H */
