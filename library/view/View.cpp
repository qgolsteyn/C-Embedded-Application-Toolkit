#include "Application.h"

#include "Assert.h"

View::View() {
	M_Stack();
	bounds = new Bound(0,0,0,0);
	absBounds = 0;
	damaged = 0;
	parent = 0;
	onDownListener = 0;
	onMoveListener = 0;
	onUpListener = 0;
	onClickListener = 0;
	M_Unstack();
}

View::~View() {
	if(absBounds) delete absBounds;
	if(bounds) delete bounds;
	if(damaged) delete damaged;
}

int View::getX() {
	return x;
}

void View::setX(int x) {
	M_Stack();
	View::x = x;
	invalidate();
	M_Unstack();
}

int View::getY() {
	return y;
}

void View::setY(int y) {
	M_Stack();
	View::y = y;
	invalidate();
	M_Unstack();
}

int View::getWidth() {
	return width;
}

void View::setWidth(int width) {
	M_Stack();
	View::width = width;
	invalidate();
	M_Unstack();
}

int View::getHeight() {
	return height;
}

void View::setHeight(int height) {
	M_Stack();
	View::height = height;
	invalidate();
	M_Unstack();
}

void View::onAttach() {
}

void View::onDetach() {
}

void View::onDraw(Canvas* canvas) {
	M_Stack();
	Log_Low("View", "onDraw");
	M_Unstack();
}

void View::onMeasure() {
}

void View::addOnDownPressListener(onDownPress fct) {
	onDownListener = fct;
}
void View::addOnMovePressListener(onMovePress fct) {
	onMoveListener = fct;
}

void View::addOnUpPressListener(onUpPress fct) {
	onUpListener = fct;
}

void View::addOnClickListener(onClick fct) {
	onClickListener = fct;
}

void View::draw() {
	M_Stack();
	if(damaged != 0) {
		Log_Low("View", "draw");

		Canvas* canvas = 0;

		if(parent)
			canvas = new Canvas(parent->absBounds->x1, parent->absBounds->y1);
		else
			canvas = new Canvas(0,0);

		canvas->setClippingBound(*damaged);

		this->onDraw(canvas);

		delete canvas;

		delete damaged;
		damaged = 0;

		Iterator* iterator = childrenViews.getIteratorStart();
		View* child = (View*) iterator->next();
		while(child != 0) {
			child->draw();
			child = (View*) iterator->next();
		}
		delete iterator;
	}
	M_Unstack();
}

void View::measure(Bound parent) {
	M_Stack();
	if(bounds == 0) internalMeasure();
	if(absBounds != 0) {
		delete absBounds;
	}

	absBounds = new Bound(parent.x1 + bounds->x1, parent.y1 + bounds->y1, parent.x1 + bounds->x2, parent.y1 + bounds->y2);

	Iterator* iterator = childrenViews.getIteratorStart();
	View* child = (View*) iterator->next();
	while(child != 0) {
		child->measure(*absBounds);
		child = (View*) iterator->next();
	}
	delete iterator;
	M_Unstack();
}

void View::internalMeasure() {
	M_Stack();
	if(bounds != 0) {
		delete bounds;
	}
	bounds = new Bound(x, y, x + width, y + height);
	M_Unstack();
}

void View::attachView(View* view) {
		M_Stack();
		M_Assert(view->parent == 0, "Trying to attach a view that is already attached!!");

		childrenViews.insertEnd(view);
		view->parent = this;
		view->invalidate();

		view->onAttach();
		M_Unstack();
}

void View::detachView(View* view) {
}

Bound View::getAbsBound() {
	return *absBounds;
}

void View::invalidate() {
	M_Stack();
	if(width != 0 && height != 0) {
		if(bounds == 0) internalMeasure();
		if(damaged != 0) delete damaged;
		Bound oldBound = Bound(bounds->x1, bounds->y1, bounds->x2, bounds->y2);
		internalMeasure();
		Bound newBound = Bound(bounds->x1, bounds->y1, bounds->x2, bounds->y2);
		damaged = newBound.merge(oldBound);
		if(parent != 0) parent->invalidateInParent(this, *damaged);
	}
	M_Unstack();
}

void View::invalidateInParent(View* caller, Bound childBound) {
	M_Stack();
	if(bounds == 0 || width == 0 || height == 0) {
		M_Unstack();
		return;
	}
	if(damaged == 0) {
		Bound temp = Bound(x + childBound.x1, y + childBound.y1, x + childBound.x2, y + childBound.y2);
		damaged = temp.intersect(*bounds);
	} else {
		Bound temp = Bound(x + childBound.x1, y + childBound.y1, x + childBound.x2, y + childBound.y2);
		Bound* mergedTemp = temp.merge(*damaged);
		delete damaged;
		damaged = mergedTemp;
	}

	Iterator* iterator = childrenViews.getIteratorStart();
	View* child = (View*) iterator->next();
	while(child != 0) {
		if(child != caller && child->bounds != 0 && childBound.intersectWith(*child->bounds)) {
			Bound* intersectChildren = childBound.intersect(*child->bounds);
			child->invalidateChildren(*intersectChildren);
			delete intersectChildren;
		}
		child = (View*) iterator->next();
	}
	delete iterator;

	if(parent != 0) parent->invalidateInParent(this, *damaged);

	M_Unstack();
}

void View::invalidateChildren(Bound parentBound) {
	if(damaged == 0) {
		damaged = new Bound(parentBound.x1, parentBound.y1, parentBound.x2, parentBound.y2);
	} else {
		Bound* mergedTemp = damaged->merge(parentBound);
		delete damaged;
		damaged = mergedTemp;
	}

	Iterator* iterator = childrenViews.getIteratorStart();
	View* child = (View*) iterator->next();
	while(child != 0) {
		if(child->bounds != 0) {
			Bound childBound = Bound(x + child->bounds->x1, y + child->bounds->y1, x + child->bounds->x2, y + child->bounds->y2);
			if(childBound.intersectWith(parentBound)) {
				Bound* intersectBound = parentBound.intersect(childBound);
				child->invalidateChildren(Bound(intersectBound->x1 - x, intersectBound->y1 - y, intersectBound->x2 - x, intersectBound->y2 - y));
				delete intersectBound;
			}
		}
		child = (View*) iterator->next();
	}
	delete iterator;
}
