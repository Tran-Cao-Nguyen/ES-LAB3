/*
 * graphic.h
 *
 *  Created on: Dec 1, 2024
 *      Author: CAO NGUYEN
 */

#ifndef INC_GRAPHIC_H_
#define INC_GRAPHIC_H_

#include "global.h"

enum LED
{
	RED_LED,
	GREEN_LED,
	AMBER_LED,
};

void lcdRedGreen();
void lcdRedAmber();
void lcdGreenRed();
void lcdAmberRed();

void updateLedBuffer(int value1, int value2);
void blinkingLed(enum LED led);


#endif /* INC_GRAPHIC_H_ */
