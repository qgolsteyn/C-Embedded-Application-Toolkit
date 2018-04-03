#ifndef RECTANGLE_VIEW_
#define RECTANGLE_VIEW_

#include "Application.h"
#include "Canvas.h"

class ShapeView : public View {
public:
	void setColour(int colour);
protected:
	int colour;
};

class RectangleView : public ShapeView {
public:
  void onDraw(Canvas* canvas);
};

class CircleView : public ShapeView {
public:
  void onDraw(Canvas* canvas);
};

#endif
