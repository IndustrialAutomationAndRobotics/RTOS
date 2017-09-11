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

void INPUT(void *pvParameters);

int main()
{
	DDRC = 0x00;	// configure portC as input
	DDRB = 0xFF;	// configure portB as output

	xTaskCreate(INPUT,NULL,STACK_SIZE, NULL, 0, NULL);
	
	vTaskStartScheduler();
		

	return 0;
}


void INPUT(void *pvParameters){

	while(1){
	
		PORTB = PINC;
		taskYIELD();
	}
}
