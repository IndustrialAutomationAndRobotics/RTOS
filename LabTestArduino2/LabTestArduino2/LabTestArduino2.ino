/*
 Name:		LabTestArduino2.ino
 Created:	10/26/2017 12:26:36 AM
 Author:	hazimgharib
*/

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

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

#define buttonLeft 32
#define buttonRight 33

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

uint8_t buttonPin[] = {

	buttonLeft,
	buttonRight,
};

void LED(void *pvParameters);
void MOTORS(void *pvParameters);
void LimitSwitchMonitoring(void *pvParameters);
void LimitSwitch(void *pvParameters);

SemaphoreHandle_t BS;

void setup() {

	for (uint8_t i = 0; i < arraySize(ledPin); i++) {

		pinMode(ledPin[i], OUTPUT);
		digitalWrite(ledPin[i], LOW);
	}
	for (uint8_t i = 0; i < arraySize(motorPin); i++) {

		pinMode(motorPin[i], OUTPUT);
	}
	for (uint8_t i = 0; i < arraySize(buttonPin); i++) {
		
		pinMode(buttonPin[i], INPUT_PULLUP);
	}

	digitalWrite(motorAen, LOW);
	digitalWrite(motorBen, LOW);

	xTaskCreate(LED, NULL, STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(MOTORS, NULL, STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(LimitSwitchMonitoring, NULL, STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(LimitSwitch, NULL, STACK_SIZE, NULL, 2, NULL);

	vSemaphoreCreateBinary(BS);

	vTaskStartScheduler();


}

void loop() {}

void LED(void *pvParameters) {
	
	for (;;) {

		digitalWrite(led_3, LOW);
		digitalWrite(led_4, HIGH);
		digitalWrite(led_5, HIGH);
		digitalWrite(led_6, LOW);
		vTaskDelay(20);
		digitalWrite(led_4, LOW);
		digitalWrite(led_3, HIGH);
		digitalWrite(led_6, HIGH);
		digitalWrite(led_5, LOW);
		vTaskDelay(20);
		taskYIELD();
	}
}

void MOTORS(void *pvParameters) {

	for (;;) {

		bool buttonLeftState = digitalRead(buttonLeft);
		bool buttonRightState = digitalRead(buttonRight);

		if (buttonLeftState) {

			digitalWrite(motorAen, HIGH);
			digitalWrite(motorBen, HIGH);
			
			digitalWrite(motorA1, HIGH);
			digitalWrite(motorA2, LOW);
			digitalWrite(motorB1, HIGH);
			digitalWrite(motorB2, LOW);
		}
		else {

			digitalWrite(motorAen, LOW);
			digitalWrite(motorBen, LOW);
		}

		taskYIELD();
	}
}

void LimitSwitchMonitoring(void *pvParameters) {

	for (;;) {

		taskYIELD();
	}
}

void LimitSwitch(void *pvParameters) {

	for (;;) {

		taskYIELD();
	}
}