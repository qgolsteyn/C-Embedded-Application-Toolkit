/*
 * ShapeView.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: k6u0b
 */

#include "ShapeView.h"

#include "Log.h"
#include "Assert.h"

void ShapeView::setColour(int colour) {
	M_Stack();
	ShapeView::colour = colour;
	M_Unstack();
}


