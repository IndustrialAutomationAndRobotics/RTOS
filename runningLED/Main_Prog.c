#include <stdio.h>
#include <avr/interrupt.h>

/*Scheduler include files*/
#include "FreeRTOS.h"
#include "croutine.h"
#include "task.h"		//tasks
#include "semphr.h"		//semaphore
#include "queue.h"		//message queue

/*FreeRTOS Function include files*/
#define STACK_SIZE 100	//minimal stack size from FreeRTOSConfig.h

// ######################################################
// #  WARNING: DO NOT CHANGE ANYTHING BEFORE THIS LINE  #
// ######################################################

void LED(void *pvParameters);

int main()
{
	DDRB = 0xFF; // Make port B as OUTPUT

	xTaskCreate(LED,NULL,STACK_SIZE, NULL, 0, NULL);
	
	vTaskStartScheduler();
		

	return 0;
}


void LED(void *pvParameters){

	while(1){
	
		PORTB |= (1<<PB0); //Set bit to high
		vTaskDelay(50);
		PORTB &= ~(1<<PB0); // Set bit to low
		
		PORTB |= (1<<PB1); //Set bit to high
		vTaskDelay(50);
		PORTB &= ~(1<<PB1); // Set bit to low
		
		PORTB |= (1<<PB2); //Set bit to high
		vTaskDelay(50);
		PORTB &= ~(1<<PB2); // Set bit to low
		
		PORTB |= (1<<PB3); //Set bit to high
		vTaskDelay(50);
		PORTB &= ~(1<<PB3); // Set bit to low
		
		PORTB |= (1<<PB4); //Set bit to high
		vTaskDelay(50);
		PORTB &= ~(1<<PB4); // Set bit to low
		
		PORTB |= (1<<PB5); //Set bit to high
		vTaskDelay(50);
		PORTB &= ~(1<<PB5); // Set bit to low
		
		PORTB |= (1<<PB6); //Set bit to high
		vTaskDelay(50);
		PORTB &= ~(1<<PB6); // Set bit to low
		
		PORTB |= (1<<PB7); //Set bit to high
		vTaskDelay(50);
		PORTB &= ~(1<<PB7); // Set bit to low
		

		taskYIELD();
	}
}
