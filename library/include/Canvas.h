#ifndef CANVAS_H_
#define CANVAS_H_

#define TRANSPARENT -1

#include <iostream>
#include <string>

using namespace std;

#include "Application.h"
#include "Bound.h"

class Canvas {
  Bound* clippingBound;
  int strokeColour;
  int fillColour;
  int borderWidth;
  int x, y;
public:
  Canvas(int x, int y);
  ~Canvas();

  void setStroke(int colour);
  void setFill(int colour);
  void setBorderWidth(int width);

  Bound getClippingBound();
  void setClippingBound(Bound bound);

  void setXOrigin(int x);
  void setYOrigin(int y);

  void drawPixel(int x, int y);
  int readPixel(int x, int y);
  void drawHLine(int y, int x1, int x2);
  void drawVLine(int x, int y1, int y2);
  void drawLine(int x1, int y1, int x2, int y2);
  void drawRect(int x1, int y1, int x2, int y2);
  void drawCirc(int x1, int y1, int r);
  void drawChar(int x, int y, char c);
};

#endif
