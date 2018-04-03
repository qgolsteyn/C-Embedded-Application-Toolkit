/*
 * ScrollBar.cpp
 *
 *  Created on: Apr 1, 2018
 *      Author: k6u0b
 */

#include "ScrollBarView.h"

#include "ShapeView.h"

CircleView* buttonView;
void ScrollBarView::onAttach() {
	buttonView = new CircleView();
	attachView(buttonView);

	buttonView->setX(0);
	buttonView->setY(getWidth()/2+15);
	buttonView->setWidth(30);
	buttonView->setHeight(30);
	buttonView->setColour(COLOR_BUTTON_DEFAULT);

	addOnMovePressListener([](View* _view, int x, int y, int dX, int dY) -> int {
		ScrollBarView* view = (ScrollBarView*) _view;
		int newX = x - view->getAbsBound().x1;
		if(newX > view->getWidth() - 30) newX = view->getWidth() - 30;
		else if(newX < 0) newX = 0;
		buttonView->setX(newX);
		if(view->onProgressListener) view->onProgressListener(view, newX/(view->getWidth() - 30.0) * 100.0 + 0.5);
		return 1;
	});
}

void ScrollBarView::onDraw(Canvas* canvas) {
	canvas->setStroke(COLOR_GREY);
	canvas->drawHLine((bounds->y2+bounds->y1)/2, bounds->x1+15, bounds->x2-15);
}

void ScrollBarView::addOnProgressListener(onProgress fct) {
	onProgressListener = fct;
}
