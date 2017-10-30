/*
 Name:		LabTestArduino1.ino
 Created:	10/25/2017 4:37:51 PM
 Author:	hazimgharib
*/

#include <Arduino_FreeRTOS.h>

#define STACK_SIZE 100
#define arraySize(x) ((sizeof(x)) / (sizeof(x[0])))

#define led_1 22
#define led_2 23
#define led_3 24
#define led_4 25
#define led_5 26
#define led_6 27
#define led_7 28
#define led_8 29

#define motorA1 36
#define motorA2 37
#define motorAen A0
#define motorB1 34
#define motorB2 35
#define motorBen A1

int ledPin[] = {

	led_1,
	led_2,
	led_3,
	led_4,
	led_5,
	led_6,
	led_7,
	led_8,
};

uint8_t motorPin[] = {

	motorA1,
	motorA2,
	motorAen,
	motorB1,
	motorB2,
	motorBen,
};


void LED(void *pvParameters);
void MOTOR(void *pvParameters);

void setup() {

	for (uint8_t i = 0; i < arraySize(ledPin); i++) {

		pinMode(ledPin[i], OUTPUT);
		digitalWrite(ledPin[i], LOW);
	}
	for (uint8_t i = 0; i < arraySize(motorPin); i++) {

		pinMode(motorPin[i], OUTPUT);
	}

	digitalWrite(motorAen, LOW);
	digitalWrite(motorBen, LOW);

	xTaskCreate(LED, NULL, STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(MOTOR, NULL, STACK_SIZE, NULL, 1, NULL);

	vTaskStartScheduler();
}

void loop() {  }

void LED(void *pvParameters) {

	for (;;) {
		
		digitalWrite(ledPin[3], HIGH);
		digitalWrite(ledPin[4], HIGH);
		vTaskDelay(20);
		digitalWrite(ledPin[3], LOW);
		digitalWrite(ledPin[4], LOW);
		digitalWrite(ledPin[2], HIGH);
		digitalWrite(ledPin[5], HIGH);
		vTaskDelay(20);
		digitalWrite(ledPin[2], LOW);
		digitalWrite(ledPin[5], LOW);
		digitalWrite(ledPin[1], HIGH);
		digitalWrite(ledPin[6], HIGH);
		vTaskDelay(20);
		digitalWrite(ledPin[1], LOW);
		digitalWrite(ledPin[6], LOW);
		digitalWrite(ledPin[0], HIGH);
		digitalWrite(ledPin[7], HIGH);
		vTaskDelay(20);
		digitalWrite(ledPin[0], LOW);
		digitalWrite(ledPin[7], LOW);
		
		taskYIELD();
	}
}

void MOTOR(void *pvParameters) {

	for (;;) {

		digitalWrite(motorAen, HIGH);
		digitalWrite(motorBen, HIGH);

		digitalWrite(motorA1, HIGH);
		digitalWrite(motorA2, LOW);
		digitalWrite(motorB1, HIGH);
		digitalWrite(motorB2, LOW);
	}

}