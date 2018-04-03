#include "ShapeView.h"

#include <cmath>

#include "Log.h"
#include "Assert.h"

void CircleView::onDraw(Canvas* canvas) {
  M_Stack();
  int r = min(getWidth(), getHeight())/2;
  canvas->setFill(ShapeView::colour);
  canvas->drawCirc((View::bounds->x1 + View::bounds->x2)/2, (View::bounds->y1 + View::bounds->y2)/2, r);
  M_Unstack();
}
