#include <Arduino.h>

// Define pin numbers
#define LED_PIN 11      // LED connected to digital pin 11
#define SWITCH_PIN 12       // Slide Switch connected to digital pin 12

// Task handle
TaskHandle_t taskHandle = NULL;

// Function to read the switch state and control the LED
void vTaskToggleLED(void *pvParameters){
  while(1){
    // Read the state of the switch (LOW when on, HIGH when OFF)
    if(digitalRead(SWITCH_PIN) == LOW){
      digitalWrite(LED_PIN, HIGH);    // Turn ON the LED
    } else {
      digitalWrite(LED_PIN, LOW);     // Turn OFF the LED
    }
    vTaskDelay(pdMS_TO_TICKS(100));   // Delay for 100ms
  }
}

void setup(){
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  xTaskCreate(vTaskToggleLED, "Toggle LED", 2048, NULL, 1, &taskHandle);

  vTaskStartScheduler();
}

void loop(){
  // This loop will run for 10 seconds, then stop the scheduler
  static uint32_t startTime = millis();
  if(millis() - startTime > 10000) {  // 10 seconds
    Serial.println("Stopping scheduler...");
    vTaskEndScheduler();
  }
}
