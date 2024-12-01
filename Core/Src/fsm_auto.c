/*
 * fsm_auto.c
 *
 *  Created on: Nov 30, 2024
 *      Author: CAO NGUYEN
 */

#include "fsm_auto.h"
#include "graphic.h"

void fsm_init()
{
	redCounter = redDuration /1000;
	greenCounter = greenDuration /1000;
	amberCounter = amberDuration /1000;
	mode = 1;
}

void fsm_automatic_run(){

	if (isButtonPressed(0))
	{
		clearAllLed();
		status = MAN_RED;
		mode = 2;
		tempRed = redDuration;
		tempGreen = greenDuration;
		tempAmber = amberDuration;
		isButtonPressed(1);
		isButtonPressed(2);
	}
	switch (status)
	{
		case INIT:
			clearAllLed();
			fsm_init();
			status = RED_GREEN;

			break;
		case RED_GREEN:
			lcd_Clear(WHITE);
			lcdRedGreen();
			road1 = redCounter;
			road2 = greenCounter;

			redCounter--;
			greenCounter--;


			if (greenCounter <= 0)
			{
				status = RED_AMBER;
				amberCounter = amberDuration / 1000;
			}
			break;
		case RED_AMBER:
			lcd_Clear(WHITE);
			lcdRedAmber();

			road1 = redCounter;
			road2 = amberCounter;

			redCounter--;
			amberCounter--;

			if (redCounter <= 0)
			{
				status = GREEN_RED;

				redCounter = redDuration/1000;
				greenCounter = greenDuration/1000;

			}
			break;
		case GREEN_RED:
			lcd_Clear(WHITE);
			lcdGreenRed();

			road1 = greenCounter;
			road2 = redCounter;

			redCounter--;
			greenCounter--;

			if (greenCounter <= 0)
			{
				status = AMBER_RED;
				amberCounter = amberDuration/1000;

			}
			break;
		case AMBER_RED:
			lcd_Clear(WHITE);
			lcdAmberRed();


			road1 = amberCounter;
			road2 = redCounter;

			redCounter--;
			amberCounter--;

			if (redCounter <= 0)
			{
				status = RED_GREEN;

				redCounter = redDuration/1000;
				greenCounter = greenDuration/1000;

			}
			break;
		default:
			break;
	}
	if (mode == 1)
	{
		updateLedBuffer(road1, road2);
	}


}
