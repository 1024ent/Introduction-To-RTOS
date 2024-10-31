#include <Arduino.h>

TaskHandle_t LEDTaskHandle = NULL;
TaskHandle_t SwitchTaskHandle = NULL;

#define LED_PIN 11      // LED connected to digital pin 11
#define SWITCH_PIN 12       // Slide Switch connected to digital pin 12

// Task to blink LED
void LEDTask(void *pvparameter){
    pinMode(LED_PIN, OUTPUT);

    while(1){
        digitalWrite(LED_PIN, HIGH);    // Turn the LED on
        vTaskDelay(pdMS_TO_TICKS(500)); // Wait for 500ms
        digitalWrite(LED_PIN, LOW);     // Turn the LED off
        vTaskDelay(pdMS_TO_TICKS(500)); // Wait for 500ms
    }
}

// Task to monitor slide switch press
void SwitchTask(void *pvparameter){
    pinMode(SWITCH_PIN, INPUT);     // Set slide switch pin as input 

    while(1){
        if(digitalRead(SWITCH_PIN) == LOW){
            Serial.println("Slide switch on. Stopping scheduler...");
            vTaskEndScheduler();    // End the scheduler
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // Check the switch every 100 ms
    }
}

void setup(){
    Serial.begin(115200);

    // Create tasks
    xTaskCreate(LEDTask, "LED TASK", 1024, NULL, 1, &LEDTaskHandle);
    xTaskCreate(SwitchTask, "Switch Task", 1024, NULL, 1, &SwitchTaskHandle);

    // Start the FreeRTOS scheduler
    Serial.println("Starting scheduler...");
    vTaskStartScheduler();
}

void loop(){
    
}
