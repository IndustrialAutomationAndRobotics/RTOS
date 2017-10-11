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
void Motor(void *pvParameters);


int main()
{
	DDRB = 0xFF; // 1111 1111
	DDRD = 0xFC; // 1111 1100

	PORTD |= (1<<PD6);
	PORTD |= (1<<PD7);

	PORTD |= (1<<PD0);
	PORTD |= (1<<PD1);

	xTaskCreate(LED,NULL,STACK_SIZE, NULL, 0, NULL);
	xTaskCreate(Motor,NULL,STACK_SIZE, NULL, 0, NULL);
	
	vTaskStartScheduler();
	
	return 0;
}


void LED(void *pvParameters){

	while(1){

		PORTB &= ~(1<<PB0);
		PORTB &= ~(1<<PB1);
		PORTB &= ~(1<<PB2);
		PORTB |= (1<<PB3);
		PORTB |= (1<<PB4);
		PORTB &= ~(1<<PB5);
		PORTB &= ~(1<<PB6);
		PORTB &= ~(1<<PB7);
		vTaskDelay(20);

		PORTB |= (1<<PB2);
		PORTB &= ~(1<<PB3);
		PORTB &= ~(1<<PB4);
		PORTB |= (1<<PB5);
		vTaskDelay(20);

		PORTB |= (1<<PB1);
		PORTB &= ~(1<<PB3);
		PORTB &= ~(1<<PB4);
		PORTB |= (1<<PB6);
		vTaskDelay(20);

		PORTB |= (1<<PB0);
		PORTB &= ~(1<<PB1);
		PORTB &= ~(1<<PB6);
		PORTB |= (1<<PB7);
		vTaskDelay(20);
		taskYIELD();
	}
}

void Motor(void *pvParameters){

	while(1){

		if((PIND & (1 << PD0)) && (PIND & (1 << PD1))){
		
			PORTD |= (1<<PD6);
			PORTD |= (1<<PD7);

			PORTD |= (1<<PD2);
			PORTD &= ~(1<<PD3);
		
			PORTD |= (1<<PD4);
			PORTD &= ~(1<<PD5);

			
		}else if(PIND & (1 << PD0)){
		

			PORTD |= (1<<PD6);
			PORTD |= (1<<PD7);

			PORTD |= (1<<PD3);
			PORTD &= ~(1<<PD2);
		
			PORTD |= (1<<PD4);
			PORTD &= ~(1<<PD5);
			
		}else if(PIND & (1 << PD1)){
		
			PORTD |= (1<<PD6);
			PORTD |= (1<<PD7);

			PORTD |= (1<<PD2);
			PORTD &= ~(1<<PD3);
		
			PORTD |= (1<<PD5);
			PORTD &= ~(1<<PD4);
			
		}else{

			
			PORTD &= ~(1<<PD6);
			PORTD &= ~(1<<PD7);
		}
		
		taskYIELD();

	}
}

