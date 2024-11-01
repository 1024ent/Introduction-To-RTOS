#include <Arduino.h>

TaskHandle_t LEDTaskHandle = NULL;
TaskHandle_t LDRTaskHandle = NULL;

#define LED_PIN 4          // LED connected to digital pin 13
#define LDR_PIN 14          // LDR connected to analog pin A0
#define LIGHT_THRESHOLD 500 // Threshold for light level (adjust as needed)

void LEDTask(void *pvParameters) {
  // Initial delay to keep the LED on before the first toggle
  vTaskDelay(pdMS_TO_TICKS(1000)); // Wait 1 second before toggling

  for (;;) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    Serial.println("LED Toggled");
    vTaskDelay(pdMS_TO_TICKS(1000)); // Toggle every 1 second

    // Suspend the task after toggling once
    vTaskSuspend(NULL);
  }
}

void LDRTask(void *pvParameters) {
  // This task continuously monitors light levels from the LDR
  for (;;) {
    int lightLevel = analogRead(LDR_PIN); // Read LDR value
    Serial.print("Light Level: ");
    Serial.println(lightLevel);

    if (lightLevel < LIGHT_THRESHOLD) {
      // If it's dark, resume the LED task to allow it to toggle
      Serial.println("It's dark. Resuming LED Task.");
      vTaskResume(LEDTaskHandle);
    } else {
      // If it's bright, suspend the LED task to conserve energy
      Serial.println("It's bright. Suspending LED Task.");
      vTaskSuspend(LEDTaskHandle);
    }

    vTaskDelay(pdMS_TO_TICKS(500)); // Check light level every 500ms
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);   // Start with the LED off

  // Create LED Task, suspended initially
  xTaskCreate(LEDTask, "LED Task", 1024, NULL, 1, &LEDTaskHandle);

  // Create LDR Task
  xTaskCreate(LDRTask, "LDR Task", 2048, NULL, 1, &LDRTaskHandle);
}

void loop() {
  // FreeRTOS takes control after setup, loop remains empty
}
