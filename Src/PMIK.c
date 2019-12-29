//******************************************************************************
//  Biblioteka obsługująca alarm - buzzer i czujnik otwarcia drzwi
//******************************************************************************


#include "keyboard_com_08653.h"
#include "stm32f4xx_hal.h"
#include "lcd_hd44780.h"
#include "alarm.h"
#include "PMIK.h"
#include "date_time.h"
#include "GSM.h"
#include "main.h"

#define PIN_LENGTH 4
unsigned char PIN_correct[PIN_LENGTH] = "4555";
unsigned char PIN_correct_2[PIN_LENGTH+1] = "5554";

unsigned char PIN[PIN_LENGTH+1];

uint8_t PINCounter;

RTC_TimeTypeDef sTime = {0};
RTC_DateTypeDef sDate = {0};

unsigned char text[40] = "607933865";
unsigned char number[40];
char alert[40];
char message[40];
char year[2];
char month[2];
char day[2];
char hours[2];
char minutes[2];
char seconds[2];

int random(int min, int max)
{
    int tmp;
    if (max>=min)
        max-= min;
    else
    {
        tmp= min - max;
        min= max;
        max= tmp;
    }
    return max ? (rand() % max + min) : min;
}
void generate_random_PIN(){
	for(int i =0; i<PIN_LENGTH; ++i){
	PIN_correct_2[i] = '0' + random(0,9);
	}
	PIN_correct_2[PIN_LENGTH]='\0';

}
void PIN_clear_display(){
	uint8_t i;
	unsigned char clear[PIN_LENGTH];
	for(i=0;i<PIN_LENGTH-1;i++){
		clear[i]=*" ";
	}
	clear[PIN_LENGTH-1] = 0;
	LCD_GoTo(0, 1);
	LCD_WriteText(clear);
}

void PIN_display(){
	LCD_Clear();
	PIN[PIN_LENGTH]=0;
	LCD_GoTo(0, 0);
	LCD_WriteText((unsigned char *)"PODAJ PIN:");
	LCD_GoTo(0, 1);
	LCD_WriteText(PIN);
}



void PIN_clear(){
	uint8_t i;
	for(i=0;i<PIN_LENGTH;i++){
		PIN[i]=0;
	}
	PINCounter=0;
}

uint8_t PIN_write(char character){
	//uint8_t temp;
	if( (character>='0' && character <= '9') || character=='*' || character=='#')
	{
		if(PINCounter>=PIN_LENGTH)
		{
			PINCounter=0;
		}
		PIN[PINCounter++]=character;
		DISPLAY = YES;
	}
	if(PINCounter == PIN_LENGTH)
		return 1;
	else
		return 0;
}

uint8_t PIN_check(){
	uint8_t i = 0;
	if(ONE_TIME_PIN==YES){
	for(i=0;i<PIN_LENGTH;i++){
		if(PIN[i]!=PIN_correct_2[i])
		break;
	}}
	if(i==PIN_LENGTH){
		ONE_TIME_PIN=NO;
		return 2;}

	for(i=0;i<PIN_LENGTH;i++){
		if(PIN[i]!=PIN_correct[i])
		break;
	}
	if(i==PIN_LENGTH)
		return 1;

	PINCounter=0;

	return 0;
}

void date_update_from_GSM(RTC_HandleTypeDef hrtc){


	  GSM_GetDate(year, month, day);
	  GSM_GetTime(hours, minutes, seconds);

	  sTime.Hours = atoi(hours);
	  sTime.Minutes = atoi(minutes);
	  sTime.Seconds = atoi(seconds);
	  sDate.Year = atoi(year);
	  sDate.Month = atoi(month);
	  sDate.Date = atoi(day);

	  HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	  HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
}

void send_alert(){

	GSM_GetDate(year, month, day);
	GSM_GetTime(hours, minutes, seconds);
	sprintf(alert, "Door alarm!!! %s:%s, %s-%s-20%s",hours, minutes, day, month, year );
	HAL_Delay(100);
	GSM_SendSMS("607933865", alert);
}

void check_one_time_PIN(){
	memset(text, 0, sizeof(text));
	memset(number, 0, sizeof(number));

 if(GSM_ReadSMS(number, text)){
	ONE_TIME_PIN=YES;
	 generate_random_PIN();
	 sprintf(message,"Your one-time PIN is: %s", PIN_correct_2);
	  GSM_SendSMS(text, message);
  }
}
