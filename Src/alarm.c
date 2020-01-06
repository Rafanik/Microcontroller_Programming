/**
  ******************************************************************************
  * File Name          : alarm.c
  * Description        : Library handling alarm functions
  * Authors			   : Rafał Szczepanik, Kacper Kaczmarek
  * Project            : University of Warsaw Project for subject "Programming Microcontrollers in C"
  * Github             : https://github.com/Rafanik/PMIK_microcontroller_programming
  ******************************************************************************
  *
  * No rights reserved
  *
  ******************************************************************************
  */


#include "alarm.h"
#include "stm32f4xx_hal.h"

enum STATE ALARM = NO;

void buzzer_on(){
	HAL_GPIO_WritePin(BUZZER_Port, BUZZER, RESET);
}

void buzzer_off(){
	HAL_GPIO_WritePin(BUZZER_Port, BUZZER, SET);
}

void buzzer_toggle(){
	HAL_GPIO_TogglePin(BUZZER_Port, BUZZER);
}

GPIO_PinState sensor_read(){
	 return HAL_GPIO_ReadPin(SENSOR_Port, SENSOR);
 }
