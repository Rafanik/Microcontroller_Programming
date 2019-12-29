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
int random(int, int);
char keyboard_read(void);
uint8_t PIN_write(char);
void PIN_clear(void);
void PIN_display(void);
void PIN_clear_display(void);
uint8_t PIN_check(void);
void date_update_from_GSM(RTC_HandleTypeDef);
void check_one_time_PIN(void);
void send_alert(void);


#endif /* __PMIK_H */
