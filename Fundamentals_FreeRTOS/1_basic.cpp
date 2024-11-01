#include <Arduino.h>

#define LEDC_CHANNEL_0 0  // PWM channel for LED 1
#define LEDC_CHANNEL_1 1  // PWM channel for LED 2
#define PWM_FREQ 5000  // 5 kHz PWM frequency
#define PWM_RES 8      // 8-bit resolution (0-255)
#define PWM_MAX_DUTY 255
#define PWM_MIN_DUTY 0

int sw1 = 13;
int led0pin = 4;
int led1pin = 5;
int led2pin = 6;
int led3pin = 7;
int led4pin = 8;
int switchState = 0; 
bool led3state = LOW;
bool led4state = LOW;

void task0(void * parameters){
  for(;;){
    //read the state of the switch value
    switchState = digitalRead(sw1);
    if (switchState == HIGH ) //if it is,the state is HIGH
    {
      digitalWrite(led0pin, HIGH); //turn the led on
    }
    else
    {
      digitalWrite(led0pin, LOW); //turn the led off
    }
  }
}

void task1(void * parameters){
  int duty = PWM_MIN_DUTY;
  bool increasing = true;

  for (;;){
    // Fade LED from dim to bright, then bright to dim
    if (increasing) {
        for (duty = PWM_MIN_DUTY; duty <= PWM_MAX_DUTY; duty++) {
            ledcWrite(LEDC_CHANNEL_0, duty);  // Set PWM duty cycle for LED 1
            vTaskDelay(10 / portTICK_PERIOD_MS);  // Delay to create slow fade effect
        }
        increasing = false;  // Switch to decreasing
    } else {
        for (duty = PWM_MAX_DUTY; duty >= PWM_MIN_DUTY; duty--) {
            ledcWrite(LEDC_CHANNEL_0, duty);  // Set PWM duty cycle for LED 1
            vTaskDelay(10 / portTICK_PERIOD_MS);  // Delay to create slow fade effect
        }
        increasing = true;  // Switch to increasing
    }

    vTaskDelay(500 / portTICK_PERIOD_MS);  // Pause between cycles
  }
}

void task2(void * parameters){
  int duty = PWM_MAX_DUTY;
  bool decreasing = true;

  for (;;){
    // Fade LED from bright to dim, then dim to bright
    if (decreasing) {
        for (duty = PWM_MAX_DUTY; duty >= PWM_MIN_DUTY; duty--) {
            ledcWrite(LEDC_CHANNEL_1, duty);  // Set PWM duty cycle for LED 2
            vTaskDelay(10 / portTICK_PERIOD_MS);  // Delay to create slow fade effect
        }
        decreasing = false;  // Switch to increasing
    } else {
        for (duty = PWM_MIN_DUTY; duty <= PWM_MAX_DUTY; duty++) {
            ledcWrite(LEDC_CHANNEL_1, duty);  // Set PWM duty cycle for LED 2
            vTaskDelay(10 / portTICK_PERIOD_MS);  // Delay to create slow fade effect
        }
        decreasing = true;  // Switch to decreasing
    }

    vTaskDelay(500 / portTICK_PERIOD_MS);  // Pause between cycles
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

    vTaskDelay(2000 / portTICK_PERIOD_MS); 
  }
}

void setup(){
  Serial.begin(115200);
  vTaskDelay(500 / portTICK_PERIOD_MS); // Add a delay to let Serial initialize

  // Set the pin modes for the LEDs
  pinMode(sw1, INPUT);
  pinMode(led0pin, OUTPUT);
  ledcSetup(LEDC_CHANNEL_0, PWM_FREQ, PWM_RES);
  ledcAttachPin(led1pin, LEDC_CHANNEL_0);
  ledcSetup(LEDC_CHANNEL_1, PWM_FREQ, PWM_RES);
  ledcAttachPin(led2pin, LEDC_CHANNEL_1);
  pinMode(led3pin, OUTPUT);
  pinMode(led4pin, OUTPUT);

  xTaskCreate(
      task0,    // function name
      "Task 0", // task name 
      1024,     // stack size
      NULL,     // task parameters
      1,        // task priority
      NULL      // task handle
  );

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