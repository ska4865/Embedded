#ifndef __NUCLEO476_LED_H
#define __NUCLEO476_LED_H

#include "stm32l476xx.h"

void LED_Init(void);

void GLED_On(void);
void RLED_On(void);
void BLED_On(void);
void WLED_On(void);
void LED_Off(void);
void GLED_Off(void);
void BLED_Off(void);
void WLED_Off(void);
void RLED_Off(void);
void GLED_Toggle(void);
void RLED_Toggle(void);
void BLED_Toggle(void);
void WLED_Toggle(void);

#endif /* __NUCLEO476_LED_H */
