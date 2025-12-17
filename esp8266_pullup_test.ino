// Define the GPIO pin for D1
const int buttonPin = 2; // GPIO5 is also known as D1 on many ESP8266 boards

// Variables for timing the output
unsigned long lastPrintTime = 0;
const long printInterval = 2000; // 2000 milliseconds = 2 seconds

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);
  delay(100);
  Serial.println("\n--- ESP8266 GPIO5 (D1) Pull-Up Test ---");
  
  // Set the pin as an input with the internal pull-up resistor enabled
  // GPIO5 fully supports the INPUT_PULLUP mode.
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.println("GPIO5 (D1) configured as INPUT_PULLUP.");
  Serial.println("Connect GPIO5 to GND to simulate a button press.");
}

void loop() {
  // Read the state of the input pin
  int buttonState = digitalRead(buttonPin);

  // Check if it's time to print the state
  if (millis() - lastPrintTime >= printInterval) {
    // Print the current state
    Serial.print("Current D1 State: ");
    if (buttonState == HIGH) {
      Serial.println("HIGH (Pulled Up)");
    } else {
      Serial.println("LOW (Pulled Down/GND)");
    }
    
    // Update the last print time
    lastPrintTime = millis();
  }

  // Check for the "Button Pressed" condition (LOW state)
  if (buttonState == LOW) {
    // Print the "Button Pressed!" message immediately upon detecting LOW
    Serial.println(">>> Button Pressed! <<<");
    
    // Optional: Add a small delay/debounce to prevent excessive printing
    // while the button is held down.
    delay(150); 
  }
}