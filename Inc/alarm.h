/**
  ******************************************************************************
  * File Name          : alarm.h
  * Description        : This file contains all the functions prototypes for
  *                      the alarm library
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

#ifndef __ALARM_H
#define __ALARM_H

#include "main.h"
#include "stm32f4xx_hal.h"

#define SENSOR_Port CZUJNIK_GPIO_Port
#define SENSOR CZUJNIK_Pin
#define BUZZER_Port BUZZER_GPIO_Port
#define BUZZER BUZZER_Pin

#define ALARM_TIME  6
#define DEBOUNCE_TIME  10

extern enum STATE ALARM;

/**
 * Indicates how many times should buzzer beep when alarming
 */
uint8_t buzzerCount;
/**
 * Used to debounce sensor
 */
uint8_t openCount;
/**
 * Used to debounce sensor
 */
uint8_t closeCount;

/**
 * Switching on buzzer
 */
void buzzer_on();
/**
 * Switching off buzzer
 */
void buzzer_off();
/**
 * Toggling buzzer state
 */
void buzzer_toggle();

/**
 * Checking if door is open or closed
 * @return door state
 */
GPIO_PinState sensor_read();

#endif /* __ALARM_H */
