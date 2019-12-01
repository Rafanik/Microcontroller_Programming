//******************************************************************************
//  Biblioteka obsługująca alarm - buzzer i czujnik otwarcia drzwi
//******************************************************************************


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
