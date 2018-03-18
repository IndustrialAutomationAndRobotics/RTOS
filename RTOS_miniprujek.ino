#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>

#define STACK_SIZE 100
#define arraySize(x) ((sizeof(x)) / (sizeof(x[0])))

void LED(void *pvParameters);
void MOTOR(void *pvParameters);
void LimitSwitchMonitoring(void *pvParameters);
void LimitSwitch(void *pvParameters);


SemaphoreHandle_t BS;

QueueHandle_t TheQueue;

#define patternLED1 11
#define patternLED2 10
#define patternLED3 9
#define patternLED4 8
#define semaphoreLED1 13
#define semaphoreLED2 2
#define msgQueueLED1 12
#define msgQueueLED2 3
#define MotorRDir 4
#define MotorREn 5
#define MotorLDir 7
#define MotorLEn 6
#define switch1 18
#define switch2 19

uint8_t outputPin[] = {
  
  patternLED1,
  patternLED2,
  patternLED3,
  patternLED4,
  semaphoreLED1,
  semaphoreLED2,
  msgQueueLED1,
  msgQueueLED2,
  MotorRDir,
  MotorREn,
  MotorLDir,
  MotorLEn,
  };
uint8_t inputPin[] = {
  
  switch1,
  switch2,
  };

bool switchState1 = false;
bool switchState2 = false;



void setup() {
  Serial.begin(9600);
  for(uint8_t i = 0; i < arraySize(inputPin); i++){
    pinMode(inputPin[i], INPUT);
  }
  for(uint8_t i = 0; i < arraySize(outputPin); i++){
    pinMode(outputPin[i], OUTPUT);
  }

  xTaskCreate(LED,(const portCHAR *)"LED", STACK_SIZE, NULL, 1, NULL);
  xTaskCreate(MOTOR,(const portCHAR *)"LED", STACK_SIZE, NULL, 1, NULL);
  xTaskCreate(LimitSwitchMonitoring,(const portCHAR *)"LED", STACK_SIZE, NULL, 1, NULL);
  xTaskCreate(LimitSwitch,(const portCHAR *)"LED", STACK_SIZE, NULL, 2, NULL);

  vSemaphoreCreateBinary(BS);

  TheQueue = xQueueCreate(1, sizeof(char));

  vTaskStartScheduler();
}

void loop() {}

void LED(void *pvParameters){

  for(;;){
    
    digitalWrite(patternLED1, LOW);
    digitalWrite(patternLED2, HIGH);
    digitalWrite(patternLED3, HIGH);
    digitalWrite(patternLED4, LOW);
    vTaskDelay(20);
    digitalWrite(patternLED1, HIGH);
    digitalWrite(patternLED2, LOW);
    digitalWrite(patternLED3, LOW);
    digitalWrite(patternLED4, HIGH);
    vTaskDelay(20);
    digitalWrite(patternLED1, LOW);
    digitalWrite(patternLED4, LOW);
    vTaskDelay(20);

    //taskYIELD();
  }
}

void MOTOR(void *pvParameters){

  for(;;){
    
    switchState1 = digitalRead(switch1);
    switchState2 = digitalRead(switch2);

    if((switchState1) && (switchState2)){
      forward();
    }else if((!switchState1) && (!switchState2)){
      motorStop(); 
    }else if(!switchState1){
      left();
    }else if(!switchState2){
      right();
    }
    
    //taskYIELD();
  }
}
void LimitSwitchMonitoring(void *pvParameters){

  static char SendAMessage;
  for(;;){

    switchState1 = digitalRead(switch1);
    switchState2 = digitalRead(switch2);
    
    if((BS != NULL) && (TheQueue != NULL)){
      
      xSemaphoreTake(BS,1);

      xQueueReset(TheQueue);
      if((!switchState1) && (!switchState2)){
        
        SendAMessage = '1';
        Serial.println("1");
        xQueueSendToBack(TheQueue, &SendAMessage, 1);
        
        xSemaphoreGive(BS);
        
      }else if(!switchState1){
        
        SendAMessage = '2';
        Serial.println("2");
        xQueueSendToBack(TheQueue, &SendAMessage, 1);

        xSemaphoreGive(BS);
        
      }else if(!switchState2){
        
        SendAMessage = '3';
        Serial.println("3");
        xQueueSendToBack(TheQueue, &SendAMessage, 1);

        xSemaphoreGive(BS);
      }else{
        
        digitalWrite(msgQueueLED1, LOW);
        digitalWrite(msgQueueLED2, LOW);
        digitalWrite(semaphoreLED1, LOW);
        digitalWrite(semaphoreLED2, LOW);
      }
    }
    
    //taskYIELD();
  }
}

void LimitSwitch(void *pvParameters){

  char ReceiveAMessage;
  for(;;){

    if(BS != NULL){

      if(xSemaphoreTake(BS, 1) == pdTRUE){

        ReceiveAMessage = xQueueReceive(TheQueue, &ReceiveAMessage, 1);
        digitalWrite(semaphoreLED1, LOW);
        digitalWrite(semaphoreLED2, LOW);
        Serial.print("\t");
        Serial.println(ReceiveAMessage);
        if(ReceiveAMessage == '1'){
          Serial.println("receive 1");
          digitalWrite(semaphoreLED1, HIGH);
          digitalWrite(semaphoreLED2, HIGH); 
          digitalWrite(msgQueueLED1, HIGH);
          digitalWrite(msgQueueLED2, HIGH);
          vTaskDelay(10);
          digitalWrite(msgQueueLED1, LOW);
          digitalWrite(msgQueueLED2, LOW);
          vTaskDelay(10);
          
        }else if(ReceiveAMessage == '2'){
          Serial.println("receive 2");
          digitalWrite(msgQueueLED1, HIGH);
          vTaskDelay(10);
          digitalWrite(msgQueueLED1, LOW);
          vTaskDelay(10);
          
        }else if(ReceiveAMessage == '3'){
          Serial.println("receive 3");
          digitalWrite(msgQueueLED2, HIGH);
          vTaskDelay(10);
          digitalWrite(msgQueueLED2, LOW);
          vTaskDelay(10);
        }
        
        xSemaphoreGive(BS);
        vTaskDelay(1);
      }
    }
    //taskYIELD();
  }
}

void forward(){

  digitalWrite(MotorRDir, HIGH);
  digitalWrite(MotorREn, HIGH);
  digitalWrite(MotorLDir, LOW);
  digitalWrite(MotorLEn, HIGH);
}

void left(){

  digitalWrite(MotorRDir, HIGH);
  digitalWrite(MotorREn, HIGH);
  digitalWrite(MotorLDir, HIGH);
  digitalWrite(MotorLEn, HIGH);
}

void right(){

  digitalWrite(MotorRDir, LOW);
  digitalWrite(MotorREn, HIGH);
  digitalWrite(MotorLDir, LOW);
  digitalWrite(MotorLEn, HIGH);
}

void motorStop(){

  digitalWrite(MotorRDir, LOW);
  analogWrite(MotorREn, 0);
  digitalWrite(MotorLDir, LOW);
  analogWrite(MotorLEn, 0);
}

