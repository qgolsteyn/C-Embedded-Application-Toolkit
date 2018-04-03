#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Bound.h"
#include "Canvas.h"
#include "List.h"
#include "Touchscreen.h"
#include "Colors.h"


#define XRES 770
#define YRES 480
#define XOFF 30
#define YOFF 0

class Application;
class Context;
class Activity;
class View;
class Renderer;
class Canvas;
class AnimatorObject;

class Application {
  friend class Context;
  Activity* currentActivity;

  Renderer* renderer;

public:
  Application();
  ~Application();
  void startApplication(Activity* activity);
  void startActivity(Activity* activity);
private:
  void stopCurrentActivity();
  void superLoop();
};

class Context {
  Application* application;
public:
  Context();
  ~Context();
  void attachApplication(Application* app);
  void detachApplication();
protected:
  //Serial* getSerial();
  void startActivity(Activity* activity);
private:
};

#define DOWN_EVENT 0
#define MOVE_EVENT 1
#define UP_EVENT 2
#define CLICK_EVENT 3

class Renderer {
	View* rootView;
	List animatorObjects;
	List touchPath;

	int pastPressed, touchMove;
	int touchX, touchY, touchDX, touchDY;
public:
	static Renderer* getInstance();
	void setRootView(View* rootView);
	void addAnimatorObject(AnimatorObject* object);
	void animate();
	void handleTouch();
	void render();
private:
	void propagateTouchEvent(int type);
	void generateTouchList(Point point);
	void generateTouchListChildren(View* view, Point point);
	void removeRestOfPath(Iterator* iterator);
	void handleDown(Point point);
	void handleMove(Point point);
	void handleUp(Point point);
	Renderer();
};

typedef int (*onDownPress)(View* view);
typedef int (*onMovePress)(View* view, int x, int y, int dx, int dy);
typedef int (*onUpPress)(View* view);
typedef int (*onClick)(View* view);

class View : public Context {
  friend class Renderer;

  int x, y, width, height;
  List childrenViews;
  View* parent;

  onDownPress onDownListener;
  onMovePress onMoveListener;
  onUpPress onUpListener;
  onClick onClickListener;

public:
  View();
  ~View();
  int getX();
  void setX(int x);
  int getY();
  void setY(int y);
  int getWidth();
  void setWidth(int width);
  int getHeight();
  void setHeight(int height);

  virtual void onAttach();
  virtual void onDetach();
  virtual void onDraw(Canvas* canvas);
  virtual void onMeasure();
  void addOnDownPressListener(onDownPress fct);
  void addOnMovePressListener(onMovePress fct);
  void addOnUpPressListener(onUpPress fct);
  void addOnClickListener(onClick fct);

  void draw();
  void measure(Bound parent);
  void internalMeasure();

  void attachView(View* view);
  void detachView(View* view);

  Bound getAbsBound();

  void invalidate();
protected:
  Bound* bounds;
  Bound* absBounds;
  Bound* damaged;
  void invalidateInParent(View* caller, Bound damaged);
  void invalidateChildren(Bound damaged);

};

class Activity : public Context {
  friend class Application;
  View rootView;
public:
  virtual void onCreate();
  virtual void onDestroy();
  virtual string getName();
protected:
  void attachView(View* view);
  void detachView();
private:
};

struct AnimatorObject {
	View* view;
	int finalX, finalY, finalWidth, finalHeight;
	int dX, dY, dWidth, dHeight;
	int length;
	int curTime;
};

int animator_isr(AnimatorObject* parameter);

class Animator {
	AnimatorObject* object;
public:
	Animator(View* view);
	void translateX(int finalX);
	void translateY(int finalX);
	void translateWidth(int finalWidth);
	void translateHeight(int finalHeight);
	void setDuration(int length);
	void setInterval(int interval);
	void start();
};

#endif
