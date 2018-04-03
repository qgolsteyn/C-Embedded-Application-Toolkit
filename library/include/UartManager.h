/*
 * UART_Manager.h
 *
 *  Created on: Apr 3, 2018
 *      Author: k6u0b
 */

#ifndef UART_MANAGER_H_
#define UART_MANAGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* DE1_uartOpen(const char* path);
void DE1_uartWrite(FILE* f, const char* message);
void DE1_uartRead(FILE* f, int maxChar, char* result);
int DE1_uartDataAvailable(FILE* f);
void DE1_uartClose(FILE* f);

#endif /* UART_MANAGER_H_ */
