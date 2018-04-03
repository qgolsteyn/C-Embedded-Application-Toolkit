#include "ShapeView.h"

#include "Log.h"
#include "Assert.h"

void RectangleView::onDraw(Canvas* canvas) {
  M_Stack();
  Log_Low("RectangleView", "onDraw");
  canvas->setFill(ShapeView::colour);
  canvas->drawRect(View::bounds->x1, View::bounds->y1, View::bounds->x2, View::bounds->y2);
  M_Unstack();
}
