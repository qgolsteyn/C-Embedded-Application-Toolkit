#ifndef MAIN_ACTIVITY_H_
#define MAIN_ACTIVITY_H_

#include <string>

using namespace std;

#include "Application.h"

#include "ShapeView.h"
#include "ButtonView.h"
#include "ScrollBarView.h"
#include "TextView.h"

class MainActivity : public Activity {

public:
  MainActivity();
  ~MainActivity();
  void onCreate();
  void onDestroy();
  string getName();
};

#endif
