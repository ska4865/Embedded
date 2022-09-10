/*
 * hello_world.c
 *
 *  Created on: Feb 10, 2022
 *      Author: ska4865
 */

#include <stdio.h>
#include "hello_world.h"
#include "UART.h"



/**
 * Get a name, print "Hello, <name>!"
 */
void hello_world() {
	int n;
	uint8_t buffer[64];
	uint8_t name[16];

	int i;
	uint8_t one = 0;
	for (i = 0; one != '\r'; i++){
		one = USART_Read(USART2);
		name[i] = one;
	}

	name [i - 1] = '\0';

	n = printf("Hello, %s\r\n" , (char*)name);

	USART_Write(USART2, buffer, n);
}
