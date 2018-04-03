/*
 * TextView.h
 *
 *  Created on: Apr 2, 2018
 *      Author: k6u0b
 */

#ifndef TEXTVIEW_H_
#define TEXTVIEW_H_

#include <iostream>
#include <string>

using namespace std;

#include "Application.h"

#define V_TOP 0
#define V_CENTER 1
#define V_BOTTOM 2

#define H_LEFT 0
#define H_CENTER 1
#define H_RIGHT 2

class TextView : public View {
	string text;
	int textColour;
	int verticalPos;
	int horizontalPos;
public:
	void setVerticalPos(int pos);
	void setHorizontalPos(int pos);
	void setTextColour(int colour);
	void setText(string text);
	void onDraw(Canvas* canvas);
};

#endif /* TEXTVIEW_H_ */
