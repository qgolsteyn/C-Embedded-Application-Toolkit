/*
 * Animator.cpp
 *
 *  Created on: Apr 1, 2018
 *      Author: k6u0b
 */

#include "Application.h"

#include "Assert.h"

int animator_isr(AnimatorObject* parameter) {
	M_Stack();
	AnimatorObject* object = (AnimatorObject*) parameter;
	if(object->dX != 0) object->view->setX(object->view->getX() + object->dX);
	if(object->dY != 0) object->view->setY(object->view->getY() + object->dY);
	if(object->dWidth != 0) object->view->setWidth(object->view->getWidth() + object->dWidth);
	if(object->dHeight != 0) object->view->setHeight(object->view->getHeight() + object->dHeight);
	object->curTime += 100;

	if(object->curTime >= object->length) {
		delete object;
		M_Unstack();
		return 1;
	} else {
		M_Unstack();
		return 0;
	}
}

Animator::Animator(View* view) {
	M_Stack();
	M_Assert(view != 0, "View cannot be null");
	object = new AnimatorObject;
	object->view = view;
	object->finalX = view->getX();
	object->finalY = view->getY();
	object->finalWidth = view->getWidth();
	object->finalHeight = view->getHeight();
	object->length = 1000;
	object->curTime = 0;
	M_Unstack();
}

void Animator::translateX(int finalX) {
	M_Stack();
	M_Assert(object != 0, "Cannot call after start()");
	object->finalX = finalX;
	M_Unstack();
}

void Animator::translateY(int finalY) {
	M_Stack();
	M_Assert(object != 0, "Cannot call after start()");
	object->finalY = finalY;
	M_Unstack();
}
void Animator::translateWidth(int finalWidth) {
	M_Stack();
	M_Assert(object != 0, "Cannot call after start()");
	object->finalWidth = finalWidth;
	M_Unstack();
}
void Animator::translateHeight(int finalHeight) {
	M_Stack();
	M_Assert(object != 0, "Cannot call after start()");
	object->finalHeight = finalHeight;
	M_Unstack();
}
void Animator::setDuration(int length) {
	M_Stack();
	M_Assert(object != 0, "Cannot call after start()");
	object->length = length;
	M_Unstack();
}

void Animator::start() {
	M_Stack();
	int interval = object->length / 100;
	object->dX = (object->finalX - object->view->getX())/interval;
	object->dY = (object->finalY - object->view->getY())/interval;
	object->dWidth = (object->finalWidth - object->view->getWidth())/interval;
	object->dHeight = (object->finalHeight - object->view->getHeight())/interval;

	Renderer::getInstance()->addAnimatorObject(object);

	object = 0;
	M_Unstack();
}
