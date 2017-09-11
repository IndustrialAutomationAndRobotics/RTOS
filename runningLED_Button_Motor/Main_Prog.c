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

void runningLED(void *pvParameters);
void MOTOR(void *pvParameters);
void BUTTON(void *pvParameters);

int main()
{
	DDRB = 0xFF;	// output pin for led
	DDRC = 0x00;	// input pin for button
	DDRD = 0xFF;	// output pin for motor
	DDRE = 0xFF;	// output pin for led

	xTaskCreate(runningLED,NULL,STACK_SIZE, NULL, 0, NULL);
	xTaskCreate(MOTOR,NULL,STACK_SIZE, NULL, 0, NULL);
	xTaskCreate(BUTTON,NULL,STACK_SIZE, NULL, 0, NULL);
	
	vTaskStartScheduler();
		

	return 0;
}



void runningLED(void *pvParameters){

	while(1){
	
		PORTE |= (1<<PE0);
		vTaskDelay(50);
		PORTE &= ~(1<<PE0);

		PORTE |= (1<<PE1);
		vTaskDelay(50);
		PORTE &= ~(1<<PE1);

		PORTE |= (1<<PE2);
		vTaskDelay(50);
		PORTE &= ~(1<<PE2);

		PORTE |= (1<<PE3);
		vTaskDelay(50);
		PORTE &= ~(1<<PE3);

		PORTE |= (1<<PE4);
		vTaskDelay(50);
		PORTE &= ~(1<<PE4);

		PORTE |= (1<<PE5);
		vTaskDelay(50);
		PORTE &= ~(1<<PE5);

		PORTE |= (1<<PE6);
		vTaskDelay(50);
		PORTE &= ~(1<<PE6);

		PORTE |= (1<<PE7);
		vTaskDelay(50);
		PORTE &= ~(1<<PE7);

		taskYIELD();
	}
}

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
	
		taskYIELD();
	}
}

void BUTTON(void *pvParameters){

	while(1){
	
		PORTB = PINC;
		taskYIELD();
	}
}

