// main.c with demo
// Updated and refactored Larry Kiser copyright 2021


// include project specific header files
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "demo.h"
#include "hello_world.h"
#include "gpio.h"
	
int main(void){

	// initialization code
	System_Clock_Init(); // set System Clock = 80 MHz
	LED_Init();
	UART2_Init(); //functions to use: USART_Read
				  //                  USART_Write
	GPIO_Init();
	
	// application run function
	run_demo() ;
	//hello_world();
}

