#include <Arduino.h>

// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
    static const BaseType_t app_cpu = 0;
#else 
    static const BaseType_t app_cpu = 1;
#endif

// String to be printed
const char msg[] = "Barkadeer brig Arr booty run.";

// Task handles
static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;

// Task: print to Serial Monitor with lower priority
void startTask1(void *pvParameters){
    // Count the number of characters in string
    int msg_len = strlen(msg);

    // Print string to Serial Monitor
    for(;;){
        Serial.println();
        for(int i=0; i < msg_len; i++){
            Serial.print(msg[i]);
        }
        Serial.println();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Task: print to Serial Monitor with higher priority
void startTask2(void *pvParameters){
    for(;;){
        Serial.print('*');
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void setup(){
    // Configure Serial (go slow so we can watch the preemtion)
    Serial.begin(300);

    // Wait a moment to start (so we don't miss Serial output)
    vTaskDelay(pdMS_TO_TICKS(1000));
    Serial.println();
    Serial.println("---FreeRTOS Task Demo---");

    // Print self priority
    Serial.print("Setup and loop task running on core ");
    Serial.print(xPortGetCoreID());
    Serial.print(" with priority ");
    Serial.println(uxTaskPriorityGet(NULL));

    // Task to run
    xTaskCreatePinnedToCore(startTask1, "Task 1", 1024, NULL, 1, &task_1, app_cpu);
    xTaskCreatePinnedToCore(startTask2, "Task 2", 1024, NULL, 2, &task_2, app_cpu);
}

void loop(){
    // Suspend the higher priority task for some intervals
    for(int i = 0; i < 3; i++){
        vTaskSuspend(task_2);
        vTaskDelay(pdMS_TO_TICKS(2000));
        vTaskResume(task_2);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }

    // Delete the lower priority task
    if (task_1 != NULL){
        vTaskDelete(task_1);
        task_1 = NULL;
    }
}
