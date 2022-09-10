/*
 * gpio.c
 *
 *  Created on: Nov 4, 2021
 *      Author: Mitesh Parikh
 */


/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
#include <stdbool.h>
#include "stm32l4xx.h"
#include "LED.h"
#include "printf.h"

int STATE = 0;


/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
void GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = B1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = R1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(R1_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = G1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(G1_GPIO_Port, &GPIO_InitStruct);

	/* EXTI15_10_IRQn interrupt init*/
	// Note you will have to add EXTI15_10_IRQn Interrupt handler function as well
	// This is the interrupt handler for the blue button

	/* EXTI9_5_IRQn interrupt init*/
	// Note you will have to add EXTI9_15_IRQn Interrupt handler function as well
	// This is the interrupt handler for the "Red" and "Green" buttons (R1 and G1)
}

/**
 * Handler for manual mode,
 */
int EXTI15_10_IRQnHandler(void){
	if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13) != 0x00u) //Checks if its flagged
	  {
		if (STATE == 0){ //checks if It is in remote mode
			STATE = 1;
			printf("\n\r***MANUAL OVERRIDE MODE ACTIVE*** \n\r");
			/**BLED_On();
			for (i = 0; i == 79999; i++);
			RLED_Toggle();
			BLED_Toggle();
			WLED_Toggle();
			for (i = 0; i == 79999; i++);
			BLED_Toggle();
			WLED_Toggle();
			for (i = 0; i == 79999; i++);
			BLED_Toggle();
			WLED_Toggle();*/

			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);
			__HAL_GPIO_EXTI_CLEAR_FLAG(GPIO_PIN_13);
			HAL_GPIO_EXTI_Callback(GPIO_PIN_13);
		}
		else{ //functionality when already in manual mode
			STATE = 0;
			__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);
			__HAL_GPIO_EXTI_CLEAR_FLAG(GPIO_PIN_13);
			HAL_GPIO_EXTI_Callback(GPIO_PIN_13);
			printf("\n\r***REMOTE MODE ACTIVE*** \n\r");
		}
	  }
	return STATE;

}
/**
 * Handler for the switch that controls the blue led (Ideally)
 */
void EXTI9_IRQnHandler(void){
	if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_9) != 0x00u)
		  {
		    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9);
		    HAL_GPIO_EXTI_Callback(GPIO_PIN_9);
		  }
}

/**
 * Handler for the switch that controls the blue led (Ideally)
 */
void EXTI15_IRQnHandler(void){
	if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_7) != 0x00u)
		  {
		    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_7);
		    HAL_GPIO_EXTI_Callback(GPIO_PIN_7);
		  }
}

/*void EXTI4_IRQHandler(void){
	HAL_GPIO_EXTI_IRQHANDLER(GPIO_4);
}

void HAL_GPIO_EXTI_CallBack(uint16_t GPIO_Pin){
	if (GPIO_Pin == GPIO_Pin_Num){
		//do things
	}
}*/
