/*
 * graphic.c
 *
 *  Created on: Dec 1, 2024
 *      Author: CAO NGUYEN
 */


#include "graphic.h"
#include "led_7seg.h"



void lcdRedGreen(){
	lcd_DrawCircle(40, 180, RED, 20, 1);
	lcd_DrawCircle(160, 50, GREEN, 20, 1);
}
void lcdRedAmber(){
	lcd_DrawCircle(40, 180, RED, 20, 1);
	lcd_DrawCircle(120, 50, YELLOW, 20, 1);
}
void lcdGreenRed(){
	lcd_DrawCircle(40, 100, GREEN, 20, 1);
	lcd_DrawCircle(80, 50, RED, 20, 1);
}
void lcdAmberRed(){
	lcd_DrawCircle(40, 140, YELLOW, 20, 1);
	lcd_DrawCircle(80, 50, RED, 20, 1);
}

void updateLedBuffer(int value1, int value2)
{
	led7_SetDigit(value1/10, 0, 0);
	led7_SetDigit(value1%10, 1, 0);
	led7_SetDigit(value2/10, 2, 0);
	led7_SetDigit(value2%10, 3, 0);
}

void blinkingLed(enum LED led){
	switch(led){
	case RED_LED:
		lcd_Clear(WHITE);
		lcd_DrawCircle(40, 180, RED, 20, 1);
		lcd_DrawCircle(80, 50, RED, 20, 1);
		break;
	case GREEN_LED:
		lcd_Clear(WHITE);
		lcd_DrawCircle(40, 100, GREEN, 20, 1);
		lcd_DrawCircle(160, 50, GREEN, 20, 1);
		break;
	case AMBER_LED:
		lcd_Clear(WHITE);
		lcd_DrawCircle(120, 50, YELLOW, 20, 1);
		lcd_DrawCircle(40, 140, YELLOW, 20, 1);
		break;
	default:
		break;
	}
}
