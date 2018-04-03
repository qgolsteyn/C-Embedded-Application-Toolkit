#include "Application.h"

#include <string>
#include <unistd.h>

using namespace std;

#include "Assert.h"
#include "Log.h"
#include "JobRunner.h"
#include "Touchscreen.h"

Application::Application() {
	M_Stack();
	//serial = new Serial();

	currentActivity = 0;
	M_Unstack();
}

Application::~Application() {
	delete JobRunner::getInstance();
	delete Renderer::getInstance();
}

int hello_world1_isr() {
	return 0;
}

int hello_world2_isr() {
	Log_Warn("Hello World2!", "123");
	return 0;
}

void Application::startApplication(Activity* startActivity) {
	M_Stack();
	Log_Low("Application", "Starting Application");

	JobRunner* instance = JobRunner::getInstance();

	//instance->scheduleRepeating(hello_world1_isr, 1000, 500);//1000);
	//instance->scheduleRepeating(hello_world2_isr, 1000, 2000);

 	renderer = Renderer::getInstance();

 	Application::startActivity(startActivity);
 	superLoop();
 	M_Unstack();
}

void Application::startActivity(Activity* activity) {
	M_Stack();
	Log_Low("Application", "Starting " + activity->getName());

	if(currentActivity != 0)
		Application::stopCurrentActivity();

	renderer->setRootView(&activity->rootView);
	activity->attachApplication(this);
	activity->onCreate();
	currentActivity = activity;
	M_Unstack();
}

void Application::stopCurrentActivity() {
	M_Stack();
	currentActivity->onDestroy();
	currentActivity->detachApplication();
	delete currentActivity;
	currentActivity = NULL;
	M_Unstack();
}

void Application::superLoop() {
	M_Stack();
	Log_Low("Application", "Starting SuperLoop");
	while(1) {
		usleep(30);
		renderer->handleTouch();
		//renderer->animate();
		renderer->render();
	}
	M_Unstack();
}
