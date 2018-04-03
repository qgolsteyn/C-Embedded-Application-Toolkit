/*
 * Uart_Manager.c
 *
 *  Created on: Apr 3, 2018
 *      Author: k6u0b
 */

#include "UartManager.h"

FILE* DE1_uartOpen(const char* path) {
	FILE *f = fopen(path, "r+");
	return f;
}

void DE1_uartWrite(FILE* f, const char* message) {
	if(f) {
		fwrite(message, strlen(message), 1, f);
		fwrite("\r\n", strlen("\r\n"), 1, f);
	} else {
		printf("UART ERROR - Cannot write to stream");
	}
}

void DE1_uartRead(FILE* f, int maxChar, char* result) {
	if(f) {
		fgets(result, maxChar, f);
	} else {
		printf("UART ERROR - Cannot read stream");
	}
}

int DE1_uartDataAvailable(FILE* f) {
	if(f) {
		return !feof(f);
	} else {
		return 0;
	}
}

void DE1_uartClose(FILE* f) {
	if(f) {
		fclose(f);
	}
}


