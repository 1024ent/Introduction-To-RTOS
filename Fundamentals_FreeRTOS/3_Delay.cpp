#include <Arduino.h>

TaskHandle_t task1_handle = NULL;
TaskHandle_t task2_handle = NULL;

#define LDR_PIN 10             // Define LDR pin (analog)
#define LED_PIN 11             // Define LED pin
#define TASK1_PERIOD pdMS_TO_TICKS(2000) // 2 seconds
#define TASK2_PERIOD pdMS_TO_TICKS(500)   // 0.5 seconds

static int task1_tick_count = 0; // Counter for Task1
static int task2_tick_count = 0; // Counter for Task2

void Task1_vTaskDelayUntil(void * pvParameter) {
  TickType_t xLastWakeTime = xTaskGetTickCount(); // Initialize last wake time

  for (;;) {
    int ldrValue = analogRead(LDR_PIN); // Read LDR value
    Serial.print("Task1: LDR Value read at tick: ");
    Serial.print(task1_tick_count++);
    Serial.print(", LDR Value: ");
    Serial.println(ldrValue);

    // Delay until the next 2-second period
    vTaskDelayUntil(&xLastWakeTime, TASK1_PERIOD);
  }
}

void Task2_vTaskDelay(void * pvParameters) {
  for (;;) {
    // Toggle LED based on LDR reading
    int ldrValue = analogRead(LDR_PIN);
    if (ldrValue < 512) { // Check if LDR value is below threshold (dark)
      digitalWrite(LED_PIN, HIGH); // Turn LED on in dark
    } else {
      digitalWrite(LED_PIN, LOW);  // Turn LED off in light
    }

    Serial.print("Task2: LED Toggled at tick: ");
    Serial.println(task2_tick_count++);

    // Delay for 500 milliseconds
    vTaskDelay(TASK2_PERIOD);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT); // Initialize LED pin
  pinMode(LDR_PIN, INPUT);  // Initialize LDR pin as input

  // Create tasks
  xTaskCreatePinnedToCore(Task1_vTaskDelayUntil, "Task1_vTaskDelayUntil", 2048, NULL, 1, &task1_handle, 0);
  xTaskCreatePinnedToCore(Task2_vTaskDelay, "Task2_vTaskDelay", 2048, NULL, 1, &task2_handle, 1);
}

void loop() {

}
