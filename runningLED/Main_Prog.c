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
	
	
		

	DDRD = 0xFF;

	xTaskCreate(MOTOR,NULL,STACK_SIZE, NULL, 0, NULL);
	
	vTaskStartScheduler();
		

	return 0;
}


void LED(void *pvParameters){

	while(1){
	
		PORTB &= (1<<PB0); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB0); // Set bit to low
		
		PORTB &= (1<<PB1); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB1); // Set bit to low
		
		PORTB &= (1<<PB2); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB2); // Set bit to low
		
		PORTB |= (1<<PB3); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB3); // Set bit to low
		
		PORTB |= (1<<PB4); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB4); // Set bit to low
		
		PORTB &= (1<<PB5); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB5); // Set bit to low
		
		PORTB &= (1<<PB6); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB6); // Set bit to low
		
		PORTB &= (1<<PB7); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB7); // Set bit to low
		

		
		PORTB &= (1<<PB0); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB0); // Set bit to low
		
		PORTB &= (1<<PB1); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB1); // Set bit to low
		
		PORTB |= (1<<PB2); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB2); // Set bit to low
		
		PORTB &= (1<<PB3); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB3); // Set bit to low
		
		PORTB &= (1<<PB4); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB4); // Set bit to low
		
		PORTB |= (1<<PB5); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB5); // Set bit to low
		
		PORTB &= (1<<PB6); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB6); // Set bit to low
		
		PORTB &= (1<<PB7); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB7); // Set bit to low

		
		PORTB &= (1<<PB0); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB0); // Set bit to low
		
		PORTB |= (1<<PB1); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB1); // Set bit to low
		
		PORTB &= (1<<PB2); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB2); // Set bit to low
		
		PORTB &= (1<<PB3); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB3); // Set bit to low
		
		PORTB &= (1<<PB4); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB4); // Set bit to low
		
		PORTB &= (1<<PB5); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB5); // Set bit to low
	
		PORTB |= (1<<PB6); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB6); // Set bit to low
		
		PORTB &= (1<<PB7); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB7); // Set bit to low

		
		PORTB |= (1<<PB0); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB0); // Set bit to low
		
		PORTB &= (1<<PB1); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB1); // Set bit to low
		
		PORTB &= (1<<PB2); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB2); // Set bit to low
		
		PORTB &= (1<<PB3); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB3); // Set bit to low
		
		PORTB &= (1<<PB4); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB4); // Set bit to low
		
		PORTB &= (1<<PB5); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB5); // Set bit to low
		
		PORTB &= (1<<PB6); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB6); // Set bit to low
		
		PORTB |= (1<<PB7); //Set bit to high
		vTaskDelay(20);
		PORTB &= ~(1<<PB7); // Set bit to low
		

void MOTOR(void *pvParameters){

while(1){

		// Rotates Motor AntiClockwise
		PORTD = 0x01; //00000001
		vTaskDelay(100);

		// Stops Motor
		PORTD = 0x00; //00000000
		vTaskDelay(100);

		// Rotates Motor Clockwise
		PORTD = 0x02; //00000010
		vTaskDelay(100);

		// Stops Motor
		PORTD = 0x03; //00000011
		vTaskDelay(100);

	

	
   		// Rotates Motor AntiClockwise
		PORTD = 0x01; //00000001
		vTaskDelay(100);

		// Stops Motor
		PORTD = 0x00; //00000000
		vTaskDelay(100);

		// Rotates Motor Clockwise
		PORTD = 0x02; //00000010
		vTaskDelay(100);

		// Stops Motor
		PORTD = 0x03; //00000011
		vTaskDelay(100);}


		taskYIELD();
	}
}
