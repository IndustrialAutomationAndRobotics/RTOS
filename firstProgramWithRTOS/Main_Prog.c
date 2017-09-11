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
	DDRB = 0xFF;

	xTaskCreate(LED,NULL,STACK_SIZE, NULL, 0, NULL);
	
	vTaskStartScheduler();
		

	return 0;
}
/*
void LED(){


	while(1){
	
		PORTB = ~PORTB;
		_delay_ms(1000);
	}

}
*/

void LED(void *pvParameters){

	while(1){
	
		PORTB = ~PORTB;
		vTaskDelay(50);
		taskYIELD();
	}
}
