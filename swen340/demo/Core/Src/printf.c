/*
 * printf.c
 *
 *  Created on: Apr 25, 2022
 *      Author: Sakai Alexander
 */

#include <stdarg.h>
#include <stdio.h>
#include "stm32l476xx.h"

int printf (const char* format, ...) {
    char buffer [256];
    int len = 0;
    va_list args;
    va_start (args, format);
    len = vsprintf (buffer, format, args);
    perror (buffer);
    va_end (args);

    for (int i = 0; i < len; i++) {
        while (!(USART2->ISR & USART_ISR_TXE));       // wait until TXE (TX empty) bit is set
        // Writing USART_DR automatically clears the TXE flag
        USART2->TDR = buffer[i] & 0xFF;
    }
    while (!(USART2->ISR & USART_ISR_TC));             // wait until TC bit is set
    USART2->ISR &= ~USART_ISR_TC;

    return len;
}
