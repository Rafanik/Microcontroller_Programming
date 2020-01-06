/**
  ******************************************************************************
  * File Name          : PMIK.h
  * Description        : This file contains all the functions prototypes for
  *                      the PMIK library
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
#ifndef __PMIK_H
#define __PMIK_H

#include "main.h"
#include "stm32f4xx_hal.h"

#define KeyGPIO GPIOB
#define COL1 COL1_Pin
#define COL2 COL2_Pin
#define COL3 COL3_Pin
#define ROW1 ROW1_Pin
#define ROW2 ROW2_Pin
#define ROW3 ROW3_Pin
#define ROW4 ROW4_Pin

#define DEBOUNCE_TIME  10

enum STATE ONE_TIME_PIN;
int random(int, int); // generating random number from given range
void generate_random_PIN(void); // generates random PIN and put it in PIN_CORRECT_2 array
void PIN_clear_display(void); // clears PIN and display
uint8_t PIN_write(char); // adds new digit to pin array
void PIN_clear(void); // clears pin array
void PIN_display(void); // displays pin on lcd
uint8_t PIN_check(void); // check if pin is correct and return if it is state pin or one-time pin
void date_update_from_GSM(RTC_HandleTypeDef);
void check_one_time_PIN(void); // checks if in gsmbuffer is request to generate new one-time pin
void send_alert(void); // sends alert to master with info about alarm


#endif /* __PMIK_H */
