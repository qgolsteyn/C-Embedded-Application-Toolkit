/*
 * PiSerial.h
 *
 *  Created on: Apr 3, 2018
 *      Author: k6u0b
 */

#ifndef PISERIAL_H_
#define PISERIAL_H_

#include <string>

extern "C" {
 #include "UartManager.h"
}

using namespace std;

typedef void (*onNewData)(string data);

class UartSerial {
	FILE* f;
	string path;
	onNewData onNewDataListener;
public:
	UartSerial(string path);
	~UartSerial();

	void writeLine(string message);
	string readLine();
	int isDataAvailable();

	void checkListener();
	void addOnNewDataListener(onNewData fct);
};

#endif /* PISERIAL_H_ */
