/*
 * demo.c
 *
 *  Created on: Feb 14, 2021
 *      Author: larry kiser
 *  Update to starter code for non-blocking assignment.
 *
 *  Updated on: Sept 20, 2021
 *      Author: Mitesh Parikh
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "stm32l476xx.h"
#include "LED.h"
#include "UART.h"
#include "demo.h"
#include "stm32l4xx.h"
#include "gpio.h"
#include "printf.h"

uint8_t one_char = 0;
uint8_t one_second_elapsed = 0;
uint8_t buffer[BUFFER_SIZE];
uint8_t action[16];
int i = 0;

/**
 * Systick handler for if a second has elapsed
 */
void Systick_Handler(){
	static uint32_t counter = 0; //counts to 1000
	counter++;
	if (counter == 1000){
		one_second_elapsed = 1;
		counter = 0;

	}
}

/**
 * initializes systick
 */
static void init_systick()
{
	// Use the SysTick global structure pointer to do the following in this
	// exact order with separate lines for each step:
	// Disable SysTick by clearing the CTRL (CSR) register.
	SysTick->CTRL = 0;
	// Set the LOAD (RVR) to 80,000 to give us a 1 millisecond timer.
	SysTick->LOAD = 79999;
	// Set the clock source bit in the CTRL (CSR) to the internal clock.
	SysTick->CTRL |= 1<<2;
	// Set the enable bit in the CTRL (CSR) to start the timer.
	SysTick->CTRL |= 1;

}

/**
 * Le internal timer of 1 second
 */
static void delay_systick()
{
	// Using the SysTick global structure pointer do the following:
	//
	// Check for the COUNTFLAG to be set. Return as soon as it is set..
	// This loop for the COUNTFLAG is a blocking call but not for more than 1 millisecond.

	while(!(SysTick->CTRL & (1<<16)))
		;

}

/**
 * A useful print function based off of USART write that can only take in strings
 */
static void print(char* message){
	int n ;

	n = sprintf((char *)buffer, message);
	USART_Write(USART2, buffer, n);

	delay_systick() ;	// enable this when you are ready to test
	n = 0;

}

/**
 * Prints out the help menu for a user
 */
static void help(){
	print("\n\r***REMOTE LED CONTROL MENU*** \n\r\0");
	print("Proper commands include: \n\r\0");
	print("RON - Turn on RED LED \n\r\0");
	print("ROFF - Turn off RED LED \n\r\0");
	print("GON - Turn on GREEN LED \n\r\0");
	print("GOFF - Turn off GREEN LED \n\r\0");
	print("RFLASH - Start flashing RED LED \n\r\0");
	print("GFLASH - Start flashing GREEN LED \n\r\0");
	print("ALLOFF - TURNOFF LEDs \n\r\0");
	print("HELP - Shows valid commands \n\r\0");
}

/**
 * In remote mode takes in user input and does the appropriate action
 * With a series of if-else statements that checks the users input against proper commands
 */
static void user_input(){
	if (!strcmp((char *)action, "HELP")){
		help();
	}

	else if (!strcmp((char *)action, "RON")){
		RLED_On();
	}

	else if (!strcmp((char *)action, "ROFF")){
		RLED_Off();
	}

	else if (!strcmp((char *)action, "GON")){
		GLED_On();
	}

	else if (!strcmp((char *)action, "GOFF")){
		GLED_Off();
	}

	else if (!strcmp((char *)action, "RFLASH")){
		RLED_Toggle();
	}

	else if (!strcmp((char *)action, "GFLASH")){
		if (one_second_elapsed){
			GLED_Toggle();
		}
	}

	else if (!strcmp((char *)action, "ALLOFF")){
		LED_Off();
	}

	else{
		print("\n\rInvalid command. Please input a proper command\n\r\0");
	}
}

/**
 * Its called a cheat because its blocking but it gets the job done
 * Honestly not sure if I should use this one because it works I'd have to do
 * some maneuvering in order to use the button tho although it works, in the works tbh
 */
void USART2Cheat(void) {
  uint8_t one = 0;
  int i;

  for (i = 0; one != '\r'; i++){
	  one = USART_Read_NB(USART2);
	  if(one != '\177'){
		  action[i] = one;
	  }
	  else{
		  i = i - 2;
	  }
  }
  action [i - 1] = '\0';
  user_input();
  i = 0;
  print("\n\r");
}

/**
 * The proper usart handler function thats non blocking although it
 * reads the variable action as improper all the time so...
 * you win some you lose some
 */
void USART2_IRQHandler(){
	one_char = USART_Read_NB( USART2 );
	USART_Write(USART2, &one_char, 1);
	if(one_char == '\r' || one_char == '\n'){
		one_char = '\n';
		action[i] = one_char;
		action [i + 1] = '\0';
		user_input();
		action[0] = 0;
		i = 0;
		USART_Write(USART2, &one_char, 1);

	}
	else{
		action[i] = one_char;
		i++;
	}
}


/**
 * RUN DEMO!!! Does everything from calling inits to starting and
 * keeping the magic going
 */
void run_demo()
{
	init_systick();
	//USART2->CR1 |= 1<<5; //enables RXNE
	NVIC_EnableIRQ(USART2_IRQn);

	print("\n\r***REMOTE MODE ACTIVE*** \n\r\0");
	while(1){

		while(EXTI15_10_IRQnHandler()){
			BLED_Toggle(); //actually a hilarious line because this dims the led when the blue button is pressed, makes it go bright and then eventually will go off. Dk why
			EXTI15_IRQnHandler();
			EXTI9_IRQnHandler();
			delay_systick();
		}
		USART2_IRQHandler();
		Systick_Handler();
	}

}
