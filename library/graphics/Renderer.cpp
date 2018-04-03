#include "Application.h"

#include <cmath>

#include "Log.h"
#include "Assert.h"
#include "Touchscreen.h"

extern "C" {
	#include "GraphicPrimitives.h"
}

Renderer* render_instance = 0;

Renderer* Renderer::getInstance(){
	M_Stack();
	if(render_instance == 0) {
		render_instance = new Renderer;
	}
	M_Unstack();
	return render_instance;
}

Renderer::Renderer() {
	pastPressed = 0;
	touchMove = 0;
	touchX = touchY = touchDX = touchDY = 0;
	rootView = 0;

	DE1_writeRect(0, 0, XRES, YRES, 0);

	DE1_programPalette(COLOR_PRIMARY, 0x18638F);
	DE1_programPalette(COLOR_DARK_PRIMARY, 0x52D1ED);
	DE1_programPalette(COLOR_ACCENT, 0xEC512B);

	DE1_programPalette(COLOR_BUTTON_DEFAULT, 0xEC512B);
	DE1_programPalette(COLOR_BUTTON_DEFAULT_BORDER, 0xd13813);
	DE1_programPalette(COLOR_BUTTON_DEFAULT_FOCUSED, 0xf0775a);

	DE1_programPalette(COLOR_WHITE, 0xffffff);
	DE1_programPalette(COLOR_GREY, 0xcccccc);
	DE1_programPalette(COLOR_BLACK, 0);

	DE1_touchInit();
}

void Renderer::setRootView(View* view) {
	M_Stack();
	view->parent = 0;
	view->x = 0;
	view->y = 0;
	view->width = XRES;
	view->height = YRES;
	Bound parent = Bound(0,0,XRES,YRES);
	view->measure(parent);
	view->invalidate();

	rootView = view;

	M_Unstack();
}

void Renderer::addAnimatorObject(AnimatorObject* object) {
	M_Stack();
	animatorObjects.insertEnd((void*) object);
	M_Unstack();
}

void Renderer::animate() {
	M_Stack();
	Iterator* iterator = animatorObjects.getIteratorStart();
	AnimatorObject* object = (AnimatorObject*) iterator->next();
	while(object != 0) {
		if(animator_isr(object)) {
			AnimatorObject* temp = object;
			object = (AnimatorObject*) iterator->next();
			animatorObjects.deleteItem((void*) temp);
		} else {
			object = (AnimatorObject*) iterator->next();
		}
	}
	delete iterator;
	M_Unstack();
}

void Renderer::handleDown(Point point) {
	M_Stack();
	Log_Low("Renderer", "down");
	generateTouchList(point);
	pastPressed = 1;
	touchX = point.x;
	touchY = point.y;
	cout << touchX << ", " << touchY << endl;
	propagateTouchEvent(DOWN_EVENT);
	M_Unstack();
}

void Renderer::handleMove(Point point) {
	M_Stack();
	Log_Low("Renderer", "move");
	touchDX = point.x - touchX;
	touchDY = point.y - touchY;
	if(touchMove) {
		touchX = point.x;
		touchY = point.y;
		propagateTouchEvent(MOVE_EVENT);
	} else {
		if(abs(touchDX) > 12 || abs(touchDY) > 12) {
			touchDX = 0;
			touchDY = 0;
			touchMove = 1;
			touchX = point.x;
			touchY = point.y;
			propagateTouchEvent(MOVE_EVENT);
		}
	}
	M_Unstack();
}

void Renderer::handleUp(Point point) {
	M_Stack();
	Log_Low("Renderer", "up");
	pastPressed = 0;
	touchMove = 0;
	Iterator* iterator = touchPath.getIteratorStart();
	View* view = (View*) iterator->next();
	while(view != 0) {
		int withinBounds = view->absBounds->containsPoint(point.x, point.y);
		if(view->onUpListener != 0) view->onUpListener(view);
		if(withinBounds && view->onClickListener != 0) view->onClickListener(view);
		view = (View*) iterator->next();
	}
	delete iterator;

	touchPath.clear();

	M_Unstack();
}

int count = 0;
void Renderer::handleTouch() {
	M_Stack();
	if(DE1_isScreenTouched()) {
		Point point = DE1_getLastTouchLocation();
		if(point.status == PRESSED) {
		  if(!pastPressed) {
			handleDown(point);
		  } else {
			handleMove(point);
		  }
		} else if(point.status == RELEASED) {
		  if(pastPressed) {
			  handleUp(point);
			  DE1_clearLastTouchLocation();
		  }
		}
	} else {
		count++;
		if(count == 9) {
			struct Point point = DE1_getLastTouchLocation();
			if(pastPressed) {
				handleUp(point);
				DE1_clearLastTouchLocation();
			}
			count = 0;
		}
	}
	M_Unstack();
}

void Renderer::propagateTouchEvent(int type) {
	M_Stack();
	Iterator* iterator = touchPath.getIteratorStart();
	View* view = (View*) iterator->next();
	while(view != 0) {
		int result = 0;
		switch(type) {
		case DOWN_EVENT:
			if(view->onDownListener != 0) result = view->onDownListener(view);
			break;
		case UP_EVENT:
			if(view->onUpListener != 0) result = view->onUpListener(view);
			break;
		case MOVE_EVENT:
			if(view->onMoveListener != 0) result = view->onMoveListener(view, touchX, touchY, touchDX, touchDY);
			break;
		case CLICK_EVENT:
			if(view->onClickListener != 0) result = view->onClickListener(view);
			break;
		}
		if(result) {
			removeRestOfPath(iterator);
			touchPath.deleteAfter((void*) view);
			view = 0;
		} else {
			view = (View*) iterator->next();
		}
	}
	delete iterator;
	M_Unstack();
}

void Renderer::generateTouchList(Point point) {
	M_Stack();
	generateTouchListChildren(rootView, point);
	M_Unstack();
}

void Renderer::generateTouchListChildren(View* view, Point point) {
	M_Stack();
	if(view->absBounds->containsPoint(point.x, point.y)) {
		touchPath.insertEnd((void*) view);

		Iterator* iterator = view->childrenViews.getIteratorEnd();
		View* child = (View*) iterator->prev();
		while(child != 0) {
			generateTouchListChildren(child, point);
			child = (View*) iterator->prev();
		}
		delete iterator;
	}
	M_Unstack();
}

void Renderer::removeRestOfPath(Iterator* iterator) {
	View* view = (View*) iterator->next();
	while(view != 0) {
		if(view->onUpListener != 0) view->onUpListener(view);
		view = (View*) iterator->next();
	}
}

void Renderer::render() {
	M_Stack();
	if(rootView != 0) {
		Bound parent = Bound(0,0,XRES,YRES);
		rootView->measure(parent);
		rootView->draw();
	} else {
		Log_Warn("Renderer", "No view to render");
	}
	M_Unstack();
}



