#include <stdio.h>
#include <avr/interrupt.h>

/*Scheduler include files*/
#include "FreeRtOSConfig.h"
#include "FreeRTOS.h"
#include "croutine.h"
#include "task.h"		//tasks
#include "semphr.h"		//semaphore
#include "queue.h"		//message queue

/*FreeRTOS Function include files*/
#define STACK_SIZE 100	//minimal stack size from FreeRTOSConfig.h


/*Task declaration/prototype*/
void LED (void *pvParameters);
void MOTORS (void *pvParameters);
void LimitSwitchMonitoring (void *pvParameters);
void LimitSwitch (void *pvParameters);

// Creates a semaphore named BS 
xSemaphoreHandle BS;


/*Start main function*/
int main()
{
	DDRB = 0xFF; //1111 1111
	DDRD = 0xFC; //1111 1100

	//Set limit switch to 1 (unpress)
	PORTD |= (1<<PD0); //1111 1101
	PORTD |= (1<<PD1); //1111 1111

	xTaskCreate(LED,NULL,STACK_SIZE,NULL,1,NULL);					//Task for LED
	xTaskCreate(MOTORS,NULL,STACK_SIZE,NULL,1,NULL);				//Task for motors
	xTaskCreate(LimitSwitchMonitoring,NULL,STACK_SIZE,NULL,1,NULL);	//Task for limit switch monitoring
	xTaskCreate(LimitSwitch,NULL,STACK_SIZE,NULL,2,NULL);			//Task for triggered both limit switch

	//Create a binary semaphore
	vSemaphoreCreateBinary(BS);

	//start the scheduler
	vTaskStartScheduler();

	return 0;
}


// ######################################################
// #  WARNING: DO NOT CHANGE ANYTHING BEFORE THIS LINE  #
// ######################################################


//Start LED function
//Modify based on the given pseudocode
void LED (void *pvParameters) {
	while(1) {
        PORTB &= ~(1<<PB2);
        PORTB |= (1<<PB3);
        PORTB |= (1<<PB4);
        PORTB &= ~(1<<PB5);
        vTaskDelay(20);
		PORTB |= (1<<PB2);
        PORTB &= ~(1<<PB3);
        PORTB &= ~(1<<PB4);
		PORTB |= (1<<PB5);
		vTaskDelay(20);

		taskYIELD();	//context switching
	}
}


/*Start Motors function*/
//Nothing to change here
void MOTORS (void *pvParameters) {
	while(1) {
		if( (PIND & (1<<PD0)) && (PIND & (1<<PD1))) {//Both unpress - Move forward
			PORTD |= (1<<PD2);
			PORTD &= ~(1<<PD3);
			PORTD &= ~(1<<PD4);
			PORTD |= (1<<PD5);
			PORTD |= (1<<PD6);  //enable 1
			PORTD |= (1<<PD7);  //enable 2
		}
		else if(PIND & (1<<PD0)) {//Trigger right switch - Move left
			PORTD &= ~(1<<PD2);
			PORTD |= (1<<PD3);
			PORTD &= ~(1<<PD4);
			PORTD |= (1<<PD5);
			PORTD |= (1<<PD6);  //enable 1
			PORTD |= (1<<PD7);  //enable 2	
		}
		else if(PIND & (1<<PD1)){//Trigger left switch - Move right
			PORTD |= (1<<PD2);
			PORTD &= ~(1<<PD3);
			PORTD |= (1<<PD4);
			PORTD &= ~(1<<PD5);	
			PORTD |= (1<<PD6);  //enable 1
			PORTD |= (1<<PD7);  //enable 2
		}
		else {//Both trigger - stop
			PORTD &= ~(1<<PD6);
			PORTD &= ~(1<<PD7);
		}
		taskYIELD();	//context switching
	}
} //Done task 2


/*LimitSwitchMonitoring function */
void LimitSwitchMonitoring(void *pvParameters)
{
  	while (1)
	{ 
		// If the binary semaphore was created successfully
		if (BS != NULL) // check wether semaphore is created successfully
		{
			//Take the semaphore - don't block if the semaphore is not
        	//immediately available.
			xSemaphoreTake(BS,1);
			
			//if both limit switch are pressed
			if( !(PIND & (1<<PD0)) && !(PIND & (1<<PD1)))
			{ 
				//Give semaphore
				xSemaphoreGive(BS);
			}
			else
			{
				PORTB &= ~(1<<PB0);
				PORTB &= ~(1<<PB7);
			}
		}
		taskYIELD();
	}
}


/*Limit switch function*/
void LimitSwitch(void *pvParameters)
{
	while (1)
	{
		// If the binary semaphore was created successfully
		if(BS != NULL) // check wether semaphore is created successfully
		{
			//if binary semaphore is taken, wait 1 tick to see if it becomes free
			if(xSemaphoreTake(BS,1) == pdTRUE)
			{
				PORTB |= (1<<PB0);
				PORTB |= (1<<PB7);

				//Give semaphore
				xSemaphoreGive(BS);
				vTaskDelay(1);
			}
		}
		taskYIELD();
	}
}
