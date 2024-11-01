#include <Arduino.h>
#include <stdio.h>

// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
    static const BaseType_t app_cpu = o;
#else
    static const BaseType_t app_cpu = 1;
#endif

// Settings
static const uint8_t buf_len = 20;

// Pins
static const int led_pin = 4;

// Globals
static int led_delay = 500;

// Task: Blink LED at rate set by global variable
void toggleLED(void *pvParameters){
    for(;;){
        digitalWrite(led_pin, HIGH);
        vTaskDelay(pdMS_TO_TICKS(led_delay));
        digitalWrite(led_pin, LOW);
        vTaskDelay(pdMS_TO_TICKS(led_delay));
    }
}

// Task: Read from the serial monitor
// Fell free to use Serial.readString() or Serial.parseInt(). I'm going to show
// it with atoi() in case you're doing this in annon-Arduino environment. You'd
// also need to replace Serial with your own UART code for non-Arduino.
void readSerial(void *pvParameters){
    char c;
    char buf[buf_len];
    uint8_t idx = 0;

    // Clear the whole buffer
    memset(buf, 0, buf_len);

    for(;;){
        // Read the characters from the serial
        if(Serial.available() > 0){
            c = Serial.read();

            // Update delay varaible and reset buffer if we get a newline character
            if(c == '\n'){
                led_delay = atoi(buf);
                Serial.print("Updated LED delay to: ");
                Serial.println(led_delay);
                memset(buf, 0, buf_len);
                idx = 0;
            } else {
                // Only append if the index is not over the message limit
                if(idx < buf_len -1){
                    buf[idx] = c;
                    idx++;
                }
            }
        }
    }
}

void setup(){
    // Configure pin
    pinMode(led_pin, OUTPUT);

    // Configure serial and wait a second
    Serial.begin(115200);
    vTaskDelay(pdMS_TO_TICKS(1000));
    Serial.println("Multi-task LED Demo");
    Serial.println("Enter a number in milliseconds to change the LED delay.");

    // Start blink task
    xTaskCreatePinnedToCore(
        toggleLED,          //Function to be called
        "Toggle LED",       // Name of task
        1024,               // Stack size
        NULL,               // Parameter to pass
        1,                  // Task priority
        NULL,               // Task handle
        app_cpu);           // Run on one core for demo purposes

    xTaskCreatePinnedToCore(readSerial, "Read Serial", 1024, NULL, 1, NULL, app_cpu);

    // Delete "setup and loop" task
    vTaskDelete(NULL);
}

void loop(){
    // Execution should never get here
}
