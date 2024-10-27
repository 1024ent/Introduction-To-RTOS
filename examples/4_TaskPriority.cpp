#include <Arduino.h>

TaskHandle_t task1_handle = NULL;
TaskHandle_t task2_handle = NULL;

#define LDR_PIN 10              // Define LDR pin
#define LED1_PIN 11             // Define LED 1 pin
#define LED2_PIN 12             // Define LED 2 pin
#define TASK2_PERIOD pdMS_TO_TICKS(1000) // Task2 toggle period in ticks (1000 ms)
#define LDR_THRESHOLD 300       // Threshold for LDR reading

void Task1_LDRMonitor(void * pvParameters) {
  for (;;) {
    int ldrValue = analogRead(LDR_PIN); // Read LDR value

    // Control LED1 based on LDR reading
    if (ldrValue < LDR_THRESHOLD) {
      digitalWrite(LED1_PIN, HIGH);  // Turn on LED1 if it's dark
    } else {
      digitalWrite(LED1_PIN, LOW);   // Turn off LED1 if it's bright
    }

    // Delay for a brief period to avoid excessive reading
    vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 100 ms
  }
}

void Task2_LEDToggle(void * pvParameters) {
  TickType_t xLastWakeTime = xTaskGetTickCount(); // Initialize the last wake time for Task2

  for (;;) {
    // Toggle LED2 state
    digitalWrite(LED2_PIN, !digitalRead(LED2_PIN));

    // Print tick count for Task2
    Serial.print("Task2 (LED2 Toggle) at tick: ");
    Serial.println(xTaskGetTickCount());

    // Check LDR value to adjust priority
    int ldrValue = analogRead(LDR_PIN);
    UBaseType_t currentPriority = uxTaskPriorityGet(NULL); // Get current priority

    if (ldrValue < LDR_THRESHOLD) {
      // Increase priority when it's dark
      if (currentPriority < 3) {
        vTaskPrioritySet(NULL, 3); // Set to higher priority (3)
        Serial.println("Increased Task2 priority to 3.");
      }
    } else {
      // Decrease priority when it's bright
      if (currentPriority > 1) {
        vTaskPrioritySet(NULL, 1); // Set to lower priority (1)
        Serial.println("Decreased Task2 priority to 1.");
      }
    }

    // Delay until the next precise cycle
    vTaskDelayUntil(&xLastWakeTime, TASK2_PERIOD); // Delay for 1 second
  }
}

void setup() {
  Serial.begin(115200);

  // Initialize LED pins as outputs
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT); // Initialize LDR pin as input

  // Create tasks with priority 1 for LDR monitor and 2 for LED toggle
  xTaskCreate(Task1_LDRMonitor, "Task1_LDRMonitor", 2048, NULL, 1, &task1_handle);
  xTaskCreate(Task2_LEDToggle, "Task2_LEDToggle", 2048, NULL, 2, &task2_handle);
}

void loop() {
  // The loop is intentionally left empty because tasks are running in the background
}
