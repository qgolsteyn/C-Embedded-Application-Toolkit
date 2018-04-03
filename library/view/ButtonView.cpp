#include "ButtonView.h"

#include "Log.h"

void ButtonView::onAttach() {

	color = COLOR_BUTTON_DEFAULT;
	focusedColor = COLOR_BUTTON_DEFAULT_FOCUSED;

	View::addOnDownPressListener([](View* _view) -> int {
		Log_Low("ButtonView", "On down press");
		ButtonView* view = (ButtonView*) _view;
		if(!view->focused) {
			view->focused = 1;
			view->invalidate();
		}

		return 1;
	});

	View::addOnUpPressListener([](View* _view) -> int {
		Log_Low("ButtonView", "On up press");
		ButtonView* view = (ButtonView*) _view;
		if(view->focused) {
			view->focused = 0;
			view->invalidate();
		}

		return 1;
	});
}

void ButtonView::onDraw(Canvas* canvas) {
	if(focused) canvas->setFill(focusedColor);
	else canvas->setFill(color);

	canvas->setStroke(COLOR_BUTTON_DEFAULT_BORDER);
	canvas->setBorderWidth(3);

	canvas->drawRect(View::bounds->x1, View::bounds->y1, View::bounds->x2, View::bounds->y2);
	//canvas.drawText((bounds->x1+bounds->x2)/2 - 5, (bounds->y1+bounds->y2)/2 - 7, text);
}

void ButtonView::setText(string text) {
	ButtonView::text = text;
	invalidate();
}

void ButtonView::setColour(int color) {
	ButtonView::color = color;
	invalidate();
}

void ButtonView::setFocusedColour(int color) {
	ButtonView::focusedColor = color;
	invalidate();
}
