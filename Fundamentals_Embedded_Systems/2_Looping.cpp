#include <Arduino.h>

// Function declarations for different types of loops
void for_loop();      // Handles LED blinking with a for loop
void while_loop();    // Handles LED blinking with a while loop
void doWhile_loop();  // Handles LED blinking with a do-while loop

// Define delay period in milliseconds
static const int delay_period = pdMS_TO_TICKS(1000); // Delay for 1 second

// Define pins for the LEDs
static const int led1_pin = 4;  // Pin for LED 1
static const int led2_pin = 5;  // Pin for LED 2

void setup() {
  // Set LED pins as output
  pinMode(led1_pin, OUTPUT);
  pinMode(led2_pin, OUTPUT);

  // Start serial communication at 115200 baud rate
  Serial.begin(115200);

  // Initial delay before starting the program
  delay(delay_period);
}

void loop() {
  // Call the doWhile_loop function to blink the LED 10 times
  doWhile_loop();

  // Infinite loop to stop further code execution after 10 blinks
  while (true) {
    // No further execution beyond this point
  }
}

// Function to blink the LED 10 times using a for loop
void for_loop(){
  // Loop to blink the LED 10 times
  for (int count = 0; count < 10; count++) {
    Serial.print("Blink count: ");
    Serial.println(count + 1);  // Display the current blink count (1 to 10)

    digitalWrite(led1_pin, HIGH);  // Turn on LED
    delay(delay_period);           // Wait for the defined delay
    digitalWrite(led1_pin, LOW);   // Turn off LED
    delay(delay_period);           // Wait for the defined delay
  }
}

// Function to blink the LED 10 times using a while loop
void while_loop(){
  int count = 0;

  // Loop to blink the LED 10 times
  while(count < 10){
    Serial.print("Blink count: ");
    Serial.println(count + 1);  // Display the current blink count (1 to 10)

    digitalWrite(led1_pin, HIGH);  // Turn on LED
    delay(delay_period);           // Wait for the defined delay
    digitalWrite(led1_pin, LOW);   // Turn off LED
    delay(delay_period);           // Wait for the defined delay
    count++;                       // Increment the count
  }
}

// Function to blink the LED 10 times using a do-while loop
void doWhile_loop(){
  int count = 0;

  // Loop to blink the LED 10 times
  do {
    Serial.print("Blink count: ");
    Serial.println(count + 1);  // Display the current blink count (1 to 10)

    digitalWrite(led1_pin, HIGH);  // Turn on LED
    delay(delay_period);           // Wait for the defined delay
    digitalWrite(led1_pin, LOW);   // Turn off LED
    delay(delay_period);           // Wait for the defined delay
    count++;                       // Increment the count
  } while(count < 10);  // Continue blinking until count reaches 10
}

