/*
 Name:		arduinoRTOS.ino
 Created:	10/11/2017 3:00:25 AM
 Author:	HazimGharib	
*/

#include <Arduino_FreeRTOS.h>

#define STACK_SIZE 100

void led1(void *prParameters);
void led2(void *prParameters);

void setup() {

	xTaskCreate(led1, NULL, STACK_SIZE, NULL, 0, NULL);
	xTaskCreate(led2, NULL, STACK_SIZE, NULL, 0, NULL);

	vTaskStartScheduler();
}

void loop() {}

void led1(void *prParameters) {

	pinMode(10, OUTPUT);

	for (;;) {

		digitalWrite(10, HIGH);
		vTaskDelay(300);
		digitalWrite(10, LOW);
		vTaskDelay(300);
		taskYIELD();
	}
}

void led2(void *prParameters) {

	pinMode(11, OUTPUT);

	for (;;) {

		digitalWrite(11, HIGH);
		vTaskDelay(500);
		digitalWrite(11, LOW);
		vTaskDelay(500);
		taskYIELD();
	}
}

