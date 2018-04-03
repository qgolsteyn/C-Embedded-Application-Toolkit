/*
 * PiSerial.cpp
 *
 *  Created on: Apr 3, 2018
 *      Author: k6u0b
 */

#include "UartSerial.h"

#include "Assert.h"

UartSerial::UartSerial(string path) {
	M_Stack();
	onNewDataListener = 0;
	f = DE1_uartOpen(path.c_str());
	M_Unstack();
}

UartSerial::~UartSerial() {
	M_Stack();
	DE1_uartClose(f);
	M_Unstack();
}

void UartSerial::writeLine(string message) {
	M_Stack();
	DE1_uartWrite(f, message.c_str());
	M_Unstack();
}

string UartSerial::readLine() {
	M_Stack();
	char result[100];
	DE1_uartRead(f, 100, result);
	M_Unstack();
	return string(result);
}

int UartSerial::isDataAvailable() {
	return DE1_uartDataAvailable(f);
}

void UartSerial::checkListener() {
	M_Stack();
	if(onNewDataListener != 0 && isDataAvailable()) {
		string data = readLine();
		onNewDataListener(data);
	}
	M_Unstack();
}

void UartSerial::addOnNewDataListener(onNewData fct) {
	M_Stack();
	onNewDataListener = fct;
	M_Unstack();
}



