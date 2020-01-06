/**
  ******************************************************************************
  * File Name          : keyboard_com_08653.c
  * Description        : Library handling keyboard_com_08653 functions
  * Authors			   : Rafał Szczepanik, Kacper Kaczmarek
  * Project            : University of Warsaw Project for subject "Programming Microcontrollers in C"
  * Github             : https://github.com/Rafanik/PMIK_microcontroller_programming
  ******************************************************************************
  *
  * No rights reserved
  *
  ******************************************************************************
  */

#include "keyboard_com_08653.h"
#include "stm32f4xx_hal.h"

char keyboard_read(void){
		int columns[3] = {COL1, COL2, COL3};
		int rows[4] = {ROW1, ROW2, ROW3, ROW4};
		unsigned int GPIO_Pin_row, GPIO_Pin_col, i, j;
		const unsigned char KBkody[12] = {'1','2','3',\
								  '4','5','6',\
								  '7','8','9',\
								  '*','0','#'};
		HAL_GPIO_WritePin(KeyGPIO, COL1| COL2| COL3, SET);
		for(i=0;i<3;++i){
			GPIO_Pin_col = columns[i];
			HAL_GPIO_WritePin(KeyGPIO, GPIO_Pin_col, RESET);
			HAL_Delay(10); // opoznienie 10 ms na ustalenie sygnalow
			for(j=0;j<4;++j){
				GPIO_Pin_row = rows[j];
				if(HAL_GPIO_ReadPin(KeyGPIO, GPIO_Pin_row) == 0){
					HAL_GPIO_WritePin(KeyGPIO, COL1|COL2|COL3, RESET);
					return KBkody[3*j+i];
				}
			}
			HAL_GPIO_WritePin(KeyGPIO, GPIO_Pin_col, SET);
		}
		HAL_GPIO_WritePin(KeyGPIO, COL1|COL2|COL3, RESET);
		return 0;
	}


