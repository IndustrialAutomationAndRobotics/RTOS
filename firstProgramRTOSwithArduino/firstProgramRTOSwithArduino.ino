#include <Arduino_FreeRTOS.h>

#define STACK_SIZE 100

void LED(void *prParameters);
void MOTOR(void *prParameters);

void setup() {

 Serial.begin(9600);

 while(!Serial){
  ;
 }

 xTaskCreate(
  LED
  , NULL
  , STACK_SIZE
  , NULL
  , 0
  , NULL);

  xTaskCreate(
  LED
  , NULL
  , STACK_SIZE
  , NULL
  , 0
  , NULL);
}

void loop() {

}
