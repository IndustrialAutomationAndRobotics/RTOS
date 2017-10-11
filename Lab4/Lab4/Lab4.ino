/*
 Name:		Lab4.ino
 Created:	10/12/2017 3:13:02 AM
 Author:	HazimGharib
 Description: Code for Lab 4 class RTOS. Use simulation file in ProteusSimulation/Arduino Mega 2560
 */

#include <Arduino_FreeRTOS.h>

#define STACK_SIZE 100

// Define the output pin
// LED pin
#define led1 22
#define led2 23
#define led3 24
#define led4 25
#define led5 26
#define led6 27
#define led7 28
#define led8 29

// Motor pin
#define motorA1 36
#define motorA2  37
#define motorAEn A0
#define motorB1 34
#define motorB2 35
#define motorBEn A1

// Define the input pin
#define buttonLeft 32
#define buttonRight 33

uint8_t outputPin[] = {

	led1,
	led2,
	led3,
	led4,
	led5,
	led6,
	led7,
	led8,
	motorA1,
	motorA2,
	motorAEn,
	motorB1,
	motorB2,
	motorBEn,
};

uint8_t inputPin[] = {

	buttonLeft,
	buttonRight,
};

void led(void *prParameters);
void motor(void *prParameters);

void setup() {

	// Set output pin as OUTPUT
	for (uint8_t i = 0; i < sizeof(outputPin); i++) {

		pinMode(outputPin[i], OUTPUT);

	}

	// Set input pin as INPUT
	for (uint8_t i = 0; i < sizeof(inputPin); i++) {

		pinMode(inputPin[i], INPUT_PULLUP);
	}

	xTaskCreate(led, NULL, STACK_SIZE, NULL, 0, NULL);
	xTaskCreate(motor, NULL, STACK_SIZE, NULL, 0, NULL);

	vTaskStartScheduler();
}

void loop() {}

void led(void *prParameters) {

	uint8_t i = 3;
	uint8_t j = 4;

	for (;;) {

		digitalWrite(outputPin[i], HIGH);
		digitalWrite(outputPin[j], HIGH);
		vTaskDelay(20);
		digitalWrite(outputPin[i], LOW);
		digitalWrite(outputPin[j], LOW);

		if (i == 0) {
			i = 3;
			j = 4;
		}
		else {
			i--;
			j++;
		}

		taskYIELD();
	}
}

void motor(void *prParameter) {

	uint8_t leftButtonState = 0;
	uint8_t rightButtonState = 0;

	for (;;) {

		leftButtonState = digitalRead(buttonLeft);
		rightButtonState = digitalRead(buttonRight);

		if ((leftButtonState) && (rightButtonState)) {

			analogWrite(motorAEn, 255);
			digitalWrite(motorA1, HIGH);
			digitalWrite(motorA2, LOW);

			analogWrite(motorBEn, 255);
			digitalWrite(motorB1, HIGH);
			digitalWrite(motorB2, LOW);
		}
		else if ((leftButtonState) && !(rightButtonState)) {

			analogWrite(motorAEn, 255);
			digitalWrite(motorA1, LOW);
			digitalWrite(motorA2, HIGH);

			analogWrite(motorBEn, 255);
			digitalWrite(motorB1, HIGH);
			digitalWrite(motorB2, LOW);
		}
		else if (!(leftButtonState) && (rightButtonState)) {

			analogWrite(motorAEn, 255);
			digitalWrite(motorA1, HIGH);
			digitalWrite(motorA2, LOW);

			analogWrite(motorBEn, 255);
			digitalWrite(motorB1, LOW);
			digitalWrite(motorB2, HIGH);
		}
		else {

			analogWrite(motorAEn, 0);
			analogWrite(motorBEn, 0);
		}
	taskYIELD();
	}
}