#include <Arduino.h>

// Function declarations
void digital_input_example();  // Handles digital input for LED control
void analog_input_example();   // Handles analog input for LDR sensor control
void switch_case_example();    // Handles user input through serial monitor

// Define constants for delays
#define short_delay pdMS_TO_TICKS(1000)
#define mid_delay pdMS_TO_TICKS(5000)
#define long_delay pdMS_TO_TICKS(10000)

// Define pin numbers for LEDs, switch, and LDR
static const int led1_pin = 4;  // LED 1 pin
static const int led2_pin = 5;  // LED 2 pin
static const int switch_pin = 13; // Switch input pin
static const int ldr_pin = 14;   // LDR (Light Dependent Resistor) input pin

// Define variables
int switch_state = 0;  // Variable to store the state of the switch
int led_delay = 500;   // Delay for LED blinking (currently unused in the code)

void setup() {
    // Set pin modes for LEDs, switch, and LDR
    pinMode(led1_pin, OUTPUT);   // Set LED 1 as output
    pinMode(led2_pin, OUTPUT);   // Set LED 2 as output
    pinMode(switch_pin, INPUT);  // Set switch pin as input
    pinMode(ldr_pin, INPUT);     // Set LDR pin as input

    // Start serial communication
    Serial.begin(115200);
    delay(short_delay);  // Short delay before starting

    // Display options for the user to choose from
    Serial.println("Choose an option:");
    Serial.println("1: Turn on LED 1");
    Serial.println("2: Turn on LED 2");
}

void loop() {
    // Continuously check for user input
    switch_case_example(); 
}

// Function to handle digital input and control LEDs based on the switch state
void digital_input_example() {
    // Read the state of the switch pin
    switch_state = digitalRead(switch_pin);

    // If the switch is pressed (HIGH), turn on LED 1 and off LED 2
    if (switch_state == HIGH) {
        digitalWrite(led1_pin, HIGH);
        digitalWrite(led2_pin, LOW);
    } else {
        // If the switch is not pressed (LOW), turn off LED 1 and turn on LED 2
        digitalWrite(led1_pin, LOW);
        digitalWrite(led2_pin, HIGH);
    }
}

// Function to handle analog input from the LDR (Light Dependent Resistor)
void analog_input_example() {
    // Read the LDR value (light intensity)
    int ldr_value = analogRead(ldr_pin);

    // If light intensity is low (below 300), turn on LED 1
    if (ldr_value < 300) {
        digitalWrite(led1_pin, HIGH);
    } else {
        // If light intensity is high (300 or more), turn off LED 1
        digitalWrite(led1_pin, LOW);
    }
}

// Function to handle user input from serial monitor using a switch-case structure
void switch_case_example() {
    // Check if data is available in the serial buffer
    if (Serial.available() > 0) {
        // Read the user's input (choice)
        int choice = Serial.parseInt();

        // Turn off both LEDs before processing the new choice
        digitalWrite(led1_pin, LOW);
        digitalWrite(led2_pin, LOW);

        // Process the user's choice using a switch-case statement
        switch (choice) {
            case 1:
                // If choice is 1, turn on LED 1
                Serial.println("LED 1 is ON");
                digitalWrite(led1_pin, HIGH);
                break;
            case 2:
                // If choice is 2, turn on LED 2
                Serial.println("LED 2 is ON");
                digitalWrite(led2_pin, HIGH);
                break;
            default:
                // If the user enters anything other than 1 or 2, display an error message
                Serial.println("Invalid choice. Please enter 1 or 2.");
                break;
        }

        // Clear any remaining data in the serial buffer
        while (Serial.available() > 0) {
            Serial.read();
        }

        // Display the options again for the user to choose from
        Serial.println("Choose an option:");
        Serial.println("1: Turn on LED 1");
        Serial.println("2: Turn on LED 2");
    }

    // Small delay to avoid bouncing issues (for serial input)
    delay(100);
}
