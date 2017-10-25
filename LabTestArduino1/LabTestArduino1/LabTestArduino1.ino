/*
 Name:		LabTestArduino1.ino
 Created:	10/25/2017 4:37:51 PM
 Author:	hazimgharib
*/

#include <Arduino_FreeRTOS.h>

#define STACK_SIZE 100


void LED(void *pvParameters);

void setup() {

	xTaskCreate(LED, NULL, STACK_SIZE, NULL, 1, NULL);

	vTaskStartScheduler();
}

void loop() {  }

void LED(void *pvParameters) {


}