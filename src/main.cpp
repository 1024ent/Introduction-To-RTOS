#include <Arduino.h>

int led1pin = 10;
int led2pin = 11;
int led3pin = 12;
int led4pin = 13;
int brightness1 = 0;
int brightness2 = 255;
int fadeAmount = 5;
bool led3state = LOW;
bool led4state = HIGH;

void task1(void * parameters){
  for (;;){
    analogWrite(led1pin, brightness1);
    brightness1 += fadeAmount;

    // Reverse direction if we've reached the maximum brightness
    if (brightness1 <= 0 || brightness1 >= 255) {
      fadeAmount = -fadeAmount;
    }

    vTaskDelay(50 / portTICK_PERIOD_MS);    
  }
}

void task2(void * parameters){
  for (;;){
    analogWrite(led2pin, brightness2);
    brightness2 -= fadeAmount;

    // Reverse direction if we've reached the maximum brightness
    if (brightness2 <= 0 || brightness2 >= 255) {
      fadeAmount = -fadeAmount;
    }

    vTaskDelay(50 / portTICK_PERIOD_MS);    
  }
}

void task3(void * parameters){
  for(;;){
    // Toggle the LED state
    led3state = !led3state;
    digitalWrite(led3pin, led3state);  // Use the toggled state

    vTaskDelay(1000 / portTICK_PERIOD_MS); 
  }
}

void task4(void * parameters){
  for(;;){
    // Toggle the LED state
    led4state = !led4state;
    digitalWrite(led4pin, led4state);  // Use the toggled state

    vTaskDelay(1000 / portTICK_PERIOD_MS); 
  }
}

void setup(){
  Serial.begin(115200);
  vTaskDelay(500 / portTICK_PERIOD_MS); // Add a delay to let Serial initialize

  // Set the pin modes for the LEDs
  pinMode(led1pin, OUTPUT);
  pinMode(led2pin, OUTPUT);
  pinMode(led3pin, OUTPUT);
  pinMode(led4pin, OUTPUT);

  xTaskCreate(
      task1,    // function name
      "Task 1", // task name 
      1024,     // stack size
      NULL,     // task parameters
      1,        // task priority
      NULL      // task handle
  );

  xTaskCreate(
      task2,    // function name
      "Task 2", // task name 
      1024,     // stack size
      NULL,     // task parameters
      1,        // task priority
      NULL      // task handle
  ); 

  xTaskCreate(
      task3,    // function name
      "Task 3", // task name 
      1024,     // stack size
      NULL,     // task parameters
      1,        // task priority
      NULL      // task handle
  );   

  xTaskCreate(
    task4,      // function name
    "Task 4",   // task name 
    1024,       // stack size
    NULL,       // task parameters
    1,          // task priority
    NULL        // task handle
  ); 
}

void loop(){

}
