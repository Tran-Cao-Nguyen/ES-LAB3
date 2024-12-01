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
			updateLedBuffer(mode, redDuration / 1000);
			if (isButtonPressed(0))
			{
				if(!isButtonPressed(2))
				{
					redDuration = tempRed;
				}
				status = MAN_AMBER;
				mode = 3;
			}
			if (isButtonPressed(1) && mode == 2)
			{
				redDuration += 1000;
				if (redDuration > 99000)
				{
					redDuration = 1000;
				}
			}

			break;
		case MAN_AMBER:
			blinkingLed(AMBER_LED);
			updateLedBuffer(mode, amberDuration / 1000);
			if (isButtonPressed(0))
			{
				if(!isButtonPressed(2))
				{
					amberDuration = tempAmber;
				}
				status = MAN_GREEN;
				mode = 4;
			}
			if (isButtonPressed(1)  && mode == 3)
			{
				amberDuration += 1000;
				if (amberDuration > 99000)
				{
					amberDuration = 1000;
				}
			}
			break;
		case MAN_GREEN:
			blinkingLed(GREEN_LED);
			updateLedBuffer(mode, greenDuration / 1000);
			if (isButtonPressed(0))
			{
				if(!isButtonPressed(2))
				{
					greenDuration = tempGreen;
				}
				if (redDuration == (greenDuration + amberDuration))
				{
					status = RED_GREEN;
					redCounter = redDuration / 1000;
					greenCounter = greenDuration / 1000;
					amberCounter = amberDuration / 1000;
					mode = 1;

				}
				else
				{
					status = ERROR;
				}
			}
			if (isButtonPressed(1) && mode == 4)
			{
				greenDuration += 1000;
				if (greenDuration > 99000)
				{
					greenDuration = 1000;
				}
			}

			break;
		case ERROR:
			status = RED_GREEN;
			redDuration = tempRed;
			amberDuration = tempAmber;
			greenDuration = tempGreen;
			redCounter = redDuration /1000;
			greenCounter = greenDuration /1000;
			amberCounter = amberDuration /1000;
			mode = 1;
			break;
		default:
			break;
	}
}
