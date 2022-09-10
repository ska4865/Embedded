/*
 * printf.h
 *
 *  Created on: Apr 25, 2022
 *      Author: piedy
 */

#ifndef INC_PRINTF_H_
#define INC_PRINTF_H_

#include <stdarg.h>
#include <stdio.h>
#include "stm32l476xx.h"

int printf (const char* format, ...);

#endif /* INC_PRINTF_H_ */
