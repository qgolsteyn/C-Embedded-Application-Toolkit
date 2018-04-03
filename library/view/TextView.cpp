/*
 * TextView.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: k6u0b
 */

#include "TextView.h"

void TextView::setTextColour(int colour) {
	textColour = colour;
	invalidate();
}

void TextView::setText(string text) {
	TextView::text = text;
	invalidate();
}

void TextView::setVerticalPos(int pos) {
	verticalPos = pos;
	invalidate();
}

void TextView::setHorizontalPos(int pos) {
	horizontalPos = pos;
	invalidate();
}

void TextView::onDraw(Canvas* canvas) {
	int x, y;
	switch(horizontalPos) {
	case H_LEFT:
		x = bounds->x1;
		break;
	case H_CENTER:
		x = (bounds->x1+bounds->x2 - 10*text.length())/2;
		break;
	case H_RIGHT:
		x = bounds->x2 - 10*text.length();
		break;
	}

	switch(verticalPos) {
	case V_TOP:
		y = bounds->y1;
		break;
	case V_CENTER:
		y = (bounds->y1 + bounds->y2 - 14)/2;
		break;
	case V_BOTTOM:
		y = bounds->y2 - 14;
		break;
	}

	canvas->setStroke(textColour);

	for(unsigned int i = 0; i < text.length(); i++) {
		canvas->drawChar(x, y, text[i]);
		x += 10;
	}
}


