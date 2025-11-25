// src/randomblinking/sos_blink.ino
// GitHub Copilot Chat Assistant
// Sends an SOS signal (Morse: ... --- ...) on pin 13 repeatedly.
// Starts with a 5 second repeat interval and increases the interval by 1 second
// every 5 seconds of elapsed time (pattern A).

const int ledPin = 13; // onboard LED

// Timing (in milliseconds)
unsigned long repeatInterval = 5000UL;       // initial repeat interval: 5s
const unsigned long increaseEvery = 5000UL;  // every 5s of elapsed time
const unsigned long increaseAmount = 1000UL; // increase by 1s
unsigned long lastIncreaseMillis = 0UL;

// Morse timing for dots and dashes
const unsigned int dotOn = 200;   // dot LED on time
const unsigned int dashOn = 3 * dotOn; // dash is 3x dot
const unsigned int intraElementGap = dotOn; // between parts of same letter
const unsigned int interLetterGap = 3 * dotOn; // between letters

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  lastIncreaseMillis = millis();
}

// Short blink for dot
void dot() {
  digitalWrite(ledPin, HIGH);
  delay(dotOn);
  digitalWrite(ledPin, LOW);
  delay(intraElementGap);
}

// Long blink for dash
void dash() {
  digitalWrite(ledPin, HIGH);
  delay(dashOn);
  digitalWrite(ledPin, LOW);
  delay(intraElementGap);
}

void sendSOS() {
  // S: ...
  dot(); dot(); dot();
  delay(interLetterGap - intraElementGap); // adjust because last element already waited intraElementGap
  // O: ---
  dash(); dash(); dash();
  delay(interLetterGap - intraElementGap);
  // S: ...
  dot(); dot(); dot();
}

void loop() {
  unsigned long now = millis();

  // Increase repeatInterval by increaseAmount for each full increaseEvery elapsed
  if (now - lastIncreaseMillis >= increaseEvery) {
    unsigned long increments = (now - lastIncreaseMillis) / increaseEvery;
    // Avoid overflow on extremely large increments (practically unlikely here)
    if (increments > 0) {
      repeatInterval += increments * increaseAmount;
      lastIncreaseMillis += increments * increaseEvery;
    }
  }

  // Send SOS pattern
  sendSOS();

  // Wait the current repeat interval before sending again
  delay(repeatInterval);
}