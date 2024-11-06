#include <Arduino.h>

// Define delay period in milliseconds
const int delay_period = 1000;

// Define pins
static const int led1_pin = 4;
static const int led2_pin = 5;

void setup() {
    pinMode(led1_pin, OUTPUT);
    pinMode(led2_pin, OUTPUT);

    Serial.begin(115200);  // Start serial communication
    delay(delay_period);   // Initial delay
}

void loop() {
    // Blink the LED 10 times
    for (int count = 0; count < 10; count++) {
        Serial.print("Blink count: ");
        Serial.println(count + 1);  // Display the blink count (1 to 10)

        digitalWrite(led1_pin, HIGH);
        delay(delay_period);
        digitalWrite(led1_pin, LOW);
        delay(delay_period);
    }

    // Stop the loop forever after 10 blinks
    while (true) {
        // Infinite loop to prevent further execution
    }
}
