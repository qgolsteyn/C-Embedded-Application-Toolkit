#ifndef BUTTON_VIEW_H_
#define BUTTON_VIEW_H_

#include "Application.h"

class ButtonView : public View {
	int color;
	int focusedColor;
	int focused;
	string text;
public:
	void onAttach();
	void setText(string text);
	void setColour(int color);
	void setFocusedColour(int color);
	void onDraw(Canvas* canvas);
};

#endif
