#include <Arduino.h>

// Function example
void digital_input_example();
void analog_input_example();
void switch_case_example();

// Define constant
#define short_delay pdMS_TO_TICKS(1000)
#define mid_delay pdMS_TO_TICKS(5000)
#define long_delay pdMS_TO_TICKS(10000)

// Define pin
static const int led1_pin = 4;
static const int led2_pin = 5;
static const int switch_pin = 13;
static const int ldr_pin = 14;

// Define variable
int switch_state = 0;
int led_delay = 500;

void setup(){
    pinMode(led1_pin, OUTPUT);
    pinMode(led2_pin, OUTPUT);
    pinMode(switch_pin, INPUT);
    pinMode(ldr_pin, INPUT);

    Serial.begin(115200);
    delay(short_delay);

    // Display menu options to the user
    // Serial.println("Choose an option:");
    // Serial.println("1: Turn on LED 1");
    // Serial.println("2: Turn on LED 2");
}

void loop(){
    digital_input_example();
}

// Example of digital input
void digital_input_example(){
    switch_state = digitalRead(switch_pin);

    if(switch_state == HIGH) {
      digitalWrite(led1_pin, HIGH);
      digitalWrite(led2_pin, LOW);
    } else {
      digitalWrite(led1_pin, LOW);
      digitalWrite(led2_pin, HIGH);
    }    
}

void analog_input_example(){
    int ldr_value = analogRead(ldr_pin);

    if (ldr_value < 300){
        digitalWrite(led1_pin, HIGH);
    } else if (ldr_value >= 300) {
        digitalWrite(led1_pin, LOW);
    }    
}

void switch_case_example(){
    // Check if data is available in the serial buffer
    if (Serial.available() > 0) {
        // Read the user's input
        int choice = Serial.parseInt(); // Read an integer from Serial Monitor

        // Turn off both LEDs before handling the new choice
        digitalWrite(led1_pin, LOW);
        digitalWrite(led2_pin, LOW);

        // Handle the user choice using a switch-case statement
        switch (choice) {
            case 1:
                Serial.println("LED 1 is ON");
                digitalWrite(led1_pin, HIGH);  // Turn on LED 1
                break;
            case 2:
                Serial.println("LED 2 is ON");
                digitalWrite(led2_pin, HIGH);  // Turn on LED 2
                break;
            default:
                Serial.println("Invalid choice. Please enter 1 or 2.");
                break;
        }

        // Display the options again for the user to choose
        Serial.println("Choose an option:");
        Serial.println("1: Turn on LED 1");
        Serial.println("2: Turn on LED 2");
    }

    delay(100); // Small delay to avoid bouncing issues    
}
