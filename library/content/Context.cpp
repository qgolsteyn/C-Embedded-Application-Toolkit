#include "Application.h"

#include "Assert.h"

Context::Context() {
	M_Stack();
	application = NULL;
	M_Unstack();
}

Context::~Context() {
	M_Stack();
	detachApplication();
	M_Unstack();
}

void Context::attachApplication(Application* app) {
	M_Stack();
	application = app;
	M_Unstack();
}

void Context::detachApplication() {
	M_Stack();
	application = NULL;
	M_Unstack();
}

void Context::attachSerial(UartSerial* serial) {
	application->attachSerial(serial);
}

void Context::detachSerial(UartSerial* serial) {
	application->detachSerial(serial);
}

void Context::startActivity(Activity* activity) {
	M_Stack();
	M_Assert(application != NULL, "Application is not attached! Have you called attachApplication()?");
	application->startActivity(activity);
	M_Unstack();
}
