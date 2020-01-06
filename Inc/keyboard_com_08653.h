/**
  ******************************************************************************
  * File Name          : keyboard_com_08653.h
  * Description        : This file contains all the functions prototypes for
  *                      the keyboard_com_08653 library
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
#ifndef __KEYBOARD_COM_08653_H
#define __KEYBOARD_COM_08653_H

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

char keyboard_read(void);

#endif /* __KEYBOARD_COM_08653_H */
