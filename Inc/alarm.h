//******************************************************************************
//    THE SOFTWARE INCLUDED IN THIS FILE IS FOR GUIDANCE ONLY.
//    AUTHOR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
//    OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
//    FROM USE OF THIS SOFTWARE.
//
//    PROGRAM ZAWARTY W TYM PLIKU PRZEZNACZONY JEST WYLACZNIE
//    DO CELOW SZKOLENIOWYCH. AUTOR NIE PONOSI ODPOWIEDZIALNOSCI
//    ZA ZADNE EWENTUALNE, BEZPOSREDNIE I POSREDNIE SZKODY
//    WYNIKLE Z JEGO WYKORZYSTANIA.
//******************************************************************************
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


uint8_t buzzerCount;
uint8_t openCount;
uint8_t closeCount;

void buzzer_on();
void buzzer_off();
void buzzer_toggle();

GPIO_PinState sensor_read();

#endif /* __ALARM_H */
