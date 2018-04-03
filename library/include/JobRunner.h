#ifndef TIMERINTERRUPT_H_
#define TIMERINTERRUPT_H_

#include "sys/alt_alarm.h"
#include "alt_types.h"

#include "List.h"

typedef int (*timer_fct)(void* context);

alt_u32 alarm_handler(void* context);

class Alarm {
public:
	alt_alarm alarm;
	int when;
	int delay;
	timer_fct fctPtr;
	void* parameter;
};

class JobRunner {
	List alarms;
public:
	static JobRunner* getInstance();
	void schedule(timer_fct fctPtr, void* parameter, int when);
	void scheduleRepeating(timer_fct fctPtr, void* parameter, int when, int delay);
private:
	Alarm* createAlarm(int when, int delay, timer_fct fctPtr, void* parameter);
};

void timer_isr(void* context);

#endif
