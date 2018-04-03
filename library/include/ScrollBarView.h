/*
 * ScrollBarView.h
 *
 *  Created on: Apr 1, 2018
 *      Author: k6u0b
 */

#ifndef SCROLLBARVIEW_H_
#define SCROLLBARVIEW_H_

#include "Application.h"

typedef void (*onProgress) (View* view, int progress);

class ScrollBarView : public View {
public:
	onProgress onProgressListener;
	void addOnProgressListener(onProgress fct);
	void onAttach();
	void onDraw(Canvas* canvas);
};

#endif /* SCROLLBARVIEW_H_ */
