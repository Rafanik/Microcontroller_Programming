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
