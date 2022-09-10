// Based on code from Yifeng Zhu with University of Maine
// Extended by Larry Kiser, RIT April 1, 2021
// Documentation updates for clarity L. Kiser RIT July 15, 2021
//				also changed 3UL and 1UL to (uint32_t)3 and (uint32_t)1 respectively

#include "LED.h"


//******************************************************************************************
// Green LED on Nucleo board is LD2 Green. This is hard wired to GPIO pin PA5.
//******************************************************************************************
#define NUCLEO_GREEN_LED_PIN (5)	// GPIO PA5

// project specific manually connected LEDs on breadboard shield.
#define ARDUINO_D12 (6)				// GPIO PA6 -- hard wired to Arduino D12
#define ARDUINO_D11 (7)				// GPIO PA7 -- hard wired to Arduino D11
#define ARDUINO_D10 (8)				// GPIO PA8 -- hard wired to Arduino D10

// GPIO Output initialization for GPIO banks A, B, C, and D only
// Expects GPIO to be GPIOA, GPIOB, GPIOC, or GPIOD.
// pin is expected to be 0 through 15
// Note -- if the clock is not enabled the 16 GPIO pins are non-functional!
void GPIO_Output_Init( GPIO_TypeDef *GPIO, uint32_t pin )
{
	// Enable the peripheral clocks of for GPIO
	if ( GPIO == GPIOA )
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN ;
	else if ( GPIO == GPIOB )
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN ;
	else if ( GPIO == GPIOC )
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN ;
	else if ( GPIO == GPIOD )
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN ;
	else
		return ;

	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	GPIO->MODER &= ~( (uint32_t)3 << ( 2 * pin ) ) ;  // clear to input mode (00)
	GPIO->MODER |= (uint32_t)1 << ( 2 * pin ) ;      //  Output(01)
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	GPIO->OSPEEDR &= ~( (uint32_t)3 << ( 2 * pin ) ) ;	// set to cleared which is low speed
	GPIO->OSPEEDR |=   (uint32_t)3 << ( 2 * pin ) ;  // High speed
	
	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	GPIO->OTYPER &= ~( (uint32_t)1 << pin ) ;       // Push-pull
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	GPIO->PUPDR   &= ~( (uint32_t)3 << ( 2 * pin ) ) ;  // No pull-up, no pull-down
}

// set up PA5, PA6, and PA7 to drive LEDs
void LED_Init(void){
	GPIO_Output_Init( GPIOA, NUCLEO_GREEN_LED_PIN ) ;	// hard wired PA5 to on-board LD2 LED
	GPIO_Output_Init( GPIOA, ARDUINO_D12 ) ;		// init PA6 as output (D12)
	GPIO_Output_Init( GPIOA, ARDUINO_D11 ) ;		// init PA7 as output (D11)
	GPIO_Output_Init( GPIOA, ARDUINO_D10 ) ;		// init PA8 as output (D10)
}

//******************************************************************************************
// Turn Green LED On and GPIOA 6 and 7 to ON
//******************************************************************************************
void GLED_On(void){
	GPIOA->ODR |= (uint32_t)1 << NUCLEO_GREEN_LED_PIN ; // PA5
}

void RLED_On(void){
	GPIOA->ODR |= (uint32_t)1 << ARDUINO_D12 ;	// PA6
}

void BLED_On(void){
	GPIOA->ODR |= (uint32_t)1 << ARDUINO_D11 ;	// PA7
}

void WLED_On(void){
	GPIOA->ODR |= (uint32_t)1 << ARDUINO_D10 ;	// PA8
}

//******************************************************************************************
// Turn Green LED Off and GPIOA 6 and 7 to OFF
//******************************************************************************************
void LED_Off(void){
	GPIOA->ODR &= ~( (uint32_t)1 << NUCLEO_GREEN_LED_PIN );
	GPIOA->ODR &= ~( (uint32_t)1 << ARDUINO_D12 ) ;	// PA6
	GPIOA->ODR &= ~( (uint32_t)1 << ARDUINO_D11 ) ;	// PA7
	GPIOA->ODR &= ~( (uint32_t)1 << ARDUINO_D10 ) ;	// PA8
}

void GLED_Off(void){
	GPIOA->ODR &= ~( (uint32_t)1 << NUCLEO_GREEN_LED_PIN );
}

void RLED_Off(void){
	GPIOA->ODR &= ~( (uint32_t)1 << ARDUINO_D12 ) ;	// PA6
}

void BLED_Off(void){
	GPIOA->ODR &= ~( (uint32_t)1 << ARDUINO_D11 ) ;	// PA7
}

void WLED_Off(void){
	GPIOA->ODR &= ~( (uint32_t)1 << ARDUINO_D10 ) ;	// PA8
}

//******************************************************************************************
// Set Green LD2 Nucleo LED and GPIOA 6 and 7 to opposite states
//******************************************************************************************
void GLED_Toggle(void){
	GPIOA->ODR ^= (uint32_t)1 << NUCLEO_GREEN_LED_PIN ;
}

void RLED_Toggle(void){
	GPIOA->ODR ^= (uint32_t)1 << ARDUINO_D12 ;	// PA6
}

void BLED_Toggle(void){
	GPIOA->ODR ^= (uint32_t)1 << ARDUINO_D11 ;	// PA7
}

void WLED_Toggle(void){
	GPIOA->ODR ^= (uint32_t)1 << ARDUINO_D10 ;	// PA8
}
