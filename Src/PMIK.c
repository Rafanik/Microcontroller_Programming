//******************************************************************************
//  Biblioteka obsługująca alarm - buzzer i czujnik otwarcia drzwi
//******************************************************************************


#include "keyboard_com_08653.h"
#include "stm32f4xx_hal.h"
#include "lcd_hd44780.h"
#include "alarm.h"
#include "PMIK.h"

#define PIN_LENGTH 4
unsigned char PIN_correct[PIN_LENGTH] = "4555";
unsigned char PIN_correct_2[PIN_LENGTH] = "5554";

unsigned char PIN[PIN_LENGTH+1];

uint8_t PINCounter;

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
	uint8_t i;
	for(i=0;i<PIN_LENGTH;i++){
		if(PIN[i]!=PIN_correct_2[i])
		break;
	}
	if(i==PIN_LENGTH)
		return 2;

	for(i=0;i<PIN_LENGTH;i++){
		if(PIN[i]!=PIN_correct[i])
		break;
	}
	if(i==PIN_LENGTH)
		return 1;

	PINCounter=0;

	return 0;


}
