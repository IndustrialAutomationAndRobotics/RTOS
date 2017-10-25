/*
 Name:		LabTest2Arduino.ino
 Created:	10/25/2017 2:09:11 PM
 Author:	hazimgharib
*/

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#define STACK_SIZE 100

void LED(void *pvParameters);
void MOTORS(void *pvParameters);
void LimitSwitchMonitoring(void *pvParameters);
void LimitSwitch(void *pvParameters);

xSemaphoreHandle BS;

void setup() {

}

void loop() {
  
}
