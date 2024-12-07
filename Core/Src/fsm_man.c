/*
 * fsm_man.c
 *
 *  Created on: Nov 30, 2024
 *      Author: CAO NGUYEN
 */




#include "fsm_man.h"

void fsm_manual_run()
{
	switch (status)
	{
		case MAN_RED:
			blinkingLed(RED_LED);
			updateLedBuffer(mode, tempRed / 1000);
			break;
		case MAN_AMBER:
			blinkingLed(AMBER_LED);
			updateLedBuffer(mode, tempAmber / 1000);
			break;
		case MAN_GREEN:
			blinkingLed(GREEN_LED);
			updateLedBuffer(mode, tempGreen / 1000);
			break;
		case ERROR:
			status = RED_GREEN;
			redDuration = oldRed;
			amberDuration = oldAmber;
			greenDuration = oldGreen;
			redCounter = redDuration /1000;
			greenCounter = greenDuration /1000;
			amberCounter = amberDuration /1000;
			mode = 1;
			break;
		default:
			break;
	}
}
