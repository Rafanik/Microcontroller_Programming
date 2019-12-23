//******************************************************************************
//  Biblioteka obsługująca alarm - buzzer i czujnik otwarcia drzwi
//******************************************************************************


#include "date_time.h"
#include "stm32f4xx_hal.h"

void date_time_init(RTC_HandleTypeDef* rtc){
	hhrtc = rtc;
}

void date_get(){
	HAL_RTC_GetDate(hhrtc, &sdatestructureget, RTC_FORMAT_BIN);
}

void time_get(){
	HAL_RTC_GetTime(hhrtc, &stimestructureget, RTC_FORMAT_BIN);
}


void display_date(){
	sprintf((char*)time,"    %02d:%02d:%02d    ", stimestructureget.Hours, stimestructureget.Minutes, stimestructureget.Seconds);
	/* Display date Format: dd-mm-yy */
	sprintf((char*)date,"   %02d-%02d-%02d   ",sdatestructureget.Date, sdatestructureget.Month, 2000 + sdatestructureget.Year);
	LCD_GoTo(0, 1);
	LCD_WriteText(time);
	LCD_GoTo(0, 0);
	LCD_WriteText(date);

}

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *handle){
	if(handle == hhrtc){
		if(DATE==YES){
		// UWAGA najpierw time_get() potem date_get() - inaczej nie działa!!!
		 time_get();
		 date_get();
		 display_date();
		}
	}
}



