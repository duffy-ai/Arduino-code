// Blinking LED example for Arduino
// This sketch blinks the onboard LED (typically attached to pin 13) every second.

const int ledPin = 13;     // Pin number for built-in LED

void setup() {
  pinMode(ledPin, OUTPUT); // Set pin as output
}

void loop() {
  digitalWrite(ledPin, HIGH);   // Turn the LED on
  delay(1000);                  // Wait for one second
  digitalWrite(ledPin, LOW);    // Turn the LED off
  delay(1000);                  // Wait for one second
