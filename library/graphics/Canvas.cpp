#include "Canvas.h"

extern "C" {
#include "GraphicPrimitives.h"
#include "OutGraphicsCharFont.h"
}

#include "Log.h"
#include "Assert.h"

Canvas::Canvas(int x, int y) {
	M_Stack();
	clippingBound = 0;
	Canvas::setStroke(TRANSPARENT);
	Canvas::setFill(TRANSPARENT);
	Canvas::setBorderWidth(0);
	Canvas::setXOrigin(XOFF + x);
	Canvas::setYOrigin(YOFF + y);
	M_Unstack();
}

Canvas::~Canvas() {
	M_Stack();
	if(clippingBound) delete clippingBound;
	M_Unstack();
}

Bound Canvas::getClippingBound() {
  return *clippingBound;
}

void Canvas::setClippingBound(Bound bound) {
	M_Stack();
	if(clippingBound) delete clippingBound;
	clippingBound = new Bound(Canvas::x + bound.x1, Canvas::y + bound.y1, Canvas::x + bound.x2, Canvas::y + bound.y2);
	M_Unstack();
}

void Canvas::setStroke(int colour) {
	M_Stack();
	strokeColour = colour;
	M_Unstack();
}

void Canvas::setFill(int colour) {
	M_Stack();
	fillColour = colour;
	M_Unstack();
}

void Canvas::setBorderWidth(int borderWidth) {
	M_Stack();
	Canvas::borderWidth = borderWidth;
	M_Unstack();
}

void Canvas::setXOrigin(int x) {
	M_Stack();
	Canvas::x = x;
	M_Unstack();
}

void Canvas::setYOrigin(int y) {
	M_Stack();
	Canvas::y = y;
	M_Unstack();
}

void Canvas::drawPixel(int x, int y) {
	M_Stack();
	if(strokeColour == TRANSPARENT) {
		Log_Warn("Canvas", "No stroke colour set for drawPixel()")
		M_Unstack();
    		return;
	}
	if(!clippingBound->containsPoint(x, y)) return;

	DE1_writePixel(Canvas::x + x,Canvas::y + y,strokeColour);
	M_Unstack();
}

int Canvas::readPixel(int x, int y) {
  return 0;
}

void Canvas::drawHLine(int y, int x1, int x2) {
	M_Stack();
	if(strokeColour == TRANSPARENT) {
		Log_Warn("Canvas", "No stroke colour set for drawHLine()")
		M_Unstack();
    	return;
	}
	M_Assert(x1 <= x2, "x1 needs to be smaller than x2");

	Bound* result = clippingBound->cohenSutherland(Canvas::x + x1, Canvas::y + y, Canvas::x + x2, Canvas::y + y);
	if(result) {
		DE1_writeHLine(result->y1, result->x1, result->x2, strokeColour);
		delete result;
	}
	M_Unstack();
}

void Canvas::drawVLine(int x, int y1, int y2) {
	M_Stack();
  if(strokeColour == TRANSPARENT) {
	  	Log_Warn("Canvas", "No stroke colour set for drawVLine()")
		M_Unstack();
	  	return;
  }
  M_Assert(y1 <= y2, "y1 needs to be smaller than y2");

  Bound* result = clippingBound->cohenSutherland(Canvas::x + x, Canvas::y + y1, Canvas::x + x, Canvas::y + y2);
  if(result) {
    DE1_writeVLine(result->x1, result->y1, result->y2, strokeColour);
    delete result;
  }
  M_Unstack();
}

void Canvas::drawLine(int x1, int y1, int x2, int y2) {
	M_Stack();
  if(strokeColour == TRANSPARENT) {
    Log_Warn("Canvas", "No stroke colour set for drawLine()")
		M_Unstack();
    return;
  }
  M_Assert(x1 <= x2, "x1 needs to be smaller than x2");
  M_Assert(y1 <= y2, "y1 needs to be smaller than y2");

  Bound* result = clippingBound->cohenSutherland(Canvas::x + x1, Canvas::y + y1, Canvas::x + x2, Canvas::y + y2);
  if(result) {
    DE1_writeLine(result->x1, result->y1, result->x2, result->y2, strokeColour);
    delete result;
  }
  M_Unstack();
}

void Canvas::drawRect(int x1, int y1, int x2, int y2) {
	M_Stack();
  M_Assert(x1 <= x2, "x1 needs to be smaller than x2");
  M_Assert(y1 <= y2, "y1 needs to be smaller than y2");

  Bound bound = Bound(Canvas::x + x1, Canvas::y + y1, Canvas::x + x2, Canvas::y + y2);

  if(!clippingBound->intersectWith(bound)) return;

  Bound* result = clippingBound->intersect(bound);

  if(fillColour != TRANSPARENT) {
    DE1_writeRect(result->x1, result->y1, result->x2, result->y2, fillColour);
  }

  if(strokeColour != TRANSPARENT && borderWidth > 0) {
    int i;
    for(i = 0; i < borderWidth; i++) {
      DE1_writeHLine(result->y1 + i, result->x1, result->x2, strokeColour);
	  DE1_writeHLine(result->y2 - i, result->x1, result->x2, strokeColour);
	  DE1_writeVLine(result->x1 + i, result->y1, result->y2, strokeColour);
	  DE1_writeVLine(result->x2 - i, result->y1, result->y2, strokeColour);
    }
  }

	delete result;
	
  M_Unstack();
}

void Canvas::drawCirc(int x1, int y1, int r) {
	M_Stack();
	M_Assert(r >= 0, "r needs to be a positive number");

	if(fillColour != TRANSPARENT) {
		int x = r - 1;
		int y = 0;
		int dx = 1;
		int dy = 1;
		int err = dx - (r << 1);

		while(x >= y) {
			DE1_writeHLine(Canvas::y + y1 + y, Canvas::x + x1 - x, Canvas::x + x1 + x, fillColour);
			DE1_writeHLine(Canvas::y + y1 + x, Canvas::x + x1 - y, Canvas::x + x1 + y, fillColour);
			DE1_writeHLine(Canvas::y + y1 - y, Canvas::x + x1 - x, Canvas::x + x1 + x, fillColour);
			DE1_writeHLine(Canvas::y + y1 - x, Canvas::x + x1 - y, Canvas::x + x1 + y, fillColour);

			if(err <= 0) {
				y++;
				err += dy;
				dy += 2;
			} else {
				x--;
				dx += 2;
				err += dx - (r << 1);
			}
		}

	}
	M_Unstack();
}

 void Canvas::drawChar(int x, int y, char c) {
 	M_Stack();
 	if(strokeColour == TRANSPARENT) {
 		Log_Warn("Canvas", "No stroke colour set for drawText()")
 		M_Unstack();
 		return;
 	}

 	OutGraphicsCharFont2(Canvas::x + x, Canvas::y + y, strokeColour, 0, c, 0);
 	M_Unstack();
 }
