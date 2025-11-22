#include <Arduino.h>

// Code: Blinking a LED;

// put function declarations here:
int ledPin = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin, HIGH);

  delay(2000);

  digitalWrite(ledPin, LOW);

  delay(3000);
}

// put function definitions here:
